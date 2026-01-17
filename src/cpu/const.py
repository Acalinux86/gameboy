REGISTER_PREFIX  = "GB_REG"
LOAD_TYPE_PREFIX = "GB_TYPE"
FLAG_BIT_PREFIX  = "GB_FLAG"
OPCODE_PREFIX    = "GB_OPCODE"
OPCODE_LUT_ROWS  = 16
OPCODE_LUT_COLS  = 16
OPCODE_LUT_NAME  = "GbOpcodeLookupTable"
ROWS_NAME        = "GB_OP_LUT_ROWS"
COLS_NAME        = "GB_OP_LUT_COLS"

REGISTER_LIST = [
    "B", "C",
    "D", "E",
    "A", "F",
    "H", "L",
    "PC", "SP"
]

LOAD_TYPES = [
    "a8", "a16",
    "n8", "n16",
    "e8"
]

UNPREFIXED_STATUS = "unprefixed"
CBPREFIXED_STATUS = "cbprefixed"
