#ifndef __HOME_LOGIC_H__
#define __HOME_LOGIC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ldGui.h"

void homeLogicInit(ld_scene_t* ptScene);
void homeLogicLoop(ld_scene_t* ptScene);
void homeLogicQuit(ld_scene_t* ptScene);

#if __cplusplus
}
#endif

#endif
