#ifndef _LD_CONFIG_H_
#define _LD_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"
#include "arm_2d_cfg.h"
#include "Virtual_TFT_Port.h"

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

// base config

// <o> Select the screen colour depth
//     <8=>     8 Bits
//     <16=>    16Bits
//     <32=>    32Bits
// <i> The colour depth of your screen
#define LD_CFG_COLOR_DEPTH                        (16)

// <o>Width of the screen <8-32767>
// <i> The width of your screen
#define LD_CFG_SCEEN_WIDTH                        (VT_WIDTH)

// <o>Height of the screen <8-32767>
// <i> The height of your screen
#define LD_CFG_SCEEN_HEIGHT                       (VT_HEIGHT)

// <o>Width of the PFB block
// <i> The width of your PFB block size
#define LD_CFG_PFB_WIDTH                          (LD_CFG_SCEEN_WIDTH)

// <o>Height of the PFB block
// <i> The height of your PFB block size
#define LD_CFG_PFB_HEIGHT                         (LD_CFG_SCEEN_HEIGHT/2)

// <o>LingDongGui memory size
// <i> The size of memory allocated to the ldgui
#define LD_MEM_SIZE                               (1024*1024) //BYTE

// <o>LingDongGui signal emit buffer size
// <i> The size of signal emit buffer to the ldgui
#define LD_EMIT_SIZE                              8

// <o>Number of project pages
// <i> Maximum number of pages
#define LD_PAGE_MAX                               (1)

// <q>Dirty Region Function
// <i> It is recommended to enable this option for applications that do not refresh full screen
#define USE_DIRTY_REGION                          (1)

// <q>External NOR support
// <i> Read external nor, please enable this option
#define USE_VIRTUAL_RESOURCE                      (0)

// widget config

// <q>Opacity support
// <i> There is no need to adjust the opacity of the widget. Please turn off this option
#define USE_OPACITY                               (0)

// <q>tlsf support
// <i> Two Level Segregated Fit memory allocator
#define USE_TLSF                                  (0)

// <q>Radia menu's scale function support
// <i> Radia menu's scale function support
#define USE_RADIA_MENU_SCALE                      (0)

// debug config

// <o> Log output level
//     <0=>    LOG_LEVEL_NONE
//     <2=>    LOG_LEVEL_ERROR
//     <3=>    LOG_LEVEL_WARNING
//     <4=>    LOG_LEVEL_INFO
//     <5=>    LOG_LEVEL_DEBUG
// <i> Do not use log. Please select LOG_LEVEL_NONE
#define USE_LOG_LEVEL                             (5)

#define LD_DEBUG                                  (0)
#define __DISP0_CFG_DEBUG_DIRTY_REGIONS__         (0)

// <<< end of configuration section >>>

// do not eidt below

#define __DISP0_CFG_DISABLE_NAVIGATION_LAYER__    (1)
#define __DISP0_CFG_DISABLE_DEFAULT_SCENE__       (1)
#define __DISP0_CFG_PFB_BLOCK_WIDTH__             LD_CFG_PFB_WIDTH
#define __DISP0_CFG_PFB_BLOCK_HEIGHT__            LD_CFG_PFB_HEIGHT
#define __DISP0_CFG_COLOUR_DEPTH__                LD_CFG_COLOR_DEPTH
#define __DISP0_CFG_SCEEN_WIDTH__                 LD_CFG_SCEEN_WIDTH
#define __DISP0_CFG_SCEEN_HEIGHT__                LD_CFG_SCEEN_HEIGHT
#if USE_VIRTUAL_RESOURCE == 0
#define __DISP0_CFG_VIRTUAL_RESOURCE_HELPER__     (0)
#else
#define __DISP0_CFG_VIRTUAL_RESOURCE_HELPER__     (2)
#endif

#if __GLCD_CFG_COLOUR_DEPTH__ != LD_CFG_COLOR_DEPTH
#error parameter configuration error. (arm_2d_cfg.h) __GLCD_CFG_COLOUR_DEPTH__ not equal to LD_CFG_COLOR_DEPTH
#endif

bool ldCfgTouchGetPoint(int16_t *x,int16_t *y);

// user key num
#define KEY_NUM_UP   0
#define KEY_NUM_DOWN   1
#define KEY_NUM_LEFT   2
#define KEY_NUM_RIGHT   3
#define KEY_NUM_ENTER   4
#define KEY_NUM_ESC   5



#ifdef __cplusplus
}
#endif

#endif //_LD_CONFIG_H_