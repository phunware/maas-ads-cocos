#ifndef PwAdsX_PwAdsXJni_h
#define PwAdsX_PwAdsXJni_h

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

extern "C"
{
    extern void showInterstitialJNI(const char* location);
}

#endif // PwAdsX_PwAdsXJni_h