#ifndef _LD_TEXT_H_
#define _LD_TEXT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ldCommon.h"
#include "xList.h"
#include "ldConfig.h"

typedef struct {
    LD_COMMON_ATTRIBUTES;
    bool isTransparent:1;
    uint32_t bgImgAddr;
    ldChar_t *ptTextInfo;
    ldColor bgColor;
    int16_t scrollOffset;
}ldText_t;

ldText_t* ldTextInit(uint16_t nameId, uint16_t parentNameId, int16_t x, int16_t y, int16_t width, int16_t height, ldFontDict_t *pFontDict);
void ldTextLoop(ldText_t *widget,const arm_2d_tile_t *ptParent,bool bIsNewFrame);
void ldTextDel(ldText_t *widget);

void ldTextSetHidden(ldText_t *widget,bool isHidden);
void ldTextSetText(ldText_t* widget,uint8_t *pStr);
void ldTextSetTextColor(ldText_t* widget,ldColor charColor);
void ldTextSetAlign(ldText_t *widget,uint8_t align);
void ldTextSetTransparent(ldText_t* widget,bool isTransparent);
void ldTextSetScroll(ldText_t *widget, int16_t offset);
void ldTextAddScroll(ldText_t *widget,int8_t add);
#ifdef __cplusplus
}
#endif

#endif //_LD_TEXT_H_