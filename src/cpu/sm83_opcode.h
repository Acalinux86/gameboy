#ifndef SM83_OPCODE_H_
#define SM83_OPCODE_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define OPCODES \
    XOPCODE(NOP    , 0x00)    \
    XOPCODE(LD_BC_N16, 0x01)   \
    XOPCODE(LD_BC_A, 0x02)     \
    XOPCODE(INC_BC , 0x03)     \
    XOPCODE(INC_B  , 0x04)     \
    XOPCODE(DEC_B  , 0x05)     \
    XOPCODE(LD_B_N8, 0x06)     \
    XOPCODE(RLCA,  0x07)       \
    XOPCODE(LD_A16_SP,  0x08)  \
    XOPCODE(ADD_HL_BC, 0x09)   \
    XOPCODE(LD_A_BC, 0x0A)     \
    XOPCODE(DEC_BC, 0x0B)      \
    XOPCODE(INC_C, 0x0C)       \
    XOPCODE(DEC_C, 0x0D)       \
    XOPCODE(LD_C_N8, 0x0E)     \
    XOPCODE(RRCA, 0x0F)        \
    XOPCODE(STOP_N8, 0x10)     \
    XOPCODE(LD_DE_N16, 0x11)   \
    XOPCODE(LD_DE_A, 0x12)     \
    XOPCODE(INC_DE, 0x13)      \
    XOPCODE(INC_D, 0x14)       \
    XOPCODE(DEC_D, 0x15)       \
    XOPCODE(LD_D_N8, 0x16)     \
    XOPCODE(RLA, 0x17)         \
    XOPCODE(JR_E8, 0x18)       \
    XOPCODE(ADD_HL_DE, 0x19)   \
    XOPCODE(LD_A_DE, 0x1A)     \
    XOPCODE(DEC_DE, 0x1B)      \
    XOPCODE(INC_E, 0x1C)       \
    XOPCODE(DEC_E, 0x1D)       \
    XOPCODE(LD_E_N8, 0x1E)     \
    XOPCODE(RRA, 0x1F)         \
    XOPCODE(JR_NZ_E8, 0x20)    \
    XOPCODE(LD_HL_N16, 0x21)   \
    XOPCODE(LD_HLI_A, 0x22)    \
    XOPCODE(INC_HL, 0x23)      \
    XOPCODE(INC_H, 0x24)       \
    XOPCODE(DEC_H, 0x25)       \
    XOPCODE(LD_H_N8, 0x26)     \
    XOPCODE(DAA, 0x27)         \
    XOPCODE(JR_Z_E8, 0x28)     \
    XOPCODE(ADD_HL_HL, 0x29)   \
    XOPCODE(LD_A_HLI, 0x2A)    \
    XOPCODE(DEC_HL, 0x2B)      \
    XOPCODE(INC_L, 0x2C)       \
    XOPCODE(DEC_L, 0x2D)       \
    XOPCODE(LD_L_N8, 0x2E)     \
    XOPCODE(CPL, 0x2F)         \
    XOPCODE(JR_NC_E8, 0x30)    \
    XOPCODE(LD_SP_N16, 0x31)   \
    XOPCODE(LD_HLD_A, 0x32)    \
    XOPCODE(INC_SP, 0x33)      \
    XOPCODE(IND_INC_HL, 0x34)  \
    XOPCODE(IND_DEC_HL, 0x35)  \
    XOPCODE(LD_HL_N8, 0x36)    \
    XOPCODE(SCF, 0x37)         \
    XOPCODE(JR_C_E8, 0x38)     \
    XOPCODE(ADD_HL_SP, 0x39)   \
    XOPCODE(LD_A_HLD, 0x3A)    \
    XOPCODE(DEC_SP, 0x3B)      \
    XOPCODE(INC_A, 0x3C)       \
    XOPCODE(DEC_A, 0x3D)       \
    XOPCODE(LD_A_N8, 0x3E)     \
    XOPCODE(CCF, 0x3F)         \
    XOPCODE(LD_B_B, 0x40)      \
    XOPCODE(LD_B_C, 0x41)      \
    XOPCODE(LD_B_D, 0x42)      \
    XOPCODE(LD_B_E, 0x43)      \
    XOPCODE(LD_B_H, 0x44)      \
    XOPCODE(LD_B_L, 0x45)      \
    XOPCODE(LD_B_HL, 0x46)     \
    XOPCODE(LD_B_A, 0x47)      \
    XOPCODE(LD_C_B, 0x48)      \
    XOPCODE(LD_C_C, 0x49)      \
    XOPCODE(LD_C_D, 0x4A)      \
    XOPCODE(LD_C_E, 0x4B)      \
    XOPCODE(LD_C_H, 0x4C)      \
    XOPCODE(LD_C_L, 0x4D)      \
    XOPCODE(LD_C_HL, 0x4E)     \
    XOPCODE(LD_C_A, 0x4F)      \
    XOPCODE(LD_D_B, 0x50)      \
    XOPCODE(LD_D_C, 0x51)      \
    XOPCODE(LD_D_D, 0x52)      \
    XOPCODE(LD_D_E, 0x53)      \
    XOPCODE(LD_D_H, 0x54)      \
    XOPCODE(LD_D_L, 0x55)      \
    XOPCODE(LD_D_HL, 0x56)     \
    XOPCODE(LD_D_A, 0x57)      \
    XOPCODE(LD_E_B, 0x58)      \
    XOPCODE(LD_E_C, 0x59)      \
    XOPCODE(LD_E_D, 0x5A)      \
    XOPCODE(LD_E_E, 0x5B)      \
    XOPCODE(LD_E_H, 0x5C)      \
    XOPCODE(LD_E_L, 0x5D)      \
    XOPCODE(LD_E_HL, 0x5E)     \
    XOPCODE(LD_E_A, 0x5F)      \
    XOPCODE(LD_H_B, 0x60)      \
    XOPCODE(LD_H_C, 0x61)      \
    XOPCODE(LD_H_D, 0x62)      \
    XOPCODE(LD_H_E, 0x63)      \
    XOPCODE(LD_H_H, 0x64)      \
    XOPCODE(LD_H_L, 0x65)      \
    XOPCODE(LD_H_HL, 0x66)     \
    XOPCODE(LD_H_A, 0x67)      \
    XOPCODE(LD_L_B, 0x68)      \
    XOPCODE(LD_L_C, 0x69)      \
    XOPCODE(LD_L_D, 0x6A)      \
    XOPCODE(LD_L_E, 0x6B)      \
    XOPCODE(LD_L_H, 0x6C)      \
    XOPCODE(LD_L_L, 0x6D)      \
    XOPCODE(LD_L_HL, 0x6E)     \
    XOPCODE(LD_L_A, 0x6F)      \
    XOPCODE(LD_HL_B, 0x70)     \
    XOPCODE(LD_HL_C, 0x71)     \
    XOPCODE(LD_HL_D, 0x72)     \
    XOPCODE(LD_HL_E, 0x73)     \
    XOPCODE(LD_HL_H, 0x74)     \
    XOPCODE(LD_HL_L, 0x75)     \
    XOPCODE(HALT, 0x76)        \
    XOPCODE(LD_HL_A, 0x77)     \
    XOPCODE(LD_A_B, 0x78)      \
    XOPCODE(LD_A_C, 0x79)      \
    XOPCODE(LD_A_D, 0x7A)      \
    XOPCODE(LD_A_E, 0x7B)      \
    XOPCODE(LD_A_H, 0x7C)      \
    XOPCODE(LD_A_L, 0x7D)      \
    XOPCODE(LD_A_HL, 0x7E)     \
    XOPCODE(LD_A_A, 0x7F)      \
    XOPCODE(ADD_A_B, 0x80)     \
    XOPCODE(ADD_A_C, 0x81)     \
    XOPCODE(ADD_A_D, 0x82)     \
    XOPCODE(ADD_A_E, 0x83)     \
    XOPCODE(ADD_A_H, 0x84)     \
    XOPCODE(ADD_A_L, 0x85)     \
    XOPCODE(ADD_A_HL, 0x86)    \
    XOPCODE(ADD_A_A, 0x87)     \
    XOPCODE(ADC_A_B, 0x88)     \
    XOPCODE(ADC_A_C, 0x89)     \
    XOPCODE(ADC_A_D, 0x8A)     \
    XOPCODE(ADC_A_E, 0x8B)     \
    XOPCODE(ADC_A_H, 0x8C)     \
    XOPCODE(ADC_A_L, 0x8D)     \
    XOPCODE(ADC_A_HL, 0x8E)    \
    XOPCODE(ADC_A_A, 0x8F)     \
    XOPCODE(SUB_A_B, 0x90)     \
    XOPCODE(SUB_A_C, 0x91)     \
    XOPCODE(SUB_A_D, 0x92)     \
    XOPCODE(SUB_A_E, 0x93)     \
    XOPCODE(SUB_A_H, 0x94)     \
    XOPCODE(SUB_A_L, 0x95)     \
    XOPCODE(SUB_A_HL, 0x96)    \
    XOPCODE(SUB_A_A, 0x97)     \
    XOPCODE(SBC_A_B, 0x98)     \
    XOPCODE(SBC_A_C, 0x99)     \
    XOPCODE(SBC_A_D, 0x9A)     \
    XOPCODE(SBC_A_E, 0x9B)     \
    XOPCODE(SBC_A_H, 0x9C)     \
    XOPCODE(SBC_A_L, 0x9D)     \
    XOPCODE(SBC_A_HL, 0x9E)    \
    XOPCODE(SBC_A_A, 0x9F)     \
    XOPCODE(AND_A_B, 0xA0)     \
    XOPCODE(AND_A_C, 0xA1)     \
    XOPCODE(AND_A_D, 0xA2)     \
    XOPCODE(AND_A_E, 0xA3)     \
    XOPCODE(AND_A_H, 0xA4)     \
    XOPCODE(AND_A_L, 0xA5)     \
    XOPCODE(AND_A_HL, 0xA6)    \
    XOPCODE(AND_A_A, 0xA7)     \
    XOPCODE(XOR_A_B, 0xA8)     \
    XOPCODE(XOR_A_C, 0xA9)     \
    XOPCODE(XOR_A_D, 0xAA)     \
    XOPCODE(XOR_A_E, 0xAB)     \
    XOPCODE(XOR_A_H, 0xAC)     \
    XOPCODE(XOR_A_L, 0xAD)     \
    XOPCODE(XOR_A_HL, 0xAE)    \
    XOPCODE(XOR_A_A, 0xAF)     \
    XOPCODE(OR_A_B, 0xB0)      \
    XOPCODE(OR_A_C, 0xB1)      \
    XOPCODE(OR_A_D, 0xB2)      \
    XOPCODE(OR_A_E, 0xB3)      \
    XOPCODE(OR_A_H, 0xB4)      \
    XOPCODE(OR_A_L, 0xB5)      \
    XOPCODE(OR_A_HL, 0xB6)     \
    XOPCODE(OR_A_A, 0xB7)      \
    XOPCODE(CP_A_B, 0xB8)      \
    XOPCODE(CP_A_C, 0xB9)      \
    XOPCODE(CP_A_D, 0xBA)      \
    XOPCODE(CP_A_E, 0xBB)      \
    XOPCODE(CP_A_H, 0xBC)      \
    XOPCODE(CP_A_L, 0xBD)      \
    XOPCODE(CP_A_HL, 0xBE)     \
    XOPCODE(CP_A_A, 0xBF)      \
    XOPCODE(RET_NZ, 0xC0)      \
    XOPCODE(POP_BC, 0xC1)      \
    XOPCODE(JP_NZ_A16, 0xC2)   \
    XOPCODE(JP_A16, 0xC3)      \
    XOPCODE(CALL_NZ_A16, 0xC4) \
    XOPCODE(PUSH_BC, 0xC5)     \
    XOPCODE(ADD_A_N8, 0xC6)    \
    XOPCODE(RST_00, 0xC7)      \
    XOPCODE(RET_Z, 0xC8)       \
    XOPCODE(RET, 0xC9)         \
    XOPCODE(JP_Z_A16, 0xCA)    \
    XOPCODE(PREFIX, 0xCB)      \
    XOPCODE(CALL_Z_A16, 0xCC)  \
    XOPCODE(CALL_A16, 0xCD)    \
    XOPCODE(ADC_A_N8, 0xCE)    \
    XOPCODE(RST_08, 0xCF)      \
    XOPCODE(RET_NC, 0xD0)      \
    XOPCODE(POP_DE, 0xD1)      \
    XOPCODE(JP_NC_A16, 0xD2)   \
    XOPCODE(ILLEGAL_D3, 0xD3)  \
    XOPCODE(CALL_NC_A16, 0xD4) \
    XOPCODE(PUSH_DE, 0xD5)     \
    XOPCODE(SUB_A_N8, 0xD6)    \
    XOPCODE(RST_10, 0xD7)      \
    XOPCODE(RET_C, 0xD8)       \
    XOPCODE(RETI, 0xD9)        \
    XOPCODE(JP_C_A16, 0xDA)    \
    XOPCODE(ILEGAL_DB, 0xDB)   \
    XOPCODE(CALL_C_A16, 0xDC)  \
    XOPCODE(ILEGALL_DD, 0xDD)  \
    XOPCODE(SBC_A_N8, 0xDE)    \
    XOPCODE(RST_18, 0xDF)      \
    XOPCODE(LDH_A8_A, 0xE0)    \
    XOPCODE(POP_HL, 0xE1)      \
    XOPCODE(LDH_C_A, 0xE2)     \
    XOPCODE(ILLEGAL_E3, 0xE3)  \
    XOPCODE(ILLEGAL_E4, 0xE4)  \
    XOPCODE(PUSH_HL, 0xE5)     \
    XOPCODE(AND_A_N8, 0xE6)    \
    XOPCODE(RST_20, 0xE7)      \
    XOPCODE(ADD_SP_E8, 0xE8)   \
    XOPCODE(JP_HL, 0xE9)       \
    XOPCODE(LD_A16_A, 0xEA)    \
    XOPCODE(ILEGAL_EB, 0xEB)   \
    XOPCODE(ILLEGAL_EC, 0xEC)  \
    XOPCODE(ILEGALL_ED, 0xED)  \
    XOPCODE(XOR_A_N8, 0xEE)    \
    XOPCODE(RST_28, 0xEF)      \
    XOPCODE(LDH_A_A8, 0xF0)    \
    XOPCODE(POP_AF, 0xF1)      \
    XOPCODE(LDH_A_C, 0xF2)     \
    XOPCODE(DI, 0xF3)  \
    XOPCODE(ILLEGAL_F4, 0xF4)  \
    XOPCODE(PUSH_AF, 0xF5)     \
    XOPCODE(OR_A_N8, 0xF6)    \
    XOPCODE(RST_30, 0xF7)      \
    XOPCODE(LD_HL_SPE8, 0xF8)   \
    XOPCODE(LD_SP_HL, 0xF9)       \
    XOPCODE(LD_A_A16, 0xFA)    \
    XOPCODE(EI, 0xFB)   \
    XOPCODE(ILLEGAL_FC, 0xFC)  \
    XOPCODE(ILEGALL_FD, 0xFD)  \
    XOPCODE(CP_A_N8, 0xFE)    \
    XOPCODE(RST_38, 0xFF)      \

