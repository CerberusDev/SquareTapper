LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
				   $(LOCAL_PATH)/../../../Classes/BaseScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/DebugScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameMask.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameSquare.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameSquareSequence.cpp \
				   $(LOCAL_PATH)/../../../Classes/HorizontalGameMask.cpp \
				   $(LOCAL_PATH)/../../../Classes/LevelSelectScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/SquareTapper.cpp \
				   $(LOCAL_PATH)/../../../Classes/StarImage.cpp \
				   $(LOCAL_PATH)/../../../Classes/ToggleGameMask.cpp \
				   $(LOCAL_PATH)/../../../Classes/TutorialScene_DoubleTap.cpp \
				   $(LOCAL_PATH)/../../../Classes/TutorialScene_Standard.cpp \
				   $(LOCAL_PATH)/../../../Classes/VerticalGameMask.cpp
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d)
$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
