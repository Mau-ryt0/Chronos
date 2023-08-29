// setup.h

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>

#include "Tiles/MapTiles.h"
#include "Tiles/DialogTiles.h"

#include "Maps/TestMap.h"
#include "Maps/Dialog.h"

#include "inc/setup.h"

#include "inc/main.h"
#include "inc/funcs.h"
#include "inc/camera.h"
#include "inc/lizzie.h"
#include "inc/gfx.h"

// Defined in setup.h
// #define Map_base 0x24
#define Dialog_base (sizeof(MapTiles_tiles)>>4)+Map_base

joypads_t jpads;

UWORD BGPalette[4] = {RGB(29, 25, 21), RGB(17, 15, 11), RGB(13, 11, 7), RGB(3, 3, 3)};
UWORD BGPaletteDark[4] = {RGB8(73, 60, 41), RGB8(73, 60, 41), RGB8(57, 44, 26), RGB8(12, 12, 12)};

void setup(void)
{
    joypad_init(1, &jpads);

    WY_REG = 144;
    WX_REG = 7;

    set_bkg_data(Map_base, sizeof(MapTiles_tiles)>>4, MapTiles_tiles);
    set_bkg_data(Dialog_base, sizeof(DialogTiles_tiles)>>4, DialogTiles_tiles);
    
    if (_cpu == CGB_TYPE)
        {cpu_fast(); for (uint8_t ii=0; ii < 2; ii++) set_bkg_palette(ii, 1, &BGPaletteDark[0]);}
    
    set_attributed_bkg_submap(0, 0, 20, 18, TestMap_map, TestMap_map_attributes, (TestMap_WIDTH>>3), Map_base);
    set_win_based_tiles(0, 0, 20, 6, Dialog_map, Dialog_base);
    setupPlayer();

    SPRITES_8x16;
    SHOW_BKG;
    SHOW_WIN;
    SHOW_SPRITES;
    // fadeout(&BGPalette6[0]);
    fadein(&BGPaletteDark[0], &BGPalette[0], 2);
}

void mainloop(void)
{
    while(true)
    {
        inputs(&lizzie.x, &lizzie.y, &lizzie.dir);
        if (lizzie.x > 160 || lizzie.x == 0 || lizzie.y > 144 || lizzie.y == 0)
            camera(TestMap_map, TestMap_map_attributes, (TestMap_WIDTH>>3), (TestMap_HEIGHT>>3), Map_base);
        else wait_vbl_done();
    }
}
