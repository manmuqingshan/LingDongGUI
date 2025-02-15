/*
 * Copyright (c) 2023-2024 Ou Jianbo (59935554@qq.com). All rights reserved.
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

#ifndef __LD_KEYBOARD_H__
#define __LD_KEYBOARD_H__

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
#ifdef __LD_KEYBOARD_IMPLEMENT__
#undef __LD_KEYBOARD_IMPLEMENT__
#define __ARM_2D_IMPL__
#elif defined(__LD_KEYBOARD_INHERIT__)
#undef __LD_KEYBOARD_INHERIT__
#define __ARM_2D_INHERIT__
#endif
#include "arm_2d_utils.h"
#include "ldBase.h"

typedef struct ldKeyboard_t ldKeyboard_t;

struct ldKeyboard_t
{
    implement(ldBase_t);
//    ARM_PRIVATE(
//            ld_scene_t *ptScene;
//    )
    uint8_t **ppStr;
    arm_2d_font_t *ptFont;
    arm_2d_location_t clickPoint;
//    arm_2d_region_t targetDirtyRegion;
    ldEditType_t editType;
    uint16_t editorId;
    uint8_t strMax;
    uint8_t kbValue;

    bool isNumber:1;
    bool isSymbol:1;
    bool isClick:1;
    uint8_t upperState:2;
    bool isWaitInit:1;
};

ldKeyboard_t* ldKeyboard_init(ld_scene_t *ptScene, ldKeyboard_t *ptWidget, uint16_t nameId, uint16_t parentNameId, arm_2d_font_t *ptFont);
void ldKeyboard_depose( ldKeyboard_t *ptWidget);
void ldKeyboard_on_load( ldKeyboard_t *ptWidget);
void ldKeyboard_on_frame_start( ldKeyboard_t *ptWidget);
void ldKeyboard_show(ld_scene_t *pScene, ldKeyboard_t *ptWidget, const arm_2d_tile_t *ptTile, bool bIsNewFrame);

#define ldKeyboardInit(nameId,parentNameId,ptFont) \
        ldKeyboard_init(ptScene,NULL,nameId,parentNameId,ptFont)

#define ldKeyboardSetHidden                ldBaseSetHidden
#define ldKeyboardMove                     ldBaseMove
#define ldKeyboardSetOpacity               ldBaseSetOpacity

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#ifdef __cplusplus
}
#endif

#endif
