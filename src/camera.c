// camera.c

#include <gb/gb.h>
#include <stdio.h>

#include "Maps/TestMap.h"
#include "Tiles/Tiles.h"

#include "inc/camera.h"
#include "inc/main.h"
#include "inc/lizzie.h"
#include "inc/setup.h"

//#define MIN(A,B) ((A)<(B)?(A):(B))

#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_DOWN 3
#define DIR_UP 4

#define SC_VEL 4

uint16_t camerax, cameray;

// The method to get the camera is that you load specific tiles.
// For that you should get the tile position in the tilemap, by dividing the Game Boy's background position into 8.
// It will give you a position in tiles, something that Game Boy can understand.
// This method should use set_bkg_based_submap(), because the first two parameters are used for both tile map position and Game Boy's Background position.
//static void updateMap(uint8_t dir, const unsigned char * MapPlane0, const unsigned char * MapPlane1, const uint8_t MapWidth, uint8_t base)
//{
//	MapPlane1;
//	switch(dir)
//	{
//		case DIR_RIGHT:
//			// Gets and puts the tiles of the tilemap in the up direction.
//			
//			break;
//		case DIR_LEFT:
//			// Gets and puts the tiles of the tilemap in the up direction.
//			
//			break;
//        case DIR_DOWN:
//        	// Gets and puts the tiles of the tilemap in the down direction.
//        	
//			break;
//        case DIR_UP:
//        	// Gets and puts the tiles of the tilemap in the up direction.
//        	// Note that isn't necesary to put "+ DEVICE_SCREEN_HEIGHT" because the tilemap is updating in the top of screen.
//			
//			break;
//		default: break;
//	}
//}

void scroll_sprites(uint8_t sprites, uint8_t direction, uint8_t vel)
{
	for (uint8_t i = 0; i < sprites; i++)
	{
		if (direction == DIR_RIGHT) scroll_sprite(i, vel, 0);
		else if (direction == DIR_LEFT) scroll_sprite(i, -vel, 0);
		else if (direction == DIR_DOWN) scroll_sprite(i, 0, vel);
		else if (direction == DIR_UP) scroll_sprite(i, 0, -vel);
	}
}

void camera(const unsigned char *map, const unsigned char *attr, const uint8_t MapWidth, const uint8_t MapHeight, uint8_t base)
{
	// Right scroll.
	if (lizzie.x > 168 && camerax < (MapWidth*4))
	{
		for (uint8_t i = 0; i < 160/SC_VEL; i++)
		{
			camerax += SC_VEL;
			if (camerax % 8 == 0) set_attributed_bkg_submap(camerax/8 - 1 + DEVICE_SCREEN_WIDTH, cameray/8, 1, 18, map, attr, MapWidth, base);
			wait_vbl_done();
			SCX_REG = camerax;
			lizzie.x -= SC_VEL; scroll_sprites(2, DIR_LEFT, SC_VEL);
		}
	}

	// Left scroll.
	if (lizzie.x < 8 && camerax > 0)
	{
		for (uint8_t i = 0; i < 160/SC_VEL; i++)
		{
			camerax -= SC_VEL;
			if (camerax % 8 == 0) set_attributed_bkg_submap(camerax/8, cameray/8, 1, 18, map, attr, MapWidth, base);
			wait_vbl_done();
			SCX_REG = camerax;
			lizzie.x += SC_VEL; scroll_sprites(2, DIR_RIGHT, SC_VEL);
		}
	}

	// Down scroll.
	if (lizzie.y > 152 && cameray < (MapHeight*4))
	{
		for (uint8_t i = 0; i < 144/SC_VEL; i++)
		{
			cameray += SC_VEL;
			if (cameray % 8 == 0) set_attributed_bkg_submap(camerax/8, (cameray/8)-1 + DEVICE_SCREEN_HEIGHT, 20, 1, map, attr, MapWidth, base);
			wait_vbl_done();
			SCY_REG = cameray;
			lizzie.y -= SC_VEL; scroll_sprites(4, DIR_UP, SC_VEL);
		}
	}

	//	Up scroll.
	if (lizzie.y < 8 && cameray > 0)
	{
		for (uint8_t i = 0; i < 144/SC_VEL; i++)
		{
			cameray -= SC_VEL;
			if (cameray % 8 == 0) set_attributed_bkg_submap(camerax/8, cameray/8, 20, 1, map, attr, MapWidth, base);
			wait_vbl_done();
			SCY_REG = cameray;
			lizzie.y += SC_VEL; scroll_sprites(4, DIR_DOWN, SC_VEL);
		}
	}
}
