// gfx.c

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>

#include "inc/structs.h"

#include "inc/funcs.h"

#define fadeDelay 2

void cfadeout(palette_color_t *from, palette_color_t *to)
{
	while (from[0] != to[0])
	{
		from[3] = (from[3] > to[3])?
			from[3]-RGB(1, 1, 1):
			to[3];

		from[2] = (from[2] > to[2])?
			from[2]-RGB(1, 1, 1):
			to[2];

		from[1] = (from[1] > to[1])?
			from[1]-RGB(1, 1, 1):
			to[1];

		from[0] = (from[0] > to[0])?
			from[0]-RGB(1, 1, 1):
			to[0];

		set_bkg_palette(0, 1, from);
		wait_vbl_done();
	}
}

void cfadein(palette_color_t *from, palette_color_t *to)
{
	// palette_color_t *from is the palette that will change.
	// palette_color_t *to is the palette which *from palette will change to.
	while (from[0] != to[0])
	{
        from[3] = (from[3] <= to[3])?
            from[3]+RGB(1, 1, 1):
            to[3];

		from[2] = (from[2] <= to[2])?
			from[2]+RGB(1, 1, 1):
			to[2];

		from[1] = (from[1] <= to[1])?
			from[1]+RGB(1, 1, 1):
			to[1];

		from[0] = (from[0] <= to[0])?
			from[0]+RGB(1, 1, 1):
			to[0];

		set_bkg_palette(0, 1, from);
		wait_vbl_done();
	}
}

void fadeout(void)
{
	for (uint8_t i=0; i<7; i++)
	{
		if (i==0)
            {BGP_REG=0b11100100; NR50_REG=vol_6;}
        else if (i==1) NR50_REG=vol_5;
        else if (i==2)
            {BGP_REG=0b11111001; NR50_REG=vol_4;}
        else if (i==3) NR50_REG=vol_3;
        else if (i==4)
            {BGP_REG=0b11111110; NR50_REG=vol_2;}
        else if (i==5) NR50_REG=vol_1;
        else if (i==6)
            {BGP_REG=0b11111111; NR50_REG=vol_0;}

		vblankDelay(fadeDelay);
	}
}

void fadein(void)
{
	for (uint8_t i=0; i<7; i++)
	{
        if (i==0)
            {BGP_REG=0b11111111; NR50_REG=vol_1;}
        else if (i==1) NR50_REG=vol_2;
        else if (i==2)
            {BGP_REG=0b11111110; NR50_REG=vol_3;}
        else if (i==3) NR50_REG=vol_4;
        else if (i==4)
            {BGP_REG=0b11111001; NR50_REG=vol_5;}
        else if (i==5) NR50_REG=vol_6;
        else if (i==6)
            {BGP_REG=0b11100100; NR50_REG=vol_7;}

		vblankDelay(fadeDelay);
	}
}
