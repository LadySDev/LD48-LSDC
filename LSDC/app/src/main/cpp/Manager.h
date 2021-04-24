#ifndef LSDC_MANAGER_H
#define LSDC_MANAGER_H


class Context;
#include "render/view/IView.h"
#include "render/view/LoadView.h"
#include "render/view/MainView.h"

class Manager {
public:
    Manager(Context* context);

    void render();

    void launchMain();
private:
    Context* mContext;
    IView* mCurrentView;

    void init();
};


#endif //LSDC_MANAGER_H
