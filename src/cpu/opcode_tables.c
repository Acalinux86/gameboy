// This file is generated automatically. DO NOT MODIFY THIS FILE!!! /*codegen.py:51*/
#include "cpu.h"    /*codegen.py:48*/

const GbOpcodeEntry GbOpcodeLookupTable[GB_OP_LUT_ROWS][GB_OP_LUT_COLS] = { /*codegen.py:57*/
    // Row Start => 0x0 
    { /*codegen.py:60*/
        { 
            // Col Start => 0x0  /*codegen.py:63*/
            .opcode = GB_OPCODE_NOP, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x0 /*codegen.py:66*/

        { 
            // Col Start => 0x1  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 3, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_B, GB_REG_C}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N16, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x1 /*codegen.py:66*/

        { 
            // Col Start => 0x2  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_B, GB_REG_C}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x2 /*codegen.py:66*/

        { 
            // Col Start => 0x3  /*codegen.py:63*/
            .opcode = GB_OPCODE_INC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x3 /*codegen.py:66*/

        { 
            // Col Start => 0x4  /*codegen.py:63*/
            .opcode = GB_OPCODE_INC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x4 /*codegen.py:66*/

        { 
            // Col Start => 0x5  /*codegen.py:63*/
            .opcode = GB_OPCODE_DEC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x5 /*codegen.py:66*/

        { 
            // Col Start => 0x6  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x6 /*codegen.py:66*/

        { 
            // Col Start => 0x7  /*codegen.py:63*/
            .opcode = GB_OPCODE_RLCA, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_RST, GB_RST, GB_RST, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x7 /*codegen.py:66*/

        { 
            // Col Start => 0x8  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 3, /*codegen.py:75*/
            .t_states = 20, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .type = GB_TYPE_A16, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_SP}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x8 /*codegen.py:66*/

        { 
            // Col Start => 0x9  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B, GB_REG_C}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_DEF, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x9 /*codegen.py:66*/

        { 
            // Col Start => 0xA  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B, GB_REG_C}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xA /*codegen.py:66*/

        { 
            // Col Start => 0xB  /*codegen.py:63*/
            .opcode = GB_OPCODE_DEC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xB /*codegen.py:66*/

        { 
            // Col Start => 0xC  /*codegen.py:63*/
            .opcode = GB_OPCODE_INC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xC /*codegen.py:66*/

        { 
            // Col Start => 0xD  /*codegen.py:63*/
            .opcode = GB_OPCODE_DEC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xD /*codegen.py:66*/

        { 
            // Col Start => 0xE  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xE /*codegen.py:66*/

        { 
            // Col Start => 0xF  /*codegen.py:63*/
            .opcode = GB_OPCODE_RRCA, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_RST, GB_RST, GB_RST, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xF /*codegen.py:66*/

    }, // Row End => 0x0 /*codegen.py:69*/

    // Row Start => 0x1 
    { /*codegen.py:60*/
        { 
            // Col Start => 0x0  /*codegen.py:63*/
            .opcode = GB_OPCODE_STOP, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x0 /*codegen.py:66*/

        { 
            // Col Start => 0x1  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 3, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_D, GB_REG_E}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N16, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x1 /*codegen.py:66*/

        { 
            // Col Start => 0x2  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_D, GB_REG_E}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x2 /*codegen.py:66*/

        { 
            // Col Start => 0x3  /*codegen.py:63*/
            .opcode = GB_OPCODE_INC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x3 /*codegen.py:66*/

        { 
            // Col Start => 0x4  /*codegen.py:63*/
            .opcode = GB_OPCODE_INC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x4 /*codegen.py:66*/

        { 
            // Col Start => 0x5  /*codegen.py:63*/
            .opcode = GB_OPCODE_DEC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x5 /*codegen.py:66*/

        { 
            // Col Start => 0x6  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x6 /*codegen.py:66*/

        { 
            // Col Start => 0x7  /*codegen.py:63*/
            .opcode = GB_OPCODE_RLA, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_RST, GB_RST, GB_RST, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x7 /*codegen.py:66*/

        { 
            // Col Start => 0x8  /*codegen.py:63*/
            .opcode = GB_OPCODE_JR, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x8 /*codegen.py:66*/

        { 
            // Col Start => 0x9  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D, GB_REG_E}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_DEF, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x9 /*codegen.py:66*/

        { 
            // Col Start => 0xA  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D, GB_REG_E}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xA /*codegen.py:66*/

        { 
            // Col Start => 0xB  /*codegen.py:63*/
            .opcode = GB_OPCODE_DEC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xB /*codegen.py:66*/

        { 
            // Col Start => 0xC  /*codegen.py:63*/
            .opcode = GB_OPCODE_INC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xC /*codegen.py:66*/

        { 
            // Col Start => 0xD  /*codegen.py:63*/
            .opcode = GB_OPCODE_DEC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xD /*codegen.py:66*/

        { 
            // Col Start => 0xE  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xE /*codegen.py:66*/

        { 
            // Col Start => 0xF  /*codegen.py:63*/
            .opcode = GB_OPCODE_RRA, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_RST, GB_RST, GB_RST, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xF /*codegen.py:66*/

    }, // Row End => 0x1 /*codegen.py:69*/

    // Row Start => 0x2 
    { /*codegen.py:60*/
        { 
            // Col Start => 0x0  /*codegen.py:63*/
            .opcode = GB_OPCODE_JR, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_E8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x0 /*codegen.py:66*/

        { 
            // Col Start => 0x1  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 3, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N16, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x1 /*codegen.py:66*/

        { 
            // Col Start => 0x2  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x2 /*codegen.py:66*/

        { 
            // Col Start => 0x3  /*codegen.py:63*/
            .opcode = GB_OPCODE_INC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x3 /*codegen.py:66*/

        { 
            // Col Start => 0x4  /*codegen.py:63*/
            .opcode = GB_OPCODE_INC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x4 /*codegen.py:66*/

        { 
            // Col Start => 0x5  /*codegen.py:63*/
            .opcode = GB_OPCODE_DEC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x5 /*codegen.py:66*/

        { 
            // Col Start => 0x6  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x6 /*codegen.py:66*/

        { 
            // Col Start => 0x7  /*codegen.py:63*/
            .opcode = GB_OPCODE_DAA, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_DEF, GB_RST, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x7 /*codegen.py:66*/

        { 
            // Col Start => 0x8  /*codegen.py:63*/
            .opcode = GB_OPCODE_JR, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .src = {
                .type = GB_TYPE_E8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x8 /*codegen.py:66*/

        { 
            // Col Start => 0x9  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_DEF, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x9 /*codegen.py:66*/

        { 
            // Col Start => 0xA  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xA /*codegen.py:66*/

        { 
            // Col Start => 0xB  /*codegen.py:63*/
            .opcode = GB_OPCODE_DEC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xB /*codegen.py:66*/

        { 
            // Col Start => 0xC  /*codegen.py:63*/
            .opcode = GB_OPCODE_INC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xC /*codegen.py:66*/

        { 
            // Col Start => 0xD  /*codegen.py:63*/
            .opcode = GB_OPCODE_DEC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xD /*codegen.py:66*/

        { 
            // Col Start => 0xE  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xE /*codegen.py:66*/

        { 
            // Col Start => 0xF  /*codegen.py:63*/
            .opcode = GB_OPCODE_CPL, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 2, /*codegen.py:212*/
            .state = {GB_DEF, GB_SET, GB_SET, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xF /*codegen.py:66*/

    }, // Row End => 0x2 /*codegen.py:69*/

    // Row Start => 0x3 
    { /*codegen.py:60*/
        { 
            // Col Start => 0x0  /*codegen.py:63*/
            .opcode = GB_OPCODE_JR, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_E8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x0 /*codegen.py:66*/

        { 
            // Col Start => 0x1  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 3, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_SP}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N16, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x1 /*codegen.py:66*/

        { 
            // Col Start => 0x2  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x2 /*codegen.py:66*/

        { 
            // Col Start => 0x3  /*codegen.py:63*/
            .opcode = GB_OPCODE_INC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x3 /*codegen.py:66*/

        { 
            // Col Start => 0x4  /*codegen.py:63*/
            .opcode = GB_OPCODE_INC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x4 /*codegen.py:66*/

        { 
            // Col Start => 0x5  /*codegen.py:63*/
            .opcode = GB_OPCODE_DEC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x5 /*codegen.py:66*/

        { 
            // Col Start => 0x6  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x6 /*codegen.py:66*/

        { 
            // Col Start => 0x7  /*codegen.py:63*/
            .opcode = GB_OPCODE_SCF, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_DEF, GB_RST, GB_RST, GB_SET} /*codegen.py:224*/
        }, // Col End => 0x7 /*codegen.py:66*/

        { 
            // Col Start => 0x8  /*codegen.py:63*/
            .opcode = GB_OPCODE_JR, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_E8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x8 /*codegen.py:66*/

        { 
            // Col Start => 0x9  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_SP}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_DEF, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x9 /*codegen.py:66*/

        { 
            // Col Start => 0xA  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xA /*codegen.py:66*/

        { 
            // Col Start => 0xB  /*codegen.py:63*/
            .opcode = GB_OPCODE_DEC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xB /*codegen.py:66*/

        { 
            // Col Start => 0xC  /*codegen.py:63*/
            .opcode = GB_OPCODE_INC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xC /*codegen.py:66*/

        { 
            // Col Start => 0xD  /*codegen.py:63*/
            .opcode = GB_OPCODE_DEC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xD /*codegen.py:66*/

        { 
            // Col Start => 0xE  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xE /*codegen.py:66*/

        { 
            // Col Start => 0xF  /*codegen.py:63*/
            .opcode = GB_OPCODE_CCF, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_DEF, GB_RST, GB_RST, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xF /*codegen.py:66*/

    }, // Row End => 0x3 /*codegen.py:69*/

    // Row Start => 0x4 
    { /*codegen.py:60*/
        { 
            // Col Start => 0x0  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x0 /*codegen.py:66*/

        { 
            // Col Start => 0x1  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x1 /*codegen.py:66*/

        { 
            // Col Start => 0x2  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x2 /*codegen.py:66*/

        { 
            // Col Start => 0x3  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x3 /*codegen.py:66*/

        { 
            // Col Start => 0x4  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x4 /*codegen.py:66*/

        { 
            // Col Start => 0x5  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x5 /*codegen.py:66*/

        { 
            // Col Start => 0x6  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x6 /*codegen.py:66*/

        { 
            // Col Start => 0x7  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x7 /*codegen.py:66*/

        { 
            // Col Start => 0x8  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x8 /*codegen.py:66*/

        { 
            // Col Start => 0x9  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x9 /*codegen.py:66*/

        { 
            // Col Start => 0xA  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xA /*codegen.py:66*/

        { 
            // Col Start => 0xB  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xB /*codegen.py:66*/

        { 
            // Col Start => 0xC  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xC /*codegen.py:66*/

        { 
            // Col Start => 0xD  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xD /*codegen.py:66*/

        { 
            // Col Start => 0xE  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xE /*codegen.py:66*/

        { 
            // Col Start => 0xF  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xF /*codegen.py:66*/

    }, // Row End => 0x4 /*codegen.py:69*/

    // Row Start => 0x5 
    { /*codegen.py:60*/
        { 
            // Col Start => 0x0  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x0 /*codegen.py:66*/

        { 
            // Col Start => 0x1  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x1 /*codegen.py:66*/

        { 
            // Col Start => 0x2  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x2 /*codegen.py:66*/

        { 
            // Col Start => 0x3  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x3 /*codegen.py:66*/

        { 
            // Col Start => 0x4  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x4 /*codegen.py:66*/

        { 
            // Col Start => 0x5  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x5 /*codegen.py:66*/

        { 
            // Col Start => 0x6  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x6 /*codegen.py:66*/

        { 
            // Col Start => 0x7  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x7 /*codegen.py:66*/

        { 
            // Col Start => 0x8  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x8 /*codegen.py:66*/

        { 
            // Col Start => 0x9  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x9 /*codegen.py:66*/

        { 
            // Col Start => 0xA  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xA /*codegen.py:66*/

        { 
            // Col Start => 0xB  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xB /*codegen.py:66*/

        { 
            // Col Start => 0xC  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xC /*codegen.py:66*/

        { 
            // Col Start => 0xD  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xD /*codegen.py:66*/

        { 
            // Col Start => 0xE  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xE /*codegen.py:66*/

        { 
            // Col Start => 0xF  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xF /*codegen.py:66*/

    }, // Row End => 0x5 /*codegen.py:69*/

    // Row Start => 0x6 
    { /*codegen.py:60*/
        { 
            // Col Start => 0x0  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x0 /*codegen.py:66*/

        { 
            // Col Start => 0x1  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x1 /*codegen.py:66*/

        { 
            // Col Start => 0x2  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x2 /*codegen.py:66*/

        { 
            // Col Start => 0x3  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x3 /*codegen.py:66*/

        { 
            // Col Start => 0x4  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x4 /*codegen.py:66*/

        { 
            // Col Start => 0x5  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x5 /*codegen.py:66*/

        { 
            // Col Start => 0x6  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x6 /*codegen.py:66*/

        { 
            // Col Start => 0x7  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x7 /*codegen.py:66*/

        { 
            // Col Start => 0x8  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x8 /*codegen.py:66*/

        { 
            // Col Start => 0x9  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x9 /*codegen.py:66*/

        { 
            // Col Start => 0xA  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xA /*codegen.py:66*/

        { 
            // Col Start => 0xB  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xB /*codegen.py:66*/

        { 
            // Col Start => 0xC  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xC /*codegen.py:66*/

        { 
            // Col Start => 0xD  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xD /*codegen.py:66*/

        { 
            // Col Start => 0xE  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xE /*codegen.py:66*/

        { 
            // Col Start => 0xF  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xF /*codegen.py:66*/

    }, // Row End => 0x6 /*codegen.py:69*/

    // Row Start => 0x7 
    { /*codegen.py:60*/
        { 
            // Col Start => 0x0  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x0 /*codegen.py:66*/

        { 
            // Col Start => 0x1  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x1 /*codegen.py:66*/

        { 
            // Col Start => 0x2  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x2 /*codegen.py:66*/

        { 
            // Col Start => 0x3  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x3 /*codegen.py:66*/

        { 
            // Col Start => 0x4  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x4 /*codegen.py:66*/

        { 
            // Col Start => 0x5  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x5 /*codegen.py:66*/

        { 
            // Col Start => 0x6  /*codegen.py:63*/
            .opcode = GB_OPCODE_HALT, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x6 /*codegen.py:66*/

        { 
            // Col Start => 0x7  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x7 /*codegen.py:66*/

        { 
            // Col Start => 0x8  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x8 /*codegen.py:66*/

        { 
            // Col Start => 0x9  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x9 /*codegen.py:66*/

        { 
            // Col Start => 0xA  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xA /*codegen.py:66*/

        { 
            // Col Start => 0xB  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xB /*codegen.py:66*/

        { 
            // Col Start => 0xC  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xC /*codegen.py:66*/

        { 
            // Col Start => 0xD  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xD /*codegen.py:66*/

        { 
            // Col Start => 0xE  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xE /*codegen.py:66*/

        { 
            // Col Start => 0xF  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xF /*codegen.py:66*/

    }, // Row End => 0x7 /*codegen.py:69*/

    // Row Start => 0x8 
    { /*codegen.py:60*/
        { 
            // Col Start => 0x0  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x0 /*codegen.py:66*/

        { 
            // Col Start => 0x1  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x1 /*codegen.py:66*/

        { 
            // Col Start => 0x2  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x2 /*codegen.py:66*/

        { 
            // Col Start => 0x3  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x3 /*codegen.py:66*/

        { 
            // Col Start => 0x4  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x4 /*codegen.py:66*/

        { 
            // Col Start => 0x5  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x5 /*codegen.py:66*/

        { 
            // Col Start => 0x6  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x6 /*codegen.py:66*/

        { 
            // Col Start => 0x7  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x7 /*codegen.py:66*/

        { 
            // Col Start => 0x8  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x8 /*codegen.py:66*/

        { 
            // Col Start => 0x9  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x9 /*codegen.py:66*/

        { 
            // Col Start => 0xA  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xA /*codegen.py:66*/

        { 
            // Col Start => 0xB  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xB /*codegen.py:66*/

        { 
            // Col Start => 0xC  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xC /*codegen.py:66*/

        { 
            // Col Start => 0xD  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xD /*codegen.py:66*/

        { 
            // Col Start => 0xE  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xE /*codegen.py:66*/

        { 
            // Col Start => 0xF  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xF /*codegen.py:66*/

    }, // Row End => 0x8 /*codegen.py:69*/

    // Row Start => 0x9 
    { /*codegen.py:60*/
        { 
            // Col Start => 0x0  /*codegen.py:63*/
            .opcode = GB_OPCODE_SUB, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x0 /*codegen.py:66*/

        { 
            // Col Start => 0x1  /*codegen.py:63*/
            .opcode = GB_OPCODE_SUB, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x1 /*codegen.py:66*/

        { 
            // Col Start => 0x2  /*codegen.py:63*/
            .opcode = GB_OPCODE_SUB, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x2 /*codegen.py:66*/

        { 
            // Col Start => 0x3  /*codegen.py:63*/
            .opcode = GB_OPCODE_SUB, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x3 /*codegen.py:66*/

        { 
            // Col Start => 0x4  /*codegen.py:63*/
            .opcode = GB_OPCODE_SUB, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x4 /*codegen.py:66*/

        { 
            // Col Start => 0x5  /*codegen.py:63*/
            .opcode = GB_OPCODE_SUB, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x5 /*codegen.py:66*/

        { 
            // Col Start => 0x6  /*codegen.py:63*/
            .opcode = GB_OPCODE_SUB, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x6 /*codegen.py:66*/

        { 
            // Col Start => 0x7  /*codegen.py:63*/
            .opcode = GB_OPCODE_SUB, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_SET, GB_SET, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x7 /*codegen.py:66*/

        { 
            // Col Start => 0x8  /*codegen.py:63*/
            .opcode = GB_OPCODE_SBC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x8 /*codegen.py:66*/

        { 
            // Col Start => 0x9  /*codegen.py:63*/
            .opcode = GB_OPCODE_SBC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x9 /*codegen.py:66*/

        { 
            // Col Start => 0xA  /*codegen.py:63*/
            .opcode = GB_OPCODE_SBC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xA /*codegen.py:66*/

        { 
            // Col Start => 0xB  /*codegen.py:63*/
            .opcode = GB_OPCODE_SBC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xB /*codegen.py:66*/

        { 
            // Col Start => 0xC  /*codegen.py:63*/
            .opcode = GB_OPCODE_SBC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xC /*codegen.py:66*/

        { 
            // Col Start => 0xD  /*codegen.py:63*/
            .opcode = GB_OPCODE_SBC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xD /*codegen.py:66*/

        { 
            // Col Start => 0xE  /*codegen.py:63*/
            .opcode = GB_OPCODE_SBC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xE /*codegen.py:66*/

        { 
            // Col Start => 0xF  /*codegen.py:63*/
            .opcode = GB_OPCODE_SBC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H}, /*codegen.py:211*/
            .flag_count = 3, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xF /*codegen.py:66*/

    }, // Row End => 0x9 /*codegen.py:69*/

    // Row Start => 0xA 
    { /*codegen.py:60*/
        { 
            // Col Start => 0x0  /*codegen.py:63*/
            .opcode = GB_OPCODE_AND, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_SET, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x0 /*codegen.py:66*/

        { 
            // Col Start => 0x1  /*codegen.py:63*/
            .opcode = GB_OPCODE_AND, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_SET, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x1 /*codegen.py:66*/

        { 
            // Col Start => 0x2  /*codegen.py:63*/
            .opcode = GB_OPCODE_AND, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_SET, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x2 /*codegen.py:66*/

        { 
            // Col Start => 0x3  /*codegen.py:63*/
            .opcode = GB_OPCODE_AND, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_SET, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x3 /*codegen.py:66*/

        { 
            // Col Start => 0x4  /*codegen.py:63*/
            .opcode = GB_OPCODE_AND, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_SET, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x4 /*codegen.py:66*/

        { 
            // Col Start => 0x5  /*codegen.py:63*/
            .opcode = GB_OPCODE_AND, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_SET, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x5 /*codegen.py:66*/

        { 
            // Col Start => 0x6  /*codegen.py:63*/
            .opcode = GB_OPCODE_AND, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_SET, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x6 /*codegen.py:66*/

        { 
            // Col Start => 0x7  /*codegen.py:63*/
            .opcode = GB_OPCODE_AND, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_SET, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x7 /*codegen.py:66*/

        { 
            // Col Start => 0x8  /*codegen.py:63*/
            .opcode = GB_OPCODE_XOR, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x8 /*codegen.py:66*/

        { 
            // Col Start => 0x9  /*codegen.py:63*/
            .opcode = GB_OPCODE_XOR, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x9 /*codegen.py:66*/

        { 
            // Col Start => 0xA  /*codegen.py:63*/
            .opcode = GB_OPCODE_XOR, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0xA /*codegen.py:66*/

        { 
            // Col Start => 0xB  /*codegen.py:63*/
            .opcode = GB_OPCODE_XOR, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0xB /*codegen.py:66*/

        { 
            // Col Start => 0xC  /*codegen.py:63*/
            .opcode = GB_OPCODE_XOR, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0xC /*codegen.py:66*/

        { 
            // Col Start => 0xD  /*codegen.py:63*/
            .opcode = GB_OPCODE_XOR, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0xD /*codegen.py:66*/

        { 
            // Col Start => 0xE  /*codegen.py:63*/
            .opcode = GB_OPCODE_XOR, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0xE /*codegen.py:66*/

        { 
            // Col Start => 0xF  /*codegen.py:63*/
            .opcode = GB_OPCODE_XOR, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_SET, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0xF /*codegen.py:66*/

    }, // Row End => 0xA /*codegen.py:69*/

    // Row Start => 0xB 
    { /*codegen.py:60*/
        { 
            // Col Start => 0x0  /*codegen.py:63*/
            .opcode = GB_OPCODE_OR, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x0 /*codegen.py:66*/

        { 
            // Col Start => 0x1  /*codegen.py:63*/
            .opcode = GB_OPCODE_OR, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x1 /*codegen.py:66*/

        { 
            // Col Start => 0x2  /*codegen.py:63*/
            .opcode = GB_OPCODE_OR, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x2 /*codegen.py:66*/

        { 
            // Col Start => 0x3  /*codegen.py:63*/
            .opcode = GB_OPCODE_OR, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x3 /*codegen.py:66*/

        { 
            // Col Start => 0x4  /*codegen.py:63*/
            .opcode = GB_OPCODE_OR, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x4 /*codegen.py:66*/

        { 
            // Col Start => 0x5  /*codegen.py:63*/
            .opcode = GB_OPCODE_OR, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x5 /*codegen.py:66*/

        { 
            // Col Start => 0x6  /*codegen.py:63*/
            .opcode = GB_OPCODE_OR, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x6 /*codegen.py:66*/

        { 
            // Col Start => 0x7  /*codegen.py:63*/
            .opcode = GB_OPCODE_OR, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x7 /*codegen.py:66*/

        { 
            // Col Start => 0x8  /*codegen.py:63*/
            .opcode = GB_OPCODE_CP, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_B}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x8 /*codegen.py:66*/

        { 
            // Col Start => 0x9  /*codegen.py:63*/
            .opcode = GB_OPCODE_CP, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x9 /*codegen.py:66*/

        { 
            // Col Start => 0xA  /*codegen.py:63*/
            .opcode = GB_OPCODE_CP, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_D}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xA /*codegen.py:66*/

        { 
            // Col Start => 0xB  /*codegen.py:63*/
            .opcode = GB_OPCODE_CP, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_E}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xB /*codegen.py:66*/

        { 
            // Col Start => 0xC  /*codegen.py:63*/
            .opcode = GB_OPCODE_CP, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xC /*codegen.py:66*/

        { 
            // Col Start => 0xD  /*codegen.py:63*/
            .opcode = GB_OPCODE_CP, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_L}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xD /*codegen.py:66*/

        { 
            // Col Start => 0xE  /*codegen.py:63*/
            .opcode = GB_OPCODE_CP, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xE /*codegen.py:66*/

        { 
            // Col Start => 0xF  /*codegen.py:63*/
            .opcode = GB_OPCODE_CP, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_SET, GB_SET, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0xF /*codegen.py:66*/

    }, // Row End => 0xB /*codegen.py:69*/

    // Row Start => 0xC 
    { /*codegen.py:60*/
        { 
            // Col Start => 0x0  /*codegen.py:63*/
            .opcode = GB_OPCODE_RET, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 20, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x0 /*codegen.py:66*/

        { 
            // Col Start => 0x1  /*codegen.py:63*/
            .opcode = GB_OPCODE_POP, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x1 /*codegen.py:66*/

        { 
            // Col Start => 0x2  /*codegen.py:63*/
            .opcode = GB_OPCODE_JP, /*codegen.py:72*/
            .bytes = 3, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_A16, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x2 /*codegen.py:66*/

        { 
            // Col Start => 0x3  /*codegen.py:63*/
            .opcode = GB_OPCODE_JP, /*codegen.py:72*/
            .bytes = 3, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x3 /*codegen.py:66*/

        { 
            // Col Start => 0x4  /*codegen.py:63*/
            .opcode = GB_OPCODE_CALL, /*codegen.py:72*/
            .bytes = 3, /*codegen.py:75*/
            .t_states = 24, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_A16, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x4 /*codegen.py:66*/

        { 
            // Col Start => 0x5  /*codegen.py:63*/
            .opcode = GB_OPCODE_PUSH, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x5 /*codegen.py:66*/

        { 
            // Col Start => 0x6  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADD, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x6 /*codegen.py:66*/

        { 
            // Col Start => 0x7  /*codegen.py:63*/
            .opcode = GB_OPCODE_RST, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x7 /*codegen.py:66*/

        { 
            // Col Start => 0x8  /*codegen.py:63*/
            .opcode = GB_OPCODE_RET, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 20, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x8 /*codegen.py:66*/

        { 
            // Col Start => 0x9  /*codegen.py:63*/
            .opcode = GB_OPCODE_RET, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x9 /*codegen.py:66*/

        { 
            // Col Start => 0xA  /*codegen.py:63*/
            .opcode = GB_OPCODE_JP, /*codegen.py:72*/
            .bytes = 3, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .src = {
                .type = GB_TYPE_A16, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xA /*codegen.py:66*/

        { 
            // Col Start => 0xB  /*codegen.py:63*/
            .opcode = GB_OPCODE_PREFIX, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xB /*codegen.py:66*/

        { 
            // Col Start => 0xC  /*codegen.py:63*/
            .opcode = GB_OPCODE_CALL, /*codegen.py:72*/
            .bytes = 3, /*codegen.py:75*/
            .t_states = 24, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .src = {
                .type = GB_TYPE_A16, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xC /*codegen.py:66*/

        { 
            // Col Start => 0xD  /*codegen.py:63*/
            .opcode = GB_OPCODE_CALL, /*codegen.py:72*/
            .bytes = 3, /*codegen.py:75*/
            .t_states = 24, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xD /*codegen.py:66*/

        { 
            // Col Start => 0xE  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADC, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xE /*codegen.py:66*/

        { 
            // Col Start => 0xF  /*codegen.py:63*/
            .opcode = GB_OPCODE_RST, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xF /*codegen.py:66*/

    }, // Row End => 0xC /*codegen.py:69*/

    // Row Start => 0xD 
    { /*codegen.py:60*/
        { 
            // Col Start => 0x0  /*codegen.py:63*/
            .opcode = GB_OPCODE_RET, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 20, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x0 /*codegen.py:66*/

        { 
            // Col Start => 0x1  /*codegen.py:63*/
            .opcode = GB_OPCODE_POP, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x1 /*codegen.py:66*/

        { 
            // Col Start => 0x2  /*codegen.py:63*/
            .opcode = GB_OPCODE_JP, /*codegen.py:72*/
            .bytes = 3, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_A16, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x2 /*codegen.py:66*/

        { 
            // Col Start => 0x3  /*codegen.py:63*/
            .opcode = GB_OPCODE_ILLEGAL_D3, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x3 /*codegen.py:66*/

        { 
            // Col Start => 0x4  /*codegen.py:63*/
            .opcode = GB_OPCODE_CALL, /*codegen.py:72*/
            .bytes = 3, /*codegen.py:75*/
            .t_states = 24, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_A16, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x4 /*codegen.py:66*/

        { 
            // Col Start => 0x5  /*codegen.py:63*/
            .opcode = GB_OPCODE_PUSH, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x5 /*codegen.py:66*/

        { 
            // Col Start => 0x6  /*codegen.py:63*/
            .opcode = GB_OPCODE_SUB, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x6 /*codegen.py:66*/

        { 
            // Col Start => 0x7  /*codegen.py:63*/
            .opcode = GB_OPCODE_RST, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x7 /*codegen.py:66*/

        { 
            // Col Start => 0x8  /*codegen.py:63*/
            .opcode = GB_OPCODE_RET, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 20, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x8 /*codegen.py:66*/

        { 
            // Col Start => 0x9  /*codegen.py:63*/
            .opcode = GB_OPCODE_RETI, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x9 /*codegen.py:66*/

        { 
            // Col Start => 0xA  /*codegen.py:63*/
            .opcode = GB_OPCODE_JP, /*codegen.py:72*/
            .bytes = 3, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_A16, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xA /*codegen.py:66*/

        { 
            // Col Start => 0xB  /*codegen.py:63*/
            .opcode = GB_OPCODE_ILLEGAL_DB, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xB /*codegen.py:66*/

        { 
            // Col Start => 0xC  /*codegen.py:63*/
            .opcode = GB_OPCODE_CALL, /*codegen.py:72*/
            .bytes = 3, /*codegen.py:75*/
            .t_states = 24, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_A16, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xC /*codegen.py:66*/

        { 
            // Col Start => 0xD  /*codegen.py:63*/
            .opcode = GB_OPCODE_ILLEGAL_DD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xD /*codegen.py:66*/

        { 
            // Col Start => 0xE  /*codegen.py:63*/
            .opcode = GB_OPCODE_SBC, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xE /*codegen.py:66*/

        { 
            // Col Start => 0xF  /*codegen.py:63*/
            .opcode = GB_OPCODE_RST, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xF /*codegen.py:66*/

    }, // Row End => 0xD /*codegen.py:69*/

    // Row Start => 0xE 
    { /*codegen.py:60*/
        { 
            // Col Start => 0x0  /*codegen.py:63*/
            .opcode = GB_OPCODE_LDH, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .type = GB_TYPE_A8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x0 /*codegen.py:66*/

        { 
            // Col Start => 0x1  /*codegen.py:63*/
            .opcode = GB_OPCODE_POP, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x1 /*codegen.py:66*/

        { 
            // Col Start => 0x2  /*codegen.py:63*/
            .opcode = GB_OPCODE_LDH, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x2 /*codegen.py:66*/

        { 
            // Col Start => 0x3  /*codegen.py:63*/
            .opcode = GB_OPCODE_ILLEGAL_E3, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x3 /*codegen.py:66*/

        { 
            // Col Start => 0x4  /*codegen.py:63*/
            .opcode = GB_OPCODE_ILLEGAL_E4, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x4 /*codegen.py:66*/

        { 
            // Col Start => 0x5  /*codegen.py:63*/
            .opcode = GB_OPCODE_PUSH, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x5 /*codegen.py:66*/

        { 
            // Col Start => 0x6  /*codegen.py:63*/
            .opcode = GB_OPCODE_AND, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_SET, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x6 /*codegen.py:66*/

        { 
            // Col Start => 0x7  /*codegen.py:63*/
            .opcode = GB_OPCODE_RST, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x7 /*codegen.py:66*/

        { 
            // Col Start => 0x8  /*codegen.py:63*/
            .opcode = GB_OPCODE_ADD, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_SP}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_E8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_RST, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x8 /*codegen.py:66*/

        { 
            // Col Start => 0x9  /*codegen.py:63*/
            .opcode = GB_OPCODE_JP, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x9 /*codegen.py:66*/

        { 
            // Col Start => 0xA  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 3, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .type = GB_TYPE_A16, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xA /*codegen.py:66*/

        { 
            // Col Start => 0xB  /*codegen.py:63*/
            .opcode = GB_OPCODE_ILLEGAL_EB, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xB /*codegen.py:66*/

        { 
            // Col Start => 0xC  /*codegen.py:63*/
            .opcode = GB_OPCODE_ILLEGAL_EC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xC /*codegen.py:66*/

        { 
            // Col Start => 0xD  /*codegen.py:63*/
            .opcode = GB_OPCODE_ILLEGAL_ED, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xD /*codegen.py:66*/

        { 
            // Col Start => 0xE  /*codegen.py:63*/
            .opcode = GB_OPCODE_XOR, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0xE /*codegen.py:66*/

        { 
            // Col Start => 0xF  /*codegen.py:63*/
            .opcode = GB_OPCODE_RST, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xF /*codegen.py:66*/

    }, // Row End => 0xE /*codegen.py:69*/

    // Row Start => 0xF 
    { /*codegen.py:60*/
        { 
            // Col Start => 0x0  /*codegen.py:63*/
            .opcode = GB_OPCODE_LDH, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_A8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x0 /*codegen.py:66*/

        { 
            // Col Start => 0x1  /*codegen.py:63*/
            .opcode = GB_OPCODE_POP, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_UPT, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x1 /*codegen.py:66*/

        { 
            // Col Start => 0x2  /*codegen.py:63*/
            .opcode = GB_OPCODE_LDH, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_C}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x2 /*codegen.py:66*/

        { 
            // Col Start => 0x3  /*codegen.py:63*/
            .opcode = GB_OPCODE_DI, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x3 /*codegen.py:66*/

        { 
            // Col Start => 0x4  /*codegen.py:63*/
            .opcode = GB_OPCODE_ILLEGAL_F4, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x4 /*codegen.py:66*/

        { 
            // Col Start => 0x5  /*codegen.py:63*/
            .opcode = GB_OPCODE_PUSH, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x5 /*codegen.py:66*/

        { 
            // Col Start => 0x6  /*codegen.py:63*/
            .opcode = GB_OPCODE_OR, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_RST, GB_RST, GB_RST} /*codegen.py:224*/
        }, // Col End => 0x6 /*codegen.py:66*/

        { 
            // Col Start => 0x7  /*codegen.py:63*/
            .opcode = GB_OPCODE_RST, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x7 /*codegen.py:66*/

        { 
            // Col Start => 0x8  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 12, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_SP}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_RST, GB_RST, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0x8 /*codegen.py:66*/

        { 
            // Col Start => 0x9  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_SP}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .gb_regs = {
                    .regs = {GB_REG_H, GB_REG_L}, .regs_count = 2
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0x9 /*codegen.py:66*/

        { 
            // Col Start => 0xA  /*codegen.py:63*/
            .opcode = GB_OPCODE_LD, /*codegen.py:72*/
            .bytes = 3, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMP, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_A16, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xA /*codegen.py:66*/

        { 
            // Col Start => 0xB  /*codegen.py:63*/
            .opcode = GB_OPCODE_EI, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xB /*codegen.py:66*/

        { 
            // Col Start => 0xC  /*codegen.py:63*/
            .opcode = GB_OPCODE_ILLEGAL_FC, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xC /*codegen.py:66*/

        { 
            // Col Start => 0xD  /*codegen.py:63*/
            .opcode = GB_OPCODE_ILLEGAL_FD, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 4, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xD /*codegen.py:66*/

        { 
            // Col Start => 0xE  /*codegen.py:63*/
            .opcode = GB_OPCODE_CP, /*codegen.py:72*/
            .bytes = 2, /*codegen.py:75*/
            .t_states = 8, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .dst = {
                .gb_regs = {
                    .regs = {GB_REG_A}, .regs_count = 1
                }, /*codegen.py:103*/
            }, /*codegen.py:104*/
            .src = {
                .type = GB_TYPE_N8, /*codegen.py:116*/
            }, /*codegen.py:119*/
            .flags = {GB_FLAG_Z, GB_FLAG_N, GB_FLAG_H, GB_FLAG_C}, /*codegen.py:211*/
            .flag_count = 4, /*codegen.py:212*/
            .state = {GB_UPT, GB_SET, GB_UPT, GB_UPT} /*codegen.py:224*/
        }, // Col End => 0xE /*codegen.py:66*/

        { 
            // Col Start => 0xF  /*codegen.py:63*/
            .opcode = GB_OPCODE_RST, /*codegen.py:72*/
            .bytes = 1, /*codegen.py:75*/
            .t_states = 16, /*codegen.py:79*/
            .mode = GB_IMM, /*codegen.py:175*/
            .flags = {0}, /*codegen.py:211*/
            .flag_count = 0, /*codegen.py:212*/
            .state = {GB_DEF, GB_DEF, GB_DEF, GB_DEF} /*codegen.py:224*/
        }, // Col End => 0xF /*codegen.py:66*/

    }, // Row End => 0xF /*codegen.py:69*/

}; /*codegen.py:123*/
