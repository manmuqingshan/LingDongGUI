#ifndef _DATA_H_
#define _DATA_H_

#include "arm_2d.h"
#include "ldConfig.h"

#define FONT_ARIAL_10 (arm_2d_font_t*)ldBaseGetVresFont(0x00000000)

#define IMAGE_LIGHT_RED_SMALL_PNG_MASK (arm_2d_tile_t*)ldBaseGetVresImage(0x00001E70)
#define IMAGE_LIGHT_RED_SMALL_PNG_A1_MASK (arm_2d_tile_t*)ldBaseGetVresImage(0x00002280)
#define IMAGE_LIGHT_RED_SMALL_PNG_A2_MASK (arm_2d_tile_t*)ldBaseGetVresImage(0x00002310)
#define IMAGE_LIGHT_RED_SMALL_PNG_A4_MASK (arm_2d_tile_t*)ldBaseGetVresImage(0x00002420)
#if LD_CFG_COLOR_DEPTH == 8
#define IMAGE_LIGHT_RED_SMALL_PNG (arm_2d_tile_t*)ldBaseGetVresImage(0x00002630)
#elif LD_CFG_COLOR_DEPTH == 16
#define IMAGE_LIGHT_RED_SMALL_PNG (arm_2d_tile_t*)ldBaseGetVresImage(0x00002A40)
#else
#define IMAGE_LIGHT_RED_SMALL_PNG (arm_2d_tile_t*)ldBaseGetVresImage(0x00003250)
#endif
#define IMAGE_LIGHT_GREEN_SMALL_PNG_MASK (arm_2d_tile_t*)ldBaseGetVresImage(0x00004260)
#define IMAGE_LIGHT_GREEN_SMALL_PNG_A1_MASK (arm_2d_tile_t*)ldBaseGetVresImage(0x00004670)
#define IMAGE_LIGHT_GREEN_SMALL_PNG_A2_MASK (arm_2d_tile_t*)ldBaseGetVresImage(0x00004700)
#define IMAGE_LIGHT_GREEN_SMALL_PNG_A4_MASK (arm_2d_tile_t*)ldBaseGetVresImage(0x00004810)
#if LD_CFG_COLOR_DEPTH == 8
#define IMAGE_LIGHT_GREEN_SMALL_PNG (arm_2d_tile_t*)ldBaseGetVresImage(0x00004A20)
#elif LD_CFG_COLOR_DEPTH == 16
#define IMAGE_LIGHT_GREEN_SMALL_PNG (arm_2d_tile_t*)ldBaseGetVresImage(0x00004E30)
#else
#define IMAGE_LIGHT_GREEN_SMALL_PNG (arm_2d_tile_t*)ldBaseGetVresImage(0x00005640)
#endif

#endif // _DATA_H_
