#include "sm83_cpu.h"

#include <stdarg.h>
#include <assert.h>

/* SM83 Error Types As Strings */
const char *sm83_error_string(enum SM83Error error)
{
    switch (error)
    {
    case SM83_OK:                 return "SM83_OK";
    case SM83_ERR_MEMORY:         return "SM83_ERR_MEMORY";
    case SM83_ERR_INVALID_OPCODE: return "SM83_ERR_INVALID_OPCODE";
    case SM83_ERR_MMU:            return "SM83_ERR_MMU";
    case SM83_ERR_NULL_CPU:       return "SM83_ERR_NULL_CPU";
    case SM83_ERR_DISASM:         return "SM83_ERR_DISASM";
    case SM83_ERR_ILLEGAL_ACCESS: return "SM83_ERR_ILLEGAL_ACCESS";
    default:                      return "UNKNOWN SM83 ERROR";
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
        free(cpu->mmu);
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
            if (cpu->disasm.disasm_items[i] == NULL) return SM83_ERR_MEMORY;
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

static inline uint8_t __sm83_get_flag_bit(struct SM83CPU *cpu, uint8_t bit_flag)
{
    return (cpu->registers.f >> bit_flag) & 1;
}

static inline void __sm83_set_z(struct SM83CPU *cpu, uint32_t value)
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

enum
{
    HALF_CARRY_DEC,
    HALF_CARRY_INC,
};

static inline void __sm83_set_n(struct SM83CPU *cpu)
{
    cpu->registers.f |= (1u << N_BIT);
}

static inline void __sm83_clr_n(struct SM83CPU *cpu)
{
    cpu->registers.f &= ~(1u << N_BIT);
}

static inline void __sm83_clr_z(struct SM83CPU *cpu)
{
    cpu->registers.f &= ~(1u << Z_BIT);
}

static inline void __sm83_set_h(struct SM83CPU *cpu)
{
    cpu->registers.f |= (1u << H_BIT);
}

static inline void __sm83_clr_h(struct SM83CPU *cpu)
{
    cpu->registers.f &= ~(1u << H_BIT);
}

static inline void __sm83_set_h_with_operation(struct SM83CPU *cpu, int operation, uint8_t value)
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

static inline void __sm83_set_h_for_adc8(struct SM83CPU *cpu, uint8_t a, uint8_t b, uint8_t carry)
{
    if (((a & 0xF) + (b & 0xF) + carry) > 0xF) cpu->registers.f |= (1u << H_BIT);
    else cpu->registers.f &= ~(1u << H_BIT);
}

static inline void __sm83_set_h_for_add16(struct SM83CPU *cpu, uint16_t a, uint16_t b)
{
    if (((a & 0x0FFF) + (b & 0x0FFF)) > 0x0FFF) cpu->registers.f |= (1u << H_BIT);
    else cpu->registers.f &= ~(1u << H_BIT);
}

static inline void __sm83_set_h_for_sub8(struct SM83CPU *cpu, uint8_t a, uint8_t b)
{
    if ((a & 0xF) < (b & 0xF)) cpu->registers.f |= (1u << H_BIT);
    else cpu->registers.f &= ~(1u << H_BIT);
}

static inline void __sm83_set_h_for_sbc8(struct SM83CPU *cpu, uint8_t a, uint8_t b, uint8_t carry)
{
    if ((a & 0xF) < ((b & 0xF) + carry)) cpu->registers.f |= (1u << H_BIT);
    else cpu->registers.f &= ~(1u << H_BIT);
}

static inline void __sm83_set_h_for_sub16(struct SM83CPU *cpu, uint16_t a, uint16_t b)
{
    if ((a & 0x0FFF) < (b & 0x0FFF)) cpu->registers.f |= (1u << H_BIT);
    else cpu->registers.f &= ~(1u << H_BIT);
}

static inline void __sm83_clr_c(struct SM83CPU *cpu)
{
    cpu->registers.f &= ~(1u << C_BIT);
}

static inline void __sm83_set_c(struct SM83CPU *cpu)
{
    cpu->registers.f |= (1u << C_BIT);
}

static inline void __sm83_set_c_for_add8(struct SM83CPU *cpu, uint16_t result)
{
    /* Set C (Bit 4) if result overflows UINT8_MAX */
    if (result > 0xFF) cpu->registers.f |= (1u << C_BIT);
    else cpu->registers.f &= ~(1u << C_BIT);
}

static inline void __sm83_set_c_for_add16(struct SM83CPU *cpu, uint32_t result)
{
    /* Set C (Bit 4) if result overflows UINT16_MAX */
    if (result > 0xFFFF) cpu->registers.f |= (1u << C_BIT);
    else cpu->registers.f &= ~(1u << C_BIT);
}

static inline void __sm83_set_c_for_sub8(struct SM83CPU *cpu, uint8_t a, uint8_t b)
{
    /* Set C (Bit 4) if a < b */
    if (a < b) cpu->registers.f |= (1u << C_BIT);
    else cpu->registers.f &= ~(1u << C_BIT);
}

static inline void __sm83_set_c_for_sbc8(struct SM83CPU *cpu, uint8_t a, uint8_t b, uint8_t carry)
{
    /* Set C (Bit 4) if a < b + carry */
    if (a < (b + carry)) cpu->registers.f |= (1u << C_BIT);
    else cpu->registers.f &= ~(1u << C_BIT);
}

static inline void __sm83_set_c_for_sub16(struct SM83CPU *cpu, uint8_t a, uint8_t b)
{
    /* Set C (Bit 4) if a < b */
    if (a < b) cpu->registers.f |= (1u << C_BIT);
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
    __sm83_clr_n(cpu);
    __sm83_set_h_with_operation(cpu, HALF_CARRY_INC, orig);
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
    __sm83_clr_n(cpu);
    __sm83_set_h_with_operation(cpu, HALF_CARRY_INC, orig);
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
    __sm83_set_n(cpu);
    __sm83_set_h_with_operation(cpu, HALF_CARRY_DEC, orig);
    return sm83_write8(cpu, data, joined);
}

/* Decrement an 8-bit register and Update the flags */
static inline void __sm83_dec_r8(struct SM83CPU *cpu, uint8_t *reg8)
{
    uint8_t orig = *reg8;
    (*reg8)--;

    /* Update the flags */
    __sm83_set_z(cpu, *reg8);
    __sm83_set_n(cpu);
    __sm83_set_h_with_operation(cpu, HALF_CARRY_DEC, orig);
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

/* Write to the memory location pointed by the high and low address to the place specified */
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

/* Copy the byte pointed by r16 into register specified */
static inline void __sm83_load_r8_r16(struct SM83CPU *cpu, uint8_t *high, uint8_t *low, uint8_t *reg8)
{
    /* Join the regs, gives us address */
    uint16_t addr = __sm83_join_eight_bits(*high, *low);

    /* Copy the Read Byte into reg8 */
    *reg8 = sm83_read(cpu, addr);
}

/* Copy the byte pointed by r16 into register a then increment r16 and save back individual regs */
static inline void __sm83_load_operation_accumulator_r16(struct SM83CPU *cpu, int operation, uint8_t *high, uint8_t *low)
{
    /* Copy the Byte First */
    __sm83_load_r8_r16(cpu, high, low, &cpu->registers.a);

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

/* Add Two Joined Registers and Update the Flags */
static inline void __sm83_add_r16_r16(struct SM83CPU *cpu, uint8_t *dst_high, uint8_t *dst_low, uint8_t *src_high, uint8_t *src_low)
{
    uint16_t r16_dst = __sm83_join_eight_bits(*dst_high, *dst_low);
    uint16_t r16_src = __sm83_join_eight_bits(*src_high, *src_low);

    /* Add the Joined Registers */
    uint32_t result = (uint32_t)r16_dst + (uint32_t)r16_src;

    /* Update Flags */
    __sm83_set_z(cpu, result);
    __sm83_clr_n(cpu);
    __sm83_set_h_for_add16(cpu, r16_dst, r16_src);
    __sm83_set_c_for_add16(cpu, result);

    /* Save Back the Result */
    *dst_high = result >> 8;
    *dst_low = result & 0XFF;
}

/* Add Two Scalar Registers and Update the Flags */
static inline void __sm83_add_r8_r8(struct SM83CPU *cpu, uint8_t *dst, uint8_t *src)
{
    /* Add the Joined Registers */
    uint16_t result = (uint16_t)*dst + (uint16_t)*src;

    /* Update Flags */
    __sm83_set_z(cpu, (uint16_t)result);
    __sm83_clr_n(cpu);
    __sm83_set_h_for_add8(cpu, *dst, *src);
    __sm83_set_c_for_add8(cpu, result);

    /* Save Back the result to dst register */
    *dst = (uint8_t) result;
}

/* Add Two Scalar Registers with the carry flag and Update the Flags */
static inline void __sm83_adc_r8_r8(struct SM83CPU *cpu, uint8_t *dst, uint8_t *src)
{
    /* Isolate the Carry Flag from the previous operation */
    uint8_t carry = (cpu->registers.f >> C_BIT) & 1;

    /* Add the Joined Registers */
    uint16_t result = (uint16_t)*dst + (uint16_t)*src + carry;

    /* Update Flags */
    __sm83_set_z(cpu, (uint16_t)result);
    __sm83_clr_n(cpu);
    __sm83_set_h_for_adc8(cpu, *dst, *src, carry);
    __sm83_set_c_for_add8(cpu, result);

    /* Save Back the result to dst register */
    *dst = (uint8_t) result;
}

/* Subtract Two Scalar Registers and Update the Flags */
static inline void __sm83_sub_r8_r8(struct SM83CPU *cpu, uint8_t *dst, uint8_t *src)
{
    /* Subtract the Joined Registers */
    uint16_t result = (uint16_t)*dst - (uint16_t)*src;

    /* Update Flags */
    __sm83_set_z(cpu, (uint16_t)result);
    __sm83_set_n(cpu);
    __sm83_set_h_for_sub8(cpu, *dst, *src);
    __sm83_set_c_for_sub8(cpu, *dst, *src);

    /* Save Back the result to dst register */
    *dst = (uint8_t) result;
}

/* Subtract Two Scalar Registers with the carry flag and Update the Flags */
static inline void __sm83_sbc_r8_r8(struct SM83CPU *cpu, uint8_t *dst, uint8_t *src)
{
    /* Isolate the Carry Flag from the previous operation */
    uint8_t carry = (cpu->registers.f >> C_BIT) & 1;

    /* Subtract the Registers with Carry */
    uint16_t result = (uint16_t)*dst - (uint16_t)*src - carry;

    /* Update Flags */
    __sm83_set_z(cpu, (uint16_t)result);
    __sm83_set_n(cpu);
    __sm83_set_h_for_sbc8(cpu, *dst, *src, carry);
    __sm83_set_c_for_sbc8(cpu, *dst, *src, carry);

    /* Save Back the result to dst register */
    *dst = (uint8_t) result;
}

/* And Two Scalar Values and Update the Flags */
static inline void __sm83_and_r8_r8(struct SM83CPU *cpu, uint8_t *dst, uint8_t *src)
{
    /* AND the Values */
    uint8_t result = *dst & *src;

    /* Update Flags */
    __sm83_set_z(cpu, (uint8_t)result);
    __sm83_clr_n(cpu); /* Clears N */
    __sm83_set_h(cpu); /* Set H */
    __sm83_clr_c(cpu); /* Clear C */

    /* Save Back the result to dst register */
    *dst = result;
}

/* Xor Two Scalar Values and Update the Flags */
static inline void __sm83_xor_r8_r8(struct SM83CPU *cpu, uint8_t *dst, uint8_t *src)
{
    /* xor the Values */
    uint8_t result = *dst ^ *src;

    /* Update Flags */
    __sm83_set_z(cpu, (uint8_t)result);
    __sm83_clr_n(cpu); /* Clears N */
    __sm83_clr_h(cpu); /* Clear H */
    __sm83_clr_c(cpu); /* Clear C */

    /* Save Back the result to dst register */
    *dst = result;
}

/* Compare Two Scalar Registers and Update the Flags */
static inline void __sm83_cp_r8_r8(struct SM83CPU *cpu, uint8_t *dst, uint8_t *src)
{
    /* Compare the Joined Registers but dont save back the result */
    uint16_t result = (uint16_t)*dst - (uint16_t)*src;

    /* Update Flags */
    __sm83_set_z(cpu, (uint16_t)result);
    __sm83_set_n(cpu);
    __sm83_set_h_for_sub8(cpu, *dst, *src);
    __sm83_set_c_for_sub8(cpu, *dst, *src);

}

/* OR Two Scalar Values and Update the Flags */
static inline void __sm83_or_r8_r8(struct SM83CPU *cpu, uint8_t *dst, uint8_t *src)
{
    /* OR the Values */
    uint8_t result = *dst | *src;

    /* Update Flags */
    __sm83_set_z(cpu, (uint8_t)result);
    __sm83_clr_n(cpu); /* Clears N */
    __sm83_clr_h(cpu); /* Clear H */
    __sm83_clr_c(cpu); /* Clear C */

    /* Save Back the result to dst register */
    *dst = result;
}

enum Condition
{
    COND_NZ,
    COND_Z,
    COND_NC,
    COND_C,

    COND_COUNT,
};

typedef uint8_t (*ConditionCheck)(struct SM83CPU *);

static inline uint8_t check_nz(struct SM83CPU *cpu)
{
    return !(cpu->registers.f & (1u << Z_BIT));
}

static inline uint8_t check_z(struct SM83CPU *cpu)
{
    return (cpu->registers.f & (1u << Z_BIT)) != 0;
}

static inline uint8_t check_nc(struct SM83CPU *cpu)
{
    return !(cpu->registers.f & (1u << C_BIT));
}

static inline uint8_t check_c(struct SM83CPU *cpu)
{
    return (cpu->registers.f & (1u << C_BIT)) != 0;
}

static ConditionCheck checks[COND_COUNT] =
{
    [COND_NZ] = check_nz,
    [COND_Z]  = check_z,
    [COND_NC] = check_nc,
    [COND_C]  = check_c,
};

/* Relative Jump to e8 + PC if condition is met */
static inline void __sm83_relative_jump_cc(struct SM83CPU *cpu, uint8_t bit_flag, enum Condition condition)
{
    /* Isolate bit_flag Bit */
    uint8_t flag = (cpu->registers.f >> bit_flag) & 1;
    int8_t offset = (int8_t)__sm83_fetch8(cpu);
    if (checks[condition](cpu) == flag)
    {
        cpu->cycles += 3;
        cpu->registers.pc += (int16_t)offset;
    }
    else
    {
        cpu->cycles += 2;
    }
}

/* Relative Jump to e8 + PC */
static inline void __sm83_relative_jump(struct SM83CPU *cpu)
{
    int8_t offset = (int8_t)__sm83_fetch8(cpu);
    cpu->registers.pc += (int16_t)offset;
    cpu->cycles += 3;
}

/* Absolute Jump to the address specified if condition is met */
static inline void __sm83_jump_cc(struct SM83CPU *cpu, uint8_t bit_flag, enum Condition condition)
{
    /* Isolate bit_flag Bit */
    uint8_t flag = (cpu->registers.f >> bit_flag) & 1;
    uint16_t addr = __sm83_fetch16(cpu);
    if (checks[condition](cpu) == flag)
    {
        cpu->registers.pc = addr;
        cpu->cycles += 4;
    }
    else
    {
        cpu->cycles += 2;
    }
}

/* Absolute Jump to address specified */
static inline void __sm83_jump(struct SM83CPU *cpu)
{
    uint16_t addr = __sm83_fetch16(cpu);
    cpu->registers.pc = addr;
    cpu->cycles += 4;
}

/* Return from Subroutine if Condition is met */
static inline void __sm83_ret_cc(struct SM83CPU *cpu, uint8_t bit_flag, enum Condition condition)
{
    uint8_t flag = (cpu->registers.f >> bit_flag) & 1;
    if (checks[condition](cpu) == flag)
    {
        // If Condition is met pop the PC from Stack
        uint8_t low =  sm83_read(cpu, cpu->registers.sp++);
        uint8_t high = sm83_read(cpu, cpu->registers.sp++);

        cpu->registers.pc = (high << 8) | low;

        /* If Condition is met Add % cycles */
        cpu->cycles += 5;
    }
    else
    {
        /* Add 2 cycles */
        cpu->cycles += 2;
    }
}

/* Return from Subroutine */
static inline void __sm83_ret(struct SM83CPU *cpu)
{
    uint8_t low =  sm83_read(cpu, cpu->registers.sp++);
    uint8_t high = sm83_read(cpu, cpu->registers.sp++);
    cpu->registers.pc = (high << 8) | low;
    cpu->cycles += 4;
}

// Push the PC to the stack, Call Subroutine
static inline void __sm83_call_cc(struct SM83CPU *cpu, uint8_t bit_flag, enum Condition condition)
{
    /* Isolate the Condition's flag */
    uint8_t flag = (cpu->registers.f >> bit_flag) & 1;

    /* Check Condtion */
    if (checks[condition](cpu) == flag)
    {
        /* Save PC before entering subroutine */
        sm83_write8(cpu, cpu->registers.pc >> 8, --cpu->registers.sp); /* Push High First */
        sm83_write8(cpu, cpu->registers.pc & 0xFF, --cpu->registers.sp); /* Push Low Second */

        /* Fetch the subroutine address */
        cpu->registers.pc = __sm83_fetch16(cpu);
        cpu->cycles += 6;
    }
    else
    {
        cpu->cycles += 3;
    }
}

/* Call Subroutine */
static inline void __sm83_call(struct SM83CPU *cpu)
{
    sm83_write8(cpu, cpu->registers.pc >> 8, --cpu->registers.sp);
    sm83_write8(cpu, cpu->registers.pc & 0xFF, --cpu->registers.sp);
    cpu->registers.pc = __sm83_fetch16(cpu);
    cpu->cycles += 6;
}

/* Restart with the specified vector same as Call vec */
static inline void __sm83_rst_vec(struct SM83CPU *cpu, uint16_t vec)
{
    sm83_write8(cpu, cpu->registers.pc >> 8, --cpu->registers.sp);
    sm83_write8(cpu, cpu->registers.pc & 0xFF, --cpu->registers.sp);
    cpu->registers.pc = vec;
    cpu->cycles += 4;
}

/* Abort on illegal access, something wrong with the fetch-decode-ececute cycle */
static inline enum SM83Error __sm83_illegal_access(uint8_t opcode)
{
    fprintf(stderr, "ILLEGAL: ILLEGAL 0x%02x access\n", opcode);
    return SM83_ERR_ILLEGAL_ACCESS;
}

/* Rotate left circular a byte left */
static inline void __sm83_rlc(struct SM83CPU *cpu, uint8_t *reg8)
{
    uint8_t result = (*reg8 << 1) | (*reg8 >> 7);

    __sm83_set_z(cpu, result);
    __sm83_clr_n(cpu);
    __sm83_clr_h(cpu);
    if (*reg8 & 0x80)
    {
        __sm83_set_c(cpu);
    }
    else
    {
        __sm83_clr_c(cpu);
    }
    cpu->cycles += 2;
    *reg8 = result;
}

/* Rotate right circular a byte left */
static inline void __sm83_rrc(struct SM83CPU *cpu, uint8_t *reg8)
{
    uint8_t result = (*reg8 >> 1) | (*reg8 << 7);

    __sm83_set_z(cpu, result);
    __sm83_clr_n(cpu);
    __sm83_clr_h(cpu);
    if (*reg8 & 0x01)
    {
        __sm83_set_c(cpu);
    }
    else
    {
        __sm83_clr_c(cpu);
    }
    cpu->cycles += 2;
    *reg8 = result;
}

/* Rotate left with carry bit */
static inline void __sm83_rl(struct SM83CPU *cpu, uint8_t *reg8)
{
    /* Extract carry bit */
    uint8_t carry = __sm83_get_flag_bit(cpu, C_BIT);

    uint8_t result = (*reg8 << 1) | carry;
    __sm83_set_z(cpu, result);
    __sm83_clr_n(cpu);
    __sm83_clr_h(cpu);
    if (*reg8 & 0x80)
    {
        __sm83_set_c(cpu);
    }
    else
    {
        __sm83_clr_c(cpu);
    }
    cpu->cycles += 2;
    *reg8 = result;
}

/* Rotate right with carry bit */
static inline void __sm83_rr(struct SM83CPU *cpu, uint8_t *reg8)
{
    /* Extract carry bit */
    uint8_t carry = __sm83_get_flag_bit(cpu, C_BIT);

    uint8_t result = (*reg8 >> 1) | (carry << 7);
    __sm83_set_z(cpu, result);
    __sm83_clr_n(cpu);
    __sm83_clr_h(cpu);
    if (*reg8 & 0x01)
    {
        __sm83_set_c(cpu);
    }
    else
    {
        __sm83_clr_c(cpu);
    }
    cpu->cycles += 2;
    *reg8 = result;
}

/* Shift left arithmetically  */
static inline void __sm83_sla(struct SM83CPU *cpu, uint8_t *reg8)
{
    uint8_t result = (*reg8 << 1);

    __sm83_set_z(cpu, result);
    __sm83_clr_n(cpu);
    __sm83_clr_h(cpu);
    if (*reg8 & 0x80)
    {
        __sm83_set_c(cpu);
    }
    else
    {
        __sm83_clr_c(cpu);
    }
    cpu->cycles += 2;
    *reg8 = result;
}

/* Shift Right logical */
static inline void __sm83_srl(struct SM83CPU *cpu, uint8_t *reg8)
{
    uint8_t result = (*reg8 >> 1);

    __sm83_set_z(cpu, result);
    __sm83_clr_n(cpu);
    __sm83_clr_h(cpu);
    if (*reg8 & 0x01)
    {
        __sm83_set_c(cpu);
    }
    else
    {
        __sm83_clr_c(cpu);
    }
    cpu->cycles += 2;
    *reg8 = result;
}

/* Shift Right Arithmetically */
static inline void __sm83_sra(struct SM83CPU *cpu, uint8_t *reg8)
{
    uint8_t result = (*reg8 >> 1) | (*reg8 & 0x80);

    __sm83_set_z(cpu, result);
    __sm83_clr_n(cpu);
    __sm83_clr_h(cpu);
    if (*reg8 & 0x01)
    {
        __sm83_set_c(cpu);
    }
    else
    {
        __sm83_clr_c(cpu);
    }
    cpu->cycles += 2;
    *reg8 = result;
}

/* Swap the four lower and upper bits of *reg8 */
static inline void __sm83_swap(struct SM83CPU *cpu, uint8_t *reg8)
{
    uint8_t result = (*reg8 << 4) | (*reg8 >> 4);
    __sm83_set_z(cpu, result);
    __sm83_clr_n(cpu);
    __sm83_clr_h(cpu);
    __sm83_clr_c(cpu);
    *reg8 = result;
    cpu->cycles += 2;
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
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld b, 0x%x ; copy 0x%x into reg b\n", cpu->registers.b, cpu->registers.b);
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
        __sm83_clr_n(cpu);
        __sm83_set_h_with_operation(cpu, HALF_CARRY_INC, 0);

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
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rlca ; rotate accumulator left\n");
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
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld [0x%04x], sp\n", addr);
    } break;

    case OP_ADD_HL_BC:
    {
        /*
          Add joined register BC to the value in HL
          Update the Flags According to the result
        */
        __sm83_add_r16_r16(cpu, &cpu->registers.h, &cpu->registers.l, &cpu->registers.b, &cpu->registers.c);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "add hl, bc\n");
    } break;

    case OP_LD_A_BC:
    {
        /*
          LD A BC
          load the value in memory location BC into A
        */
        __sm83_load_r8_r16(cpu, &cpu->registers.b, &cpu->registers.c, &cpu->registers.a);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld a, [bc]\n");
    } break;

    case OP_DEC_BC:
    {
        /*
          DEC BC
          Decrement joined regs BC by 1
        */
        __sm83_dec_r16(&cpu->registers.b, &cpu->registers.c);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "dec bc\n");
    } break;

    case OP_INC_C:
    {
        /* INC Register C, also flags are updated */
        __sm83_inc_r8(cpu, &cpu->registers.c);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "inc c\n");
    } break;

    case OP_DEC_C:
    {
        /* INC Register C, also flags are updated */
        __sm83_dec_r8(cpu, &cpu->registers.c);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "dec c\n");
    } break;

    case OP_LD_C_N8:
    {
        /*
          LD C, N8
          Copy The fetched byte to register C
        */
        __sm83_load_r8_n8(cpu, &cpu->registers.c);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld c, 0x%x\n", cpu->registers.c);
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
        __sm83_clr_n(cpu);
        __sm83_set_h_with_operation(cpu, HALF_CARRY_INC, 0);

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
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rrca ; rotate accumulator right\n");
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
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "stop 0x%x\n", n8);
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
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld de, 0x%x\n", n16);
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
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld [de], a\n");
    } break;

    case OP_INC_DE:
    {
        /* INC DE, Increment DE joined Regs */
        __sm83_inc_r16(&cpu->registers.d, &cpu->registers.e);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "inc de\n");
    } break;

    case OP_INC_D:
    {
        /* INC D, Increment Register D */
        __sm83_inc_r8(cpu, &cpu->registers.d); /* Updates the Flag */
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "inc d\n");
    } break;

    case OP_DEC_D:
    {
        /* DEC D, Decrements D */
        __sm83_dec_r8(cpu, &cpu->registers.d);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "dec d\n");
    } break;

    case OP_LD_D_N8:
    {
        /*
          LD D, N8
          Copy N8 into Register D
        */
        __sm83_load_r8_n8(cpu, &cpu->registers.d);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld d, 0x%x\n", cpu->registers.d);
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
        __sm83_clr_n(cpu);
        __sm83_set_h_with_operation(cpu, HALF_CARRY_INC, 0);

        /* Set C bit according to old bit 7 */
        cpu->registers.f |= (bit7 << C_BIT);

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rla\n");
    } break;

    case OP_JR_E8:
    {
        /*
          JR E8
          Increment the PC with the Signed Offset Obtained from fetch8
        */
        __sm83_relative_jump(cpu);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "jr 0x%x\n", cpu->registers.pc);
    } break;

    case OP_ADD_HL_DE:
    {
        /*
          ADD HL, DE
          Add Hl and DE, Save Back the bytes of the result to Individual H and L
        */
        __sm83_add_r16_r16(cpu, &cpu->registers.h, &cpu->registers.l, &cpu->registers.d, &cpu->registers.e);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "add hl, de\n");
    } break;

    case OP_LD_A_DE:
    {
        /*
          LD A DE
          Load the value in Memory Location DE into Accumulator
        */
        __sm83_load_r8_r16(cpu, &cpu->registers.d, &cpu->registers.e, &cpu->registers.a);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld a, [de]\n");
    } break;

    case OP_DEC_DE:
    {
        /* DEC DE, Decrement Joined Register DE */
        __sm83_dec_r16(&cpu->registers.d, &cpu->registers.e);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "dec de\n");
    } break;

    case OP_INC_E:
    {
        /* INC E, Increment Register E */
        __sm83_inc_r8(cpu, &cpu->registers.e);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "inc e\n");
    } break;

    case OP_DEC_E:
    {
        /* DEC E, Deccrement Register E */
        __sm83_dec_r8(cpu, &cpu->registers.e);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "dec e\n");
    } break;

    case OP_LD_E_N8:
    {
        /*
          LD E, N8, Copy N8 To Register E
        */
        __sm83_load_r8_n8(cpu, &cpu->registers.e);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld e, n8\n");
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
        uint8_t old_carry = (cpu->registers.f >> C_BIT) & 1;

        /* bit 0 goes to 7 */
        cpu->registers.a  = (a >> 1) | (old_carry << 7);

        /* Clear Z N H */
        __sm83_set_z(cpu, 0XFF);
        __sm83_clr_n(cpu);
        __sm83_set_h_with_operation(cpu, HALF_CARRY_INC, 0);

        /* Set C bit according to old carry */
        cpu->registers.f |= (bit0 << C_BIT);

        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rra ; rotate accumulator right\n");
    } break;

    case OP_JR_NZ_E8:
    {
        /*
          JR NZ, E8
          Jump if Z flag is 0 else dont
        */
        __sm83_relative_jump_cc(cpu, Z_BIT, COND_NZ);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "jr nz, 0x%04x\n", cpu->registers.pc);
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
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld hl, 0x%04x\n", n16);
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
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld [hli], a\n");
    } break;

    case OP_INC_HL:
    {
        /* INC HL, Increment Joined Register HL */
        __sm83_inc_r16(&cpu->registers.h, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "inc hl\n");
    } break;

    case OP_INC_H:
    {
        /* INC H, Increment Register H , Update Flags */
        __sm83_inc_r8(cpu, &cpu->registers.h);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "inc h\n");
    } break;

    case OP_DEC_H:
    {
        /* INC H, Increment Register H */
        __sm83_dec_r8(cpu, &cpu->registers.h);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "dec h\n");
    } break;

    case OP_LD_H_N8:
    {
        /* LD H, N8. Copy fetched Value n8 into H */
        __sm83_load_r8_n8(cpu, &cpu->registers.h);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld h, n8\n");
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
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "daa\n");
    } break;

    case OP_JR_Z_E8:
    {
        /* JR Z, E8. Jump if Z == 1 else dont */
        __sm83_relative_jump_cc(cpu, Z_BIT, COND_Z);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "jr z, 0x%04x\n", cpu->registers.pc);
    } break;

    case OP_ADD_HL_HL:
    {
        /* ADD HL, HL. add the Joined register HL with itself, update the Flags*/
        __sm83_add_r16_r16(cpu, &cpu->registers.h, &cpu->registers.l, &cpu->registers.h, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "add hl, hl\n");
    } break;

    case OP_LD_A_HLI:
    {
        /* LD A, HLI , load the byte pointed by HL into A and increment HL*/
        __sm83_load_operation_accumulator_r16(cpu, FLAG_ADD, &cpu->registers.h, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld a, [hli]\n");
    } break;

    case OP_DEC_HL:
    {
        /* DEC, HL , Decremnt the Joined Register HL */
        __sm83_dec_r16(&cpu->registers.h, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "dec, hl\n");
    } break;

    case OP_INC_L:
    {
        /* INC L. Increment the Register L */
        __sm83_inc_r8(cpu, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "inc, l\n");
    } break;

    case OP_DEC_L:
    {
        /* DEC L. Decrement the Register L */
        __sm83_dec_r8(cpu, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "dec, l\n");
    } break;

    case OP_LD_L_N8:
    {
        /* LD L, N8. Copy n8 into Register L*/
        __sm83_load_r8_n8(cpu, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld l, 0x%02x\n", cpu->registers.l);
    } break;

    case OP_CPL:
    {
        /* CPL => CPL A. Complement Accumulator A = ~A */
        cpu->registers.a = ~cpu->registers.a;
        /* Set N and H */
        cpu->registers.f |= (1u << N_BIT);
        cpu->registers.f |= (1u << H_BIT);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "cpl a\n");
    } break;

    case OP_JR_NC_E8:
    {
        /*
          JR NC, E8
          Jump if C flag is 0 else dont
        */
        /* Isolate C Bit */
        __sm83_relative_jump_cc(cpu, C_BIT, COND_NC);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "jr nc, 0x%04x\n", cpu->registers.pc);
    } break;

    case OP_LD_SP_N16:
    {
        /* LD SP, N16. Copy N16 into Register SP */
        cpu->registers.sp = __sm83_fetch16(cpu);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld sp, 0x%04x\n", cpu->registers.sp);
    } break;

    case OP_LD_HLD_A:
    {
        /* LD HLD, A, Write memory[HL] = A, then decrement HL */
        __sm83_load_operation_r16_accumulator(cpu, FLAG_SUB, &cpu->registers.h, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld [hld], a\n");
    } break;

    case OP_INC_SP:
    {
        /* INC SP. Increment Stack Pointer */
        cpu->registers.sp++;
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "inc sp\n");
    } break;

    case OP_IND_INC_HL:
    {
        /* Increment the byte Pointed to by HL */
        enum SM83Error ret = __sm83_inc_ind_r16(cpu, &cpu->registers.h, &cpu->registers.l);
        if (ret != SM83_OK) return ret;
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "inc [hl]\n");
    } break;

    case OP_IND_DEC_HL:
    {
        /* Decrement the byte Pointed to by HL */
        enum SM83Error ret = __sm83_dec_ind_r16(cpu, &cpu->registers.h, &cpu->registers.l);
        if (ret != SM83_OK) return ret;
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "dec [hl]\n");
    } break;

    case OP_LD_HL_N8:
    {
        /* LD HL, N8. Copy the the next byte into the byte in memory pointed by HL */
        uint8_t n8 = __sm83_fetch8(cpu);
        __sm83_load_r16_n8(cpu, cpu->registers.h, cpu->registers.l, n8);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld [hl], 0x%02x\n", n8);
    } break;

    case OP_SCF:
    {
        /* SCF, Set Carry Flag bit */
        cpu->registers.f |= (1u << C_BIT);
        /* Clear N and H flag bits*/
        cpu->registers.f &= ~(1u << N_BIT);
        cpu->registers.f &= ~(1u << H_BIT);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "scf\n");
    } break;

    case OP_JR_C_E8:
    {
        /* JR C, E8. Jump if C flag bit is 1*/
        __sm83_relative_jump_cc(cpu, C_BIT, COND_C);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "jr c, 0x%02x\n", cpu->registers.pc);
    } break;

    case OP_ADD_HL_SP:
    {
        /* ADD HL, SP. Add the Joined Registers HL to Stack Pointer */
        uint8_t sp_high = (cpu->registers.sp >> 8);
        uint8_t sp_low = (cpu->registers.sp & 0xFF);
        __sm83_add_r16_r16(cpu, &cpu->registers.h, &cpu->registers.l, &sp_high, &sp_low);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "add hl, sp\n");
    } break;

    case OP_LD_A_HLD:
    {
        /* LD A, HLD, load the byte in memory address HL and then decement HL */
        __sm83_load_operation_accumulator_r16(cpu, FLAG_SUB, &cpu->registers.h, &cpu->registers.l);
        /* Emit Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld a, [hld]\n");
    } break;

    case OP_DEC_SP:
    {
        /* DEC SP. Decrement SP*/
        cpu->registers.sp--;
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "dec sp\n");
    } break;

    case OP_INC_A:
    {
        /* INC A, increment accumulator */
        __sm83_inc_r8(cpu, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "inc a\n");
    } break;

    case OP_DEC_A:
    {
        /* DEC A, decrement accumulator */
        __sm83_dec_r8(cpu, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "dec a\n");
    } break;

    case OP_LD_A_N8:
    {
        /* LD A, N8. Copy the fetched byte n8 to accumulator*/
        __sm83_load_r8_n8(cpu, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld a, 0x%02x\n", cpu->registers.a);
    } break;

    case OP_CCF:
    {
        /* CCF. Flip the Carry Flag*/
        cpu->registers.f ^= (1u << C_BIT);
        /* Clear N and H */
        cpu->registers.f &= ~(1u << N_BIT);
        cpu->registers.f &= ~(1u << H_BIT);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ccf\n");
    } break;

    case OP_LD_B_B:
    {
        /* LD B, B */
        __sm83_load_r8_r8(&cpu->registers.b, &cpu->registers.b);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld b, b\n");
    } break;

    case OP_LD_B_C:
    {
        /* LD B, C */
        __sm83_load_r8_r8(&cpu->registers.b, &cpu->registers.c);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld b, c\n");
    } break;

    case OP_LD_B_D:
    {
        /* LD B, D */
        __sm83_load_r8_r8(&cpu->registers.b, &cpu->registers.d);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld b, d\n");
    } break;

    case OP_LD_B_E:
    {
        /* LD B, E */
        __sm83_load_r8_r8(&cpu->registers.b, &cpu->registers.e);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld b, e\n");
    } break;

    case OP_LD_B_H:
    {
        /* LD B, H */
        __sm83_load_r8_r8(&cpu->registers.b, &cpu->registers.h);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld b, h\n");
    } break;

    case OP_LD_B_L:
    {
        /* LD B, L */
        __sm83_load_r8_r8(&cpu->registers.b, &cpu->registers.l);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld b, l\n");
    } break;

    case OP_LD_B_HL:
    {
        /* LD B, HL */
        __sm83_load_r8_r16(cpu, &cpu->registers.h, &cpu->registers.l, &cpu->registers.b);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld b, [hl]\n");
    } break;

    case OP_LD_B_A:
    {
        /* LD B, A */
        __sm83_load_r8_r8(&cpu->registers.b, &cpu->registers.a);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld b, a\n");
    } break;

    case OP_LD_C_B:
    {
        /* LD C, B */
        __sm83_load_r8_r8(&cpu->registers.c, &cpu->registers.b);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld c, b\n");
    } break;

    case OP_LD_C_C:
    {
        /* LD C, C */
        __sm83_load_r8_r8(&cpu->registers.c, &cpu->registers.c);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld c, c\n");
    } break;

    case OP_LD_C_D:
    {
        /* LD C, D */
        __sm83_load_r8_r8(&cpu->registers.c, &cpu->registers.d);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld c, d\n");
    } break;

    case OP_LD_C_E:
    {
        /* LD C, E */
        __sm83_load_r8_r8(&cpu->registers.c, &cpu->registers.e);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld c, e\n");
    } break;

    case OP_LD_C_H:
    {
        /* LD C, H */
        __sm83_load_r8_r8(&cpu->registers.c, &cpu->registers.h);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld c, h\n");
    } break;

    case OP_LD_C_L:
    {
        /* LD C, L */
        __sm83_load_r8_r8(&cpu->registers.c, &cpu->registers.l);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld c, l\n");
    } break;

    case OP_LD_C_HL:
    {
        /* LD C, HL */
        __sm83_load_r8_r16(cpu, &cpu->registers.h, &cpu->registers.l, &cpu->registers.c);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld c, [hl]\n");
    } break;

    case OP_LD_C_A:
    {
        /* LD C, A */
        __sm83_load_r8_r8(&cpu->registers.c, &cpu->registers.a);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld c, a\n");
    } break;

    case OP_LD_D_B:
    {
        /* LD D, B */
        __sm83_load_r8_r8(&cpu->registers.d, &cpu->registers.b);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld d, b\n");
    } break;

    case OP_LD_D_C:
    {
        /* LD D, C */
        __sm83_load_r8_r8(&cpu->registers.d, &cpu->registers.c);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld d, c\n");
    } break;

    case OP_LD_D_D:
    {
        /* LD D, D */
        __sm83_load_r8_r8(&cpu->registers.d, &cpu->registers.d);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld d, d\n");
    } break;

    case OP_LD_D_E:
    {
        /* LD D, E */
        __sm83_load_r8_r8(&cpu->registers.d, &cpu->registers.e);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld d, e\n");
    } break;

    case OP_LD_D_H:
    {
        /* LD D, H */
        __sm83_load_r8_r8(&cpu->registers.d, &cpu->registers.h);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld d, h\n");
    } break;

    case OP_LD_D_L:
    {
        /* LD D, L */
        __sm83_load_r8_r8(&cpu->registers.d, &cpu->registers.l);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld d, l\n");
    } break;

    case OP_LD_D_HL:
    {
        /* LD D, HL */
        __sm83_load_r8_r16(cpu, &cpu->registers.h, &cpu->registers.l, &cpu->registers.d);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld d, [hl]\n");
    } break;

    case OP_LD_D_A:
    {
        /* LD D, A */
        __sm83_load_r8_r8(&cpu->registers.d, &cpu->registers.a);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld d, a\n");
    } break;

    case OP_LD_E_B:
    {
        /* LD E, B */
        __sm83_load_r8_r8(&cpu->registers.e, &cpu->registers.b);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld e, b\n");
    } break;

    case OP_LD_E_C:
    {
        /* LD E, C */
        __sm83_load_r8_r8(&cpu->registers.e, &cpu->registers.c);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld e, c\n");
    } break;

    case OP_LD_E_D:
    {
        /* LD E, D */
        __sm83_load_r8_r8(&cpu->registers.e, &cpu->registers.d);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld e, d\n");
    } break;

    case OP_LD_E_E:
    {
        /* LD E, E */
        __sm83_load_r8_r8(&cpu->registers.e, &cpu->registers.e);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld e, e\n");
    } break;

    case OP_LD_E_H:
    {
        /* LD E, H */
        __sm83_load_r8_r8(&cpu->registers.e, &cpu->registers.h);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld e, h\n");
    } break;

    case OP_LD_E_L:
    {
        /* LD E, L */
        __sm83_load_r8_r8(&cpu->registers.e, &cpu->registers.l);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld e, l\n");
    } break;

    case OP_LD_E_HL:
    {
        /* LD E, HL */
        __sm83_load_r8_r16(cpu, &cpu->registers.h, &cpu->registers.l, &cpu->registers.e);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld e, [hl]\n");
    } break;

    case OP_LD_E_A:
    {
        /* LD E, A */
        __sm83_load_r8_r8(&cpu->registers.e, &cpu->registers.a);
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld e, a\n");
    } break;

    case OP_LD_H_B:
    {
        /* LD H, B */
        __sm83_load_r8_r8(&cpu->registers.h, &cpu->registers.b);
        /* emit disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld h, b\n");
    } break;

    case OP_LD_H_C:
    {
        /* LD H, C */
        __sm83_load_r8_r8(&cpu->registers.h, &cpu->registers.c);
        /* emit disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld h, c\n");
    } break;

    case OP_LD_H_D:
    {
        /* LD H, D */
        __sm83_load_r8_r8(&cpu->registers.h, &cpu->registers.d);
        /* emit disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld h, d\n");
    } break;

    case OP_LD_H_E:
    {
        /* LD H, E */
        __sm83_load_r8_r8(&cpu->registers.h, &cpu->registers.e);
        /* emit disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld h, e\n");
    } break;

    case OP_LD_H_H:
    {
        /* LD H, H */
        __sm83_load_r8_r8(&cpu->registers.h, &cpu->registers.h);
        /* emit disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld h, h\n");
    } break;

    case OP_LD_H_L:
    {
        /* LD H, L */
        __sm83_load_r8_r8(&cpu->registers.h, &cpu->registers.l);
        /* emit disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld h, l\n");
    } break;

    case OP_LD_H_HL:
    {
        /* LD H, HL */
        __sm83_load_r8_r16(cpu, &cpu->registers.h, &cpu->registers.l, &cpu->registers.h);
        /* emit disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld h, [hl]\n");
    } break;

    case OP_LD_H_A:
    {
        /* LD H, A */
        __sm83_load_r8_r8(&cpu->registers.h, &cpu->registers.a);
        /* emit disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld h, a\n");
    } break;

    case OP_LD_L_B:
    {
        /* LD L, B */
        __sm83_load_r8_r8(&cpu->registers.l, &cpu->registers.b);
        /* emit disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld l, b\n");
    } break;

    case OP_LD_L_C:
    {
        /* LD L, C */
        __sm83_load_r8_r8(&cpu->registers.l, &cpu->registers.c);
        /* emit disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld l, c\n");
    } break;

    case OP_LD_L_D:
    {
        /* LD L, D */
        __sm83_load_r8_r8(&cpu->registers.l, &cpu->registers.d);
        /* emit disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld l, d\n");
    } break;

    case OP_LD_L_E:
    {
        /* LD L, E */
        __sm83_load_r8_r8(&cpu->registers.l, &cpu->registers.e);
        /* emit disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld l, e\n");
    } break;

    case OP_LD_L_H:
    {
        /* LD L, H */
        __sm83_load_r8_r8(&cpu->registers.l, &cpu->registers.h);
        /* emit disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld l, h\n");
    } break;

    case OP_LD_L_L:
    {
        /* LD L, L */
        __sm83_load_r8_r8(&cpu->registers.l, &cpu->registers.l);
        /* emit disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld l, l\n");
    } break;

    case OP_LD_L_HL:
    {
        /* LD L, HL */
        __sm83_load_r8_r16(cpu, &cpu->registers.h, &cpu->registers.l, &cpu->registers.l);
        /* emit disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld l, [hl]\n");
    } break;

    case OP_LD_L_A:
    {
        /* LD L, A */
        __sm83_load_r8_r8(&cpu->registers.l, &cpu->registers.a);
        /* emit disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld l, a\n");
    } break;

    case OP_LD_HL_B:
    {
        /* LD HL, B */
        enum SM83Error ret = __sm83_load_r16_n8(cpu, cpu->registers.h, cpu->registers.l, cpu->registers.b);
        if (ret != SM83_OK) return SM83_ERR_INVALID_OPCODE;
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld [hl], b\n");
    } break;

    case OP_LD_HL_C:
    {
        /* LD HL, C */
        enum SM83Error ret = __sm83_load_r16_n8(cpu, cpu->registers.h, cpu->registers.l, cpu->registers.c);
        if (ret != SM83_OK) return SM83_ERR_INVALID_OPCODE;
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld [hl], c\n");
    } break;

    case OP_LD_HL_D:
    {
        /* LD HL, D */
        enum SM83Error ret = __sm83_load_r16_n8(cpu, cpu->registers.h, cpu->registers.l, cpu->registers.d);
        if (ret != SM83_OK) return SM83_ERR_INVALID_OPCODE;
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld [hl], d\n");
    } break;

    case OP_LD_HL_E:
    {
        /* LD HL, E */
        enum SM83Error ret = __sm83_load_r16_n8(cpu, cpu->registers.h, cpu->registers.l, cpu->registers.e);
        if (ret != SM83_OK) return SM83_ERR_INVALID_OPCODE;
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld [hl], e\n");
    } break;

    case OP_LD_HL_H:
    {
        /* LD HL, H */
        enum SM83Error ret = __sm83_load_r16_n8(cpu, cpu->registers.h, cpu->registers.l, cpu->registers.h);
        if (ret != SM83_OK) return SM83_ERR_INVALID_OPCODE;
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld [hl], h\n");
    } break;

    case OP_LD_HL_L:
    {
        /* LD HL, L */
        enum SM83Error ret = __sm83_load_r16_n8(cpu, cpu->registers.h, cpu->registers.l, cpu->registers.l);
        if (ret != SM83_OK) return SM83_ERR_INVALID_OPCODE;
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld [hl], l\n");
    } break;

    case OP_HALT:
    {
        /* Halt the Execution Process */
        fprintf(stderr, "TODO: HALT Not handled Yet!\n");
        abort();
    } break;

    case OP_LD_HL_A:
    {
        /* LD HL, A */
        enum SM83Error ret = __sm83_load_r16_n8(cpu, cpu->registers.h, cpu->registers.l, cpu->registers.a);
        if (ret != SM83_OK) return SM83_ERR_INVALID_OPCODE;
        /* EMIT Disassembly */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld [hl], a\n");
    } break;

    case OP_LD_A_B:
    {
        /* LD A, B */
        __sm83_load_r8_r8(&cpu->registers.a, &cpu->registers.b);
        /* Emit Disasm */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld a, b\n");
    } break;

    case OP_LD_A_C:
    {
        /* LD A, C */
        __sm83_load_r8_r8(&cpu->registers.a, &cpu->registers.c);
        /* Emit Disasm */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld a, c\n");
    } break;

    case OP_LD_A_D:
    {
        /* LD A, D */
        __sm83_load_r8_r8(&cpu->registers.a, &cpu->registers.d);
        /* Emit Disasm */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld a, d\n");
    } break;

    case OP_LD_A_E:
    {
        /* LD A, E */
        __sm83_load_r8_r8(&cpu->registers.a, &cpu->registers.e);
        /* Emit Disasm */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld a, e\n");
    } break;

    case OP_LD_A_H:
    {
        /* LD A, H */
        __sm83_load_r8_r8(&cpu->registers.a, &cpu->registers.h);
        /* Emit Disasm */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld a, h\n");
    } break;

    case OP_LD_A_L:
    {
        /* LD A, L */
        __sm83_load_r8_r8(&cpu->registers.a, &cpu->registers.l);
        /* Emit Disasm */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld a, l\n");
    } break;

    case OP_LD_A_HL:
    {
        /* LD A, HL */
        __sm83_load_r8_r16(cpu, &cpu->registers.h, &cpu->registers.l, &cpu->registers.a);
        /* Emit Disasm */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld a, [hl]\n");
    } break;

    case OP_LD_A_A:
    {
        /* LD A, A */
        __sm83_load_r8_r8(&cpu->registers.a, &cpu->registers.a);
        /* Emit Disasm */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld a, a\n");
    } break;

    case OP_ADD_A_B:
    {
        /* ADD A, B */
        __sm83_add_r8_r8(cpu, &cpu->registers.a, &cpu->registers.b);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "add a, b\n");
    } break;

    case OP_ADD_A_C:
    {
        /* ADD A, C */
        __sm83_add_r8_r8(cpu, &cpu->registers.a, &cpu->registers.c);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "add a, c\n");
    } break;

    case OP_ADD_A_D:
    {
        /* ADD A, D */
        __sm83_add_r8_r8(cpu, &cpu->registers.a, &cpu->registers.d);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "add a, d\n");
    } break;

    case OP_ADD_A_E:
    {
        /* ADD A, E */
        __sm83_add_r8_r8(cpu, &cpu->registers.a, &cpu->registers.e);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "add a, e\n");
    } break;

    case OP_ADD_A_H:
    {
        /* ADD A, H */
        __sm83_add_r8_r8(cpu, &cpu->registers.a, &cpu->registers.h);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "add a, h\n");
    } break;

    case OP_ADD_A_L:
    {
        /* ADD A, L */
        __sm83_add_r8_r8(cpu, &cpu->registers.a, &cpu->registers.l);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "add a, l\n");
    } break;

    case OP_ADD_A_HL:
    {
        /* ADD A, HL */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        uint8_t data = sm83_read(cpu, addr);
        __sm83_add_r8_r8(cpu, &cpu->registers.a, &data);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "add a, [hl]\n");
    } break;

    case OP_ADD_A_A:
    {
        /* ADD A, A */
        __sm83_add_r8_r8(cpu, &cpu->registers.a, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "add a, a\n");
    } break;


    case OP_ADC_A_B:
    {
        /* ADC, A, B */
        __sm83_adc_r8_r8(cpu, &cpu->registers.a, &cpu->registers.b);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "adc, a, b\n");
    } break;

    case OP_ADC_A_C:
    {
        /* ADC, A, C */
        __sm83_adc_r8_r8(cpu, &cpu->registers.a, &cpu->registers.c);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "adc, a, c\n");
    } break;

    case OP_ADC_A_D:
    {
        /* ADC, A, D */
        __sm83_adc_r8_r8(cpu, &cpu->registers.a, &cpu->registers.d);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "adc, a, d\n");
    } break;

    case OP_ADC_A_E:
    {
        /* ADC, A, E */
        __sm83_adc_r8_r8(cpu, &cpu->registers.a, &cpu->registers.e);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "adc, a, e\n");
    } break;

    case OP_ADC_A_H:
    {
        /* ADC, A, H */
        __sm83_adc_r8_r8(cpu, &cpu->registers.a, &cpu->registers.h);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "adc, a, h\n");
    } break;

    case OP_ADC_A_L:
    {
        /* ADC, A, L */
        __sm83_adc_r8_r8(cpu, &cpu->registers.a, &cpu->registers.l);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "adc, a, l\n");
    } break;

    case OP_ADC_A_HL:
    {
        /* ADC, A_, L */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        uint8_t data = sm83_read(cpu, addr);
        __sm83_adc_r8_r8(cpu, &cpu->registers.a, &data);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "adc, a_, l\n");
    } break;

    case OP_ADC_A_A:
    {
        /* ADC, A, A */
        __sm83_adc_r8_r8(cpu, &cpu->registers.a, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "adc, a, a\n");
    } break;

    case OP_SUB_A_B:
    {
        /* SUB A, B */
        __sm83_sub_r8_r8(cpu, &cpu->registers.a, &cpu->registers.b);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sub a, b\n");
    } break;

    case OP_SUB_A_C:
    {
        /* SUB A, C */
        __sm83_sub_r8_r8(cpu, &cpu->registers.a, &cpu->registers.c);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sub a, c\n");
    } break;

    case OP_SUB_A_D:
    {
        /* SUB A, D */
        __sm83_sub_r8_r8(cpu, &cpu->registers.a, &cpu->registers.d);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sub a, d\n");
    } break;

    case OP_SUB_A_E:
    {
        /* SUB A, E */
        __sm83_sub_r8_r8(cpu, &cpu->registers.a, &cpu->registers.e);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sub a, e\n");
    } break;

    case OP_SUB_A_H:
    {
        /* SUB A, H */
        __sm83_sub_r8_r8(cpu, &cpu->registers.a, &cpu->registers.h);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sub a, h\n");
    } break;

    case OP_SUB_A_L:
    {
        /* SUB A, L */
        __sm83_sub_r8_r8(cpu, &cpu->registers.a, &cpu->registers.l);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sub a, l\n");
    } break;

    case OP_SUB_A_HL:
    {
        /* SUB A_, L */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        uint8_t data = sm83_read(cpu, addr);
        __sm83_sub_r8_r8(cpu, &cpu->registers.a, &data);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sub a, [hl]\n");
    } break;

    case OP_SUB_A_A:
    {
        /* SUB A, A */
        __sm83_sub_r8_r8(cpu, &cpu->registers.a, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sub a, a\n");
    } break;


    case OP_SBC_A_B: {
        /* SBC A, B */
        __sm83_sbc_r8_r8(cpu, &cpu->registers.a, &cpu->registers.b);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sbc a, b\n");
    } break;
    case OP_SBC_A_C: {
        /* SBC A, C */
        __sm83_sbc_r8_r8(cpu, &cpu->registers.a, &cpu->registers.c);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sbc a, c\n");
    } break;
    case OP_SBC_A_D: {
        /* SBC A, D */
        __sm83_sbc_r8_r8(cpu, &cpu->registers.a, &cpu->registers.d);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sbc a, d\n");
    } break;
    case OP_SBC_A_E: {
        /* SBC A, E */
        __sm83_sbc_r8_r8(cpu, &cpu->registers.a, &cpu->registers.e);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sbc a, e\n");
    } break;
    case OP_SBC_A_H: {
        /* SBC A, H */
        __sm83_sbc_r8_r8(cpu, &cpu->registers.a, &cpu->registers.h);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sbc a, h\n");
    } break;
    case OP_SBC_A_L: {
        /* SBC A, L */
        __sm83_sbc_r8_r8(cpu, &cpu->registers.a, &cpu->registers.l);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sbc a, l\n");
    } break;
    case OP_SBC_A_HL: {
        /* SBC A_, L */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        uint8_t data = sm83_read(cpu, addr);
        __sm83_sbc_r8_r8(cpu, &cpu->registers.a, &data);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sbc a, [hl]\n");
    } break;
    case OP_SBC_A_A: {
        /* SBC A, A */
        __sm83_sbc_r8_r8(cpu, &cpu->registers.a, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sbc a, a\n");
    } break;

    case OP_AND_A_B: {
        /* AND A, B */
        __sm83_and_r8_r8(cpu, &cpu->registers.a, &cpu->registers.b);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "and a, b\n");
    } break;
    case OP_AND_A_C: {
        /* AND A, C */
        __sm83_and_r8_r8(cpu, &cpu->registers.a, &cpu->registers.c);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "and a, c\n");
    } break;
    case OP_AND_A_D: {
        /* AND A, D */
        __sm83_and_r8_r8(cpu, &cpu->registers.a, &cpu->registers.d);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "and a, d\n");
    } break;
    case OP_AND_A_E: {
        /* AND A, E */
        __sm83_and_r8_r8(cpu, &cpu->registers.a, &cpu->registers.e);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "and a, e\n");
    } break;
    case OP_AND_A_H: {
        /* AND A, H */
        __sm83_and_r8_r8(cpu, &cpu->registers.a, &cpu->registers.h);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "and a, h\n");
    } break;
    case OP_AND_A_L: {
        /* AND A, L */
        __sm83_and_r8_r8(cpu, &cpu->registers.a, &cpu->registers.l);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "and a, l\n");
    } break;
    case OP_AND_A_HL: {
        /* AND A, HL */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        uint8_t data = sm83_read(cpu, addr);
        __sm83_and_r8_r8(cpu, &cpu->registers.a, &data);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "and a, [hl]\n");
    } break;
    case OP_AND_A_A: {
        /* AND A, A */
        __sm83_and_r8_r8(cpu, &cpu->registers.a, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "and a, a\n");
    } break;

    case OP_XOR_A_B:
    {
        /* XOR A, B */
        __sm83_xor_r8_r8(cpu, &cpu->registers.a, &cpu->registers.b);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "xor a, b\n");
    } break;

    case OP_XOR_A_C:
    {
        /* XOR A, C */
        __sm83_xor_r8_r8(cpu, &cpu->registers.a, &cpu->registers.c);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "xor a, c\n");
    } break;

    case OP_XOR_A_D:
    {
        /* XOR A, D */
        __sm83_xor_r8_r8(cpu, &cpu->registers.a, &cpu->registers.d);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "xor a, d\n");
    } break;

    case OP_XOR_A_E:
    {
        /* XOR A, E */
        __sm83_xor_r8_r8(cpu, &cpu->registers.a, &cpu->registers.e);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "xor a, e\n");
    } break;

    case OP_XOR_A_H:
    {
        /* XOR A, H */
        __sm83_xor_r8_r8(cpu, &cpu->registers.a, &cpu->registers.h);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "xor a, h\n");
    } break;

    case OP_XOR_A_L:
    {
        /* XOR A, L */
        __sm83_xor_r8_r8(cpu, &cpu->registers.a, &cpu->registers.l);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "xor a, l\n");
    } break;

    case OP_XOR_A_HL:
    {
        /* XOR A, HL */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        uint8_t data = sm83_read(cpu, addr);
        __sm83_xor_r8_r8(cpu, &cpu->registers.a, &data);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "xor a, [hl]\n");
    } break;

    case OP_XOR_A_A:
    {
        /* XOR A, A */
        __sm83_xor_r8_r8(cpu, &cpu->registers.a, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "xor a, a\n");
    } break;

    case OP_OR_A_B:
    {
        /* OR A, B */
        __sm83_or_r8_r8(cpu, &cpu->registers.a, &cpu->registers.b);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "or a, b\n");
    } break;

    case OP_OR_A_C:
    {
        /* OR A, C */
        __sm83_or_r8_r8(cpu, &cpu->registers.a, &cpu->registers.c);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "or a, c\n");
    } break;

    case OP_OR_A_D:
    {
        /* OR A, D */
        __sm83_or_r8_r8(cpu, &cpu->registers.a, &cpu->registers.d);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "or a, d\n");
    } break;

    case OP_OR_A_E:
    {
        /* OR A, E */
        __sm83_or_r8_r8(cpu, &cpu->registers.a, &cpu->registers.e);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "or a, e\n");
    } break;

    case OP_OR_A_H:
    {
        /* OR A, H */
        __sm83_or_r8_r8(cpu, &cpu->registers.a, &cpu->registers.h);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "or a, h\n");
    } break;

    case OP_OR_A_L:
    {
        /* OR A, L */
        __sm83_or_r8_r8(cpu, &cpu->registers.a, &cpu->registers.l);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "or a, l\n");
    } break;

    case OP_OR_A_HL:
    {
        /* OR A, HL */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        uint8_t data = sm83_read(cpu, addr);
        __sm83_or_r8_r8(cpu, &cpu->registers.a, &data);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "or a, [hl]\n");
    } break;

    case OP_OR_A_A:
    {
        /* OR A, A */
        __sm83_or_r8_r8(cpu, &cpu->registers.a, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "or a, a\n");
    } break;

    case OP_CP_A_B:
    {
        /* CP A, B */
        __sm83_cp_r8_r8(cpu, &cpu->registers.a, &cpu->registers.b);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "cp a, b\n");
    } break;

    case OP_CP_A_C:
    {
        /* CP A, C */
        __sm83_cp_r8_r8(cpu, &cpu->registers.a, &cpu->registers.c);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "cp a, c\n");
    } break;

    case OP_CP_A_D:
    {
        /* CP A, D */
        __sm83_cp_r8_r8(cpu, &cpu->registers.a, &cpu->registers.d);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "cp a, d\n");
    } break;

    case OP_CP_A_E:
    {
        /* CP A, E */
        __sm83_cp_r8_r8(cpu, &cpu->registers.a, &cpu->registers.e);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "cp a, e\n");
    } break;

    case OP_CP_A_H:
    {
        /* CP A, H */
        __sm83_cp_r8_r8(cpu, &cpu->registers.a, &cpu->registers.h);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "cp a, h\n");
    } break;

    case OP_CP_A_L:
    {
        /* CP A, L */
        __sm83_cp_r8_r8(cpu, &cpu->registers.a, &cpu->registers.l);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "cp a, l\n");
    } break;

    case OP_CP_A_HL:
    {
        /* CP A, HL */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        uint8_t data = sm83_read(cpu, addr);
        __sm83_cp_r8_r8(cpu, &cpu->registers.a, &data);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "cp a, [hl]\n");
    } break;

    case OP_CP_A_A:
    {
        /* CP A, A */
        __sm83_cp_r8_r8(cpu, &cpu->registers.a, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "cp a, a\n");
    } break;

    case OP_RET_NZ:
    {
        /* RET NZ. Return from Subroutine if Z == 0 */
        __sm83_ret_cc(cpu, Z_BIT, COND_NZ);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ret nz\n");
    } break;

    case OP_POP_BC:
    {
        /* POP BC. Pop the values of regs B and C from the stack */
        cpu->registers.c = sm83_read(cpu, cpu->registers.sp++);
        cpu->registers.b = sm83_read(cpu, cpu->registers.sp++);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "pop bc\n");
    } break;

    case OP_JP_NZ_A16:
    {
        /* JP NZ A16, Jump if not Z */
        __sm83_jump_cc(cpu, Z_BIT, COND_NZ);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "jp nz\n");
    } break;

    case OP_JP_A16:
    {
        /* JP A16, Jump to the address in the next two bytes */
        __sm83_jump(cpu);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "jp 0x%04x\n", cpu->registers.pc);
    } break;

    case OP_CALL_NZ_A16:
    {
        /* CALL NZ A16, Call Subroutine at a16 if not z*/
        __sm83_call_cc(cpu, Z_BIT, COND_NZ);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "call nz\n");
    } break;

    case OP_PUSH_BC:
    {
        /* PUSH BC, push B and C to Stack */
        sm83_write8(cpu, cpu->registers.b, --cpu->registers.sp);
        sm83_write8(cpu, cpu->registers.c, --cpu->registers.sp);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "push bc\n");
    } break;

    case OP_ADD_A_N8:
    {
        /* ADD A, N8 add a to the next byte and save back to a*/
        uint8_t n8 = __sm83_fetch8(cpu);
        __sm83_add_r8_r8(cpu, &cpu->registers.a, &n8);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "add a, 0x%02x\n", n8);
    } break;

    case OP_RST_00:
    {
        /* RST 00, Call the subroutine at address 0x0000*/
        __sm83_rst_vec(cpu, 0x0000);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rst 0x%04x\n", 0x0000);
    } break;

    case OP_RET_Z:
    {
        /* RET Z. Return from subroutine if Z bit */
        __sm83_ret_cc(cpu, Z_BIT, COND_Z);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ret z\n");
    } break;

    case OP_RET:
    {
        /* Ret from Subroutine */
        __sm83_ret(cpu);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ret 0x%04x\n", cpu->registers.pc);
    } break;

    case OP_JP_Z_A16:
    {
        /* JP Z A16, Jump to fetched a16 if Z */
        __sm83_jump_cc(cpu, Z_BIT, COND_Z);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "jp z\n");
    } break;

    case OP_PREFIX:
    {
        sm83_decode_cb_prefixed(cpu);
    } break;

    case OP_CALL_Z_A16:
    {
        /* Call Z a16 Call Subroutine a16 if Z */
        __sm83_call_cc(cpu, Z_BIT, COND_Z);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "call z\n");
    } break;

    case OP_CALL_A16:
    {
        /* Call a16 Call Subroutine a16 */
        __sm83_call(cpu);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "call 0x%04x\n", cpu->registers.pc);
    } break;

    case OP_ADC_A_N8:
    {
        /* ADC A N8, Add a and fetched n8 with carry */
        uint8_t n8 = __sm83_fetch8(cpu);
        __sm83_adc_r8_r8(cpu, &cpu->registers.a, &n8);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "adc a, 0x%02x\n", n8);
    } break;

    case OP_RST_08:
    {
        /* RST 08 Call subroutine at address 08 */
        __sm83_rst_vec(cpu, 0x0008);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rst 0x%04x\n", 0x0008);
    } break;

    case OP_RET_NC:
    {
        /* RET NC. Return from Subroutine if not C */
        __sm83_ret_cc(cpu, C_BIT, COND_NC);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ret nc\n");
    } break;

    case OP_POP_DE:
    {
        /* POP DE, read d and e from the stack */
        cpu->registers.e = sm83_read(cpu, cpu->registers.sp++); /* Pop low first */
        cpu->registers.d = sm83_read(cpu, cpu->registers.sp++); /* Pop high second */
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "pop de\n");
    } break;

    case OP_JP_NC_A16:
    {
        /* Jump if not c flag */
        __sm83_jump_cc(cpu, C_BIT, COND_NC);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "jp nc\n");
    } break;

    case OP_ILLEGAL_D3: return __sm83_illegal_access(0xD3);

    case OP_CALL_NC_A16:
    {
        /* CALL Subroutine if not c flag */
        __sm83_call_cc(cpu, C_BIT, COND_NC);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "call nc\n");
    } break;

    case OP_PUSH_DE:
    {
        /* PUSH DE */
        sm83_write8(cpu, cpu->registers.d, --cpu->registers.sp); // Push high
        sm83_write8(cpu, cpu->registers.e, --cpu->registers.sp); // Push low
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "push de\n");
    } break;

    case OP_SUB_A_N8:
    {
        /* Subtract a from fetched n8 then save back to a */
        uint8_t n8 = __sm83_fetch8(cpu);
        __sm83_sub_r8_r8(cpu, &cpu->registers.a, &n8);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sub a, 0x%02x\n", n8);
    } break;

    case OP_RST_10:
    {
        /* RST 10 */
        __sm83_rst_vec(cpu, 0x0010);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rst 0x%04x\n", 0x0010);
    } break;

    case OP_RET_C:
    {
        /* Return if C */
        __sm83_ret_cc(cpu, C_BIT, COND_C);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ret c\n");
    } break;

    case OP_RETI:
    {
        /* Return from subroutine and set interrupt flag */
        cpu->ime = 1;
        __sm83_ret(cpu);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "reti\n");
    } break;

    case OP_JP_C_A16:
    {
        /* Jump if c flag */
        __sm83_jump_cc(cpu, C_BIT, COND_C);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "jp c\n");
    } break;

    case OP_ILEGAL_DB: return __sm83_illegal_access(0xDB);

    case OP_CALL_C_A16: {
        /* Call if c flag */
        __sm83_call_cc(cpu, C_BIT, COND_C);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "call c\n");
    } break;
    
    case OP_ILEGALL_DD: return __sm83_illegal_access(0xDD);

    case OP_SBC_A_N8:
    {
        /* Subtract with carry a from n8 */
        uint8_t n8 = __sm83_fetch8(cpu);
        __sm83_sbc_r8_r8(cpu, &cpu->registers.a, &n8);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sbc a, 0x%02x\n", n8);
    } break;

    case OP_RST_18:
    {
        /* RST 18 */
        __sm83_rst_vec(cpu, 0x0018);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rst 0x%04x\n", 0x0018);
    } break;

    case OP_LDH_A8_A:
    {
        /*LDH [A8] A Load FF00 + A8 into a */
        uint8_t a8 = __sm83_fetch8(cpu);
        uint8_t high = 0xFF;
        uint16_t addr = __sm83_join_eight_bits(high, a8);
        sm83_write8(cpu, cpu->registers.a, addr);
       EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ldh [0x%04x], a\n", addr);
    } break;

    case OP_POP_HL:
    {
        /* POP HL, pop h and l from stack */
        cpu->registers.l = sm83_read(cpu, cpu->registers.sp++); // pop low
        cpu->registers.h = sm83_read(cpu, cpu->registers.sp++); // pop high
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "pop hl\n");
    } break;

    case OP_LDH_C_A: {
        /*LDH [C] A Load FF00 + C into a */
        uint8_t C = cpu->registers.c;
        uint8_t high = 0xFF;
        uint16_t addr = __sm83_join_eight_bits(high, C);
        sm83_write8(cpu, cpu->registers.a, addr);
       EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ldh [0x%04x], a\n", addr);
    } break;

    case OP_ILLEGAL_E3: return __sm83_illegal_access(0xE3);
    case OP_ILLEGAL_E4: return __sm83_illegal_access(0xE4);

    case OP_PUSH_HL:
    {
        /* PUSH HL onto the Stack */
        sm83_write8(cpu, cpu->registers.h, --cpu->registers.sp); // push high
        sm83_write8(cpu, cpu->registers.l, --cpu->registers.sp); // push low
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "push hl\n");
    } break;

    case OP_AND_A_N8:
    {
        /* and a and fetched n8 */
        uint8_t n8 = __sm83_fetch8(cpu);
        __sm83_and_r8_r8(cpu, &cpu->registers.a, &n8);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "and a, 0x%02x\n", n8);
    } break;

    case OP_RST_20:
    {
        /* RST 20 */
        __sm83_rst_vec(cpu, 0x0020);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rst 0x%04x\n", 0x0020);
    } break;

    case OP_ADD_SP_E8:
    {
        int8_t e8 = (int8_t)__sm83_fetch8(cpu);
        uint32_t sp = (uint32_t)cpu->registers.sp;
        uint32_t result = sp + (int16_t) e8;
        /* Update Flags */
        __sm83_clr_z(cpu); /* Clear Z*/
        __sm83_clr_n(cpu); /* Clear N*/
        __sm83_set_h_for_add8(cpu, sp & 0xFF, e8);
        __sm83_set_c_for_add8(cpu, (uint16_t)((sp & 0xFF) + e8));

        cpu->registers.sp = result;
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "add sp, 0x%02x\n", e8);
    } break;

    case OP_JP_HL:
    {
        /* Jump to HL, PC = Joined HL */
        cpu->registers.pc = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "jp hl\n");
        cpu->cycles += 1;
    } break;

    case OP_LD_A16_A:
    {
        /* LD A16 A, Write a into byte in a16 */
        uint8_t high = __sm83_fetch8(cpu);
        uint8_t low =  __sm83_fetch8(cpu);
        __sm83_load_r16_n8(cpu, high, low, cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld [0x%04x], a\n", ((high << 8) | low));
    } break;

    case OP_ILEGAL_EB: return __sm83_illegal_access(0xEB);
    case OP_ILLEGAL_EC: return __sm83_illegal_access(0xEC);
    case OP_ILEGALL_ED: return __sm83_illegal_access(0xED);

    case OP_XOR_A_N8:
    {
        /* xor a with n8 and save back to a */
        uint8_t n8 = __sm83_fetch8(cpu);
        __sm83_xor_r8_r8(cpu, &cpu->registers.a, &n8);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld a, [0x%02x]\n", n8);
    } break;

    case OP_RST_28:
    {
        /* RST 28 */
        __sm83_rst_vec(cpu, 0x0028);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rst 0x%04x\n", 0x0028);
    } break;

    case OP_LDH_A_A8:
    {
        /* LDH A, [A8] Write a into FF00 + A8 */
        uint8_t a8 = __sm83_fetch8(cpu);
        uint8_t high = 0xFF;
        uint16_t addr = __sm83_join_eight_bits(high, a8);
        cpu->registers.a = sm83_read(cpu, addr);
       EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ldh a, [0x%04x]\n", addr);
    } break;

    case OP_POP_AF:
    {
        /* POP AF */
        cpu->registers.a = sm83_read(cpu, cpu->registers.sp++); // pop low
        cpu->registers.f = sm83_read(cpu, cpu->registers.sp++); // pop high
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "pop af\n");        
    } break;

    case OP_LDH_A_C:
    {
        /* LDH A, [C] Write A into FF00 + C */
        uint8_t C = cpu->registers.c;
        uint8_t high = 0xFF;
        uint16_t addr = __sm83_join_eight_bits(high, C);
        cpu->registers.a = sm83_read(cpu, addr);
       EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ldh a, [0x%04x]\n", C);
    } break;

    case OP_DI:
    {
        /* Disasble Interrupt, clear ime flag */
        cpu->ime = 0;
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "di\n");
    } break;

    case OP_ILLEGAL_F4: return __sm83_illegal_access(0xF4);

    case OP_PUSH_AF:
    {
        /* Push AF */
        sm83_write8(cpu, cpu->registers.a, --cpu->registers.sp);
        sm83_write8(cpu, cpu->registers.f, --cpu->registers.sp);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "push af\n");
    } break;

    case OP_OR_A_N8:
    {
        /* or a with n8, save back to a*/
        uint8_t n8 = __sm83_fetch8(cpu);
        __sm83_or_r8_r8(cpu, &cpu->registers.a, &n8);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "or a, 0x%02x\n", n8);
    } break;

    case OP_RST_30:
    {
        /* RST 30 */
        __sm83_rst_vec(cpu, 0x0030);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rst 0x%04x\n", 0x0030);
    } break;

    case OP_LD_HL_SPE8:
    {
        /* LDH HL, SP + E8 */
        int8_t e8 = __sm83_fetch8(cpu);
        uint16_t sp = cpu->registers.sp;
        uint16_t result = sp + (int16_t)e8;
        cpu->registers.h = result >> 8;
        cpu->registers.l = result & 0xFF;
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld hl, sp + 0x%02x", e8);
    } break;

    case OP_LD_SP_HL:
    {
        /* LD SP, HL Copy HL into SP */
        uint16_t hl = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        cpu->registers.sp = hl;
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld sp, hl");
    } break;

    case OP_LD_A_A16:
    {
        /* LD A a16, copy byte in a16 into a*/
        uint8_t low  = __sm83_fetch8(cpu);
        uint8_t high = __sm83_fetch8(cpu);
        __sm83_load_r8_r16(cpu, &high, &low, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ld a, [0x%04x]", ((high << 8) | low));
    } break;

    case OP_EI:
    {
        /* Enable Interrupt, set ime flag */
        cpu->ime = 1;
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "ei\n");
    } break;

    case OP_ILLEGAL_FC: return __sm83_illegal_access(0xFC);
    case OP_ILEGALL_FD: return __sm83_illegal_access(0xFD);

    case OP_CP_A_N8:
    {
        /* CP A N8 */
        uint8_t n8 = __sm83_fetch8(cpu);
        __sm83_cp_r8_r8(cpu, &cpu->registers.a, &n8);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "cp a, 0x%02x\n", n8);
    } break;

    case OP_RST_38:
    {
        /* RST 38 */
        __sm83_rst_vec(cpu, 0x0038);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rst 0x%04x\n", 0x0038);
    } break;

    default:
        fprintf(stderr, "ERROR: `0x%x`, `%s` Intruction Not Handled Yet\n", instr, sm83_opcode_as_cstr(instr));
        return SM83_ERR_INVALID_OPCODE;
    }
    return SM83_OK;
}

