#include <stdio.h>

#include "./log/log.h"
#include "./mmu/mmu.h"

int main(void)
{
    GbMemoryMap mmu = {0};
    gb_info("Initializing Memory");
    gb_mmu_init(&mmu);
    gb_mmu_destroy(&mmu);
    gb_info("Memory Destroyed");
    return 0;
}
