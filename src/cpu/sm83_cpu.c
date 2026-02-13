#include "sm83_cpu.h"

#include <stdarg.h>

#define MAX_TMP_BUF_SIZE 256
char tmp_buf[MAX_TMP_BUF_SIZE];

static inline void tmp_sprintf(const char *fmt, ...)
{
    memset(tmp_buf, 0, sizeof(tmp_buf));

    va_list args;
    va_start(args, fmt);
    vsprintf(tmp_buf, fmt, args);
    va_end(args);
}

static inline char *sm83_strdup(char *src)
{
    /* Calculate The Length of the String */
    size_t length = strlen(src);

    /*
      Malloc Size of Src string + 1 for null termination
     */
    char *dst = (char *)malloc(sizeof(*dst) * (length + 1));
    if (dst == NULL)
    {
        fprintf(stderr, "Failed to Allocate Memory For String Duplication: `%s`\n", src);
        return NULL;
    }

    /* Copy the Source String into Destination String */
    strncpy(dst, src, length);

    /* Null Terminate the String */
    dst[length] = '\0';

    /* Return Destination String */
    return dst;
}

/* Function that Appends a string to disassembly buffer */
static inline int sm83_disasm_append(struct Disasm *disasm, char *buffer)
{
    if (disasm == NULL || buffer == NULL) return -1;

    if (disasm->disasm_size >= disasm->disasm_cap)
    {
        disasm->disasm_cap = disasm->disasm_cap == 0 ? SM83_DISASM_CAP : disasm->disasm_cap * 2 ;
        disasm->disasm_items = realloc(disasm->disasm_items, sizeof(*disasm->disasm_items) * disasm->disasm_cap);
        if (disasm->disasm_items == NULL)
        {
            fprintf(stderr, "ERROR: Memory Reallocation foe disasm->disasm_items failed\n");
            return -1;
        }
    }

    disasm->disasm_items[disasm->disasm_size++] = sm83_strdup(buffer);
    return 0;
}

/* Joining of 8-bit Integers */
static inline uint16_t sm83_join_eight_bits(uint8_t hi, uint8_t lo)
{
    return (uint16_t) ((hi << 8) | lo);
}

/* Function to Copy Data into Registers */
static inline void sm83_copy_to_bc(struct SM83CPU *cpu, uint8_t B, uint8_t C)
{
    cpu->registers.b = B;
    cpu->registers.c = C;
}

/*Modifies the CPU, fetches 8-bit Data */
static inline uint8_t sm83_fetch8(struct SM83CPU *cpu)
{
    return gb_mmu_read(cpu->mmu, cpu->registers.pc++);
}

/* Modifies the CPU, fetches 16 bit data */
static inline uint16_t sm83_fetch16(struct SM83CPU *cpu)
{
    uint8_t hi = gb_mmu_read(cpu->mmu, cpu->registers.pc++);
    uint8_t lo = gb_mmu_read(cpu->mmu, cpu->registers.pc++);
    return (hi << 8) | lo;
}

/* Modifies The CPU, Writes Back 8 bit data */
static inline int sm83_write8(struct SM83CPU *cpu, const uint8_t data, const uint16_t addr)
{
    if (cpu == NULL) return -1;
    int ret = gb_mmu_write(cpu->mmu, addr, data);
    if (ret != 0) return -1;
    return 0;
}

/* Initializer the sm83 cpu members */
int sm83_cpu_init(struct SM83CPU *cpu, uint16_t pc)
{
    /* Initialize the Program Counter */
    cpu->registers.pc = pc;

    /* Emit Disassembly Flag is False By default */
    cpu->emit_disasm = 0;

    /* If Emit Disassembly is True Allocate Memory */
    if (cpu->emit_disasm)
    {
        cpu->disasm.disasm_size  = 0;
        cpu->disasm.disasm_cap   = SM83_DISASM_CAP;
        cpu->disasm.disasm_items = (char **)malloc(sizeof(*cpu->disasm.disasm_items)*cpu->disasm.disasm_cap);
        if (cpu->disasm.disasm_items)
        {
            fprintf(stderr, "Failed to Allocate Memory For Disasm Buffer\n");
            return -1;
        }
    } else {
        /* Dont Allocate anything and Zero Initialize the Disasm Members */
        cpu->disasm.disasm_size   = 0;
        cpu->disasm.disasm_cap    = 0;
        cpu->disasm.disasm_items = NULL;
    }

    /* Initialize the Memory Management Unit */
    cpu->mmu = gb_mmu_init();
    if (cpu->mmu == NULL)
    {
        fprintf(stderr, "Failed To Initialize the Memory Management Unit\n");
        return -1;
    }

    return 0;
}

