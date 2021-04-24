#include "Context.h"

Context::Context(AAssetManager *assetManager, int width, int height) {
    mWidth = width;
    mHeight = height;

    mUiShader = new Shader(assetManager, "shader/ui/uiVS.txt", "shader/ui/uiFS.txt");

    int nbTexture = 1;
    mTextures = new GLuint[nbTexture] ();
    glGenTextures(nbTexture, mTextures);

    mBgLoad = new Texture(assetManager, "bgLoad.png", 0, mTextures);
}

int Context::getWidth() {
    return mWidth;
}

int Context::getHeight() {
    return mHeight;
}

Shader *Context::getUIShader() {
    return mUiShader;
}

GLuint Context::getBgLoadTexture() {
    return mTextures[0];
}
