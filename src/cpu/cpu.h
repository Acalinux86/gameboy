#ifndef GB_CPU_H_
#define GB_CPU_H_

#include <stdint.h>
#include "../mmu/mmu.h"

typedef struct GbRegisters {
    uint8_t A, F;
    uint8_t B, C;
    uint8_t D, E;
    uint8_t H, L;
    uint16_t SP;
    uint16_t PC;
} GbRegisters;

typedef enum GbRegisterType {
    GB_REG_A,
    GB_REG_F,
    GB_REG_B,
    GB_REG_C,
    GB_REG_D,
    GB_REG_E,
    GB_REG_H,
    GB_REG_L,
    GB_REG_SP,
    GB_REG_PC,
} GbRegisterType;

#include "./opcodes.h"
typedef enum GbOpcodes {
    #define GB_OPCODE(c) GB_OPCODE_##c,
    GB_OPCODES
    #undef GB_OPCODE
} GbOpcodes;

typedef enum GbFlagBits {
    GB_FLAG_C = 4,
    GB_FLAG_H = 5,
    GB_FLAG_N = 6,
    GB_FLAG_Z = 7,
} GbFlagBits;

typedef enum GbFlagState {
    GB_DEF, // Left-Untouched
    GB_RST, // Reset => 0
    GB_SET, // Set => 1
    GB_UPT, // Updated => based on the operation performed
} GbFlagState;

typedef struct GbCpuState {
    GbMemoryMap *mmu;
    GbRegisters regs;
} GbCpuState;

typedef enum GbLoadType {
    GB_TYPE_R, // No Immediate loads or access
    GB_TYPE_N8,
    GB_TYPE_N16,
    GB_TYPE_A8,
    GB_TYPE_A16,
    GB_TYPE_E8
} GbLoadType;

typedef enum GbAddressMode {
    GB_IND,
    GB_ABS,
    GB_IMM,
    GB_REL,
    GB_REG,
    GB_IMP,
} GbAddressMode;

#define MAX_REGS_COUNT 10
#define MAX_FLAG_BIT_COUNT 4
#define MAX_FLAG_STATE_COUNT 4

// TODO: Document this Struct
typedef struct GbOpcodeEntry {
    GbOpcodes opcode;
    GbLoadType type;
    GbAddressMode mode;

    GbRegisterType regs[MAX_REGS_COUNT];
    int regs_count;

    int bytes;
    int t_states;

    GbFlagBits flags[MAX_FLAG_BIT_COUNT];
    int flag_count;

    GbFlagState state[MAX_FLAG_STATE_COUNT];
} GbOpcodeEntry;

const char *gb_cpu_opcode_string(const GbOpcodes opcode);
const char *gb_cpu_reg_string(const GbRegisterType type);
const char *gb_cpu_addr_mode_string(const GbAddressMode mode);
const char *gb_cpu_load_type_string(const GbLoadType type);
const char *gb_cpu_flag_bit_string(const GbFlagBits bit);
const char *gb_cpu_flag_state_string(const GbFlagState state);
void gb_cpu_instruction_string(const GbOpcodeEntry *entry);

#define GB_OP_LUT_ROWS 16 // Opcode LookUp Table Rows
#define GB_OP_LUT_COLS 16 // Opcode LookUp Table Cols
extern const GbOpcodeEntry GbOpcodeLookupTable[GB_OP_LUT_ROWS][GB_OP_LUT_COLS];

GbCpuState gb_cpu_init_states(uint16_t PC);
void gb_cpu_shutdown(GbCpuState *state);

uint8_t  gb_cpu_fetch8 (GbCpuState *cpu);
uint16_t gb_cpu_fetch16(GbCpuState *cpu);
bool     gb_cpu_decode (GbCpuState *cpu);

// TODO: Addressing Modes
// TODO: Logging Instruction
// TODO: private method to join resgister
//       Based on the Resgister Array provided also
//       uint16 gb__cpu_join_regs(GbCpustate *cpu, GbRegistertype regs[], const int regs_count);

#endif // GB_CPU_H_
