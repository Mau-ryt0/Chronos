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
	// , old_dir[2];
	bool canMove, canAnimate;
};

extern struct character lizzie;

extern bool canMove(uint16_t PosX, uint16_t PosY);
extern void setupPlayer();
extern void mv_spr(uint8_t x, uint8_t y, uint8_t dir);

#endif
