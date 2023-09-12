// strutcs.h

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdbool.h>

#include "hUGEDriver.h"

// #include "funcs.h"

#define textvel1 1
#define textvel2 2
#define textvel3 4

#define DIR_RIGHT 1
#define DIR_LEFT -1
#define DIR_DOWN 2
#define DIR_UP -2
#define DIR_NULL 0

#define Map_base 0x34

extern joypads_t jpads;
extern bool showingDialog;

typedef struct player_t
{
	// UBYTE sprites[4];
	int16_t x, y;
	uint8_t width;
	uint8_t height;
	uint8_t hearts;
	uint8_t old_hearts;
	// uint8_t health, old_health;
	int8_t dir;
	bool canMove, canAnimate;
}player_t;

extern player_t player;

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

    const uint8_t player_palette;

    const hUGESong_t *song;

    // const uint8_t colliders[];
} level_t;

extern const level_t levels[];
extern level_t currlvl;
