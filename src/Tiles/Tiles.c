/*

 TILES.C

 Tile Source File.

 Info:
  Form                 : All tiles as one unit.
  Format               : Gameboy 4 color.
  Compression          : None.
  Counter              : None.
  Tile size            : 8 x 8
  Tiles                : 0 to 33

  Palette colors       : Included.
  SGB Palette          : None.
  CGB Palette          : 1 Byte per entry.

  Convert to metatiles : No.

 This file was generated by GBTD v2.2

*/

/* CGBpalette entries. */
const unsigned char TestRoomTilesCGB[] =
{
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,
  0x01,0x00
};
/* Start of tile array. */
const unsigned char TestRoomTiles[] =
{
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x80,0xFF,0x40,0xFF,0x3F,0xFF,0x30,0xF0,
  0x28,0xE8,0x24,0xE4,0x22,0xE2,0x21,0xE1,
  0x21,0xE0,0x22,0xE0,0x21,0xE0,0x22,0xE0,
  0x21,0xE0,0x22,0xE0,0x21,0xE0,0x22,0xE0,
  0xFF,0x80,0xFF,0x40,0xFF,0x3F,0xFF,0x30,
  0xFF,0x2F,0xFE,0x2D,0xFB,0x2E,0xF9,0x3F,
  0xF9,0x2F,0xF9,0x2F,0xFF,0x2F,0xF9,0x2F,
  0xF9,0x2F,0xF9,0x2F,0xF9,0x2F,0xFB,0x3D,
  0xFB,0x2D,0xFF,0x2F,0xF9,0x2F,0xF9,0x2F,
  0xF9,0x2F,0xF9,0x2F,0xF9,0x3F,0xFB,0x2D,
  0x21,0xE1,0x22,0xE2,0x24,0xE4,0x28,0xE8,
  0x30,0xF0,0x3F,0xFF,0x40,0xFF,0x80,0xFF,
  0xAA,0x00,0x55,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0xFF,0xFF,0x00,0xFF,0x00,0xFF,
  0xFB,0x2D,0xFE,0x2B,0xFC,0x2F,0xFF,0x2F,
  0xFF,0x31,0xFF,0x3F,0xFF,0x40,0xFF,0x80,
  0xFF,0xFF,0x21,0xFE,0x20,0xFF,0xFF,0xFF,
  0xFF,0x01,0xFF,0xFF,0xFF,0x00,0xFF,0x00,
  0xFF,0xFF,0xC1,0x7E,0x40,0xFF,0xFF,0xFF,
  0xFF,0x02,0xFF,0xFF,0xFF,0x00,0xFF,0x00,
  0x84,0x87,0x44,0x47,0x24,0x27,0x14,0x17,
  0x0C,0x0F,0xFC,0xFF,0x02,0xFF,0x01,0xFF,
  0x44,0x07,0x84,0x07,0x44,0x07,0x84,0x07,
  0x44,0x07,0x84,0x07,0x44,0x07,0x84,0x07,
  0x9F,0xFC,0xDF,0x74,0x7F,0xB4,0xFF,0xF4,
  0xFF,0x0C,0xFF,0xFC,0xFF,0x02,0xFF,0x01,
  0xDF,0xBC,0x9F,0xF4,0x9F,0xF4,0x9F,0xF4,
  0x9F,0xF4,0xFF,0xF4,0x9F,0xF4,0x9F,0xF4,
  0xDF,0xB4,0x9F,0xFC,0x9F,0xF4,0x9F,0xF4,
  0x9F,0xF4,0x9F,0xF4,0xFF,0xF4,0xDF,0xB4,
  0x01,0xFF,0x02,0xFF,0xFC,0xFF,0x0C,0x0F,
  0x14,0x17,0x24,0x27,0x44,0x47,0x84,0x87,
  0x00,0xFF,0x00,0xFF,0xFF,0xFF,0x00,0x00,
  0x00,0x00,0x00,0x00,0xAA,0x00,0x55,0x00,
  0xFF,0x01,0xFF,0x02,0xFF,0xFC,0xFF,0x8C,
  0xFF,0xF4,0x3F,0xF4,0x7F,0xD4,0xDF,0xB4,
  0xFF,0x00,0xFF,0x00,0xFF,0xFF,0xFF,0x80,
  0xFF,0xFF,0x04,0xFF,0x84,0x7F,0xFF,0xFF,
  0xFF,0x00,0xFF,0x00,0xFF,0xFF,0xFF,0x40,
  0xFF,0xFF,0x02,0xFF,0x83,0x7E,0xFF,0xFF,
  0x73,0x08,0x7B,0x08,0x5B,0x08,0x5B,0x08,
  0x5B,0x08,0x7B,0x08,0x7B,0x08,0x38,0x0F,
  0xCE,0x21,0xEE,0x21,0xEE,0x21,0x6E,0x21,
  0x6A,0x21,0x6A,0x21,0xEA,0x21,0x2A,0xE1,
  0x2B,0x08,0x2B,0x08,0x6B,0x08,0x5B,0x08,
  0x7B,0x08,0x7B,0x08,0x7B,0x08,0x03,0xF8,
  0xEE,0x21,0x6E,0x21,0x6E,0x21,0x6A,0x21,
  0xEA,0x21,0xEA,0x21,0xEE,0x21,0xC0,0x3F,
  0x00,0x00,0x7F,0x00,0x4F,0x00,0x5C,0x00,
  0x73,0x00,0x77,0x00,0x6F,0x00,0x6F,0x00,
  0x00,0x00,0xFE,0x00,0xF2,0x00,0x3A,0x00,
  0xCE,0x00,0xEE,0x00,0xF6,0x00,0xF6,0x00,
  0x6F,0x00,0x6F,0x00,0x77,0x00,0x73,0x00,
  0x5C,0x00,0x4F,0x00,0x7F,0x00,0x00,0x00,
  0xF6,0x00,0xF6,0x00,0xEE,0x00,0xCE,0x00,
  0x3A,0x00,0xF2,0x00,0xFE,0x00,0x00,0x00,
  0xFF,0xFF,0x80,0x80,0x80,0x80,0xFF,0xFF,
  0x80,0xFF,0x9F,0xFF,0x90,0xF0,0x93,0xF3,
  0xFF,0xFF,0x01,0x01,0x01,0x01,0xFF,0xFF,
  0x01,0xFF,0xF9,0xFF,0x09,0x0F,0xC9,0xCF,
  0x90,0xF3,0x9F,0xFF,0x90,0xF0,0x93,0xF3,
  0x90,0xF3,0x9F,0xFF,0x80,0xFF,0xFF,0xFF,
  0x09,0xCF,0xF9,0xFF,0x09,0x0F,0xC9,0xCF,
  0x09,0xCF,0xF9,0xFF,0x01,0xFF,0xFF,0xFF,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

/* End of TILES.C */
