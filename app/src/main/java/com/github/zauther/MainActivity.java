 package com.github.zauther;

 import android.os.Bundle;
 import android.util.Log;
 import android.widget.TextView;

 import androidx.appcompat.app.AppCompatActivity;

 import com.github.zauther.quickjs.QuickJS;
 import com.github.zauther.quickjs.jni.QJSContext;
 import com.github.zauther.quickjs.jni.QJSInt;
 import com.github.zauther.quickjs.jni.QJSRuntime;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
//    static {
//        System.loadLibrary("native-lib");
//    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText("stringFromJNI");
       String path= getApplicationInfo().nativeLibraryDir+"/libndklogmodule.so";

        QJSRuntime runtime = QJSRuntime.newQJSRuntime();
        if(runtime!=null){
           QJSContext qjsContext = runtime.newQJSContext();
           if(qjsContext!=null){
              QJSInt a= qjsContext.eval("console.log(\"Hello World\");console.log(\"Hello \\n World\")","",QJSInt.class);
               Log.i("QuickJS",""+ a.getValue());
               a.release(qjsContext);
           }
        }


//        Log.d("test","runtime: "+runtime.getInstance());
//        String script ="import fib from '"+path+"';"
//                +"fib(10);"
//                +"console.log('hello test');";
////        int ret = runtime.run("std.sprintf(\"a=%d s=%s\", 123, \"abc\")");
//        int ret = runtime.run(script);
//        Log.d("test","result: "+ret);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
//    public native String stringFromJNI();
}