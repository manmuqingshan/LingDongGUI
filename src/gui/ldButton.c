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

#define __LD_BUTTON_IMPLEMENT__
#include "__common.h"
#include "arm_2d.h"
#include "arm_2d_helper.h"
#include <assert.h>
#include <string.h>

#include "ldButton.h"

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-warning-option"
#pragma clang diagnostic ignored "-Wreserved-identifier"
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wcast-qual"
#pragma clang diagnostic ignored "-Wcast-align"
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#pragma clang diagnostic ignored "-Wmissing-braces"
#pragma clang diagnostic ignored "-Wunused-const-variable"
#pragma clang diagnostic ignored "-Wmissing-declarations"
#pragma clang diagnostic ignored "-Wmissing-variable-declarations"
#endif

const ldBaseWidgetFunc_t ldButtonFunc = {
    .depose = (ldDeposeFunc_t)ldButton_depose,
    .load = (ldLoadFunc_t)ldButton_on_load,
    .frameStart = (ldFrameStartFunc_t)ldButton_on_frame_start,
    .frameComplete = (ldFrameCompleteFunc_t)ldButton_on_frame_complete,
    .show = (ldShowFunc_t)ldButton_show,
};

static bool slotButtonToggle(ld_scene_t *ptScene,ldMsg_t msg)
{
    ldButton_t *ptWidget;

    ptWidget = msg.ptSender;

    switch (msg.signal)
    {
    case SIGNAL_PRESS:
    {
        if (ptWidget->isCheckable)
        {
            ptWidget->isPressed = !ptWidget->isPressed;
        }
        else
        {
            ptWidget->isPressed = true;
        }
        ptWidget->use_as__ldBase_t.isDirtyRegionUpdate = true;
        break;
    }
    case SIGNAL_RELEASE:
    {
        if (!ptWidget->isCheckable)
        {
            ptWidget->isPressed = false;
        }
        ptWidget->use_as__ldBase_t.isDirtyRegionUpdate = true;
        break;
    }
    default:
        break;
    }

    return false;
}

ldButton_t *ldButton_init(ld_scene_t *ptScene, ldButton_t *ptWidget, uint16_t nameId, uint16_t parentNameId, int16_t x, int16_t y, int16_t width, int16_t height)
{
    assert(NULL != ptScene);
    ldBase_t *ptParent;

    if (NULL == ptWidget)
    {
        ptWidget = ldCalloc(1, sizeof(ldButton_t));
        if (NULL == ptWidget)
        {
            LOG_ERROR("[init failed][button] id:%d", nameId);
            return NULL;
        }
    }
    else
    {
        memset(ptWidget, 0, sizeof(ldButton_t));
    }

    ptParent = ldBaseGetWidget(ptScene->ptNodeRoot,parentNameId);
    assert(NULL != ptParent);
    ldBaseNodeAdd((arm_2d_control_node_t *)ptParent, (arm_2d_control_node_t *)ptWidget);

    ptWidget->use_as__ldBase_t.use_as__arm_2d_control_node_t.tRegion.tLocation.iX = x;
    ptWidget->use_as__ldBase_t.use_as__arm_2d_control_node_t.tRegion.tLocation.iY = y;
    ptWidget->use_as__ldBase_t.use_as__arm_2d_control_node_t.tRegion.tSize.iWidth = width;
    ptWidget->use_as__ldBase_t.use_as__arm_2d_control_node_t.tRegion.tSize.iHeight = height;
    ptWidget->use_as__ldBase_t.nameId = nameId;
    ptWidget->use_as__ldBase_t.widgetType = widgetTypeButton;
    ptWidget->use_as__ldBase_t.ptGuiFunc = &ldButtonFunc;
    ptWidget->use_as__ldBase_t.isDirtyRegionUpdate = true;
    ptWidget->use_as__ldBase_t.isDirtyRegionAutoReset = true;
    ptWidget->use_as__ldBase_t.opacity = 255;
    ptWidget->use_as__ldBase_t.tTempRegion=ptWidget->use_as__ldBase_t.use_as__arm_2d_control_node_t.tRegion;

    ptWidget->releaseColor = __RGB(217, 225, 244);
    ptWidget->pressColor = __RGB(255, 243, 202);


    ldMsgConnect(ptWidget, SIGNAL_PRESS, slotButtonToggle);
    ldMsgConnect(ptWidget, SIGNAL_RELEASE, slotButtonToggle);

    LOG_INFO("[init][button] id:%d, size:%llu", nameId,sizeof (*ptWidget));
    return ptWidget;
}

