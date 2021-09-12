package com.github.zauther.quickjs.jni;

import android.util.Log;

/**
 * Description:
 *
 * @author zauther
 * @data 21-4-3
 */
public class QJSValue {
    long tag;
    long instance;

    public QJSValue(long instance) {
        this.instance = instance;
    }


    public void release(QJSContext context) {
        if (instance != 0 && context != null && context.getInstance() != 0) {
            try {
                QuickJSJNI.nativeReleaseJSValue(context.getInstance(), instance);
            } catch (Throwable e) {
                Log.e("QuickJS", e.toString());
            }

        }
    }
}
