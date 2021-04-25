#include "Image.h"

Image::Image(Context *context, float width, float height, GLuint texture) {
    mContext = context;

    mPosX = -1.0f;
    mPosY = 1.0f;

    mVertices = new float []{
            -1.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, -1.0f,
            -1.0f, -1.0f
    };

    mColours = new float []{
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f
    };

    mIndices = new short []{ 0, 1, 2, 0, 2, 3 };

    mTextureCoords = new float []{
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
    };

    float pos1X = mVertices[0];
    float pos1Y = mVertices[1];
    float pos2X = (2 * width / (float)mContext->getWidth()) - 1;
    float pos2Y = 1 - (2 * height / (float)mContext->getHeight());
    //float w = ((2 * width) / (float)context->getWidth()) - 1 - (-1.0f);
    //float w = abs(pos1X - pos2X);
    //float h = 1.0f - (-(((2 * height) / (float)context->getHeight()) - 1));
    //float h = abs(pos1Y - pos2Y);

    mWidth = pos2X;
    mHeight = pos2Y;

    mTexture = texture;

    mVertices[2] = mVertices[0] + abs(mWidth - (-1.0));
    mVertices[4] = mVertices[0] + abs(mWidth - (-1.0));

    mVertices[5] = mVertices[1] - abs(1.0 - mHeight);
    mVertices[7] = mVertices[1] - abs(1.0 - mHeight);

    mProgram = context->getUIShader()->getProgram();
    mVertexPosition = glGetAttribLocation(*mProgram, "vertexPosition");
    mVertexColourLocation = glGetAttribLocation(*mProgram, "vertexColour");
    mTextureCoordLocation = glGetAttribLocation(*mProgram, "vertexTextureCoord");
}

void Image::setSize(float width, float height) {
    float pos1X = mVertices[0];
    float pos1Y = mVertices[1];

    float pos2X = (2 * width / (float)mContext->getWidth()) - 1;
    float pos2Y = 1 - (2 * height / (float)mContext->getHeight());

    //float w = abs(pos1X - pos2X);
    //float h = abs(pos1Y - pos2Y);

    mWidth = pos2X;
    mHeight = pos2Y;

    mVertices[2] = mVertices[0] + abs(mWidth - (-1.0));
    mVertices[4] = mVertices[0] + abs(mWidth - (-1.0));

    mVertices[5] = mVertices[1] - abs(1.0 - mHeight);
    mVertices[7] = mVertices[1] - abs(1.0 - mHeight);
}

void Image::setPosition(float x, float y) {
    mPosX = (2 * x / (float)mContext->getWidth()) - 1;
    mPosY = 1 - (2 * y / (float)mContext->getHeight());
    //mPosX = x;
    //mPosY = y;

    mVertices[0] = mPosX;
    mVertices[2] = mVertices[0] + abs(mWidth - (-1.0));
    mVertices[4] = mVertices[0] + abs(mWidth - (-1.0));
    mVertices[6] = mPosX;

    mVertices[1] = mPosY;
    mVertices[3] = mPosY;
    mVertices[5] = mVertices[1] - abs(1.0 - mHeight);
    mVertices[7] = mVertices[1] - abs(1.0 - mHeight);
}

void Image::setColor(float r, float g, float b) {
    mColours = new float []{
            r, g, b,
            r, g, b,
            r, g, b,
            r, g, b
    };
}

void Image::setTextureCoord(float *textureCoord) {
    mTextureCoords = textureCoord;
}

void Image::setTexture(GLuint texture) {
    mTexture = texture;

    setTextureCoord(new float []{
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
    });
}

void Image::render() {
    glUseProgram(*mProgram);

    glVertexAttribPointer(mVertexPosition, 2, GL_FLOAT, GL_FALSE, 0, mVertices);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(mVertexColourLocation, 3, GL_FLOAT, GL_FALSE, 0, mColours);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(mTextureCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, mTextureCoords);
    glEnableVertexAttribArray(2);

    glBindTexture(GL_TEXTURE_2D, mTexture);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, mIndices);

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glUseProgram(0);
}

float Image::getWidth() {
    return (mWidth + 1) * mContext->getWidth() / 2.0f;
}

float Image::getHeight() {
    return (-mHeight + 1) * mContext->getHeight() / 2.0f;
}

float Image::getPosX() {
    return (mPosX + 1) * mContext->getWidth() / 2.0f;
}

float Image::getPosY() {
    return (-mPosY + 1) * mContext->getHeight() / 2.0f;
}
