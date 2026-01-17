#!/usr/bin/env python3

import sys
import os
import inspect
import json

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

OPCODES_LIST = set()

UNPREFIXED_STATUS = "unprefixed"
CBPREFIXED_STATUS = "cbprefixed"

class LineNo:
    def __int__(self):
        return inspect.currentframe().f_back.f_back.f_lineno

FILE = os.path.basename(__file__)
LINE = LineNo()

def output_stats():
    return "/*%s:%d*/" % (FILE, int(LINE))

def generate_directive(directive):
    return "\n#include \"%s\"    %s\n\n" % (directive, output_stats())

def generate_comment(comment):
    return "// %s %s" % (comment, output_stats())

def generate_macro(name, value):
    return "#define %s %s %s\n" % (name.upper(), value, output_stats())

def generate_prologue(table_rows, table_cols, table_name):
    return "const GbOpcodeEntry %s[%s][%s] = { %s\n" % (table_name, table_rows, table_cols, output_stats())

def generate_row_prologue(row_number):
    return "    // Row Start => 0x%X \n    { %s\n" % (row_number, output_stats())

def generate_col_prologue(col_number):
    return "%s{ \n%s// Col Start => 0x%X  %s\n" % (' '*8, ' '*12, col_number, output_stats())

def generate_col_epilogue(col_number):
    return "        }, // Col End => 0x%X %s\n\n" % (col_number, output_stats())

def generate_row_epilogue(row_number):
    return "    }, // Row End => 0x%X %s\n\n" % (row_number, output_stats())

def generate_opcode(opcode):
    return "%s.opcode = %s_%s, %s\n" % (" "*12, OPCODE_PREFIX, opcode, output_stats())

def generate_bytes(_bytes):
    buf = "%s.bytes = %s, %s\n" % (' '*12, _bytes, output_stats())
    return buf

def generate_cycles(cycles):
    buf = "%s.t_states = %s, %s\n" % (' '*12, cycles[0], output_stats())
    return buf

def generate_operand_from_regs(operands, operand_type):
    spaces = 12
    tab = 4
    buf = "%s.%s = {\n" % (' '*(spaces), operand_type)
    buf += "%s.gb_regs = {\n" % (' '*(spaces+tab))
    buf += "%s.regs = {" % (' '*(spaces+tab+tab))
    length = len(operands)
    if length > 0:
        for i in range(0, length):
            if operands[i] in REGISTER_LIST:
                if i + 1 == length:
                    buf += "%s_%s" % (REGISTER_PREFIX, operands[i])
                else:
                    buf += "%s_%s, " % (REGISTER_PREFIX, operands[i])
            else:
                pass # Do Nothing
    else:
        buf += "0"
    buf += "}, "
    buf += ".regs_count = %d\n" % (len(operands))
    buf += "%s}, %s\n" % (' '*(spaces+tab), output_stats())
    buf += "%s}, %s\n" % (' '*(spaces), output_stats())
    return buf

def generate_operand_from_loads(operands, operand_type):
    spaces = 12
    tab = 4
    buf = "%s.%s = {\n" % (' '*(spaces), operand_type)
    buf += "%s.type = " % (" "*(spaces+tab))
    if operands:
        if operands[0] in LOAD_TYPES:
            buf += "%s_%s, %s\n" % (LOAD_TYPE_PREFIX,
                                    "".join((x.upper() for x in operands[0] if not isinstance(x, int))),
                                    output_stats())
    else:
        pass
    buf += "%s}, %s\n" % (' '*(spaces), output_stats())
    return buf

def generate_epilogue():
    return "};  %s %s\n" % (generate_comment("%s ends here" % (OPCODE_LUT_NAME)), output_stats())

# Status here is prefixed or unprefixed
def extract_opcode_from_dict(dictionary, index, status):
    opcode = dictionary[status][index]["mnemonic"]
    return opcode

def extract_bytes_from_dict(dictionary, index, status):
    _bytes = dictionary[status][index]["bytes"]
    return _bytes

def extract_cycles_from_dict(dictionary, index, status):
    cycles = dictionary[status][index]["cycles"]
    return cycles

def extract_operand_from_dict_with_list_index(dictionary, index, list_index, status):
    operands = dictionary[status][index]["operands"]
    if operands:
        if len(operands) > 1:
            return operands[list_index]
        else:
            return []
    else:
        return []

def is_numeric(num):
    try:
        float(num)
        return True
    except ValueError:
        return False

def parse_operand(operand):
    loads_list = []
    regs_list = []
    num_list = []
    if operand:
        for key, value in operand.items():
            if key == "name":
                if value in LOAD_TYPES:
                    loads_list.append(value)
                elif value in REGISTER_LIST:
                    regs_list.append(value)
                elif is_numeric(value):
                    num_list.append(value)
                else:
                    if len(value) > 1:
                        for i in list(value):
                            regs_list.append(i)
            elif key == "bytes":
                pass # Do Nothing
            elif key == "immediate":
                pass # Do Nothing
    return regs_list, loads_list

def extract_addr_mode_from_dict(dictionary, index, status):
    mode = dictionary[status][index]["immediate"]
    return mode

def generate_addr_mode(mode):
    string = "IMM" if mode == True else "IMP"
    buf = "%s.mode = GB_%s, %s\n" % (' '*12, string, output_stats())
    return buf

def extract_flags_from_dict(dictionary, index, status):
    _flags = dictionary[status][index]["flags"]
    return _flags

def parse_flags_states(flags):
    state_list = []
    flags_list = []
    for key, value in flags.items():
        if value == '-':
            state_list.append("def")
        elif value == '1':
            state_list.append("set")
            flags_list.append(key)
        elif value == '0':
            state_list.append("rst")
            flags_list.append(key)
        else:
            state_list.append("upt")
            flags_list.append(key)
    return state_list, flags_list

