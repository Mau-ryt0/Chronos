// funcs.h
#ifndef _FUNCS_H_INCLUDE
#define _FUNCS_H_INCLUDE
#include <gb/gb.h>
#include <stdbool.h>

#include "../Ost/hUGEDriver.h"

#define vblankDelay(d) for (uint8_t i=0; i<d; i++) wait_vbl_done();

// Music/Sound stuff.
extern void hUGEisr(void) NONBANKED;
extern void play(const hUGESong_t *Song) NONBANKED;

extern void set_banked_bkg_data(uint8_t base, uint8_t count, const uint8_t *data, uint8_t bank) NONBANKED;

// Sprites stuff.
extern void scroll_sprites(uint8_t sprites, int8_t _dir, uint8_t vel) NONBANKED;

// Collisions stuff.
extern bool colliding(uint8_t x, uint8_t y, const unsigned char *map) NONBANKED;
extern bool canInteract(uint8_t x, uint8_t y, const unsigned char *map) NONBANKED;

// Window/Dialogs stuff.
extern void show_dialog(uint8_t x, uint8_t y) NONBANKED;
extern void win_print(unsigned char *text, uint8_t size) NONBANKED;

#endif
