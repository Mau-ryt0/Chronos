// funcs.h
#ifndef _FUNCS_H_INCLUDE
#define _FUNCS_H_INCLUDE
#include <gb/gb.h>
#include <stdbool.h>

#define vblankDelay(d) for (uint8_t i=0; i<d; i++) wait_vbl_done();

extern bool colliding(uint16_t x, uint16_t y);
extern bool canInteract(uint16_t x, uint16_t y);

#endif