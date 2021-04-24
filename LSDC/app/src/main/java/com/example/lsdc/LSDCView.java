package com.example.lsdc;

import android.content.Context;
import android.opengl.GLSurfaceView;

public class LSDCView  extends GLSurfaceView {
    public LSDCView(Context context) {
        super(context);

        setEGLConfigChooser(8, 8, 8, 0, 16, 0);
        setEGLContextClientVersion(3);

        LSDCRenderer renderer = new LSDCRenderer(getResources().getAssets());
        setRenderer(renderer);
    }
}
