#ifndef LSDC_ANIMATION_H
#define LSDC_ANIMATION_H

#include <string>
#include <vector>
#include <array>

class Animation {
public:
    Animation(std::string name, float textureWidth, float textureHeight, float frameWidth, float frameHeight, float framerate, bool looping);

    std::string getName();

    void addFrame(int row, int col);
    std::array<float, 8> getFrame(int number);

    float getFramerate();
    bool isLooping();
    int getFrameCount();
    void setCurrentFrame(int number);
    int getCurrentFrame();
private:
    std::string mName;

    float mTextureWidth;
    float mTextureHeight;
    float mFrameWidth;
    float mFrameHeight;

    float mFramerate;

    bool mIsLooping;

    int mCurrentFrame;
    std::vector<std::array<float, 8>> mFrames;
};


#endif //LSDC_ANIMATION_H
