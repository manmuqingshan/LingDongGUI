/*
 * Copyright (c) 2023-2025 Ou Jianbo (59935554@qq.com). All rights reserved.
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

#ifndef _X_LOG_H_
#define _X_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ldConfig.h"

#ifndef LOG_PRINT
#include "stdio.h"
#endif

#if (USE_LOG_LEVEL>=LOG_LEVEL_DEBUG)
#include "arm_2d_helper.h"
#endif

#define LOG_LEVEL_NONE                  (0)
#define LOG_LEVEL_ERROR                 (1)
#define LOG_LEVEL_WARNING               (2)
#define LOG_LEVEL_INFO                  (3)
#define LOG_LEVEL_DEBUG                 (4)

#ifndef USE_LOG_COLOR
#define USE_LOG_COLOR                   (0)
#endif

#ifndef USE_LOG_LEVEL
#define USE_LOG_LEVEL                   LOG_LEVEL_DEBUG
#endif

#ifndef LOG_PRINT
#define LOG_PRINT                       printf
#endif

#define LF_END                          "\n"
#define CR_END                          "\r"
#define CRLF_END                        "\r\n"

#ifndef LOG_NEW_LINE_TYPE
#define LOG_NEW_LINE_TYPE               (0)
#endif

#if LOG_NEW_LINE_TYPE == 0
#define LOG_END                         LF_END
#elif LOG_NEW_LINE_TYPE == 1
#define LOG_END                         CR_END
#elif LOG_NEW_LINE_TYPE == 2
#define LOG_END                         CRLF_END
#endif

#if     USE_LOG_COLOR == 1
#define ANSI_RED                        "\x1b[31m"
#define ANSI_GREEN                      "\x1b[32m"
#define ANSI_YELLOW                     "\x1b[33m"
#define ANSI_BLUE                       "\x1b[34m"
#define ANSI_MAGENTA                    "\x1b[35m"
#define ANSI_CYAN                       "\x1b[36m"
#define ANSI_WHITE                      "\x1b[37m"
#define ANSI_RESET                      "\x1b[0m"
#else
#define ANSI_RED
#define ANSI_GREEN
#define ANSI_YELLOW
#define ANSI_BLUE
#define ANSI_MAGENTA
#define ANSI_CYAN
#define ANSI_WHITE
#define ANSI_RESET
#endif

#if (USE_LOG_LEVEL>=LOG_LEVEL_ERROR)
#define LOG_ERROR(fmt, ...)             LOG_PRINT(ANSI_RED"[E] " ANSI_RESET fmt LOG_END,##__VA_ARGS__)
#define LOG_NORMAL(fmt, ...)            LOG_PRINT(ANSI_RESET fmt LOG_END,##__VA_ARGS__)
#else
#define LOG_ERROR(...)                  {}
#define LOG_NORMAL(...)                 {}
#endif
#if (USE_LOG_LEVEL>=LOG_LEVEL_WARNING)
#define LOG_WARNING(fmt, ...)           LOG_PRINT(ANSI_YELLOW"[W] " ANSI_RESET fmt LOG_END,##__VA_ARGS__)
#else
#define LOG_WARNING(...)                {}
#endif
#if (USE_LOG_LEVEL>=LOG_LEVEL_INFO)
#define LOG_INFO(fmt, ...)              LOG_PRINT(ANSI_GREEN"[I] " ANSI_RESET fmt LOG_END,##__VA_ARGS__)
#else
#define LOG_INFO(...)                   {}
#endif
#if (USE_LOG_LEVEL>=LOG_LEVEL_DEBUG)
#define LOG_DEBUG(fmt, ...)             LOG_PRINT(ANSI_BLUE"[D] " ANSI_RESET fmt LOG_END,##__VA_ARGS__)
#define LOG_REGION(str,region)          LOG_PRINT("[REGION] %s %d,%d,%d,%d" LOG_END,str,(region).tLocation.iX,(region).tLocation.iY,(region).tSize.iWidth,(region).tSize.iHeight)
#define LOG_LOCATION(str,location)      LOG_PRINT("[LOCATION] %s x=%d,y=%d" LOG_END,str,(location).iX,(location).iY)
#define LOG_SIZE(str,size)              LOG_PRINT("[SIZE] %s w=%d,h=%d" LOG_END,str,(size).iWidth,(size).iHeight)
#define LOG_POINT(str,point)            LOG_PRINT("[POINT] %s x=%d,y=%d" LOG_END,str,(point).x,(point).y)
#define LOG_XY(str,x,y)                 LOG_PRINT("[XY] %s x=%d,y=%d" LOG_END,str,(x),(y))
#define LOG_TIME_STAMP(fmt, ...)        LOG_PRINT(ANSI_BLUE"[T] %I64d " ANSI_RESET fmt LOG_END,arm_2d_helper_convert_ticks_to_ms(arm_2d_helper_get_system_timestamp()),##__VA_ARGS__)
#define LOG_TILE(str,tile)              LOG_PRINT("[TILE] %s \n" \
                                                  "      [INFO]   bIsRoot = %d\n" \
                                                  "               bHasEnforcedColour = %d\n" \
                                                  "               bDerivedResource = %d\n" \
                                                  "               bVirtualResource = %d\n" \
                                                  "               bVirtualScreen = %d\n" \
                                                  "               u3ExtensionID = %d\n" \
                                                  "      [COLOUR] chScheme = %d\n" \
                                                  "      [REGION] %d,%d,%d,%d\n" \
                                                  "      [ADDR]   %d" \
                                                  LOG_END, \
                                                  str, \
                                                  (tile).tInfo.bIsRoot,(tile).tInfo.bHasEnforcedColour,(tile).tInfo.bDerivedResource,(tile).tInfo.bVirtualResource,(tile).tInfo.bVirtualScreen,(tile).tInfo.u3ExtensionID, \
                                                  (tile).tColourInfo.chScheme, \
                                                  (tile).tRegion.tLocation.iX,(tile).tRegion.tLocation.iY,(tile).tRegion.tSize.iWidth,(tile).tRegion.tSize.iHeight), \
                                                  (tile).nAddress;
#else
#define LOG_DEBUG(...)                  {}
#define LOG_REGION(...)                 {}
#define LOG_LOCATION(...)               {}
#define LOG_SIZE(...)                   {}
#define LOG_POINT(...)                  {}
#define LOG_XY(...)                     {}
#define LOG_TIME_STAMP(...)             {}
#define LOG_TILE(str,tile)              {}
#endif

#ifdef __cplusplus
}
#endif

#endif //_X_LOG_H_
