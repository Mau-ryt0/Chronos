// lizzie.c

// #include <GB/gb.h>
// #include <stdio.h>
// #include <stdbool.h>

#include <gb/cgb.h>

#include "Sprites/lizzie_spr.h"
#include "Maps/TestMap.h"

#include "inc/lizzie.h"
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

//Define the Player color palette.
UWORD PlayerPalette[4] = {RGB8(196, 207, 161), RGB8(139, 149, 109), RGB8(77, 83, 60), RGB8(31, 31, 31)};

uint8_t dir, old_dir;
uint16_t timer, frame;
// bool done, done1;

/* bool canMove(uint16_t x, uint16_t y)
{
    uint16_t MapIndex = (x >> 3) + ((y >> 3) * 20) - 40;
    uint16_t Tile = Map[MapIndex];
    
    if (Tile == EmptyTile[0]) return true;

    return false;
}*/

bool canMove(uint16_t PosX, uint16_t PosY)
{
	// Divide the player's position by 8 to translate it to a tile position.
    uint16_t MapIndex = TestMap_WIDTH * ((camerax<<3)+(PosX-1)/8) + ((cameray<<3)+(PosY-1)/8);
    
    if (TestMap_map[MapIndex] == 0x0A || TestMap_map[MapIndex] == 0x2E) return false;
    return true;
}

void walking(uint8_t dir)
{
	if (old_dir != dir) {timer = frame = 0; old_dir = dir;}
	
	else if (dir == DIR_RIGHT || dir == DIR_LEFT)
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
	
	switch (frame)
	{
		case 0:
				if (dir == DIR_RIGHT || dir == DIR_LEFT) set_sprite_data(0, 4, &lizzie_spr_tiles[0]);
				else if (dir == DIR_DOWN) set_sprite_data(0, 4, &lizzie_spr_tiles[6*32]);
				else if (dir == DIR_UP) set_sprite_data(0, 4, &lizzie_spr_tiles[12*32]);
			break;
		case 1:
				if (dir == DIR_RIGHT || dir == DIR_LEFT) set_sprite_data(0, 4, &lizzie_spr_tiles[2*32]);
				else if (dir == DIR_DOWN) set_sprite_data(0, 4, &lizzie_spr_tiles[8*32]);
				else if (dir == DIR_UP) set_sprite_data(0, 4, &lizzie_spr_tiles[14*32]);
			break;
		case 2:
				if (dir == DIR_RIGHT || dir == DIR_LEFT) set_sprite_data(0, 4, &lizzie_spr_tiles[4*32]);
				else if (dir == DIR_DOWN) set_sprite_data(0, 4, &lizzie_spr_tiles[10*32]);
				else if (dir == DIR_UP) set_sprite_data(0, 4, &lizzie_spr_tiles[16*32]);
			break;
		case 3:
				if (dir == DIR_RIGHT || dir == DIR_LEFT) set_sprite_data(0, 4, &lizzie_spr_tiles[2*32]);
				else if (dir == DIR_DOWN) set_sprite_data(0, 4, &lizzie_spr_tiles[8*32]);
				else if (dir == DIR_UP) set_sprite_data(0, 4, &lizzie_spr_tiles[14*32]);
			break;
	}
	timer++;
}

void mv_spr(uint8_t x, uint8_t y, uint8_t dir)
{
	if (dir == DIR_RIGHT)
	{
		for (uint8_t i=0; i<2; i++) set_sprite_prop(i, 0);
		move_sprite(0, x-8, y); move_sprite(1, x, y);

		walking(dir);
	}
	else if (dir == DIR_LEFT)
	{
		for (uint8_t i=0; i<2; i++) set_sprite_prop(i, S_FLIPX);
		move_sprite(0, x, y); move_sprite(1, x-8, y);

		walking(dir);
	}

	if (dir == DIR_DOWN)
	{
		for (uint8_t i=0; i<2; i++) set_sprite_prop(i, 0);
		move_sprite(0, x-8, y); move_sprite(1, x, y);

		walking(dir);
	}
	else if (dir == DIR_UP)
	{
		for (uint8_t i=0; i<2; i++) set_sprite_prop(i, 0);
		move_sprite(0, x-8, y); move_sprite(1, x, y);

		walking(dir);
	}
}

void setupPlayer()
{
	lizzie.x = 88;
	lizzie.y = 72;
	lizzie.width = 14;
	lizzie.height = 16;
	lizzie.canMove = true;
	lizzie.canAnimate = true;
	lizzie.dir = DIR_RIGHT;

	set_sprite_data(0, 4, &lizzie_spr_tiles[0]);
	set_sprite_tile(0, 0); set_sprite_tile(1, 2);
	for (uint8_t i=8; i<40; i++) set_sprite_tile(i, 0x7F);
	set_sprite_palette(0, 1, &PlayerPalette[0]);
	mv_spr(lizzie.x, lizzie.y, lizzie.dir);
}
