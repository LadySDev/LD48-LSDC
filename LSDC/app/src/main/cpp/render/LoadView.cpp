#include "LoadView.h"

LoadView::LoadView(Context* context) : IView(context) {
    mBgLoadImg = new Image(mContext, (float)mContext->getWidth(), (float)mContext->getHeight(), mContext->getBgLoadTexture());
}

void LoadView::render() {
    mBgLoadImg->render();
}
