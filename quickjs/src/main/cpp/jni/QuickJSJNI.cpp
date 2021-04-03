//
// Created by zauther on 21-4-3.
//

#include "QuickJSJNI.h"
#include <jni.h>
#include <cstddef>
#include "QuickJS.h"


static jlong CreateJSRuntime(JNIEnv *env, jclass clazz) {
    QuickJS *js = new QuickJS();
    js->createNewQJSRuntime();
    return reinterpret_cast<long >(js);
}

static jint EvalExpr(JNIEnv *env, jclass clazz, jlong instance, jstring expr) {
    QuickJS *js = reinterpret_cast<QuickJS * >(instance);
    JSContext *ctx = js->createNewQJSContext();
    const char *nativeString = env->GetStringUTFChars(expr, 0);
    int ret = QuickJS::eval_expr(ctx, nativeString);
    env->ReleaseStringUTFChars(expr, nativeString);
    return reinterpret_cast<jint >(ret);
}


static JNINativeMethod gMethod[] = {
        {
                .name = "nativeCreateJSRuntime",
                .signature ="()J",
                .fnPtr = reinterpret_cast<void *>(&CreateJSRuntime)
        },
        {
                .name ="nativeEvalExpr",
                .signature = "(JLjava/lang/String;)I",
                .fnPtr = reinterpret_cast<void *>(&EvalExpr)
        }
};


template<typename T, std::size_t N>
constexpr std::size_t size(T (&array)[N]) {
    return N;
}

bool QuickJSJNI::RegisterApi(JNIEnv *env) {
    if (env == nullptr) {
        return false;
    }
    jclass clazz = env->FindClass("com/github/zauther/quickjs/jni/QuickJSJNI");
    if (clazz == nullptr) {
        return false;
    }
    return env->RegisterNatives(clazz, gMethod, size(gMethod)) == 0;
}