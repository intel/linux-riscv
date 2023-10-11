/* This file is released under LGPL2.
   See COPYING.LGPL2 in root directory for more details
*/

/*
 This file is to support header files that are missing in MSVC and
 other non-standard compilers.
*/
#ifndef UNICORN_PLATFORM_H
#define UNICORN_PLATFORM_H

// this system does not have stdint.h
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef signed long long int64_t;
typedef unsigned long long uint64_t;

typedef signed char int_fast8_t;
typedef int int_fast16_t;
typedef int int_fast32_t;
typedef long long int_fast64_t;
typedef unsigned char uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long long uint_fast64_t;

#define INT8_MIN (-127i8 - 1)
#define INT16_MIN (-32767i16 - 1)
#define INT32_MIN (-2147483647i32 - 1)
#define INT64_MIN (-9223372036854775807i64 - 1)
#define INT8_MAX 127i8
#define INT16_MAX 32767i16
#define INT32_MAX 2147483647i32
#define INT64_MAX 9223372036854775807i64
#define UINT8_MAX 0xffui8
#define UINT16_MAX 0xffffui16
#define UINT32_MAX 0xffffffffui32
#define UINT64_MAX 0xffffffffffffffffui64

#define INT_FAST8_MIN INT8_MIN
#define INT_FAST16_MIN INT32_MIN
#define INT_FAST32_MIN INT32_MIN
#define INT_FAST64_MIN INT64_MIN
#define INT_FAST8_MAX INT8_MAX
#define INT_FAST16_MAX INT32_MAX
#define INT_FAST32_MAX INT32_MAX
#define INT_FAST64_MAX INT64_MAX
#define UINT_FAST8_MAX UINT8_MAX
#define UINT_FAST16_MAX UINT32_MAX
#define UINT_FAST32_MAX UINT32_MAX
#define UINT_FAST64_MAX UINT64_MAX

#define INTPTR_MIN INT32_MIN
#define INTPTR_MAX INT32_MAX

// handle inttypes.h compatibility
#define PRId64 __PRI_64_LENGTH_MODIFIER__ "d"
#define PRIi64 __PRI_64_LENGTH_MODIFIER__ "i"
#define PRIo64 __PRI_64_LENGTH_MODIFIER__ "o"
#define PRIu64 __PRI_64_LENGTH_MODIFIER__ "u"
#define PRIx64 __PRI_64_LENGTH_MODIFIER__ "x"
#define PRIX64 __PRI_64_LENGTH_MODIFIER__ "X"

#ifndef va_copy
#define va_copy(d, s) ((d) = (s))
#endif
#define strcasecmp _stricmp

#ifndef NULL
#define NULL 0
#endif

#endif // UNICORN_PLATFORM_H
