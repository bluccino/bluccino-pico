// pico/api.h - complete C++ pico API
// in one of your c-files declare a `pico` API in a global scope as follows:
//
//     PI_api pico = PI_API();  // declaration of pico API
//
#ifndef __PICO__H__
#define __PICO__H__

#include "pico/api.h"  // iclude first!

#undef pico
extern PI_api pico;

#endif // __PICO__H__
