package com.example.lsdc;

import android.content.res.AssetManager;

public class LSDCLib {
    static {
        System.loadLibrary("native-lib");
    }

    public static native void init(AssetManager assetManager, int width, int height);
    public static native void update();
    public static native void onClick(float x, float y);
}
