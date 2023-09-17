// funcs.c

#include <gb/gb.h>
#include <gb/cgb.h>
#include <gbdk/platform.h>
#include <stdbool.h>

// Remove and change to currlvl.maps.
#include "Maps/TestMap.h"

#include "inc/structs.h"

#include "inc/funcs.h"
#include "inc/setup.h"
#include "inc/camera.h"

#include "inc/hUGEDriver.h"

#define appearvel 4

bool showingDialog = false;

const unsigned char text[] = "abc the text test no. 1";
const unsigned char funfact[] = "if you didn't know, you can talk to me if you press the a button, but you already know. the text test no. 2";
const unsigned char abc[] = "abcdefghijklmnopqrstvwxyz";

void VBL_isr(void) {hUGE_dosound();}

void play(const hUGESong_t *Song)
{
	NR52_REG = 0x80;
	NR51_REG = 0xFF;
	NR50_REG = vol_7;

	__critical {hUGE_init(Song);}
}

void scroll_sprites(uint8_t sprites, int8_t _dir, uint8_t vel)
{
	for (uint8_t i = 0; i < sprites; i++)
	{
		if (_dir == DIR_RIGHT) scroll_sprite(i, vel, 0);
		else if (_dir == DIR_LEFT) scroll_sprite(i, -vel, 0);
		else if (_dir == DIR_DOWN) scroll_sprite(i, 0, vel);
		else if (_dir == DIR_UP) scroll_sprite(i, 0, -vel);
	}
}

// Function thanks to Larold's Jubilant Junkyard.
// https://github.com/LaroldsJubilantJunkyard/gbdk-tilemap-collision
bool colliding(uint8_t x, uint8_t y, const unsigned char *map)
{
	// Divide the player's position by 8 to index it to a tile position.
	uint8_t TileIndex = map [
        ((camerax>>3)+x) + ((cameray>>3)+y) * (currlvl.width>>3)
    ];
	
	uint8_t index=0;

	// Get the tile based on the index variable.
	while (index<27)
	{
		if (TileIndex == currlvl.solids[index]) return true;
		else index++;
	}
	return false;
}

bool canInteract(uint8_t x, uint8_t y, const unsigned char *map)
{
	// Divide the player's position by 8 to index it to a tile position.
	uint8_t TileIndex = map [
        ((camerax>>3)+x) + ((cameray>>3)+y) * (currlvl.width>>3)
    ];

	uint8_t index=0;

    // Get the tile based on the index variable.
    while (index<3)
    {
        if (TileIndex == currlvl.objects[index]) return true;
        else index++;
    }
	return false;
}

void win_print(unsigned char *text, uint8_t size)
{
	uint8_t xpos=0, ypos=0;
	uint8_t index=0;
	
	while (index<(size-1))
	{
		if (xpos % 18 == 0) {xpos=1; ypos++;}
		else xpos++;

		(xpos == 1 && text[index] == ' ')?index++:index;
		if (xpos == 18 && text[index] != ' '
			&& text[index+1] != ' ') // This line is optional. Just remember to close the brackets.
			{set_win_tile_xy(xpos, ypos, ('-'-0x20)); xpos=1; ypos++;}

		const unsigned char *current = &text[index];

		if (ypos > 4)
			{waitpad(J_A); fill_win_rect(1, 1, 18, 4, 0x00); xpos=1; ypos=1;}

		if (*current != ' ') set_win_tile_xy(xpos, ypos, (*current-0x47));

		for (uint8_t i=0; i<(sizeof(symbols)); i++)
			if (*current == symbols[i]) set_win_tile_xy(xpos, ypos, (*current-0x20));

		if (!(jpads.joy0 & J_B)) vblankDelay(textvel2);

		index++;
	}
}

void show_dialog(uint8_t x, uint8_t y)
{
	if (canInteract((x-7)>>3, (y-1*4)>>3, currlvl.map))
	{
		if (showingDialog == false)
		{
			showingDialog = true;
			fill_win_rect(1, 1, 18, 4, 0x00);
			for (uint8_t i=0; i<(48/appearvel); i++)
				{scroll_win(0, -appearvel); wait_vbl_done();}

			if(currlvl.x == 0) win_print(text, sizeof(text));
			else if (currlvl.x == 1) win_print(funfact, sizeof(funfact));
		}
		else
		{
			showingDialog = false;
			for (uint8_t i=0; i<(48/appearvel); i++)
				{scroll_win(0, appearvel); wait_vbl_done();}
		}
	}
}
