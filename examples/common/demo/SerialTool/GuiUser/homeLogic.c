#include "homeLogic.h"
#include "home.h"
#include "ldGui.h"

bool home_action_Button_open_release(ld_scene_t *ptScene,ldMsg_t msg)
{
    ldButton_t *btn=msg.ptSender;
    if(btn->isPressed==false)
    {
        ldImage_t *img=ldBaseGetWidgetById(ID_IMAGE_OPEN);
        ldImageSetImage(img,IMAGE_LIGHT_RED_SMALL_PNG,IMAGE_LIGHT_RED_SMALL_PNG_MASK);
        ldButtonSetText(btn,"Open");
    }
    return false;
}

bool home_action_Button_open_press(ld_scene_t *ptScene,ldMsg_t msg)
{
    ldButton_t *btn=msg.ptSender;
    if(btn->isPressed==false)
    {
        ldImage_t *img=ldBaseGetWidgetById(ID_IMAGE_OPEN);
        ldImageSetImage(img,IMAGE_LIGHT_GREEN_SMALL_PNG,IMAGE_LIGHT_GREEN_SMALL_PNG_MASK);
        ldButtonSetText(btn,"Close");
    }

    return false;
}

bool home_action_Button_setting_release(ld_scene_t *ptScene,ldMsg_t msg)
{
    ldWindow_t *win=ldBaseGetWidgetById(ID_WINDOW_SETTING);
    if(ldBaseIsHidden((ldBase_t*)win))
    {
        ldBaseSetHidden((ldBase_t*)win,false);
    }
    return false;
}

bool home_action_Button_close_release(ld_scene_t *ptScene,ldMsg_t msg)
{
    ldWindow_t *win=ldBaseGetWidgetById(ID_WINDOW_SETTING);

    ldBaseSetHidden((ldBase_t*)win,true);

    return false;
}

void homeLogicInit(ld_scene_t* ptScene)
{
    ldBase_t *win=ldBaseGetWidgetById(ID_WINDOW_SETTING);

    ldBaseSetHidden(win,true);


}

void homeLogicLoop(ld_scene_t* ptScene)
{





}

void homeLogicQuit(ld_scene_t* ptScene)
{





}
