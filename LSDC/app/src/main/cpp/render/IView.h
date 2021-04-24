#ifndef LSDC_IVIEW_H
#define LSDC_IVIEW_H

#include "../Context.h"
#include "ui/Image.h"

class IView {
public:
    IView(Context* context){ mContext = context; }
    virtual void render() = 0;
protected:
    Context* mContext;
};


#endif //LSDC_IVIEW_H
