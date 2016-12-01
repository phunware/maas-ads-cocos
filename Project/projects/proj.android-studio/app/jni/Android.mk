LOCAL_PATH := $(call my-dir)

APP_PLATFORM := android-9

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../../external/cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../../external/cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../../external/cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../../external/cocos2d/cocos/audio/include)
$(call import-add-path,$(LOCAL_PATH)/../../../../external/phunware/source/common)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../../source/AppDelegate.cpp \
                   ../../../../source/BaseScene.cpp \
                   ../../../../source/BannerSdkScene.cpp \
                   ../../../../source/InterstitialSdkScene.cpp \
                   ../../../../source/LandingPageSdkScene.cpp \
                   ../../../../source/JSONValue.cpp \
				   ../../../../source/JSONParse.cpp \
                   ../../../../source/RewardedVideoSdkScene.cpp \
                   ../../../../source/MasterScene.cpp \
                   ../../../../source/NativeSdkScene.cpp \
                   ../../../../source/VideoInterstitialSdkScene.cpp \
				   ../../../../external/phunware/source/android/PwAdsX.cpp \
				   ../../../../external/phunware/source/android/PwAdsXJni.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../source \
					$(LOCAL_PATH)/../../../../external/phunware/source/common \
					$(LOCAL_PATH)/../../../../external/phunware/source/android

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
