#include "./mmu.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

const int DEBUG = 0;

const char *gb_mmu_section_string(const GbMemoryMapUnitSection section)
{
    switch (section) {
    case GB_ILLEGAL_SECTION: return "illegal section";
    case GB_ROM_SECTION:     return "Rom";
    case GB_VRAM_SECTION:    return "Video Ram";
    case GB_ERAM_SECTION:    return "External Ram";
    case GB_WRAM_SECTION:    return "Work Ram";
    case GB_ECHO_SECTION:    return "Echo of Work Ram";
    case GB_ORAM_SECTION:    return "Object Attribute Memory";
    case GB_IO_SECTION:      return "Input/Output";
    case GB_HRAM_SECTION:    return "High Ram";
    default:
        fprintf(stderr, "ERROR: Unreachable Section\n");
        abort();
    }
    fprintf(stderr, "ERROR: Unreachable `gb_mmu_section_string` Code\n");
    abort();
}

static inline struct Memory *gb_mmu__alloc_memory(const int capacity, const int start, const int end)
{
    struct Memory *mem = (struct Memory *)calloc(1, sizeof(*mem));
    if (mem == NULL) {
        fprintf(stderr, "ERROR: Memory Allocation Failed For Struct\n");
        return NULL;
    }

    mem->data = (uint8_t*)calloc(capacity, sizeof(*mem->data));
    if (mem->data == NULL) {
        fprintf(stderr, "ERROR: Memory Allocation Failed For Data\n");
        return NULL;
    }

    mem->capacity = capacity;
    mem->start = start;
    mem->end = end;
    return mem;
}

static inline bool gb_mmu__dealloc_memory(struct Memory *mem)
{
    if (!mem) return false;
    if (mem->data != NULL) {
        free(mem->data);
    }

    mem->data = NULL;
    free(mem);

    mem = NULL;
    return true;
}

static inline int gb_mmu__get_virtual_location(const int start, const int end, const int loc)
{
    const int virtual_location = loc - start;
    assert(virtual_location >= 0);
    assert(virtual_location < (end - start));
    return virtual_location;
}

static inline bool gb_mmu__write_memory(struct Memory *mem, const int location, const uint8_t value)
{
    if (!mem) return false;

    // Gives you an index within the allocated memory for a section
    const int index = gb_mmu__get_virtual_location(mem->start, mem->end, location);
    if (DEBUG) printf("DEBUG: Writing to Virtual Location: %d\n", index);

    /* Read And Write Are True By Default */
    mem->read = true;
    mem->write = true;

    mem->data[index] = value;
    return true;
}

static uint8_t gb_mmu__read_memory(const struct Memory *mem, const int loc)
{
    const int index = gb_mmu__get_virtual_location(mem->start, mem->end, loc);
    if (DEBUG) printf("DEBUG: Reading from Virtual Location: %d\n", index);
    return mem->data[index];
}

void gb_mmu_set_read_access (struct Memory *mem, bool enable)
{
    mem->read = enable;
}

void gb_mmu_set_write_access(struct Memory *mem, bool enable)
{
    mem->write = enable;
}

void gb_mmu_disable_write_access_to_rom(GbMemoryMap *mmu)
{
    gb_mmu_set_write_access(mmu->rom, false);
}

static inline GbMemoryMap *gb_mmu__alloc(void)
{
    GbMemoryMap *unit = (GbMemoryMap*)malloc(sizeof(*unit));
    if (unit == NULL) {
        fprintf(stderr, "ERROR: Memory Allocation Failed For Struct\n");
        return NULL;
    }
    return unit;
}

#define GB_REGISTER_MEMORY(mem, cap, start, end, read, write) \
    mem = gb_mmu__alloc_memory(cap, start, end); \
    assert(mem != NULL); \
    gb_mmu_set_read_access(mem, read);\
    gb_mmu_set_write_access(mem, write);\

GbMemoryMap *gb_mmu_init(void)
{
    // Initialize the Memory Management Unit
    GbMemoryMap *mmu = (GbMemoryMap*)malloc(sizeof(*mmu));
    if (mmu == NULL) return NULL;

    GB_REGISTER_MEMORY(mmu->eram, GB_ERAM_SIZE, GB_ERAM_START, GB_ERAM_END, true, true);
    GB_REGISTER_MEMORY(mmu->wram, GB_WRAM_SIZE, GB_WRAM_START, GB_WRAM_END, true, true);
    GB_REGISTER_MEMORY(mmu->vram, GB_VRAM_SIZE, GB_VRAM_START, GB_VRAM_END, true, true);
    GB_REGISTER_MEMORY(mmu->hram, GB_HRAM_SIZE, GB_HRAM_START, GB_HRAM_END, true, true);
    GB_REGISTER_MEMORY(mmu->oram, GB_ORAM_SIZE, GB_ORAM_START, GB_ORAM_END, true, true);
    GB_REGISTER_MEMORY(mmu->rom,  GB_ROM_SIZE,  GB_ROM_START,  GB_ROM_END,  true, true);
    GB_REGISTER_MEMORY(mmu->io,   GB_IO_SIZE,   GB_IO_START,   GB_IO_END,   true, true);
    return mmu;
}

static inline bool gb_mmu__validate_location(const int start, const int end, const int location)
{
    return location >= start && location < end;
}

