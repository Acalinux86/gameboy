#ifndef SM83_CPU_H_
#define SM83_CPU_H_

#include "disasm/disasm.h"
#include "sm83_opcode.h"
#include "mmu.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct SM83Registers
{
    /*
      8-bit accumulator
      and the flag registers
    */
    uint8_t a, f;

    /* regular 8-bit registers */
    uint8_t b, c;
    uint8_t d, e;
    uint8_t h, l;

    /* 16-bit program counter */
    uint16_t pc;

    /* 16-bit stack pointer */
    uint16_t sp;
};

enum SM83REGS
{
    REG_A,
    REG_F,
    REG_B,
    REG_C,
    REG_D,
    REG_E,
    REG_H,
    REG_L,
    REG_SP,
    REG_PC,
};

struct SM83CPU
{
    /* Disassembly Buffer */
    struct Disasm disasm;
    /*
      if true, emit disassembly, else dont
      0 => dont emit => false
      1 => emit => true
     */
    int emit_disasm;

    /* Flag to Signal the CPU to Stop until Interrupt */
    int stopped;

    /* Registers */
    struct SM83Registers registers;

    /* Memory Management Unit */
    struct MMU *mmu;
};

/* Return Types For CPU Functions */
enum SM83Error {
    SM83_OK = 0,
    SM83_ERR_MEMORY = -1,
    SM83_ERR_INVALID_OPCODE = -2,
    SM83_ERR_MMU = -3,
    SM83_ERR_NULL_CPU = -4,
    SM83_ERR_DISASM = -5,
};

/* Initializer the sm83 cpu members */
enum SM83Error sm83_cpu_init(struct SM83CPU *cpu, FILE *fp, uint16_t pc);

/* Shutdown the CPU and free the allocated members */
enum SM83Error sm83_cpu_shutdown(struct SM83CPU *cpu);

/* Decode the Instructions */
enum SM83Error sm83_decode(struct SM83CPU *cpu);

/* Write back a byte to Memory */
enum SM83Error sm83_write8(struct SM83CPU *cpu, const uint8_t data, const uint16_t addr);

/* Read a byte from Memory */
uint8_t sm83_read(const struct SM83CPU *cpu, const uint16_t addr);

/* SM83 Error Types As Strings */
const char *sm83_error_string(enum SM83Error error);

/* Helper function to tell the CPU to emit disassembly or not */
void sm83_cpu_emit_disasm(struct SM83CPU *cpu, int emit);

#endif /* SM83_CPU_H_*/
