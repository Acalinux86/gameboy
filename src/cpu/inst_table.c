#include "./cpu.h"

const GbOpcodeEntry GbOpcodeLookupTable[GB_OP_LUT_ROWS][GB_OP_LUT_COLS] = {
    // Row 0x0
    {
        {
            // NOP => Col 0x0
            .opcode = GB_OPCODE_NOP, .type = GB_TYPE_R,
            .regs = {0}, .regs_count = 0,
            .bytes = 1, .t_states = 4,
            .flags = {0}, .flag_count = 0,
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF}
        },
        {
            // LD BC, n16 => Col 0x1
            .opcode = GB_OPCODE_LD, .type = GB_TYPE_N16,
            .regs = {GB_REG_B, GB_REG_C}, .regs_count = 2,
            .bytes = 3, .t_states = 12,
            .flags = {0}, .flag_count = 0,
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF}
        },
        {
            // LD [BC] A => Col 0x2
            .opcode = GB_OPCODE_LD, .type = GB_TYPE_R,
            .regs = {GB_REG_A}, .regs_count = 1,
            .bytes = 1, .t_states = 8,
            .flags = {0}, .flag_count = 0,
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF}
        },
        {
            // INC BC => Col 0x3
            .opcode = GB_OPCODE_INC, .type = GB_TYPE_R,
            .regs = {GB_REG_B, GB_REG_C}, .regs_count = 2,
            .bytes = 1, .t_states = 8,
            .flags = {0}, .flag_count = 0,
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF}
        },
        {
            // INC B => Col 0x4
            .opcode = GB_OPCODE_INC, .type = GB_TYPE_R,
            .regs = {GB_REG_B}, .regs_count = 1,
            .bytes = 1, .t_states = 4,
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H},
            .flag_count = 0,
            .state = {GB_UPT, GB_RST, GB_UPT, GB_DEF}
        },
        {
            // DEC B => Col 0x5
            .opcode = GB_OPCODE_DEC, .type = GB_TYPE_R,
            .regs = {GB_REG_B}, .regs_count = 1,
            .bytes = 1, .t_states = 4,
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H},
            .flag_count = 0,
            .state = {GB_UPT, GB_SET, GB_UPT, GB_DEF}
        },
        {
            // LD B, n8 => Col 0x6
            .opcode = GB_OPCODE_LD, .type = GB_TYPE_N8,
            .regs = {GB_REG_B}, .regs_count = 1,
            .bytes = 2, .t_states = 8,
            .flags = {0}, .flag_count = 0,
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF}
        },
        {
            // RLC A => Col 0x7
            .opcode = GB_OPCODE_RLC, .type = GB_TYPE_R,
            .regs = {GB_REG_A}, .regs_count = 1,
            .bytes = 1, .t_states = 4,
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C},
            .flag_count = 4,
            .state = {GB_RST, GB_RST, GB_RST, GB_UPT}
        },
        {
            // LD [A16], SP => Col 0x8
            .opcode = GB_OPCODE_LD, .type = GB_TYPE_A16,
            .regs = {GB_REG_SP}, .regs_count = 1,
            .bytes = 3, .t_states = 20,
            .flags = {0}, .flag_count = 0,
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF}
        },
        {
            // ADD HL, BC => 0x9
            .opcode = GB_OPCODE_ADD, .type = GB_TYPE_R,
            .regs = {GB_REG_H, GB_REG_L, GB_REG_B, GB_REG_C},
            .regs_count = 4,
            .bytes = 1, .t_states = 8,
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C},
            .flag_count = 4,
            .state = {GB_DEF, GB_RST, GB_UPT, GB_UPT}
        },
        {
            // LD A, [BC] => 0xA
            .opcode = GB_OPCODE_LD, .type = GB_TYPE_R,
            .regs = {GB_REG_A, GB_REG_B, GB_REG_C},
            .regs_count = 4,
            .bytes = 1, .t_states = 8,
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C},
            .flag_count = 4,
            .state = {GB_DEF, GB_RST, GB_UPT, GB_UPT}
        },
    },
};
