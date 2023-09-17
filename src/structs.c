// structs.c

#include "inc/structs.h"

#include "Tiles/MapTiles.h"
#include "Maps/TestMap.h"

#include "Maps/WaterSpring.h"

#include "Ost/Ost.h"

#define lvl_0 0
#define lvl_1 1

uint8_t load_lvl = lvl_0;

const unsigned char symbols[25] =
{
	'!', '"', '#', '$', '%', '&', 39, '(', ')', '*', '+', ',', '-', '.', '/',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

palette_color_t BGPalette[4] = {RGB(29, 25, 21), RGB(17, 15, 11), RGB(13, 11, 7), RGB(3, 3, 3)};
palette_color_t BGPaletteDark[4] = {RGB8(73, 60, 41), RGB8(73, 60, 41), RGB8(57, 44, 26), RGB8(12, 12, 12)};

const uint8_t Lvl_0_solids[] =
{
	0x00, 0x02, 0x03, 0x05,
	0x06, 0x07, 0x08, 0x09,
	0x0A, 0x0B, 0x0C, 0x0D,
	0x0E, 0x0F, 0x10, 0x11,
	0x16, 0x17, 0x18, 0x19
};

const uint8_t Lvl_0_objects[] = {0x18, 0x19};

// Set the player data.
player_t player =
{
	.x = 80,
	.y = 72,
	.width = 14, .height = 16,
	.canAnimate = true,
	.hearts = 3,
	.old_hearts = 3,
	.dir = DIR_RIGHT
};

// This set the levels data.
const level_t levels[] =
{
	{
		.lvl_num = 0,
		.x = 0,
		.y = 0,
		.width = TestMap_WIDTH,
		.height = TestMap_HEIGHT,
		.tile_data = MapTiles_tiles,
		.tile_count = MapTiles_TILE_COUNT,
		.map = TestMap_map,
		.attr = TestMap_map_attributes,
		.solids = Lvl_0_solids,
		.objects = Lvl_0_objects,
		.palettes = BGPalette,
		.palettes_count = sizeof(BGPalette),
		.player_palette = 0,
		.song = &Menuet,
	},
	{
		.lvl_num = 1,
		.x = 0,
		.y = 0,
		.width = WaterSpring_WIDTH,
		.height = WaterSpring_HEIGHT,
		.tile_data = WaterSpring_tiles,
		.tile_count = WaterSpring_TILE_COUNT,
		.map = WaterSpring_map,
		.attr = WaterSpring_map_attributes,
		.palettes = WaterSpring_palettes,
		.palettes_count = WaterSpring_PALETTE_COUNT,
		.player_palette = 1,
		.song = &Spring,
	}
};

level_t currlvl;
