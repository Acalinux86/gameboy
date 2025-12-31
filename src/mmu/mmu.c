#include "./mmu.h"

const char *gb_mmu_section_string(GbMemoryMapUnitSection section)
{
    switch (section) {
    case GB_ILLEGAL_SECTION: return "illegal section";
    case GB_ROM_SECTION:     return "Rom";
    case GB_VRAM_SECTION:    return "Video Ram";
    case GB_SRAM_SECTION:    return "Switchable Ram";
    case GB_IRAM_SECTION:    return "Internal(Work) Ram";
    case GB_ORAM_SECTION:    return "Object Attribute Memory";
    case GB_IO_SECTION:      return "Input/Output";
    case GB_HRAM_SECTION:    return "High Ram";
    default:
        gb_abort("Unreachable Section");
    }
}

static inline struct Memory *gb__mmu_alloc_memory(int capacity, int start, int end)
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
    mem->start = start;
    mem->end = end;
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

    mem = NULL;
    return true;
}

#define GB_CHECK_MEMORY_CAPACITY(mem) \
    if ((mem)->count >= (mem)->capacity) {\
        gb_abort("Capacity Reached Used: %d, Capacity: %d", \
                 (mem)->count, (mem)->capacity);\
    }

static bool gb__mmu_write_memory(struct Memory *mem, int loc, int value)
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
    // Gives you an index with the allocated memory
    int index = loc - mem->start;
    assert(index <= mem->capacity);
    gb_info("Writing to Virtual Location: %d", index);

    mem->data[index] = value;
    mem->count++;
    return true;
}

