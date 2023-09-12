// camera.c

#include <gb/gb.h>
#include <stdio.h>

#include "Maps/TestMap.h"

#include "inc/camera.h"
#include "inc/main.h"
#include "inc/funcs.h"
#include "inc/lizzie.h"
#include "inc/setup.h"

// Defined in lizzie.h
// #define DIR_RIGHT 1
// #define DIR_LEFT -1
// #define DIR_DOWN 2
// #define DIR_UP -2
// #define DIR_NULL 0

#define SC_VEL 4

uint16_t camerax, cameray;

// The method to get the camera is that you load specific tiles.
// For that you should get the tile position in the tilemap, by dividing the Game Boy's background position by 8.
// It will give you a position in tiles, something that the Game Boy can understand.
// This method should use set_bkg_based_submap(), because the first two parameters are used for both tile map position and Game Boy's Background position.
void camera(const uint16_t MapWidth, uint8_t base)
{
	// Right scroll.
	if (lizzie.x > 166)
	{
		currlvl.x++;
		for (uint8_t i = 0; i < 160/SC_VEL; i++)
		{
			camerax += SC_VEL;
			if (camerax % 8 == 0) set_attributed_bkg_submap(((camerax>>3)-1) + DEVICE_SCREEN_WIDTH, (cameray>>3), 1, 18, currlvl.map, currlvl.attr, MapWidth, base);
			wait_vbl_done();
			SCX_REG = camerax;
			lizzie.x -= SC_VEL; scroll_sprites(2, DIR_LEFT, SC_VEL);
		}
	}

	// Left scroll.
	if (lizzie.x <= -6)
	{
		currlvl.x--;
		for (uint8_t i = 0; i < 160/SC_VEL; i++)
		{
			camerax -= SC_VEL;
			if (camerax % 8 == 0) set_attributed_bkg_submap(camerax>>3, cameray>>3, 1, 18, currlvl.map, currlvl.attr, MapWidth, base);
			wait_vbl_done();
			SCX_REG = camerax;
			lizzie.x += SC_VEL; scroll_sprites(2, DIR_RIGHT, SC_VEL);
		}
	}

	// Down scroll.
	if (lizzie.y > 144)
	{
		currlvl.y++;
		for (uint8_t i = 0; i < 144/SC_VEL; i++)
		{
			cameray += SC_VEL;
			if (cameray % 8 == 0) set_attributed_bkg_submap(camerax>>3, (cameray>>3)-1 + DEVICE_SCREEN_HEIGHT, 20, 1, currlvl.map, currlvl.attr, MapWidth, base);
			wait_vbl_done();
			SCY_REG = cameray;
			lizzie.y -= SC_VEL; scroll_sprites(4, DIR_UP, SC_VEL);
		}
	}

	//	Up scroll.
	if (lizzie.y <= 0)
	{
		currlvl.y--;
		for (uint8_t i = 0; i < 144/SC_VEL; i++)
		{
			cameray -= SC_VEL;
			// Note that isn't necesary to put "+ DEVICE_SCREEN_HEIGHT" because the tilemap is updating in the top of screen.
			if (cameray % 8 == 0) set_attributed_bkg_submap(camerax>>3, cameray>>3, 20, 1, currlvl.map, currlvl.attr, MapWidth, base);
			wait_vbl_done();
			SCY_REG = cameray;
			lizzie.y += SC_VEL; scroll_sprites(4, DIR_DOWN, SC_VEL);
		}
	}
}
