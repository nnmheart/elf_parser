#include<stdint.h>
#include<elf.h>

#define HOST_ENDIAN ((__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) ? elf_endian_big : elf_endian_little)
#define _BYTEPTR(p) ((uint8_t*)&p)
// NOTE: Macro below uses "shouldSwap" that is defined beforehand.
#define _SHORT_MEMCPYSWAP(field, offset, length) mem_cpy_swap(_BYTEPTR(field), &content[offset - 0x10], length, shouldSwap)


int elf_parse_ident(struct elf_hident* ident, uint8_t* content) {
    ident->magic[0] = content[0x00];
    ident->magic[1] = content[0x01];
    ident->magic[2] = content[0x02];
    ident->magic[3] = content[0x03];

    if (content[0] != 0x7F) return 1;
    if (content[1] != 0x45) return 1;
    if (content[2] != 0x4C) return 1;
    if (content[3] != 0x46) return 1;

    ident->bit        = content[0x04];
    ident->endian     = content[0x05];
    ident->version    = content[0x06];
    ident->osabi      = content[0x07];
    ident->abiversion = content[0x08];

    ident->pad[0] = content[0x09];
    ident->pad[1] = content[0x0A];
    ident->pad[2] = content[0x0B];
    ident->pad[3] = content[0x0C];
    ident->pad[4] = content[0x0D];
    ident->pad[5] = content[0x0E];
    ident->pad[6] = content[0x0F];

    return 0;
}

void mem_cpy_swap(uint8_t* dst, uint8_t* src, int length, int doSwap) {
    if (doSwap) {
        for (int i = 0; i < length; i++) {
            dst[i] = src[length - 1 - i];
        }
    }
    else{    
        for (int i = 0; i < length; i++) {
            dst[i] = src[i];
        }
    }
}

int elf_parse_header32(struct elf32_header* header, uint8_t* content) {
    if (header->ident.bit != elf_bit_32) {
        return 1;
    }
    // Will be used inside macro.
    int shouldSwap = header->ident.endian != HOST_ENDIAN; 
    // I know it's bad, but i think it's fine as long as we warn about it
    // And restrict it's use?
    struct elf_hinfo1* info1 = &header->info1;
    struct elf_hinfo2* info2 = &header->info2;

    _SHORT_MEMCPYSWAP(info1->file_type,     0x10, 2);
    _SHORT_MEMCPYSWAP(info1->machine,       0x12, 2);
    _SHORT_MEMCPYSWAP(info1->version,       0x14, 4);
    
    _SHORT_MEMCPYSWAP(header->entry,        0x18, 4);
    _SHORT_MEMCPYSWAP(header->offset_ph,    0x1C, 4);
    _SHORT_MEMCPYSWAP(header->offset_sh,    0x20, 4);

    _SHORT_MEMCPYSWAP(info2->flags,         0x24, 4);

    _SHORT_MEMCPYSWAP(info2->size_eh,       0x28, 2);
    _SHORT_MEMCPYSWAP(info2->size_ph_entry, 0x2A, 2);
    _SHORT_MEMCPYSWAP(info2->count_ph,      0x2C, 2);
    _SHORT_MEMCPYSWAP(info2->size_sh_entry, 0x2E, 2);
    _SHORT_MEMCPYSWAP(info2->count_sh,      0x30, 2);
    _SHORT_MEMCPYSWAP(info2->index_shstr,   0x32, 2);

    return 0;
}

// Copy of above, just modified to account for address being 8 bytes.
int elf_parse_header64(struct elf64_header* header, uint8_t* content) {
    if (header->ident.bit != elf_bit_64) {
        return 1;
    }
    // Will be used inside macro.
    int shouldSwap = header->ident.endian != HOST_ENDIAN; 
    // I know it's bad, but i think it's fine as long as we warn about it
    // And restrict it's use?
    struct elf_hinfo1* info1 = &header->info1;
    struct elf_hinfo2* info2 = &header->info2;

    _SHORT_MEMCPYSWAP(info1->file_type,     0x10, 2);
    _SHORT_MEMCPYSWAP(info1->machine,       0x12, 2);
    _SHORT_MEMCPYSWAP(info1->version,       0x14, 4);
    
    _SHORT_MEMCPYSWAP(header->entry,        0x18, 8);
    _SHORT_MEMCPYSWAP(header->offset_ph,    0x20, 8);
    _SHORT_MEMCPYSWAP(header->offset_sh,    0x28, 8);

    _SHORT_MEMCPYSWAP(info2->flags,         0x30, 4);

    _SHORT_MEMCPYSWAP(info2->size_eh,       0x34, 2);
    _SHORT_MEMCPYSWAP(info2->size_ph_entry, 0x36, 2);
    _SHORT_MEMCPYSWAP(info2->count_ph,      0x38, 2);
    _SHORT_MEMCPYSWAP(info2->size_sh_entry, 0x3A, 2);
    _SHORT_MEMCPYSWAP(info2->count_sh,      0x3C, 2);
    _SHORT_MEMCPYSWAP(info2->index_shstr,   0x3E, 2);

    return 0;
}