static int gb__mmu_read_memory(struct Memory *mem, int loc)
{
    int index = loc - mem->start;
    assert(index <= mem->capacity);
    gb_info("Reading from Virtual Location: %d", index);
    return mem->data[index];
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

#define GB_REGISTER_UNIT(mem)    \
    mem = gb__mmu_alloc(); \
    assert(mem != NULL);

#define GB_REGISTER_MEMORY(mem, cap, start, end) \
    mem = gb__mmu_alloc_memory(cap, start, end); \
    assert(mem != NULL); \

GbMemoryMapUnitSection gb__mmu_get_section(GbMemoryMap *mmu)
{
    return mmu->section;
}

void gb__mmu_set_section(GbMemoryMap *mmu, GbMemoryMapUnitSection section)
{
    mmu->section = section;
}

void gb_mmu_init(GbMemoryMap *mmu)
{
    // Initialize the Memory Management Unit
    mmu->section = GB_ILLEGAL_SECTION;
    GB_REGISTER_UNIT(mmu->unit);
    GB_REGISTER_MEMORY(mmu->unit->sram, GB_SRAM_SIZE, GB_SRAM_START, GB_SRAM_END);
    GB_REGISTER_MEMORY(mmu->unit->iram, GB_IRAM_SIZE, GB_IRAM_START, GB_IRAM_END);
    GB_REGISTER_MEMORY(mmu->unit->vram, GB_VRAM_SIZE, GB_VRAM_START, GB_VRAM_END);
    GB_REGISTER_MEMORY(mmu->unit->hram, GB_HRAM_SIZE, GB_HRAM_START, GB_HRAM_END);
    GB_REGISTER_MEMORY(mmu->unit->oram, GB_ORAM_SIZE, GB_ORAM_START, GB_ORAM_END);
    GB_REGISTER_MEMORY(mmu->unit->rom, GB_ROM_SIZE, GB_ROM_START, GB_ROM_END);
    GB_REGISTER_MEMORY(mmu->unit->io, GB_IO_SIZE, GB_IO_START, GB_IO_END);
}

static inline bool gb__mmu_validate_location(int start, int end, int location)
{
    return location >= start && location < end;
}

const int GbAddressSpace[GB_ADDRESS_SPACES_COUNT][2] = {
    [GB_ILLEGAL_SECTION] = {GB_ILLEGAL_ADDR, GB_ILLEGAL_ADDR},
    [GB_ROM_SECTION]     = {GB_ROM_START   , GB_ROM_END},
    [GB_IO_SECTION]      = {GB_IO_START    , GB_IO_END},
    [GB_VRAM_SECTION]    = {GB_VRAM_START  , GB_VRAM_END},
    [GB_IRAM_SECTION]    = {GB_IRAM_START  , GB_IRAM_END},
    [GB_SRAM_SECTION]    = {GB_SRAM_START  , GB_SRAM_END},
    [GB_ORAM_SECTION]    = {GB_ORAM_START  , GB_ORAM_END},
    [GB_HRAM_SECTION]    = {GB_HRAM_START  , GB_HRAM_END},
};

static inline GbMemoryMapUnitSection gb__mmu_match_location_to_section(int loc)
{
    int start, end;
    gb_info("location => %d", loc);
    GbMemoryMapUnitSection section = GB_ILLEGAL_SECTION;
    for (int i = 0; i < GB_ADDRESS_SPACES_COUNT; ++i) {
        start = GbAddressSpace[i][0];
        end = GbAddressSpace[i][1];
        if (gb__mmu_validate_location(start, end, loc)) {
            section = i;
            break;
        }
    }
    gb_info("section => %d", section);
    return section;
}

bool gb_mmu_write(GbMemoryMap *mmu, int location, int value)
{
    GbMemoryMapUnitSection section = gb__mmu_match_location_to_section(location);
    gb__mmu_set_section(mmu, section);

    switch (mmu->section) {
    case GB_ROM_SECTION: {
        gb_error("Write To ROM Section Forbidden");
        return false;
    } break;

    case GB_IRAM_SECTION: {
        gb__mmu_write_memory(mmu->unit->iram, location, value);
        return true;
    } break;

    case GB_SRAM_SECTION: {
        gb__mmu_write_memory(mmu->unit->sram, location, value);
        return true;
    } break;

    case GB_IO_SECTION: {
        gb__mmu_write_memory(mmu->unit->io, location, value);
        return true;
    } break;

    case GB_VRAM_SECTION: {
        gb__mmu_write_memory(mmu->unit->vram, location, value);
        return true;
    } break;

    case GB_ORAM_SECTION: {
        gb__mmu_write_memory(mmu->unit->oram, location, value);
        return true;
    }

    case GB_HRAM_SECTION: {
        gb__mmu_write_memory(mmu->unit->hram, location, value);
        return true;
    } break;

    case GB_ILLEGAL_SECTION:
    default:
        gb_abort("Writing to Unreachable Section");
    }
    return false;
}

int gb_mmu_read(GbMemoryMap *mmu, int location)
{
    GbMemoryMapUnitSection section = gb__mmu_match_location_to_section(location);
    gb__mmu_set_section(mmu, section);

    switch (section) {
    case GB_ROM_SECTION: {
        return gb__mmu_read_memory(mmu->unit->rom, location);
    }

    case GB_VRAM_SECTION: {
        return gb__mmu_read_memory(mmu->unit->vram, location);
    }

    case GB_SRAM_SECTION: {
        return gb__mmu_read_memory(mmu->unit->sram, location);
    }

    case GB_IRAM_SECTION: {
        return gb__mmu_read_memory(mmu->unit->iram, location);
    }

    case GB_ORAM_SECTION: {
        return gb__mmu_read_memory(mmu->unit->oram, location);
    }

    case GB_IO_SECTION: {
        return gb__mmu_read_memory(mmu->unit->io, location);
    }

    case GB_HRAM_SECTION: {
        return gb__mmu_read_memory(mmu->unit->hram, location);
    }

    case GB_ILLEGAL_SECTION:
    default: {
        gb_abort("Reading From Unreachable Section")
    }
    }
}

bool gb_mmu_destroy(GbMemoryMap *mmu)
{
    if (!mmu) return false;
    if (!mmu->unit) return false;

    if (!gb__mmu_dealloc_memory(mmu->unit->rom))  return false;
    if (!gb__mmu_dealloc_memory(mmu->unit->vram)) return false;
    if (!gb__mmu_dealloc_memory(mmu->unit->sram)) return false;
    if (!gb__mmu_dealloc_memory(mmu->unit->iram)) return false;
    if (!gb__mmu_dealloc_memory(mmu->unit->io))   return false;
    if (!gb__mmu_dealloc_memory(mmu->unit->oram)) return false;
    if (!gb__mmu_dealloc_memory(mmu->unit->hram)) return false;
    if (mmu->unit) free(mmu->unit);
    mmu->unit = NULL;
    return false;
}

// TODO: Trace MMU logs
