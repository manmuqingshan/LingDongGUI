#ifndef _DATA_H_
#define _DATA_H_

#include "arm_2d.h"
#include "ldConfig.h"

#define FONT_ARIAL_10 (arm_2d_font_t*)ldBaseGetVresFont(0x00000000)

#define IMAGE_LIGHT_RED_SMALL_PNG_MASK (arm_2d_tile_t*)ldBaseGetVresImage(0x00001DB8)
#define IMAGE_LIGHT_RED_SMALL_PNG_A1_MASK (arm_2d_tile_t*)ldBaseGetVresImage(0x000021C8)
#define IMAGE_LIGHT_RED_SMALL_PNG_A2_MASK (arm_2d_tile_t*)ldBaseGetVresImage(0x00002258)
#define IMAGE_LIGHT_RED_SMALL_PNG_A4_MASK (arm_2d_tile_t*)ldBaseGetVresImage(0x00002368)
#if LD_CFG_COLOR_DEPTH == 8
#define IMAGE_LIGHT_RED_SMALL_PNG (arm_2d_tile_t*)ldBaseGetVresImage(0x00002578)
#elif LD_CFG_COLOR_DEPTH == 16
#define IMAGE_LIGHT_RED_SMALL_PNG (arm_2d_tile_t*)ldBaseGetVresImage(0x00002988)
#else
#define IMAGE_LIGHT_RED_SMALL_PNG (arm_2d_tile_t*)ldBaseGetVresImage(0x00003198)
#endif
#define IMAGE_LIGHT_GREEN_SMALL_PNG_MASK (arm_2d_tile_t*)ldBaseGetVresImage(0x000041A8)
#define IMAGE_LIGHT_GREEN_SMALL_PNG_A1_MASK (arm_2d_tile_t*)ldBaseGetVresImage(0x000045B8)
#define IMAGE_LIGHT_GREEN_SMALL_PNG_A2_MASK (arm_2d_tile_t*)ldBaseGetVresImage(0x00004648)
#define IMAGE_LIGHT_GREEN_SMALL_PNG_A4_MASK (arm_2d_tile_t*)ldBaseGetVresImage(0x00004758)
#if LD_CFG_COLOR_DEPTH == 8
#define IMAGE_LIGHT_GREEN_SMALL_PNG (arm_2d_tile_t*)ldBaseGetVresImage(0x00004968)
#elif LD_CFG_COLOR_DEPTH == 16
#define IMAGE_LIGHT_GREEN_SMALL_PNG (arm_2d_tile_t*)ldBaseGetVresImage(0x00004D78)
#else
#define IMAGE_LIGHT_GREEN_SMALL_PNG (arm_2d_tile_t*)ldBaseGetVresImage(0x00005588)
#endif

#endif // _DATA_H_
