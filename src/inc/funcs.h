// funcs.h
#include <gb/gb.h>

#define vblankDelay(d) for (uint8_t i=0; i<d; i++) wait_vbl_done();