#ifndef LSDC_LOADVIEW_H
#define LSDC_LOADVIEW_H

#include "IView.h"
#include <chrono>

class LoadView : public IView {
public:
    LoadView(Context* context, Manager* manager, nlohmann::json data);

    virtual void update(nlohmann::json data);
    virtual void render();
private:
    Image* mBgLoadImg;
    bool mIsTimerRunning;
    std::chrono::time_point<std::chrono::system_clock> mTimerOld;
    std::chrono::time_point<std::chrono::system_clock> mTimerNew;
};


#endif //LSDC_LOADVIEW_H
