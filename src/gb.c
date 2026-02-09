#include "log.h"
#include "mmu.h"
#include "cpu.h"
#include "common.c"

int main(void)
{
    const char *gb_dir = "./src";
    const char *log_file_path = "gameboy.log";
    gb_log_init(gb_dir, log_file_path, GB_LOG_INFO);
    gb_log_set_timestamp(false);
    gb_log_set_stats(false);

    GbCpuState state = gb_cpu_init_states(0xC000);
    size_t size = 0;
    const char *file_path = "tests/roms/test.gb";
    unsigned char *buffer = read_file(file_path, &size);
    for (int i = 0; i < (int)size; ++i) {
        if (!gb_mmu_write(state.mmu, state.regs.PC + i, buffer[i])) {
            free(buffer);
            return 1;
        }
        printf("0X%X\n", buffer[i]);
    }
    while (1) {
        gb_cpu_decode(&state);
        if (state.regs.PC >= 0xC000 + size) break;
    }

    gb_log_shutdown();
    free(buffer);
    gb_cpu_shutdown(&state);
    return 0;
}
