// gfx.c

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include "inc/main.h"

void fadeout(UWORD palette[4])
{
    if (_cpu != CGB_TYPE)
    {
        for (uint8_t i=0; i<4; i++)
        {
            switch(i)
            {
                case 0:
                    BGP_REG = 0xE4; break;
                case 1:
                    BGP_REG = 0xF9; break;
                case 2:
                    BGP_REG = 0xFE; break;
                case 3:
                    BGP_REG = 0xFF; break;
            }
            perfomantDelay(4);
        }
    }
    else
    {
        while (palette[0] != RGB(1, 1, 1))
        {
            if(palette[2] >= RGB(2, 2, 2)) palette[2] -= RGB(1, 1, 1);
            else palette[2] = RGB(1, 1, 1);

            if(palette[1] >= RGB(2, 2, 2)) palette[1] -= RGB(1, 1, 1);
            else palette[1] = RGB(1, 1, 1);
            
            if(palette[0] >= RGB(2, 2, 2)) palette[0] -= RGB(1, 1, 1);
            else palette[0] = RGB(1, 1, 1);
            set_bkg_palette(0, 1, &palette[0]);
            perfomantDelay(4);
        }
    }
}

void fadein(UWORD from[4], UWORD to[4], uint8_t modify)
{
    from[0]; to[0];
    if (_cpu != CGB_TYPE)
    {
        for (uint8_t i=0; i<3; i++)
        {
            switch(i)
            {
                case 0:
                    BGP_REG = 0xFE; break;
                case 1:
                    BGP_REG = 0xF9; break;
                case 2:
                    BGP_REG = 0xE4; break;
            }
            perfomantDelay(4);
        }
    }
    else
    {
        while (from[0] != to[0])
        {
            if(from[2] <= to[2]) from[2] += RGB(1, 1, 1);
            else from[2] = to[2];

            if(from[1] <= to[1]) from[1] += RGB(1, 1, 1);
            else from[1] = to[1];
            
            if(from[0] <= to[0]) from[0] += RGB(1, 1, 1);
            else from[0] = to[0];
            for (uint8_t ii=0; ii < modify; ii++) set_bkg_palette(ii, 1, &from[0]);
            wait_vbl_done();
        }
    }
}
