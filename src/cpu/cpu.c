#include "cpu.h"
#include "log.h"
#include "opcode_tables.c"
#include "opcodes.h"

const char *gb_cpu_opcode_string(const GbOpcodes opcode)
{
    switch (opcode) {
        #define GB_OPCODE(c) case GB_OPCODE_##c: return #c;
        GB_OPCODES
        #undef GB_OPCODE
        default: return "Unknown Opcode";
    }
}

const char *gb_cpu_reg_string(const GbRegisterType type)
{
    switch (type) {
    case GB_REG_A:  return "Accumulator";
    case GB_REG_F:  return "Flag Resister";
    case GB_REG_B:  return "B Register";
    case GB_REG_C:  return "C Register";
    case GB_REG_D:  return "D Register";
    case GB_REG_E:  return "E Register";
    case GB_REG_H:  return "H Register";
    case GB_REG_L:  return "L Register";
    case GB_REG_SP: return "Stack Pointer";
    case GB_REG_PC: return "Program Counter";
    default:        return "Unknown Register";
    }
}

const char *gb_cpu_addr_mode_string(const GbAddressMode mode)
{
    switch (mode) {
    case GB_IND: return "Indirect";
    case GB_ABS: return "Absolute";
    case GB_IMM: return "Immediate";
    case GB_REL: return "Relative";
    case GB_REG: return "Register";
    case GB_IMP: return "Implicit";
    default:     return "Unknown Addressing Mode";
    }
}

const char *gb_cpu_load_type_string(const GbLoadType type)
{
    switch (type) {
    case GB_TYPE_N8:  return "immediate 8-bit data";
    case GB_TYPE_N16: return "immediate LE 16-bit data";
    case GB_TYPE_A8:  return "8-bit unsigned address";
    case GB_TYPE_A16: return "LE 16-bit address";
    case GB_TYPE_E8:  return "8-bit signed data";
    default:          return "Unknown Load type";
    }
}

const char *gb_cpu_flag_bit_string(const GbFlagBits bit)
{
    switch (bit) {
    case GB_FLAG_Z: return "Z-Bit(7)";
    case GB_FLAG_N: return "N-Bit(6)";
    case GB_FLAG_H: return "H-Bit(5)";
    case GB_FLAG_C: return "C-Bit(4)";
    default: return "Unknown F flag bit";
    }
}

const char *gb_cpu_flag_state_string(const GbFlagState state)
{
    switch (state) {
    case GB_DEF: return "Left-Untouched";
    case GB_RST: return "Reset => 0";
    case GB_SET: return "Set => 1";
    case GB_UPT: return "Updated => based on the operation performed";
    default:     return "Unknown Flag State";
    }
}

GbCpuState gb_cpu_init_states(const uint16_t PC)
{
    GbMemoryMap *mmu = gb_mmu_init();
    GbCpuState state = {0};
    state.mmu = mmu;
    state.regs.PC = PC;
    return state;
}

void gb_cpu_shutdown(GbCpuState *state)
{
    gb_mmu_destroy(state->mmu);
    state = NULL;
}

uint8_t gb_cpu_fetch8(GbCpuState *cpu)
{
    const uint8_t data = gb_mmu_read(cpu->mmu, cpu->regs.PC++);
    return data;
}

uint16_t gb_cpu_fetch16(GbCpuState *cpu)
{
    const uint8_t lsb = gb_mmu_read(cpu->mmu, cpu->regs.PC++);
    const uint8_t msb = gb_mmu_read(cpu->mmu, cpu->regs.PC++);
    const uint16_t data = (uint16_t)((msb << 8) | lsb);
    return data;
}

typedef struct Nibbles {
    uint8_t upper;
    uint8_t lower;
} Nibbles;

Nibbles gb_cpu_split_u8(const uint8_t value)
{
    return (Nibbles){
        .lower = value & 0x0F,
        .upper = (value >> 4) & 0X0F
    };
}

uint8_t gb_cpu_join_nibbles(const Nibbles nibble)
{
    return nibble.upper << 4 | nibble.lower;
}

bool gb_cpu_decode(GbCpuState *cpu)
{
    uint8_t data = gb_cpu_fetch8(cpu);
    uint8_t upper = (data >> 4) & 0xF;
    uint8_t lower = data & 0xF;
    const GbOpcodeEntry entry = GbOpcodeLookupTable[upper][lower];

    switch (entry.opcode)
    {
    case GB_OPCODE_NOP:
        gb_cpu_fetch8(cpu);
        break;
    default:
        GB_ERROR("Unimplemented Opcode: %s", gb_cpu_opcode_string(entry.opcode));
        return false;
    }
    return true;
}

static uint16_t gb_cpu_join_af(const GbCpuState *cpu)
{
    return cpu->regs.A << 8 | cpu->regs.F;
}

static uint16_t gb_cpu_join_bc(const GbCpuState *cpu)
{
    return cpu->regs.B << 8 | cpu->regs.C;
}

static uint16_t gb_cpu_join_hl(const GbCpuState *cpu)
{
    return cpu->regs.H << 8 | cpu->regs.L;
}

static uint16_t gb_cpu_join_de(const GbCpuState *cpu)
{
    return cpu->regs.D << 8 | cpu->regs.E;
}
