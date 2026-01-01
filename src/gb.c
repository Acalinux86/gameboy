#include "./log/log.h"
#include "./mmu/mmu.h"

int main(void)
{
    const char *gb_dir = "./src";
    const char *log_file_path = NULL;
    gb_log_init(gb_dir, log_file_path, GB_LOG_DEBUG);
    GbMemoryMap mmu = {0};
    GB_INFO("Initializing Memory");
    gb_mmu_init(&mmu);
    GB_INFO("Initialized Memory");
    const int location = 0xA100;
    if (!gb_mmu_write(&mmu, location, 69)) {
        GB_ABORT("Could Not Write to Location: %d", location);
        return 1;
    }
    GB_INFO("Successfully wrote to %d", location);

    const int data = gb_mmu_read(&mmu, location);
    GB_INFO("Successfully Read => %d from %d", data, location);
    gb_mmu_destroy(&mmu);
    GB_INFO("Memory Destroyed");
    gb_log_shutdown();
    return 0;
}
