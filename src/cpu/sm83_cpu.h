#ifndef SM83_CPU_H_
#define SM83_CPU_H_

#include "sm83_opcode.h"
#include "mmu.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define SM83_DISASM_CAP 128

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

struct Disasm
{
    /*
     * char **disasm is a dynamic buffer of buffers,
     Contains the disassembly of the Rom.

     * Allocated when init sm83_cpu_init,
     Freed when sm83_cpu_shutdown is called,

      * size_t disasm_size is the size of the disasm.
      * size_t disasm_cap is the capacity of the disasm buffer.
      * disasm is dynamically reallocated if size reaches capacity,
      and capacity is increased.
    */
    char **disasm_items;
    size_t disasm_size;
    size_t disasm_cap;
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

    /* Registers */
    struct SM83Registers registers;

    /* Memory Management Unit */
    GbMemoryMap *mmu;
};

/* Initializer the sm83 cpu members */
int sm83_cpu_init(struct SM83CPU *cpu, uint16_t pc);

/* Shutdown the CPU and free the allocated members */
void sm83_cpu_shutdown(struct SM83CPU *cpu);

/* 8-Bit load instructions */
void sm83_8_bit_load(uint8_t dst, uint8_t src);

/* 16-Bit load instructions */
void sm83_16_bit_load(uint16_t dst, uint16_t src);

/* Decode the Instructions */
int sm83_decode(struct SM83CPU *cpu);

/* Dump the Disassembly Contents into a file */
void sm83_dump_disasm(const struct Disasm *disasm, FILE *fp);

/* Helper function to tell the CPU to emit disassembly or not */
void sm83_cpu_emit_disasm(struct SM83CPU *cpu, int emit);

#endif /* SM83_CPU_H_*/
