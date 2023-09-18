// camera.c

#include <gb/gb.h>
#include <stdio.h>

#include "Maps/TestMap.h"

#include "inc/structs.h"

#include "inc/camera.h"
#include "inc/funcs.h"

// Defined in structs.h
// #define DIR_RIGHT 1
// #define DIR_LEFT -1
// #define DIR_DOWN 2
// #define DIR_UP -2
// #define DIR_NULL 0

#define SC_VEL 4

camera_t camera;

// The method to get the camera is that you load specific tiles.
// For that you should get the tile position in the tilemap, by dividing the Game Boy's background position by 8.
// It will give you a position in tiles, something that the Game Boy can understand.
// This method should use set_bkg_based_submap(), because the first two parameters are used for both tile map position and Game Boy's Background position.
void camera_proc(const uint16_t MapWidth, uint8_t base)
{
	// Right scroll.
	if (player.x > 166)
	{
		currlvl.x++;
		for (uint8_t i = 0; i < 160/SC_VEL; i++)
		{
			camera.x += SC_VEL;
			if (camera.x % 8 == 0) set_attributed_bkg_submap(((camera.x>>3)-1) + DEVICE_SCREEN_WIDTH, (camera.y>>3), 1, 18, currlvl.map, currlvl.attr, MapWidth, base);
			wait_vbl_done();
			SCX_REG = camera.x;
			player.x -= SC_VEL; scroll_sprites(2, DIR_LEFT, SC_VEL);
		}
	}

	// Left scroll.
	if (player.x <= -6)
	{
		currlvl.x--;
		for (uint8_t i = 0; i < 160/SC_VEL; i++)
		{
			camera.x -= SC_VEL;
			if (camera.x % 8 == 0) set_attributed_bkg_submap(camera.x>>3, camera.y>>3, 1, 18, currlvl.map, currlvl.attr, MapWidth, base);
			wait_vbl_done();
			SCX_REG = camera.x;
			player.x += SC_VEL; scroll_sprites(2, DIR_RIGHT, SC_VEL);
		}
	}

	// Down scroll.
	if (player.y > 144)
	{
		currlvl.y++;
		for (uint8_t i = 0; i < 144/SC_VEL; i++)
		{
			camera.y += SC_VEL;
			if (camera.y % 8 == 0) set_attributed_bkg_submap(camera.x>>3, (camera.y>>3)-1 + DEVICE_SCREEN_HEIGHT, 20, 1, currlvl.map, currlvl.attr, MapWidth, base);
			wait_vbl_done();
			SCY_REG = camera.y;
			player.y -= SC_VEL; scroll_sprites(2, DIR_UP, SC_VEL);
		}
	}

	//	Up scroll.
	if (player.y <= 0)
	{
		currlvl.y--;
		for (uint8_t i = 0; i < 144/SC_VEL; i++)
		{
			camera.y -= SC_VEL;
			// Note that isn't necesary to put "+ DEVICE_SCREEN_HEIGHT" because the tilemap is updating in the top of screen.
			if (camera.y % 8 == 0) set_attributed_bkg_submap(camera.x>>3, camera.y>>3, 20, 1, currlvl.map, currlvl.attr, MapWidth, base);
			wait_vbl_done();
			SCY_REG = camera.y;
			player.y += SC_VEL; scroll_sprites(2, DIR_DOWN, SC_VEL);
		}
	}
}
