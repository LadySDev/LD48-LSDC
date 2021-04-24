#include "Texture.h"

Texture::Texture(AAssetManager* assetManager, const char* path, int id, GLuint* textures) {
    mID = id;

    AAsset* mTexture1;
    mTexture1 = AAssetManager_open(assetManager, path,AASSET_MODE_UNKNOWN);

    if(mTexture1){
        size_t assetLength = AAsset_getLength(mTexture1);
        char* buffer = (char*) malloc(assetLength + 1);
        AAsset_read(mTexture1, buffer, assetLength);
        buffer[assetLength] = 0;
        AAsset_close(mTexture1);
        int textureWidth, textureHeight, nrChannels;
        unsigned char *data = stbi_load_from_memory((unsigned char*)buffer, assetLength, &textureWidth, &textureHeight, &nrChannels, 0);
        glBindTexture(GL_TEXTURE_2D, textures[mID]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
        free(buffer);
    }
}

int Texture::getID() {
    return mID;
}
