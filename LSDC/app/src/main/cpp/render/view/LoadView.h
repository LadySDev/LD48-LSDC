#ifndef LSDC_LOADVIEW_H
#define LSDC_LOADVIEW_H

#include <android/log.h>
#define LOG_TAG "libNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#include "IView.h"
#include <chrono>

class LoadView : public IView {
public:
    LoadView(Context* context, Manager* manager);

    virtual void update();
    virtual void render();
private:
    Image* mBgLoadImg;
    bool mIsTimerRunning;
    std::chrono::time_point<std::chrono::system_clock> mTimerOld;
    std::chrono::time_point<std::chrono::system_clock> mTimerNew;
};


#endif //LSDC_LOADVIEW_H
