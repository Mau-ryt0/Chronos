// lizzie.c

// #include <GB/gb.h>
// #include <stdio.h>
// #include <stdbool.h>

#include <gb/cgb.h>
#include <stdlib.h>

#include "Sprites/lizzie_spr.h"
#include "Sprites/Heart.h"

#include "Tiles/MapTiles.h"
#include "Tiles/DialogTiles.h"

#include "Maps/TestMap.h"
#include "Maps/Dialog.h"

#include "inc/lizzie.h"
#include "inc/setup.h"
#include "inc/funcs.h"
#include "inc/main.h"
#include "inc/camera.h"

// Defined in lizzie.h
// #define DIR_RIGHT 1
// #define DIR_LEFT -1
// #define DIR_DOWN 2
// #define DIR_UP -2
// #define DIR_NULL 0

// for (uint8_t i=8; i<40; i++) set_sprite_tile(i, 0x7F);

#define velocity 1

struct character lizzie;

// Define the Player color palette.
// UWORD PlayerPalette[4] = {RGB8(196, 207, 161), RGB8(139, 149, 109), RGB8(77, 83, 60), RGB8(31, 31, 31)};

int8_t dir, old_dir;
uint8_t timer, frame;
bool done = false;
bool pressingA = false;
bool pressingB = false;
bool isColliding = false;

void walking(void)
{
	timer = (old_dir != lizzie.dir)?0:timer;
	old_dir = lizzie.dir;

	switch (lizzie.dir)
	{
		case DIR_RIGHT:
			if (timer == 0) set_sprite_data(0, 4, &lizzie_spr_tiles[0]);
			else if (timer == 6) set_sprite_data(0, 4, &lizzie_spr_tiles[1*64]);
			else if (timer == 12) set_sprite_data(0, 4, &lizzie_spr_tiles[2*64]);
			else if (timer == 18) set_sprite_data(0, 4, &lizzie_spr_tiles[1*64]);
			break;

		case DIR_LEFT:
			if (timer == 0) set_sprite_data(0, 4, &lizzie_spr_tiles[3*64]);
			else if (timer == 6) set_sprite_data(0, 4, &lizzie_spr_tiles[4*64]);
			else if (timer == 12) set_sprite_data(0, 4, &lizzie_spr_tiles[5*64]);
			else if (timer == 18) set_sprite_data(0, 4, &lizzie_spr_tiles[4*64]);
			break;

		case DIR_DOWN:
			if (timer == 0) set_sprite_data(0, 4, &lizzie_spr_tiles[12*32]);
			else if (timer == 6) set_sprite_data(0, 4, &lizzie_spr_tiles[14*32]);
			else if (timer == 12) set_sprite_data(0, 4, &lizzie_spr_tiles[16*32]);
			else if (timer == 18) set_sprite_data(0, 4, &lizzie_spr_tiles[14*32]);
			break;

		case DIR_UP:
			if (timer == 0) set_sprite_data(0, 4, &lizzie_spr_tiles[18*32]);
			else if (timer == 6) set_sprite_data(0, 4, &lizzie_spr_tiles[20*32]);
			else if (timer == 12) set_sprite_data(0, 4, &lizzie_spr_tiles[22*32]);
			else if (timer == 18) set_sprite_data(0, 4, &lizzie_spr_tiles[20*32]);
			break;
	}
	timer = (timer > 24)?0:timer+1;
}

