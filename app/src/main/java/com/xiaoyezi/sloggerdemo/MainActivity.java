package com.xiaoyezi.sloggerdemo;

import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.TextView;

import com.sun.jna.Pointer;
import com.xiaoyezi.slogger.SloggerLibrary;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = MainActivity.class.getSimpleName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final TextView tv = findViewById(R.id.sample_text);

        SloggerLibrary.init(Environment.getExternalStorageDirectory().toString(), new SloggerLibrary.FileCallback() {
            @Override
            public void apply(Pointer fileFullPath) {
                String path = fileFullPath.getString(0);
                Log.d(TAG, "apply: " + path);

                tv.append(path);
            }
        }, new SloggerLibrary.ErrorCallback() {
            @Override
            public void apply(Pointer errorMsg) {
                tv.append(errorMsg.getString(0));
            }
        });

        SloggerLibrary.startRecord();
        for (int i = 0; i < 100; i++) {
            SloggerLibrary.logMsg("hello world:" + i);
        }
        SloggerLibrary.stopRecord();
    }
}
