#include "sm83_cpu.h"

#include <stdarg.h>
#include <assert.h>

/* Global Temporary Variable to append the disassembly String. */
char tmp_buf[MAX_TMP_BUF_SIZE];

/* Modifies The CPU, Writes Back 8 bit data */
enum SM83Error sm83_write8(struct SM83CPU *cpu, const uint8_t data, const uint16_t addr)
{
    if (cpu == NULL) return SM83_ERR_NULL_CPU;
    int ret = mmu_write(cpu->mmu, addr, data);
    if (ret != 0) return SM83_ERR_MMU;
    return SM83_OK;
}

/* Returns the byte pointed by the addr  */
uint8_t sm83_read(const struct SM83CPU *cpu, const uint16_t addr)
{
    assert(cpu != NULL);
    uint8_t data = mmu_read(cpu->mmu, addr);
    return data;
}

/*Modifies the CPU, fetches 8-bit Data */
static inline uint8_t __sm83_fetch8(struct SM83CPU *cpu)
{
    return sm83_read(cpu, cpu->registers.pc++);
}

/* Modifies the CPU, fetches 16 bit data */
static inline uint16_t __sm83_fetch16(struct SM83CPU *cpu)
{
    uint8_t lo = sm83_read(cpu, cpu->registers.pc++);
    uint8_t hi = sm83_read(cpu, cpu->registers.pc++);
    return (hi << 8) | lo;
}

/* Initializer the sm83 cpu members */
enum SM83Error sm83_cpu_init(struct SM83CPU *cpu, FILE *fp, uint16_t pc)
{
    /* Initialize the Program Counter */
    cpu->registers.pc = pc;

    /* Emit Disassembly Flag is False By default */
    cpu->emit_disasm = 0;

    /* If Emit Disassembly is True Allocate Memory */
    if (cpu->emit_disasm)
    {
        cpu->disasm.disasm_size  = 0;
        cpu->disasm.disasm_cap   = DISASM_CAP;
        cpu->disasm.disasm_items = (char **)malloc(sizeof(*cpu->disasm.disasm_items)*cpu->disasm.disasm_cap);
        if (cpu->disasm.disasm_items == NULL)
        {
            fprintf(stderr, "Failed to Allocate Memory For Disasm Buffer\n");
            return SM83_ERR_MEMORY;
        }
    } else {
        /* Dont Allocate anything and Zero Initialize the Disasm Members */
        cpu->disasm.disasm_size   = 0;
        cpu->disasm.disasm_cap    = 0;
        cpu->disasm.disasm_items = NULL;
    }

    /* Allocate And Initialize the Memory Management Unit */
    cpu->mmu = malloc(sizeof(*cpu->mmu));
    if (cpu->mmu == NULL)
    {
        fprintf(stderr, "Failed To Allocate Memory Management Unit\n");
        return SM83_ERR_MEMORY;
    }

    int ret = mmu_init(cpu->mmu, fp);
    if (ret != 0)
    {
        fprintf(stderr, "Failed To Initialize the Memory Management Unit\n");
        return SM83_ERR_MMU;
    }

    return SM83_OK;
}

/* Shutdown the CPU and free the allocated members */
enum SM83Error sm83_cpu_shutdown(struct SM83CPU *cpu)
{
    if (cpu == NULL) return SM83_ERR_NULL_CPU;
    /*
      Free Allocated Memory For the Disassembly Buffer
    */
    if (cpu->emit_disasm)
    {
        if (cpu->disasm.disasm_items == NULL) return SM83_ERR_MEMORY;
        for (size_t i = 0; i < cpu->disasm.disasm_size; ++i)
        {
            if (cpu->disasm.disasm_items[i] == NULL) return -1;
            free(cpu->disasm.disasm_items[i]);
            cpu->disasm.disasm_items[i] = NULL;
        }
        free(cpu->disasm.disasm_items);
        cpu->disasm.disasm_items = NULL;
    }

    /*
      Destroy The Memory Management Unit
    */
    int ret = mmu_destroy(cpu->mmu);
    if (ret != 0) return SM83_ERR_MMU;

