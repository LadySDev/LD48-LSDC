#ifndef LSDC_MANAGER_H
#define LSDC_MANAGER_H


#include "Context.h"
#include "render/IView.h"
#include "render/LoadView.h"

class Manager {
public:
    Manager(Context* context);

    void render();
private:
    Context* mContext;
    IView* mCurrentView;

    void init();
};


#endif //LSDC_MANAGER_H
