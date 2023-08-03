// gfx.c

#include <gb/gb.h>
#include <stdio.h>
#include "inc/main.h"

// void fadeout(UWORD palette[4])
void fadeout()
{
    // palette[0];
    if (_cpu != CGB_TYPE)
    {
        for (uint8_t i=0; i<4; i++)
        {
            switch(i)
            {
                case 0:
                    BGP_REG = 0xE4; break;
                case 1:
                    BGP_REG = 0xF9; break;
                case 2:
                    BGP_REG = 0xFE; break;
                case 3:
                    BGP_REG = 0xFF; break;
            }
            perfomantDelay(4);
        }
    }
}

// void fadein(UWORD from[4], UWORD to[4])
void fadein()
{
    // from[0]; to[0];
    if (_cpu != CGB_TYPE)
    {
        for (uint8_t i=0; i<3; i++)
        {
            switch(i)
            {
                case 0:
                    BGP_REG = 0xFE; break;
                case 1:
                    BGP_REG = 0xF9; break;
                case 2:
                    BGP_REG = 0xE4; break;
            }
            perfomantDelay(4);
        }
    }
}
