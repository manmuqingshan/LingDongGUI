#ifndef __UI_FONTS_H__
#define __UI_FONTS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "arm_2d_helper.h"

extern const
struct {
    implement(arm_2d_user_font_t);
    arm_2d_char_idx_t tUTF8Table;
} ARM_2D_FONT_Arial_10_A8;

#define FONT_ARIAL_10          (arm_2d_font_t*)&ARM_2D_FONT_Arial_10_A8

#ifdef __cplusplus
}
#endif

#endif
