#include "MainView.h"
#include "../../Context.h"
#include "../../Manager.h"

MainView::MainView(Context *context, Manager* manager) : IView(context, manager) {
    mBgImg = new Image(mContext, (float)mContext->getWidth(), (float)mContext->getHeight(), mContext->getBgMainTexture());
}

void MainView::update() {

}

void MainView::render() {
    mBgImg->render();
}
