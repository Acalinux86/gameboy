#ifndef SM83_OPCODE_H_
#define SM83_OPCODE_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define OPCODES              \
    XOPCODE(NOP    , 0x00)   \
    XOPCODE(LD_BC_N16, 0x01) \
    XOPCODE(LD_BC_A, 0x02)   \
    XOPCODE(INC_BC , 0x03)   \
    XOPCODE(INC_B  , 0x04)   \
    XOPCODE(DEC_B  , 0x05)   \
    XOPCODE(LD_B_N8, 0x06)   \
    XOPCODE(RLCA,  0x07)   \
    XOPCODE(LD_A16_SP,  0x08)   \
    XOPCODE(ADD_HL_BC, 0x09)\
    XOPCODE(LD_A_BC, 0x0A)\
    XOPCODE(DEC_BC, 0x0B)\
    XOPCODE(INC_C, 0x0C)\
    XOPCODE(DEC_C, 0x0D)\
    XOPCODE(LD_C_N8, 0x0E)\
    XOPCODE(RRCA, 0x0F)\
    XOPCODE(STOP_N8, 0x10)\
    XOPCODE(LD_DE_N16, 0x11)\
    XOPCODE(LD_DE_A, 0x12)\
    XOPCODE(INC_DE, 0x13)\
    XOPCODE(INC_D, 0x14)\
    XOPCODE(DEC_D, 0x15)\
    XOPCODE(LD_D_N8, 0x16)\
    XOPCODE(RLA, 0x17)\
    XOPCODE(JR_E8, 0x18)\
    XOPCODE(ADD_HL_DE, 0x19)\
    XOPCODE(LD_A_DE, 0x1A)\
    XOPCODE(DEC_DE, 0x1B)\
    XOPCODE(INC_E, 0x1C)\
    XOPCODE(DEC_E, 0x1D)\
    XOPCODE(LD_E_N8, 0x1E)\
    XOPCODE(RRA, 0x1F)\
    XOPCODE(LD_L_D, 0x69)

enum SM83OP
{
#define XOPCODE(opcode, val) OP_##opcode = val,
    OPCODES
#undef XOPCODE
};

static inline const char *sm83_opcode_as_cstr(enum SM83OP op)
{
    switch (op) {
#define XOPCODE(opcode, val) case OP_##opcode: return #opcode;
        OPCODES
#undef XOPCODE
    default:
        return "UNKNOWN OPCODE";
    }
}

static inline uint8_t sm83_map_opcode_to_u8(enum SM83OP op)
{
    switch (op) {
#define XOPCODE(opcode, val) case OP_##opcode: return val;
        OPCODES
#undef XOPCODE
    default:
        fprintf(stderr, "ERROR: Unreachable Opcode\n");
        abort();
    }
}

#endif /* SM83_OPCODE_H_*/
