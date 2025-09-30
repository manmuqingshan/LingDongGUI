#ifndef __HOME_H__
#define __HOME_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ldBase.h"
#if USE_VIRTUAL_RESOURCE == 0
#include "fonts/uiFonts.h"
#include "images/uiImages.h"
#else
#include "binData.h"
#endif

extern const ldPageFuncGroup_t homeFunc;

#define ID_BACKGROUND_0                 0
#define ID_TEXT_0                 1
#define ID_BUTTON_OPEN                 2
#define ID_WINDOW_SETTING                 4
#define ID_LINEEDIT_BAUDRATE                 5
#define ID_COMBOBOX_PORTNAME                 6
#define ID_CHECKBOX_0                 3
#define ID_CHECKBOX_1                 7
#define ID_CHECKBOX_2                 8
#define ID_LABEL_0                 9
#define ID_BUTTON_CLOSE                 11
#define ID_LABEL_1                 12
#define ID_LABEL_2                 12
#define ID_LABEL_3                 9
#define ID_CHECKBOX_9                 16
#define ID_CHECKBOX_10                 17
#define ID_CHECKBOX_11                 20
#define ID_BUTTON_SETTING                 10
#define ID_IMAGE_OPEN                 18
#define ID_LINEEDIT_SEND                 19
#define ID_CHECKBOX_HEXSEND                 20
#define ID_BUTTON_SEND                 21
#define ID_CHECKBOX_7                 14
#define ID_CHECKBOX_8                 15


#ifdef __cplusplus
}
#endif

#endif
