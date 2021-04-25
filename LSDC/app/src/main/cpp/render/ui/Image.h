#ifndef LSDC_IMAGE_H
#define LSDC_IMAGE_H

#include "../../Context.h"

class Image {
public:
    Image(Context* context, float width, float height, GLuint texture);

    void setSize(float width, float height);
    void setPosition(float x, float y);
    void setColor(float r, float g, float b);
    void setTextureCoord(float *textureCoord);
    void setTexture(GLuint texture);

    void render();
private:
    Context* mContext;

    float* mVertices;
    float* mColours;
    short* mIndices;
    float* mTextureCoords;

    GLuint* mProgram;
    GLint mVertexPosition;
    GLint mVertexColourLocation;
    GLint mTextureCoordLocation;

    float mWidth;
    float mHeight;

    float mPosX;
    float mPosY;

    GLuint mTexture;
};


#endif //LSDC_IMAGE_H
