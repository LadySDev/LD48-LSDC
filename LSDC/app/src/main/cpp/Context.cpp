#include "Context.h"

Context::Context(AAssetManager *assetManager, int width, int height) {
    mWidth = width;
    mHeight = height;

    mUiShader = new Shader(assetManager, "render/shader/ui/uiVS.txt", "render/shader/ui/uiFS.txt");

    int nbTexture = 3;
    mTextures = new GLuint[nbTexture] ();
    glGenTextures(nbTexture, mTextures);

    new Texture(assetManager, "bgLoad.png", 0, mTextures);
    new Texture(assetManager, "bgMain.png", 1, mTextures);
    new Texture(assetManager, "LadyS-font.png", 2, mTextures);
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

GLuint Context::getBgMainTexture() {
    return mTextures[1];
}

GLuint Context::getFontTexture() {
    return mTextures[2];
}
