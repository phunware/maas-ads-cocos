package com.phunware.advertising.sample;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;

import com.phunware.PwAdsXBridge;
import com.phunware.advertising.PwAdLoader;
import com.phunware.advertising.PwNativeAd;
import com.phunware.advertising.sample.nativeads.NativeAds;
import com.phunware.core.PwLog;

//import com.zgames.testerapp.R;
//import com.softeq.adstest.R;
import com.softeq.testerapp.R;

import java.util.List;


public class NativeAdActivity extends Activity {
    private static final String TAG = NativeAdActivity.class.getSimpleName();

    public static final String TYPE_CONTENT_STREAM = "nativeAdContentStream";
    public static final String TYPE_APP_WALL = "nativeAdAppWall";
    public static final String EXTRA_TYPE = "nativeAdType";
    public static final String TEST_MODE = "testMode";

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.native_ad);
        final ViewGroup container = (ViewGroup) findViewById(R.id.adContainer);

        final String adType = getIntent().getStringExtra(EXTRA_TYPE);


        String testModeStr = getIntent().getStringExtra(TEST_MODE);
        final boolean testMode = testModeStr.equals("true");

        // native ad zone id
        String zoneId = getResources().getString(R.string.native_zone_id);

        if (TYPE_CONTENT_STREAM.equals(adType)) {
            PwNativeAd nativeAd = PwNativeAd.getInstance(this, zoneId);
            nativeAd.setTestMode(testMode);

            nativeAd.setListener(new PwNativeAd.PwNativeAdListener() {
                @Override
                public void nativeAdDidLoad(PwNativeAd nativeAd) {
                    View view = NativeAds.getContentStreamView(NativeAdActivity.this, nativeAd);
                    container.addView(view);
                    //TODO: add inerface to fix this
                    PwAdsXBridge.adnativeDidLoad("param");
                }

                @Override
                public void nativeAdDidFail(PwNativeAd nativeAd, String errMsg) {
                    // The ad failed to load and the errMsg describes why.
                    // Error messages are not intended for user display.
                    PwLog.e(TAG, errMsg);
                    PwAdsXBridge.adnativeDidFail("param");
                    onBackPressed();
                }
            });

            nativeAd.load();
        }
        else if (TYPE_APP_WALL.equals(adType)) {
            PwAdLoader<PwNativeAd> adLoader = PwAdLoader.getNativeAdLoader();
            adLoader.setZone(zoneId);
            adLoader.setTestMode(testMode);

            adLoader.loadAds(this, 8, new PwAdLoader.PwAdLoaderListener<PwNativeAd>() {
                @Override
                public void onSuccess(PwAdLoader loader, List<PwNativeAd> ads) {
                    View innerView = NativeAds.getAppWallView(NativeAdActivity.this, ads);
                    container.addView(innerView);
                    PwAdsXBridge.adnativeDidLoad("param");
                }

                @Override
                public void onFail(PwAdLoader loader, String error) {
                    PwLog.e(TAG, error);
                    PwAdsXBridge.adnativeDidFail("param");
                    onBackPressed();
                }
            });
        }
    }
}