def generate_flags(bits):
    spaces = 12
    buf = "%s.flags = {" % (' '*(spaces))
    length = len(bits)
    if length > 0:
        for i in range(0, length):
            if i + 1 == length:
                buf += "%s_%s" % (FLAG_BIT_PREFIX, bits[i])
            else:
                buf += "%s_%s, " % (FLAG_BIT_PREFIX, bits[i])
    else:
        buf += "0"
    buf += "}, %s\n" % (output_stats())
    buf += "%s.flag_count = %d, %s\n" % (' '*(spaces), length, output_stats())
    return buf

def generate_states(states):
    spaces = 12
    buf = "%s.state = {" % (' '*(spaces))
    length = len(states)
    for i in range(0, length):
        if i + 1 == length:
            buf += "GB_%s" % (states[i].upper())
        else:
            buf += "GB_%s, " % (states[i].upper())
    buf += "} %s\n" % (output_stats())
    return buf


def construct_index(row, col):
    return "0x%X%X" % (row, col)

def generate_opcodes_header_file_prologue(filename):
    fname = "".join(filename.split('.h'))
    buf =  "#ifndef GB_%s_H_ %s\n" % (fname.upper(), output_stats())
    buf += "#define GB_%s_H_ %s\n\n" % (fname.upper(), output_stats())
    return buf

def generate_opcodes_header_file_body(opcodes):
    buf = "#define GB_OPCODES %s\\" % output_stats()
    buf += "\n"
    length = len(opcodes)
    for i in range(0, length):
        if i + 1 == length:
            buf += "    GB_OPCODE(%s) %s\n\n" % (opcodes[i], output_stats())
        else:
            buf += "    GB_OPCODE(%s) %s\\" % (opcodes[i], output_stats())
            buf += "\n"
    return buf

def generate_opcodes_header_file_epilogue(filename):
    fname = "".join(filename.split('.h'))
    buf =  "#endif // GB_%s_H_ %s\n" % (fname.upper(), output_stats())
    return buf

def generate_opcodes_x_macros(fpo):
    comment = "This file is generated automatically. DO NOT MODIFY THIS FILE!!! %s" % output_stats()
    fpo.write(generate_comment(comment + "\n"))
    fpo.write(generate_opcodes_header_file_prologue("opcodes.h"))
    fpo.write(generate_opcodes_header_file_body(list(OPCODES_LIST)))
    fpo.write(generate_opcodes_header_file_epilogue("opcodes.h"))

def generate_and_write_operand(fpw, dictionary, index, status, list_index):
    operands = extract_operand_from_dict_with_list_index(dictionary, index, list_index, status)
    regs, loads = parse_operand(operands)
    operand_type = ""

    if list_index == 0:
        operand_type = "dst"
    elif list_index == 1:
        operand_type = "src"
    else:
        assert 0 ,"unreachable"

    if len(regs) > 0:
        fpw.write(generate_operand_from_regs(regs, operand_type))

    if len(loads) > 0:
        fpw.write(generate_operand_from_loads(loads, operand_type))

def main():
    fullpath = os.path.abspath(__file__)
    dirpath = os.path.dirname(fullpath)
    opjson_path = os.path.basename("Opcodes.json")
    read_file = os.path.join(dirpath, opjson_path)
    if not os.path.lexists(read_file):
        print("Path Does Not Exist")
        return 1
    print(read_file)

    write_file = os.path.join(dirpath, "opcode_tables.c")
    fpr = open(read_file, "r")
    loaded_json = json.load(fpr)
    fpr.close()

    fpw = open(write_file, "w")
    comment = "This file is generated automatically. DO NOT MODIFY THIS FILE!!!"
    fpw.write(generate_comment(comment))
    fpw.write(generate_directive("cpu.h"))
    fpw.write(generate_prologue(ROWS_NAME, COLS_NAME, OPCODE_LUT_NAME))
    for i in range(0, OPCODE_LUT_ROWS):
        fpw.write(generate_row_prologue(i))
        for j in range(0, OPCODE_LUT_COLS):
            fpw.write(generate_col_prologue(j))

            index = construct_index(i, j)

            opcode = extract_opcode_from_dict(loaded_json, index, UNPREFIXED_STATUS)
            OPCODES_LIST.add(opcode)
            fpw.write(generate_opcode(opcode))

            _bytes = extract_bytes_from_dict(loaded_json, index, UNPREFIXED_STATUS)
            fpw.write(generate_bytes(str(_bytes)))

            cycles = extract_cycles_from_dict(loaded_json, index, UNPREFIXED_STATUS);
            fpw.write(generate_cycles(cycles))

            mode = extract_addr_mode_from_dict(loaded_json, index, UNPREFIXED_STATUS)
            fpw.write(generate_addr_mode(mode))

            generate_and_write_operand(fpw, loaded_json, index, UNPREFIXED_STATUS, 0)
            generate_and_write_operand(fpw, loaded_json, index, UNPREFIXED_STATUS, 1)

            flags = extract_flags_from_dict(loaded_json, index, UNPREFIXED_STATUS)
            states, bits = parse_flags_states(flags)
            fpw.write(generate_flags(bits))
            fpw.write(generate_states(states))

            fpw.write(generate_col_epilogue(j))
        fpw.write(generate_row_epilogue(i))
    fpw.write(generate_epilogue())
    print("generated %s." % (write_file))
    fpw.close()

    opcode_macro = os.path.join(dirpath, "opcodes.h")
    fpo = open(opcode_macro, "w")
    generate_opcodes_x_macros(fpo)
    fpo.close()
    print("generated %s." % (opcode_macro))
    return 0

if __name__ == "__main__":
    os._exit(main())
