#ifndef LSDC_CONTEXT_H
#define LSDC_CONTEXT_H

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "render/Shader.h"

#include "render/Texture.h"

#include "utils/json.hpp"

class Context {
public:
    Context(AAssetManager* assetManager, int width, int height);

    int getWidth();
    int getHeight();

    Shader* getUIShader();
    GLuint getBgLoadTexture();
    GLuint getBgMainTexture();
    GLuint getFontTexture();
    GLuint getLifeBarTexture();
    GLuint getMinerTexture();

    nlohmann::json mDescriptor;
    nlohmann::json mDescriptor2;
private:
    int mWidth;
    int mHeight;

    Shader* mUiShader;

    GLuint* mTextures;
};


#endif //LSDC_CONTEXT_H
