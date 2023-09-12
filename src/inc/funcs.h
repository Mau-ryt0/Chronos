// funcs.h
#ifndef _FUNCS_H_INCLUDE
#define _FUNCS_H_INCLUDE
#include <gb/gb.h>
#include <stdbool.h>

#include "hUGEDriver.h"

// #include <gbdk/emu_debug.h>

#define textvel1 1
#define textvel2 2
#define textvel3 4

extern bool showingDialog;

#define vblankDelay(d) for (uint8_t i=0; i<d; i++) wait_vbl_done();

typedef struct level_t
{
    uint8_t x;
    uint8_t y;

    const uint16_t width;
    // const uint16_t height;

    const uint8_t *tile_data;
    const uint8_t tile_count;

    const unsigned char * map;
    const unsigned char * attr;

    const palette_color_t *palettes;
    const uint8_t palettes_count;

    // const uint8_t colliders[];
} level_t;

extern void VBL_isr(void);
extern void play(const hUGESong_t Song);
extern void show_dialog(uint16_t x, uint16_t y);
extern void win_print(unsigned char *text, uint8_t size);
extern void scroll_sprites(uint8_t sprites, int8_t _dir, uint8_t vel);

extern bool colliding(int16_t x, int16_t y, const unsigned char *map);
extern bool canInteract(int16_t x, int16_t y);

#endif