    /* Free the MMU pointer in the CPU */
    free(cpu->mmu);
    return SM83_OK;
}

/* Helper function to tell the CPU to emit disassembly or not */
void sm83_cpu_emit_disasm(struct SM83CPU *cpu, int emit)
{
    cpu->emit_disasm = emit;
}

enum
{
    Z_BIT = 0x07, /* Zero Flag */
    N_BIT = 0x06, /* Subtraction Flag */
    H_BIT = 0x05, /* Half Carry Flag */
    C_BIT = 0x04, /* Carry Flag */
};

static inline void __sm83_set_z(struct SM83CPU *cpu, uint8_t value)
{
    /* Set Z (Bit 7) if value == 0 */
    if (value == 0) cpu->registers.f |= (1u << Z_BIT);
    else cpu->registers.f &= ~(1u << Z_BIT);
}

enum
{
    FLAG_ADD = 0x01,
    FLAG_SUB = 0x02,
};

static inline void __sm83_set_n(struct SM83CPU *cpu, uint8_t operation)
{
    switch (operation)
    {

        /* case Addtion Clear the N bit in Flag Reg */
    case FLAG_ADD: cpu->registers.f &= ~(1u << N_BIT); break;

        /* case Subtraction set the N bit in Flag Reg */
    case FLAG_SUB: cpu->registers.f |= (1u << N_BIT); break;

    default:
        fprintf(stderr, "ERROR: Unknown case %d\n", operation);
        abort();
    }
}

enum
{
    HALF_CARRY_DEC,
    HALF_CARRY_INC,
};

static inline void __sm83_set_h(struct SM83CPU *cpu, int operation, uint8_t value)
{
    switch (operation)
    {

    case HALF_CARRY_DEC:
    {
        if ((value & 0xF) == 0) cpu->registers.f |= (1u << H_BIT);
        else cpu->registers.f &= ~(1u << H_BIT);
    } break;

    case HALF_CARRY_INC:
    {
        if ((value & 0xF) == 0xF) cpu->registers.f |= (1u << H_BIT);
        else cpu->registers.f &= ~(1u << H_BIT);
    } break;

    default:
        fprintf(stderr, "ERROR: Unknown Half Carry Bit Operation: %d\n", operation);
        abort();
    }
}

static inline void __sm83_set_h_for_add(struct SM83CPU *cpu, uint8_t a, uint8_t b)
{
    if ((a & 0xF) + (b & 0xF) > 0xF) cpu->registers.f |= (1u << H_BIT);
    else cpu->registers.f &= ~(1u << H_BIT);
}

static inline void __sm83_set_c(struct SM83CPU *cpu, uint8_t value)
{
    /* Set C (Bit 4) if value > UINT8_MAX */
    uint16_t casted = (uint16_t)value;
    if (casted > 0xFF) cpu->registers.f |= (1u << C_BIT);
    else cpu->registers.f &= ~(1u << 4);
}

/* Joining of 8-bit Integers */
static inline uint16_t __sm83_join_eight_bits(uint8_t hi, uint8_t lo)
{
    return (uint16_t) ((hi << 8) | lo);
}

/* Function to Copy Data into Registers */
static inline void __sm83_copy_to_bc(struct SM83CPU *cpu, uint8_t B, uint8_t C)
{
    cpu->registers.b = B;
    cpu->registers.c = C;
}

/* Increment an 8-bit register and Update the flags */
static inline void __sm83_inc_r8(struct SM83CPU *cpu, uint8_t reg8)
{
    uint8_t orig = reg8;
    reg8++;

    /* Update the flags */
    __sm83_set_z(cpu, reg8);
    __sm83_set_n(cpu, FLAG_ADD);
    __sm83_set_h(cpu, HALF_CARRY_INC, orig);
}

/* Increment the Joined 8-bit Registers and Save Back to the individual 8-bit Registers */
static inline void __sm83_inc_r16(uint8_t *high, uint8_t *low)
{
    uint16_t joined = __sm83_join_eight_bits(*high, *low);
    joined++;

    /* Save Back the Result */
    *high = joined >> 8;
    *low  = joined & 0XFF;
}

