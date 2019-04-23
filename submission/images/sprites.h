/*
 * Exported with nin10kit v1.7
 * Invocation command was nin10kit --mode=sprites --bpp=4 --for_bitmap --transparent=FFFFFF sprites gatech.png georgia.png
 * Time-stamp: Thursday 04/11/2019, 02:55:49
 *
 * Image Information
 * -----------------
 * gatech.png 32@32
 * georgia.png 16@16
 * Transparent color: (255, 255, 255)
 *
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#ifndef SPRITES_H
#define SPRITES_H

#define SPRITES_PALETTE_TYPE (0 << 13)
#define SPRITES_DIMENSION_TYPE (1 << 6)

extern const unsigned short sprites_palette[256];
#define SPRITES_PALETTE_SIZE 512
#define SPRITES_PALETTE_LENGTH 256

extern const unsigned short sprites[320];
#define SPRITES_SIZE 640
#define SPRITES_LENGTH 320

#define GATECH_PALETTE_ID (0 << 12)
#define GATECH_SPRITE_SHAPE (0 << 14)
#define GATECH_SPRITE_SIZE (2 << 14)
#define GATECH_ID 512

#define GEORGIA_PALETTE_ID (1 << 12)
#define GEORGIA_SPRITE_SHAPE (0 << 14)
#define GEORGIA_SPRITE_SIZE (1 << 14)
#define GEORGIA_ID 528

#endif