enum SM83OP
{
    #define XOPCODE(opcode, val) OP_##opcode = val,
    OPCODES
    #undef XOPCODE
};

static inline const char *sm83_opcode_as_cstr(enum SM83OP op)
{
    switch (op)
    {
    #define XOPCODE(opcode, val) case OP_##opcode: return #opcode;
    OPCODES
    #undef XOPCODE
    default: return "UNKNOWN OPCODE";
    }
}

static inline uint8_t sm83_map_opcode_to_u8(enum SM83OP op)
{
    switch (op)
    {
    #define XOPCODE(opcode, val) case OP_##opcode: return val;
    OPCODES
    #undef XOPCODE
    default:
        fprintf(stderr, "ERROR: Unreachable Opcode\n");
        abort();
    }
}

/* CB Prefixed Opcodes */
#define CB_PREFIXED_OPCODES\
    XOPCODE(RLC_B, 0x00)\
    XOPCODE(RLC_C, 0x01)\
    XOPCODE(RLC_D, 0x02)\
    XOPCODE(RLC_E, 0x03)\
    XOPCODE(RLC_H, 0x04)\
    XOPCODE(RLC_L, 0x05)\
    XOPCODE(RLC_HL, 0x06)\
    XOPCODE(RLC_A, 0x07)\
    XOPCODE(RRC_B, 0x08)\
    XOPCODE(RRC_C, 0x09)\
    XOPCODE(RRC_D, 0x0A)\
    XOPCODE(RRC_E, 0x0B)\
    XOPCODE(RRC_H, 0x0C)\
    XOPCODE(RRC_L, 0x0D)\
    XOPCODE(RRC_HL, 0x0E)\
    XOPCODE(RRC_A, 0x0F)\
    XOPCODE(RL_B, 0x10)\
    XOPCODE(RL_C, 0x11)\
    XOPCODE(RL_D, 0x12)\
    XOPCODE(RL_E, 0x13)\
    XOPCODE(RL_H, 0x14)\
    XOPCODE(RL_L, 0x15)\
    XOPCODE(RL_HL, 0x16)\
    XOPCODE(RL_A, 0x17)\
    XOPCODE(RR_B, 0x18)\
    XOPCODE(RR_C, 0x19)\
    XOPCODE(RR_D, 0x1A)\
    XOPCODE(RR_E, 0x1B)\
    XOPCODE(RR_H, 0x1C)\
    XOPCODE(RR_L, 0x1D)\
    XOPCODE(RR_HL, 0x1E)\
    XOPCODE(RR_A, 0x1F)\
    XOPCODE(SLA_B, 0x20)\
    XOPCODE(SLA_C, 0x21)\
    XOPCODE(SLA_D, 0x22)\
    XOPCODE(SLA_E, 0x23)\
    XOPCODE(SLA_H, 0x24)\
    XOPCODE(SLA_L, 0x25)\
    XOPCODE(SLA_HL, 0x26)\
    XOPCODE(SLA_A, 0x27)\
    XOPCODE(SRA_B, 0x28)\
    XOPCODE(SRA_C, 0x29)\
    XOPCODE(SRA_D, 0x2A)\
    XOPCODE(SRA_E, 0x2B)\
    XOPCODE(SRA_H, 0x2C)\
    XOPCODE(SRA_L, 0x2D)\
    XOPCODE(SRA_HL, 0x2E)\
    XOPCODE(SRA_A, 0x2F)\
    XOPCODE(SWAP_B, 0x30)\
    XOPCODE(SWAP_C, 0x31)\
    XOPCODE(SWAP_D, 0x32)\
    XOPCODE(SWAP_E, 0x33)\
    XOPCODE(SWAP_H, 0x34)\
    XOPCODE(SWAP_L, 0x35)\
    XOPCODE(SWAP_HL, 0x36)\
    XOPCODE(SWAP_A, 0x37)\
    XOPCODE(SRL_B, 0x38)\
    XOPCODE(SRL_C, 0x39)\
    XOPCODE(SRL_D, 0x3A)\
    XOPCODE(SRL_E, 0x3B)\
    XOPCODE(SRL_H, 0x3C)\
    XOPCODE(SRL_L, 0x3D)\
    XOPCODE(SRL_HL, 0x3E)\
    XOPCODE(SRL_A, 0x3F)\

enum SM83CBPREFIX
{
    #define XOPCODE(opcode, val) OP_##opcode = val,
    CB_PREFIXED_OPCODES
    #undef XOPCODE
};

#endif /* SM83_OPCODE_H_*/