void inputs(int16_t *x, int16_t *y, int8_t *_dir)
{
    joypad_ex(&jpads);

	if (jpads.joy0 != NULL && !showingDialog)
		{move_sprite(0, *x, *y+8); move_sprite(1, *x+8, *y+8); walking();}

    // if ((joypads_t) == J_BUTTON) is incorrect. Character will not move in 8 directions.
    // Use if ((joypads_t) & J_BUTTON) instead to avoid problems.

    if (jpads.joy0 & J_RIGHT && !(jpads.joy0 & J_LEFT))
    {
        if (*_dir == DIR_NULL) *_dir = DIR_RIGHT;
        isColliding = colliding(*x+1*7, *y+7, currlvl.map) || colliding(*x+1*7, *y+1, currlvl.map);
        if (!isColliding && !showingDialog)
        	*x+=1;
    }
    else if (!(jpads.joy0 & J_RIGHT) && *_dir == DIR_RIGHT) *_dir = DIR_NULL;

    if (jpads.joy0 & J_LEFT && !(jpads.joy0 & J_RIGHT))
    {
        if (*_dir == DIR_NULL) *_dir = DIR_LEFT;
        isColliding = colliding(*x-1*8, *y+7, currlvl.map) || colliding(*x-1*8, *y+1, currlvl.map);
        if (!isColliding && !showingDialog)
        	*x-=1;
    }
    else if (!(jpads.joy0 & J_LEFT) && *_dir == DIR_LEFT) *_dir = DIR_NULL;

    if (jpads.joy0 & J_DOWN && !(jpads.joy0 & J_UP))
    {
        if (*_dir == DIR_NULL) *_dir = DIR_DOWN;
        isColliding = colliding(*x+6, *y+1*8, currlvl.map) || colliding(*x-7, *y+1*8, currlvl.map);
        if (!isColliding && !showingDialog)
        	*y+=1;
    }
    else if (!(jpads.joy0 & J_DOWN) && *_dir == DIR_DOWN) *_dir = DIR_NULL;

    if (jpads.joy0 & J_UP && !(jpads.joy0 & J_DOWN))
    {
        if (*_dir == DIR_NULL) *_dir = DIR_UP;
        isColliding = colliding(*x+6, *y-1/2, currlvl.map) || colliding(*x-7, *y-1/2, currlvl.map);
        if (!isColliding && !showingDialog)
        	*y-=1;
    }
    else if (!(jpads.joy0 & J_UP) && *_dir == DIR_UP) *_dir = DIR_NULL;

    if (jpads.joy0 & J_A && !pressingA)
    {
    	pressingA = true;
    	show_dialog(*x, *y);
	}
	else if (pressingA == true && !(jpads.joy0 & J_A)) pressingA = false;

	if (jpads.joy0 & J_B && !pressingB)
	{
		pressingB = true;
		// if (lizzie.hearts != 0 && !showingDialog) lizzie.hearts--;
	}
	else if (pressingB == true && !(jpads.joy0 & J_B)) pressingB = false;

	if (lizzie.old_hearts != lizzie.hearts)
	{
		lizzie.old_hearts = lizzie.hearts;
		for (uint8_t i=0; i<3; i++) set_sprite_tile(i+37, 0x7E);
		for (uint8_t i=0; i<lizzie.hearts; i++) set_sprite_tile(i+37, 0x7C);
	}
}

void setupPlayer(void)
{
	lizzie.x = 80;
	lizzie.y = 72;
	lizzie.width = 14;
	lizzie.height = 16;
	lizzie.canMove = true;
	lizzie.canAnimate = true;
	lizzie.hearts = 3;
	lizzie.old_hearts = lizzie.hearts;
	lizzie.dir = DIR_RIGHT;

	// Loads Character's Sprites.
	set_sprite_palette(0, 1, &lizzie_spr_palettes[0]);
	set_sprite_data(0, 4, &lizzie_spr_tiles[0]);

	// Loads Heart's Sprites.
	set_sprite_palette(1, 1, &Heart_palettes[0]);
	set_sprite_data(0x7C, 1,&Heart_tiles[0]);
	set_sprite_data(0x7E, 1,&Heart_tiles[2*8]);

	// Put Character's Sprites in OAM.
	set_sprite_tile(0, 0); set_sprite_tile(1, 2);

	// Put Heart Sprites in OAM.
	for (uint8_t i=0; i<lizzie.hearts; i++) set_sprite_tile(i+37, 0x7C);

	// Move Character's Sprites to initial position.
	move_sprite(0, lizzie.x, lizzie.y+8); move_sprite(1, lizzie.x+8, lizzie.y+8);

	// Move Hearts Sprites to its position.
	move_sprite(37, 9, 17); move_sprite(38, 14, 25); move_sprite(39, 19, 17);
	for (uint8_t i=0; i<3; i++) set_sprite_prop(i+37, 1);

	// Set the initial Character's Sprites according to it's initial direction.
	walking();
}