void ldButton_depose(ld_scene_t *ptScene, ldButton_t *ptWidget)
{
    assert(NULL != ptWidget);
    if (ptWidget == NULL)
    {
        return;
    }
    if(ptWidget->use_as__ldBase_t.widgetType!=widgetTypeButton)
    {
        return;
    }

    LOG_INFO("[depose][button] id:%d", ptWidget->use_as__ldBase_t.nameId);

    ldMsgDelConnect(ptWidget);
    ldBaseNodeRemove((arm_2d_control_node_t*)ptWidget);
    ldFree(ptWidget->pStr);
    ldFree(ptWidget);
}

void ldButton_on_load(ld_scene_t *ptScene, ldButton_t *ptWidget)
{
    assert(NULL != ptWidget);
    if(ptWidget == NULL)
    {
        return;
    }
}

void ldButton_on_frame_start(ld_scene_t *ptScene, ldButton_t *ptWidget)
{
    assert(NULL != ptWidget);
    if(ptWidget == NULL)
    {
        return;
    }
}

void ldButton_on_frame_complete(ld_scene_t *ptScene, ldButton_t *ptWidget)
{
    assert(NULL != ptWidget);
    if(ptWidget == NULL)
    {
        return;
    }
}

void ldButton_show(ld_scene_t *ptScene, ldButton_t *ptWidget, const arm_2d_tile_t *ptTile, bool bIsNewFrame)
{
    assert(NULL != ptWidget);
    if(ptWidget == NULL)
    {
        return;
    }

#if 0
    if (bIsNewFrame) {

    }
#endif

    arm_2d_region_t globalRegion;
    arm_2d_helper_control_get_absolute_region((arm_2d_control_node_t*)ptWidget,&globalRegion,true);

    if(arm_2d_helper_pfb_is_region_active(ptTile,&globalRegion,true))
    {
        arm_2d_container(ptTile, tTarget, &globalRegion)
        {
            if(ldBaseIsHidden((ldBase_t*)ptWidget))
            {
                break;
            }

            if(!ptWidget->isTransparent)
            {
                if ((ptWidget->ptReleaseImgTile == NULL) &&
                        (ptWidget->ptReleaseMaskTile == NULL) &&
                        (ptWidget->ptPressImgTile == NULL) &&
                        (ptWidget->ptPressMaskTile == NULL)) // color
                {

                    if (ptWidget->use_as__ldBase_t.isCorner)
                    {
                        if (ptWidget->isPressed)
                        {
                            draw_round_corner_box(&tTarget,
                                                  NULL,
                                                  ptWidget->pressColor,
                                                  ptWidget->use_as__ldBase_t.opacity,
                                                  bIsNewFrame);
                        }
                        else
                        {
                            draw_round_corner_box(&tTarget,
                                                  NULL,
                                                  ptWidget->releaseColor,
                                                  ptWidget->use_as__ldBase_t.opacity,
                                                  bIsNewFrame);
                        }
                    }
                    else
                    {
                        if (ptWidget->isPressed)
                        {
                            ldBaseColor(&tTarget,
                                        NULL,
                                        ptWidget->pressColor,
                                        ptWidget->use_as__ldBase_t.opacity);
                        }
                        else
                        {
                            ldBaseColor(&tTarget,
                                        NULL,
                                        ptWidget->releaseColor,
                                        ptWidget->use_as__ldBase_t.opacity);
                        }
                    }
                }
                else
                {
                    if (ptWidget->use_as__ldBase_t.isCorner)
                    {
                        if (ptWidget->isPressed)
                        {
                            draw_round_corner_image(ptWidget->ptPressImgTile,
                                                    &tTarget,
                                                    NULL,
                                                    bIsNewFrame,
                                                    ptWidget->use_as__ldBase_t.opacity);
                        }
                        else
                        {
                            draw_round_corner_image(ptWidget->ptReleaseImgTile,
                                                    &tTarget,
                                                    NULL,
                                                    bIsNewFrame,
                                                    ptWidget->use_as__ldBase_t.opacity);
                        }
                    }
                    else
                    {
                        if (ptWidget->isPressed)
                        {
                            ldBaseImage(&tTarget,
                                        NULL,
                                        ptWidget->ptPressImgTile,
                                        ptWidget->ptPressMaskTile,
                                        ptWidget->pressColor,
                                        ptWidget->use_as__ldBase_t.opacity);
                        }
                        else
                        {
                            ldBaseImage(&tTarget,
                                        NULL,
                                        ptWidget->ptReleaseImgTile,
                                        ptWidget->ptReleaseMaskTile,
                                        ptWidget->releaseColor,
                                        ptWidget->use_as__ldBase_t.opacity);
                        }
                    }
                }

                LD_BASE_WIDGET_SELECT;
            }

            arm_2d_op_wait_async(NULL);

            if(ptWidget->pStr!=NULL)
            {
                ldBaseLabel(&tTarget,
                            &tTarget_canvas,
                            ptWidget->pStr,
                            ptWidget->ptFont,
                            ARM_2D_ALIGN_CENTRE,
                            ptWidget->charColor,
                            ptWidget->use_as__ldBase_t.opacity);
                arm_2d_op_wait_async(NULL);
            }
        }
    }
}

