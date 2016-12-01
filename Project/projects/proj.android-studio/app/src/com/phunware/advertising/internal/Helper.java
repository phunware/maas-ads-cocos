package com.phunware.advertising.internal;

import com.phunware.advertising.PwInterstitialAd;
import com.phunware.advertising.PwLandingPageAd;
import com.phunware.advertising.PwNativeAd;
import com.phunware.advertising.PwVideoInterstitialAd;
import com.phunware.advertising.internal.InterstitialAdImpl;

/**
 * Created by sbakinovskij on 30.09.2016.
 */
public class Helper {

    public static void setCreativeIdInterstitial(PwInterstitialAd pwInterstitialAd, String creativeId) {
        ((InterstitialAdImpl)pwInterstitialAd).setCreativeId(creativeId);
    }

    public static void setCreativeIdVideo(PwVideoInterstitialAd pwInterstitialAd, String creativeId) {
        ((VideoInterstitialAdImpl)pwInterstitialAd).setCreativeId(creativeId);
    }

    public static void setCreativeIdLandingPage(PwLandingPageAd pwLandingPageAd, String creativeId) {
        ((InterstitialAdImpl)pwLandingPageAd).setCreativeId(creativeId);
    }

    public static void setCreativeIdNative(PwNativeAd pwNativeAd, String creativeId) {
        ((NativeAdImpl)pwNativeAd).setCreativeId(creativeId);
    }

    public static void setCreativeIdNativeLoader(NativeAdLoader pwNativeLoader, String creativeId) {
        (pwNativeLoader).setCreativeId(creativeId);
    }
}
