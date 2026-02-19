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
    XOPCODE(RLCA,  0x07)     \
    XOPCODE(LD_A16_SP,  0x08)\
    XOPCODE(ADD_HL_BC, 0x09) \
    XOPCODE(LD_A_BC, 0x0A)   \
    XOPCODE(DEC_BC, 0x0B)    \
    XOPCODE(INC_C, 0x0C)     \
    XOPCODE(DEC_C, 0x0D)     \
    XOPCODE(LD_C_N8, 0x0E)   \
    XOPCODE(RRCA, 0x0F)      \
    XOPCODE(STOP_N8, 0x10)   \
    XOPCODE(LD_DE_N16, 0x11) \
    XOPCODE(LD_DE_A, 0x12)   \
    XOPCODE(INC_DE, 0x13)    \
    XOPCODE(INC_D, 0x14)     \
    XOPCODE(DEC_D, 0x15)     \
    XOPCODE(LD_D_N8, 0x16)   \
    XOPCODE(RLA, 0x17)       \
    XOPCODE(JR_E8, 0x18)     \
    XOPCODE(ADD_HL_DE, 0x19) \
    XOPCODE(LD_A_DE, 0x1A)   \
    XOPCODE(DEC_DE, 0x1B)    \
    XOPCODE(INC_E, 0x1C)     \
    XOPCODE(DEC_E, 0x1D)     \
    XOPCODE(LD_E_N8, 0x1E)   \
    XOPCODE(RRA, 0x1F)       \
    XOPCODE(JR_NZ_E8, 0x20)  \
    XOPCODE(LD_HL_N16, 0x21) \
    XOPCODE(LD_HLI_A, 0x22)  \
    XOPCODE(INC_HL, 0x23)  \
    XOPCODE(INC_H, 0x24)  \
    XOPCODE(DEC_H, 0x25)  \
    XOPCODE(LD_H_N8, 0x26)  \
    XOPCODE(DAA, 0x27)  \
    XOPCODE(JR_Z_E8, 0x28)  \
    XOPCODE(ADD_HL_HL, 0x29)  \
    XOPCODE(LD_A_HLI, 0x2A)  \
    XOPCODE(DEC_HL, 0x2B)  \
    XOPCODE(INC_L, 0x2C)  \
    XOPCODE(DEC_L, 0x2D)  \
    XOPCODE(LD_L_N8, 0x2E)  \
    XOPCODE(CPL, 0x2F)  \
    XOPCODE(JR_NC_E8, 0x30)  \
    XOPCODE(LD_SP_N16, 0x31) \
    XOPCODE(LD_HLD_A, 0x32)  \
    XOPCODE(INC_SP, 0x33)  \
    XOPCODE(IND_INC_HL, 0x34)  \
    XOPCODE(IND_DEC_HL, 0x35)  \
    XOPCODE(LD_HL_N8, 0x36)  \
    XOPCODE(SCF, 0x37)  \
    XOPCODE(JR_C_E8, 0x38)  \
    XOPCODE(ADD_HL_SP, 0x39)  \
    XOPCODE(LD_A_HLD, 0x3A)  \
    XOPCODE(DEC_SP, 0x3B)  \
    XOPCODE(INC_A, 0x3C)  \
    XOPCODE(DEC_A, 0x3D)  \
    XOPCODE(LD_A_N8, 0x3E)  \
    XOPCODE(CCF, 0x3F)  \
    XOPCODE(LD_B_B, 0x40)  \
    XOPCODE(LD_B_C, 0x41) \
    XOPCODE(LD_B_D, 0x42)  \
    XOPCODE(LD_B_E, 0x43)  \
    XOPCODE(LD_B_H, 0x44)  \
    XOPCODE(LD_B_L, 0x45)  \
    XOPCODE(LD_B_HL, 0x46)  \
    XOPCODE(LD_B_A, 0x47)  \
    XOPCODE(LD_C_B, 0x48)  \
    XOPCODE(LD_C_C, 0x49)  \
    XOPCODE(LD_C_D, 0x4A)  \
    XOPCODE(LD_C_E, 0x4B)  \
    XOPCODE(LD_C_H, 0x4C)  \
    XOPCODE(LD_C_L, 0x4D)  \
    XOPCODE(LD_C_HL, 0x4E)  \
    XOPCODE(LD_C_A, 0x4F)  \
    XOPCODE(LD_D_B, 0x50) \
    XOPCODE(LD_D_C, 0x51) \
    XOPCODE(LD_D_D, 0x52)  \
    XOPCODE(LD_D_E, 0x53)  \
    XOPCODE(LD_D_H, 0x54)  \
    XOPCODE(LD_D_L, 0x55)  \
    XOPCODE(LD_D_HL, 0x56)  \
    XOPCODE(LD_D_A, 0x57)  \
    XOPCODE(LD_E_B, 0x58)  \
    XOPCODE(LD_E_C, 0x59)  \
    XOPCODE(LD_E_D, 0x5A)  \
    XOPCODE(LD_E_E, 0x5B)  \
    XOPCODE(LD_E_H, 0x5C)  \
    XOPCODE(LD_E_L, 0x5D)  \
    XOPCODE(LD_E_HL, 0x5E)  \
    XOPCODE(LD_E_A, 0x5F)  \
    XOPCODE(LD_H_B, 0x60) \
    XOPCODE(LD_H_C, 0x61) \
    XOPCODE(LD_H_D, 0x62)  \
    XOPCODE(LD_H_E, 0x63)  \
    XOPCODE(LD_H_H, 0x64)  \
    XOPCODE(LD_H_L, 0x65)  \
    XOPCODE(LD_H_HL, 0x66)  \
    XOPCODE(LD_H_A, 0x67)  \
    XOPCODE(LD_L_B, 0x68)  \
    XOPCODE(LD_L_C, 0x69)  \
    XOPCODE(LD_L_D, 0x6A)  \
    XOPCODE(LD_L_E, 0x6B)  \
    XOPCODE(LD_L_H, 0x6C)  \
    XOPCODE(LD_L_L, 0x6D)  \
    XOPCODE(LD_L_HL, 0x6E)  \
    XOPCODE(LD_L_A, 0x6F)

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
