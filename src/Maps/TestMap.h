//AUTOGENERATED FILE FROM png2asset
#ifndef METASPRITE_TestMap_H
#define METASPRITE_TestMap_H

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#define TestMap_TILE_ORIGIN 0
#define TestMap_TILE_W 8
#define TestMap_TILE_H 8
#define TestMap_WIDTH 480
#define TestMap_HEIGHT 288
#define TestMap_TILE_COUNT 28
#define TestMap_PALETTE_COUNT 2
#define TestMap_COLORS_PER_PALETTE 4
#define TestMap_TOTAL_COLORS 8
#define TestMap_MAP_ATTRIBUTES TestMap_map_attributes
#define TestMap_MAP_ATTRIBUTES_WIDTH 60
#define TestMap_MAP_ATTRIBUTES_HEIGHT 36
#define TestMap_MAP_ATTRIBUTES_PACKED_WIDTH 60
#define TestMap_MAP_ATTRIBUTES_PACKED_HEIGHT 36

BANKREF_EXTERN(TestMap)

extern const palette_color_t TestMap_palettes[8];
extern const uint8_t TestMap_tiles[448];

extern const unsigned char TestMap_map[2160];
extern const unsigned char TestMap_map_attributes[2160];

#endif
