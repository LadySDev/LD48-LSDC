#ifndef LSDC_IVIEW_H
#define LSDC_IVIEW_H

class Context;
class Manager;
#include "../ui/Image.h"
#include "../ui/Sprite.h"
#include "../ui/Animation.h"
#include "../ui/Text.h"
#include "../../utils/json.hpp"

class Manager;

class IView {
public:
    IView(Context* context, Manager* manager, nlohmann::json data){ mContext = context; mManager = manager; mData = data; }
    virtual void update(float elapsed, nlohmann::json data) = 0;
    virtual void render() = 0;
protected:
    Context* mContext;
    Manager* mManager;
    nlohmann::json mData;
};


#endif //LSDC_IVIEW_H
