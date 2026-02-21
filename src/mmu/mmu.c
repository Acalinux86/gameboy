#include "./mmu.h"

#include <assert.h>

int mmu_init(struct MMU *mmu, FILE *fp)
{
    if (mmu == NULL) return -1;
    if (fp == NULL) return -1;

    /*
      Load BOOT Sequence First 256 bytes
      0x0000 - 0x0100
    */
    size_t boot_bytes = fread(mmu->rom.sequence, sizeof(byte), BOOT_SEQUENCE_SIZE, fp);
    if (boot_bytes != BOOT_SEQUENCE_SIZE) return -1;

    /*
      Load the Cartridge Header, the Next 80 bytes
      0x0100 - 0x014F
    */
    size_t cart_bytes = fread(&mmu->rom.cart, sizeof(byte), sizeof(struct CartridgeHeader), fp);
    if (cart_bytes != CARTRIDGE_HEADER_SIZE) return -1;

    /*
      The Loaded Cartridge Header Should give us an insight to the RAM Available
      in the Cartridge and the banks count
    */
    size_t ram_size = cart_determine_ram_size(&mmu->rom.cart);

    if (ram_size == 0)
    {
        /*
           No Banks Available in Cartridge (No RAM)
           Determine ROM Size and Load The Rest of the ROM
           Null Initialize them
        */
        mmu->rom.banks = NULL;
        mmu->rom.banks_count = 0;

        /* Rewind the FP */
        rewind(fp);

        /* Dynamically Allocate the all the rom bytes Here */
        mmu->rom.rom_size = cart_determine_rom_size(&mmu->rom.cart);
        if (mmu->rom.rom_size <= 0) return -1;

        mmu->rom.rom_bytes = (byte*)malloc(sizeof(byte) * mmu->rom.rom_size);
        if (mmu->rom.rom_bytes == NULL) return -1;

        size_t rom_bytes_read = fread(mmu->rom.rom_bytes, sizeof(*mmu->rom.rom_bytes), mmu->rom.rom_size, fp);
        if (rom_bytes_read != mmu->rom.rom_size) return -1;
    }
    else
    {
        // Handle Bank Access Here
    }

    /* Pass the Game Title To the MMU game title Pointer */
    mmu->game_title = cart_extract_title(&mmu->rom.cart);
    if (mmu->game_title == NULL) return -1;
    return 0;
}

int mmu_destroy(struct MMU *mmu)
{
    /* Return Error if Pointers Are NULL */
    if (mmu == NULL) return -1;
    if (mmu->rom.rom_bytes == NULL) return -1;
    if (mmu->game_title == NULL) return -1;

    /* Free Allocated Memory */
    free(mmu->game_title);
    free(mmu->rom.rom_bytes);
    return 0;
}

#define ADDRESS_SPACES_COUNT 10
const uint16_t PhysicalAddressSpace[ADDRESS_SPACES_COUNT][2] = {
    {ROM_START              , ROM_END              },
    {VIDEO_RAM_START        , VIDEO_RAM_END        },
    {EXTERNAL_RAM_START     , EXTERNAL_RAM_END     },
    {WORK_RAM_START         , WORK_RAM_END         },
    {ECHO_RAM_START         , ECHO_RAM_END         },
    {OBJECT_RAM_START       , OBJECT_RAM_END       },
    {PROHIBITED_SPACE_START , PROHIBITED_SPACE_END },
    {IO_START               , IO_END               },
    {HIGH_RAM_START         , HIGH_RAM_END         },
    {IER_START              , IER_END              }
};

enum MapSection __mmu_map_addr_to_section(const uint16_t addr)
{
    for (uint16_t i = 0; i < ADDRESS_SPACES_COUNT; ++i)
    {
        const uint16_t start = PhysicalAddressSpace[i][0];
        const uint16_t end   = PhysicalAddressSpace[i][1];

        if (addr >= start && addr <= end)
        {
            return (enum MapSection)i;
        }
    }
    return SECTION_ILLEGAL;
}

static inline uint16_t __mmu_calculate_virtual_addr(uint16_t allocated, uint16_t start, uint16_t end, uint16_t physical_addr)
{
    printf("START => 0x%04x | ", start);
    printf("END   => 0x%04x | ", end);
    printf("physical addr => 0x%04x | ", physical_addr);
    assert(physical_addr <= end);
    uint16_t index = physical_addr - start;
    printf("Calculate index => 0x%04x\n", index);
    assert(index < allocated);
    return index;
}

