#ifndef GB_MEMORY_MAP_SECTION_H_
#define GB_MEMORY_MAP_SECTION_H_

#include "../log/log.h"

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define GB_ROM_SIZE  (32 * 1024) /* Rom size*/
#define GB_VRAM_SIZE (8  * 1024) /* Video Ram size */
#define GB_SRAM_SIZE (8  * 1024) /* Switchable Ram size */
#define GB_IRAM_SIZE (8  * 1024) /* Internal Ram size */
#define GB_IO_SIZE   (128)       /* IO size */

#define GB_MAX_U16 ((1 << 16) - 1)

struct Memory {
    int *data;
    int count;
    int capacity;
};

typedef struct Memory GbROM;

typedef struct Memory GbSRAM;
typedef struct Memory GbIRAM;
typedef struct Memory GbVRAM;
typedef struct Memory GbIO;

typedef struct GbRAM {
    GbSRAM *sram;
    GbIRAM *iram;
} GbRAM;

typedef enum GbMemoryMapUnitSection {
    GB_ILLEGAL_SECTION,
    GB_ROM_SECTION,
    GB_RAM_SECTION,
    GB_IO_SECTION,
    GB_VRAM_SECTION,
} GbMemoryMapUnitSection;

typedef struct GbMemoryMapUnit {
    GbROM  *rom;
    GbRAM  *ram;
    GbIO   *io;
    GbVRAM *vram;
} GbMemoryMapUnit;

typedef struct MemoryMap {
    GbMemoryMapUnitSection section;
    GbMemoryMapUnit *unit;
} GbMemoryMap;

void gb_mmu_init(GbMemoryMap *mmu);
bool gb_mmu_destroy(GbMemoryMap *mmu);

#endif // GB_MEMORY_MAP_SECTION_H_
