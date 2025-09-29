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

#define __ARM_2D_IMPL__
#define __ARM_2D_INHERIT__
#include "arm_2d.h"
#include "ldGui.h"
#include "ldScene0.h"
#include "ldScene1.h"

static volatile arm_2d_location_t pressLocation;
static volatile int16_t deltaMoveTime;
static volatile arm_2d_location_t prevLocation;
static void *prevWidget;
static uint8_t pageNumNow=0;
uint8_t cursorBlinkCount=0;
bool cursorBlinkFlag=false;

#if USE_SCENE_SWITCHING == 2
bool isGuiSwthcnScene=false;
static uint8_t sysSceneNum=0;
#endif
static ldPageFuncGroup_t *ptSysGuiFuncGroup[2]={0};

#ifndef LD_EMIT_SIZE
#define LD_EMIT_SIZE                    8
#endif

bool isFullWidgetUpdate=false;

void ldGuiDraw(ld_scene_t *ptScene,arm_2d_tile_t *ptTile,bool bIsNewFrame)
{
    // draw ldgui background
    if(ptScene->ptNodeRoot!=NULL)
    {
        ((ldBase_t*)ptScene->ptNodeRoot)->ptGuiFunc->show(ptScene,ptScene->ptNodeRoot,ptTile,bIsNewFrame);
    }

    // draw arm 2d code
    if(ptScene->ldGuiFuncGroup->draw!=NULL)
    {
        ptScene->ldGuiFuncGroup->draw(ptScene,ptTile,bIsNewFrame);
    }

    // draw ldgui code
    if(ptScene->ptNodeRoot!=NULL)
    {
        ldBase_t *child=ldBaseGetChildList((ldBase_t*)ptScene->ptNodeRoot);
        if(child!=NULL)
        {
            arm_ctrl_enum(child, ptItem, PREORDER_TRAVERSAL) {
                ((ldBase_t*)ptItem)->ptGuiFunc->show(ptScene,ptItem,ptTile,bIsNewFrame);
            }
        }
    }
}


void ldGuiClickedAction(ld_scene_t *ptScene,uint8_t touchSignal,arm_2d_location_t tLocation)
{
    ldBase_t *ptWidget;
    uint64_t u64Temp=0;

    switch(touchSignal)
    {
    case SIGNAL_NO_OPERATION:
    {
        break;
    }
    case SIGNAL_PRESS:
    {
        if(ptScene->ptNodeRoot!=NULL)
        {
            ptWidget=(ldBase_t*)arm_2d_helper_control_find_node_with_location(ptScene->ptNodeRoot,tLocation);
        }

#if (USE_LOG_LEVEL>=LOG_LEVEL_DEBUG)
        if(ptWidget!=NULL)
        {
            LOG_DEBUG("click widget id:%d",ptWidget->nameId);
        }
#endif

        prevLocation=tLocation;
        prevWidget=ptWidget;//准备数据,释放时候使用
        pressLocation=tLocation;
        deltaMoveTime=arm_2d_helper_convert_ticks_to_ms(arm_2d_helper_get_system_timestamp());

        if(ptWidget!=NULL)
        {
            u64Temp=tLocation.iX;
            u64Temp<<=16;
            u64Temp+=tLocation.iY;
            emit(ptWidget->nameId,touchSignal,u64Temp);
        }
        break;
    }
    case SIGNAL_HOLD_DOWN:
    {
        if((prevLocation.iX!=tLocation.iX)||(prevLocation.iY!=tLocation.iY))
        {
            ptWidget=prevWidget;//不可以把static变量作为函数变量调用
            if(ptWidget!=NULL)
            {
                u64Temp=tLocation.iX-pressLocation.iX;
                u64Temp<<=16;
                u64Temp+=tLocation.iY-pressLocation.iY;
                u64Temp<<=16;
                u64Temp+=tLocation.iX;
                u64Temp<<=16;
                u64Temp+=tLocation.iY;

                emit(ptWidget->nameId,touchSignal,u64Temp);
            }
            prevLocation=tLocation;
        }
        break;
    }
    case SIGNAL_RELEASE:
    {
        ptWidget=prevWidget;
        if(ptWidget!=NULL)
        {
            //cal speed
            deltaMoveTime=arm_2d_helper_convert_ticks_to_ms(arm_2d_helper_get_system_timestamp())-deltaMoveTime;
            pressLocation.iX=(prevLocation.iX-pressLocation.iX);
            pressLocation.iY=(prevLocation.iY-pressLocation.iY);
            pressLocation.iX=(pressLocation.iX*100)/deltaMoveTime;
            pressLocation.iY=(pressLocation.iY*100)/deltaMoveTime;

            // x speed,y speed,x,y
            u64Temp=pressLocation.iX;
            u64Temp<<=16;
            u64Temp+=pressLocation.iY;
            u64Temp<<=16;
            u64Temp+=prevLocation.iX;
            u64Temp<<=16;
            u64Temp+=prevLocation.iY;

            emit(ptWidget->nameId,touchSignal,u64Temp);
        }
        break;
    }
    default:
        break;
    }
}

