// lizzie.c

// #include <GB/gb.h>
// #include <stdio.h>
// #include <stdbool.h>

#include <gb/cgb.h>

#include "Sprites/lizzie_spr.h"
#include "Maps/TestMap.h"

#include "inc/lizzie.h"
#include "inc/setup.h"
#include "inc/main.h"
#include "inc/camera.h"

// Defined in lizzie.h
// #define DIR_RIGHT 1
// #define DIR_LEFT -1
// #define DIR_DOWN 2
// #define DIR_UP -2
// #define DIR_NULL 0

#define velocity 1

struct character lizzie;

// Define the Player color palette.
// UWORD PlayerPalette[4] = {RGB8(196, 207, 161), RGB8(139, 149, 109), RGB8(77, 83, 60), RGB8(31, 31, 31)};

uint8_t solidTiles[] =
{
	0x04, 0x05, 0x06, 0x07,
	0x09, 0x0A, 0x0B, 0x0E,
	0x0F, 0x14, 0x15, 0x16,
	0x17, 0x18, 0x01, 0x03,
	0x08, 0x1A, 0x10, 0x11
};

int8_t dir, old_dir;
uint16_t timer, frame;
bool done = false;

// Function thanks to Larold's Jubilant Junkyard.
// https://github.com/LaroldsJubilantJunkyard/gbdk-tilemap-collision
bool colliding(uint16_t x, uint16_t y)
{
	// Divide the player's position by 8 to index it to a tile position.
	uint16_t column = (camerax>>3)+x/8;
	uint16_t row = (cameray>>3)+y/8;
    uint16_t TileIndex = TestMap_map[column + row * (TestMap_WIDTH>>3)];
    
    // Get the tile based on the index variable.
    return
    	TileIndex == solidTiles[0]||
    	TileIndex == solidTiles[1]||
    	TileIndex == solidTiles[2]||
    	TileIndex == solidTiles[3]||
    	TileIndex == solidTiles[4]||
    	TileIndex == solidTiles[5]||
    	TileIndex == solidTiles[6]||
    	TileIndex == solidTiles[7]||
    	TileIndex == solidTiles[8]||
    	TileIndex == solidTiles[9]||
    	TileIndex == solidTiles[10]||
    	TileIndex == solidTiles[11]||
    	TileIndex == solidTiles[12]||
    	TileIndex == solidTiles[13]||
    	TileIndex == solidTiles[14]||
    	TileIndex == solidTiles[15]||
    	TileIndex == solidTiles[16]||
    	TileIndex == solidTiles[17]||
    	TileIndex == solidTiles[18]||
    	TileIndex == solidTiles[19]
    	?true:false;
}

void walking(int8_t _dir)
{
	if (old_dir != _dir) {timer = frame = 0; old_dir = _dir;}
	
	if (_dir == DIR_RIGHT || _dir == DIR_LEFT)
	{
		if (timer > 8)
		{
			if (frame < 3) frame++;
			else frame = 0;
			timer = 0;
		}
	}
	else if (_dir == DIR_DOWN || _dir == DIR_UP)
	{
		if (timer > 6)
		{
			if (frame < 3) frame++;
			else frame = 0;
			timer = 0;
		}
	}
	
	done = (timer<=0)?false:true;

	switch (frame)
	{
		case 0:
				if (_dir == DIR_RIGHT && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[0]);
				else if (_dir == DIR_LEFT && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[6*32]);
				else if (_dir == DIR_DOWN && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[12*32]);
				else if (_dir == DIR_UP && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[18*32]);
			break;
		case 1:
				if (_dir == DIR_RIGHT && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[2*32]);
				else if (_dir == DIR_LEFT && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[8*32]);
				else if (_dir == DIR_DOWN && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[14*32]);
				else if (_dir == DIR_UP && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[20*32]);
			break;
		case 2:
				if (_dir == DIR_RIGHT && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[4*32]);
				else if (_dir == DIR_LEFT && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[10*32]);
				else if (_dir == DIR_DOWN && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[16*32]);
				else if (_dir == DIR_UP && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[22*32]);
			break;
		case 3:
				if (_dir == DIR_RIGHT && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[2*32]);
				else if (_dir == DIR_LEFT && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[8*32]);
				else if (_dir == DIR_DOWN && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[14*32]);
				else if (_dir == DIR_UP && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[20*32]);
			break;
	}
	timer++;
}

void inputs(uint8_t *x, uint8_t *y, int8_t *_dir)
{
    joypad_ex(&jpads);

    // if ((joypads_t) == J_BUTTON) is incorrect. Character will not move in 8 directions.
    // Use if ((joypads_t) & J_BUTTON) instead to avoid problems.

    if (jpads.joy0 & J_RIGHT && !(jpads.joy0 & J_LEFT))
    {
        if (*_dir == DIR_NULL) *_dir = DIR_RIGHT;
        if (!colliding(*x+1*7, *y))
        	*x+=1;
    }
    else if (!(jpads.joy0 & J_RIGHT) && *_dir == DIR_RIGHT) *_dir = DIR_NULL;

    if (jpads.joy0 & J_LEFT && !(jpads.joy0 & J_RIGHT))
    {
        if (*_dir == DIR_NULL) *_dir = DIR_LEFT;
        if (!colliding(*x-1*8, *y))
        	*x-=1;
    }
    else if (!(jpads.joy0 & J_LEFT) && *_dir == DIR_LEFT) *_dir = DIR_NULL;

    if (jpads.joy0 & J_DOWN && !(jpads.joy0 & J_UP))
    {
        if (*_dir == DIR_NULL) *_dir = DIR_DOWN;
        if (!colliding(*x, *y+1*8))
        	*y+=1;
    }
    else if (!(jpads.joy0 & J_DOWN) && *_dir == DIR_DOWN) *_dir = DIR_NULL;

    if (jpads.joy0 & J_UP && !(jpads.joy0 & J_DOWN))
    {
        if (*_dir == DIR_NULL) *_dir = DIR_UP;
        if (!colliding(*x, *y-1*2))
        	*y-=1;
    }
    else if (!(jpads.joy0 & J_UP) && *_dir == DIR_UP) *_dir = DIR_NULL;

    if (jpads.joy0 != NULL)
    	{move_sprite(0, *x, *y+8); move_sprite(1, *x+8, *y+8); walking(*_dir);}
    else return;
}

void setupPlayer(void)
{
	lizzie.x = 80;
	lizzie.y = 72;
	lizzie.width = 14;
	lizzie.height = 16;
	lizzie.canMove = true;
	lizzie.canAnimate = true;
	lizzie.dir = DIR_RIGHT;

	set_sprite_palette(0, 1, &lizzie_spr_palettes[0]);
	set_sprite_data(0, 4, &lizzie_spr_tiles[0]);
	set_sprite_tile(0, 0); set_sprite_tile(1, 2);
	// for (uint8_t i=8; i<40; i++) set_sprite_tile(i, 0x7F);
	move_sprite(0, lizzie.x, lizzie.y+8); move_sprite(1, lizzie.x+8, lizzie.y+8);
	walking(lizzie.dir);
}
