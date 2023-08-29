// lizzie.c

// #include <GB/gb.h>
// #include <stdio.h>
// #include <stdbool.h>

#include <gb/cgb.h>

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
#define appearvel 4

struct character lizzie;

// Define the Player color palette.
// UWORD PlayerPalette[4] = {RGB8(196, 207, 161), RGB8(139, 149, 109), RGB8(77, 83, 60), RGB8(31, 31, 31)};

int8_t dir, old_dir;
uint16_t timer, frame;
bool done = false;
bool showingDialog = false;
bool pressingA = false;
bool isColliding = false;

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
        isColliding = colliding(*x+1*7, *y+6) || colliding(*x+1*7, *y+4);
        if (!isColliding && !showingDialog)
        	*x+=1;
    }
    else if (!(jpads.joy0 & J_RIGHT) && *_dir == DIR_RIGHT) *_dir = DIR_NULL;

    if (jpads.joy0 & J_LEFT && !(jpads.joy0 & J_RIGHT))
    {
        if (*_dir == DIR_NULL) *_dir = DIR_LEFT;
        isColliding = colliding(*x-1*8, *y+6) || colliding(*x-1*8, *y+4);
        if (!isColliding && !showingDialog)
        	*x-=1;
    }
    else if (!(jpads.joy0 & J_LEFT) && *_dir == DIR_LEFT) *_dir = DIR_NULL;

    if (jpads.joy0 & J_DOWN && !(jpads.joy0 & J_UP))
    {
        if (*_dir == DIR_NULL) *_dir = DIR_DOWN;
        isColliding = colliding(*x+6, *y+1*8) || colliding(*x-7, *y+1*8);
        if (!isColliding && !showingDialog)
        	*y+=1;
    }
    else if (!(jpads.joy0 & J_DOWN) && *_dir == DIR_DOWN) *_dir = DIR_NULL;

    if (jpads.joy0 & J_UP && !(jpads.joy0 & J_DOWN))
    {
        if (*_dir == DIR_NULL) *_dir = DIR_UP;
        isColliding = colliding(*x+6, *y-1/2) || colliding(*x-7, *y-1/2);
        if (!isColliding && !showingDialog)
        	*y-=1;
    }
    else if (!(jpads.joy0 & J_UP) && *_dir == DIR_UP) *_dir = DIR_NULL;

    if (canInteract(*x-7, *y-1*4) && jpads.joy0 & J_A && pressingA == false)
    {
    	pressingA = true;
    	if (showingDialog == false)
    	{
    		showingDialog = true;
	    	for (uint8_t i=0; i<(48/appearvel); i++)
	    		{scroll_win(0, -appearvel); wait_vbl_done();}
    	}
    	else
    	{
    		showingDialog = false;
    		for (uint8_t i=0; i<(48/appearvel); i++)
	    		{scroll_win(0, appearvel); wait_vbl_done();}
	    }
	}
	if (pressingA == true && !(jpads.joy0 & J_A)) pressingA = false;

    if (jpads.joy0 != NULL && !showingDialog)
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
	lizzie.hearts = 3;
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
	for (uint8_t i=0; i<3; i++) set_sprite_tile(i+37, 0x7C);

	// Move Character's Sprites to initial position.
	move_sprite(0, lizzie.x, lizzie.y+8); move_sprite(1, lizzie.x+8, lizzie.y+8);

	// Move Hearts Sprites to its position.
	move_sprite(37, 8, 16); move_sprite(38, 13, 24); move_sprite(39, 18, 16);
	for (uint8_t i=0; i<3; i++) set_sprite_prop(i+37, 1);

	// Set the initial Character's Sprites according to it's initial direction.
	walking(lizzie.dir);
}
