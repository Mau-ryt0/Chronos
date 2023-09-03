// funcs.c

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdbool.h>

#include "Maps/TestMap.h"

#include "inc/funcs.h"
#include "inc/lizzie.h"
#include "inc/setup.h"
#include "inc/main.h"
#include "inc/camera.h"

// unsigned char *current=0;

const unsigned char symbols[] =
{
    '!', '"', '#', '$', '%', '&', 39, '(', ')', '*', '+', ',', '-', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

// const unsigned char numbers[] = {};

uint8_t solidTiles[] =
{
    0x00, 0x02, 0x03, 0x05,
    0x06, 0x07, 0x08, 0x09,
    0x0A, 0x0B, 0x0C, 0x0D,
    0x0E, 0x0F, 0x10, 0x11,
    0x16, 0x17, 0x18, 0x19
};

uint8_t objectTiles[] = {0x18, 0x19};

void VBL_isr(void) {hUGE_dosound();}

void play(const hUGESong_t Song)
{
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;

    __critical {hUGE_init(&Song);}
}

void win_print(unsigned char *text, uint8_t size)
{
    uint8_t xpos=1, ypos=0;
    uint8_t index=0;
    
    while (index<=size-1)
    {
        if (index % 18 == 0) {xpos=1; ypos++;}
        else xpos++;

        const unsigned char *current = &text[index];

        if (*current != ' ') set_win_tile_xy(xpos, ypos, (*current-0x48));
        for (uint8_t i=0; i<(sizeof(symbols)); i++)
            if (*current == symbols[i]) set_win_tile_xy(xpos, ypos, (*current-0x21));
        vblankDelay(textvel2);
        index++;
    }
}

// Function thanks to Larold's Jubilant Junkyard.
// https://github.com/LaroldsJubilantJunkyard/gbdk-tilemap-collision
bool colliding(int16_t x, int16_t y)
{
	// Divide the player's position by 8 to index it to a tile position.
	int16_t column = (camerax>>3)+x/8;
	int16_t row = (cameray>>3)+y/8;
    int16_t TileIndex = TestMap_map[column + row * (TestMap_WIDTH>>3)];
    
    // Get the tile based on the index variable.
    for (uint8_t index=0; index<sizeof(solidTiles); index++)
    	if (TileIndex == solidTiles[index] && camerax >= (Test.x*20) && cameray >= (Test.y*18)) return true;
    return false;
}

bool canInteract(int16_t x, int16_t y)
{
	// Divide the player's position by 8 to index it to a tile position.
	int16_t column = (camerax>>3)+x/8;
	int16_t row = (cameray>>3)+y/8;
    int16_t TileIndex = TestMap_map[column + row * (TestMap_WIDTH>>3)];
    
    // Get the tile based on the index variable.
    for (uint8_t index=0; index<sizeof(objectTiles); index++)
    	if (TileIndex == objectTiles[index]) return true;
    return false;
}