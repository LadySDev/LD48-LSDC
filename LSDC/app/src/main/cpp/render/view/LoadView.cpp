#include "LoadView.h"
#include "../../Context.h"
#include "../../Manager.h"

LoadView::LoadView(Context* context, Manager* manager) : IView(context, manager) {
    mBgLoadImg = new Image(mContext, (float)mContext->getWidth(), (float)mContext->getHeight(), mContext->getBgLoadTexture());

    mIsTimerRunning = true;
    mTimerOld = std::chrono::system_clock::now();
}

void LoadView::update() {
    if(mIsTimerRunning == true) {
        mTimerNew = std::chrono::system_clock::now();
        double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                mTimerNew - mTimerOld).count();
        elapsed = elapsed / 1000.0;
        //LOGI("timer: %f", elapsed);
        if (elapsed >= 5.0) {
            mIsTimerRunning = false;
            mManager->launchMain();
        }
    }
}

void LoadView::render() {
    mBgLoadImg->render();
}