/* Shutdown the CPU and free the allocated members */
void sm83_cpu_shutdown(struct SM83CPU *cpu)
{
    /*
      Free Allocated Memory For the Disassembly Buffer
    */
    if (cpu->emit_disasm)
    {
        for (size_t i = 0; i < cpu->disasm.disasm_size; ++i)
        {
            free(cpu->disasm.disasm_items[i]);
        }
        free(cpu->disasm.disasm_items);
    }

    /*
      Destroy The Memory Management Unit
    */
    gb_mmu_destroy(cpu->mmu);
}

/* Helper function to tell the CPU to emit disassembly or not */
void sm83_cpu_emit_disasm(struct SM83CPU *cpu, int emit)
{
    cpu->emit_disasm = emit;
}

/* 8-Bit load instructions */
void sm83_8_bit_load(uint8_t dst, uint8_t src)
{
    (void) dst;
    (void) src;
}

/* 16-Bit load instructions */
void sm83_16_bit_load(uint16_t dst, uint16_t src)
{
    (void) dst;
    (void) src;
}

/* Dump the Disassembly Contents into a file */
void sm83_dump_disasm(const struct Disasm *disasm, FILE *fp)
{
    for (size_t i = 0; i < disasm->disasm_size; ++i)
    {
        fprintf(fp, "%s", disasm->disasm_items[i]);
    }
}

/* Decode the Instructions */
int sm83_decode(struct SM83CPU *cpu)
{
    /* Read the Instruction From the ROM */
    uint8_t instr = sm83_fetch8(cpu);

    /* Emit Status */
    int emit = cpu->emit_disasm;

    /* Temporary Variable to Hold Values Throughout the Function */
    int ret;

    switch (instr) {
    case 0x00:
    {
        /* NOP: DO NOTHING */
        if (emit) ret = sm83_disasm_append(&cpu->disasm, "NOP\n");
        if (ret != 0) return -1;
    } break;

    case 0x01:
    {
        /*
          LD BC, N16
          Copy fetched 16-bit value to Joined Registers BC
        */

        uint8_t C = sm83_fetch8(cpu); // low-order byte
        uint8_t B = sm83_fetch8(cpu); // high-order byte
        sm83_copy_to_bc(cpu, B,  C);

        if (emit)
        {
            uint16_t value = sm83_join_eight_bits(B, C);
            tmp_sprintf("LD BC, 0x%x ; BC = 0x%x\n", value, value);
            ret = sm83_disasm_append(&cpu->disasm, tmp_buf);
            if (ret != 0) return -1;
        }
    } break;

    case 0x02:
    {
        /*
          LD [BC], A
          Copy A into memory address pointed by BC
        */
        uint16_t addr = sm83_join_eight_bits(cpu->registers.b, cpu->registers.c);
        ret = sm83_write8(cpu, cpu->registers.b, addr);
        if (ret != 0) return -1;

        if (emit)
        {
            tmp_sprintf("LD [BC], A ; Copy Accumulator into Memory Pointed by BC\n");
            ret = sm83_disasm_append(&cpu->disasm, tmp_buf);
            if (ret != 0) return -1;
        }
    } break;

    case 0x03:
    {
        /*
          INC BC
          increment register BC
        */
        uint16_t BC = sm83_join_eight_bits(cpu->registers.b, cpu->registers.c);
        BC++;

        cpu->registers.b = BC >> 8;
        cpu->registers.c = BC & 0XFF;
        if (emit)
        {
            tmp_sprintf("INC BC ; Increment the Joined BC Registers\n");
            ret = sm83_disasm_append(&cpu->disasm, tmp_buf);
            if (ret != 0) return -1;
        }
    } break;

    case 0x04:
    {
        /*
          INC B
          Update the Flags
        */
        uint8_t orig = cpu->registers.b;
        cpu->registers.b++;
        uint8_t res = cpu->registers.b;

        /* Set Z (Bit 7) if result == 0*/
        if (res == 0)
        {
            cpu->registers.f |= (1u << 7);
        }

        /* Clear N (Bit 6)*/
        cpu->registers.f &= ~(1u << 6);

        /* Set if Overflow From Bit 3 */
        if ((orig & 0xF) & 0x0F)
        {
            /* Set it */
            cpu->registers.f |= (1u << 5);
        }
        else
        {
            /* clear it */
            cpu->registers.f &= ~(1u << 5);
        }

        if (emit)
        {
            tmp_sprintf("INC B ; Increment B and Update Flags\n");
            ret = sm83_disasm_append(&cpu->disasm, tmp_buf);
            if (ret != 0) return -1;
        }
    } break;

    default:
        fprintf(stderr, "ERROR: `0x%x` Intruction Not Handled Yet\n", instr);
        return -1;
    }
    return 0;
}
