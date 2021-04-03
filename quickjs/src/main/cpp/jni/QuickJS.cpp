//
// Created by zauther on 21-4-3.
//

#include <cstddef>
#include "QuickJS.h"
#include <quickjs-libc.h>
#include <quickjs.h>
#include <cutils.h>
#include <cstring>

JSRuntime *QuickJS::createNewQJSRuntime() {
    qjsRuntime = JS_NewRuntime();
    if (!qjsRuntime)
        return nullptr;
    return qjsRuntime;
}

JSContext *QuickJS::createNewQJSContext() {
    if (!qjsRuntime) {
        return nullptr;
    }
    qjsContext = JS_NewContext(qjsRuntime);
    if (!qjsContext) {
        return nullptr;
    }
    js_init_module_std(qjsContext, "std");
    js_init_module_os(qjsContext, "os");
    JS_SetModuleLoaderFunc(qjsRuntime, nullptr, js_module_loader, nullptr);
    return qjsContext;
}

int QuickJS::eval_buf(JSContext *ctx, const void *buf, int buf_len,
                      const char *filename, int eval_flags) {
    JSValue val;
    int ret;

    if ((eval_flags & JS_EVAL_TYPE_MASK) == JS_EVAL_TYPE_MODULE) {
        /* for the modules, we compile then run to be able to set
           import.meta */
        val = JS_Eval(ctx, static_cast<const char *>(buf), buf_len, filename,
                      eval_flags | JS_EVAL_FLAG_COMPILE_ONLY);
        if (!JS_IsException(val)) {
            js_module_set_import_meta(ctx, val, TRUE, TRUE);
            val = JS_EvalFunction(ctx, val);
        }
    } else {
        val = JS_Eval(ctx, static_cast<const char *>(buf), buf_len, filename, eval_flags);
    }
    if (JS_IsException(val)) {
        js_std_dump_error(ctx);
        ret = -1;
    } else {
        ret = 0;
    }
    JS_FreeValue(ctx, val);
    return ret;
}

int QuickJS::eval_file(JSContext *ctx, const char *filename, int module) {
    uint8_t *buf;
    int ret, eval_flags;
    size_t buf_len;

    buf = js_load_file(ctx, &buf_len, filename);
    if (!buf) {
        perror(filename);
        exit(1);
    }

//    if (module < 0) {
//        module = (has_suffix(filename, ".mjs") ||
//                  JS_DetectModule((const char *) buf, buf_len));
//    }
    if (module)
        eval_flags = JS_EVAL_TYPE_MODULE;
    else
        eval_flags = JS_EVAL_TYPE_GLOBAL;
    ret = eval_buf(ctx, buf, buf_len, filename, eval_flags);
    js_free(ctx, buf);
    return ret;
}

int QuickJS::eval_expr(JSContext *ctx,const char *expr) {
    return QuickJS::eval_buf(ctx, expr, strlen(expr), "<cmdline>", 0);
}