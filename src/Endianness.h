//
//  Endianness.h
//  CoreTypes
//
//  Created by Kostis Giannousakis on 12/21/14.
//  Copyright (c) 2014 Kostis Giannousakis. All rights reserved.
//

#ifndef CoreTypes_Endianness_h
#define CoreTypes_Endianness_h

#define byteswap_16(x) ((__uint16_t)(((x & 0xff)<<8) | ((x & 0xff00)>>8)));
#define byteswap_32(x) ((__uint32_t)(((x & 0x000000ff)<<24) | ((x & 0x0000ff00)<<8) | ((x & 0x00ff0000)>>8) | ((x & 0xff000000)>>24)));

#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && defined(__ORDER_BIG_ENDIAN__)
# if    __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#  define htole_16(x)               ((__uint16_t)(x))
#  define htobe_16(x) byteswap_16   (x)
#  define letoh_16(x)               ((__uint16_t)(x))
#  define betoh_16(x) byteswap_16   (x)
#  define htole_32(x)               ((__uint32_t)(x))
#  define htobe_32(x) byteswap_32   (x)
#  define letoh_32(x)               ((__uint32_t)(x))
#  define betoh_32(x) byteswap_32   (x)
# elif  __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#  define htole_16(x) byteswap_16   (x)
#  define htobe_16(x)               ((__uint16_t)(x))
#  define letoh_16(x) byteswap_16   (x)
#  define betoh_16(x)               ((__uint16_t)(x))
#  define htole_32(x) byteswap_32   (x)
#  define htobe_32(x)               ((__uint32_t)(x))
#  define letoh_32(x) byteswap_32   (x)
#  define betoh_32(x)               ((__uint32_t)(x))
# else
#  error Unknown endianness
# endif
#else
# error Endianness not defined
#endif /* defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && defined(__ORDER_BIG_ENDIAN__) */

#endif
