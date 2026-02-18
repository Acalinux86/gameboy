#ifndef MMU_H_
#define MMU_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cart/cart.h"

enum MapSection
{
    SECTION_ROM,
    SECTION_VIDEO_RAM,
    SECTION_EXTERNAL_RAM,
    SECTION_WORK_RAM,
    SECTION_ECHO_RAM,
    SECTION_OBJECT_RAM,
    SECTION_PROHIBITED,
    SECTION_INPUT_OUTPUT,
    SECTION_HIGH_RAM,
    SECTION_IER,
    SECTION_ILLEGAL,
};

/* Read Only Memory Address SPACE */
#define ROM_START 0x0000
#define ROM_END   0x8000

/* Video Ram Address SPACE */
#define VIDEO_RAM_START 0x8000
#define VIDEO_RAM_END   0x9FFF

/* From Cartridge Switchable Bank Address SPACE */
#define EXTERNAL_RAM_START 0xA000
#define EXTERNAL_RAM_END   0xBFFF

/* Read Only Memory Address SPACE */
#define WORK_RAM_START 0xC000
#define WORK_RAM_END   0xDFFF

/* Work RAM Address SPACE */
#define ECHO_RAM_START 0xE000
#define ECHO_RAM_END   0xFDFF

/* Object Atribute Memory Address SPACE */
#define OBJECT_RAM_START 0xFE00
#define OBJECT_RAM_END   0xFE9F

/* This Space is Prohibited for Read and Write Address SPACE */
#define PROHIBITED_SPACE_START 0xFEA0
#define PROHIBITED_SPACE_END   0xFEFF

/* This Space is Mapped to inpu and Output Ports Address SPACE */
#define IO_START 0xFF00
#define IO_END   0xFF7F

/* High RAM Address SPACE */
#define HIGH_RAM_START 0xFF80
#define HIGH_RAM_END   0xFFFE

/* Interrupt Enable Register Address SPACE */
#define IER_START 0xFFFF
#define IER_END   0xFFFF

#define BOOT_SEQUENCE_SIZE 0x100
typedef byte Boot[BOOT_SEQUENCE_SIZE];

struct ROM
{
    Boot sequence;
    struct CartridgeHeader cart;
    struct Bank *banks;
    size_t banks_count;
    byte *rom_bytes;
    size_t rom_size;
    int enable_banking;
};

/* 8 KiB of Video RAM*/
#define VRAM_SIZE 8*1024
typedef byte VRAM[VRAM_SIZE];

/* 8 KiB of External RAM*/
#define EXRAM_SIZE 8*1024
typedef byte EXRAM[EXRAM_SIZE];

/* 8 KiB of Work RAM*/
#define WRAM_SIZE 8*1024
typedef byte WRAM[VRAM_SIZE];

/* 160 Bytes of OAM */
#define OAM_SIZE 160
typedef byte OAM[OAM_SIZE];

/* 128 Bytes of IO */
#define IO_SIZE 128
typedef byte IO[IO_SIZE];

/* 127 Bytes of HRAM */
#define HRAM_SIZE 127
typedef byte HRAM[HRAM_SIZE];

struct MMU
{
    char *game_title; /* Game Title */
    uint16_t rom_size;
    struct ROM rom; /* ROM */
    VRAM vram; /* Video Ram */
    EXRAM exram; /* External Ram*/
    WRAM wram; /* Work Ram */
    OAM oam; /* Object Attribute Memory */
    IO io; /* Input Output Space */
    HRAM hram; /* High Ram */
    byte ier; /* Interrupt Enable Register */
};

int mmu_destroy(struct MMU *mmu);
int mmu_init(struct MMU *mmu, FILE *fp);


int mmu_write(struct MMU *mmu, uint16_t addr, byte value);

#define bad_value 0xFF
/**
 * Reads a Byte from Gameboy Space
 *
 * @return byte value at addr, bad_value(0XFF) on error
 */
byte mmu_read(struct MMU *mmu, uint16_t addr);

#endif /* MMU_H_ */
