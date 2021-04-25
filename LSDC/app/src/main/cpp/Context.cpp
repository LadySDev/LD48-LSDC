#include "Context.h"

Context::Context(AAssetManager *assetManager, int width, int height) {
    mWidth = width;
    mHeight = height;

    mUiShader = new Shader(assetManager, "render/shader/ui/uiVS.txt", "render/shader/ui/uiFS.txt");

    int nbTexture = 5;
    mTextures = new GLuint[nbTexture] ();
    glGenTextures(nbTexture, mTextures);

    new Texture(assetManager, "bgLoad.png", 0, mTextures);
    new Texture(assetManager, "bgMain.png", 1, mTextures);
    new Texture(assetManager, "LadyS-font.png", 2, mTextures);
    new Texture(assetManager, "lifeBar.png", 3, mTextures);
    new Texture(assetManager, "miner.png", 4, mTextures);




    int32_t descriptor = -1;
    off_t start = 0;
    off_t length = 0;

    AAsset* lAsset = AAssetManager_open(assetManager, "enchanted tiki 86.mp3",AASSET_MODE_UNKNOWN);
    if (lAsset != NULL) {
        descriptor = AAsset_openFileDescriptor(lAsset, &start, &length);
        AAsset_close(lAsset);
    }

    mDescriptor = {};
    mDescriptor["descriptor"] = descriptor;
    mDescriptor["start"] = start;
    mDescriptor["length"] = length;

    int32_t descriptor2 = -1;
    off_t start2 = 0;
    off_t length2 = 0;

    AAsset* lAsset2 = AAssetManager_open(assetManager, "Pick Hitting Rock.wav",AASSET_MODE_UNKNOWN);
    if (lAsset2 != NULL) {
        descriptor2 = AAsset_openFileDescriptor(lAsset2, &start2, &length2);
        AAsset_close(lAsset2);
    }

    mDescriptor2 = {};
    mDescriptor2["descriptor"] = descriptor2;
    mDescriptor2["start"] = start2;
    mDescriptor2["length"] = length2;
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

GLuint Context::getLifeBarTexture() {
    return mTextures[3];
}

GLuint Context::getMinerTexture() {
    return mTextures[4];
}
