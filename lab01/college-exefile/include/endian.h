/*
 * endian.h
 *
 *  Created on: 5 нояб. 2016 г.
 *      Author: sadko
 */

#ifndef ENDIAN_H_
#define ENDIAN_H_

#include <types.h>

extern uint16_t     bytes_swap_u16(uint16_t v);
extern uint32_t     bytes_swap_u32(uint32_t v);
extern uint64_t     bytes_swap_u64(uint64_t v);

extern int16_t      bytes_swap_i16(int16_t v);
extern int32_t      bytes_swap_i32(int32_t v);
extern int64_t      bytes_swap_i64(int64_t v);

#if defined(__i386__) || defined(__x86_64__)
    // little-endian platform
    #define uint16_le(x)            (x)
    #define uint32_le(x)            (x)
    #define uint64_le(x)            (x)

    #define int16_le(x)             (x)
    #define int32_le(x)             (x)
    #define int64_le(x)             (x)

    #define uint16_be(x)            bytes_swap_u16(x)
    #define uint32_be(x)            bytes_swap_u32(x)
    #define uint64_be(x)            bytes_swap_u64(x)

    #define int16_be(x)             bytes_swap_i16(x)
    #define int32_be(x)             bytes_swap_i32(x)
    #define int64_be(x)             bytes_swap_i64(x)

#else
    // Consider platform is big-endian
    #define uint16_le(x)            bytes_swap_u16(x)
    #define uint32_le(x)            bytes_swap_u32(x)
    #define uint64_le(x)            bytes_swap_u64(x)

    #define int16_le(x)             bytes_swap_i16(x)
    #define int32_le(x)             bytes_swap_i32(x)
    #define int64_le(x)             bytes_swap_i64(x)

    #define uint16_be(x)            (x)
    #define uint32_be(x)            (x)
    #define uint64_be(x)            (x)

    #define int16_be(x)             (x)
    #define int32_be(x)             (x)
    #define int64_be(x)             (x)

#endif

#endif /* ENDIAN_H_ */
