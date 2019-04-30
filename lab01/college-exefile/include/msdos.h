/*
 * msdos.h
 *
 *  Created on: 5 нояб. 2016 г.
 *      Author: sadko
 */

#ifndef MSDOS_H_
#define MSDOS_H_

#include <fmt/msdos.h>

/** Parse MS DOS EXE header and output it to the console
 * Prints errors to stderr if there are andy
 *
 * @param fname file name to parse
 * @return 0 on success
 */
extern int msdos_parse(const char *fname);

#endif /* MSDOS_H_ */
