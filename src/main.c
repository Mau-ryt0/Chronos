// main.c

#include <gb/gb.h>
#include <gb/cgb.h>
#include <gbdk/font.h>
#include <stdio.h>
#include <stdbool.h>

#include "inc/setup.h"

#include "inc/structs.h"

/*void trans_LCD()
{
}*/

const palette_color_t bp[] =
{
	RGB(31, 31, 31), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0)
};


// Function and assembly code by Valentina "Coffe Bat".
// https://twitter.com/Cofebbat
bool shouldBlock(void)
{
	__asm
	ld de, #0xFFFF
	push de
	pop af
	push af
	pop de
	inc e
	ld a, d
	ret z
	__endasm;
	return 0;
}

void main(void)
{
	if (shouldBlock())
	{
		if (_cpu == CGB_TYPE) set_bkg_palette(0, 1, &bp[0]);

		font_t font;
		font_init();
		font = font_load(font_ibm);
		font_set(font);

		printf("\n <<Very important>>");
		printf("\n This emulator is\n shit.\n\n This game can't run\n on this emulator.");
		printf("\n Change it or lick\n a dog's butt.\n");
		printf("\n Your best options\n are BGB, SameBoy,\n Emulicious, \n Gambatte, \n or others.");
	}
	else
	{
		if (_cpu == CGB_TYPE) cpu_fast();
		setup();
		wait_vbl_done();
		mainloop();
	}
}
