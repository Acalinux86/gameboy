#include "sm83_cpu.h"

#include <stdarg.h>
#include <assert.h>

/* SM83 Error Types As Strings */
const char *sm83_error_string(enum SM83Error error)
{
    switch (error)
    {
    case SM83_OK: return "SM83_OK";
    case SM83_ERR_MEMORY: return "SM83_ERR_MEMORY";
    case SM83_ERR_INVALID_OPCODE: return "SM83_ERR_INVALID_OPCODE";
    case SM83_ERR_MMU: return "SM83_ERR_MMU";
    case SM83_ERR_NULL_CPU: return "SM83_ERR_NULL_CPU";
    case SM83_ERR_DISASM: return "SM83_ERR_DISASM";
    default: return "UNKNOWN SM83 ERROR";
    }
}

/* Helper function to tell the CPU to emit disassembly or not */
void sm83_cpu_emit_disasm(struct SM83CPU *cpu, int emit)
{
    cpu->emit_disasm = emit;
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

static inline void __sm83_set_h_for_add8(struct SM83CPU *cpu, uint8_t a, uint8_t b)
{
    if (((a & 0xF) + (b & 0xF)) > 0xF) cpu->registers.f |= (1u << H_BIT);
    else cpu->registers.f &= ~(1u << H_BIT);
}

static inline void __sm83_set_h_for_add16(struct SM83CPU *cpu, uint16_t a, uint16_t b)
{
    if (((a & 0x0FFF) + (b & 0x0FFF)) > 0x0FFF) cpu->registers.f |= (1u << H_BIT);
    else cpu->registers.f &= ~(1u << H_BIT);
}

static inline void __sm83_set_c_for_add8(struct SM83CPU *cpu, uint16_t result)
{
    /* Set C (Bit 4) if a + b overflows UINT8_MAX */
    if (result > 0xFF) cpu->registers.f |= (1u << C_BIT);
    else cpu->registers.f &= ~(1u << C_BIT);
}

static inline void __sm83_set_c_for_add16(struct SM83CPU *cpu, uint32_t result)
{
    /* Set C (Bit 4) if result overflows UINT16_MAX */
    if (result > 0xFFFF) cpu->registers.f |= (1u << C_BIT);
    else cpu->registers.f &= ~(1u << C_BIT);
}

/* Joining of 8-bit Integers */
static inline uint16_t __sm83_join_eight_bits(uint8_t hi, uint8_t lo)
{
    return (uint16_t) ((hi << 8) | lo);
}

/* Increment an 8-bit register and Update the flags */
static inline void __sm83_inc_r8(struct SM83CPU *cpu, uint8_t *reg8)
{
    uint8_t orig = *reg8;
    (*reg8)++;

    /* Update the flags */
    __sm83_set_z(cpu, *reg8);
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

/* Increment the byte pointed to by the Joined 8-bit Registers */
static inline enum SM83Error __sm83_inc_ind_r16(struct SM83CPU *cpu, uint8_t *high, uint8_t *low)
{
    uint16_t joined = __sm83_join_eight_bits(*high, *low);
    uint8_t orig = sm83_read(cpu, joined);
    uint8_t data = orig + 1;
    /* Update the flags */
    __sm83_set_z(cpu, data);
    __sm83_set_n(cpu, FLAG_ADD);
    __sm83_set_h(cpu, HALF_CARRY_INC, orig);
    return sm83_write8(cpu, data, joined);
}

/* Decrement the byte pointed to by the Joined 8-bit Registers */
static inline enum SM83Error __sm83_dec_ind_r16(struct SM83CPU *cpu, uint8_t *high, uint8_t *low)
{
    uint16_t joined = __sm83_join_eight_bits(*high, *low);
    uint8_t orig = sm83_read(cpu, joined);
    uint8_t data = orig - 1;
    /* Update the flags */
    __sm83_set_z(cpu, data);
    __sm83_set_n(cpu, FLAG_SUB);
    __sm83_set_h(cpu, HALF_CARRY_DEC, orig);
    return sm83_write8(cpu, data, joined);
}

/* Decrement an 8-bit register and Update the flags */
static inline void __sm83_dec_r8(struct SM83CPU *cpu, uint8_t *reg8)
{
    uint8_t orig = *reg8;
    (*reg8)--;

    /* Update the flags */
    __sm83_set_z(cpu, *reg8);
    __sm83_set_n(cpu, FLAG_SUB);
    __sm83_set_h(cpu, HALF_CARRY_DEC, orig);
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

/* Copy the contents of src register into dst register */
static inline void __sm83_load_r8_r8(uint8_t *dst, uint8_t *src)
{
    *dst = *src;
}

/* Load the fetched byte n8 into Register r8*/
static inline void __sm83_load_r8_n8(struct SM83CPU *cpu, uint8_t *r8)
{
    *r8 = __sm83_fetch8(cpu);
}

/* Load the fetched next two bytes n16 to joined 8-bits register r16 */
static inline void __sm83_load_r16_n16(struct SM83CPU *cpu, uint8_t *r16_high, uint8_t *r16_low)
{
    *r16_low = __sm83_fetch8(cpu); // low-order byte
    *r16_high = __sm83_fetch8(cpu); // high-order byte
}

/* Write to the memory location pointed by the joined register to the accumulator */
static inline enum SM83Error __sm83_load_r16_n8(struct SM83CPU *cpu, uint8_t high, uint8_t low, uint8_t data)
{
    uint16_t addr = __sm83_join_eight_bits(high, low);
    return sm83_write8(cpu, data, addr);
}

/*
  Write to the memory location pointed by the joined register to the accumulator,
  then increment/decrement r16
*/
static inline enum SM83Error __sm83_load_operation_r16_accumulator(struct SM83CPU *cpu, int operation, uint8_t *high, uint8_t *low)
{
    enum SM83Error ret = __sm83_load_r16_n8(cpu, *high, *low, cpu->registers.a);
    if (ret != SM83_OK) return ret;

    uint16_t joined = __sm83_join_eight_bits(*high, *low);

    /* Increment r16 Afterwards */
    if (operation == FLAG_ADD) joined++;
    /* Decrement r16 Afterwards */
    else if (operation == FLAG_SUB) joined--;

    /* Save Back the Incremented Register */
    *high = joined >> 8;
    *low = joined & 0XFF;
    return SM83_OK;
}

/* Copy the byte pointed by r16 into regiter a */
static inline void __sm83_load_accumulator_r16(struct SM83CPU *cpu, uint8_t *high, uint8_t *low)
{
    /* Join the regs, gives us address */
    uint16_t addr = __sm83_join_eight_bits(*high, *low);

    /* Copy the Read Byte into the Accumulator */
    cpu->registers.a = sm83_read(cpu, addr);
}

/* Copy the byte pointed by r16 into regiter a then increment r16 and save back individual regs */
static inline void __sm83_load_operation_accumulator_r16(struct SM83CPU *cpu, int operation, uint8_t *high, uint8_t *low)
{
    /* Copy the Byte First */
    __sm83_load_accumulator_r16(cpu, high, low);

    /* Join the regs */
    uint16_t joined = __sm83_join_eight_bits(*high, *low);

    /* Determine if we are incrementing/decrementing the joined regs */
    /* Increment r16 Afterwards */
    if (operation == FLAG_ADD) joined++;
    /* Decrement r16 Afterwards */
    else if (operation == FLAG_SUB) joined--;

    /* Save Back the Incremented Register */
    *high = joined >> 8;
    *low = joined & 0XFF;
}

/* Add Two Joined Registers ans Update the Flags */
static inline void __sm83_add_r16_r16(struct SM83CPU *cpu, uint8_t *dst_high, uint8_t *dst_low, uint8_t *src_high, uint8_t *src_low)
{
    uint16_t r16_dst = __sm83_join_eight_bits(*dst_high, *dst_low);
    uint16_t r16_src = __sm83_join_eight_bits(*src_high, *src_low);

    /* Add the Joined Registers */
    uint32_t result = (uint32_t)r16_dst + (uint32_t)r16_src;

    /* Save Back the Result */
    *dst_high = result >> 8;
    *dst_low = result & 0XFF;

    /* Update Flags */
    __sm83_set_n(cpu, FLAG_ADD);
    __sm83_set_h_for_add16(cpu, r16_dst, r16_src);
    __sm83_set_c_for_add16(cpu, result);
}

/* Add Two Scalar Registers and Update the Flags */
static inline void __sm83_add_r8_r8(struct SM83CPU *cpu, uint8_t *dst, uint8_t *src)
{
    /* Add the Joined Registers */
    uint16_t result = (uint16_t)*dst + (uint16_t)*src;

    /* Update Flags */
    __sm83_set_n(cpu, FLAG_ADD);
    __sm83_set_h_for_add8(cpu, *dst, *src);
    __sm83_set_c_for_add8(cpu, result);
}

/* Callback Function to Check a negative Jump Condition */
static inline uint8_t __sm83_jump_condition_not(void)
{
    return 0;
}

/* Callback Function to Check a positive Jump Condition */
static inline uint8_t __sm83_jump_condition_yes(void)
{
    return 1;
}

/* Relative Jump to e8 + PC if condition is met */
static inline void __sm83_relative_jump_cc_e8(struct SM83CPU *cpu, uint8_t bit_flag, uint8_t (*jump_condition)(void))
{
    /* Isolate bit_flag Bit */
    uint8_t condition = (cpu->registers.f >> bit_flag) & 1;
    int8_t offset = (int8_t)__sm83_fetch8(cpu);
    if (jump_condition() == condition) cpu->registers.pc += offset;
}

/* Relative Jump to e8 + PC */
static inline void __sm83_relative_jump_e8(struct SM83CPU *cpu)
{
    int8_t offset = (int8_t)__sm83_fetch8(cpu);
    cpu->registers.pc += offset;
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
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "nop\n");
    } break;

    case OP_LD_BC_N16:
    {
        /*
          LD BC, N16
          Copy fetched 16-bit value to Joined Registers BC
        */
        __sm83_load_r16_n16(cpu, &cpu->registers.b, &cpu->registers.c);
        uint16_t value = __sm83_join_eight_bits(cpu->registers.b, cpu->registers.c);
        /* Emit Disasm */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld bc, 0x%x ; bc = 0x%x\n", value, value);
    } break;

    case OP_LD_BC_A:
    {
        /*
          LD [BC], A
          Copy A into memory address pointed by BC
        */
        enum SM83Error ret = __sm83_load_r16_n8(cpu, cpu->registers.b, cpu->registers.c, cpu->registers.a);
        if (ret != SM83_OK) return ret;
        /* Emit Disasm */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld [bc], a ; copy accumulator into memory pointed by bc\n");
    } break;

    case OP_INC_BC:
    {
        /*
          INC BC
          increment the joined b and c registers
        */
        __sm83_inc_r16(&cpu->registers.b, &cpu->registers.c);
        /* Emit Disasm */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "inc bc ; increment the joined bc registers\n");
    } break;

    case OP_INC_B:
    {
        /*
          INC B
          Increment B register
          Update the Flags
        */
        __sm83_inc_r8(cpu, &cpu->registers.b);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "inc b ; increment b and update flags\n");
    } break;

    case OP_DEC_B:
    {
        /*
          DEC B
          Decrement Register B
          Update the Flags
        */
        __sm83_dec_r8(cpu, &cpu->registers.b);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "dec b ; decrement b and update flags\n");
    } break;

    case OP_LD_B_N8:
    {
        /*
          LD B N8
          Copy Value N8 into Register B
        */
        __sm83_load_r8_n8(cpu, &cpu->registers.b);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD B, 0x%X ; Copy 0x%x into reg B\n", cpu->registers.b, cpu->registers.b);
    } break;

    case OP_RLCA:
    {
        /*
          RLCA
          Circular Rotation
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
            cpu->registers.f |= (1u << C_BIT);
        }
        else
        {
            cpu->registers.f &= ~(1u << C_BIT);
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

        enum SM83Error ret;
        uint16_t addr = __sm83_fetch16(cpu);
        uint16_t SP = cpu->registers.sp;

        /* Write Low SP byte first */
        ret = sm83_write8(cpu, SP & 0xFF, addr);
        if (ret != SM83_OK) return ret;

        /* Write Hight SP byte second */
        ret = sm83_write8(cpu, SP >> 8, addr + 1);
        if (ret != SM83_OK) return ret;

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD [0x%04x], SP\n", addr);
    } break;

    case OP_ADD_HL_BC:
    {
        /*
          Add joined register BC to the value in HL
          Update the Flags According to the result
        */
        __sm83_add_r16_r16(cpu, &cpu->registers.h, &cpu->registers.l, &cpu->registers.b, &cpu->registers.c);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ADD HL, BC\n");
    } break;

    case OP_LD_A_BC:
    {
        /*
          LD A BC
          load the value in memory location BC into A
        */
        __sm83_load_accumulator_r16(cpu, &cpu->registers.b, &cpu->registers.c);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD A, [BC]\n");
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
        __sm83_inc_r8(cpu, &cpu->registers.c);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "INC C\n");
    } break;

    case OP_DEC_C:
    {
        /* INC Register C, also flags are updated */
        __sm83_dec_r8(cpu, &cpu->registers.c);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "DEC C\n");
    } break;

    case OP_LD_C_N8:
    {
        /*
          LD C, N8
          Copy The fetched byte to register C
        */
        __sm83_load_r8_n8(cpu, &cpu->registers.c);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD C, 0x%x\n", cpu->registers.c);
    } break;

    case OP_RRCA:
    {
        /*
          RRCA
          Rotate the accumulator to the right,
          Circular Rotation
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
            cpu->registers.f |= (C_BIT);
        }
        else
        {
            cpu->registers.f &= ~(1u << C_BIT);
        }

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "RRCA ; Rotate Accumulator Right\n");
    } break;

    case OP_STOP_N8:
    {
        /*
          STOP N8
          fetch the byte but ignore
          pause the execution until interrupt
        */
        uint8_t n8 = __sm83_fetch8(cpu);
        cpu->stopped = 1;
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "STOP 0x%x\n", n8);
    } break;

    case OP_LD_DE_N16:
    {
        /*
          LD DE, n16
          fetch 2 bytes, then copy the result into DE
        */
        __sm83_load_r16_n16(cpu, &cpu->registers.d, &cpu->registers.e);
        uint16_t n16 = __sm83_join_eight_bits(cpu->registers.d, cpu->registers.e);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD DE, 0x%x\n", n16);
    } break;

    case OP_LD_DE_A:
    {
        /*
          LD [DE], A
          write memory[DE] = a
        */
        enum SM83Error ret = __sm83_load_r16_n8(cpu, cpu->registers.d, cpu->registers.e, cpu->registers.a);
        if (ret != SM83_OK) return ret;
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD [DE], A\n");
    } break;

    case OP_INC_DE:
    {
        /* INC DE, Increment DE joined Regs */
        __sm83_inc_r16(&cpu->registers.d, &cpu->registers.e);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "INC DE\n");
    } break;

    case OP_INC_D:
    {
        /* INC D, Increment Register D */
        __sm83_inc_r8(cpu, &cpu->registers.d); /* Updates the Flag */
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "INC D\n");
    } break;

    case OP_DEC_D:
    {
        /* DEC D, Decrements D */
        __sm83_dec_r8(cpu, &cpu->registers.d);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "DEC D\n");
    } break;

    case OP_LD_D_N8:
    {
        /*
          LD D, N8
          Copy N8 into Register D
        */
        __sm83_load_r8_n8(cpu, &cpu->registers.d);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD D, 0x%x\n", cpu->registers.d);
    } break;

    case OP_RLA:
    {
        /* RLA, Rotate the Accumulator Left with the Carry Flag */

        /* Save Accumulator */
        uint8_t a = cpu->registers.a;

        /* Save Bit 7 */
        uint8_t bit7 = (cpu->registers.a >> 7) & 1;

        /* Old Carry */
        uint8_t old_carry = (cpu->registers.f >> C_BIT) & 1;

        /* bit 7 goes to 0 */
        cpu->registers.a  = (a << 1) | old_carry;

        /* Clear Z N H */
        __sm83_set_z(cpu, 0XFF);
        __sm83_set_n(cpu, FLAG_ADD);
        __sm83_set_h(cpu, HALF_CARRY_INC, 0);

        /* Set C bit according to old bit 7 */
        cpu->registers.f |= (bit7 << C_BIT);

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "RLA\n");
    } break;

    case OP_JR_E8:
    {
        /*
          JR E8
          Increment the PC with the Signed Offset Obtained from fetch8
        */
        __sm83_relative_jump_e8(cpu);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "JR 0x%x\n", cpu->registers.pc);
    } break;

    case OP_ADD_HL_DE:
    {
        /*
          ADD HL, DE
          Add Hl and DE, Save Back the bytes of the result to Individual H and L
        */
        __sm83_add_r16_r16(cpu, &cpu->registers.h, &cpu->registers.l, &cpu->registers.d, &cpu->registers.e);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ADD HL, DE\n");
    } break;

    case OP_LD_A_DE:
    {
        /*
          LD A DE
          Load the value in Memory Location DE into Accumulator
        */
        __sm83_load_accumulator_r16(cpu, &cpu->registers.d, &cpu->registers.e);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD A, [DE]\n");
    } break;

    case OP_DEC_DE:
    {
        /* DEC DE, Decrement Joined Register DE */
        __sm83_dec_r16(&cpu->registers.d, &cpu->registers.e);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "DEC DE\n");
    } break;

    case OP_INC_E:
    {
        /* INC E, Increment Register E */
        __sm83_inc_r8(cpu, &cpu->registers.e);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "INC E\n");
    } break;

    case OP_DEC_E:
    {
        /* DEC E, Deccrement Register E */
        __sm83_dec_r8(cpu, &cpu->registers.e);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "DEC E\n");
    } break;

    case OP_LD_E_N8:
    {
        /*
          LD E, N8, Copy N8 To Register E
        */
        __sm83_load_r8_n8(cpu, &cpu->registers.e);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD E, N8\n");
    } break;

    case OP_RRA:
    {
        /*
          RRCA Rotate the accumulator to the right with the Carry Bit
          update Flags
        */

        /* Save Accumulator */
        uint8_t a = cpu->registers.a;

        /* Save Bit 0 */
        uint8_t bit0 = a & 1;

        /* Old Carry */
        uint8_t old_carry = (cpu->registers.f << C_BIT) & 1;

        /* bit 0 goes to 7 */
        cpu->registers.a  = (a >> 1) | (old_carry << 7);

        /* Clear Z N H */
        __sm83_set_z(cpu, 0XFF);
        __sm83_set_n(cpu, FLAG_ADD);
        __sm83_set_h(cpu, HALF_CARRY_INC, 0);

        /* Set C bit according to old carry */
        cpu->registers.f |= (bit0 << C_BIT);

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "RRA ; Rotate Accumulator Right\n");
    } break;

    case OP_JR_NZ_E8:
    {
        /*
          JR NZ, E8
          Jump if Z flag is 0 else dont
        */
        __sm83_relative_jump_cc_e8(cpu, Z_BIT, __sm83_jump_condition_not);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "JR NZ, 0x%04x\n", cpu->registers.pc);
    } break;

    case OP_LD_HL_N16:
    {
        /*
          LD HL, N16
          Copy the value N16 into joined register r16
          Save back the Individual registers after copy
        */
        __sm83_load_r16_n16(cpu, &cpu->registers.h, &cpu->registers.l);
        uint16_t n16 = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD HL, 0x%04x\n", n16);
    } break;

    case OP_LD_HLI_A:
    {
        /*
          LD HLI, A
          Copy the value pointed by HL into A then increment HL
        */
        enum SM83Error ret = __sm83_load_operation_r16_accumulator(cpu, FLAG_ADD, &cpu->registers.h, &cpu->registers.l);
        if (ret != SM83_OK) return ret;
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD [HLI], A\n");
    } break;

    case OP_INC_HL:
    {
        /* INC HL, Increment Joined Register HL */
        __sm83_inc_r16(&cpu->registers.h, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "INC HL\n");
    } break;

    case OP_INC_H:
    {
        /* INC H, Increment Register H , Update Flags */
        __sm83_inc_r8(cpu, &cpu->registers.h);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "INC H\n");
    } break;

    case OP_DEC_H:
    {
        /* INC H, Increment Register H */
        __sm83_dec_r8(cpu, &cpu->registers.h);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "INC H\n");
    } break;

    case OP_LD_H_N8:
    {
        /* LD H, N8. Copy fetched Value n8 into H */
        __sm83_load_r8_n8(cpu, &cpu->registers.h);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD H, N8\n");
    } break;

    case OP_DAA:
    {
        /* DAA, Adjust Accumulator After BCD Operation */
        uint8_t a = cpu->registers.a;
        uint8_t n = (cpu->registers.f >> N_BIT) & 1;
        uint8_t h = (cpu->registers.f >> H_BIT) & 1;
        uint8_t c = (cpu->registers.f >> C_BIT) & 1;

        uint8_t adjust = 0;
        uint8_t C = c;

        if (n == 1)
        {
            /* If n is set */
            if (h) { adjust += 0x06; }        /* Add 0x6 if h is set */
            if (c) { adjust += 0x60; C = 1; } /* Add 0x60 if c is set */
            a -= adjust;
        }
        else
        {
            /* If n is not set */
            if (h || ((a & 0xF) > 0x09)) { adjust += 0x06; } /* Add 0x06 if h is set or a & 0xF > 0x09*/
            if (c || a > 0x99) { adjust += 0x60; C = 1; }    /* Add 0x60 if c is set or a > 0x99 */
            a += adjust;
        }

        /* Set Z if a == 0 */
        if (a == 0) cpu->registers.f |= (1u << Z_BIT);
        else cpu->registers.f &= ~(1u << Z_BIT);

        /* Clear H */
        cpu->registers.f &= ~(1u << H_BIT);

        /* C Set According to Operation */
        if (C == 1) cpu->registers.f |= (1u << C_BIT);
        else cpu->registers.f &= ~(1u << C_BIT);

        /* Write Back A */
        cpu->registers.a = a;
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "DAA\n");
    } break;

    case OP_JR_Z_E8:
    {
        /* JR Z, E8. Jump if Z == 1 else dont */
        __sm83_relative_jump_cc_e8(cpu, Z_BIT, __sm83_jump_condition_yes);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "JR Z, 0x%04x\n", cpu->registers.pc);
    } break;

    case OP_ADD_HL_HL:
    {
        /* ADD HL, HL. add the Joined register HL with itself, update the Flags*/
        __sm83_add_r16_r16(cpu, &cpu->registers.h, &cpu->registers.l, &cpu->registers.h, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ADD HL, HL\n");
    } break;

    case OP_LD_A_HLI:
    {
        /* LD A, HLI , load the byte pointed by HL into A and increment HL*/
        __sm83_load_operation_accumulator_r16(cpu, FLAG_ADD, &cpu->registers.h, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD A, [HLI]\n");
    } break;

    case OP_DEC_HL:
    {
        /* DEC, HL , Decremnt the Joined Register HL */
        __sm83_dec_r16(&cpu->registers.h, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "DEC, HL\n");
    } break;

    case OP_INC_L:
    {
        /* INC L. Increment the Register L */
        __sm83_inc_r8(cpu, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "INC, L\n");
    } break;

    case OP_DEC_L:
    {
        /* DEC L. Decrement the Register L */
        __sm83_dec_r8(cpu, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "DEC, L\n");
    } break;

    case OP_LD_L_N8:
    {
        /* LD L, N8. Copy n8 into Register L*/
        __sm83_load_r8_n8(cpu, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD L, 0x%02x\n", cpu->registers.l);
    } break;

    case OP_CPL:
    {
        /* CPL => CPL A. Complement Accumulator A = ~A */
        cpu->registers.a = ~cpu->registers.a;
        /* Set N and H */
        cpu->registers.f |= (1u << N_BIT);
        cpu->registers.f |= (1u << H_BIT);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "CPL A\n");
    } break;

    case OP_JR_NC_E8:
    {
        /*
          JR NC, E8
          Jump if C flag is 0 else dont
        */
        /* Isolate C Bit */
        __sm83_relative_jump_cc_e8(cpu, C_BIT, __sm83_jump_condition_not);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "JR NC, 0x%04x\n", cpu->registers.pc);
    } break;

    case OP_LD_SP_N16:
    {
        /* LD SP, N16. Copy N16 into Register SP */
        cpu->registers.sp = __sm83_fetch16(cpu);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD SP, 0x%04x\n", cpu->registers.sp);
    } break;

    case OP_LD_HLD_A:
    {
        /* LD HLD, A, Write memory[HL] = A, then decrement HL */
        __sm83_load_operation_r16_accumulator(cpu, FLAG_SUB, &cpu->registers.h, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD [HLD], A\n", cpu->registers.sp);
    } break;

    case OP_INC_SP:
    {
        /* INC SP. Increment Stack Pointer */
        cpu->registers.sp++;
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "INC SP\n", cpu->registers.sp);
    } break;

    case OP_IND_INC_HL:
    {
        /* Increment the byte Pointed to by HL */
        enum SM83Error ret = __sm83_inc_ind_r16(cpu, &cpu->registers.h, &cpu->registers.l);
        if (ret != SM83_OK) return ret;
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "INC [HL]\n", cpu->registers.sp);
    } break;

    case OP_IND_DEC_HL:
    {
        /* Decrement the byte Pointed to by HL */
        enum SM83Error ret = __sm83_dec_ind_r16(cpu, &cpu->registers.h, &cpu->registers.l);
        if (ret != SM83_OK) return ret;
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "DEC [HL]\n", cpu->registers.sp);
    } break;

    case OP_LD_HL_N8:
    {
        /* LD HL, N8. Copy the the next byte into the byte in memory pointed by HL */
        uint8_t n8 = __sm83_fetch8(cpu);
        __sm83_load_r16_n8(cpu, cpu->registers.h, cpu->registers.l, n8);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD [HL], 0x%02x\n", n8);
    } break;

    case OP_SCF:
    {
        /* SCF, Set Carry Flag bit */
        cpu->registers.f |= (1u << C_BIT);
        /* Clear N and H flag bits*/
        cpu->registers.f &= ~(1u << N_BIT);
        cpu->registers.f &= ~(1u << H_BIT);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "SCF\n");
    } break;

    case OP_JR_C_E8:
    {
        /* JR C, E8. Jump if C flag bit is 1*/
        __sm83_relative_jump_cc_e8(cpu, C_BIT, __sm83_jump_condition_yes);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "JR C, 0x%02x\n", cpu->registers.pc);
    } break;

    case OP_ADD_HL_SP:
    {
        /* ADD HL, SP. Add the Joined Registers HL to Stack Pointer */
        uint8_t sp_high = (cpu->registers.sp >> 8);
        uint8_t sp_low = (cpu->registers.sp & 0xFF);
        __sm83_add_r16_r16(cpu, &cpu->registers.h, &cpu->registers.l, &sp_high, &sp_low);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ADD HL, SP\n", cpu->registers.pc);
    } break;

    case OP_LD_A_HLD:
    {
        /* LD A, HLD, load the byte in memory address HL and then decement HL */
        __sm83_load_operation_accumulator_r16(cpu, FLAG_SUB, &cpu->registers.h, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD A, [HLD]\n", cpu->registers.pc);
    } break;

    case OP_DEC_SP:
    {
        /* DEC SP. Decrement SP*/
        cpu->registers.sp--;
    } break;

    case OP_INC_A:
    {

    } break;

    case OP_DEC_A:
    {

    } break;

    case OP_LD_A_N8:
    {

    } break;

    case OP_CCF:
    {

    } break;




    case OP_LD_L_D:
    {
        __sm83_load_r8_r8(&cpu->registers.l, &cpu->registers.d);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "LD L, D\n");
    } break;

    default:
        fprintf(stderr, "ERROR: `0x%x`, `%s` Intruction Not Handled Yet\n", instr, sm83_opcode_as_cstr(instr));
        return SM83_ERR_INVALID_OPCODE;
    }
    return SM83_OK;
}
