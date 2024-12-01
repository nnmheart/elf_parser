#pragma once
#include<stdint.h>

// Defined values of bit.
enum elf_bit {
    elf_bit_32 = 1,
    elf_bit_64 = 2
};

// Defined values of endian.
enum elf_endian {
    elf_endian_little = 1,
    elf_endian_big = 2
};

// Defined values of OSABI field.
enum elf_osabi {
    elf_abi_system_v,
    elf_abi_hpux,
    elf_abi_netbsd,
    elf_abi_linux,
    elf_abi_gnuhurd,
    elf_abi_solaris,
    elf_abi_aix,
    elf_abi_irix,
    elf_abi_freebsd,
    elf_abi_tru64,
    elf_abi_novellmodesto,
    elf_abi_openbsd,
    elf_abi_openvms,
    elf_abi_nonstopkernel,
    elf_abi_aros,
    elf_abi_fenixos,
    elf_abi_cloudabi,
    elf_abi_openvos
};

// ELF file type.
enum elf_ftype {
    elf_ftype_none,
    elf_ftype_relocatable,
    elf_ftype_executable,
    elf_ftype_shared,
    elf_ftype_core,
    
    // OS specific. Inclusive range.
    elf_ftype_loos = 0xFE00,
    elf_ftype_hios = 0xFEFF,

    // Processor specific. Inclusive range.
    elf_ftype_loproc = 0xFF00,
    elf_ftype_hiproc = 0xFFFF
};

// ELF program header type field.
enum elf_ptype {
    elf_ptype_null,
    elf_ptype_loadable,
    elf_ptype_dynamic_info,
    elf_ptype_interpreter_info,
    elf_ptype_note,
    elf_ptype_shlib, // Reserved
    elf_ptype_phdr,
    elf_ptype_tls,
    // OS specific. Inclusive range.
    elf_ptype_loos   = 0x60000000,
    elf_ptype_hios   = 0x6FFFFFFF,
    // Processor specific. Inclusive range.
    elf_ptype_loproc = 0x70000000,
    elf_ptype_hiproc = 0x7FFFFFFF
};

// ELF program flag field.
enum elf_pflags {
    elf_pflags_executable = 1,
    elf_pflags_writeable = 2,
    elf_pflags_readable = 4
};

// Section header type field.
enum elf_stype {
    elf_stype_null,
    elf_stype_progbits,
    elf_stype_symtab,
    elf_stype_strtab,
    elf_stype_rela,
    elf_stype_hash,
    elf_stype_dynamic_info,
    elf_stype_note,
    elf_stype_nobits,
    elf_stype_rel,
    elf_stype_shlib, // Reserved
    elf_stype_dynsym,
    elf_stype_init_array,
    elf_stype_finish_array,
    elf_stype_preinit_array,
    elf_stype_group,
    elf_stype_symtab_shndx,
    elf_stype_num,
    // OS specific.
    elf_stype_loos = 0x60000000
};

// Section header flags field.
enum elf_sflags {
    elf_sflags_writable         = 0x1,
    elf_sflags_allocates        = 0x2,
    elf_sflags_executable       = 0x4,
    elf_sflags_merge            = 0x10,
    elf_sflags_strings          = 0x20,
    elf_sflags_info_link        = 0x40,
    elf_sflags_link_order       = 0x80,
    elf_sflags_os_nonconforming = 0x100,
    elf_sflags_group            = 0x200,
    elf_sflags_tls              = 0x400,
    elf_sflags_maskos           = 0x0FF00000,
    elf_sflags_maskproc         = 0xF0000000,
    elf_sflags_ordered          = 0x4000000,
    elf_sflags_excluded         = 0x8000000
};

// Magic bytes of ELF header.
struct elf_hident {
    uint8_t magic[4];
    uint8_t bit;     // 1 = 32, 2 = 64
    uint8_t endian;  // 1 = little, 2 = big
    uint8_t version; // 1.
    uint8_t osabi;
    uint8_t abiversion;
    uint8_t pad[7];
};

