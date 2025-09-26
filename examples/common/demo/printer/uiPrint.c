#include "uiPrint.h"
#include "ldGui.h"

void uiPrintInit(ld_scene_t* ptScene);
void uiPrintLoop(ld_scene_t* ptScene);
void uiPrintQuit(ld_scene_t* ptScene);
void uiPrintDraw(ld_scene_t *ptScene,arm_2d_tile_t *ptTile,bool bIsNewFrame);

const ldPageFuncGroup_t uiPrintFunc={
    .init=uiPrintInit,
    .loop=uiPrintLoop,
    .quit=uiPrintQuit,
    .draw=uiPrintDraw,
#if (USE_LOG_LEVEL>=LOG_LEVEL_INFO)
    .pageName="uiPrint",
#endif
};

uint8_t gPrintImgNum=0;

static arm_2d_tile_t *imgList[8]={IMAGE_ALARMCLOCK_S_PNG,IMAGE_BLOCKRABBIT_S_PNG,IMAGE_CAKE_S_PNG,IMAGE_DOLL_S_PNG,IMAGE_MILK_S_PNG,IMAGE_MUG_S_PNG,IMAGE_SMALLROOM_S_PNG};

static uint8_t *pListName[]={"闹钟","方块兔","巧克力蛋糕","福娃","奶牛盒","马克杯","小房间"};

static bool slotJumpMain(ld_scene_t *ptScene,ldMsg_t msg)
{
    ldGuiJumpPageFast(uiMainFunc);
    return false;
}

static bool slotShowImg(ld_scene_t *ptScene,ldMsg_t msg)
{
    ldImage_t* ptWidget = ldBaseGetWidgetById(ID_IMG);
    ldImageSetImage(ptWidget,imgList[msg.value],NULL);
    return false;
}

static bool slotJumpPrinting(ld_scene_t *ptScene,ldMsg_t msg)
{
    ldList_t* ptWidget = ldBaseGetWidgetById(ID_LIST);
    gPrintImgNum=ldListGetSelectItem(ptWidget);
    ldGuiJumpPageFast(uiPrintingFunc);
    return false;
}



void uiPrintInit(ld_scene_t* ptScene)
{
    void *obj,*win;

    obj=ldWindowInit(ID_BG, ID_BG, 0, 0, LD_CFG_SCEEN_WIDTH, LD_CFG_SCEEN_HEIGHT);
    ldWindowSetColor(obj,GLCD_COLOR_BLACK);

    obj=ldButtonInit(ID_BTN_RET,ID_BG,20,5,80,40);
    ldButtonSetFont(obj,FONT_ALIBABAPUHUITI_3_55_REGULAR_18);
    ldButtonSetColor(obj,__RGB(0x64,0x95,0xED),__RGB(0x41,0x69,0xE1));
    ldButtonSetCorner(obj,true);
    ldButtonSetText(obj,"返回");

    connect(ID_BTN_RET,SIGNAL_RELEASE,slotJumpMain);

    obj=ldListInit(ID_LIST,ID_BG,20,55,250,200);
    ldListSetText(obj,(const unsigned char **)pListName,7,FONT_ALIBABAPUHUITI_3_55_REGULAR_18);
    ldListSetItemHeight(obj,40);
    ldListSetAlign(obj,ARM_2D_ALIGN_LEFT);
    ((ldList_t*)obj)->padding.left=20;
    ldListSetBackgroundColor(obj,GLCD_COLOR_BLACK);
    ldListSetTextColor(obj,GLCD_COLOR_WHITE);
    ldListSetSelectColor(obj,__RGB(0xF4,0xA4,0x60));
    ldListSetSelectItem(obj,gPrintImgNum);

    connect(ID_LIST,SIGNAL_CLICKED_ITEM,slotShowImg);

    obj=ldImageInit(ID_IMG,ID_BG,280,50,176,160,imgList[gPrintImgNum],NULL,false);

    obj=ldButtonInit(ID_BTN_PRINT,ID_BG,300,220,150,40);
    ldButtonSetFont(obj,FONT_ALIBABAPUHUITI_3_55_REGULAR_18);
    ldButtonSetText(obj,"打印");
    ldButtonSetCorner(obj,true);
    ldButtonSetColor(obj,__RGB(0xF4,0xA4,0x60),__RGB(0xD2,0x69,0x1E));
    connect(ID_BTN_PRINT,SIGNAL_RELEASE,slotJumpPrinting);


    obj=ldDateTimeInit(ID_DATE_TIME,ID_BG,250,5,200,40,FONT_ALIBABAPUHUITI_3_55_REGULAR_16);
    ldDateTimeSetTextColor(obj,GLCD_COLOR_WHITE);
    ldDateTimeSetDate(obj,2024,8,17);
    ldDateTimeSetTime(obj,20,10,0);


}

void uiPrintDraw(ld_scene_t *ptScene,arm_2d_tile_t *ptTile,bool bIsNewFrame)
{

}

void uiPrintLoop(ld_scene_t* ptScene)
{




}

void uiPrintQuit(ld_scene_t* ptScene)
{




}
