package com.phunware;

import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import com.phunware.advertising.*;
import com.phunware.advertising.internal.NativeAdLoader;
import com.phunware.advertising.internal.vast.RVSuccessInfo;
import com.phunware.advertising.internal.vast.TVASTRewardedVideoInfo;
import com.phunware.advertising.sample.NativeAdActivity;
import com.phunware.advertising.sample.nativeads.NativeAds;
import com.phunware.core.PwLog;
import com.phunware.utils;
//import com.softeq.adstest.R;
//import com.zgames.testerapp.R;
import com.softeq.testerapp.R;

import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.phunware.AppActivity;
import org.cocos2dx.lib.Cocos2dxActivity;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

public class PwAdsXBridge {
    private static final String TAG = "PwAdsXBridge";

    private static final String loadingTitle = "Loading";
    private static final String loadingText = "Wait while loading...";

    static PwBannerAdView adView = null;
    static PwNativeAd adNativeView = null;
    static ViewGroup mNativeAdHolder = null;
    static PwRewardedVideoAd mRewardedVideoAd = null;
    static ProgressDialog progress;
    static int mRVRemainingViews;

    private final static double lat = 40.7787895;
    private final static double lng = -73.9660945;

    private static native void nativeAdinterstitialDidClose(String params);
    private static native void nativeAdinterstitialDidFail(String params);
    private static native void nativeAdinterstitialDidLoad(String params);

    private static native void nativeAdvideoInterstitialDidLoad(String params);
    private static native void nativeAdvideoInterstitialDidFail(String params);
    private static native void nativeAdvideoInterstitialDidClose(String params);

    private static native void nativeAdrewardedVideoDidLoad(String params);
    private static native void nativeAdrewardedVideoDidFail(String params);
    private static native void nativeAdrewardedVideoDidClose(String params);
    private static native void nativeAdrewardedVideoDidSucceed(String params);

    private static native void nativeAdbannerDidLoad(String params);
    private static native void nativeAdbannerDidFail(String params);
    private static native void nativeAdbannerDidClose(String params);

    private static native void nativeAdnativeDidLoad(String params);
    private static native void nativeAdnativeDidFail(String params);
    private static native void nativeAdnativeDidClose(String params);

    private static native void nativeAdlandingPageDidLoad(String params);
    private static native void nativeAdlandingPageDidFail(String params);
    private static native void nativeAdlandingPageDidClose(String params);


    public static void adnativeDidLoad(String params)
    {
        nativeAdnativeDidLoad(params);
    }

    public static void adnativeDidFail(String params)
    {
        nativeAdnativeDidFail(params);
    }

    public static void adnativeDidClose(String params)
    {
        nativeAdnativeDidClose(params);
    }

