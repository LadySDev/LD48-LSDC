#include "MainView.h"
#include "../../Context.h"
#include "../../Manager.h"

MainView::MainView(Context *context, Manager* manager, nlohmann::json data) : IView(context, manager, data) {
    mBgImg = new Image(mContext, (float)mContext->getWidth(), (float)mContext->getHeight(), mContext->getBgMainTexture());

    mTimerText = new Text(mContext, 250.0f, 250.0f, mContext->getFontTexture(), "ABCD");

    mTitleLevelText = new Text(mContext, 250.0f, 250.0f, mContext->getFontTexture(), "LEVEL");
    mTitleLevelText->setPosition((float)mContext->getWidth() / 2.0f, 0.0f);

    mParticleTexts = std::vector<std::pair<int, Text*>>();
}

void MainView::update(nlohmann::json data) {


    double timer = (double)data["time"];
    int test = (int)std::trunc(timer);
    //LOGI("timer: %f", timer);
    mTimerText->setText(std::to_string(test));

    for(int i=0;i<data["particles"].size();i++){
        int index = data["particles"][i]["id"];

        bool found = false;
        for(int j=0;j<mParticleTexts.size();j++){

            if(mParticleTexts[j].first == index){
                found = true;
                break;
            }

        }

        if(found == false){
            float posX = ((float)data["particles"][i]["x"] + 1) * (float)mContext->getWidth() / 2.0f;
            float posY = (-(float)data["particles"][i]["y"] + 1) * (float)mContext->getHeight() / 2.0f;

            Text* text = new Text(mContext, 250.0f, 250.0f, mContext->getFontTexture(), "PARTICULE");
            text->setPosition(posX, posY);

            mParticleTexts.push_back(std::pair<int, Text*>(index, text));
        }

    }

    for(int i=mParticleTexts.size()-1;i>-1;i--){
        bool found = false;
        for(int j=0;j<data["particles"].size();j++){
            if(mParticleTexts[i].first == data["particles"][j]["id"]){
                found = true;
                break;
            }
        }

        if(found == false){
            mParticleTexts.erase(mParticleTexts.begin() + i);
            break;
        }
    }
}

void MainView::render() {
    mTimerText->render();
    mTitleLevelText->render();

    for(int i=0;i<mParticleTexts.size();i++){
        mParticleTexts[i].second->render();
    }


    mBgImg->render();
}
