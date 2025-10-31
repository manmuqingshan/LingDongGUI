#ifndef __UI_IMAGES_H__
#define __UI_IMAGES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "arm_2d.h"
#include "ldConfig.h"

// light_red_small.png < 32x32 >
#if LD_CFG_COLOR_DEPTH == 8
extern const arm_2d_tile_t c_tile_light_red_small_png_GRAY8;
#define IMAGE_LIGHT_RED_SMALL_PNG          (arm_2d_tile_t*)&c_tile_light_red_small_png_GRAY8
#elif LD_CFG_COLOR_DEPTH == 16
extern const arm_2d_tile_t c_tile_light_red_small_png_RGB565;
#define IMAGE_LIGHT_RED_SMALL_PNG          (arm_2d_tile_t*)&c_tile_light_red_small_png_RGB565
#else
extern const arm_2d_tile_t c_tile_light_red_small_png_CCCA8888;
#define IMAGE_LIGHT_RED_SMALL_PNG          (arm_2d_tile_t*)&c_tile_light_red_small_png_CCCA8888
#endif
extern const arm_2d_tile_t c_tile_light_red_small_png_A1Mask;
#define IMAGE_LIGHT_RED_SMALL_PNG_A1_MASK   (arm_2d_tile_t*)&c_tile_light_red_small_png_A1Mask
extern const arm_2d_tile_t c_tile_light_red_small_png_A2Mask;
#define IMAGE_LIGHT_RED_SMALL_PNG_A2_MASK   (arm_2d_tile_t*)&c_tile_light_red_small_png_A2Mask
extern const arm_2d_tile_t c_tile_light_red_small_png_A4Mask;
#define IMAGE_LIGHT_RED_SMALL_PNG_A4_MASK   (arm_2d_tile_t*)&c_tile_light_red_small_png_A4Mask
extern const arm_2d_tile_t c_tile_light_red_small_png_Mask;
#define IMAGE_LIGHT_RED_SMALL_PNG_MASK     (arm_2d_tile_t*)&c_tile_light_red_small_png_Mask

// light_green_small.png < 32x32 >
#if LD_CFG_COLOR_DEPTH == 8
extern const arm_2d_tile_t c_tile_light_green_small_png_GRAY8;
#define IMAGE_LIGHT_GREEN_SMALL_PNG          (arm_2d_tile_t*)&c_tile_light_green_small_png_GRAY8
#elif LD_CFG_COLOR_DEPTH == 16
extern const arm_2d_tile_t c_tile_light_green_small_png_RGB565;
#define IMAGE_LIGHT_GREEN_SMALL_PNG          (arm_2d_tile_t*)&c_tile_light_green_small_png_RGB565
#else
extern const arm_2d_tile_t c_tile_light_green_small_png_CCCA8888;
#define IMAGE_LIGHT_GREEN_SMALL_PNG          (arm_2d_tile_t*)&c_tile_light_green_small_png_CCCA8888
#endif
extern const arm_2d_tile_t c_tile_light_green_small_png_A1Mask;
#define IMAGE_LIGHT_GREEN_SMALL_PNG_A1_MASK   (arm_2d_tile_t*)&c_tile_light_green_small_png_A1Mask
extern const arm_2d_tile_t c_tile_light_green_small_png_A2Mask;
#define IMAGE_LIGHT_GREEN_SMALL_PNG_A2_MASK   (arm_2d_tile_t*)&c_tile_light_green_small_png_A2Mask
extern const arm_2d_tile_t c_tile_light_green_small_png_A4Mask;
#define IMAGE_LIGHT_GREEN_SMALL_PNG_A4_MASK   (arm_2d_tile_t*)&c_tile_light_green_small_png_A4Mask
extern const arm_2d_tile_t c_tile_light_green_small_png_Mask;
#define IMAGE_LIGHT_GREEN_SMALL_PNG_MASK     (arm_2d_tile_t*)&c_tile_light_green_small_png_Mask

#ifdef __cplusplus
}
#endif

#endif
