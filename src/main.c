// main.c

#include <gb/gb.h>
#include <stdio.h>
#include <stdbool.h>

#include "inc/setup.h"
#include "inc/funcs.h"

#include "Ost/Menuet.h"

/*void trans_LCD()
{
}*/

void main(void)
{
    CRITICAL {add_VBL(&VBL_isr);}
    set_interrupts(IE_REG | VBL_IFLAG);
    setup();
    play(Menuet);
    mainloop();
}
