#include <jni.h>

#include <GLES3/gl3.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "shader/Shader.h"
Shader* mUiShader;

extern "C" {
    JNIEXPORT void JNICALL
    Java_com_example_lsdc_LSDCLib_init(JNIEnv *env, jclass clazz, jobject asset_manager,
                                            jint width, jint height) {
        glViewport(0, 0, width, height);

        AAssetManager* assetManager = AAssetManager_fromJava(env, asset_manager);


        mUiShader = new Shader(assetManager, "shader/ui/uiVS.txt", "shader/ui/uiFS.txt");
    }

    JNIEXPORT void JNICALL
    Java_com_example_lsdc_LSDCLib_update(JNIEnv *env, jclass clazz) {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear (GL_COLOR_BUFFER_BIT);
    }
}