#include "PwAdsX.h"
//#include "ChartboostXJni.h"

#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include <string>

#define  LOG_TAG    "PwAdsX.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)


#define  CLASS_NAME "com/phunware/PwAdsXBridge"

 PwAdsX::PwAdsX()
 //   : m_delegate(NULL)
 {
 }

static PwAdsX* s_pPwAdsX = NULL;

PwAdsX* PwAdsX::sharedPwAdsX()
{
    if (s_pPwAdsX == NULL)
    {
        s_pPwAdsX = new PwAdsX();
    }
    return s_pPwAdsX;
}

void PwAdsX::showIntersitialAd(bool isTestMode, const char* zoneId, const char* creativeId)
{
	LOGD("PwAdsX::showIntersitialAd");
    LOGD("PwAdsX::showIntersitialAd isTestMode: %i", isTestMode);
    LOGD("zoneId %s",zoneId );
    LOGD("creativeId %s ", creativeId);
	//this->showIntersitialAdJNI();	
	cocos2d::JniMethodInfo methodInfo;        
    if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showInterstitialAd", "(Ljava/lang/String;Ljava/lang/String;Z)V"))
    {
        return;
    }
	jstring zoneIdstr = methodInfo.env->NewStringUTF(zoneId);
	jstring creativeIdstr = methodInfo.env->NewStringUTF(creativeId);
	LOGD("PwAdsX::showIntersitialAd strings");
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, zoneIdstr, creativeIdstr, isTestMode);        
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
	LOGD("PwAdsX::showIntersitialAd end");
}

void PwAdsX::showVideoIntersitialAd(bool isTestMode, const char* zoneId, const char* creativeId)
{
    LOGD("PwAdsX::showVideoIntersitialAd");
	cocos2d::JniMethodInfo methodInfo;        
    if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showVideoInterstitalAd", "(Ljava/lang/String;Ljava/lang/String;Z)V"))
    {
        return;
    }
	jstring zoneIdstr = methodInfo.env->NewStringUTF(zoneId);
	jstring creativeIdstr = methodInfo.env->NewStringUTF(creativeId);
	LOGD("PwAdsX::showVideoIntersitialAd strings");
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, zoneIdstr, creativeIdstr, isTestMode);        
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void PwAdsX::showRewardedVideoAd(bool isTestMode, const char* zoneId, const char* creativeId, const char* customDataString)
{
    LOGD("PwAdsX::showRewardedVideoAd");
	cocos2d::JniMethodInfo methodInfo;        
    if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showRewardedVideoAd", "(Ljava/lang/String;Ljava/lang/String;ZLjava/lang/String;)V"))
    {
        return;
    }
	jstring zoneIdstr = methodInfo.env->NewStringUTF(zoneId);
	jstring creativeIdstr = methodInfo.env->NewStringUTF(creativeId);
	jstring customDataStringIdstr = methodInfo.env->NewStringUTF(customDataString);
	LOGD("PwAdsX::showRewardedVideoAd strings");
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, zoneIdstr, creativeIdstr, isTestMode, customDataStringIdstr);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void PwAdsX::loadRewardedVideoAd(bool isTestMode, const char* zoneId, const char* creativeId, const char* userId)
{
    LOGD("PwAdsX::loadRewardedVideoAd");
	cocos2d::JniMethodInfo methodInfo;        
    if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "loadRewardedVideoAd", "(Ljava/lang/String;Ljava/lang/String;ZLjava/lang/String;)V"))
    {
        return;
    }
	jstring zoneIdstr = methodInfo.env->NewStringUTF(zoneId);
	jstring creativeIdstr = methodInfo.env->NewStringUTF(creativeId);
	jstring userIdIdstr = methodInfo.env->NewStringUTF(userId);
	LOGD("PwAdsX::loadRewardedVideoAd strings");
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, zoneIdstr, creativeIdstr, isTestMode, userIdIdstr);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void PwAdsX::showBannerAd(bool isTestMode, bool is3dBanner, const char* zoneId, const char* creativeId)
{
    LOGD("PwAdsX::showBannerAd");
	cocos2d::JniMethodInfo methodInfo;        
    if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showBannerAd", "(Ljava/lang/String;Ljava/lang/String;ZZ)V"))
    {
        return;
    }
	jstring zoneIdstr = methodInfo.env->NewStringUTF(zoneId);
	jstring creativeIdstr = methodInfo.env->NewStringUTF(creativeId);
	LOGD("PwAdsX::showBannerAd strings");
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, zoneIdstr, creativeIdstr, isTestMode, is3dBanner);        
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void PwAdsX::showNativeAd(const char* nativeAd, bool isTestMode, const char* zoneId, const char* creativeId)
{
    LOGD("PwAdsX::showNativeAd nativeAd type: %s", nativeAd);
	cocos2d::JniMethodInfo methodInfo;        
    if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showNativeAd", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V"))
    {
        return;
    }
	jstring jstr = methodInfo.env->NewStringUTF(nativeAd);
	jstring zoneIdstr = methodInfo.env->NewStringUTF(zoneId);
	jstring creativeIdstr = methodInfo.env->NewStringUTF(creativeId);
	LOGD("PwAdsX::showNativeAd strings");
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jstr, zoneIdstr, creativeIdstr, isTestMode);        
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void PwAdsX::showLandingPageAd(bool isTestMode, const char* zoneId, const char* creativeId)
{
    LOGD("PwAdsX::showLandingPageAd");
	cocos2d::JniMethodInfo methodInfo;        
    if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showLandingPageAd", "(Ljava/lang/String;Ljava/lang/String;Z)V"))
    {
        return;
    }
	jstring zoneIdstr = methodInfo.env->NewStringUTF(zoneId);
	jstring creativeIdstr = methodInfo.env->NewStringUTF(creativeId);
	LOGD("PwAdsX::showLandingPageAd strings");
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, zoneIdstr, creativeIdstr, isTestMode);        
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}
    
void PwAdsX::hideBannerAd()
{
    LOGD("PwAdsX::hideBannerAd");
	cocos2d::JniMethodInfo methodInfo;        
    if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "hideBannerAd", "()V"))
    {
        return;
    }
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);        
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void PwAdsX::hideNativeAd()
{
    LOGD("PwAdsX::hideNativeAd");
	cocos2d::JniMethodInfo methodInfo;        
    if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "hideNativeAd", "()V"))
    {
        return;
    }
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);        
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}


    