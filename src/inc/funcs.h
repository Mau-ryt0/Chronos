// funcs.h
#ifndef _FUNCS_H_INCLUDE
#define _FUNCS_H_INCLUDE
#include <gb/gb.h>
#include <stdbool.h>

#include "hUGEDriver.h"

#define textvel1 1
#define textvel2 2
#define textvel3 4

#define vblankDelay(d) for (uint8_t i=0; i<d; i++) wait_vbl_done();

extern void VBL_isr(void);

struct map
{
    int8_t x;
    int8_t y;
};

extern struct map Test;

extern void play(const hUGESong_t Song);
extern void win_print(unsigned char *text, uint8_t size);
extern bool colliding(int16_t x, int16_t y);
extern bool canInteract(int16_t x, int16_t y);


#endif