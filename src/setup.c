// setup.h

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>

#include "Maps/TestMap.h"
#include "Tiles/Tiles.h"

#include "inc/main.h"
#include "inc/camera.h"
#include "inc/lizzie.h"

joypads_t jpads;

UWORD BGPalette6[4] = {RGB(29, 25, 21), RGB(17, 15, 11), RGB(13, 11, 7), RGB(3, 3, 3)};

void setup()
{
    joypad_init(1, &jpads);

    set_bkg_data(0x24, sizeof(TestMap_tiles)>>4, TestMap_tiles);
    
    if (_cpu == CGB_TYPE)
        {cpu_fast(); for (uint8_t ii=0; ii < 2; ii++) set_bkg_palette(ii, 1, &BGPalette6[0]);}
    
    set_attributed_bkg_submap(0, 0, 21, 19, TestMap_map, TestMap_map_attributes, (TestMap_WIDTH>>3), 0x24);
    setupPlayer();

    SPRITES_8x16;
    SHOW_BKG;
    SHOW_SPRITES;
    // fadeout();
}

void mainloop()
{
    while(1)
    {
        inputs(&lizzie.x, &lizzie.y, &lizzie.dir);
        if (lizzie.x > 168 || lizzie.x < 8 || lizzie.y > 152 || lizzie.y < 8) camera(&lizzie.dir, TestMap_map, TestMap_map_attributes, TestMap_WIDTH, TestMap_HEIGHT, 0x24);
        wait_vbl_done();
    }
}
