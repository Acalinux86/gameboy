#include "./log/log.h"
#include "./mmu/mmu.h"

int main(void)
{
    const char *gb_dir = "./src";
    const char *log_file_path = "gameboy.log";
    gb_log_init(gb_dir, log_file_path, GB_LOG_INFO);

    for (int i = 0; i < Logger.files->count; ++i) {
        GB_INFO("%s", gb__log_get_src_file(Logger.files, i));
    }

    GbMemoryMap mmu = {0};
    GB_INFO("Initializing Memory");

    gb_mmu_init(&mmu);
    GB_INFO("Memory initialized");

    const int location = 0xA100;
    const int count = 1;
    for (int i = 0; i < count; ++i) {
        const int data = i + 1;
        if (!gb_mmu_write(&mmu, location + i, data)) {
            GB_ABORT("Could Not Write to Location: %d", location + i);
            return 1;
        }
        GB_INFO("Successfully wrote => %d to %d", data, location + i);
    }

    for (int i = 0; i < count; ++i) {
        const int data = gb_mmu_read(&mmu, location + i);
        GB_INFO("Successfully Read => %d from %d", data, location + i);
    }

    gb_mmu_destroy(&mmu);
    GB_INFO("Memory Destroyed");
    gb_log_shutdown();
    return 0;
}