/* Decrement an 8-bit register and Update the flags */
static inline void __sm83_dec_r8(struct SM83CPU *cpu, uint8_t reg8)
{
    uint8_t orig = reg8;
    reg8--;

    /* Update the flags */
    __sm83_set_z(cpu, reg8);
    __sm83_set_n(cpu, FLAG_SUB);
    __sm83_set_h(cpu, HALF_CARRY_INC, orig);
}

/* Decrement the Joined 8-bit Registers and Save Back to the individual 8-bit Registers */
static inline void __sm83_dec_r16(uint8_t *high, uint8_t *low)
{
    uint16_t joined = __sm83_join_eight_bits(*high, *low);
    joined--;

    /* Save Back the Result */
    *high = joined >> 8;
    *low  = joined & 0XFF;
}

/* Decode the Instructions */
enum SM83Error sm83_decode(struct SM83CPU *cpu)
{
    /* Read the Instruction From the ROM */
    uint8_t instr = __sm83_fetch8(cpu);

    /* Emit Status */
    int emit = cpu->emit_disasm;

    switch (instr) {
    case OP_NOP:
    {
        /* NOP: DO NOTHING */
        /* Emit Disasm */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "NOP\n");
    } break;

    case OP_LD_BC_N16:
    {
        /*
          LD BC, N16
          Copy fetched 16-bit value to Joined Registers BC
        */

        uint8_t C = __sm83_fetch8(cpu); // low-order byte
        uint8_t B = __sm83_fetch8(cpu); // high-order byte
        __sm83_copy_to_bc(cpu, B,  C);

        uint16_t value = __sm83_join_eight_bits(B, C);

        /* Emit Disasm */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD BC, 0x%x ; BC = 0x%x\n", value, value);
    } break;

    case OP_LD_BC_A:
    {
        /*
          LD [BC], A
          Copy A into memory address pointed by BC
        */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.b, cpu->registers.c);

        enum SM83Error ret = sm83_write8(cpu, cpu->registers.a, addr);
        if (ret != SM83_OK) return ret;

