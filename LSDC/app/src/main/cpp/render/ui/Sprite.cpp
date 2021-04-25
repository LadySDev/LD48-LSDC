#include "Sprite.h"

Sprite::Sprite(Context *context, float width, float height, GLuint texture) {
    mContext = context;
    mProgram = mContext->getUIShader()->getProgram();
    mTexture = texture;

    mPosX = 0.0f;
    mPosY = 0.0f;

    mOffsetX = 0.0f;
    mOffsetY = 0.0f;

    mWidth = width;
    mHeight = height;

    mImage = new Image(mContext, mWidth, mHeight, mTexture);
    mAnimTimer = 0.0f;
}

void Sprite::update(float elapsed) {
    if(mIsAnimPlaying == true){
        mAnimTimer = mAnimTimer + elapsed;

        if(mAnimTimer >= mCurrentAnimation->getFramerate()){
            mAnimTimer = 0;

            int currentFrame = mCurrentAnimation->getCurrentFrame();

            if(currentFrame < mCurrentAnimation->getFrameCount() - 1){
                std::array<float, 8> frame = mCurrentAnimation->getFrame(currentFrame + 1);
                float* correctFrame = new float []{
                        frame[0], frame[1],
                        frame[2], frame[3],
                        frame[4], frame[5],
                        frame[6], frame[7],
                };
                mImage->setTextureCoord(correctFrame);
                mCurrentAnimation->setCurrentFrame(currentFrame + 1);
            }
            else if(currentFrame == mCurrentAnimation->getFrameCount() - 1 && mCurrentAnimation->isLooping()){
                std::array<float, 8> frame = mCurrentAnimation->getFrame(0);
                float* correctFrame = new float []{
                        frame[0], frame[1],
                        frame[2], frame[3],
                        frame[4], frame[5],
                        frame[6], frame[7],
                };
                mImage->setTextureCoord(correctFrame);
                mCurrentAnimation->setCurrentFrame(0);
            }
            else{
                mIsAnimPlaying = false;
            }
        }
    }
}

void Sprite::render() {
    mImage->render();
}

float Sprite::getWidth() {
    return mWidth;
}

float Sprite::getHeight() {
    return mHeight;
}

void Sprite::setPosition(float x, float y) {
    mPosX = x;
    mPosY = y;

    mImage->setPosition(mPosX + mOffsetX, mPosY + mOffsetY);
}

float Sprite::getPosX() {
    return mPosX;
}

float Sprite::getPosY() {
    return mPosY;
}

void Sprite::setOffset(float offsetX, float offsetY) {
    mOffsetX = offsetX;
    mOffsetY = offsetY;

    mImage->setPosition(mPosX + mOffsetX, mPosY + mOffsetY);
}

void Sprite::setTextureCoord(float *textureCoord) {
    mImage->setTextureCoord(textureCoord);
}

void Sprite::addAnimation(Animation *animation) {
    mAnimations[animation->getName()] = animation;
}

void Sprite::playAnimation(std::string name) {
    mCurrentAnimation = mAnimations[name];

    if(mCurrentAnimation != nullptr){
        
        mIsAnimPlaying = true;
    }
}
