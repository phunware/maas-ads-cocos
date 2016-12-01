#include "PwAdsXJni.h"
#include "PwAdsX.h"

#define  CLASS_NAME "com/phunware/PwAdsXBridge"

using namespace cocos2d;


extern "C"
{
	void Java_com_phunware_PwAdsXBridge_nativeAdinterstitialDidClose(JNIEnv*  env, jobject thiz, jstring location)
    {
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdinterstitialDidClose");
		if( PwAdsX::sharedPwAdsX()->getInterstitialDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getInterstitialDelegate()->pwInterstitialAdDidDismissModal();
    }
	
	void Java_com_phunware_PwAdsXBridge_nativeAdinterstitialDidFail(JNIEnv*  env, jobject thiz, jstring location)
    {
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdinterstitialDidFail");
		if( PwAdsX::sharedPwAdsX()->getInterstitialDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getInterstitialDelegate()->pwInterstitialAdDidFailError();
    }
	
	void Java_com_phunware_PwAdsXBridge_nativeAdinterstitialDidLoad(JNIEnv*  env, jobject thiz, jstring location)
    {
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdinterstitialDidLoad");               
		if( PwAdsX::sharedPwAdsX()->getInterstitialDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getInterstitialDelegate()->pwInterstitialAdDidLoadAd();
    }
	
	
	void Java_com_phunware_PwAdsXBridge_nativeAdvideoInterstitialDidLoad(JNIEnv*  env, jobject thiz, jstring location)
	{
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdvideoInterstitialDidLoad");	
		if( PwAdsX::sharedPwAdsX()->getVideoDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getVideoDelegate()-> pwVideoInterstitialAdDidLoadAd();
	}
	
    void Java_com_phunware_PwAdsXBridge_nativeAdvideoInterstitialDidFail(JNIEnv*  env, jobject thiz, jstring location)
	{
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdvideoInterstitialDidFail");		
		if( PwAdsX::sharedPwAdsX()->getVideoDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getVideoDelegate()-> pwVideoInterstitialAdDidFailError();
	}
	
    void Java_com_phunware_PwAdsXBridge_nativeAdvideoInterstitialDidClose(JNIEnv*  env, jobject thiz, jstring location)
	{
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdvideoInterstitialDidClose");	
		if( PwAdsX::sharedPwAdsX()->getVideoDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getVideoDelegate()-> pwVideoInterstitialAdDidPresentModal();	
	}
	
	//rewarded video
	void Java_com_phunware_PwAdsXBridge_nativeAdrewardedVideoDidLoad(JNIEnv*  env, jobject thiz, jstring location)
	{
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdrewardedVideoDidLoad");	
		const char *cstr = (env)->GetStringUTFChars(location, 0);

		if( PwAdsX::sharedPwAdsX()->getRewardedVideoDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getRewardedVideoDelegate()-> pwRewardedVideoAdDidLoadAd(cstr);

		//env->ReleaseStringUTFChars(location, cstr);
	}
	
    void Java_com_phunware_PwAdsXBridge_nativeAdrewardedVideoDidFail(JNIEnv*  env, jobject thiz, jstring location)
	{
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdrewardedVideoDidFail");	
		const char *cstr = (env)->GetStringUTFChars(location, 0);

		if( PwAdsX::sharedPwAdsX()->getRewardedVideoDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getRewardedVideoDelegate()-> pwRewardedVideoAdDidFailError(cstr);

		//env->ReleaseStringUTFChars(location, cstr);
	}
	
    void Java_com_phunware_PwAdsXBridge_nativeAdrewardedVideoDidClose(JNIEnv*  env, jobject thiz, jstring location)
	{
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdrewardedVideoDidClose");	
		const char *cstr = (env)->GetStringUTFChars(location, 0);

		if( PwAdsX::sharedPwAdsX()->getRewardedVideoDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getRewardedVideoDelegate()-> pwRewardedVideoAdDidDismissModal(cstr);

		//env->ReleaseStringUTFChars(location, cstr);
	}

    void Java_com_phunware_PwAdsXBridge_nativeAdrewardedVideoDidSucceed(JNIEnv*  env, jobject thiz, jstring location)
	{
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdrewardedVideoDidSucceed");
		const char *cstr = (env)->GetStringUTFChars(location, 0);

		if( PwAdsX::sharedPwAdsX()->getRewardedVideoDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getRewardedVideoDelegate()->pwRewardedVideoAdDidSucceed(cstr);

		//env->ReleaseStringUTFChars(location, cstr);
	}
	// rewarded video
	
    void Java_com_phunware_PwAdsXBridge_nativeAdbannerDidLoad(JNIEnv*  env, jobject thiz, jstring location)
	{
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdbannerDidLoad");	
		if( PwAdsX::sharedPwAdsX()->getBannerDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getBannerDelegate()->pwBannerAdDidLoadAd();
	}
    void Java_com_phunware_PwAdsXBridge_nativeAdbannerDidFail(JNIEnv*  env, jobject thiz, jstring location)
	{
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdbannerDidFail");			
		if( PwAdsX::sharedPwAdsX()->getBannerDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getBannerDelegate()->pwBannerAdDidFailError();    

	}
    void Java_com_phunware_PwAdsXBridge_nativeAdbannerDidClose(JNIEnv*  env, jobject thiz, jstring location)
	{
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdbannerDidClose");		
		if( PwAdsX::sharedPwAdsX()->getBannerDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getBannerDelegate()->pwBannerAdDidPresentModal();		
	}

    void Java_com_phunware_PwAdsXBridge_nativeAdnativeDidLoad(JNIEnv*  env, jobject thiz, jstring location)
	{
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdnativeDidLoad");	
		if( PwAdsX::sharedPwAdsX()->getNativeDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getNativeDelegate()->pwNativeAdDidLoadAd();
	}
    void Java_com_phunware_PwAdsXBridge_nativeAdnativeDidFail(JNIEnv*  env, jobject thiz, jstring location)
	{
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdnativeDidFail");		
		if( PwAdsX::sharedPwAdsX()->getNativeDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getNativeDelegate()->pwNativeAdDidFailError();		
	}
    void Java_com_phunware_PwAdsXBridge_nativeAdnativeDidClose(JNIEnv*  env, jobject thiz, jstring location)
	{
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdnativeDidClose");	
		if( PwAdsX::sharedPwAdsX()->getNativeDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getNativeDelegate()->pwNativeAdDidPresentModal();	
	}
	
	void Java_com_phunware_PwAdsXBridge_nativeAdlandingPageDidLoad(JNIEnv*  env, jobject thiz, jstring location)
	{
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdnativeDidLoad");			
		if( PwAdsX::sharedPwAdsX()->getLandingPageDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getLandingPageDelegate()->pwLandingPageAdDidLoadAd();
	}
    void Java_com_phunware_PwAdsXBridge_nativeAdlandingPageDidFail(JNIEnv*  env, jobject thiz, jstring location)
	{
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdnativeDidFail");					
		if( PwAdsX::sharedPwAdsX()->getLandingPageDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getLandingPageDelegate()->pwLandingPageAdDidFailError();		
	}
    void Java_com_phunware_PwAdsXBridge_nativeAdlandingPageDidClose(JNIEnv*  env, jobject thiz, jstring location)
	{
		CCLOG("Java_com_phunware_PwAdsXBridge_nativeAdnativeDidClose");					
		if( PwAdsX::sharedPwAdsX()->getLandingPageDelegate() != nullptr)
			PwAdsX::sharedPwAdsX()->getLandingPageDelegate()->pwLandingPageAdDidDismissModal();
	}
	
}