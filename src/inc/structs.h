// strutcs.h

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdbool.h>

#include "hUGEDriver.h"

// Right & Left = 7
#define vol_7 0b11101110

// Right & Left = 6
#define vol_6 0b01100110

// Right & Left = 5
#define vol_5 0b01010101

// Right & Left = 4
#define vol_4 0b01000100

// Right & Left = 3
#define vol_3 0b00110011

// Right & Left = 2
#define vol_2 0b00100010

// Right & Left = 1
#define vol_1 0b00010001

// Right & Left = 0
#define vol_0 0b00000000

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

extern const unsigned char symbols[25];

extern palette_color_t BGPalette[4];
extern palette_color_t BGPaletteDark[4];

extern const uint8_t solidTiles[];
extern const uint8_t objectTiles[];

extern uint8_t load_lvl;

typedef struct player_t
{
	// UBYTE sprites[4];
	int16_t x, y;
	uint8_t width, height;
	uint8_t hearts, old_hearts;
	// uint8_t health, old_health;
	int8_t dir, old_dir;
	bool canAnimate;
}player_t;

extern player_t player;

typedef struct level_t
{
    const uint8_t lvl_num;
    uint8_t x;
    uint8_t y;

    const uint16_t width;
    const uint16_t height;

    const uint8_t *tile_data;
    const uint8_t tile_count;

    const unsigned char * map;
    const unsigned char * attr;

    const uint8_t *solids;
    const uint8_t *objects;

    const palette_color_t *palettes;
    const uint8_t palettes_count;

    const uint8_t player_palette;

    const hUGESong_t *song;
} level_t;

extern const level_t levels[];
extern level_t currlvl;
