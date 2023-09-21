// setup.h

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include <gbdk/emu_debug.h>

#include "inc/structs.h"

#include "inc/lizzie.h"
#include "inc/funcs.h"
#include "inc/camera.h"
#include "inc/gfx.h"
#include "inc/main.h"

#include "Tiles/MapTiles.h"
#include "Tiles/DialogTiles.h"

#include "Sprites/Glitters.h"

#include "UI/Font.h"
#include "UI/Dialog.h"

#include "Ost/hUGEDriver.h"

// Defined in structs.h
// #define Map_base 0x24

// const int8_t waterfx[] = {1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1};

void setupBkg(void)
{
    BGP_REG=0b11111111;
    // Set the Background, map and camera position.
    SCX_REG = camera.x = (currlvl.x*20)<<3, SCY_REG = camera.y = (currlvl.y*18)<<3;

    // Set the map.
    set_bkg_data(Map_base, currlvl.tile_count, currlvl.tile_data);
    set_attributed_bkg_submap((camera.x)>>3, (camera.y)>>3, 20, 18, currlvl.map, currlvl.attr, currlvl.width, Map_base);

    SHOW_BKG;
}

void setupSprites(void)
{
    // Loads Character's Sprites and palette.
    set_sprite_data(0, 4, lizzie_r_frame_1);
    set_sprite_palette(0, 1, lizzie_p);

    // Put Character's Sprites in OAM.
    set_sprite_tile(0, 0); set_sprite_tile(1, 2);

    // Move Character's Sprites to initial position.
    move_sprite(0, player.x, player.y+8); move_sprite(1, player.x+8, player.y+8);

    OBP0_REG=0b10010000;

    SPRITES_8x16;
    SHOW_SPRITES;
}

void setupUI(void)
{
    // Loads Heart's Sprites and palette.
    set_sprite_data(0x7D, 1, heart_t);
    set_sprite_palette(1, 1, heart_p);

    // Put Heart Sprites in OAM.
    for (uint8_t i=0; i<player.hearts; i++) set_sprite_tile(i+2, 0x7D);

    // Move Hearts Sprites to its position.
    move_sprite(2, 9, 9); move_sprite(3, 14, 17); move_sprite(4, 19, 9);

    /* Sprites properties */
    // Put Hearts in OBP1 (if CPU == DMG).
    if (_cpu != CGB_TYPE)
    {
        OBP1_REG=0b11100100;
        for (uint8_t i=2; i<5; i++) set_sprite_prop(i, 0b00010000);
    } // if CPU == CGB put a color palette.
    else for (uint8_t i=2; i<5; i++) set_sprite_prop(i, 0b00000001);

    // Set window position.
    WY_REG = 144, WX_REG = 7;

    // Set the font.
    set_bkg_data(0x00, sizeof(Font_tiles)>>4, Font_tiles);

    // Set the base tile of the dialog.
    const uint8_t Dialog_base = (currlvl.tile_count)+Map_base;

    // Set the dialog tiles and map.
    set_bkg_data(Dialog_base, sizeof(DialogTiles_tiles)>>4, DialogTiles_tiles);
    set_win_based_tiles(0, 0, 20, 6, Dialog_map, Dialog_base);

    SHOW_WIN;
}

void setupMusic(void)
{
    // Set interrupts.
    CRITICAL \
        add_VBL(&hUGEisr);
    set_interrupts(IE_REG | VBL_IFLAG);

    // Play the current level song.
    play(currlvl.song);
}

void setup(void)
{
    setupBkg();
    setupMusic();
    setupSprites();
    setupUI();

    /* WARNING! */
    // The next line SHOULDN'T be before the setupMusic(); call or the game will crash.
    (_cpu == CGB_TYPE)?cfadein(currlvl.palette_dark, currlvl.palettes):fadein();
}

void changelvl(void)
{
    // Fade and hide background.
    (_cpu == CGB_TYPE)?cfadeout(currlvl.palettes, currlvl.palette_dark):fadeout();
    HIDE_BKG;

    // Shut down music.
    NR51_REG = NR52_REG = 0x00;

    CRITICAL \
        remove_VBL(&hUGEisr);
    set_interrupts(IE_REG & ~VBL_IFLAG);

    // Setup new level.
    currlvl = levels[load_lvl];

    setupBkg();
    setupSprites();
    setupMusic();

    /* WARNING! */
    // The next line SHOULDN'T be before the setupMusic(); call or the game will crash.
    (_cpu == CGB_TYPE)?cfadein(currlvl.palette_dark, currlvl.palettes):fadein();
}

void mainloop(void)
{
    while(true)
	{
		(player.x > 166 || player.x < -6 || player.y > 144 || player.y == 0)?
            camera_proc(Map_base):
            inputs(&player.x, &player.y, &player.dir);

		(load_lvl != currlvl.lvl_num)?changelvl():vsync();
	}
}