enum SM83Error sm83_decode_cb_prefixed(struct SM83CPU *cpu)
{
    /* Read the CB Prefixed Instruction From the ROM */
    uint8_t cb_prefixed_instr = __sm83_fetch8(cpu);

    /* Emit Status */
    int emit = cpu->emit_disasm;

    switch (cb_prefixed_instr)
    {
    case OP_RLC_B:
    {
        /* RLC B */
        __sm83_rlc(cpu, &cpu->registers.b);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rlc b\n");
    } break;

    case OP_RLC_C:
    {
        /* RLC C */
        __sm83_rlc(cpu, &cpu->registers.c);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rlc c\n");
    } break;

    case OP_RLC_D:
    {
        /* RLC D */
        __sm83_rlc(cpu, &cpu->registers.d);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rlc d\n");
    } break;

    case OP_RLC_E:
    {
        /* RLC E */
        __sm83_rlc(cpu, &cpu->registers.e);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rlc e\n");
    } break;

    case OP_RLC_H:
    {
        /* RLC H */
        __sm83_rlc(cpu, &cpu->registers.h);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rlc h\n");
    } break;

    case OP_RLC_L:
    {
        /* RLC L */
        __sm83_rlc(cpu, &cpu->registers.l);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rlc l\n");
    } break;

    case OP_RLC_HL:
    {
        /* RLC HL */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        uint8_t data = sm83_read(cpu, addr);
        __sm83_rlc(cpu, &data);
        sm83_write8(cpu, data, addr);
        cpu->cycles +=2;
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rlc [hl]\n");
    } break;

    case OP_RLC_A:
    {
        /* RLC A */
        __sm83_rlc(cpu, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rlc a\n");
    } break;

    case OP_RRC_B:
    {
        /* RRC B */
        __sm83_rrc(cpu, &cpu->registers.b);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rrc b\n");
    } break;

    case OP_RRC_C:
    {
        /* RRC C */
        __sm83_rrc(cpu, &cpu->registers.c);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rrc c\n");
    } break;

    case OP_RRC_D:
    {
        /* RRC D */
        __sm83_rrc(cpu, &cpu->registers.d);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rrc d\n");
    } break;

    case OP_RRC_E:
    {
        /* RRC E */
        __sm83_rrc(cpu, &cpu->registers.e);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rrc e\n");
    } break;

    case OP_RRC_H:
    {
        /* RRC H */
        __sm83_rrc(cpu, &cpu->registers.h);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rrc h\n");
    } break;

    case OP_RRC_L:
    {
        /* RRC L */
        __sm83_rrc(cpu, &cpu->registers.l);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rrc l\n");
    } break;

    case OP_RRC_HL:
    {
        /* RRC HL */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        uint8_t data = sm83_read(cpu, addr);
        __sm83_rrc(cpu, &data);
        sm83_write8(cpu, data, addr);
        cpu->cycles += 2;
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rrc [hl]\n");
    } break;

    case OP_RRC_A: {
        /* RRC A */
        __sm83_rrc(cpu, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rrc a\n");
    } break;

    case OP_RL_B:
    {
        /* RL B */
        __sm83_rl(cpu, &cpu->registers.b);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rl b\n");
    } break;

    case OP_RL_C:
    {
        /* RL C */
        __sm83_rl(cpu, &cpu->registers.c);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rl c\n");
    } break;

    case OP_RL_D:
    {
        /* RL D */
        __sm83_rl(cpu, &cpu->registers.d);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rl d\n");
    } break;

    case OP_RL_E:
    {
        /* RL E */
        __sm83_rl(cpu, &cpu->registers.e);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rl e\n");
    } break;

    case OP_RL_H:
    {
        /* RL H */
        __sm83_rl(cpu, &cpu->registers.h);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rl h\n");
    } break;

    case OP_RL_L:
    {
        /* RL L */
        __sm83_rl(cpu, &cpu->registers.l);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rl l\n");
    } break;

    case OP_RL_HL:
    {
        /* RL HL */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        uint8_t data = sm83_read(cpu, addr);
        __sm83_rl(cpu, &data);
        sm83_write8(cpu, data, addr);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rl [hl]\n");
    } break;

    case OP_RL_A:
    {
        /* RL A */
        __sm83_rl(cpu, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rl a\n");
    } break;

    case OP_RR_B:
    {
        /* RR B */
        __sm83_rr(cpu, &cpu->registers.b);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rr b\n");
    } break;

    case OP_RR_C:
    {
        /* RR C */
        __sm83_rr(cpu, &cpu->registers.c);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rr c\n");
    } break;

    case OP_RR_D:
    {
        /* RR D */
        __sm83_rr(cpu, &cpu->registers.d);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rr d\n");
    } break;

    case OP_RR_E:
    {
        /* RR E */
        __sm83_rr(cpu, &cpu->registers.e);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rr e\n");
    } break;

    case OP_RR_H:
    {
        /* RR H */
        __sm83_rr(cpu, &cpu->registers.h);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rr h\n");
    } break;

    case OP_RR_L:
    {
        /* RR L */
        __sm83_rr(cpu, &cpu->registers.l);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rr l\n");
    } break;

    case OP_RR_HL:
    {
        /* RR HL */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        uint8_t data = sm83_read(cpu, addr);
        __sm83_rr(cpu, &data);
        sm83_write8(cpu, data, addr);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rr [hl]\n");
    } break;

    case OP_RR_A:
    {
        /* RR A */
        __sm83_rr(cpu, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "rr a\n");
    } break;

    case OP_SLA_C:
    {
        /* SLA C */
        __sm83_sla(cpu, &cpu->registers.c);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sla c\n");
    } break;

    case OP_SLA_D:
    {
        /* SLA D */
        __sm83_sla(cpu, &cpu->registers.d);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sla d\n");
    } break;

    case OP_SLA_E:
    {
        /* SLA E */
        __sm83_sla(cpu, &cpu->registers.e);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sla e\n");
    } break;

    case OP_SLA_H:
    {
        /* SLA H */
        __sm83_sla(cpu, &cpu->registers.h);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sla h\n");
    } break;

    case OP_SLA_L:
    {
        /* SLA L */
        __sm83_sla(cpu, &cpu->registers.l);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sla l\n");
    } break;

    case OP_SLA_HL:
    {
        /* SLA HL */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        uint8_t data = sm83_read(cpu, addr);
        __sm83_sla(cpu, &data);
        sm83_write8(cpu, data, addr);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sla [hl]\n");
    } break;

    case OP_SLA_A:
    {
        /* SLA A */
        __sm83_sla(cpu, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sla a\n");
    } break;

    case OP_SRA_B:
    {
        /* SRA B */
        __sm83_sra(cpu, &cpu->registers.b);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sra b\n");
    } break;

    case OP_SRA_C:
    {
        /* SRA C */
        __sm83_sra(cpu, &cpu->registers.c);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sra c\n");
    } break;

    case OP_SRA_D:
    {
        /* SRA D */
        __sm83_sra(cpu, &cpu->registers.d);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sra d\n");
    } break;

    case OP_SRA_E:
    {
        /* SRA E */
        __sm83_sra(cpu, &cpu->registers.e);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sra e\n");
    } break;

    case OP_SRA_H:
    {
        /* SRA H */
        __sm83_sra(cpu, &cpu->registers.h);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sra h\n");
    } break;

    case OP_SRA_L:
    {
        /* SRA L */
        __sm83_sra(cpu, &cpu->registers.l);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sra l\n");
    } break;

    case OP_SRA_HL:
    {
        /* SRA HL */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        uint8_t data = sm83_read(cpu, addr);
        __sm83_sla(cpu, &data);
        sm83_write8(cpu, data, addr);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sra hl\n");
    } break;

    case OP_SRA_A:
    {
        /* SRA A */
        __sm83_sra(cpu, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "sra a\n");
    } break;

    case OP_SWAP_B:
    {
        /* SWAP B */
        __sm83_swap(cpu, &cpu->registers.b);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "swap b\n");
    } break;

    case OP_SWAP_C:
    {
        /* SWAP C */
        __sm83_swap(cpu, &cpu->registers.c);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "swap c\n");
    } break;

    case OP_SWAP_D:
    {
        /* SWAP D */
        __sm83_swap(cpu, &cpu->registers.d);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "swap d\n");
    } break;

    case OP_SWAP_E:
    {
        /* SWAP E */
        __sm83_swap(cpu, &cpu->registers.e);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "swap e\n");
    } break;

    case OP_SWAP_H:
    {
        /* SWAP H */
        __sm83_swap(cpu, &cpu->registers.h);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "swap h\n");
    } break;

