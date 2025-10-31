#include "uiStartup.h"
#include "ldGui.h"

void uiStartupInit(ld_scene_t* ptScene);
void uiStartupLoop(ld_scene_t* ptScene);
void uiStartupQuit(ld_scene_t* ptScene);
void uiStartupDraw(ld_scene_t* ptScene, arm_2d_tile_t *ptTile, bool bIsNewFrame);

const ldPageFuncGroup_t uiStartupFunc={
    .init=uiStartupInit,
    .loop=uiStartupLoop,
    .quit=uiStartupQuit,
    .draw=uiStartupDraw,
#if (USE_LOG_LEVEL>=LOG_LEVEL_INFO)
    .pageName="uiStartup",
#endif
};

void uiStartupInit(ld_scene_t* ptScene)
{
    void *obj,*win;

    obj=ldWindowInit(ID_BG, ID_BG, 0, 0, LD_CFG_SCREEN_WIDTH, LD_CFG_SCREEN_HEIGHT);

    obj=ldWindowInit(ID_WIN, ID_BG, LD_CFG_SCREEN_WIDTH/3,LD_CFG_SCREEN_HEIGHT/3,LD_CFG_SCREEN_WIDTH/3,LD_CFG_SCREEN_HEIGHT/3);
    ldWindowSetColor(obj,GLCD_COLOR_LIGHT_GREY);

}

void uiStartupLoop(ld_scene_t* ptScene)
{




}

void uiStartupDraw(ld_scene_t *ptScene,arm_2d_tile_t *ptTile,bool bIsNewFrame)
{

}

void uiStartupQuit(ld_scene_t* ptScene)
{




}
