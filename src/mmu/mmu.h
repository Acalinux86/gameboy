#ifndef GB_MEMORY_MAP_SECTION_H_
#define GB_MEMORY_MAP_SECTION_H_

#include <stdbool.h>
#include <stdint.h>

#define GB_ROM_SIZE  (32 * 1024) /* Rom size*/
#define GB_VRAM_SIZE (8  * 1024) /* Video Ram size */
#define GB_ERAM_SIZE (8  * 1024) /* External Ram size */
#define GB_WRAM_SIZE (8  * 1024) /* Work Ram size */
#define GB_IO_SIZE   (128)       /* IO size */
#define GB_HRAM_SIZE (128)       /* High Ram size */
#define GB_ORAM_SIZE (160)       /* Object Attribute Memory size */

#define GB_MAX_U16 ((1 << 16) - 1)
#define GB_MAX_U8 ((1 << 8) - 1)

#define GB_ILLEGAL_ADDR (1 << 31)
#define GB_ROM_START    0x0000
#define GB_ROM_END      0x8000
#define GB_VRAM_START   0x8000
#define GB_VRAM_END     0x9FFF
#define GB_ERAM_START   0xA000
#define GB_ERAM_END     0xBFFF
#define GB_WRAM_START   0xC000
#define GB_WRAM_END     0xDFFF
#define GB_ECHO_START   0xE000
#define GB_ECHO_END     0xFDFF
#define GB_ORAM_START   0xFE00
#define GB_ORAM_END     0xFE9F
#define GB_IO_START     0xFF00
#define GB_IO_END       0xFF7F
#define GB_HRAM_START   0xFF80
#define GB_HRAM_END     0xFFFE

struct Memory {
    uint8_t *data;
    int start, end, capacity;
    bool write, read;
};

typedef struct Memory GbROM;  /* Read-Only Memory     */
typedef struct Memory GbERAM; /* External RAM         */
typedef struct Memory GbWRAM; /* Work Ram             */
typedef struct Memory GbVRAM; /* Video Ram            */
typedef struct Memory GbIO;   /* Input/Output         */
typedef struct Memory GbORAM; /* Object Attribute Map */
typedef struct Memory GbHRAM; /* High RAM             */

typedef enum GbMemoryMapUnitSection {
    GB_ILLEGAL_SECTION,
    GB_ROM_SECTION,
    GB_VRAM_SECTION,
    GB_ERAM_SECTION,
    GB_WRAM_SECTION,
    GB_ECHO_SECTION,
    GB_ORAM_SECTION,
    GB_IO_SECTION,
    GB_HRAM_SECTION,
} GbMemoryMapUnitSection;

const char *gb_mmu_section_string(const GbMemoryMapUnitSection section);

#define GB_ADDRESS_SPACES_COUNT 9

typedef struct GbMemoryMapUnit {
    GbROM  *rom;
    GbIO   *io;
    GbVRAM *vram;
    GbORAM *oram;
    GbHRAM *hram;
    GbERAM *eram;
    GbWRAM *wram;
} GbMemoryMapUnit;

typedef struct GbMemoryMapUnit GbMemoryMap;

bool gb_mmu_write(GbMemoryMap *mmu, const int location, const uint8_t value);
uint8_t  gb_mmu_read (GbMemoryMap *mmu, const int location);

GbMemoryMap *gb_mmu_init(void);
bool gb_mmu_destroy(GbMemoryMap *mmu);

void gb_mmu_set_read_access (struct Memory *mem, bool enable);
void gb_mmu_set_write_access(struct Memory *mem, bool enable);
#endif // GB_MEMORY_MAP_SECTION_H_