void ldButtonSetColor(ldButton_t* ptWidget, ldColor releaseColor, ldColor pressColor)
{
    assert(NULL != ptWidget);
    if(ptWidget == NULL)
    {
        return;
    }
    ptWidget->use_as__ldBase_t.isDirtyRegionUpdate = true;
    ptWidget->releaseColor=releaseColor;
    ptWidget->pressColor=pressColor;
}

void ldButtonSetImage(ldButton_t* ptWidget,arm_2d_tile_t* ptReleaseImgTile,arm_2d_tile_t* ptReleaseMaskTile,arm_2d_tile_t* ptPressImgTile,arm_2d_tile_t* ptPressMaskTile)
{
    assert(NULL != ptWidget);
    if(ptWidget == NULL)
    {
        return;
    }
    ptWidget->use_as__ldBase_t.isDirtyRegionUpdate = true;
    ptWidget->ptReleaseImgTile=ptReleaseImgTile;
    ptWidget->ptReleaseMaskTile=ptReleaseMaskTile;
    ptWidget->ptPressImgTile=ptPressImgTile;
    ptWidget->ptPressMaskTile=ptPressMaskTile;
}

void ldButtonSetTransparent(ldButton_t* ptWidget,bool isTransparent)
{
    assert(NULL != ptWidget);
    if(ptWidget == NULL)
    {
        return;
    }
    ptWidget->use_as__ldBase_t.isDirtyRegionUpdate = true;
    ptWidget->isTransparent=isTransparent;
}

void ldButtonSetFont(ldButton_t *ptWidget, arm_2d_font_t *ptFont)
{
    assert(NULL != ptWidget);
    if(ptWidget == NULL)
    {
        return;
    }
    ptWidget->use_as__ldBase_t.isDirtyRegionUpdate = true;
    ptWidget->ptFont=ptFont;
}

void ldButtonSetText(ldButton_t* ptWidget,uint8_t *pStr)
{
    assert(NULL != ptWidget);
    if(ptWidget == NULL)
    {
        return;
    }
    ptWidget->use_as__ldBase_t.isDirtyRegionUpdate = true;
    ldFree(ptWidget->pStr);
    ptWidget->pStr=ldCalloc(1,strlen((char*)pStr)+1);
    if(ptWidget->pStr!=NULL)
    {
        strcpy((char*)ptWidget->pStr,(char*)pStr);
    }
}

void ldButtonSetTextColor(ldButton_t* ptWidget,ldColor charColor)
{
    assert(NULL != ptWidget);
    if(ptWidget == NULL)
    {
        return;
    }
    ptWidget->use_as__ldBase_t.isDirtyRegionUpdate = true;
    ptWidget->charColor=charColor;
}

void ldButtonSetCheckable(ldButton_t *ptWidget,bool isCheckable)
{
    assert(NULL != ptWidget);
    if(ptWidget == NULL)
    {
        return;
    }
    ptWidget->isCheckable=isCheckable;
}

void ldButtonSetKeyValue(ldButton_t *ptWidget,uint32_t value)
{
    assert(NULL != ptWidget);
    if(ptWidget == NULL)
    {
        return;
    }
    ptWidget->keyValue=value;
}

bool ldButtonActionIsPressById(uint16_t nameId,ld_scene_t *ptScene)
{
    ldButton_t *ptWidget=ldBaseGetWidgetById(nameId);
    if(ptWidget == NULL)
    {
        return 0;
    }
    return ptWidget->isPressed;
}

void ldButtonSetPress(ldButton_t *ptWidget,bool isPress)
{
    assert(NULL != ptWidget);
    if(ptWidget == NULL)
    {
        return;
    }
    ptWidget->isPressed=isPress;
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif
