// lizzie.h

#ifndef _LIZZIE_H_INCLUDE
#define _LIZZIE_H_INCLUDE

#include <gb/gb.h>
#include <stdio.h>
#include <stdbool.h>

#define DIR_RIGHT 1
#define DIR_LEFT -1
#define DIR_DOWN 2
#define DIR_UP -2
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
	int8_t dir;
	bool canMove, canAnimate;
};

extern struct character lizzie;

// extern bool colliding(uint8_t x, uint8_t y, uint8_t dir);
extern bool colliding(uint16_t x, uint16_t y);
extern void inputs(uint8_t *x, uint8_t *y, int8_t *dir);
extern void setupPlayer(void);

#endif
