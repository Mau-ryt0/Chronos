// camera.h
#ifndef _CAMERA_H_
#define _CAMERA_H_

extern uint16_t camerax, cameray;

// extern static void updateMap(uint8_t dir, const unsigned char * MapPlane0, const unsigned char * MapPlane1, uint8_t base);
// extern void camera(const unsigned char *map, const unsigned char *attr, const uint16_t MapWidth, const uint8_t MapHeight, uint8_t base);
extern void camera(const uint16_t MapWidth, uint8_t base);

inline void set_attributed_bkg_submap(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const unsigned char *map, const unsigned char *attr, const uint16_t MapWidth, uint8_t base)
{
	if (_cpu == CGB_TYPE)
	{
		VBK_REG = 1;
		set_bkg_submap( x, y, w, h, attr, MapWidth>>3);
		VBK_REG = 0;
	}
	set_bkg_based_submap(x, y, w, h, map, MapWidth>>3, base);
}

#endif
