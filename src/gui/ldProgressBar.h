/*
 * Copyright (c) 2023-2025 Ou Jianbo (59935554@qq.com). All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __LD_PROGRESS_BAR_H__
#define __LD_PROGRESS_BAR_H__

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-declarations"
#pragma clang diagnostic ignored "-Wmicrosoft-anon-tag"
#pragma clang diagnostic ignored "-Wpadded"
#endif



/* OOC header, please DO NOT modify  */
#ifdef __LD_PROGRESS_BAR_IMPLEMENT__
#undef __LD_PROGRESS_BAR_IMPLEMENT__
#define __ARM_2D_IMPL__
#elif defined(__LD_PROGRESS_BAR_INHERIT__)
#undef __LD_PROGRESS_BAR_INHERIT__
#define __ARM_2D_INHERIT__
#endif
#include "arm_2d_utils.h"
#include "ldBase.h"

typedef struct ldProgressBar_t ldProgressBar_t;

struct ldProgressBar_t
{
    implement(ldBase_t);
    uint16_t permille;
    ldColor bgColor;
    ldColor fgColor;
    ldColor frameColor;
    arm_2d_tile_t *ptBgImgTile;
    arm_2d_tile_t *ptBgMaskTile;
    arm_2d_tile_t *ptFgImgTile;
    arm_2d_tile_t *ptFgMaskTile;
    arm_2d_tile_t *ptFrameImgTile;
    arm_2d_tile_t *ptFrameMaskTile;
    uint8_t bgOffset;
    uint8_t fgOffset;
    uint8_t frameColorSize;
    int64_t timer;
    bool isHorizontal:1;
    bool isInverted:1;
};

#define PROGRESS_BAR_SPEED              10

ldProgressBar_t* ldProgressBar_init(ld_scene_t *ptScene, ldProgressBar_t *ptWidget, uint16_t nameId, uint16_t parentNameId, int16_t x, int16_t y, int16_t width, int16_t height);
void ldProgressBar_depose(ld_scene_t *ptScene, ldProgressBar_t *ptWidget);
void ldProgressBar_on_load(ld_scene_t *ptScene, ldProgressBar_t *ptWidget);
void ldProgressBar_on_frame_start(ld_scene_t *ptScene, ldProgressBar_t *ptWidget);
void ldProgressBar_on_frame_complete(ld_scene_t *ptScene, ldProgressBar_t *ptWidget);
void ldProgressBar_show(ld_scene_t *pScene, ldProgressBar_t *ptWidget, const arm_2d_tile_t *ptTile, bool bIsNewFrame);

void ldProgressBarSetPercent(ldProgressBar_t *ptWidget,float percent);
void ldProgressBarSetImage(ldProgressBar_t *ptWidget, arm_2d_tile_t *ptBgImgTile, arm_2d_tile_t *ptBgMaskTile, arm_2d_tile_t *ptFgImgTile, arm_2d_tile_t *ptFgMaskTile);
void ldProgressBarSetFrameImage(ldProgressBar_t *ptWidget, arm_2d_tile_t *ptFrameImgTile, arm_2d_tile_t *ptFrameMaskTile);
void ldProgressBarSetColor(ldProgressBar_t *ptWidget, ldColor bgColor, ldColor fgColor);
void ldProgressBarSetFrameColor(ldProgressBar_t *ptWidget, ldColor frameColor, uint8_t frameColorSize);
void ldProgressBarSetHorizontal(ldProgressBar_t *ptWidget,bool isHorizontal);
void ldProgressBarSetInverted(ldProgressBar_t *ptWidget,bool isInverted);

#define ldProgressBarInit(nameId,parentNameId,x,y,width,height) \
        ldProgressBar_init(ptScene,NULL,nameId,parentNameId,x,y,width,height)

#define ldProgressBarSetHidden                ldBaseSetHidden
#define ldProgressBarMove                     ldBaseMove
#define ldProgressBarSetOpacity               ldBaseSetOpacity
#define ldProgressBarSetSelectable           ldBaseSetSelectable
#define ldProgressBarSetSelect               ldBaseSetSelect
#define ldProgressBarSetCorner               ldBaseSetCorner

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#ifdef __cplusplus
}
#endif

#endif
