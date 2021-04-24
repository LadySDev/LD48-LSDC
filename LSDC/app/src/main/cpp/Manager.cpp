#include "Manager.h"
#include "Context.h"

Manager::Manager(Context *context) {
    mContext = context;

    init();
}

void Manager::init() {
    mCurrentView = new LoadView(mContext, this);
}

void Manager::render() {
    if(mCurrentView != nullptr){
        mCurrentView->update();
    }
    if(mCurrentView != nullptr){
        mCurrentView->render();
    }
}

void Manager::launchMain() {
    mCurrentView = new MainView(mContext, this);
}
