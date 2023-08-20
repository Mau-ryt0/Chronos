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
// #define DIR_LEFT 2
// #define DIR_DOWN 3
// #define DIR_UP 4
// #define DIR_NULL 0

#define velocity 1

struct character lizzie;

// Define the Player color palette.
// UWORD PlayerPalette[4] = {RGB8(196, 207, 161), RGB8(139, 149, 109), RGB8(77, 83, 60), RGB8(31, 31, 31)};

uint8_t dir, old_dir;
uint16_t timer, frame;
bool done = false;

bool colliding(uint8_t x, uint8_t y)
{
	// Divide the player's position by 8 to index it to a tile position.
	uint16_t xa = ((camerax<<3) + x-7)/8;
	uint16_t ya = ((cameray<<3) + y-15)/8;
    uint16_t TileIndex = TestMap_map[TestMap_WIDTH * (xa + ya)];
    
    // Get the tile based on the index variable.
    return TileIndex == 0x00?false:true;
}

void walking(uint8_t dir)
{
	if (old_dir != dir) {timer = frame = 0; old_dir = dir;}
	
	if (dir == DIR_RIGHT || dir == DIR_LEFT)
	{
		if (timer > 8)
		{
			if (frame < 3) frame++;
			else frame = 0;
			timer = 0;
		}
	}
	else if (dir == DIR_DOWN || dir == DIR_UP)
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
				if (dir == DIR_RIGHT && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[0]);
				else if (dir == DIR_LEFT && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[6*32]);
				else if (dir == DIR_DOWN && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[12*32]);
				else if (dir == DIR_UP && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[18*32]);
			break;
		case 1:
				if (dir == DIR_RIGHT && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[2*32]);
				else if (dir == DIR_LEFT && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[8*32]);
				else if (dir == DIR_DOWN && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[14*32]);
				else if (dir == DIR_UP && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[20*32]);
			break;
		case 2:
				if (dir == DIR_RIGHT && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[4*32]);
				else if (dir == DIR_LEFT && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[10*32]);
				else if (dir == DIR_DOWN && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[16*32]);
				else if (dir == DIR_UP && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[22*32]);
			break;
		case 3:
				if (dir == DIR_RIGHT && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[2*32]);
				else if (dir == DIR_LEFT && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[8*32]);
				else if (dir == DIR_DOWN && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[14*32]);
				else if (dir == DIR_UP && done == false) set_sprite_data(0, 4, &lizzie_spr_tiles[20*32]);
			break;
	}
	timer++;
}

void inputs(uint8_t *x, uint8_t *y, uint8_t *dir)
{
    joypad_ex(&jpads);

    // if ((joypads_t) == J_BUTTON) is incorrect. Character will not move in 8 directions.
    // Use if ((joypads_t) & J_BUTTON) instead to avoid problems.

    if (jpads.joy0 & J_RIGHT && !(jpads.joy0 & J_LEFT))
    {
        if (*dir == DIR_NULL) *dir = DIR_RIGHT;
        if (colliding(*x-15, *y) == true)
        	*x+=1;
    }
    else if (!(jpads.joy0 & J_RIGHT) && *dir == DIR_RIGHT) *dir = DIR_NULL;

    if (jpads.joy0 & J_LEFT && !(jpads.joy0 & J_RIGHT))
    {
        if (*dir == DIR_NULL) *dir = DIR_LEFT;
        if (colliding(*x+128, *y) == true)
        	*x-=1;
    }
    else if (!(jpads.joy0 & J_LEFT) && *dir == DIR_LEFT) *dir = DIR_NULL;

    if (jpads.joy0 & J_DOWN && !(jpads.joy0 & J_UP))
    {
        if (*dir == DIR_NULL) *dir = DIR_DOWN;
        if (colliding(*x, *y-1) == true)
        	*y+=1;
    }
    else if (!(jpads.joy0 & J_DOWN) && *dir == DIR_DOWN) *dir = DIR_NULL;

    if (jpads.joy0 & J_UP && !(jpads.joy0 & J_DOWN))
    {
        if (*dir == DIR_NULL) *dir = DIR_UP;
        if (colliding(*x, *y+1) == true)
        	*y-=1;
    }
    else if (!(jpads.joy0 & J_UP) && *dir == DIR_UP) *dir = DIR_NULL;

    if (jpads.joy0 != NULL)
    	{move_sprite(0, *x-8, *y-8); move_sprite(1, *x, *y-8); walking(*dir);}
    else return;
}

void setupPlayer(void)
{
	lizzie.x = 88;
	lizzie.y = 88;
	lizzie.width = 14;
	lizzie.height = 16;
	lizzie.canMove = true;
	lizzie.canAnimate = true;
	lizzie.dir = DIR_RIGHT;

	set_sprite_palette(0, 1, &lizzie_spr_palettes[0]);
	set_sprite_data(0, 4, &lizzie_spr_tiles[0]);
	set_sprite_tile(0, 0); set_sprite_tile(1, 2);
	// for (uint8_t i=8; i<40; i++) set_sprite_tile(i, 0x7F);
	move_sprite(0, lizzie.x-8, lizzie.y-8); move_sprite(1, lizzie.x, lizzie.y-8);
	walking(lizzie.dir);
}
