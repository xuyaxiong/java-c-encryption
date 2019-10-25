package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.example.myapplication.Utils.Util;

public class MainActivity extends AppCompatActivity {

    public static final String TAG = "MainActivity";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText("");

        byte[] text = {
                '1', '2', '3', '4', '5', '6', '7', '8',
                '9', '0', 'a', 'b', 'c', 'd', 'e', 'f',
        };
        Log.d(TAG, "onCreate: origin = " + Util.bytes2Hex(text));
        Log.d(TAG, "onCreate: =====================");
        byte[] encrypted = encryptedFromJNI(text);
        Log.d(TAG, "onCreate: encrypted = " + Util.bytes2Hex(encrypted));
        Log.d(TAG, "onCreate: =====================");
        byte[] decrypted = decryptedFromJNI(encrypted);
        Log.d(TAG, "onCreate: decrypted = " + Util.bytes2Hex(decrypted));
    }



    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native byte[] encryptedFromJNI(byte[] clearBytes);
    public native byte[] decryptedFromJNI(byte[] secretBytes);
}
