#include <jni.h>

#include <GLES3/gl3.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#define STB_IMAGE_IMPLEMENTATION

#include "Context.h"
Context* mContext;

#include "render/ui/Image.h"
Image* mBgLoadImg;

extern "C" {
    JNIEXPORT void JNICALL
    Java_com_example_lsdc_LSDCLib_init(JNIEnv *env, jclass clazz, jobject asset_manager,
                                            jint width, jint height) {
        glEnable(GL_DEPTH_TEST);
        glViewport(0, 0, width, height);

        AAssetManager* assetManager = AAssetManager_fromJava(env, asset_manager);

        mContext = new Context(assetManager, width, height);

        mBgLoadImg = new Image(mContext, (float)mContext->getWidth(), (float)mContext->getHeight(), mContext->getBgLoadTexture());
    }

    JNIEXPORT void JNICALL
    Java_com_example_lsdc_LSDCLib_update(JNIEnv *env, jclass clazz) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        mBgLoadImg->render();
    }
}