const int GbPhysicalAddressSpace[GB_ADDRESS_SPACES_COUNT][2] = {
    /*[GB_ILLEGAL_SECTION] = */ {GB_ILLEGAL_ADDR, GB_ILLEGAL_ADDR},
    /*[GB_ROM_SECTION]     = */ {GB_ROM_START   , GB_ROM_END},
    /*[GB_IO_SECTION]      = */ {GB_IO_START    , GB_IO_END},
    /*[GB_VRAM_SECTION]    = */ {GB_VRAM_START  , GB_VRAM_END},
    /*[GB_WRAM_SECTION]    = */ {GB_WRAM_START  , GB_WRAM_END},
    /*[GB_ECHO_SECTION]    = */ {GB_ECHO_START  , GB_ECHO_END},
    /*[GB_ERAM_SECTION]    = */ {GB_ERAM_START  , GB_ERAM_END},
    /*[GB_ORAM_SECTION]    = */ {GB_ORAM_START  , GB_ORAM_END},
    /*[GB_HRAM_SECTION]    = */ {GB_HRAM_START  , GB_HRAM_END},
};

static inline GbMemoryMapUnitSection gb_mmu__match_location_to_section(const int loc)
{
    if (DEBUG) printf("DEBUG: location => %d\n", loc);
    GbMemoryMapUnitSection section = GB_ILLEGAL_SECTION;
    for (int i = 0; i < GB_ADDRESS_SPACES_COUNT; ++i) {
        const int start = GbPhysicalAddressSpace[i][0];
        const int end   = GbPhysicalAddressSpace[i][1];
        const bool valid = gb_mmu__validate_location(start, end, loc);
        if (valid) {
            section = (GbMemoryMapUnitSection)i;
            break;
        } else {
            continue;
        }
    }
    if (DEBUG) printf("DEBUG: section => %s\n", gb_mmu_section_string(section));
    return section;
}

#define GB_MMU_WRITE_ON_CHECK(mem, location, value, section)\
    do {\
        if ((mem)->write) {\
            if (!gb_mmu__write_memory(mem, location, value)) return false;\
        } else {\
            fprintf(stderr, "ERROR: Write Access Memory Section \'%s\' Denied.\n", gb_mmu_section_string(section));\
            return false;\
        }\
    } while (0)

int gb_mmu_write(GbMemoryMap *mmu, const int location, const uint8_t value)
{
    const GbMemoryMapUnitSection section = gb_mmu__match_location_to_section(location);

    switch (section) {
    case GB_ROM_SECTION: {
        GB_MMU_WRITE_ON_CHECK(mmu->rom, location, value, section);
        return 0;
    }

    /* Defer Writes from echo ram to work ram*/
    case GB_ECHO_SECTION:
    case GB_WRAM_SECTION: {
        GB_MMU_WRITE_ON_CHECK(mmu->wram, location, value, section);
        return 0;
    }

    case GB_ERAM_SECTION: {
        GB_MMU_WRITE_ON_CHECK(mmu->eram, location, value, section);
        return 0;
    }

    case GB_IO_SECTION: {
        GB_MMU_WRITE_ON_CHECK(mmu->io, location, value, section);
        return 0;
    }

    case GB_VRAM_SECTION: {
        GB_MMU_WRITE_ON_CHECK(mmu->vram, location, value, section);
        return 0;
    }

    case GB_ORAM_SECTION: {
        GB_MMU_WRITE_ON_CHECK(mmu->oram, location, value, section);
        return 0;
    }

    case GB_HRAM_SECTION: {
        GB_MMU_WRITE_ON_CHECK(mmu->hram, location, value, section);
        return 0;
    }

    case GB_ILLEGAL_SECTION:
    default:
        fprintf(stderr, "ERROR: Writing to Unreachable Section: `%s`\n", gb_mmu_section_string(section));
        return -1;
    }
    fprintf(stderr, "ERROR: Unreachable `gb_mmu_write` Code\n");
    return -1;
}

uint8_t gb_mmu_read(GbMemoryMap *mmu, const int location)
{
    const GbMemoryMapUnitSection section = gb_mmu__match_location_to_section(location);
    switch (section) {
    case GB_ROM_SECTION: {
        return gb_mmu__read_memory(mmu->rom, location);
    }

    case GB_VRAM_SECTION: {
        return gb_mmu__read_memory(mmu->vram, location);
    }

    case GB_ERAM_SECTION: {
        return gb_mmu__read_memory(mmu->eram, location);
    }

    /* defer read from echo ram section to work ram */
    case GB_ECHO_SECTION:
    case GB_WRAM_SECTION: {
        return gb_mmu__read_memory(mmu->wram, location);
    }

    case GB_ORAM_SECTION: {
        return gb_mmu__read_memory(mmu->oram, location);
    }

    case GB_IO_SECTION: {
        return gb_mmu__read_memory(mmu->io, location);
    }

    case GB_HRAM_SECTION: {
        return gb_mmu__read_memory(mmu->hram, location);
    }

    case GB_ILLEGAL_SECTION:
    default: {
        fprintf(stderr, "ERROR: Reading From Unreachable Section: `%s`\n", gb_mmu_section_string(section));
        abort();
    }
    }
    fprintf(stderr, "Unreachable `gb_mmu_read` Code\n");
    abort();
}

bool gb_mmu_destroy(GbMemoryMap *mmu) {
    if (!mmu) return false;

    if (!gb_mmu__dealloc_memory(mmu->rom))  return false;
    if (!gb_mmu__dealloc_memory(mmu->vram)) return false;
    if (!gb_mmu__dealloc_memory(mmu->eram)) return false;
    if (!gb_mmu__dealloc_memory(mmu->wram)) return false;
    if (!gb_mmu__dealloc_memory(mmu->io))   return false;
    if (!gb_mmu__dealloc_memory(mmu->oram)) return false;
    if (!gb_mmu__dealloc_memory(mmu->hram)) return false;
    free(mmu);
    mmu = NULL;
    return true;
}
