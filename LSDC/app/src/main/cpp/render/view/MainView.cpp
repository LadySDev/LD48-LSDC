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

    mMiner = new Sprite(mContext, 800.0, 800.0, mContext->getMinerTexture());
    mMiner->setPosition((float)mContext->getWidth() / 2.0f, mBgLifeBarImg->getPosY() + mBgLifeBarImg->getHeight() + 50.0f);
    mMiner->setOffset(-mMiner->getWidth() / 2.0f, 0.0f);
    mMiner->setTextureCoord(new float []{
            4 * 72.f / 360.f, 0 * 72.f / 936.f,
            (4 + 1) * 72.f / 360.f, 0 * 72.f / 936.f,
            (4 + 1) * 72.f / 360.f, (0 + 1) * 72.f / 936.f,
            4 * 72.f / 360.f, (0 + 1) * 72.f / 936.f
    });

    Animation* mMinerDigging = new Animation("minerDigging", 360.f, 936.f,72.f, 72.f, 0.15, true);
//    mMinerDigging->addFrame(0, 4);
//    mMinerDigging->addFrame(1, 4);
//    mMinerDigging->addFrame(2, 4);
//    mMinerDigging->addFrame(3, 4);
    mMinerDigging->addFrame(4, 4);
    mMinerDigging->addFrame(5, 4);
    mMinerDigging->addFrame(6, 4);
    mMinerDigging->addFrame(7, 4);
    mMinerDigging->addFrame(8, 4);
    mMinerDigging->addFrame(9, 4);

    LOGI("anim count: %i", mMinerDigging->getFrameCount());

    mMiner->addAnimation(mMinerDigging);
    mMiner->playAnimation("minerDigging");

}

void MainView::update(float elapsed, nlohmann::json data) {

    double timerD = (double)data["time"];
    int timerI = (int)std::trunc(timerD);
    //LOGI("timer: %f", timer);

    std::string timerText = "DUREE ";
    if(timerI >= 3600){
        int hour = timerI / 3600;
        int min = (timerI - (hour * 3600)) / 60;
        int sec = timerI - (min * 60);
        timerText = timerText + std::to_string(hour) + "H ";
        timerText = timerText + std::to_string(min) + "M ";
        timerText = timerText + std::to_string(sec) + "S";
    }
    else if(timerI >= 60){
        int min = timerI / 60;
        int sec = timerI - (min * 60);
        timerText = timerText + std::to_string(min) + "M ";
        timerText = timerText + std::to_string(sec) + "S";
    }
    else{
        timerText = timerText + std::to_string(timerI) + "S";
    }

    mTimerText->setText(timerText);

    mMiner->update(elapsed);

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

    mMiner->render();

    mTimerText->render();
    mTitleLevelText->render();

    mLevelLifeText->render();
    mLifeBarImg->render();
    mBgLifeBarImg->render();


    mBgImg->render();
}
