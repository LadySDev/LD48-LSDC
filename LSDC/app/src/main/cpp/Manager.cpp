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

            for(int i=mData["particles"].size() - 1;i>-1;i--){
                mData["particles"][i]["life"] = (double)mData["particles"][i]["life"] - (double)elapsed;

                if(mData["particles"][i]["life"] <= 0){
                    mData["particles"].erase(i);
                }
            }
        }

        mCurrentView->update(elapsed, mData);
    }
    if(mCurrentView != nullptr){
        mCurrentView->render();
    }
}

void Manager::launchMain() {
    mData = {};
    mData["time"] = 0;
    mData["level"] = 1;
    mData["levelMaxLife"] = 20;
    mData["levelCurrentLife"] = 20;
    mData["damage"] = 1;
    mData["particles"] = {};

    mParticles = 0;

    mCurrentView = new MainView(mContext, this, mData);
}

void Manager::onClick(float x, float y) {
    if(dynamic_cast<MainView*>(mCurrentView) != nullptr){

        nlohmann::json particle;
        particle["id"] = mParticles;
        particle["value"] = 10;
        particle["x"] = x;
        particle["y"] = y;
        particle["life"] = 1.0;

        mData["particles"].push_back(particle);

        mParticles = mParticles + 1;

        mData["levelCurrentLife"] = (int)mData["levelCurrentLife"] - (int)mData["damage"];

        if((int)mData["levelCurrentLife"] == 0){
            mData["level"] = (int)mData["level"] + 1;
            mData["levelMaxLife"] = 20;
            mData["levelCurrentLife"] = 20;
            mData["damage"] = 1;
        }
    }
}
