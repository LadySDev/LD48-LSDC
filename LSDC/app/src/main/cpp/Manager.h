#ifndef LSDC_MANAGER_H
#define LSDC_MANAGER_H


class Context;
#include "render/view/IView.h"
#include "render/view/LoadView.h"
#include "render/view/MainView.h"

#include "utils/json.hpp"
#include <chrono>

class Manager {
public:
    Manager(Context* context);

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
};


#endif //LSDC_MANAGER_H
