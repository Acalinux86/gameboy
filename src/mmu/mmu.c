#include "./mmu.h"

static inline struct Memory *gb__mmu_alloc_memory(int capacity)
{
    struct Memory *mem = (struct Memory *)calloc(1, sizeof(*mem));
    if (mem == NULL) {
        gb_error("Memory Allocation Failed For Struct");
        return NULL;
    }

    mem->data = (int*)calloc(capacity, sizeof(*mem->data));
    if (mem->data == NULL) {
        gb_error("Memory Allocation Failed For Data");
        return NULL;
    }

    mem->capacity = capacity;
    mem->count = 0;

    return mem;
}

static inline bool gb__mmu_dealloc_memory(struct Memory *mem)
{
    if (!mem) return false;
    if (mem->data != NULL) {
        free(mem->data);
    }

    mem->data = NULL;
    mem->capacity = 0;
    mem->count = 0;
    free(mem);
    return true;
}

#define GB_CHECK_MEMORY_CAPACITY(mem) \
    if ((mem)->count >= (mem)->capacity) {\
        gb_abort("Capacity Reached Used: %d, Capacity: %d", \
                 (mem)->count, (mem)->capacity);\
    }

static inline bool gb__mmu_append(struct Memory *mem, int value)
{
    if (!mem) return false;
    if (value < 0) {
        gb_error("Value less than Zero => Value %d", value);
        return false;
    }

    if (value > GB_MAX_U16) {
        gb_error("Value Exceeded 16 bit Max => Value %d", value);
        return false;
    }

    GB_CHECK_MEMORY_CAPACITY(mem);
    mem->data[mem->count++] = value;
    return true;
}

static inline GbMemoryMapUnit *gb__mmu_alloc(void)
{
    GbMemoryMapUnit *unit = (GbMemoryMapUnit*)malloc(sizeof(*unit));
    if (unit == NULL) {
        gb_error("Memory Allocation Failed For Struct");
        return NULL;
    }
    return unit;
}

static inline GbRAM *gb__mmu_ram_alloc(void)
{
    GbRAM *ram = (GbRAM*)malloc(sizeof(*ram));
    if (ram == NULL) {
        gb_error("Memory Allocation Failed For Struct");
        return NULL;
    }
    return ram;
}

void gb_mmu_init(GbMemoryMap *mmu)
{
    // Initialize the Memory Management Unit
    mmu->section = GB_ILLEGAL_SECTION;
    mmu->unit = gb__mmu_alloc();
    assert(mmu->unit != NULL);

    mmu->unit->ram = gb__mmu_ram_alloc();
    assert(mmu->unit->ram != NULL);

    mmu->unit->ram->iram = (GbIRAM *) gb__mmu_alloc_memory(GB_IRAM_SIZE);
    assert(mmu->unit->ram->iram != NULL);

    mmu->unit->ram->sram = (GbSRAM *)gb__mmu_alloc_memory(GB_SRAM_SIZE);
    assert(mmu->unit->ram->sram != NULL);

    mmu->unit->io = (GbIO *)gb__mmu_alloc_memory(GB_IO_SIZE);
    assert(mmu->unit->io != NULL);

    mmu->unit->rom = (GbROM *)gb__mmu_alloc_memory(GB_ROM_SIZE);
    assert(mmu->unit->rom != NULL);

    mmu->unit->vram = (GbVRAM *)gb__mmu_alloc_memory(GB_VRAM_SIZE);
    assert(mmu->unit->vram != NULL);
}

bool gb_mmu_write(GbMemoryMapUnit *mmu, GbMemoryMapUnitSection section, int location, int value)
{
    (void) mmu;
    (void) section;
    (void) location;
    (void) value;
    return false;
}

bool gb_mmu_destroy(GbMemoryMap *mmu)
{
    if (!mmu) return false;
    if (!mmu->unit) return false;

    if (!gb__mmu_dealloc_memory(mmu->unit->ram->iram)) return false;
    if (!gb__mmu_dealloc_memory(mmu->unit->ram->sram)) return false;
    if (mmu->unit->ram) free(mmu->unit->ram);

    if (!gb__mmu_dealloc_memory(mmu->unit->io)) return false;
    if (!gb__mmu_dealloc_memory(mmu->unit->rom)) return false;
    if (!gb__mmu_dealloc_memory(mmu->unit->vram)) return false;
    if (mmu->unit) free(mmu->unit);
    return false;
}
