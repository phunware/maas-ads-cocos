# Add project specific ProGuard rules here.
# By default, the flags in this file are appended to flags specified
# in E:\developSoftware\Android\SDK/tools/proguard/proguard-android.txt
# You can edit the include path and order by changing the proguardFiles
# directive in build.gradle.
#
# For more details, see
#   http://developer.android.com/guide/developing/tools/proguard.html

# Add any project specific keep options here:

# If your project uses WebView with JS, uncomment the following
# and specify the fully qualified class name to the JavaScript interface
# class:
#-keepclassmembers class fqcn.of.javascript.interface.for.webview {
#   public *;
#}


# please KEEP ALL THE NAMES
#-keepnames class ** { *; }
-dontwarn com.google.android.gms.internal.**
-keep class com.google.android.gms.internal.** {*;}

-dontwarn com.google.gson.**
-keep class com.google.gson.** {*;}

-dontwarn android.support.customtabs.**
-keep class android.support.customtabs.** {*;}

-dontwarn com.millennialmedia.android.**
-keep class com.millennialmedia.android.** {*;}

-dontwarn org.apache.http.**
-keep class org.apache.http.** {*;}

-dontwarn com.squareup.**
-keep class com.squareup.** {*;}

-keep class org.cocos2dx.lib.** {*;}

-keep class com.softeq.** {*;}

-dontwarn com.squareup.**
-keep class com.squareup.** {*;}

-dontwarn com.phunware.**
-keep class com.phunware.** {*;}

-dontwarn okhttp3.**
-keep class okhttp3.** {*;}

-dontwarn java.nio.**
-keep class java.nio.**  {*;}

-dontwarn org.codehaus.**
-keep class org.codehaus.**  {*;}

-dontwarn retrofit.**
-keep class retrofit.** {*;}

-keep class * implements android.os.Parcelable {
    public static final android.os.Parcelable$Creator *;
}

-keepattributes *Annotation*
-dontoptimize
-dontobfuscate