#define TOUCH_NO_CLICK           0
#define TOUCH_CLICK              1

void ldGuiTouchProcess(ld_scene_t *ptScene)
{
    arm_2d_location_t clickLocation;
    bool nowState;
    static bool prevState=TOUCH_NO_CLICK;
    uint8_t touchSignal=SIGNAL_NO_OPERATION;

    nowState = ldCfgTouchGetPoint(&clickLocation.iX,&clickLocation.iY);

    if(nowState==TOUCH_CLICK)
    {
        if(prevState==TOUCH_NO_CLICK)//按下,                下降沿触发
        {
            touchSignal=SIGNAL_PRESS;
        }
        else// prevState==TOUCH_CLICK 按住                低电平
        {
            touchSignal=SIGNAL_HOLD_DOWN;
        }
    }
    else// nowState==TOUCH_NO_CLICK 无按下
    {
        if(prevState==TOUCH_NO_CLICK)//无按下                高电平
        {
            touchSignal=SIGNAL_NO_OPERATION;
        }
        else// prevState==TOUCH_CLICK 按下,上升沿触发       上降沿触发
        {
            touchSignal=SIGNAL_RELEASE;
        }
    }
    prevState=nowState;

    ldGuiClickedAction(ptScene,touchSignal,clickLocation);
}

void ldGuiSceneInit(ld_scene_t *ptScene)
{
    ldMsgInit(&ptScene->ptMsgQueue,LD_EMIT_SIZE);

    if(ptScene->ldGuiFuncGroup!=NULL)
    {
        ptScene->ldGuiFuncGroup->init(ptScene);
    }
#if USE_SCENE_SWITCHING == 2
    isGuiSwthcnScene=false;
#endif
    ldBaseFocusNavigateInit();
    LOG_INFO("[sys] page %s init",ptScene->ldGuiFuncGroup->pageName);
}

void ldGuiUpdateScene(void)
{
    isFullWidgetUpdate=true;
}

void ldGuiFrameStart(ld_scene_t *ptScene)
{
    if(isFullWidgetUpdate==true)
    {
        arm_2d_scene_player_update_scene_background(ptScene->use_as__arm_2d_scene_t.ptPlayer);
        isFullWidgetUpdate=false;
    }

    if(ptScene->ptNodeRoot!=NULL)
    {
        arm_ctrl_enum(ptScene->ptNodeRoot, ptItem, PREORDER_TRAVERSAL)
        {
            if(((ldBase_t*)ptItem)->ptGuiFunc->frameStart!=NULL)
            {
                ((ldBase_t*)ptItem)->ptGuiFunc->frameStart(ptScene,ptItem);
            }
        }
    }

    if(ldTimeOut(SYS_TICK_CYCLE_MS,true))
    {
        xBtnTick(SYS_TICK_CYCLE_MS,ptScene);
        cursorBlinkCount++;
    }

    if(ptScene->ldGuiFuncGroup!=NULL)
    {
        if(ptScene->ldGuiFuncGroup->loop)
        {
            ptScene->ldGuiFuncGroup->loop(ptScene);
        }
    }
}

void ldGuiLoad(ld_scene_t *ptScene)
{
    if(ptScene->ptNodeRoot!=NULL)
    {
        arm_ctrl_enum(ptScene->ptNodeRoot, ptItem, PREORDER_TRAVERSAL)
        {
            if(((ldBase_t*)ptItem)->ptGuiFunc->load!=NULL)
            {
                ((ldBase_t*)ptItem)->ptGuiFunc->load(ptScene,ptItem);
            }
        }
    }
}

void ldGuiDespose(ld_scene_t *ptScene)
{
    if(ptScene->ldGuiFuncGroup!=NULL)
    {
        if(ptScene->ldGuiFuncGroup->quit)
        {
            ptScene->ldGuiFuncGroup->quit(ptScene);
        }
    }

    if(ptScene->ptNodeRoot!=NULL)
    {
        arm_ctrl_enum(ptScene->ptNodeRoot, ptItem, POSTORDER_TRAVERSAL)
        {
            if(((ldBase_t *)ptItem))
            {
                ((ldBase_t *)ptItem)->ptGuiFunc->depose(ptScene,ptItem);
            }
        }
    }

    LOG_INFO("[sys] page %s quit",ptScene->ldGuiFuncGroup->pageName);
}

