#ifndef __BRIDGE_PRIVATE_H_
#define __BRIDGE_PRIVATE_H_
#include <stdint.h>

// the generic wrapper pointer functions
typedef void (*wrapper_t)(x86emu_t* emu, uintptr_t fnc);

#pragma pack(push, 1)
typedef struct onebridge_s {
    uint8_t CC;     // CC int 0x3
    uint8_t S, C;   // 'S' 'C', just a signature
    wrapper_t w;    // wrapper
    uintptr_t f;    // the function for the wrapper
    uint8_t C3;     // C2 or C3 ret
    uint16_t N;     // N in case of C2 ret
} onebridge_t;
#pragma pack(pop)

#endif //__BRIDGE_PRIVATE_H_