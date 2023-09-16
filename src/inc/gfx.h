// gfx.h

#ifndef _GFX_H_
#define _GFX_H_

extern void fadeout(void);
extern void fadein(void);

// This only work on cgb.
extern void cfadeout(palette_color_t *from, const palette_color_t *to);
extern void cfadein(palette_color_t *from, const palette_color_t *to);

#endif
