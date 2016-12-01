/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.phunware;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.widget.Toast;

import com.phunware.core.PwCoreModule;
import com.phunware.core.PwCoreSession;
import com.phunware.core.PwLog;

//import com.softeq.adstest.R;
//import com.zgames.testerapp.R;
import com.softeq.testerapp.R;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.ResizeLayout;

public class AppActivity extends Cocos2dxActivity {
	private final static String TAG = "AppActivity:";
	private static final int RC_PERM = 2330;
	private boolean permissionGranted = false;

	public ResizeLayout GetLayout()
	{
		return mFrameLayout;
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		PwLog.setShowLog(true);
		PwCoreModule.validateManifestCoreSetup(getContext());
		checkPermissions();
	}

	private void checkPermissions() {
		if (!canAccessLocation()) {
			if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
				requestPermissions(new String[]{Manifest.permission.ACCESS_COARSE_LOCATION}, RC_PERM);
			}
		} else {
			onLocationPermissionGranted();
		}
	}

	private boolean canAccessLocation() {
		return(hasPermission(Manifest.permission.ACCESS_COARSE_LOCATION));
	}

	private boolean hasPermission(String perm) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
			return(PackageManager.PERMISSION_GRANTED == checkSelfPermission(perm));
		}
		return true;
	}

	@Override
	public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
		if (requestCode == RC_PERM) {
			if (canAccessLocation()) {
				onLocationPermissionGranted();
			} else {
				Toast.makeText(AppActivity.this, "Location permission denied", Toast.LENGTH_SHORT).show();
			}
		}
	}

	private void onLocationPermissionGranted() {
		permissionGranted = true;

		if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.KITKAT_WATCH) {
			PwCoreSession.getInstance().registerKeys(this,
					getString(R.string.app_appid),
					getString(R.string.app_accesskey),
					getString(R.string.app_signaturekey),
					getString(R.string.app_encryptionkey));
		}


	}

	@Override
	protected void onStart() {
		super.onStart();

		if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.KITKAT_WATCH) {
			if (!permissionGranted) {
				return;
			}

			if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.KITKAT_WATCH) {
				PwCoreSession.getInstance().activityStartSession(this);
			}
		}

	}

	@Override
	protected void onResume() {
		super.onResume();
	}

	@Override
	protected void onStop() {
		super.onStop();

		if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.KITKAT_WATCH) {
			if (!permissionGranted) {
				return;
			}

			PwCoreSession.getInstance().activityStopSession(this);
		}
	}
}
