#include <stdio.h>

#include "./log/log.h"
#include "./mmu/mmu.h"

int main(void)
{
    GbMemoryMap mmu = {0};
    gb_info("Initializing Memory");
    gb_mmu_init(&mmu);
    gb_info("Initialized Memory");
    int location = 0xA100;
    if (!gb_mmu_write(&mmu, location, 69)) {
        gb_error("Could Not Write to Location: %d", location);
        return 1;
    }
    gb_info("Successfully wrote to %d", location);

    int data = gb_mmu_read(&mmu, location);
    gb_info("Successfully Read => %d from %d", data, location);
    gb_mmu_destroy(&mmu);
    gb_info("Memory Destroyed");
    return 0;
}
