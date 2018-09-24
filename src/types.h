#ifndef _NUCLEUS_TYPES_H
#define _NUCLEUS_TYPES_H

#if defined(__i386__)
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef signed long long int int64_t;
typedef unsigned long long int uint64_t;
#else
#error Build for x86_32 only
#endif

#endif
