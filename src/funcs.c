// funcs.c

#include <gb/gb.h>
#include <gb/cgb.h>
#include <gbdk/platform.h>
#include <stdbool.h>

#include "Maps/TestMap.h"

#include "inc/funcs.h"
#include "inc/lizzie.h"
#include "inc/setup.h"
#include "inc/main.h"
#include "inc/camera.h"

#define appearvel 4

// unsigned char *current=0;

bool showingDialog = false;

const unsigned char symbols[] =
{
    '!', '"', '#', '$', '%', '&', 39, '(', ')', '*', '+', ',', '-', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

// const unsigned char numbers[] = {};

const unsigned char text[] = "abc the text test no. 1";
const unsigned char funfact[] = "if you didn't know, you can talk to me if you press the a button, but you already know. the text test no. 2";
const unsigned char abc[] = "abcdefghijklmnopqrstvwxyz";

uint8_t solidTiles[] =
{
    0x00, 0x02, 0x03, 0x05,
    0x06, 0x07, 0x08, 0x09,
    0x0A, 0x0B, 0x0C, 0x0D,
    0x0E, 0x0F, 0x10, 0x11,
    0x16, 0x17, 0x18, 0x19
};

uint8_t objectTiles[] = {0x18, 0x19};

void VBL_isr(void) {hUGE_dosound();}

void play(const hUGESong_t Song)
{
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;

    __critical {hUGE_init(&Song);}
}

void show_dialog(uint16_t x, uint16_t y)
{
    if (canInteract(x-7, y-1*4))
    {
        if (showingDialog == false)
        {
            showingDialog = true;
            fill_win_rect(1, 1, 18, 4, 0x00);
            for (uint8_t i=0; i<(48/appearvel); i++)
                {scroll_win(0, -appearvel); wait_vbl_done();}

            if(*room[0]->x == 0) win_print(text, sizeof(text));
            else if (room[0]->x == 1) win_print(funfact, sizeof(funfact));
        }
        else
        {
            showingDialog = false;
            for (uint8_t i=0; i<(48/appearvel); i++)
                {scroll_win(0, appearvel); wait_vbl_done();}
        }
    }
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
bool colliding(int16_t x, int16_t y, bkgmap *load)
{
	// Divide the player's position by 8 to index it to a tile position.
	int16_t column = (camerax>>3)+(x>>3);
	int16_t row = (cameray>>3)+(y>>3);
    int16_t TileIndex = load->map[column + row * (TestMap_WIDTH>>3)];
    
    // Get the tile based on the index variable.
    for (uint8_t index=0; index<sizeof(solidTiles); index++)
    	if (TileIndex == solidTiles[index] && camerax >= (load->x*20) && cameray >= (load->y*18)) return true;
    return false;
}

bool canInteract(int16_t x, int16_t y)
{
	// Divide the player's position by 8 to index it to a tile position.
	int16_t column = (camerax>>3)+x/8;
	int16_t row = (cameray>>3)+y/8;
    int16_t TileIndex = TestMap_map[column + row * (TestMap_WIDTH>>3)];
    
    // Get the tile based on the index variable.
    for (uint8_t index=0; index<sizeof(objectTiles); index++)
    	if (TileIndex == objectTiles[index]) return true;
    return false;
}