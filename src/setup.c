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

#include "inc/hUGEDriver.h"

// Defined in structs.h
// #define Map_base 0x24

// const int8_t waterfx[] = {1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1};

joypads_t jpads;

void setup(void)
{
	CRITICAL {add_VBL(&VBL_isr);}
	set_interrupts(IE_REG | VBL_IFLAG);

	joypad_init(1, &jpads);

	wait_vbl_done();

	currlvl = levels[load_lvl];

	WY_REG = 144, WX_REG = 7;
	SCX_REG = camerax = (currlvl.x), SCY_REG = cameray = (currlvl.y);

	const uint8_t Dialog_base = (currlvl.tile_count)+Map_base;

	set_bkg_data(0x00, sizeof(Font_tiles)>>4, Font_tiles);
	set_bkg_data(Map_base, currlvl.tile_count, currlvl.tile_data);
	set_bkg_data(Dialog_base, sizeof(DialogTiles_tiles)>>4, DialogTiles_tiles);

	set_attributed_bkg_submap(camerax, cameray, 20, 18, currlvl.map, currlvl.attr, currlvl.width, Map_base);
	set_win_based_tiles(0, 0, 20, 6, Dialog_map, Dialog_base);
	setupPlayer();

    /*if (currlvl.lvl_num == 1)
    {
        set_sprite_data(0x70, 2, &Glitters_tiles[0]);
        for (uint8_t i=2; i<18; i++) set_sprite_tile(i, 0x70);
        for (uint8_t i=2; i<18; i++) move_sprite(i, 32, 32);
    }*/

    OBP0_REG=0b10010000;

	SPRITES_8x16;
	SHOW_BKG;
	SHOW_WIN;
	SHOW_SPRITES;

    if (_cpu == CGB_TYPE) set_bkg_palette(0, 2, currlvl.palettes);
    else fadein();

	play(currlvl.song);
}

void mainloop(void)
{
    // uint8_t wfx_i=0;
    while(true)
	{
		inputs(&player.x, &player.y, &player.dir);
        /*if (currlvl.lvl_num == 1)
        {
            wfx_i = (wfx_i<sizeof(waterfx))?wfx_i+1:0;
            for (uint8_t spr_i=2; spr_i<18; spr_i++)
                scroll_sprite(spr_i, waterfx[wfx_i], 0);
        }*/

		if (player.x > 166 || player.x < -6 || player.y > 144 || player.y == 0)
			camera(currlvl.width, Map_base);
		else vsync();
		if (load_lvl != currlvl.lvl_num)
		{
            if (_cpu != CGB_TYPE) fadeout();

			CRITICAL
				{remove_VBL(&VBL_isr);}
			set_interrupts(IE_REG & ~VBL_IFLAG);

            NR52_REG = 0x00;
            NR51_REG = 0x00;

            HIDE_BKG;

			main();
		}
	}
}
