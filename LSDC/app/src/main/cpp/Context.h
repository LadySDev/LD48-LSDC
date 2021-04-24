#ifndef LSDC_CONTEXT_H
#define LSDC_CONTEXT_H

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "shader/Shader.h"

#include "Texture.h"

class Context {
public:
    Context(AAssetManager* assetManager, int width, int height);

    int getWidth();
    int getHeight();

    Shader* getUIShader();
    GLuint getBgLoadTexture();
private:
    int mWidth;
    int mHeight;

    Shader* mUiShader;

    GLuint* mTextures;
    Texture* mBgLoad;
};


#endif //LSDC_CONTEXT_H
