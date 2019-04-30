/*
 * msdos.c
 *
 *  Created on: 5 нояб. 2016 г.
 *      Author: sadko
 */

// Standard library includes
#include <stdio.h>

// Program headers includes
#include <msdos.h>
#include <errors.h>
#include <endian.h>

/** Dump valid header of the MS-DOS EXE to console
 *
 * @param hdr MS-DOS EXE header
 */
static void msdos_dump_header(const exe_header_t *hdr)
{
    int v, w;
    printf("MS-DOS EXE Header Information:\n");
    printf("  Signature:                  %c%c\n", hdr->signature[0], hdr->signature[1]);
    v   = uint16_le(hdr->bytes_in_last_block);
    printf("  Bytes in last block:        %d (0x%x)\n", v, v);
    v   = uint16_le(hdr->blocks_in_file);
    printf("  512-byte blocks in file:    %d (0x%x)\n", v, v);
    v   = uint16_le(hdr->num_relocs);
    printf("  Relocation records:         %d (0x%x)\n", v, v);
    v   = uint16_le(hdr->header_paragraphs) * 16;
    printf("  Header size:                %d (0x%x)\n", v, v);
    v   = uint16_le(hdr->min_extra_paragraphs) * 16;
    printf("  Minimum extra memory:       %d (0x%x)\n", v, v);
    v   = uint16_le(hdr->max_extra_paragraphs) * 16;
    printf("  Maximum extra memory:       %d (0x%x)\n", v, v);
    v   = uint16_le(hdr->ss);
    w   = uint16_le(hdr->sp);
    printf("  Initial SS:SP (hex):        %04x:%04x\n", v, w);
    v   = uint16_le(hdr->checksum);
    printf("  Header checksum:            %d (0x%x)\n", v, v);
    v   = uint16_le(hdr->cs);
    w   = uint16_le(hdr->ip);
    printf("  Relative CS:IP (hex):       %04x:%04x\n", v, w);
    v   = uint16_le(hdr->reloc_table_offset);
    printf("  Relocation table offset:    %d (0x%x)\n", v, v);
    v   = uint16_le(hdr->overlay_number);
    printf("  Overlay number:             %d (0x%x)\n", v, v);

}

int msdos_dump_relocation(const exe_header_t *hdr, FILE *fd)
{
    int v, w;
    exe_reloc_t reloc;

    // Get number of relocs
    int n   = uint16_le(hdr->num_relocs);
    if (n <= 0)
    {
        printf("There is no relocation data\n");
        return ERR_OK;
    }

    // Seek file at the relocation table position
    int off = uint16_le(hdr->reloc_table_offset);
    if (fseek(fd, off, SEEK_SET) != 0)
    {
        fprintf(stderr, "Could not read MS-DOS relocation information\n");
        return ERR_BAD_FORMAT;
    }

    // Output relocation data
    printf("\nRelocation data (segment:offset=linear):\n");
    for (int i=0; i<n; ++i)
    {
        // Read relocation record
        int result = fread(&reloc, sizeof(exe_reloc_t), 1, fd);
        if (result <= 0)
        {
            fprintf(stderr, "Unexpected end of file\n");
            return ERR_BAD_FORMAT;
        }

        // Dump relocation record
        w   = uint16_le(reloc.offset);
        v   = uint16_le(reloc.segment);
        off = (v << 4) + w;

        // Output record
        if ((i%4) == 0)
            printf(" ");
        printf(" %04x:%04x=%05x", v, w, off);
        if ((i%4) == 3)
            printf("\n");
    }
    printf("\n");

    return ERR_OK;
}

int msdos_parse(const char *fname)
{
    // Open binary file for reading
    FILE *fd = fopen(fname, "rb");
    if (fd == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", fname);
        return ERR_CANT_OPEN_FILE;
    }

    // Try to read header
    exe_header_t hdr;
    int result = fread(&hdr, sizeof(exe_header_t), 1, fd);
    if (result <= 0)
    {
        fclose(fd); // Close file!
        fprintf(stderr, "Could not read MS-DOS header\n");
        return ERR_BAD_FORMAT;
    }

    // Analyze header
    if ((hdr.signature[0] != 'M') ||
        (hdr.signature[1] != 'Z'))
    {
        fclose(fd); // Close file!
        fprintf(stderr, "File is not of MS-DOS EXE format\n");
        return ERR_BAD_FORMAT;
    }

    // Dump header
    msdos_dump_header(&hdr);
    result = msdos_dump_relocation(&hdr, fd);
    fclose(fd); // Close file!

    return result;
}


