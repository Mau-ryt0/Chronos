// setup.h

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include <gbdk/emu_debug.h>

#include "Tiles/MapTiles.h"
#include "Tiles/DialogTiles.h"

#include "Maps/TestMap.h"
#include "Maps/WaterSpring.h"
#include "Maps/Dialog.h"

#include "UI/Font.h"

#include "inc/setup.h"

#include "inc/main.h"
#include "inc/funcs.h"
#include "inc/camera.h"
#include "inc/lizzie.h"
#include "inc/gfx.h"

#include "Ost/Ost.h"

UWORD BGPalette[4] = {RGB(29, 25, 21), RGB(17, 15, 11), RGB(13, 11, 7), RGB(3, 3, 3)};
UWORD BGPaletteDark[4] = {RGB8(73, 60, 41), RGB8(73, 60, 41), RGB8(57, 44, 26), RGB8(12, 12, 12)};

const level_t levels[] =
{
    {
        .x = 0,
        .y = 0,
        .width = TestMap_WIDTH,
        .tile_data = MapTiles_tiles,
        .tile_count = MapTiles_TILE_COUNT,
        .map = TestMap_map,
        .attr = TestMap_map_attributes,
        .palettes = 2
        // ,
        // .colliders =
        // {
        //     0x00, 0x02, 0x03, 0x05,
        //     0x06, 0x07, 0x08, 0x09,
        //     0x0A, 0x0B, 0x0C, 0x0D,
        //     0x0E, 0x0F, 0x10, 0x11,
        //     0x16, 0x17, 0x18, 0x19
        // }
    },
    {
        .x = 0,
        .y = 0,
        .width = WaterSpring_WIDTH,
        .tile_data = WaterSpring_tiles,
        .tile_count = WaterSpring_TILE_COUNT,
        .map = WaterSpring_map,
        .attr = WaterSpring_map_attributes,
        .palettes = WaterSpring_palettes,
        .palettes_count = WaterSpring_PALETTE_COUNT
    }
};

level_t currlvl;

// Defined in setup.h
// #define Map_base 0x24

joypads_t jpads;

// int8_t bkgLastPosx = 0;
// int8_t bkgLastPosy = 0;

void setup(void)
{
    if (_cpu == CGB_TYPE)
    {
        cpu_fast(); for (uint8_t ii=0; ii < 2; ii++);
        // set_bkg_palette(ii, 1, &BGPaletteDark[0]);
    }

    CRITICAL {add_VBL(&VBL_isr);}
    set_interrupts(IE_REG | VBL_IFLAG);

    joypad_init(1, &jpads);

    WY_REG = 144;
    WX_REG = 7;

    currlvl = levels[1];

    const uint8_t Dialog_base = (currlvl.tile_count)+Map_base;

    set_bkg_data(0x00, sizeof(Font_tiles)>>4, Font_tiles);
    set_bkg_data(Map_base, currlvl.tile_count, currlvl.tile_data);
    set_bkg_data(Dialog_base, sizeof(DialogTiles_tiles)>>4, DialogTiles_tiles);

    set_attributed_bkg_submap(currlvl.x, currlvl.y, 20, 18, currlvl.map, currlvl.attr, currlvl.width, Map_base);
    set_win_based_tiles(0, 0, 20, 6, Dialog_map, Dialog_base);
    setupPlayer();

    SPRITES_8x16;
    SHOW_BKG;
    SHOW_WIN;
    SHOW_SPRITES;

    // fadein(&BGPaletteDark[0], currlvl.palettes, 2);
    set_bkg_palette(0, currlvl.palettes_count, currlvl.palettes);
    play(Spring);
}

void mainloop(void)
{   while(true)
    {
        inputs(&lizzie.x, &lizzie.y, &lizzie.dir);
        if (lizzie.x > 166 || lizzie.x < -6 || lizzie.y > 144 || lizzie.y == 0)
            camera(currlvl.width, Map_base);
        else wait_vbl_done();
    }
}
