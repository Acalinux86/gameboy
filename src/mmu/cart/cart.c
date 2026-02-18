#include "cart.h"

#include <stdio.h>
#include <string.h>

char *cart_extract_title(const struct CartridgeHeader *cart)
{
    size_t title_len = 0;
    for (int i = 0; i < TITLE_MANC_CGBF_SIZE && cart->title_block[i] != '\0'; ++i)
    {
        title_len++;
    }
    char *title = malloc(sizeof(char) * title_len + 1);
    if (!title) return NULL;

    strncpy(title, (char*)&cart->title_block, title_len);
    title[title_len] = '\0';
    return title;
}


size_t cart_determine_rom_size(const struct CartridgeHeader *cart)
{
    enum RomSize rom_size = (enum RomSize)cart->rom_size;
    switch (rom_size)
    {
    case ROM32KiB:  return 32*1024;
    case ROM64KiB:  return 64*1024;
    case ROM128KiB: return 128*1024;
    case ROM256KiB: return 256*1024;
    case ROM512KiB: return 512*1024;
    case ROM1MiB:   return 1*1024*1024;
    case ROM2MiB:   return 2*1024*1024;
    case ROM4MiB:   return 4*1024*1024;
    case ROM8MiB:   return 8*1024*1024;
    default:
        fprintf(stderr, "ERROR: Rom SIZE '%d' Not Handled Yet", cart->rom_size);
        abort();
    }
}

size_t cart_determine_ram_size(const struct CartridgeHeader *cart)
{
    enum RamSize ram_size = (enum RamSize)cart->ram_size;
    switch (ram_size)
    {
    case ZERO:      return 0;
    case UNUSED:    return 0;
    case RAM8KiB:   return 8*1024;
    case RAM32KiB:  return 32*1024;
    case RAM64KiB:  return 64*1024;
    case RAM128KiB: return 128*1024;
    default:
        fprintf(stderr, "ERROR: Ram SIZE '%d' Not Handled Yet", cart->ram_size);
        abort();
    }
}

// int main(void)
// {
//     FILE *fp = fopen("aoss.gb", "rb");
//     if (!fp) return 1;

//     uint8_t buffer[0x100];
//     fread(&buffer, sizeof(buffer), 1, fp);

//     struct CartridgeHeader cart;
//     fread(&cart, sizeof(struct CartridgeHeader), 1, fp);

//     fclose(fp);

//     char *title = cart_extract_title(&cart);
//     printf("%s\n", title);

//     __asm__("int3");
//     return 0;
// }
