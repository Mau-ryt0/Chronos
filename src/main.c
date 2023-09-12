// main.c

#include <gb/gb.h>
#include <stdio.h>
#include <stdbool.h>

#include "inc/setup.h"

/*void trans_LCD()
{
}*/

void main(void)
{
    setup();
    wait_vbl_done();
    mainloop();
}
