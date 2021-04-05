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

    public  void setMemoryLimit(long memoryLimit) {
        if (instance == 0) {
            return;
        }
        if(memoryLimit<0){
            memoryLimit =0;
        }
        QuickJSJNI.nativeSetMemoryLimit(instance,memoryLimit);

    }

    public void setMaxStackSize(long stackSize) {
        if (instance == 0) {
            return;
        }
        if(stackSize < 0){
            stackSize = 0;
            QuickJSJNI.nativeSetMaxStackSize(instance,stackSize);
        }

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
