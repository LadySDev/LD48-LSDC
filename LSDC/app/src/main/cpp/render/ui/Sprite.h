#ifndef LSDC_SPRITE_H
#define LSDC_SPRITE_H

#include "../../Context.h"
#include "Image.h"
#include "Animation.h"

#include <map>

#include <android/log.h>
#define LOG_TAG "libNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

class Sprite {
public:
    Sprite(Context* context, float width, float height, GLuint texture);

    void update(float elapsed);
    void render();

    float getWidth();
    float getHeight();

    void setPosition(float x, float y);
    float getPosX();
    float getPosY();

    void setOffset(float offsetX, float offsetY);

    void setTextureCoord(float *textureCoord);

    void addAnimation(Animation* animation);

    void playAnimation(std::string name);
private:
    Context* mContext;
    GLuint* mProgram;
    GLuint mTexture;

    float mPosX;
    float mPosY;

    float mOffsetX;
    float mOffsetY;

    float mWidth;
    float mHeight;

    Image* mImage;
    std::map<std::string, Animation*> mAnimations;

    Animation* mCurrentAnimation;
    bool mIsAnimPlaying;
    float mAnimTimer;
};


#endif //LSDC_SPRITE_H
