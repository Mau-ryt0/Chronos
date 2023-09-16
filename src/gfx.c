// gfx.c

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>

#include "inc/funcs.h"

uint8_t fadevel = 4;

void cfadeout(palette_color_t *from, const palette_color_t *to)
{
	while (from[0] != to[0])
	{
		from[2] = (from[2] >= to[2])?
			from[2]-RGB(1, 1, 1):
			to[2];

		from[1] = (from[1] >= to[1])?
			from[1]-RGB(1, 1, 1):
			to[1];

		from[0] = (from[0] >= to[0])?
			from[0]-RGB(1, 1, 1):
			to[0];

		set_bkg_palette(0, 1, from);
		vblankDelay(fadevel);
	}
}

void cfadein(palette_color_t *from, const palette_color_t *to)
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
	for (uint8_t i=0; i<4; i++)
	{
		BGP_REG=(i==1)?0xE4:0x00;
		BGP_REG=(i==2)?0xF9:0x00;
		BGP_REG=(i==3)?0xFE:0x00;
		BGP_REG=(i==4)?0xFF:0x00;
		vblankDelay(fadevel);
	}
}

void fadein(void)
{
	for (uint8_t i=0; i<3; i++)
	{
		BGP_REG = (i==0)?0xFE:0x00;
		BGP_REG = (i==1)?0xF9:0x00;
		BGP_REG = (i==2)?0xE4:0x00;
		vblankDelay(fadevel);
	}
}