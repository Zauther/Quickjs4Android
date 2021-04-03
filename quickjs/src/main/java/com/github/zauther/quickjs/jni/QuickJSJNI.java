package com.github.zauther.quickjs.jni;

import android.util.Log;

public class QuickJSJNI {
    private static final String TAG = "quickjs4android";

    static {
        try {
            System.loadLibrary("quickjs4android");
        } catch (Exception e) {
            Log.e(TAG, e.toString());
        }
    }


    public static String eval(){
        return "";
    }

    public static String runJS(String js){
        return js;
    }

    public native static long nativeCreateJSRuntime();

    public native static int nativeEvalExpr(long instance,String expr);
}
