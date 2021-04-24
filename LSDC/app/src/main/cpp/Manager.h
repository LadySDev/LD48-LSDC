#ifndef LSDC_MANAGER_H
#define LSDC_MANAGER_H

#include <android/log.h>
#define LOG_TAG "libNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

class Context;
#include "render/view/IView.h"
#include "render/view/LoadView.h"
#include "render/view/MainView.h"

#include "utils/json.hpp"
#include <chrono>

class Manager {
public:
    Manager(Context* context);

    void onClick(float x, float y);
    void render();

    void launchMain();
private:
    Context* mContext;
    IView* mCurrentView;

    void init();

    nlohmann::json mData;

    bool mIsTimerRunning;
    std::chrono::time_point<std::chrono::system_clock> mTimerOld;
    std::chrono::time_point<std::chrono::system_clock> mTimerNew;

    int mParticles;
};


#endif //LSDC_MANAGER_H
