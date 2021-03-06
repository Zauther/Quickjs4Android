package com.github.zauther.quickjs.jni;

/**
 * Description:
 *
 * @author zauther
 * @data 21-9-12
 */
public class QJSInt extends QJSValue{

    int value;
    public QJSInt(long instance){
        super(instance);
        value = QuickJSJNI.nativeGetInt(instance);
    }

    public int getValue() {
        return value;
    }
}
