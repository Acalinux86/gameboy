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
#define GB_HRAM_SIZE (128)       /* High Ram size */
#define GB_ORAM_SIZE (160)       /* Object Attribute Memory size */

#define GB_MAX_U16 ((1 << 16) - 1)

#define GB_ILLEGAL_ADDR 1 << 31
#define GB_ROM_START    0x0000
#define GB_ROM_END      0x8000
#define GB_VRAM_START   0x8000
#define GB_VRAM_END     0xA000
#define GB_SRAM_START   0xA000
#define GB_SRAM_END     0xC000
#define GB_IRAM_START   0xE000
#define GB_IRAM_END     0xFE00
#define GB_ORAM_START   0xFE00
#define GB_ORAM_END     0xFE9F
#define GB_IO_START     0xFF00
#define GB_IO_END       0xF800
#define GB_HRAM_START   0xFF80
#define GB_HRAM_END     0xFFFE

struct Memory {
    int *data;
    int count;
    int capacity;
    int start;
    int end;
};

typedef struct Memory GbROM; // Read Only Memory
typedef struct Memory GbSRAM; // Switchable RAM
typedef struct Memory GbIRAM; // Internal Ram
typedef struct Memory GbVRAM; // Video Ram
typedef struct Memory GbIO;  // Input/Output
typedef struct Memory GbORAM; // Object Attribute Map
typedef struct Memory GbHRAM; // High RAM

typedef enum GbMemoryMapUnitSection {
    GB_ILLEGAL_SECTION,
    GB_ROM_SECTION,
    GB_VRAM_SECTION,
    GB_SRAM_SECTION,
    GB_IRAM_SECTION,
    GB_ORAM_SECTION,
    GB_IO_SECTION,
    GB_HRAM_SECTION,
} GbMemoryMapUnitSection;

#define GB_ADDRESS_SPACES_COUNT 8

typedef struct GbMemoryMapUnit {
    GbROM  *rom;
    GbIO   *io;
    GbVRAM *vram;
    GbORAM *oram;
    GbHRAM *hram;
    GbSRAM *sram;
    GbIRAM *iram;
} GbMemoryMapUnit;

typedef struct MemoryMap {
    GbMemoryMapUnitSection section;
    GbMemoryMapUnit *unit;
} GbMemoryMap;

const char *gb_mmu_section_string(GbMemoryMapUnitSection section);

void gb_mmu_init(GbMemoryMap *mmu);
bool gb_mmu_destroy(GbMemoryMap *mmu);
bool gb_mmu_write(GbMemoryMap *mmu, int location, int value);
int gb_mmu_read(GbMemoryMap *mmu, int location);

#endif // GB_MEMORY_MAP_SECTION_H_
