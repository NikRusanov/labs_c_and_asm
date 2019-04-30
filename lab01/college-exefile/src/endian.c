/*
 * endian.c
 *
 *  Created on: 5 нояб. 2016 г.
 *      Author: sadko
 */

#include <endian.h>

uint16_t bytes_swap_u16(uint16_t v)
{
    return (v >> 8) | (v << 8);
}

uint32_t bytes_swap_u32(uint32_t v)
{
    v   = (v >> 16) | (v << 16);
    return ((v & 0xff00ff00) >> 8) | ((v & 0xff00ff) << 8);
}

uint64_t bytes_swap_u64(uint64_t v)
{
    v   = (v >> 32) | (v << 32);
    v   = ((v & 0xffff0000ffff0000ULL) >> 16) | ((v & 0xffff0000ffffULL) << 16);
    return ((v & 0xff00ff00ff00ff00ULL) >> 8) | ((v & 0xff00ff00ff00ffULL) << 8);
}

int16_t bytes_swap_i16(int16_t v)
{
    return bytes_swap_u16(v);
}

int32_t bytes_swap_i32(int32_t v)
{
    return bytes_swap_u32(v);
}

int64_t bytes_swap_i64(int64_t v)
{
    return bytes_swap_u64(v);
}



