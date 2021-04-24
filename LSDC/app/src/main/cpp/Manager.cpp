#include "Manager.h"

Manager::Manager(Context *context) {
    mContext = context;

    init();
}

void Manager::init() {
    mCurrentView = new LoadView(mContext);
}

void Manager::render() {
    if(mCurrentView != nullptr){
        mCurrentView->render();
    }
}