    public static void showInterstitialAd(final String zoneId, final String creativeId, final boolean isTestMode){
        Log.d(TAG, "android_showInterstitialAd isTestMode: " + isTestMode + " zoneId: " + zoneId + " creativeId: " + creativeId);
    /*}

	public static void showInterstitialAd(){*/

        String params = "param";

		final AppActivity activity = (AppActivity) Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                String defaultZoneId = activity.getString(R.string.intrs_zone_id);

                if (!zoneId.equals(""))
                    defaultZoneId = zoneId;
                final ProgressDialog progress = new ProgressDialog(activity);
                progress.setTitle(loadingTitle);
                progress.setMessage(loadingText);
                progress.show();

                PwInterstitialAd interstitialAd = PwInterstitialAd.getInstance(activity, defaultZoneId);
                interstitialAd.setTestMode(isTestMode);
                interstitialAd.updateLocation(lat, lng);
                //interstitialAd.setKeywords(Arrays.asList("keyword1", "keyword2"));

                if (!creativeId.equals(""))
                    com.phunware.advertising.internal.Helper.setCreativeIdInterstitial(interstitialAd, creativeId);

                // register for ad lifecycle callbacks
                interstitialAd.setListener(new PwInterstitialAd.PwInterstitialAdListener() {
                    @Override
                    public void interstitialDidLoad(PwInterstitialAd ad) {
                        Log.d(TAG, "Interstitial Did Load");
                        ad.show();
                        activity.runOnGLThread(new Runnable() {
                            @Override
                            public void run() {
                                nativeAdinterstitialDidLoad("nativeAdinterstitialDidLoad");
                            }
                        });

                        progress.dismiss();
                    }

                    @Override
                    public void interstitialDidClose(PwInterstitialAd ad) {
                        Log.d(TAG, "Interstitial Did Close");
                        nativeAdinterstitialDidClose("nativeAdinterstitialDidClose");
                        progress.dismiss();
                    }

                    @Override
                    public void interstitialDidFail(PwInterstitialAd ad, String error) {
                        Log.d(TAG, "Interstitial Did Fail: " + error);
                        nativeAdinterstitialDidFail("interstitialDidFail");
                        progress.dismiss();
                    }

                    @Override
                    public void interstitialActionWillLeaveApplication(PwInterstitialAd ad) {
                        Log.d(TAG, "Interstitial Will Leave App");
                    }
                });

                interstitialAd.load();
            }
        });

	}

    public static void loadRewardedVideoAd(final String zoneId, final String creativeId, final boolean isTestMode) {
        loadRewardedVideoAd(zoneId, creativeId, isTestMode, "CocosDude");
    }
    public static void loadRewardedVideoAd(final String zoneId, final String creativeId, final boolean isTestMode, final String userid) {
        Log.d(TAG, "PWAdsXBridge.loadRewardedVideoAd: zoneId=" + zoneId + ", creativeId=" + creativeId + ", isTestMode=" + isTestMode + ", userid=" + userid);

        final AppActivity activity = (AppActivity) Cocos2dxActivity.getContext();

        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                final ProgressDialog progress = new ProgressDialog(activity);
                progress.setTitle(loadingTitle);
                progress.setMessage(loadingText);
                progress.show();

                mRewardedVideoAd = PwRewardedVideoAd.getInstance(activity, zoneId);
                mRewardedVideoAd.setTestMode(isTestMode);
                mRewardedVideoAd.updateLocation(33.659, -117.861);
                //videoAd.setKeywords(Arrays.asList("keyword1", "keyword2"));
                mRewardedVideoAd.setUserId(userid);

                mRewardedVideoAd.setListener(new PwRewardedVideoAd.PwRewardedVideoAdListener() {
                    @Override
                    public void rewardedVideoDidLoad(PwRewardedVideoAd rewardedVideoAd, TVASTRewardedVideoInfo rewardedVideoInfo) {
                        final String rvdString = RVDataToString(rewardedVideoInfo);
                        Log.d(TAG, "loadRewardedVideoAd-rewardedVideoDidLoad: RV_Data=" + rvdString);
                        activity.runOnGLThread(new Runnable() {
                            @Override
                            public void run() {
                                nativeAdrewardedVideoDidLoad(rvdString);
                            }
                        });
                        progress.dismiss();
                    }

                    @Override
                    public void rewardedVideoDidClose(PwRewardedVideoAd rewardedVideoAd, TVASTRewardedVideoInfo rewardedVideoInfo) {
                        final String rvdString = RVDataToString(rewardedVideoInfo);
                        Log.d(TAG, "loadRewardedVideoAd-rewardedVideoDidClose: RV_Data=" + rvdString);
                        activity.runOnGLThread(new Runnable() {
                            @Override
                            public void run() {
                                nativeAdrewardedVideoDidClose(rvdString);
                            }
                        });
                        progress.dismiss();
                    }

                    @Override
                    public void rewardedVideoDidFail(PwRewardedVideoAd rewardedVideoAd, String error, TVASTRewardedVideoInfo rewardedVideoInfo) {
                        final String rvdString = RVDataToString(rewardedVideoInfo, error);
                        Log.d(TAG, "loadRewardedVideoAd-rewardedVideoDidFail: RV_Data=" + rvdString);
                        activity.runOnGLThread(new Runnable() {
                            @Override
                            public void run() {
                                nativeAdrewardedVideoDidFail(rvdString);
                            }
                        });
                        progress.dismiss();
                    }

                    @Override
                    public void rewardedVideoActionWillLeaveApplication(PwRewardedVideoAd rewardedVideoAd, TVASTRewardedVideoInfo rewardedVideoInfo) {
                        final String rvdString = RVDataToString(rewardedVideoInfo);
                        Log.d(TAG, "loadRewardedVideoAd-rewardedVideoActionWillLeaveApplication: RV_Data=" + rvdString);
                        activity.runOnGLThread(new Runnable() {
                            @Override
                            public void run() {
                                nativeAdrewardedVideoDidClose(rvdString);
                            }
                        });
                        progress.dismiss();
                    }

                    @Override
                    public void rewardedVideoDidEndPlaybackSuccessfully(PwRewardedVideoAd rewardedVideoAd, RVSuccessInfo rewardedVideoSuccessInfo, TVASTRewardedVideoInfo rewardedVideoInfo) {
                        final String rvdString = RVDataToString(rewardedVideoInfo, rewardedVideoSuccessInfo);
                        Log.d(TAG, "loadRewardedVideoAd-rewardedVideoDidEndPlaybackSuccessfully: RV_Data=" + rvdString);
                        activity.runOnGLThread(new Runnable() {
                            @Override
                            public void run() {
                                nativeAdrewardedVideoDidSucceed(rvdString);
                            }
                        });
                        progress.dismiss();
                    }
                });

                mRewardedVideoAd.load();
            }
        });
    }

    public static void showRewardedVideoAd(final String zoneId, final String creativeId, final boolean isTestMode) {
        showRewardedVideoAd(zoneId, creativeId, isTestMode, "{}");
    }
    public static void showRewardedVideoAd(final String zoneId, final String creativeId, final boolean isTestMode, final String customDataString) {
        Log.d(TAG, "PWAdsXBridge.showRewardedVideoAd: zoneId=" + zoneId + ", creativeId=" + creativeId + ", isTestMode=" + isTestMode + ", customDataString=" + customDataString);

        final AppActivity activity = (AppActivity) Cocos2dxActivity.getContext();
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (mRewardedVideoAd != null) {
                    mRewardedVideoAd.setCustomData(utils.deserialize(customDataString));
                    mRewardedVideoAd.show();
                }
            }
        });
    }

    public static void showVideoInterstitalAd(final String zoneId, final String creativeId, final boolean isTestMode){

        Log.d(TAG, "android showVideoInterstitalAd isTestMode: " + isTestMode + " zoneId: " + zoneId + " creativeId: " + creativeId);
    /*}

	public static void showVideoInterstitalAd(){*/

		final AppActivity activity = (AppActivity) Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                String defaultZoneId = activity.getString(R.string.video_zone_id);

                if (!zoneId.equals(""))
                    defaultZoneId = zoneId;

                final ProgressDialog progress = new ProgressDialog(activity);
                progress.setTitle(loadingTitle);
                progress.setMessage(loadingText);
                progress.show();

                PwVideoInterstitialAd videoAd = PwVideoInterstitialAd.getInstance(activity.getApplicationContext(), defaultZoneId);
                videoAd.setTestMode(isTestMode);
                videoAd.setPlacementType(PwVideoInterstitialAd.TYPE_ALL);
                videoAd.updateLocation(lat, lng);
                //videoAd.setKeywords(Arrays.asList("keyword1", "keyword2"));

                if (!creativeId.equals(""))
                    com.phunware.advertising.internal.Helper.setCreativeIdVideo(videoAd, creativeId);

                videoAd.setListener(new PwVideoInterstitialAd.PwVideoInterstitialAdListener() {
                    @Override
                    public void videoInterstitialDidLoad(final PwVideoInterstitialAd videoInterstitialAd) {
                        Log.d(TAG, "Video Did Load");
                        videoInterstitialAd.show();
                        nativeAdvideoInterstitialDidLoad("param");
                        progress.dismiss();
                    }

                    @Override
                    public void videoInterstitialDidClose(PwVideoInterstitialAd videoInterstitialAd) {
                        Log.d(TAG, "Video Did Close");
                        nativeAdvideoInterstitialDidClose("parametr");
                    }

                    @Override
                    public void videoInterstitialDidFail(PwVideoInterstitialAd videoInterstitialAd, String error) {
                        Log.d(TAG, "Video Did Fail");
                        nativeAdvideoInterstitialDidFail("param");
                        progress.dismiss();
                    }

                    @Override
                    public void videoInterstitialActionWillLeaveApplication(PwVideoInterstitialAd videoInterstitialAd) {
                        Log.d(TAG, "Video Will Leave Application");
                    }
                });

                videoAd.load();
            }
        });
	}

    public void callTmp(String zoneId, String creativeId, boolean isTestMode, boolean is3dBan)
    {
        Log.d(TAG, "android callTmp isTestMode: " + isTestMode + " zoneId: " + zoneId + " creativeId: " + creativeId);
    }

    public static void showBannerAd(final String zoneId, final String creativeId, final boolean isTestMode, final boolean is3dBanner)
    {
        Log.d(TAG, "android showBannerAd isTestMode: " + isTestMode + " zoneId: " + zoneId + " creativeId: " + creativeId);
    /*}

	public static void showBannerAd(final boolean is3dBanner){*/

        Log.d(TAG, "Android is3dBanner: {0}" + is3dBanner);
		final AppActivity activity = (AppActivity) Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {

                if (adView != null) {
                    adView.setVisibility(View.GONE);
                    ((ViewGroup) adView.getParent()).removeView(adView);
                    adView = null;
                }

                if (adView == null) {
                    //LinearLayout testLayout = new LinearLayout(activity);
                    View bannerLayout = activity.getLayoutInflater().inflate(R.layout.banner_layout, activity.GetLayout());
                    bannerLayout.findViewById(R.id.bannerAdView).setBackgroundColor(0x01000000);
                    final PwBannerAdView mBannerAdView = (PwBannerAdView) bannerLayout.findViewById(R.id.bannerAdView);

                    if (is3dBanner) {
                        mBannerAdView.setAdUpdateInterval(30);
                        mBannerAdView.set3dAnimation(true);
                    }
                    adView = mBannerAdView;
                    adView.setVisibility(View.VISIBLE);
                    adView.updateLocation(lat, lng);

                    String defaultZoneId = activity.getString(R.string.banner_zone_id);

                    if (!zoneId.equals(""))
                        defaultZoneId = zoneId;

                    final ProgressDialog progress = new ProgressDialog(activity);
                    progress.setTitle(loadingTitle);
                    progress.setMessage(loadingText);
                    progress.show();

                    mBannerAdView.setZone(defaultZoneId)
                            .setTestMode(isTestMode);                               // enable during the development phase
                    //.setKeywords(Arrays.asList("keyword1", "keyword2")); // optional keywords for custom targeting

                    mBannerAdView.setListener(new PwBannerAdView.BannerAdListener() {
                        @Override
                        public void onReceiveBannerAd(PwBannerAdView ad) {
                            Log.d(TAG, "Banner onReceiveBannerAd");
                            nativeAdbannerDidLoad("params");
                            progress.dismiss();
                        }

                        @Override
                        public void onBannerAdError(PwBannerAdView ad, String errorMsg) {
                            Log.d(TAG, "Banner onBannerAdError: " + errorMsg);
                            nativeAdbannerDidFail("params");
                            progress.dismiss();
                        }

                        @Override
                        public void onBannerAdFullscreen(PwBannerAdView ad) {
                            Log.d(TAG, "Banner onBannerAdFullscreen");
                        }

                        @Override
                        public void onBannerAdDismissFullscreen(PwBannerAdView ad) {
                            Log.d(TAG, "Banner onBannerAdDismissFullscreen");
                            nativeAdbannerDidClose("params");
                        }

                        @Override
                        public void onBannerAdLeaveApplication(PwBannerAdView ad) {
                            Log.d(TAG, "Banner onBannerAdLeaveApplication");
                        }
                    });

                    if (!creativeId.equals(""))
                        com.phunware.advertising.Helper.setCreativeIdBanner(mBannerAdView, creativeId);

                    mBannerAdView.startRequestingAds();

                    //activity.GetLayout().addView(testLayout);
                } else {
                    adView.setVisibility(View.VISIBLE);
                    adView.updateLocation(33.659, -117.861);
                    adView.startRequestingAds();
                }
            }
        });
	}

    public static void hideBannerAd(){
        final AppActivity activity = (AppActivity) Cocos2dxActivity.getContext();

        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(adView != null)
                    adView.setVisibility(View.INVISIBLE);
            }
            //TODO show native AD here
        });
    }

    public static void hideNativeAd(){
        final AppActivity activity = (AppActivity) Cocos2dxActivity.getContext();

        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(mNativeAdHolder != null) {
                    mNativeAdHolder.setVisibility(View.INVISIBLE);
                    ((ViewGroup)mNativeAdHolder.getParent()).removeView(mNativeAdHolder);
                    mNativeAdHolder = null;
                }
            }
        });
    }
    //, final String zoneId
    public static void showNativeAd(final String nativeAdType, final String zoneId, final String creativeId, final boolean isTestMode)
    {

        Log.d(TAG, "android showNativeAd isTestMode: " + isTestMode + " zoneId: " + zoneId + " creativeId: " + creativeId);
    /*}

    public static void showNativeAd(final String nativeAdType)
    {*/
        final AppActivity activity = (AppActivity) Cocos2dxActivity.getContext();

        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (mNativeAdHolder != null) {
                    mNativeAdHolder.setVisibility(View.INVISIBLE);
                    ((ViewGroup) mNativeAdHolder.getParent()).removeView(mNativeAdHolder);
                    mNativeAdHolder = null;
                }
                if (mNativeAdHolder == null) {
                    Log.d(TAG, "PwAdsXBridge: mNativeAdHolder == null");
                    LinearLayout nativeLayout = new LinearLayout(activity);

                    View nativeView = activity.getLayoutInflater().inflate(R.layout.native_layout, activity.GetLayout());
                    //nativeView.findViewById(R.id.native_ad_view_placeholder).setBackgroundColor(Color.RED);

                    mNativeAdHolder = (ViewGroup) nativeView.findViewById(R.id.native_ad_view_placeholder);

                    activity.GetLayout().addView(nativeLayout);

                    String defaultZoneId = activity.getString(R.string.native_zone_id);

                    if(!zoneId.equals(""))
                        defaultZoneId = zoneId;

                    progress = new ProgressDialog(activity);
                    progress.setTitle(loadingTitle);
                    progress.setMessage(loadingText);
                    //progress.show();

                    if (nativeAdType.equals("App Wall")) {
                        fireNativeAppWall(activity, defaultZoneId, isTestMode, creativeId);
                    } else if (nativeAdType.equals("Content Stream")) {
                        fireNativeContentStream(activity, defaultZoneId, isTestMode, creativeId);
                    } else if (nativeAdType.equals("Clean")) {
                        progress.show();
                        fireNativeClean(activity, defaultZoneId, isTestMode, creativeId);
                    } else if (nativeAdType.equals("Content Wall")) {
                        progress.show();
                        fireNativeContentWall(activity, defaultZoneId, isTestMode, creativeId);
                    } else if (nativeAdType.equals("News Feed")) {
                        progress.show();
                        fireNativeNewsFeed(activity, defaultZoneId, isTestMode, creativeId);
                    } else if (nativeAdType.equals("3Up")) {
                        progress.show();
                        fireNative3Up(activity, defaultZoneId, isTestMode, creativeId);
                    } else if (nativeAdType.equals("3UpWith2Ads")) {
                        fireNative3UpWith2Ads(activity, defaultZoneId, isTestMode, creativeId);
                        progress.show();
                        fireNative3Up(activity, defaultZoneId, isTestMode, creativeId);
                    } else if (nativeAdType.equals("3UpWith1Ad")) {
                        progress.show();
                        fireNative3UpWith1Ad(activity, defaultZoneId, isTestMode, creativeId);
                    } else if (nativeAdType.equals("Single Icon")) {
                        progress.show();
                        fireNativeIcon(activity, defaultZoneId, isTestMode, creativeId);
                    } else if (nativeAdType.equals("Multi Icon")) {
                        progress.show();
                        fireNativeIcon(activity, defaultZoneId, isTestMode, creativeId);
                    }
                } else {
                    Log.d(TAG, "PwAdsXBridge: mNativeAdHolder.setVisibility true");
                    mNativeAdHolder.setVisibility(View.VISIBLE);
                }
            }
        });
    }

    public static void fireNativeAppWall(final AppActivity activity, String zoneId, final boolean isTestMode, String creativeId)
    {
        //TODO: finish testMode
        Log.d(TAG, "fireNativeAppWall");
        Intent intent = new Intent(activity, NativeAdActivity.class);
        intent.putExtra(NativeAdActivity.EXTRA_TYPE, NativeAdActivity.TYPE_APP_WALL);
        intent.putExtra(NativeAdActivity.TEST_MODE, isTestMode ? "true" : "false");
        activity.startActivity(intent);
    }

    public static void fireNativeContentStream(final AppActivity activity, String zoneId, final boolean isTestMode, String creativeId)
    {
        //TODO: finish testMode
        Log.d(TAG, "fireNativeContentStream");
        Intent intent = new Intent(activity, NativeAdActivity.class);
        intent.putExtra(NativeAdActivity.EXTRA_TYPE, NativeAdActivity.TYPE_CONTENT_STREAM);
        intent.putExtra(NativeAdActivity.TEST_MODE, isTestMode ? "true" : "false" );
        activity.startActivity(intent);
    }

    public static void fireNativeContentWall(final AppActivity activity, String zoneId, final boolean isTestMode, String creativeId)
    {
        PwNativeAd nativeAd = PwNativeAd.getInstance(activity, zoneId);
        nativeAd.setTestMode(isTestMode);

        if(!creativeId.equals(""))
            com.phunware.advertising.internal.Helper.setCreativeIdNative(nativeAd, creativeId);

        nativeAd.setListener(new PwNativeAd.PwNativeAdListener() {
            @Override
            public void nativeAdDidLoad(PwNativeAd nativeAd) {
                View view = NativeAds.getContentWallView(activity, nativeAd);
                mNativeAdHolder.addView(view);
                mNativeAdHolder.setVisibility(View.VISIBLE);
                nativeAdnativeDidLoad("param");
                progress.dismiss();
            }

            @Override
            public void nativeAdDidFail(PwNativeAd nativeAd, String errMsg) {
                Log.e(TAG, errMsg);
                nativeAdnativeDidFail("param");
                progress.dismiss();
            }
        });
        adNativeView = nativeAd;
        nativeAd.load();
    }

    public static void fireNativeClean(final AppActivity activity, String zoneId, final boolean isTestMode, String creativeId)
    {
        PwNativeAd nativeAd = PwNativeAd.getInstance(activity, zoneId);

        if(!creativeId.equals(""))
            com.phunware.advertising.internal.Helper.setCreativeIdNative(nativeAd, creativeId);

        nativeAd.setTestMode(isTestMode);
        nativeAd.setListener(new PwNativeAd.PwNativeAdListener() {
            @Override
            public void nativeAdDidLoad(PwNativeAd nativeAd) {
                View view = NativeAds.getCleanView(activity, nativeAd);
                mNativeAdHolder.addView(view);
                mNativeAdHolder.setVisibility(View.VISIBLE);
                nativeAdnativeDidLoad("param");
                progress.dismiss();
            }

            @Override
            public void nativeAdDidFail(PwNativeAd nativeAd, String errMsg) {
                Log.e(TAG, errMsg);
                nativeAdnativeDidFail("param");
                progress.dismiss();
            }
        });
        adNativeView = nativeAd;
        nativeAd.load();
    }

    public static void fireNativeNewsFeed(final AppActivity activity, String zoneId, final boolean isTestMode, String creativeId)
    {
        PwNativeAd nativeAd = PwNativeAd.getInstance(activity, zoneId);

        if(!creativeId.equals(""))
            com.phunware.advertising.internal.Helper.setCreativeIdNative(nativeAd, creativeId);

        nativeAd.setTestMode(isTestMode);
        nativeAd.setListener(new PwNativeAd.PwNativeAdListener() {
            @Override
            public void nativeAdDidLoad(PwNativeAd nativeAd) {
                View view = NativeAds.getNewsFeedView(activity, nativeAd);
                mNativeAdHolder.addView(view);
                mNativeAdHolder.setVisibility(View.VISIBLE);
                nativeAdnativeDidLoad("param");
                progress.dismiss();
            }

            @Override
            public void nativeAdDidFail(PwNativeAd nativeAd, String errMsg) {
                Log.e(TAG, errMsg);
                nativeAdnativeDidFail("param");
                progress.dismiss();
            }
        });
        adNativeView = nativeAd;
        nativeAd.load();
    }

    public static void fireNative3Up(final AppActivity activity, String zoneId, final boolean isTestMode, String creativeId)
    {
        fireNativeAd3(activity, zoneId, Gravity.START, isTestMode, creativeId);
    }

    public static void fireNative3UpWith2Ads(final AppActivity activity, String zoneId, final boolean isTestMode, String creativeId)
    {
        fireNativeAd3(activity, zoneId, Gravity.CENTER_HORIZONTAL, isTestMode, creativeId);
    }

    public static void fireNative3UpWith1Ad(final AppActivity activity, String zoneId, final boolean isTestMode, String creativeId)
    {
        fireNativeAd3(activity, zoneId, Gravity.END, isTestMode, creativeId);
    }

    public static void fireNativeAd3(final AppActivity activity, String zoneId, final int gravity, final boolean isTestMode, String creativeId)
    {
        PwAdLoader<PwNativeAd> adLoader = PwAdLoader.getNativeAdLoader();
        adLoader.setZone(zoneId);
        adLoader.setTestMode(isTestMode);
        adLoader.updateLocation(lat, lng);

        if(!creativeId.equals(""))
            com.phunware.advertising.internal.Helper.setCreativeIdNativeLoader(((NativeAdLoader)adLoader), creativeId);

        int countAds;

        if(gravity == Gravity.CENTER_HORIZONTAL){
            countAds = 3;
        }else{
            countAds = 2;
        }

        adLoader.loadAds(activity, countAds, new PwAdLoader.PwAdLoaderListener<PwNativeAd>() {
            @Override
            public void onSuccess(PwAdLoader loader, List<PwNativeAd> ads) {
                View innerView = NativeAds.get3UpView(activity, ads, gravity);
                mNativeAdHolder.addView(innerView);
                mNativeAdHolder.setVisibility(View.VISIBLE);
                nativeAdnativeDidLoad("param");
                progress.dismiss();
            }

            @Override
            public void onFail(PwAdLoader loader, String error) {
                PwLog.e(TAG, error);
                nativeAdnativeDidFail("param");
                progress.dismiss();
            }
        });
    }

    public static void fireNativeIcon(final AppActivity activity, String zoneId, final boolean isTestMode, String creativeId)
    {
        PwAdLoader<PwNativeAd> adLoader = PwAdLoader.getNativeAdLoader();

        /*
        if(!creativeId.equals(""))
            com.phunware.advertising.internal.Helper.setCreativeIdNativeLoader(((NativeAdLoader) adLoader), creativeId);
            */

        adLoader.setZone(zoneId);
        if(isTestMode)
            adLoader.setTestMode(isTestMode);


        adLoader.loadAds(activity, 3, new PwAdLoader.PwAdLoaderListener<PwNativeAd>() {
            @Override
            public void onSuccess(PwAdLoader loader, List<PwNativeAd> ads) {
                View innerView = NativeAds.getIconsView(activity, ads, new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        mNativeAdHolder.setVisibility(View.GONE);
                        mNativeAdHolder.removeAllViewsInLayout();
                    }
                });
                mNativeAdHolder.addView(innerView);
                mNativeAdHolder.setVisibility(View.VISIBLE);
                nativeAdnativeDidLoad("param");
                progress.dismiss();
            }

            @Override
            public void onFail(PwAdLoader loader, String error) {
                PwLog.e(TAG, error);
                nativeAdnativeDidFail("param");
                progress.dismiss();
            }
        });
    }

    public static void showLandingPageAd(final String zoneId, final String creativeId, final boolean isTestMode) {


        Log.d(TAG, "android showLandingPageAd isTestMode: " + isTestMode + " zoneId: " + zoneId + " creativeId: " + creativeId);
    /*}

    public static void showLandingPageAd() {*/
        final AppActivity activity = (AppActivity) Cocos2dxActivity.getContext();

        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {

                String defaultZoneId = activity.getString(R.string.landing_page_zone_id);

                if(!zoneId.equals(""))
                    defaultZoneId = zoneId;

                progress = new ProgressDialog(activity);
                progress.setTitle(loadingTitle);
                progress.setMessage(loadingText);
                progress.show();

                PwLandingPageAd pageAd = PwLandingPageAd.getInstance(activity, defaultZoneId);
                pageAd.setTestMode(isTestMode);
                pageAd.updateLocation(lat, lng);

                if(!creativeId.equals(""))
                    com.phunware.advertising.internal.Helper.setCreativeIdLandingPage(pageAd, creativeId);

                pageAd.setListener(new PwLandingPageAd.PwPageAdListener() {
                    @Override
                    public void pageDidLoad(PwLandingPageAd ad) {
                        // show ad as soon as it's loaded
                        Log.d(TAG, "Page Did Load");
                        ad.show();
                        nativeAdlandingPageDidLoad("param");
                        progress.dismiss();
                    }

                    @Override
                    public void pageDidClose(PwLandingPageAd ad) {
                        Log.d(TAG, "Page Did Close");
                        nativeAdlandingPageDidClose("param");
                    }

                    @Override
                    public void pageDidFail(PwLandingPageAd ad, String error) {
                        Log.d(TAG, "Page Did Fail: " + error);
                        nativeAdlandingPageDidFail("param");
                        progress.dismiss();
                    }

                    @Override
                    public void pageActionWillLeaveApplication(PwLandingPageAd ad) {
                        Log.d(TAG, "Page Will Leave App");
                    }
                });

                pageAd.load();
            }
        });
    }

    private static String RVDataToString(TVASTRewardedVideoInfo rewardedVideoInfo)
    {
        return RVDataToString(rewardedVideoInfo, null, null);
    }
    private static String RVDataToString(TVASTRewardedVideoInfo rewardedVideoInfo, String error)
    {
        return RVDataToString(rewardedVideoInfo, null, error);
    }
    private static String RVDataToString(TVASTRewardedVideoInfo rewardedVideoInfo, RVSuccessInfo rvSuccessInfo)
    {
        return RVDataToString(rewardedVideoInfo, rvSuccessInfo, null);
    }
    private static String RVDataToString(TVASTRewardedVideoInfo rewardedVideoInfo, RVSuccessInfo rvSuccessInfo, String error)
    {
        HashMap<String, Object> hm = new HashMap<String, Object>();
        if (rewardedVideoInfo != null) {
            hm.put("remainingViews", rewardedVideoInfo.getRemainingView());
            hm.put("startsCount", rewardedVideoInfo.getStarts());
            hm.put("successesCount", rewardedVideoInfo.getSuccessfulViewings());
            hm.put("errorCode", rewardedVideoInfo.getError());
        }

        if (rvSuccessInfo != null)
        {
            hm.put("currencyId", String.valueOf(rvSuccessInfo.getCurrencyId()));
            hm.put("rewardAmount", rvSuccessInfo.getAmount());
            hm.put("remainingViews", rvSuccessInfo.getRemainingViews());
        }

        if (error != null) hm.put("error", String.valueOf(error));

        return utils.serialize(hm);
    }
}
