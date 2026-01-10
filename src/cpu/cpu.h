#ifndef GB_CPU_H_
#define GB_CPU_H_

#include <stdint.h>
#include "../mmu/mmu.h"

typedef struct GbRegisters {
    uint8_t A, F;
    uint8_t B, C;
    uint8_t D, E;
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
    GB_REG_SP,
    GB_REG_PC,
} GbRegisterType;

typedef enum GbOpcodes {
    #define GB_OPCODE(c) GB_OPCODE_##c
    #include "./opcodes.h"
    #undef OPCODE
} GbOpcodes;

typedef enum GbFlagBits {
    GB_FLAG_Z,
    GB_FLAG_N,
    GB_FLAG_H,
    GB_FLAG_C,
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

} GbAddressMode;

#define MAX_REGS_COUNT 8
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

GbCpuState gb_cpu_init_states(void);

uint8_t gb_cpu_fetch8 (GbCpuState *cpu);
uint8_t gb_cpu_fetch16(GbCpuState *cpu);

bool   gb_cpu_decode_instruction(GbCpuState *cpu, const uint8_t instruction);

// TODO: Addressing Modes
// TODO: Logging Instruction
// TODO: private method to join resgister
//       Based on the Resgister Array provided also
//       uint16 gb__cpu_join_regs(GbCpustate *cpu, GbRegistertype[] regs, const int regs_count);

#endif // GB_CPU_H_
