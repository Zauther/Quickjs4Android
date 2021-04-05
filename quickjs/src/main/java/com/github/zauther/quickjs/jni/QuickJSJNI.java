package com.github.zauther.quickjs.jni;

import android.util.Log;

public class QuickJSJNI {
    private static final String TAG = "quickjs4android";

    static {
        try {
            System.loadLibrary("quickjs4android");
            System.loadLibrary("ndklogmodule");
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
    public native static void nativeSetMemoryLimit(long rtmInstance,long limit);
    public native static void nativeSetMaxStackSize(long rtmInstance,long size);


    public native static int nativeEvalExpr(long rtmInstance,String expr);
}
