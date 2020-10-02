LOCAL_PATH := $(call my-dir)
TARGET_ARCH_ABI := $(APP_ABI)

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# Build the modloader shared library
include $(CLEAR_VARS)
LOCAL_MODULE := modloader
LOCAL_EXPORT_C_INCLUDES := extern/modloader
LOCAL_SRC_FILES := extern/libmodloader.so
include $(PREBUILT_SHARED_LIBRARY)

# Build the beatsaber-hook shared library, SPECIFICALLY VERSIONED!
include $(CLEAR_VARS)
LOCAL_MODULE := beatsaber-hook_0_7_1
LOCAL_EXPORT_C_INCLUDES := extern/beatsaber-hook
LOCAL_SRC_FILES := extern/libbeatsaber-hook_0_7_1.so
include $(PREBUILT_SHARED_LIBRARY)
# Creating prebuilt for dependency: codegen - version: 0.2.6
include $(CLEAR_VARS)
LOCAL_MODULE := codegen_0_2_6
LOCAL_EXPORT_C_INCLUDES := extern/codegen
LOCAL_SRC_FILES := extern/libcodegen_0_2_6.so
include $(PREBUILT_SHARED_LIBRARY)

#cURL prebuilt
include $(CLEAR_VARS)
LOCAL_MODULE := curl-prebuilt
LOCAL_EXPORT_C_INCLUDES := include/Curl
LOCAL_SRC_FILES := include/libcurl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := PPUtils
LOCAL_SRC_FILES += $(call rwildcard,src/,*.cpp)
LOCAL_SRC_FILES += $(call rwildcard,extern/beatsaber-hook/src/inline-hook,*.cpp)
LOCAL_SRC_FILES += $(call rwildcard,extern/beatsaber-hook/src/inline-hook,*.c)	
COMMON_CFLAGS := -Werror -DANDROID 
LOCAL_LDLIBS := -lz -llog -Wl,-s
LOCAL_SHARED_LIBRARIES += modloader
LOCAL_SHARED_LIBRARIES += beatsaber-hook_0_7_1
LOCAL_SHARED_LIBRARIES += codegen_0_2_6
LOCAL_STATIC_LIBRARIES := curl-prebuilt 
LOCAL_LDLIBS += -llog
LOCAL_CFLAGS += -I'c:/Program Files/Unity/Hub/Editor/2019.3.1f1/Editor/Data/il2cpp/libil2cpp' -DID='"PPUtils"' -DVERSION='"0.1.0"' -I'./shared' -I'./extern' -I'./extern/modloader' -I'./extern/codegen/include' -I'./include/Curl/include' -I'./include'
LOCAL_CPPFLAGS += -std=c++2a
LOCAL_C_INCLUDES += ./include ./src
include $(BUILD_SHARED_LIBRARY)