    case OP_SWAP_L:
    {
        /* SWAP L */
        __sm83_swap(cpu, &cpu->registers.l);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "swap l\n");
    } break;

    case OP_SWAP_HL:
    {
        /* SWAP HL */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        uint8_t data = sm83_read(cpu, addr);
        __sm83_swap(cpu, &data);
        sm83_write8(cpu, data, addr);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "swap [hl]\n");
    } break;

    case OP_SWAP_A:
    {
        /* SWAP A */
        __sm83_swap(cpu, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "swap a\n");
    } break;

    case OP_SRL_B:
    {
        /* SRL B */
        __sm83_srl(cpu, &cpu->registers.b);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "srl b\n");
    } break;

    case OP_SRL_C:
    {
        /* SRL C */
        __sm83_srl(cpu, &cpu->registers.c);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "srl c\n");
    } break;

    case OP_SRL_D:
    {
        /* SRL D */
        __sm83_srl(cpu, &cpu->registers.d);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "srl d\n");
    } break;

    case OP_SRL_E:
    {
        /* SRL E */
        __sm83_srl(cpu, &cpu->registers.e);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "srl e\n");
    } break;

    case OP_SRL_H:
    {
        /* SRL H */
        __sm83_srl(cpu, &cpu->registers.h);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "srl h\n");
    } break;

    case OP_SRL_L:
    {
        /* SRL L */
        __sm83_srl(cpu, &cpu->registers.l);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "srl l\n");
    } break;

    case OP_SRL_HL:
    {
        /* SRL HL */
        uint16_t addr = __sm83_join_eight_bits(cpu->registers.h, cpu->registers.l);
        uint8_t data = sm83_read(cpu, addr);
        __sm83_srl(cpu, &data);
        sm83_write8(cpu, data, addr);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "srl [hl]\n");
    } break;

    case OP_SRL_A:
    {
        /* SRL A */
        __sm83_srl(cpu, &cpu->registers.a);
        EMIT_DISASM(emit, SM83_ERR_DISASM, &cpu->disasm, "srl a\n");
    } break;

    default:
        fprintf(stderr, "ERROR: `0x%x` CB Intruction Not Handled Yet\n", cb_prefixed_instr);
        return SM83_ERR_INVALID_OPCODE;
    }

    return SM83_OK;
}