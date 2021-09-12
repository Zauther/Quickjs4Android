package com.github.zauther.quickjs.jni;

/**
 * Description:
 *
 * @author zauther
 * @data 21-4-3
 */
public class QJSContext {
    private long instance;
    public QJSContext(long instance){
        this.instance = instance;
    }


    public<T extends QJSValue> T eval(String expr,String fileName,Class<T> clz){
       long jsValue = QuickJSJNI.nativeEval(instance,expr,fileName,0);
       if(QJSInt.class.isAssignableFrom(clz)&&jsValue!=0){
           return (T) new QJSInt(jsValue);
       }
       return null;
    }

    public long getInstance() {
        return instance;
    }

    public void release(){
        if(instance !=0) {
            QuickJSJNI.nativeReleaseQJSContext(instance);
        }
    }
}
