//
// Created by zauther on 21-4-3.
//

#ifndef QUICKJS4ANDROID_QUICKJS_H
#define QUICKJS4ANDROID_QUICKJS_H
#include <quickjs.h>

class QuickJS {
private:
    JSRuntime * runtime;
    JSContext * context;

public:
    JSRuntime * createNewQJSRuntime();
    JSContext * getQJSContext();

    int eval();

    int eval_file(JSContext *ctx, const char *filename, int module);

    void setMemoryLimit();
    void setMaxStackSize();


    static int eval_expr(JSContext *ctx, const char * expr);

    static int eval_buf(JSContext *ctx, const void *buf, int buf_len,
                         const char *filename, int eval_flags);

};


#endif //QUICKJS4ANDROID_QUICKJS_H
