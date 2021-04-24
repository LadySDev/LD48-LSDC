package com.example.lsdc;

import android.opengl.GLSurfaceView;
import android.view.MotionEvent;
import android.view.View;

public class LSDCOnTouchListener implements GLSurfaceView.OnTouchListener {

    private GLSurfaceView mView;
    private LSDCRenderer mRenderer;

    public LSDCOnTouchListener(GLSurfaceView view, LSDCRenderer renderer){
        mView = view;
        mRenderer = renderer;
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        if(event != null){
            final float normalizedX = (event.getX() / (float) v.getWidth()) * 2 - 1;
            final float normalizedY = -((event.getY() / (float) v.getHeight()) * 2 - 1);

            if (event.getAction() == MotionEvent.ACTION_DOWN) {
                mView.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        mRenderer.onTouchPress(normalizedX, normalizedY);
                    }
                });

            }

            return true;
        }else{
            return false;
        }
    }
}
