#include "home.h"
#include "homeLogic.h"
#include "ldGui.h"

void homeInit(ld_scene_t* ptScene);
void homeLoop(ld_scene_t* ptScene);
void homeQuit(ld_scene_t* ptScene);
void homeDraw(ld_scene_t* ptScene, arm_2d_tile_t *ptTile, bool bIsNewFrame);

const ldPageFuncGroup_t homeFunc={
    .init=homeInit,
    .loop=homeLoop,
    .quit=homeQuit,
    .draw=homeDraw,
#if (USE_LOG_LEVEL>=LOG_LEVEL_INFO)
    .pageName="home",
#endif
};

#if 0 != 0
const uint8_t *COMBOBOX_PORTNAME_itemList[0] = {};
#endif



__WEAK bool home_action_Button_open_release(ld_scene_t *ptScene,ldMsg_t msg)
{
   return false;
}

__WEAK bool home_action_Button_open_press(ld_scene_t *ptScene,ldMsg_t msg)
{
   return false;
}

__WEAK bool home_action_Button_close_release(ld_scene_t *ptScene,ldMsg_t msg)
{
   return false;
}

__WEAK bool home_action_Button_setting_release(ld_scene_t *ptScene,ldMsg_t msg)
{
   return false;
}



void homeInit(ld_scene_t* ptScene)
{
    void *obj;
    obj=ldWindowInit(ID_BACKGROUND_0, ID_BACKGROUND_0, 0, 0, 480, 320);
#if 0==0
    ldWindowSetColor(obj, __RGB(0xF0, 0xF0, 0xF0));
#endif
#if 0==1
    ldWindowSetImage(obj, IMAGE_, IMAGE__MASK);
#endif

    obj=ldTextInit(ID_TEXT_0, ID_BACKGROUND_0, 10, 10, 460, 200, FONT_ARIAL_10, 0, 0);
#if 0==0
    ldTextSetText(obj, (uint8_t*)"");
#endif
#if 0==1
    ldTextSetStaticText(obj, (uint8_t*)"");
#endif
    ldTextSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
#if 1==0
    ldTextSetTransparent(obj, true);
#endif
#if 1==1
    ldTextSetBackgroundColor(obj, __RGB(0xFF, 0xFF, 0xFF));
#endif
#if 1==2
    ldTextSetBackgroundImage(obj, IMAGE_, IMAGE__MASK);
#endif

    obj=ldButtonInit(ID_BUTTON_OPEN, ID_BACKGROUND_0, 20, 270, 80, 30);
    ldButtonSetFont(obj, FONT_ARIAL_10);
    ldButtonSetText(obj, (uint8_t*)"Open");
    ldButtonSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
    ldButtonSetCorner(obj, 1);
#if 1==0
    ldButtonSetTransparent(obj, true);
#endif
#if 1==1
    ldButtonSetColor(obj, __RGB(0x78, 0xC8, 0xFF), __RGB(0xFF, 0xFF, 0x80));
#endif
#if 1==2
    ldButtonSetImage(obj, IMAGE_, IMAGE__MASK, IMAGE_, IMAGE__MASK);
#endif
    ldButtonSetCheckable(obj, 1);
    ldButtonSetPress(obj, 0);
    ldButtonSetKeyValue(obj, 0);
    connect(ID_BUTTON_OPEN,SIGNAL_RELEASE,home_action_Button_open_release);
    connect(ID_BUTTON_OPEN,SIGNAL_PRESS,home_action_Button_open_press);

    obj=ldWindowInit(ID_WINDOW_SETTING, ID_BACKGROUND_0, 40, 20, 406, 176);
#if 1==1
    ldWindowSetColor(obj, __RGB(0xE6, 0xE6, 0xE6));
#endif

    obj=ldLineEditInit(ID_LINEEDIT_BAUDRATE, ID_WINDOW_SETTING, 110, 50, 100, 20, FONT_ARIAL_10, 10);
    ldLineEditSetColor(obj, __RGB(0x00, 0x00, 0x00), __RGB(0xFF, 0xFF, 0xFF), __RGB(0xC0, 0xC0, 0xC0));
    ldLineEditSetText(obj, (uint8_t*)"");
    ldLineEditSetType(obj, 1);
#if 0==0
#define LINEEDIT_BAUDRATE_ALIGN_H ARM_2D_ALIGN_LEFT
#endif
#if 0==1
#define LINEEDIT_BAUDRATE_ALIGN_H ARM_2D_ALIGN_RIGHT
#endif
#if 0==2
#define LINEEDIT_BAUDRATE_ALIGN_H ARM_2D_ALIGN_CENTRE
#endif
    ldLineEditSetAlign(obj, LINEEDIT_BAUDRATE_ALIGN_H);
#ifdef ID_KEYBOARD_0
    ldLineEditSetKeyboard(obj,ID_KEYBOARD_0);
#endif

    obj=ldComboBoxInit(ID_COMBOBOX_PORTNAME, ID_WINDOW_SETTING, 110, 10, 100, 20, FONT_ARIAL_10);
    ldComboBoxSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
    ldComboBoxSetBackgroundColor(obj, __RGB(0xFF, 0xFF, 0xFF));
    ldComboBoxSetFrameColor(obj, __RGB(0x00, 0x00, 0x00));
    ldComboBoxSetSelectColor(obj, __RGB(0xC8, 0xC8, 0xC8));
#if 0 != 0
    ldComboBoxSetItems(obj, COMBOBOX_PORTNAME_itemList, 0);
    ldComboBoxSetSelectItem(obj, 0);
#endif
    ldComboBoxSetCorner(obj, 1);
#ifdef IMAGE_
    ldComboBoxSetDropdownImage(obj, IMAGE_, IMAGE__MASK);
#endif

    obj=ldCheckBoxInit(ID_CHECKBOX_0, ID_WINDOW_SETTING, 110, 90, 60, 20);
    ldCheckBoxSetText(obj, FONT_ARIAL_10, (uint8_t*)"1");
    ldCheckBoxSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
#if 0==0
    ldCheckBoxSetColor(obj, __RGB(0xFF, 0xFF, 0xFF), __RGB(0x00, 0x00, 0x00));
#endif
#if 0==1
    ldCheckBoxSetImage(obj, IMAGE_, IMAGE__MASK, IMAGE_, IMAGE__MASK);
#endif
    ldCheckBoxSetChecked(obj, 1);
    ldCheckBoxSetCorner(obj, 1);
#if 1==1
    ldCheckBoxSetRadioButtonGroup(obj, 0);
#endif

    obj=ldCheckBoxInit(ID_CHECKBOX_1, ID_WINDOW_SETTING, 180, 90, 60, 20);
    ldCheckBoxSetText(obj, FONT_ARIAL_10, (uint8_t*)"1.5");
    ldCheckBoxSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
#if 0==0
    ldCheckBoxSetColor(obj, __RGB(0xFF, 0xFF, 0xFF), __RGB(0x00, 0x00, 0x00));
#endif
#if 0==1
    ldCheckBoxSetImage(obj, IMAGE_, IMAGE__MASK, IMAGE_, IMAGE__MASK);
#endif
    ldCheckBoxSetChecked(obj, 0);
    ldCheckBoxSetCorner(obj, 1);
#if 1==1
    ldCheckBoxSetRadioButtonGroup(obj, 0);
#endif

    obj=ldCheckBoxInit(ID_CHECKBOX_2, ID_WINDOW_SETTING, 250, 90, 60, 20);
    ldCheckBoxSetText(obj, FONT_ARIAL_10, (uint8_t*)"2");
    ldCheckBoxSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
#if 0==0
    ldCheckBoxSetColor(obj, __RGB(0xFF, 0xFF, 0xFF), __RGB(0x00, 0x00, 0x00));
#endif
#if 0==1
    ldCheckBoxSetImage(obj, IMAGE_, IMAGE__MASK, IMAGE_, IMAGE__MASK);
#endif
    ldCheckBoxSetChecked(obj, 0);
    ldCheckBoxSetCorner(obj, 1);
#if 1==1
    ldCheckBoxSetRadioButtonGroup(obj, 0);
#endif

    obj=ldLabelInit(ID_LABEL_0, ID_WINDOW_SETTING, 20, 90, 68, 20, FONT_ARIAL_10);
    ldLabelSetText(obj, (uint8_t*)"Data Bits:");
    ldLabelSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
#if 0==0
    ldLabelSetTransparent(obj, true);
#endif
#if 0==1
    ldLabelSetBackgroundColor(obj, __RGB(0xFF, 0xFF, 0xFF));
#endif
#if 0==2
    ldLabelSetBackgroundImage(obj, IMAGE_, IMAGE__MASK);
#endif
#if 0==0
#define LABEL_0_ALIGN_H ARM_2D_ALIGN_LEFT
#endif
#if 0==1
#define LABEL_0_ALIGN_H ARM_2D_ALIGN_RIGHT
#endif
#if 0==2
#define LABEL_0_ALIGN_H ARM_2D_ALIGN_CENTRE
#endif
#if 2==0
#define LABEL_0_ALIGN_V ARM_2D_ALIGN_TOP
#endif
#if 2==1
#define LABEL_0_ALIGN_V ARM_2D_ALIGN_BOTTOM
#endif
#if 2==2
#define LABEL_0_ALIGN_V ARM_2D_ALIGN_CENTRE
#endif
    ldLabelSetAlign(obj, LABEL_0_ALIGN_H|LABEL_0_ALIGN_V);

    obj=ldButtonInit(ID_BUTTON_CLOSE, ID_WINDOW_SETTING, 360, 10, 30, 30);
    ldButtonSetFont(obj, FONT_ARIAL_10);
    ldButtonSetText(obj, (uint8_t*)"X");
    ldButtonSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
    ldButtonSetCorner(obj, 1);
#if 1==0
    ldButtonSetTransparent(obj, true);
#endif
#if 1==1
    ldButtonSetColor(obj, __RGB(0x78, 0xC8, 0xFF), __RGB(0xFF, 0xFF, 0x80));
#endif
#if 1==2
    ldButtonSetImage(obj, IMAGE_, IMAGE__MASK, IMAGE_, IMAGE__MASK);
#endif
    ldButtonSetCheckable(obj, 0);
    ldButtonSetPress(obj, 0);
    ldButtonSetKeyValue(obj, 0);
    connect(ID_BUTTON_CLOSE,SIGNAL_RELEASE,home_action_Button_close_release);

    obj=ldLabelInit(ID_LABEL_1, ID_WINDOW_SETTING, 20, 10, 76, 20, FONT_ARIAL_10);
    ldLabelSetText(obj, (uint8_t*)"Port:");
    ldLabelSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
#if 0==0
    ldLabelSetTransparent(obj, true);
#endif
#if 0==1
    ldLabelSetBackgroundColor(obj, __RGB(0xFF, 0xFF, 0xFF));
#endif
#if 0==2
    ldLabelSetBackgroundImage(obj, IMAGE_, IMAGE__MASK);
#endif
#if 0==0
#define LABEL_1_ALIGN_H ARM_2D_ALIGN_LEFT
#endif
#if 0==1
#define LABEL_1_ALIGN_H ARM_2D_ALIGN_RIGHT
#endif
#if 0==2
#define LABEL_1_ALIGN_H ARM_2D_ALIGN_CENTRE
#endif
#if 2==0
#define LABEL_1_ALIGN_V ARM_2D_ALIGN_TOP
#endif
#if 2==1
#define LABEL_1_ALIGN_V ARM_2D_ALIGN_BOTTOM
#endif
#if 2==2
#define LABEL_1_ALIGN_V ARM_2D_ALIGN_CENTRE
#endif
    ldLabelSetAlign(obj, LABEL_1_ALIGN_H|LABEL_1_ALIGN_V);

    obj=ldLabelInit(ID_LABEL_2, ID_WINDOW_SETTING, 20, 50, 76, 20, FONT_ARIAL_10);
    ldLabelSetText(obj, (uint8_t*)"Baud Rate:");
    ldLabelSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
#if 0==0
    ldLabelSetTransparent(obj, true);
#endif
#if 0==1
    ldLabelSetBackgroundColor(obj, __RGB(0xFF, 0xFF, 0xFF));
#endif
#if 0==2
    ldLabelSetBackgroundImage(obj, IMAGE_, IMAGE__MASK);
#endif
#if 0==0
#define LABEL_2_ALIGN_H ARM_2D_ALIGN_LEFT
#endif
#if 0==1
#define LABEL_2_ALIGN_H ARM_2D_ALIGN_RIGHT
#endif
#if 0==2
#define LABEL_2_ALIGN_H ARM_2D_ALIGN_CENTRE
#endif
#if 2==0
#define LABEL_2_ALIGN_V ARM_2D_ALIGN_TOP
#endif
#if 2==1
#define LABEL_2_ALIGN_V ARM_2D_ALIGN_BOTTOM
#endif
#if 2==2
#define LABEL_2_ALIGN_V ARM_2D_ALIGN_CENTRE
#endif
    ldLabelSetAlign(obj, LABEL_2_ALIGN_H|LABEL_2_ALIGN_V);

    obj=ldLabelInit(ID_LABEL_3, ID_WINDOW_SETTING, 20, 130, 68, 20, FONT_ARIAL_10);
    ldLabelSetText(obj, (uint8_t*)"Parity:");
    ldLabelSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
#if 0==0
    ldLabelSetTransparent(obj, true);
#endif
#if 0==1
    ldLabelSetBackgroundColor(obj, __RGB(0xFF, 0xFF, 0xFF));
#endif
#if 0==2
    ldLabelSetBackgroundImage(obj, IMAGE_, IMAGE__MASK);
#endif
#if 0==0
#define LABEL_3_ALIGN_H ARM_2D_ALIGN_LEFT
#endif
#if 0==1
#define LABEL_3_ALIGN_H ARM_2D_ALIGN_RIGHT
#endif
#if 0==2
#define LABEL_3_ALIGN_H ARM_2D_ALIGN_CENTRE
#endif
#if 2==0
#define LABEL_3_ALIGN_V ARM_2D_ALIGN_TOP
#endif
#if 2==1
#define LABEL_3_ALIGN_V ARM_2D_ALIGN_BOTTOM
#endif
#if 2==2
#define LABEL_3_ALIGN_V ARM_2D_ALIGN_CENTRE
#endif
    ldLabelSetAlign(obj, LABEL_3_ALIGN_H|LABEL_3_ALIGN_V);

    obj=ldCheckBoxInit(ID_CHECKBOX_9, ID_WINDOW_SETTING, 110, 130, 60, 20);
    ldCheckBoxSetText(obj, FONT_ARIAL_10, (uint8_t*)"None");
    ldCheckBoxSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
#if 0==0
    ldCheckBoxSetColor(obj, __RGB(0xFF, 0xFF, 0xFF), __RGB(0x00, 0x00, 0x00));
#endif
#if 0==1
    ldCheckBoxSetImage(obj, IMAGE_, IMAGE__MASK, IMAGE_, IMAGE__MASK);
#endif
    ldCheckBoxSetChecked(obj, 1);
    ldCheckBoxSetCorner(obj, 1);
#if 1==1
    ldCheckBoxSetRadioButtonGroup(obj, 1);
#endif

    obj=ldCheckBoxInit(ID_CHECKBOX_10, ID_WINDOW_SETTING, 180, 130, 60, 20);
    ldCheckBoxSetText(obj, FONT_ARIAL_10, (uint8_t*)"Odd");
    ldCheckBoxSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
#if 0==0
    ldCheckBoxSetColor(obj, __RGB(0xFF, 0xFF, 0xFF), __RGB(0x00, 0x00, 0x00));
#endif
#if 0==1
    ldCheckBoxSetImage(obj, IMAGE_, IMAGE__MASK, IMAGE_, IMAGE__MASK);
#endif
    ldCheckBoxSetChecked(obj, 0);
    ldCheckBoxSetCorner(obj, 1);
#if 1==1
    ldCheckBoxSetRadioButtonGroup(obj, 1);
#endif

    obj=ldCheckBoxInit(ID_CHECKBOX_11, ID_WINDOW_SETTING, 250, 130, 60, 20);
    ldCheckBoxSetText(obj, FONT_ARIAL_10, (uint8_t*)"Even");
    ldCheckBoxSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
#if 0==0
    ldCheckBoxSetColor(obj, __RGB(0xFF, 0xFF, 0xFF), __RGB(0x00, 0x00, 0x00));
#endif
#if 0==1
    ldCheckBoxSetImage(obj, IMAGE_, IMAGE__MASK, IMAGE_, IMAGE__MASK);
#endif
    ldCheckBoxSetChecked(obj, 0);
    ldCheckBoxSetCorner(obj, 1);
#if 1==1
    ldCheckBoxSetRadioButtonGroup(obj, 1);
#endif

    obj=ldButtonInit(ID_BUTTON_SETTING, ID_BACKGROUND_0, 20, 230, 80, 30);
    ldButtonSetFont(obj, FONT_ARIAL_10);
    ldButtonSetText(obj, (uint8_t*)"Setting");
    ldButtonSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
    ldButtonSetCorner(obj, 1);
#if 1==0
    ldButtonSetTransparent(obj, true);
#endif
#if 1==1
    ldButtonSetColor(obj, __RGB(0x78, 0xC8, 0xFF), __RGB(0xFF, 0xFF, 0x80));
#endif
#if 1==2
    ldButtonSetImage(obj, IMAGE_, IMAGE__MASK, IMAGE_, IMAGE__MASK);
#endif
    ldButtonSetCheckable(obj, 0);
    ldButtonSetPress(obj, 0);
    ldButtonSetKeyValue(obj, 0);
    connect(ID_BUTTON_SETTING,SIGNAL_RELEASE,home_action_Button_setting_release);

    obj=ldImageInit(ID_IMAGE_OPEN, ID_BACKGROUND_0, 110, 270, 32, 32,IMAGE_LIGHT_RED_SMALL_PNG,IMAGE_LIGHT_RED_SMALL_PNG_MASK,false);

    obj=ldLineEditInit(ID_LINEEDIT_SEND, ID_BACKGROUND_0, 180, 230, 207, 30, FONT_ARIAL_10, 10);
    ldLineEditSetColor(obj, __RGB(0x00, 0x00, 0x00), __RGB(0xFF, 0xFF, 0xFF), __RGB(0xC0, 0xC0, 0xC0));
    ldLineEditSetText(obj, (uint8_t*)"LineEdit");
    ldLineEditSetType(obj, 0);
#if 0==0
#define LINEEDIT_SEND_ALIGN_H ARM_2D_ALIGN_LEFT
#endif
#if 0==1
#define LINEEDIT_SEND_ALIGN_H ARM_2D_ALIGN_RIGHT
#endif
#if 0==2
#define LINEEDIT_SEND_ALIGN_H ARM_2D_ALIGN_CENTRE
#endif
    ldLineEditSetAlign(obj, LINEEDIT_SEND_ALIGN_H);
#ifdef ID_KEYBOARD_0
    ldLineEditSetKeyboard(obj,ID_KEYBOARD_0);
#endif

    obj=ldCheckBoxInit(ID_CHECKBOX_HEXSEND, ID_BACKGROUND_0, 390, 220, 85, 30);
    ldCheckBoxSetText(obj, FONT_ARIAL_10, (uint8_t*)"HEX Send");
    ldCheckBoxSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
#if 0==0
    ldCheckBoxSetColor(obj, __RGB(0xFF, 0xFF, 0xFF), __RGB(0x00, 0x00, 0x00));
#endif
#if 0==1
    ldCheckBoxSetImage(obj, IMAGE_, IMAGE__MASK, IMAGE_, IMAGE__MASK);
#endif
    ldCheckBoxSetChecked(obj, 0);
    ldCheckBoxSetCorner(obj, 0);
#if 0==1
    ldCheckBoxSetRadioButtonGroup(obj, 0);
#endif

    obj=ldButtonInit(ID_BUTTON_SEND, ID_BACKGROUND_0, 300, 270, 80, 30);
    ldButtonSetFont(obj, FONT_ARIAL_10);
    ldButtonSetText(obj, (uint8_t*)"Send");
    ldButtonSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
    ldButtonSetCorner(obj, 1);
#if 1==0
    ldButtonSetTransparent(obj, true);
#endif
#if 1==1
    ldButtonSetColor(obj, __RGB(0x78, 0xC8, 0xFF), __RGB(0xFF, 0xFF, 0x80));
#endif
#if 1==2
    ldButtonSetImage(obj, IMAGE_, IMAGE__MASK, IMAGE_, IMAGE__MASK);
#endif
    ldButtonSetCheckable(obj, 0);
    ldButtonSetPress(obj, 0);
    ldButtonSetKeyValue(obj, 0);

    obj=ldCheckBoxInit(ID_CHECKBOX_7, ID_BACKGROUND_0, 390, 250, 85, 30);
    ldCheckBoxSetText(obj, FONT_ARIAL_10, (uint8_t*)"HEX Recv");
    ldCheckBoxSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
#if 0==0
    ldCheckBoxSetColor(obj, __RGB(0xFF, 0xFF, 0xFF), __RGB(0x00, 0x00, 0x00));
#endif
#if 0==1
    ldCheckBoxSetImage(obj, IMAGE_, IMAGE__MASK, IMAGE_, IMAGE__MASK);
#endif
    ldCheckBoxSetChecked(obj, 0);
    ldCheckBoxSetCorner(obj, 0);
#if 0==1
    ldCheckBoxSetRadioButtonGroup(obj, 0);
#endif

    obj=ldCheckBoxInit(ID_CHECKBOX_8, ID_BACKGROUND_0, 390, 280, 85, 30);
    ldCheckBoxSetText(obj, FONT_ARIAL_10, (uint8_t*)"Auto Frame");
    ldCheckBoxSetTextColor(obj, __RGB(0x00, 0x00, 0x00));
#if 0==0
    ldCheckBoxSetColor(obj, __RGB(0xFF, 0xFF, 0xFF), __RGB(0x00, 0x00, 0x00));
#endif
#if 0==1
    ldCheckBoxSetImage(obj, IMAGE_, IMAGE__MASK, IMAGE_, IMAGE__MASK);
#endif
    ldCheckBoxSetChecked(obj, 0);
    ldCheckBoxSetCorner(obj, 0);
#if 0==1
    ldCheckBoxSetRadioButtonGroup(obj, 0);
#endif

    

    homeLogicInit(ptScene);
}

void homeLoop(ld_scene_t* ptScene)
{
    

    homeLogicLoop(ptScene);
}

void homeDraw(ld_scene_t *ptScene,arm_2d_tile_t *ptTile,bool bIsNewFrame)
{

}

void homeQuit(ld_scene_t* ptScene)
{

    homeLogicQuit(ptScene);
}
