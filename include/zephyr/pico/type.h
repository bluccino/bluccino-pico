// pico/type.h - pico type definitions
#ifndef __PICO_TYPE_H__
#define __PICO_TYPE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef int64_t pico_us;          // micro seconds
typedef int64_t pico_ms;          // mili seconds
typedef const char *pico_txt;     // pointer to text

#ifdef __cplusplus
}
#endif
#endif // __PICO_TYPE_H__