void ldGuiFrameComplete(ld_scene_t *ptScene)
{
    if(ptScene->ptNodeRoot!=NULL)
    {
        arm_ctrl_enum(ptScene->ptNodeRoot, ptItem, PREORDER_TRAVERSAL)
        {
            if(((ldBase_t*)ptItem)->ptGuiFunc->frameComplete!=NULL)
            {
                ((ldBase_t*)ptItem)->ptGuiFunc->frameComplete(ptScene,ptItem);
            }
        }
    }

#if USE_SCENE_SWITCHING == 2
    if(isGuiSwthcnScene)
    {
        isGuiSwthcnScene=false;
        arm_2d_scene_player_switch_to_next_scene(ptScene->use_as__arm_2d_scene_t.ptPlayer);
        prevWidget=NULL;
    }
#elif USE_SCENE_SWITCHING == 1
    if(ptSysGuiFuncGroup[0]!=ptSysGuiFuncGroup[1])
    {
        ldGuiDespose(ptScene);
        ptSysGuiFuncGroup[0]=ptSysGuiFuncGroup[1];
        ptScene->ldGuiFuncGroup=ptSysGuiFuncGroup[0];
        arm_2d_scene_player_update_scene_background(ptScene->use_as__arm_2d_scene_t.ptPlayer);
        ldGuiSceneInit(ptScene);
        prevWidget=NULL;
    }
#else
    if(ptSysGuiFuncGroup[0]!=ptSysGuiFuncGroup[1])
    {
        ldGuiDespose(ptScene);
        ptSysGuiFuncGroup[1]=ptSysGuiFuncGroup[0];
        arm_2d_scene_player_update_scene_background(ptScene->use_as__arm_2d_scene_t.ptPlayer);
        ldGuiSceneInit(ptScene);
        prevWidget=NULL;
    }
#endif
}

void __ldGuiJumpPage(ldPageFuncGroup_t *ptFuncGroup,arm_2d_scene_switch_mode_t *ptMode,uint16_t switchTimeMs)
{
#if USE_SCENE_SWITCHING == 2

    if (sysSceneNum ==0)
    {
        sysSceneNum = 1;
    }
    else
    {
        sysSceneNum = 0;
    }

    ptSysGuiFuncGroup[sysSceneNum]=ptFuncGroup;

    __arm_2d_scene_player_set_switching_mode(&DISP0_ADAPTER,ptMode,0);
    arm_2d_scene_player_set_switching_period(&DISP0_ADAPTER, switchTimeMs);
    isGuiSwthcnScene=true;
#elif USE_SCENE_SWITCHING == 1 || USE_SCENE_SWITCHING == 0
    ptSysGuiFuncGroup[1]=ptFuncGroup;
#endif
}

#if USE_SCENE_SWITCHING == 2
void scene0_loader(void)
{
    __arm_2d_scene0_init(&DISP0_ADAPTER,NULL,ptSysGuiFuncGroup[0]);
}

void scene1_loader(void)
{
    __arm_2d_scene1_init(&DISP0_ADAPTER,NULL,ptSysGuiFuncGroup[1]);
}

typedef void scene_loader_t(void);

static scene_loader_t * const c_SceneLoaders[] = {
    scene0_loader,
    scene1_loader,
};

void before_scene_switching_handler(void *pTarget,arm_2d_scene_player_t *ptPlayer,arm_2d_scene_t *ptScene)
{
    c_SceneLoaders[sysSceneNum]();
}
#endif

void ldGuiInit(ldPageFuncGroup_t *ptFuncGroup)
{
    if(ptFuncGroup==NULL)
    {
        return;
    }
    ptSysGuiFuncGroup[0]=ptFuncGroup;
    ptSysGuiFuncGroup[1]=ptFuncGroup;
#if USE_SCENE_SWITCHING == 2
    arm_2d_scene_player_register_before_switching_event_handler(&DISP0_ADAPTER,before_scene_switching_handler);
    arm_2d_scene_player_set_switching_mode( &DISP0_ADAPTER,ARM_2D_SCENE_SWITCH_MODE_NONE);
    arm_2d_scene_player_set_switching_period(&DISP0_ADAPTER, 0);
    arm_2d_scene_player_switch_to_next_scene(&DISP0_ADAPTER);
#elif USE_SCENE_SWITCHING == 1 || USE_SCENE_SWITCHING == 0
    __arm_2d_scene0_init(&DISP0_ADAPTER,NULL,ptSysGuiFuncGroup[0]);
#endif
}
