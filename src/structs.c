// structs.c

#include "inc/structs.h"

#include "Tiles/MapTiles.h"
#include "Maps/TestMap.h"

#include "Maps/WaterSpring.h"

#include "Ost/Ost.h"

palette_color_t BGPalette[4] = {RGB(29, 25, 21), RGB(17, 15, 11), RGB(13, 11, 7), RGB(3, 3, 3)};
palette_color_t BGPaletteDark[4] = {RGB8(73, 60, 41), RGB8(73, 60, 41), RGB8(57, 44, 26), RGB8(12, 12, 12)};

const level_t levels[] =
{
    {
        .x = 0,
        .y = 0,
        .width = TestMap_WIDTH,
        .tile_data = MapTiles_tiles,
        .tile_count = MapTiles_TILE_COUNT,
        .map = TestMap_map,
        .attr = TestMap_map_attributes,
        .palettes = BGPalette,
        .palettes_count = sizeof(BGPalette),
        .player_palette = 1,
        .song = &Menuet

        // ,
        // .colliders =
        // {
        //     0x00, 0x02, 0x03, 0x05,
        //     0x06, 0x07, 0x08, 0x09,
        //     0x0A, 0x0B, 0x0C, 0x0D,
        //     0x0E, 0x0F, 0x10, 0x11,
        //     0x16, 0x17, 0x18, 0x19
        // }
    },
    {
        .x = 0,
        .y = 0,
        .width = WaterSpring_WIDTH,
        .tile_data = WaterSpring_tiles,
        .tile_count = WaterSpring_TILE_COUNT,
        .map = WaterSpring_map,
        .attr = WaterSpring_map_attributes,
        .palettes = WaterSpring_palettes,
        .palettes_count = WaterSpring_PALETTE_COUNT,
        .player_palette = 1,
        .song = &Spring
    }
};

level_t currlvl;
