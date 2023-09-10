// lizzie.h

#ifndef _LIZZIE_H_INCLUDE
#define _LIZZIE_H_INCLUDE

#include <gb/gb.h>
#include <stdio.h>
#include <stdbool.h>

#include "funcs.h"

#define DIR_RIGHT 1
#define DIR_LEFT -1
#define DIR_DOWN 2
#define DIR_UP -2
#define DIR_NULL 0

struct character
{
	// UBYTE sprites[4];
	int16_t x, y;
	uint8_t width;
	uint8_t height;
	uint8_t hearts;
	uint8_t old_hearts;
	// uint8_t health, old_health;
	int8_t dir;
	bool canMove, canAnimate;
};

extern struct character lizzie;

extern void inputs(int16_t *x, int16_t *y, int8_t *_dir, bkgmap *load);
extern void setupPlayer(void);

#endif
