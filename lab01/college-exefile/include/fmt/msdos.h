/*
 * msdos.h
 *
 *  Created on: 5 нояб. 2016 г.
 *      Author: sadko
 */

#ifndef FMT_MSDOS_H_
#define FMT_MSDOS_H_

#include <types.h>

/**
    The MS-DOS EXE format, also known as MZ after its signature
    (the initials of Microsoft engineer Mark Zbykowski), was introduced
    with MS-DOS 2.0 (version 1.0 only sported the simple COM format).
    It is designed as a relocatable executable running under real mode.
    As such, only DOS and Windows 9x can use this format natively, but
    there are several free DOS emulators (e.g., DOSBox) that support it
    and that run under various operating systems (e.g., Linux, Amiga,
    Windows NT, etc.). Although they can exist on their own, MZ executables
    are embedded in all NE, LE, and PE executables, usually as stubs
    so that when they are ran under DOS, they display:

       This program cannot be run in MS-DOS mode.

    However, they can also be used so that a single executable can provide
    2 ports of the same application (e.g.,one for DOS and one for Windows).
    Windows 9x will run the MZ executable if the program is started from the
    command line prompt, or the PE executable if started normally. In the case
    of boot loaders, they can help provide a DOS version, esp. since (U)EFI
    requires the PE format which contains a MZ executable.
 */

#pragma pack(push, 1)

/** DOS EXE Header structure
 *
 */
typedef struct exe_header_t
{
    uint8_t     signature[2];           // +0x00: 0x5A4D (ASCII for 'M' and 'Z')
    uint16_t    bytes_in_last_block;    // +0x02: Number of bytes in the last page.
    uint16_t    blocks_in_file;         // +0x04: Number of whole/partial pages.
    uint16_t    num_relocs;             // +0x06: Number of entries in the relocation table
    uint16_t    header_paragraphs;      // +0x08: The number of paragraphs taken up by the header
    uint16_t    min_extra_paragraphs;   // +0x0a: The number of paragraphs required by the program, excluding the PSP and program image. If no free block is big enough, the loading stops
    uint16_t    max_extra_paragraphs;   // +0x0c: The number of paragraphs requested by the program. If no free block is big enough, the biggest one possible is allocated.
    uint16_t    ss;                     // +0x0e: Relocatable segment address for SS
    uint16_t    sp;                     // +0x10: Initial value for SP
    uint16_t    checksum;               // +0x12: When added to the sum of all other words in the file, the result should be zero
    uint16_t    ip;                     // +0x14: Initial value for IP
    uint16_t    cs;                     // +0x16: Relocatable segment address for CS
    uint16_t    reloc_table_offset;     // +0x18: The (absolute) offset to the relocation table
    uint16_t    overlay_number;         // +0x1a: Value used for overlay management. If zero, this is the main executable
} exe_header_t;

/** DOS EXE Relocation structure
 *
 */
typedef struct exe_reloc_t
{
    uint16_t    offset;
    uint16_t    segment;
} exe_reloc_t;

#pragma pack(pop)


#endif /* FMT_MSDOS_H_ */
