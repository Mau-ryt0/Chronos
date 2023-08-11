// lizzie.h

#ifndef _LIZZIE_H_INCLUDE
#define _LIZZIE_H_INCLUDE

#include <gb/gb.h>
#include <stdio.h>
#include <stdbool.h>

#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_DOWN 3
#define DIR_UP 4
#define DIR_NULL 0

struct character
{
	// UBYTE sprites[4];
	uint8_t x, y;
	uint8_t width;
	uint8_t height;
	// uint8_t hearts;
	// uint8_t old_hearts;
	// uint8_t health, old_health;
	uint8_t dir;
	bool canMove, canAnimate;
};
// extern void mv_spr(uint8_t x, uint8_t y, uint8_t dir);
/* void mv_spr(uint8_t x, uint8_t y, uint8_t dir)
{
	move_sprite(0, x-8, y); move_sprite(1, x, y);
	walking(dir);
	if (dir == DIR_RIGHT)
	{
		// for (uint8_t i=0; i<2; i++) set_sprite_prop(i, 0);
		move_sprite(0, x-8, y); move_sprite(1, x, y);

		walking(dir);
	}
	else if (dir == DIR_LEFT)
	{
		// for (uint8_t i=0; i<2; i++) set_sprite_prop(i, S_FLIPX);
		move_sprite(0, x, y); move_sprite(1, x-8, y);

		walking(dir);
	}

	if (dir == DIR_DOWN)
	{
		// for (uint8_t i=0; i<2; i++) set_sprite_prop(i, 0);
		move_sprite(0, x-8, y); move_sprite(1, x, y);

		walking(dir);
	}
	else if (dir == DIR_UP)
	{
		// for (uint8_t i=0; i<2; i++) set_sprite_prop(i, 0);
		move_sprite(0, x-8, y); move_sprite(1, x, y);

		walking(dir);
	}
}*/

extern struct character lizzie;

extern bool colliding(uint16_t PosX, uint16_t PosY);
extern void inputs(uint8_t *x, uint8_t *y, uint8_t *dir);
extern void setupPlayer(void);

#endif
