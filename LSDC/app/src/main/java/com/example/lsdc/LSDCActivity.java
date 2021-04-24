package com.example.lsdc;

import android.app.Activity;
import android.os.Bundle;

public class LSDCActivity extends Activity {

    LSDCView mView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mView = new LSDCView(getApplication());
        setContentView(mView);
    }
}