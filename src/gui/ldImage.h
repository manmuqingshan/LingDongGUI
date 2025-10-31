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

#ifndef __LD_IMAGE_H__
#define __LD_IMAGE_H__

#ifdef   __cplusplus
extern "C" {
#endif

#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wmissing-declarations"
#   pragma clang diagnostic ignored "-Wmicrosoft-anon-tag"
#   pragma clang diagnostic ignored "-Wpadded"
#endif

/* OOC header, please DO NOT modify  */
#ifdef __LD_IMAGE_IMPLEMENT__
#   undef   __LD_IMAGE_IMPLEMENT__
#   define  __ARM_2D_IMPL__
#elif defined(__LD_IMAGE_INHERIT__)
#   undef   __LD_IMAGE_INHERIT__
#   define __ARM_2D_INHERIT__
#endif

#include "arm_2d_utils.h"
#include "ldBase.h"

typedef struct ldImage_t ldImage_t;

struct ldImage_t {
    implement(ldBase_t);
    ldColor bgColor;
    arm_2d_tile_t* ptImgTile;
    arm_2d_tile_t* ptMaskTile;
    bool isTransparent:1;//window专用
};

ldImage_t* ldImage_init(ld_scene_t *ptScene, ldImage_t *ptWidget, uint16_t nameId, uint16_t parentNameId, int16_t x, int16_t y, int16_t width, int16_t height, arm_2d_tile_t* ptImgTile, arm_2d_tile_t* ptMaskTile, bool isWindow);
void ldImage_depose(ld_scene_t *ptScene, ldImage_t *ptWidget);
void ldImage_on_load(ld_scene_t *ptScene, ldImage_t *ptWidget);
void ldImage_on_frame_start(ld_scene_t *ptScene, ldImage_t *ptWidget);
void ldImage_on_frame_complete(ld_scene_t *ptScene, ldImage_t *ptWidget);
void ldImage_show(ld_scene_t *ptScene,ldImage_t *ptWidget,const arm_2d_tile_t *ptTile,bool bIsNewFrame);

void ldImageSetBackgroundColor(ldImage_t *ptWidget,ldColor bgColor);
void ldImageSetImage(ldImage_t *ptWidget, arm_2d_tile_t* ptImgTile, arm_2d_tile_t* ptMaskTile);

#define ldImageInit(nameId,parentNameId,x,y,width,height,ptImgTile,ptMaskTile,isWindow) \
        ldImage_init(ptScene,NULL,nameId,parentNameId,x,y,width,height,ptImgTile,ptMaskTile,isWindow)

#define ldImageSetHidden                ldBaseSetHidden
#define ldImageMove                     ldBaseMove
#define ldImageSetOpacity               ldBaseSetOpacity
#define ldImageSetSelectable            ldBaseSetSelectable
#define ldImageSetSelect                ldBaseSetSelect
#define ldImageSetCorner                ldBaseSetCorner

#if defined(__clang__)
#   pragma clang diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif

#endif
