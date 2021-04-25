#include "MainView.h"
#include "../../Context.h"
#include "../../Manager.h"

MainView::MainView(Context *context, Manager* manager, nlohmann::json data) : IView(context, manager, data) {
    mBgImg = new Image(mContext, (float)mContext->getWidth(), (float)mContext->getHeight(), mContext->getBgMainTexture());

    mTimerText = new Text(mContext, 250.0f, 250.0f, mContext->getFontTexture(), "DUREE 0S");
    mTimerText->setPosition(0.0f, (float)mContext->getHeight() - mTimerText->getHeightBounds());

    mTitleLevelText = new Text(mContext, 250.0f, 250.0f, mContext->getFontTexture(), "LEVEL" + std::to_string((int)data["level"]));
    mTitleLevelText->setPosition((float)mContext->getWidth() / 2.0f, 0.0f);
    mTitleLevelText->setOffsetX(-mTitleLevelText->getWidthBounds() / 2.0f);

    mBgLifeBarImg = new Image(mContext, 810.0, 105.0, mContext->getLifeBarTexture());
    mBgLifeBarImg->setTextureCoord(new float []{
            0.0f, 0 * 105.f / 211.f,
            1.0f, 0 * 105.f / 211.f,
            1.0f, (0 + 1) * 105.f / 211.f,
            0.0f, (0 + 1) * 105.f / 211.f
    });
    mBgLifeBarImg->setPosition((float)mContext->getWidth() / 2.0f - mBgLifeBarImg->getWidth() / 2.0f, mTitleLevelText->getPosY() + mTitleLevelText->getHeightBounds());

    mLifeBarImg = new Image(mContext, 810.0, 105.0, mContext->getLifeBarTexture());
    mLifeBarImg->setTextureCoord(new float []{
            0.0f, 1 * 105.f / 211.f,
            1.0f, 1 * 105.f / 211.f,
            1.0f, (1 + 1) * 105.f / 211.f,
            0.0f, (1 + 1) * 105.f / 211.f
    });
    mLifeBarImg->setPosition(mBgLifeBarImg->getPosX(), mBgLifeBarImg->getPosY());
    mLifeBarImg->setColor(1.0f, 0.0f, 0.0f);

    mLevelLifeText = new Text(mContext, 810.0f, 105.0f, mContext->getFontTexture(), std::to_string((int)data["levelCurrentLife"]) + " " + std::to_string((int)data["levelMaxLife"]));
    mLevelLifeText->setPosition(mBgLifeBarImg->getPosX() + mBgLifeBarImg->getWidth() / 2.0f, mBgLifeBarImg->getPosY() + mBgLifeBarImg->getHeight() / 2.0f);
    mLevelLifeText->setOffsetX(-mLevelLifeText->getWidthBounds() / 2.0f);
    mLevelLifeText->setOffsetY(-mLevelLifeText->getHeightBounds() / 2.0f);

    mParticleTexts = std::vector<std::pair<int, Text*>>();
}

void MainView::update(nlohmann::json data) {


    double timer = (double)data["time"];
    int test = (int)std::trunc(timer);
    //LOGI("timer: %f", timer);
    mTimerText->setText("DUREE " + std::to_string(test) + "S");

    for(int i=0;i<data["particles"].size();i++){
        int index = data["particles"][i]["id"];

        bool found = false;
        for(int j=0;j<mParticleTexts.size();j++){

            if(mParticleTexts[j].first == index){

                mParticleTexts[j].second->setPosition(mParticleTexts[j].second->getPosX(), mParticleTexts[j].second->getPosY() - 1);
                mParticleTexts[j].second->setCharacterSize(mParticleTexts[j].second->getCharacterSize() - 1);

                found = true;
                break;
            }

        }

        if(found == false){
            float posX = ((float)data["particles"][i]["x"] + 1) * (float)mContext->getWidth() / 2.0f;
            float posY = (-(float)data["particles"][i]["y"] + 1) * (float)mContext->getHeight() / 2.0f;

            Text* text = new Text(mContext, 250.0f, 250.0f, mContext->getFontTexture(), std::to_string((int)mData["damage"]));
            text->setPosition(posX, posY);
            text->setOffsetX( - text->getWidthBounds() / 2.0f);
            text->setOffsetY(- text->getHeightBounds() / 2.0f);

            mParticleTexts.push_back(std::pair<int, Text*>(index, text));

            mLevelLifeText->setText(std::to_string((int)data["levelCurrentLife"]) + " " + std::to_string((int)data["levelMaxLife"]));
            mLevelLifeText->setOffsetX(-mLevelLifeText->getWidthBounds() / 2.0f);
            mLevelLifeText->setOffsetY(-mLevelLifeText->getHeightBounds() / 2.0f);

            mTitleLevelText->setText("LEVEL" + std::to_string((int)data["level"]));
            mTitleLevelText->setOffsetX(-mTitleLevelText->getWidthBounds() / 2.0f);

            float percent = (float)data["levelCurrentLife"] / (float)data["levelMaxLife"];
            LOGI("percent: %f", percent);
            LOGI("bg bar life width: %f", mBgLifeBarImg->getWidth());
            LOGI("multip: %f", mBgLifeBarImg->getWidth() * percent);
            mLifeBarImg->setSize(mBgLifeBarImg->getWidth() * percent, mLifeBarImg->getHeight());
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
    for(int i=0;i<mParticleTexts.size();i++){
        mParticleTexts[i].second->render();
    }


    mTimerText->render();
    mTitleLevelText->render();

    mLevelLifeText->render();
    mLifeBarImg->render();
    mBgLifeBarImg->render();


    mBgImg->render();
}
