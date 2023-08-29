// funcs.c

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdbool.h>

#include "Maps/TestMap.h"

#include "inc/lizzie.h"
#include "inc/setup.h"
#include "inc/main.h"
#include "inc/camera.h"

uint8_t solidTiles[] =
{
    0x00, 0x02, 0x03, 0x05,
    0x06, 0x07, 0x08, 0x09,
    0x0A, 0x0B, 0x0C, 0x0D,
    0x0E, 0x0F, 0x10, 0x11,
    0x16, 0x17, 0x18, 0x19
};

uint8_t objectTiles[] = {0x18, 0x19};

// Function thanks to Larold's Jubilant Junkyard.
// https://github.com/LaroldsJubilantJunkyard/gbdk-tilemap-collision
bool colliding(uint16_t x, uint16_t y)
{
	// Divide the player's position by 8 to index it to a tile position.
	uint16_t column = (camerax>>3)+x/8;
	uint16_t row = (cameray>>3)+y/8;
    uint16_t TileIndex = TestMap_map[column + row * (TestMap_WIDTH>>3)];
    
    // Get the tile based on the index variable.
    for (uint8_t index=0; index<sizeof(solidTiles); index++)
    	if (TileIndex == solidTiles[index]) return true;
    return false;
}

bool canInteract(uint16_t x, uint16_t y)
{
	// Divide the player's position by 8 to index it to a tile position.
	uint16_t column = (camerax>>3)+x/8;
	uint16_t row = (cameray>>3)+y/8;
    uint16_t TileIndex = TestMap_map[column + row * (TestMap_WIDTH>>3)];
    
    // Get the tile based on the index variable.
    for (uint8_t index=0; index<sizeof(objectTiles); index++)
    	if (TileIndex == objectTiles[index]) return true;
    return false;
}