int mmu_write(struct MMU *mmu, uint16_t addr, byte value)
{
    printf("write: => ");
    if (mmu == NULL) return -1;
    enum MapSection section = __mmu_map_addr_to_section(addr);

    switch (section)
    {

    case SECTION_WORK_RAM:
    {
        /* Writes to WRAM */
        uint16_t index = __mmu_calculate_virtual_addr(WRAM_SIZE, WORK_RAM_START, WORK_RAM_END, addr);
        mmu->wram[index] = value;
    } break;

    case SECTION_ECHO_RAM:
    {
        /*
          any Writes to Echo RAM mirrors Work Ram
          They are the same sizes
        */
        uint16_t index = __mmu_calculate_virtual_addr(WRAM_SIZE, ECHO_RAM_START, ECHO_RAM_END, addr);
        mmu->wram[index] = value;
    } break;

    case SECTION_VIDEO_RAM:
    {
        /* Write to Video RAM */
        uint16_t index = __mmu_calculate_virtual_addr(VRAM_SIZE, VIDEO_RAM_START, VIDEO_RAM_END, addr);
        mmu->vram[index] = value;
    } break;

    case SECTION_EXTERNAL_RAM:
    {
        /* Write to External RAM */
        uint16_t index = __mmu_calculate_virtual_addr(EXRAM_SIZE, EXTERNAL_RAM_START, EXTERNAL_RAM_END, addr);
        mmu->exram[index] = value;
    } break;

    case SECTION_OBJECT_RAM:
    {
        /* Write to Object Attribute Memory RAM */
        uint16_t index = __mmu_calculate_virtual_addr(OAM_SIZE, OBJECT_RAM_START, OBJECT_RAM_END, addr);
        mmu->oam[index] = value;
    } break;

    case SECTION_INPUT_OUTPUT:
    {
        /* Write to Input Output Memory RAM */
        uint16_t index = __mmu_calculate_virtual_addr(IO_SIZE, IO_START, IO_END, addr);
        mmu->io[index] = value;
    } break;

    case SECTION_HIGH_RAM:
    {
        /* Write to HIGH RAM */
        uint16_t index = __mmu_calculate_virtual_addr(HRAM_SIZE, HIGH_RAM_START, HIGH_RAM_END, addr);
        mmu->hram[index] = value;
    } break;

    case SECTION_IER:
    {
        /* Write to Interrupt Enable Register */
        mmu->ier = value;
    } break;

    case SECTION_ROM:
    case SECTION_PROHIBITED:
    case SECTION_ILLEGAL:
    default:
        fprintf(stderr, "Write Prohibited\n");
        return -1;
    }

    return 0;
}

byte mmu_read(struct MMU *mmu, uint16_t addr)
{
    printf("read : => ");
    enum MapSection section = __mmu_map_addr_to_section(addr);

    /* Reussable Variable */
    uint16_t virtual_addr;

    switch (section)
    {
    case SECTION_ROM:
    {
        virtual_addr = __mmu_calculate_virtual_addr(mmu->rom.rom_size, ROM_START, ROM_END, addr);
        return mmu->rom.rom_bytes[virtual_addr];
    }

    case SECTION_VIDEO_RAM:
    {
        virtual_addr = __mmu_calculate_virtual_addr(VRAM_SIZE, VIDEO_RAM_START, VIDEO_RAM_END, addr);
        return mmu->vram[virtual_addr];
    }

    case SECTION_EXTERNAL_RAM:
    {
        virtual_addr = __mmu_calculate_virtual_addr(EXRAM_SIZE, EXTERNAL_RAM_START, EXTERNAL_RAM_END, addr);
        return mmu->exram[virtual_addr];
    }

    case SECTION_WORK_RAM:
    {
        virtual_addr = __mmu_calculate_virtual_addr(WRAM_SIZE, WORK_RAM_START, WORK_RAM_END, addr);
        return mmu->wram[virtual_addr];
    }

    case SECTION_ECHO_RAM:
    {
        /*
          We are calculating the Index using the ECHO RAM bounds
          Since any read or write mirrors with the work ram
          we should be able to use the calculated index within the
          work ram buffer
        */
        virtual_addr = __mmu_calculate_virtual_addr(WRAM_SIZE, ECHO_RAM_START, ECHO_RAM_END, addr);
        return mmu->wram[virtual_addr];
    }

    case SECTION_OBJECT_RAM:
    {
        virtual_addr = __mmu_calculate_virtual_addr(OAM_SIZE, OBJECT_RAM_START, OBJECT_RAM_END, addr);
        return mmu->oam[virtual_addr];
    }

    case SECTION_INPUT_OUTPUT:
    {
        virtual_addr = __mmu_calculate_virtual_addr(IO_SIZE, IO_START, IO_END, addr);
        return mmu->io[virtual_addr];
    }

    case SECTION_HIGH_RAM:
    {
        virtual_addr = __mmu_calculate_virtual_addr(HRAM_SIZE, HIGH_RAM_START, HIGH_RAM_END, addr);
        return mmu->hram[virtual_addr];
    }

    case SECTION_IER:
    {
        return mmu->ier;
    }

    case SECTION_ILLEGAL:
    case SECTION_PROHIBITED:
    default:
        return bad_value;
    }
}
