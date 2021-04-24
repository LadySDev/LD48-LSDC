#ifndef LSDC_IVIEW_H
#define LSDC_IVIEW_H

class Context;
class Manager;
#include "../ui/Image.h"

class Manager;

class IView {
public:
    IView(Context* context, Manager* manager){ mContext = context; mManager = manager; }
    virtual void update() = 0;
    virtual void render() = 0;
protected:
    Context* mContext;
    Manager* mManager;
};


#endif //LSDC_IVIEW_H
