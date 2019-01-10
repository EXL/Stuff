package com.brackeen.glfmexample;

import android.os.Bundle;
import android.app.Activity;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.content.Intent;

public class LauncherActivity extends Activity {

    public static class Settings {
        public static String  MY_OPTION_1 = "String from Java";
        public static float   MY_OPTION_2 = 398.0f;
        public static boolean MY_OPTION_3 = false;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.launcher);

        Button runButton = (Button)findViewById(R.id.button);
        runButton.setOnClickListener(new OnClickListener() {

            @Override
            public void onClick(View v) {
                Intent intent = new Intent(v.getContext(), android.app.NativeActivity.class);

                intent.putExtra("MY_OPTION_1", Settings.MY_OPTION_1);
                intent.putExtra("MY_OPTION_2", Settings.MY_OPTION_2);
                intent.putExtra("MY_OPTION_3", Settings.MY_OPTION_3);

                startActivity(intent);
            }
        });
    }
}
