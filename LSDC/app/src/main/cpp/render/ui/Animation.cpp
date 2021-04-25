#include "Animation.h"

Animation::Animation(std::string name, float textureWidth, float textureHeight, float frameWidth, float frameHeight, float framerate, bool looping) {
    mName = name;

    mTextureWidth = textureWidth;
    mTextureHeight = textureHeight;
    mFrameWidth = frameWidth;
    mFrameHeight = frameHeight;

    mFramerate = framerate;
    mIsLooping = looping;

    mCurrentFrame = 0;

    mFrames = std::vector<std::array<float, 8>>();
}

std::string Animation::getName() {
    return mName;
}

void Animation::addFrame(int row, int col) {
    std::array<float, 8> frame = {
            col * mFrameWidth / mTextureWidth, row * mFrameHeight / mTextureHeight,
            (col + 1) * mFrameWidth / mTextureWidth, row * mFrameHeight / mTextureHeight,
            (col + 1) * mFrameWidth / mTextureWidth, (row + 1) * mFrameHeight / mTextureHeight,
            col * mFrameWidth / mTextureWidth, (row + 1) * mFrameHeight / mTextureHeight
    };

    auto it = mFrames.begin();
    mFrames.insert(it, frame);
}

float Animation::getFramerate() {
    return mFramerate;
}

bool Animation::isLooping() {
    return mIsLooping;
}


int Animation::getFrameCount() {
    return mFrames.size();
}

void Animation::setCurrentFrame(int number) {
    mCurrentFrame = number;
}

int Animation::getCurrentFrame() {
    return mCurrentFrame;
}

std::array<float, 8> Animation::getFrame(int number) {
    return mFrames[number];
}
