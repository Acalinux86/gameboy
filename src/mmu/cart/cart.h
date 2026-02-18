#ifndef CART_H_
#define CART_H_

#include <stdlib.h>
#include <stdint.h>

typedef uint8_t byte;

/* The Cartridge Header is 80 bytes */
#define CARTRIDGE_HEADER_SIZE 0x50

/*
  - Entry Point - 0x100 - 0x103
  The Four Byte Entry Point After the Boot Rom Sequence
  Which Takes Up the First 256 Bytes of the Rom
*/
#define ENRTY_POINT_LENGTH 4
typedef byte EntryPoint[ENRTY_POINT_LENGTH];

/*
  - Nintendo Logo - 0x104 - 0x133
  The Next 48 Bytes Contain the Nintendo Logo,
  Which is a bit Map Image, they must be the
  following or game wont run

  ===================================================
  | CE ED 66 66 CC 0D 00 0B 03 73 00 83 00 0C 00 0D |
  | 00 08 11 1F 88 89 00 0E DC CC 6E E6 DD DD D9 99 |
  | BB BB 67 63 6E 0E EC CC DD DC 99 9F BB B9 33 3E |
  ===================================================

  the first 24 bytes going from top to bottom is the
  first half of the logo, the remaining 24-bytes is the
  bottom half.

  The bytes are interpreted as a 4 pixel for each nibble in
  a byte so a byte decoded gives us 8 pixels
*/
#define LOGO_DATA_SIZE 48
typedef byte Logo[LOGO_DATA_SIZE];

/*
  - Title - 0x134 - 0x143
  These Bytes contain the Title of the Game in UpperCase
  ASCII Chars. They are padded with 0x00 bytes if lenght is
  less than 0

  * In later Cartridges:
  - Bytes 0x13F - 0x142 contained the manufactures code.
  - Byte 0x143 contained CGB Flag

  The CGB FLAG is interpreted as below:
  - 0x80 - meant the game supported CGB and was backwards compatible with
  monochrome gameboys
  - 0xCO - meant the game only supported CGB and was not backwards compatible
  with monochrome gameboys

  Since these Three Varibles are interpreted different on different gameboys
  and Architecture, we have to the Cartride type. So We put them all in buffer
  and slice the buffer after we determine

  TITLE_MANC_CGBF_SIZE => title, manufacture code and CGB Flag total size
*/
#define TITLE_MANC_CGBF_SIZE 16
typedef byte TitleBlock[TITLE_MANC_CGBF_SIZE];

enum CartridgeType
{
    MBC_NO = 0x0,
    MBC_1,
    MBC_2,
    MBC_3,
    MBC_5,
    MBC_6,
    MBC_7,
    MMM01,
    M161,
    HUC_1,
    HUC_2,
};

enum RomSize
{
    ROM32KiB  = 0x00,
    ROM64KiB  = 0x01,
    ROM128KiB  = 0x02,
    ROM256KiB  = 0x03,
    ROM512KiB  = 0x04,
    ROM1MiB  = 0x05,
    ROM2MiB  = 0x06,
    ROM4MiB  = 0x07,
    ROM8MiB  = 0x08,
};

enum RamSize
{
    ZERO = 0x00,
    UNUSED = 0x01,
    RAM8KiB = 0x02,
    RAM32KiB = 0x03,
    RAM128KiB = 0x04,
    RAM64KiB = 0x05,
};

struct CartridgeHeader
{
    EntryPoint entry_point;
    Logo logo;
    TitleBlock title_block;

    /*
      - New Licesnsee Code - 0x144 - 0x145
      Two Byte Identifying the Publisher of the game, it only
      works if the the Old Licensee Bytes is 0x33

      - NOTE: Not Useful in this Emulator
    */
    byte new_licensee[2];

    /*
      - SGB Flag - 0x146
      Specifies whether game supports SGB Functions
    */
    byte sgb_flag;

    /*
      - Cartridge Type - 0x147
      It indicates what kind of hardware is present in the cartridge

      - NOTE: The Cartridge Types are enumerated in the CartridgeType
      ENUM Above
    */
    byte cartridge_type;

    /*
      - ROM Size - 0x148
      Indicates the Size of ROM Present in the Cartridge
    */
    byte rom_size;

    /*
      - RAM Size - 0x149
      Indicates How Much RAM is Inside the Cartridge
    */
    byte ram_size;

    /*
      - Destination Code - 0x14A
      Indicates Whether Game is Sold On Japan Or Overseas

      - NOTE: Not Useful in this Emulator
    */
    byte destination_code;

    /*
      - Old Licensee Code
      Pre-SGB Licensee code for the games publishes

      - NOTE: Not Useful in this Emulator
    */

    byte old_licensee;

    /*
      - ROM Version Number - 0x14C
      Specifies the Games Version Number
    */
    byte version;

    /*
      - Header checkSum - 0x14D
    */
    byte header_checksum;

    /*
      - Global Checksum - 0x14E - 0x14F
      Interprets as a 16 bit big endian number computed as a total sum
      of all the bytes in the ROM
    */
    byte global_checksum[2];
};

/* The Title Is Borrowed Memory and Must Be freed in the Main Function */
char *cart_extract_title(const struct CartridgeHeader *cart);

size_t cart_determine_rom_size(const struct CartridgeHeader *cart);
size_t cart_determine_ram_size(const struct CartridgeHeader *cart);
size_t cart_determine_bank_count(const struct CartridgeHeader *cart);

#endif /* CART_H_*/
