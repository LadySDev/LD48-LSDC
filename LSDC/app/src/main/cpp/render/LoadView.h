#ifndef LSDC_LOADVIEW_H
#define LSDC_LOADVIEW_H

#include "IView.h"

class LoadView : public IView {
public:
    LoadView(Context* context);

    virtual void render();
private:
    Image* mBgLoadImg;
};


#endif //LSDC_LOADVIEW_H
