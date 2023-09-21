// player.c

#include <gb/cgb.h>
#include <stdlib.h>

#include "Sprites/lizzie_spr.h"
#include "UI/Heart.h"

#include "Tiles/DialogTiles.h"

#include "inc/structs.h"

#include "inc/funcs.h"
#include "inc/camera.h" 

// Defined in structs.h
// #define DIR_RIGHT 1
// #define DIR_LEFT -1
// #define DIR_DOWN 2
// #define DIR_UP -2
// #define DIR_NULL 0

#define velocity 1

uint8_t timer;

bool done = false;
bool pressingA = false;
bool pressingB = false;
bool isColliding = false;

void walking(void)
{
	timer = (player.old_dir != player.dir)?0:timer;
	player.old_dir = player.dir;

	switch (player.dir)
	{
		case DIR_RIGHT:
			if (timer == 0)
				set_sprite_data(0, 4, lizzie_r_frame_1);
			else if (timer == 8)
				set_sprite_data(0, 4, lizzie_r_frame_2);
			else if (timer == 16)
				set_sprite_data(0, 4, lizzie_r_frame_3);
			else if (timer == 24)
				set_sprite_data(0, 4, lizzie_r_frame_2);
			break;

		case DIR_LEFT:
			if (timer == 0)
				set_sprite_data(0, 4, lizzie_l_frame_1);
			else if (timer == 8)
				set_sprite_data(0, 4, lizzie_l_frame_2);
			else if (timer == 16)
				set_sprite_data(0, 4, lizzie_l_frame_3);
			else if (timer == 24)
				set_sprite_data(0, 4, lizzie_l_frame_2);
			break;

		case DIR_DOWN:
			if (timer == 0)
				set_sprite_data(0, 4, lizzie_d_frame_1);
			else if (timer == 6)
				set_sprite_data(0, 4, lizzie_d_frame_2);
			else if (timer == 12)
				set_sprite_data(0, 4, lizzie_d_frame_3);
			else if (timer == 18)
				set_sprite_data(0, 4, lizzie_d_frame_2);
			break;

		case DIR_UP:
			if (timer == 0)
				set_sprite_data(0, 4, lizzie_u_frame_1);
			else if (timer == 6)
				set_sprite_data(0, 4, lizzie_u_frame_2);
			else if (timer == 12)
				set_sprite_data(0, 4, lizzie_u_frame_3);
			else if (timer == 18)
				set_sprite_data(0, 4, lizzie_u_frame_2);
			break;
	}
	timer = (player.dir == DIR_RIGHT || player.dir == DIR_LEFT)?
			(timer > 32)?0:timer+1:
			(timer > 24)?0:timer+1;
}

void inputs(int16_t *x, int16_t *y, int8_t *_dir)
{
    joypad_ex(&jpads);

    // if ((joypads_t) == J_BUTTON) is incorrect. Character will not move in 8 directions.
    // Use if ((joypads_t) & J_BUTTON) instead to avoid problems.

	// Right movement.
    if (jpads.joy0 & J_RIGHT && !(jpads.joy0 & J_LEFT))
    {
        if (*_dir == DIR_NULL) *_dir = DIR_RIGHT;

        isColliding =
        	colliding((*x+1*7)>>3, (*y+7)>>3, currlvl.map) ||
        	colliding((*x+1*7)>>3, (*y+1)>>3, currlvl.map);

        if (!isColliding && !showingDialog && (*x+7) != currlvl.width)
        	*x+=1;
    }
    else if (!(jpads.joy0 & J_RIGHT) && *_dir == DIR_RIGHT) *_dir = DIR_NULL;

    // Left movement.
    if (jpads.joy0 & J_LEFT && !(jpads.joy0 & J_RIGHT))
    {
        if (*_dir == DIR_NULL) *_dir = DIR_LEFT;

        isColliding =
        	colliding((*x-1*8)>>3, (*y+7)>>3, currlvl.map) ||
        	colliding((*x-1*8)>>3, (*y+1)>>3, currlvl.map);

        if (!isColliding && !showingDialog)
       		*x-=1;
    }
    else if (!(jpads.joy0 & J_LEFT) && *_dir == DIR_LEFT) *_dir = DIR_NULL;

    // Down movement.
    if (jpads.joy0 & J_DOWN && !(jpads.joy0 & J_UP))
    {
        if (*_dir == DIR_NULL) *_dir = DIR_DOWN;

        isColliding =
        	colliding((*x+6)>>3, (*y+1*8)>>3, currlvl.map) ||
        	colliding((*x-7)>>3, (*y+1*8)>>3, currlvl.map);

        if (!isColliding && !showingDialog && (*y+8) != currlvl.height)
        	*y+=1;
    }
    else if (!(jpads.joy0 & J_DOWN) && *_dir == DIR_DOWN) *_dir = DIR_NULL;

    // Up movement.
    if (jpads.joy0 & J_UP && !(jpads.joy0 & J_DOWN))
    {
        if (*_dir == DIR_NULL) *_dir = DIR_UP;
        isColliding = colliding((*x+6)>>3, (*y-1/2)>>3, currlvl.map) || colliding((*x-7)>>3, (*y-1/2)>>3, currlvl.map);
        if (!isColliding && !showingDialog)
       		*y-=1;
    }
    else if (!(jpads.joy0 & J_UP) && *_dir == DIR_UP) *_dir = DIR_NULL;

    // Detects interactions, other functionality is pending.
    if (jpads.joy0 & J_A && !pressingA)
    {
    	pressingA = true;
    	show_dialog(*x, *y);
    	// load_lvl = 1;
	}
	else if (pressingA == true && !(jpads.joy0 & J_A)) pressingA = false;

	// It's just for test.
	if (jpads.joy0 & J_B && !pressingB)
	{
		pressingB = true;
		ENABLE_RAM_MBC1;
		load_lvl = (load_lvl == 0 && !showingDialog)?1:0;
		DISABLE_RAM_MBC1;
		// if (player.hearts != 0 && !showingDialog) player.hearts--;
	}
	else if (pressingB == true && !(jpads.joy0 & J_B)) pressingB = false;

	// Do the hearts status stuff.
	/* Unused by the moment.
	if (player.old_hearts != player.hearts)
	{
		player.old_hearts = player.hearts;
		for (uint8_t i=0; i<3; i++) set_sprite_tile(i+37, 0x7E);
		for (uint8_t i=0; i<player.hearts; i++) set_sprite_tile(i+37, 0x7C);
	}*/

	// Do the animations and movement stuff.
	if (jpads.joy0 != NULL && !showingDialog)
		{move_sprite(0, *x, *y+8); move_sprite(1, *x+8, *y+8); walking();}
}
