// main.c

#include <gb/gb.h>
#include <stdio.h>
#include <stdbool.h>

#include "inc/setup.h"

/*void trans_LCD()
{
}*/

void perfomantDelay(UINT8 delay) {for (uint8_t d=0; d<delay; d++) wait_vbl_done();}

void main(void)
{
    setup();
    mainloop();
}
