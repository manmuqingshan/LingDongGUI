CCPATH = D:/mingw64/bin
USE_DEMO = 2

CC = $(CCPATH)/gcc.exe
ifeq ($(OS),Windows_NT)
    SDL2_PATH = $(subst /,\,$(CURDIR))\sdl2\64\bin\SDL2.dll
    OutLibFile = $(subst /,\,$(CURDIR))\build\SDL2.dll
else
    SDL2_PATH = $(CURDIR)/sdl2/64/bin/libSDL2.so
    OutLibFile = $(CURDIR)/build/libSDL2.so
endif

# 编译选项
CFLAGS = -fdiagnostics-color=always -w -g -std=gnu11 -MMD -ffunction-sections -fdata-sections -fno-ms-extensions -Wno-macro-redefined -Ofast -flto
LDFLAGS =

# 链接参数
LIBS = -L./sdl2/64/lib -lSDL2 -lSDL2main -lpthread

# 输出目录
BUILD_DIR = ./build

# 源文件收集
SOURCES = \
    virtualNor/virtualNor.c \
    user/main.c \
    user/ldConfig.c \
    user/Virtual_TFT_Port.c \
    user/arm_2d_disp_adapter_0.c \
    $(wildcard ../common/Arm-2D/examples/common/controls/*.c) \
	$(wildcard ../common/Arm-2D/examples/common/asset/*.c) \
    $(wildcard ../common/Arm-2D/Library/Source/*.c) \
    $(wildcard ../common/Arm-2D/Helper/Source/*.c) \
    $(wildcard ../common/math/*.c) \
    $(wildcard ../../src/gui/*.c) \
    $(wildcard ../../src/misc/*.c) \
    $(wildcard ../common/demo/startup/*.c) \
    $(wildcard ../common/demo/startup/fonts/*.c) \
    $(wildcard ../common/demo/startup/images/*.c) \
    $(wildcard ../common/demo/widget/*.c) \
    $(wildcard ../common/demo/widget/fonts/*.c) \
    $(wildcard ../common/demo/widget/images/*.c) \
    $(wildcard ../common/demo/printer/*.c) \
    $(wildcard ../common/demo/printer/fonts/*.c) \
    $(wildcard ../common/demo/printer/images/*.c)

# 自动生成目标文件列表（带目录前缀）
OBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES:.c=.o)))
TARGET = $(BUILD_DIR)/demo

# 声明源文件搜索路径
vpath %.c $(sort $(dir $(SOURCES)))

# 宏定义
DEFINES = \
    -DUSE_DEMO=$(USE_DEMO) \
    -D__ARM_2D_USER_APP_CFG_H__=\"ldConfig.h\" \
    "-DARM_SECTION(x)= "\
    -D__va_list=va_list \
    -DRTE_Acceleration_Arm_2D_Helper_Disp_Adapter0

# 头文件搜索路径
INCLUDEPATH = \
    -I$(CURDIR)/user \
    -I$(CURDIR)/virtualNor \
    -I$(CURDIR)/../common/Arm-2D \
    -I$(CURDIR)/../common/Arm-2D/Helper/Include \
    -I$(CURDIR)/../common/Arm-2D/Library/Include \
	-I$(CURDIR)/../common/Arm-2D/Library/Source \
    -I$(CURDIR)/../common/Arm-2D/examples/common/controls \
    -I$(CURDIR)/../common/math \
    -I$(CURDIR)/../../src/gui \
    -I$(CURDIR)/../../src/misc \
    -I$(CURDIR)/sdl2/64/include/SDL2 \
    -I$(CURDIR)/../common/demo/startup \
    -I$(CURDIR)/../common/demo/startup/fonts \
    -I$(CURDIR)/../common/demo/startup/images \
    -I$(CURDIR)/../common/demo/widget \
    -I$(CURDIR)/../common/demo/widget/fonts \
    -I$(CURDIR)/../common/demo/widget/images \
    -I$(CURDIR)/../common/demo/printer \
    -I$(CURDIR)/../common/demo/printer/fonts \
    -I$(CURDIR)/../common/demo/printer/images

# 合并编译参数
CFLAGS += $(DEFINES) $(INCLUDEPATH)

export PATH := $(CCPATH):$(PATH)

all: clean create_dir copy_dll $(TARGET) run

create_dir:
	@ if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

copy_dll:
ifeq ($(OS),Windows_NT)
	@-cmd /c if exist "$(SDL2_PATH)" copy /y "$(SDL2_PATH)" "$(OutLibFile)"
else
	@-if [ -f "$(SDL2_PATH)" ]; then cp -f "$(SDL2_PATH)" "$(OutLibFile)"; fi
endif

run: $(TARGET)
	@echo Running $(TARGET)...
	./$(TARGET)

clean:
ifeq ($(OS),Windows_NT)
	@-cmd /c if exist "$(BUILD_DIR)" rd /s /q "$(BUILD_DIR)"
else
	@-rm -rf "$(BUILD_DIR)"
endif

# 声明伪目标
.PHONY: all clean copy_dll create_dir
