package com.github.zauther.quickjs.jni;

/**
 * Description:
 *
 * @author zauther
 * @data 21-4-3
 */
public class QJSRuntime {
    private long instance;

    public QJSRuntime(long instance) {
        this.instance = instance;
    }

    public int run(String script) {
        if (instance != 0) {
            return QuickJSJNI.nativeEvalExpr(instance, script);
        }
        return -1;
    }

    public long getInstance() {
        return this.instance;
    }
}
