//
// Created by zauther on 21-4-3.
//

#include <cstddef>
#include "QuickJS.h"
#include <quickjs-libc.h>
#include <quickjs.h>
#include <cutils.h>
#include <cstring>

int has_suffix(const char *str, const char *suffix)
{
    size_t len = strlen(str);
    size_t slen = strlen(suffix);
    return (len >= slen && !memcmp(str + len - slen, suffix, slen));
}
JSContext * JS_NewCustomContext(JSRuntime *rt) {
    JSContext *ctx;
    ctx = JS_NewContext(rt);
    if (!ctx)
        return NULL;
#ifdef CONFIG_BIGNUM
    if (bignum_ext) {
        JS_AddIntrinsicBigFloat(ctx);
        JS_AddIntrinsicBigDecimal(ctx);
        JS_AddIntrinsicOperators(ctx);
        JS_EnableBignumExt(ctx, TRUE);
    }
#endif
    /* system modules */
    js_init_module_std(ctx, "std");
    js_init_module_os(ctx, "os");
    return ctx;
}

JSRuntime *QuickJS::createNewQJSRuntime() {
    runtime = JS_NewRuntime();
    if (!runtime)
        return nullptr;
    js_std_set_worker_new_context_func(JS_NewCustomContext);
    js_std_init_handlers(runtime);
    context = JS_NewCustomContext(runtime);
    if(!context){
        return nullptr;
    }
    /* loader for ES6 modules */
    JS_SetModuleLoaderFunc(runtime, NULL, js_module_loader, NULL);
    const char *str = "import * as std from 'std';\n"
                      "import * as os from 'os';\n"
                      "globalThis.std = std;\n"
                      "globalThis.os = os;\n";
    eval_buf(context, str, strlen(str), "<input>", JS_EVAL_TYPE_MODULE);
    return runtime;
}

JSContext *QuickJS::getQJSContext() {
//    if (!qjsRuntime) {
//        return nullptr;
//    }
//    qjsContext = JS_NewContext(qjsRuntime);
//    if (!qjsContext) {
//        return nullptr;
//    }
//
//    js_init_module_std(qjsContext, "std");
//    js_init_module_os(qjsContext, "os");
//
//    JS_SetModuleLoaderFunc(qjsRuntime, nullptr, js_module_loader, nullptr);
    return context;
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
    if (module < 0) {
        module = (has_suffix(filename, ".mjs") ||
                  JS_DetectModule((const char *) buf, buf_len));
    }
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

