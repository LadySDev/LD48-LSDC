#include "Manager.h"
#include "Context.h"

Manager::Manager(Context *context) {
    mContext = context;
    mData = {};

    init();

    mIsTimerRunning = true;
    mTimerOld = std::chrono::system_clock::now();
}

void Manager::init() {
    mCurrentView = new LoadView(mContext, this, mData);
}

void Manager::render() {
    //if(mIsTimerRunning == true) {
        mTimerNew = std::chrono::system_clock::now();
        double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                mTimerNew - mTimerOld).count();
        elapsed = elapsed / 1000.0;
        mTimerOld = std::chrono::system_clock::now();
    //}

    if(mCurrentView != nullptr){

        if(dynamic_cast<MainView*>(mCurrentView) != nullptr){
            mData["time"] = (double)mData["time"] + elapsed;
        }

        mCurrentView->update(mData);
    }
    if(mCurrentView != nullptr){
        mCurrentView->render();
    }
}

void Manager::launchMain() {
    mData = {};
    mData["time"] = 0;
    mCurrentView = new MainView(mContext, this, mData);
}
