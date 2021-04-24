#include "MainView.h"
#include "../../Context.h"
#include "../../Manager.h"

MainView::MainView(Context *context, Manager* manager, nlohmann::json data) : IView(context, manager, data) {
    mBgImg = new Image(mContext, (float)mContext->getWidth(), (float)mContext->getHeight(), mContext->getBgMainTexture());
    mTimerText = new Text(mContext, 250.0f, 250.0f, mContext->getFontTexture(), "ABCD");
}

void MainView::update(nlohmann::json data) {
    double timer = (double)data["time"];
    int test = (int)std::trunc(timer);
    //LOGI("timer: %f", timer);
    mTimerText->setText(std::to_string(test));
}

void MainView::render() {
    mTimerText->render();
    mBgImg->render();
}
