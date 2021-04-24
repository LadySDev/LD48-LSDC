#ifndef LSDC_MAINVIEW_H
#define LSDC_MAINVIEW_H

#include <android/log.h>
#define LOG_TAG "libNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#include "IView.h"

class MainView : public IView {
public:
    MainView(Context* context, Manager* manager, nlohmann::json data);

    virtual void update(nlohmann::json data);
    virtual void render();
private:
    Image* mBgImg;
    Text* mTimerText;
};


#endif //LSDC_MAINVIEW_H
