/*
 * main.c
 *
 *  Created on: 5 нояб. 2016 г.
 *      Author: sadko
 */

// Standard headers
#include <stdio.h>

// Program headers
#include <errors.h>
#include <msdos.h>

/** Main function
 *
 * @param argc number of arguments passed from command line
 * @param argv array of arguments
 * @return 0 on success
 */
int main(int argc, const char **argv)
{
    // Check argument count
    if (argc < 2)
    {
        fprintf(stderr, "File name required as first parameter\n");
        return ERR_ARGUMENT_REQUIRED;
    }

    // Call msdos_parse to parse the file
    return msdos_parse(argv[1]);
}

