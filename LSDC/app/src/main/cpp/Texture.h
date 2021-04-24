#ifndef LSDC_TEXTURE_H
#define LSDC_TEXTURE_H

#include "utils/stb_image.h"

#include <GLES3/gl3.h>
#include <android/asset_manager.h>

class Texture {
public:
    Texture(AAssetManager* assetManager, const char* path, int id, GLuint* textures);

    int getID();
private:
    int mID;
};


#endif //LSDC_TEXTURE_H
