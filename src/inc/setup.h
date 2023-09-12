// setup.h

#ifndef _SETUP_H_INCLUDE
#define _SETUP_H_INCLUDE

#include "funcs.h"

#define Map_base 0x34


extern level_t currlvl;

extern joypads_t jpads;

extern void setup(void);
extern void mainloop(void);

#endif
