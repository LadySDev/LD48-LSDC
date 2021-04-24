package com.example.lsdc;

import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class LSDCRenderer implements GLSurfaceView.Renderer {

    private final AssetManager mAssetManager;

    public LSDCRenderer(AssetManager assetManager){
        mAssetManager = assetManager;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        LSDCLib.init(mAssetManager, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        LSDCLib.update();
    }

    public void onTouchPress(float x, float y){
        LSDCLib.onClick(x, y);
    }
}
