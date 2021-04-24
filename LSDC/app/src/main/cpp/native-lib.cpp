#include <jni.h>

#include <GLES3/gl3.h>

extern "C" {
    JNIEXPORT void JNICALL
    Java_com_example_lsdc_LSDCLib_init(JNIEnv *env, jclass clazz, jobject asset_manager,
                                            jint width, jint height) {
        glViewport(0, 0, width, height);
    }

    JNIEXPORT void JNICALL
    Java_com_example_lsdc_LSDCLib_update(JNIEnv *env, jclass clazz) {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear (GL_COLOR_BUFFER_BIT);
    }
}