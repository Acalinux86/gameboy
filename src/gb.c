#include "mmu.h"
#include "sm83_cpu.h"
#include "common.c"

#define INITIALIZE_PROGRAM_COUNTER 0x0000

int main(void)
{
    /* Initialize the Cpu */
    struct SM83CPU cpu = {0};
    int ret = sm83_cpu_init(&cpu, INITIALIZE_PROGRAM_COUNTER);
    if (ret != 0) return 1;

    /* Emit Disassembly */
    sm83_cpu_emit_disasm(&cpu, 1);

    /* Read the Rom File into memory */
    size_t size = 0;
    const char *file_path = "data/roms/test.gb";
    unsigned char *buffer = read_file(file_path, &size);

    /* Write the Rom file into the Gameboy ROM */
    for (int i = 0; i < (int)size; ++i)
    {
        if (gb_mmu_write(cpu.mmu, cpu.registers.pc + i, buffer[i]) != 0)
        {
            /* Free Buffer if write fails */
            fprintf(stderr, "ERROR: Write Failed\n");
            free(buffer);
            return 1;
        }
    }

    /* 
        After Loading the Rom to the MMU->ROM, 
        disable write Access to the ROM 
    */
    gb_mmu_disable_write_access_to_rom(cpu.mmu);

    /* Fetch => Decode => Execute Loop Cycle */
    while (1)
    {
        if (sm83_decode(&cpu) != 0)
        {
            fprintf(stderr, "ERROR: Decode ERROR\n");
            break;
        }
        // if (cpu.registers.pc >= INITIALIZE_PROGRAM_COUNTER + size) break;
    }

    /* File to Be Dump Rom Assembly*/
    const char *asm_file = "data/disasm/tetris.asm";

    /* Open File For writing */
    FILE *fp = fopen(asm_file, "wb");
    if (fp == NULL)
    {
        fprintf(stderr, "ERROR: Fail to Open File: %s\n", asm_file);
        return 1;
    }

    /* Dump the Disassembly */
    sm83_dump_disasm(&cpu.disasm, fp);

    /* Close the File Pointer */
    fclose(fp);

    /* Free the Allocated Rom Buffer */
    free(buffer);

    /* Shutdown the CPU */
    sm83_cpu_shutdown(&cpu);
    return 0;
}
