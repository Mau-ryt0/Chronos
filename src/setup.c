// setup.h

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include <gbdk/emu_debug.h>

#include "Tiles/MapTiles.h"
#include "Tiles/DialogTiles.h"

#include "Maps/Dialog.h"

#include "UI/Font.h"

#include "inc/structs.h"

#include "inc/lizzie.h"
#include "inc/funcs.h"
#include "inc/camera.h"
#include "inc/gfx.h"
#include "inc/main.h"

#include "inc/hUGEDriver.h"

// Defined in structs.h
// #define Map_base 0x24

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

	SPRITES_8x16;
	SHOW_BKG;
	SHOW_WIN;
	SHOW_SPRITES;

    (_cpu == CGB_TYPE)?cfadein(&BGPaletteDark[0], currlvl.palettes):fadein();
	// set_bkg_palette(0, currlvl.palettes_count, currlvl.palettes);
	play(currlvl.song);
}

void mainloop(void)
{   while(true)
	{
		inputs(&player.x, &player.y, &player.dir);
		if (player.x > 166 || player.x < -6 || player.y > 144 || player.y == 0)
			camera(currlvl.width, Map_base);
		else wait_vbl_done();
		if (load_lvl != currlvl.lvl_num)
		{
            // palette_color_t *aux = BGPalette;
            // (_cpu == CGB_TYPE)?cfadeout(aux, &BGPaletteDark[0]):fadeout();

			CRITICAL
				{remove_VBL(&VBL_isr);}
			set_interrupts(IE_REG & ~VBL_IFLAG);

			main();
		}
	}
}
