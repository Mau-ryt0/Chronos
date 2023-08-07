// main.c

#include <gb/gb.h>
#include <stdio.h>
#include <stdbool.h>

#include "inc/setup.h"
#include "inc/lizzie.h"

/*void trans_LCD()
{
}*/

void perfomantDelay(UINT8 delay) {for (uint8_t d=0; d<delay; d++) wait_vbl_done();}

void inputs(uint8_t *x, uint8_t *y, uint8_t *dir)
{
    joypad_ex(&jpads);
    
    // if ((joypads_t) == J_BUTTON) is incorrect. Character will not move in 8 directions.
    // Use if ((joypads_t) & J_BUTTON) instead to avoid problems.

    if (jpads.joy0 & J_RIGHT && !(jpads.joy0 &J_LEFT))
    {
        if (*dir == DIR_NULL) *dir = DIR_RIGHT;
        if (canMove(*x, *y) == false) *x+=1;
    }
    else if (!(jpads.joy0 & J_RIGHT) && *dir == DIR_RIGHT) *dir = DIR_NULL;

    if (jpads.joy0 & J_LEFT && !(jpads.joy0 & J_RIGHT))
    {
        if (*dir == DIR_NULL) *dir = DIR_LEFT;
        if (canMove(*x, *y) == false) *x-=1;
    }
    else if (!(jpads.joy0 & J_LEFT) && *dir == DIR_LEFT) *dir = DIR_NULL;

    if (jpads.joy0 & J_DOWN && !(jpads.joy0 & J_UP))
    {
        if (*dir == DIR_NULL) *dir = DIR_DOWN;
        if (canMove(*x, *y) == true) *y+=1;
    }
    else if (!(jpads.joy0 & J_DOWN) && *dir == DIR_DOWN) *dir = DIR_NULL;

    if (jpads.joy0 & J_UP && !(jpads.joy0 & J_DOWN))
    {
        if (*dir == DIR_NULL) *dir = DIR_UP;
        if (canMove(*x, *y) == true) *y-=1;
    }
    else if (!(jpads.joy0 & J_UP) && *dir == DIR_UP) *dir = DIR_NULL;

    if (jpads.joy0 != 0) mv_spr(*x, *y, *dir);
    else return;
}

void main()
{
    setup();
    mainloop();
}
