#pragma once

#include <Framebuffer_GFX.h>

// The number of pixels in each tile
#define TILE_PIXELS_X 32
#define TILE_PIXELS_Y 8

// The number of tiles
#define TILES_X 1
#define TILES_Y 1

// The total pixels in each direction
#define PIXELS_X (TILE_PIXELS_X * TILES_X)
#define PIXELS_Y (TILE_PIXELS_Y * TILES_Y)

// The total LED/pixel count
#define NUM_LEDS (PIXELS_X * PIXELS_Y)

// Matrix layout 
#define MATRIX_TYPE (NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG)