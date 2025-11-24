# Support for Different Texture Sizes

## Overview

This branch adds support for different texture sizes in the cub3D raycaster. Previously, the code had hardcoded assumptions that textures were 16x16 pixels, matching the tile size. Now, textures can be of any size while maintaining a configurable tile size.

## Key Concepts

### Tile Size vs Texture Size

It's important to distinguish between two different "sizes":

1. **Tile Size (SIZE_IMG)**: The size of each map block/tile in pixels. This determines how the game world is subdivided and is defined by the `SIZE_IMG` macro (default: 16 pixels).

2. **Texture Size**: The resolution of texture images (can be any size). Each texture file can have its own dimensions, which are loaded dynamically via `mlx_xpm_file_to_image()`.

### How It Works

The texture mapping system already supports different texture sizes through the `sample_texture()` function in `tex_mapping.c`. This function:
- Takes UV coordinates in the range [0, 1]
- Maps them to actual texture pixel coordinates using the texture's width and height
- Returns the appropriate pixel color

The changes in this branch ensure all calculations use `SIZE_IMG` instead of hardcoded `16` values for tile-based calculations.

## Changes Made

### 1. line_drawing.c

**UV Coordinate Calculation** (lines 37-40):
- Changed `hit.collision.x % 16` to `hit.collision.x % SIZE_IMG`
- Changed `hit.collision.y % 16` to `hit.collision.y % SIZE_IMG`
- Simplified `(count * 16) / line_size / SIZE_IMG` to `count / line_size` (the SIZE_IMG terms cancel out)

**Collision Detection** (lines 98-99):
- Changed `hit.collision.x / 16` to `hit.collision.x / SIZE_IMG`
- Changed `hit.collision.y / 16` to `hit.collision.y / SIZE_IMG`

**Edge Detection** (lines 119-148):
- Changed `hit.collision.x % 16 == 15` to `hit.collision.x % SIZE_IMG == SIZE_IMG - 1`
- Changed `hit.collision.x % 16 == 0` to `hit.collision.x % SIZE_IMG == 0`

### 2. tex_mapping.c

**Collision Block/Pixel Calculation** (lines 140-143):
- Changed `collision.x / 16` to `collision.x / SIZE_IMG`
- Changed `collision.y / 16` to `collision.y / SIZE_IMG`
- Changed `collision.x % 16` to `collision.x % SIZE_IMG`
- Changed `collision.y % 16` to `collision.y % SIZE_IMG`

**Diagonal Direction Detection** (lines 113, 118, 125):
- Changed `15 - collision_pixel.x` to `SIZE_IMG - 1 - collision_pixel.x`
- Changed `15 - collision_pixel.y` to `SIZE_IMG - 1 - collision_pixel.y`

### 3. main.c

**Player Position Initialization** (lines 41-44):
- Changed `i * 16` to `i * SIZE_IMG`
- Changed `j * 16` to `j * SIZE_IMG`
- Changed `16 >> 1` to `SIZE_IMG >> 1`

## Testing

The changes have been tested with:
- Default 16x16 textures (n.xpm, s.xpm, e.xpm, w.xpm, f.xpm)
- Large 512x512 texture (pl.xpm)

Example test map: `maps/map1.cub` uses a mix of texture sizes.

## Benefits

1. **Flexibility**: Textures can now be any size (8x8, 16x16, 32x32, 64x64, 128x128, 512x512, etc.)
2. **Quality**: Higher resolution textures can be used for better visual quality
3. **Consistency**: The tile size (SIZE_IMG) can be changed in one place
4. **Maintainability**: No more magic numbers scattered throughout the code

## How to Use Different Texture Sizes

Simply provide XPM texture files of any size in your .cub map file:

```
NO ./textures/my_64x64_texture.xpm
SO ./textures/my_128x128_texture.xpm
EA ./textures/my_16x16_texture.xpm
WE ./textures/my_512x512_texture.xpm
```

The texture system will automatically handle the different sizes.

## How to Change Tile Size

To change the tile size, modify the `SIZE_IMG` definition in `includes/cub.h`:

```c
#ifndef SIZE_IMG
 #define SIZE_IMG 32  // Change from 16 to 32, for example
#endif
```

Then rebuild the project:
```bash
make re
```

## Implementation Notes

- The `sample_texture()` function correctly handles texture sampling for any texture size
- UV coordinates are always normalized to [0, 1] range regardless of texture size
- The tile size controls game world subdivision, not texture resolution
- Edge detection logic properly accounts for variable tile sizes
