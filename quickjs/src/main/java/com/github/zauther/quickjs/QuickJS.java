package com.github.zauther.quickjs;

import android.util.Log;

import androidx.annotation.Nullable;

import com.github.zauther.quickjs.jni.QJSRuntime;
import com.github.zauther.quickjs.jni.QuickJSJNI;

import java.util.List;

public class QuickJS {

    public static void init() {
    }



    @Nullable
    public static QJSRuntime createJSRuntime() {
        long instance = QuickJSJNI.nativeCreateJSRuntime();
        if (instance == 0) {
            Log.w("QuickJS", "createJSRuntime Error");
            return null;
        }
        return new QJSRuntime(instance);
    }

//    public static int run(QJSRuntime runtime, String script) {
//        if (runtime != null && runtime.getInstance() != 0) {
//            return QuickJSJNI.nativeEvalExpr(runtime.getInstance(), script);
//        }
//        return -1;
//    }


    public static String getVersion() {

        return "";
    }


    public static List<String> getSupportGlobalFunc() {
        return null;
    }

    public static String eval(String script) {
        return "";
    }
}