        /* Emit Disasm */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD [BC], A ; Copy Accumulator into Memory Pointed by BC\n");
    } break;

    case OP_INC_BC:
    {
        /*
          INC BC
          increment the joined b and c registers
        */
        __sm83_inc_r16(&cpu->registers.b, &cpu->registers.c);
        /* Emit Disasm */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "INC BC ; Increment the Joined BC Registers\n");
    } break;

    case OP_INC_B:
    {
        /*
          INC B
          Increment B register
          Update the Flags
        */
        __sm83_inc_r8(cpu, cpu->registers.b);

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "INC B ; Increment B and Update Flags\n");
    } break;

    case OP_DEC_B:
    {
        /*
          DEC B
          Decrement Register B
          Update the Flags
        */
        __sm83_dec_r8(cpu, cpu->registers.b);

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "DEC B ; Decrement B and Update Flags\n");
    } break;

    case OP_LD_B_N8:
    {
        /*
          LD B N8
          Copy Value N8 into Register B
        */

        uint8_t n8 = __sm83_fetch8(cpu);
        cpu->registers.b = n8;

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD B, 0x%X ; Copy 0x%x into reg B\n", n8, n8);
    } break;

    case OP_RLCA:
    {
        /*
          RLCA
          Rotate the accumulator to the Left,
          update Flags
        */

        /* Save Accumulator */
        uint8_t a = cpu->registers.a;

        /* Save Bit 7 */
        uint8_t bit7 = (cpu->registers.a >> 7) & 1;

        /* bit 7 goes to 0 */
        cpu->registers.a  = (a << 1) | bit7;

        /* Clear Z N H */
        __sm83_set_z(cpu, 0XFF);
        __sm83_set_n(cpu, FLAG_ADD);
        __sm83_set_h(cpu, HALF_CARRY_INC, 0);

        /* Set C bit according to result */
        if (a & 0x80)
        {
            cpu->registers.f |= (1u << 4);
        }
        else
        {
            cpu->registers.f &= ~(1u << 4);
        }

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "RLCA ; Rotate Accumulator Left\n");
    } break;

    case OP_LD_A16_SP:
    {
        /*
          LD A16, SP
          fetch16 addr
          write memory[addr] = high SP
          write memory[addr + 1] = low SP
        */

        uint16_t addr = __sm83_fetch16(cpu);
        uint16_t SP = cpu->registers.sp;
        sm83_write8(cpu, SP & 0xFF, addr);
        sm83_write8(cpu, SP >> 8,   addr + 1);

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD (a16), SP\n");
    } break;

    case OP_ADD_HL_BC:
    {
        /*
          Add joined register BC to the value in HL
          Update the Flags According to the result
        */

        /* Join the Registers */
        uint16_t HL = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        uint16_t BC = __sm83_join_eight_bits(cpu->registers.b, cpu->registers.c);

        /* Add the Joined Registers */
        uint32_t result = (uint32_t)HL + (uint32_t)BC;

        /* Save Back the Result */
        cpu->registers.h = result >> 8;
        cpu->registers.l = result & 0XFF;

        /* Update Flags */
        __sm83_set_n(cpu, FLAG_ADD);

        if (((HL & 0x0FFF) + (BC & 0x0FFF)) > 0x0FFF) cpu->registers.f |= (1u << H_BIT);
        else cpu->registers.f &= ~(1u << H_BIT);

        if (result > 0xFFFF) cpu->registers.f |= (1u << C_BIT);
        else cpu->registers.f &= ~(1u << C_BIT);

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ADD HL, BC\n");
    } break;

    case OP_LD_A_BC:
    {
        /*
          LD A BC
          load the value in memory location BC into A
        */

        /* Join the regs, gives us address */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.b, cpu->registers.c);

        /* Copy the Read Byte into the Accumulator */
        cpu->registers.a = sm83_read(cpu, addr);

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD A, (BC)\n");
    } break;

    case OP_DEC_BC:
    {
        /*
          DEC BC
          Decrement joined regs BC by 1
        */
        __sm83_dec_r16(&cpu->registers.b, &cpu->registers.c);

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "DEC BC\n");
    } break;

    case OP_INC_C:
    {
        /* INC Register C, also flags are updated */
        __sm83_inc_r8(cpu, cpu->registers.c);

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "INC C\n");
    } break;

    case OP_DEC_C:
    {
        /* INC Register C, also flags are updated */
        __sm83_dec_r8(cpu, cpu->registers.c);

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "DEC C\n");
    } break;

    case OP_LD_C_N8:
    {
        /*
          LD C, N8
          Copy The fetched byte to register C
        */

        uint8_t n8 = __sm83_fetch8(cpu);
        cpu->registers.c = n8;

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD C, 0x%x\n", n8);
    } break;

    case OP_RRCA:
    {
        /*
          RRCA
          Rotate the accumulator to the right,
          update Flags
        */

        /* Save Accumulator */
        uint8_t a = cpu->registers.a;

        /* Save Bit 0 */
        uint8_t bit0 = a & 1;

        /* bit 0 goes to 7 */
        cpu->registers.a  = (a >> 1) | (bit0 << 7);

        /* Clear Z N H */
        __sm83_set_z(cpu, 0XFF);
        __sm83_set_n(cpu, FLAG_ADD);
        __sm83_set_h(cpu, HALF_CARRY_INC, 0);

        /* Set C bit according to result */
        if (a & 0x80)
        {
            cpu->registers.f |= (1u << 4);
        }
        else
        {
            cpu->registers.f &= ~(1u << 4);
        }

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "RRCA ; Rotate Accumulator Right\n");
    } break;

    default:
        fprintf(stderr, "ERROR: `0x%x`, `%s` Intruction Not Handled Yet\n", instr, sm83_opcode_as_cstr(instr));
        return -1;
    }
    return 0;
}
