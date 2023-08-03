// camera.h
#ifndef _CAMERA_H_
#define _CAMERA_H_

// extern static void updateMap(uint8_t dir, const unsigned char * MapPlane0, const unsigned char * MapPlane1, uint8_t base);
extern void camera(uint8_t *dir, const unsigned char *map, const unsigned char *attr, const uint16_t MapWidth, const uint16_t MapHeight, uint8_t base);

inline void set_attributed_bkg_submap(UBYTE x, UBYTE y, UBYTE w, UBYTE h, const unsigned char *map, const unsigned char *attr, const uint8_t MapWidth, uint8_t base)
{
    if (_cpu == CGB_TYPE)
    {
        VBK_REG = 1;
        set_bkg_submap(x, y, w, h, attr, MapWidth);
        VBK_REG = 0;
    }
    set_bkg_based_submap(x, y, w, h, map, MapWidth, base);
}

#endif
