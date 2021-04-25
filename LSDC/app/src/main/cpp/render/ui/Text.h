#ifndef LSDC_TEXT_H
#define LSDC_TEXT_H

#include <android/log.h>
#define LOG_TAG "libNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#include "../../Context.h"
#include "Image.h"
#include <string>
#include <vector>

class Text {
public:
    Text(Context* context, float width, float height, GLuint texture, std::string text);

    void render();

    void setText(std::string text);
    void setCharacterSize(int size);
    int getCharacterSize();

    void setPosition(float x, float y);
    float getPosX();
    float getPosY();

    void setOffsetX(float offset);
    void setOffsetY(float offset);

    float getWidthBounds();
    float getHeightBounds();
private:
    Context* mContext;
    GLuint* mProgram;
    GLuint mTexture;

    float mWidth;
    float mHeight;

    float mPosX;
    float mPosY;

    float mOffsetX;
    float mOffsetY;

    std::string mText;
    int mCharacterSize;
    int mCharacterSpacing;

    std::vector<Image> mImages;

    Image getLetter(int row, int col);
    void addLetter(char letter);

    void updateImages();
};


#endif //LSDC_TEXT_H
