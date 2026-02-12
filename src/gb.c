#include "mmu.h"
#include "sm83_cpu.h"
#include "common.c"

int main(void)
{
    struct SM83CPU cpu = {0};
    int ret = sm83_cpu_init(&cpu, 0xC000);
    if (ret != 0) return 1;

    /* Emit Disassembly */
    sm83_cpu_emit_disasm(&cpu, 1);

    size_t size = 0;
    const char *file_path = "tests/roms/test.gb";
    unsigned char *buffer = read_file(file_path, &size);

    for (int i = 0; i < (int)size; ++i) {
        if (!gb_mmu_write(cpu.mmu, cpu.registers.pc + i, buffer[i])) {
            free(buffer);
            return 1;
        }
    }

    while (1) {
        sm83_decode(&cpu);
        if (cpu.registers.pc >= 0xC000 + size) break;
    }

    FILE *fp = stdout;
    sm83_dump_disasm(&cpu.disasm, fp);

    free(buffer);
    sm83_cpu_shutdown(&cpu);
    return 0;
}