// Below are just parts of ELF header informations separated by address fields.
struct elf_hinfo1 {
    uint16_t file_type;
    uint16_t machine;
    uint32_t version; // 1.
};

struct elf_hinfo2 {
    uint32_t flags;
    uint16_t size_eh;
    uint16_t size_ph_entry;
    uint16_t count_ph;
    uint16_t size_sh_entry;
    uint16_t count_sh;
    uint16_t index_shstr;
};

// Header for 32 bit ELF files.
struct elf32_header {
    struct elf_hident ident;
    struct elf_hinfo1 info1;
    uint32_t entry;
    uint32_t offset_ph;
    uint32_t offset_sh;
    struct elf_hinfo2 info2;
};

// Header for 64 bit ELF files. Same as above but addresses are 64 bits.
struct elf64_header {
    struct elf_hident ident;
    struct elf_hinfo1 info1;
    uint64_t entry;
    uint64_t offset_ph;
    uint64_t offset_sh;
    struct elf_hinfo2 info2;
};

// Program header for 32 bit ELF files.
struct elf32_program_header {
    uint32_t type;
    uint32_t offset;
    uint32_t vaddr;
    uint32_t paddr;
    uint32_t filesz;
    uint32_t memsz;
    uint32_t flags;
    uint32_t alignment;
};

// Program header for 64 bit ELF files. Same as above(except position of flags) but most things are 64 bit.
struct elf64_program_header {
    uint32_t type;
    uint32_t flags;
    uint64_t offset;
    uint64_t vaddr;
    uint64_t paddr;
    uint64_t filesz;
    uint64_t memsz;
    uint64_t align;
};

// Section header for 32 bit ELF files.
struct elf32_section_header {
    uint32_t name_offset;
    uint32_t type;
    uint32_t flags;
    uint32_t virtual_addr;
    uint32_t file_offset;
    uint32_t size;
    uint32_t link;
    uint32_t info;
    uint32_t alignment;
    uint32_t size_entry;
};

// Section header for 64 bit ELF files. Same as above but addresses, flags, sizes are 64 bit.
struct elf64_section_header {
    uint32_t name_offset;
    uint32_t type;
    uint64_t flags;
    uint64_t virtual_addr;
    uint64_t file_offset;
    uint64_t size;
    uint32_t link;
    uint32_t info;
    uint64_t alignment;
    uint64_t size_entry;
};

// Functions.
/**
 * @pre This assumes that data passed into `content` is 100% valid. The only check done is ELF magic.
 * 
 * @param[in, out] ident Pointer to identity header struct to put datas into.
 * @param[in] content Pointer to memory to parse header.
 * 
 * @return 0 if everything succeeded. Otherwise 1. (Currently means magic is invalid.)
 */
int elf_parse_ident(struct elf_hident* ident, uint8_t* content);

/**
 * @pre This assumes that data passed into `content` is 100% valid AND `ident` field of `header` value is valid.
 * 
 * @param[in, out] header Pointer to ELF32 header struct to read and put datas into.
 * @param[in] content Pointer to memory that STARTS from bytes AFTER ident header.
 * 
 * @return 0 if everything succeeded. Otherwise 1. (Currently this means ident header is 64 bit while programmer requested for parsing of 32 bit.)
 */
int elf_parse_header32(struct elf32_header* header, uint8_t* content);

/**
 * @pre This assumes that data passed into `content` is 100% valid AND `ident` field of `header` value is valid.
 * 
 * @param[in, out] header Pointer to ELF64 header struct to read and put datas into.
 * @param[in] content Pointer to memory that STARTS from bytes AFTER ident header.
 * 
 * @return 0 if everything succeeded. Otherwise 1. (Currently this means ident header is 32 bit while programmer requested for parsing of 64 bit.)
 */
int elf_parse_header64(struct elf64_header* header, uint8_t* content);

