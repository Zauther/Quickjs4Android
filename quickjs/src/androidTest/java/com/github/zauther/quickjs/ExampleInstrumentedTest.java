package com.github.zauther.quickjs;

import android.content.Context;
import android.util.Log;

import androidx.test.platform.app.InstrumentationRegistry;
import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.github.zauther.quickjs.jni.QJSRuntime;

import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.*;

/**
 * Instrumented test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
public class ExampleInstrumentedTest {
    @Test
    public void useAppContext() {
        // Context of the app under test.
        Context appContext = InstrumentationRegistry.getInstrumentation().getTargetContext();
        assertEquals("com.github.zauther.quickjs.test", appContext.getPackageName());

        QJSRuntime runtime =QuickJS.createJSRuntime();
        Log.d("test","runtime: "+runtime.getInstance());
        String script ="import { fib } from 'libndklogmodule.so';\n"
                +"fib(10);\n"
                +"console.log('hello test');\n";
        int ret = runtime.run("std.sprintf(\"a=%d s=%s\", 123, \"abc\")");
        Log.d("test","result: "+runtime.getInstance());
    }
}