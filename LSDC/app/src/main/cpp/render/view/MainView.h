#ifndef LSDC_MAINVIEW_H
#define LSDC_MAINVIEW_H


#include "IView.h"

class MainView : public IView {
public:
    MainView(Context* context, Manager* manager);

    virtual void update();
    virtual void render();
private:
    Image* mBgImg;
};


#endif //LSDC_MAINVIEW_H
