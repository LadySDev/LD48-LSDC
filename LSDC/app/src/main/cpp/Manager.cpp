#include "Manager.h"
#include "Context.h"

Manager::Manager(Context *context) {
    mContext = context;
    mData = {};

    init();

    mIsTimerRunning = true;
    mTimerOld = std::chrono::system_clock::now();

    startBGMEngine();
    startBGM();

    startBGMEngine2();
    startBGM2();
}

void Manager::init() {
    mCurrentView = new LoadView(mContext, this, mData);
}

void Manager::render() {
    //if(mIsTimerRunning == true) {
        mTimerNew = std::chrono::system_clock::now();
        double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                mTimerNew - mTimerOld).count();
        elapsed = elapsed / 1000.0;
        mTimerOld = std::chrono::system_clock::now();
    //}

    if(mCurrentView != nullptr){

        if(dynamic_cast<MainView*>(mCurrentView) != nullptr){
            mData["time"] = (double)mData["time"] + elapsed;

            for(int i=mData["particles"].size() - 1;i>-1;i--){
                mData["particles"][i]["life"] = (double)mData["particles"][i]["life"] - (double)elapsed;

                if(mData["particles"][i]["life"] <= 0){
                    mData["particles"].erase(i);
                }
            }
        }

        mCurrentView->update(elapsed, mData);
    }
    if(mCurrentView != nullptr){
        mCurrentView->render();
    }
}

void Manager::launchMain() {
    mData = {};
    mData["time"] = 0;
    mData["level"] = 1;
    mData["levelMaxLife"] = 20;
    mData["levelCurrentLife"] = 20;
    mData["damage"] = 1;
    mData["particles"] = {};

    mParticles = 0;

    mCurrentView = new MainView(mContext, this, mData);
}

void Manager::onClick(float x, float y) {
    if(dynamic_cast<MainView*>(mCurrentView) != nullptr){

        nlohmann::json particle;
        particle["id"] = mParticles;
        particle["value"] = 10;
        particle["x"] = x;
        particle["y"] = y;
        particle["life"] = 1.0;

        mData["particles"].push_back(particle);

        mParticles = mParticles + 1;

        mData["levelCurrentLife"] = (int)mData["levelCurrentLife"] - (int)mData["damage"];

        if((int)mData["levelCurrentLife"] == 0){
            mData["level"] = (int)mData["level"] + 1;
            mData["levelMaxLife"] = 20;
            mData["levelCurrentLife"] = 20;
            mData["damage"] = 1;
        }
    }
}

bool Manager::startBGMEngine() {
    SLresult result;
    const SLuint32 engineMixIIDCount = 1;
    const SLInterfaceID engineMixIIDs[] = {SL_IID_ENGINE};
    const SLboolean engineMixReqs[] = {SL_BOOLEAN_TRUE};
    const SLuint32 outputMixIIDCount = 0;
    const SLInterfaceID outputMixIIDs[] = {};
    const SLboolean outputMixReqs[] = {};

    // Creates OpenSL ES engine and dumps its capabilities.
    result = slCreateEngine(&mEngineObj, 0, NULL, engineMixIIDCount, engineMixIIDs, engineMixReqs);
    if (result != SL_RESULT_SUCCESS) { exit(-1); };
    result = (*mEngineObj)->Realize(mEngineObj,SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS) { exit(-1); };
    result = (*mEngineObj)->GetInterface(mEngineObj, SL_IID_ENGINE, &mEngine);
    if (result != SL_RESULT_SUCCESS) { exit(-1); };
    // Creates audio output.
    result = (*mEngine)->CreateOutputMix(mEngine, &mOutputMixObj, outputMixIIDCount, outputMixIIDs, outputMixReqs);
    result = (*mOutputMixObj)->Realize(mOutputMixObj,SL_BOOLEAN_FALSE);
    return true;
}

void Manager::stopBGMEngine() {
    stopBGM();

    if (mOutputMixObj != NULL) {
        (*mOutputMixObj)->Destroy(mOutputMixObj);
        mOutputMixObj = NULL;
    }
    if (mEngineObj != NULL) {
        (*mEngineObj)->Destroy(mEngineObj);
        mEngineObj = NULL; mEngine = NULL;
    }

}

bool Manager::startBGM() {
    SLresult result;
    if (mContext->mDescriptor["descriptor"] < 0) {
        exit(-1);
    }
    SLDataLocator_AndroidFD dataLocatorIn;
    dataLocatorIn.locatorType = SL_DATALOCATOR_ANDROIDFD;
    dataLocatorIn.fd = mContext->mDescriptor["descriptor"];
    dataLocatorIn.offset = mContext->mDescriptor["start"];
    dataLocatorIn.length = mContext->mDescriptor["length"];
    SLDataFormat_MIME dataFormat;
    dataFormat.formatType = SL_DATAFORMAT_MIME;
    dataFormat.mimeType = NULL;
    dataFormat.containerType = SL_CONTAINERTYPE_UNSPECIFIED;
    SLDataSource dataSource;
    dataSource.pLocator = &dataLocatorIn;
    dataSource.pFormat = &dataFormat;
    SLDataLocator_OutputMix dataLocatorOut;
    dataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
    dataLocatorOut.outputMix = mOutputMixObj;
    SLDataSink dataSink;
    dataSink.pLocator = &dataLocatorOut;
    dataSink.pFormat = NULL;
    const SLuint32 bgmPlayerIIDCount = 2;
    const SLInterfaceID bgmPlayerIIDs[] = { SL_IID_PLAY, SL_IID_SEEK };
    const SLboolean bgmPlayerReqs[] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
    result = (*mEngine)->CreateAudioPlayer(mEngine, &mBGMPlayerObj, &dataSource, &dataSink, bgmPlayerIIDCount, bgmPlayerIIDs, bgmPlayerReqs);
    if (result != SL_RESULT_SUCCESS) exit(-1);
    result = (*mBGMPlayerObj)->Realize(mBGMPlayerObj, SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS) exit(-1);
    result = (*mBGMPlayerObj)->GetInterface(mBGMPlayerObj, SL_IID_PLAY, &mBGMPlayer);
    if (result != SL_RESULT_SUCCESS) exit(-1);
    result = (*mBGMPlayerObj)->GetInterface(mBGMPlayerObj, SL_IID_SEEK, &mBGMPlayerSeek);
    if (result != SL_RESULT_SUCCESS) exit(-1);
    result = (*mBGMPlayerSeek)->SetLoop(mBGMPlayerSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
    if (result != SL_RESULT_SUCCESS) exit(-1);
    result = (*mBGMPlayer)->SetPlayState(mBGMPlayer, SL_PLAYSTATE_PLAYING);
    if (result != SL_RESULT_SUCCESS) exit(-1);
    return true;
}

void Manager::stopBGM() {
    if (mBGMPlayer != NULL) {
        SLuint32 bgmPlayerState;
        (*mBGMPlayerObj)->GetState(mBGMPlayerObj, &bgmPlayerState);
        if (bgmPlayerState == SL_OBJECT_STATE_REALIZED) {
            (*mBGMPlayer)->SetPlayState(mBGMPlayer, SL_PLAYSTATE_PAUSED);
            (*mBGMPlayerObj)->Destroy(mBGMPlayerObj);
            mBGMPlayerObj = NULL;
            mBGMPlayer = NULL;
            mBGMPlayerSeek = NULL;
        }
    }
}

bool Manager::startBGMEngine2() {
    SLresult result;
    const SLuint32 engineMixIIDCount = 1;
    const SLInterfaceID engineMixIIDs[] = {SL_IID_ENGINE};
    const SLboolean engineMixReqs[] = {SL_BOOLEAN_TRUE};
    const SLuint32 outputMixIIDCount = 0;
    const SLInterfaceID outputMixIIDs[] = {};
    const SLboolean outputMixReqs[] = {};

    // Creates OpenSL ES engine and dumps its capabilities.
    result = slCreateEngine(&mEngineObj2, 0, NULL, engineMixIIDCount, engineMixIIDs, engineMixReqs);
    if (result != SL_RESULT_SUCCESS) { exit(-1); };
    result = (*mEngineObj2)->Realize(mEngineObj2,SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS) { exit(-1); };
    result = (*mEngineObj2)->GetInterface(mEngineObj2, SL_IID_ENGINE, &mEngine2);
    if (result != SL_RESULT_SUCCESS) { exit(-1); };
    // Creates audio output.
    result = (*mEngine2)->CreateOutputMix(mEngine2, &mOutputMixObj2, outputMixIIDCount, outputMixIIDs, outputMixReqs);
    result = (*mOutputMixObj2)->Realize(mOutputMixObj2,SL_BOOLEAN_FALSE);
    return true;
}

void Manager::stopBGMEngine2() {
    stopBGM();

    if (mOutputMixObj2 != NULL) {
        (*mOutputMixObj2)->Destroy(mOutputMixObj2);
        mOutputMixObj2 = NULL;
    }
    if (mEngineObj2 != NULL) {
        (*mEngineObj2)->Destroy(mEngineObj2);
        mEngineObj2 = NULL; mEngine2 = NULL;
    }

}

bool Manager::startBGM2() {
    SLresult result;
    if (mContext->mDescriptor2["descriptor"] < 0) {
        exit(-1);
    }
    SLDataLocator_AndroidFD dataLocatorIn;
    dataLocatorIn.locatorType = SL_DATALOCATOR_ANDROIDFD;
    dataLocatorIn.fd = mContext->mDescriptor2["descriptor"];
    dataLocatorIn.offset = mContext->mDescriptor2["start"];
    dataLocatorIn.length = mContext->mDescriptor2["length"];
    SLDataFormat_MIME dataFormat;
    dataFormat.formatType = SL_DATAFORMAT_MIME;
    dataFormat.mimeType = NULL;
    dataFormat.containerType = SL_CONTAINERTYPE_UNSPECIFIED;
    SLDataSource dataSource;
    dataSource.pLocator = &dataLocatorIn;
    dataSource.pFormat = &dataFormat;
    SLDataLocator_OutputMix dataLocatorOut;
    dataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
    dataLocatorOut.outputMix = mOutputMixObj2;
    SLDataSink dataSink;
    dataSink.pLocator = &dataLocatorOut;
    dataSink.pFormat = NULL;
    const SLuint32 bgmPlayerIIDCount = 2;
    const SLInterfaceID bgmPlayerIIDs[] = { SL_IID_PLAY, SL_IID_SEEK };
    const SLboolean bgmPlayerReqs[] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
    result = (*mEngine2)->CreateAudioPlayer(mEngine2, &mBGMPlayerObj2, &dataSource, &dataSink, bgmPlayerIIDCount, bgmPlayerIIDs, bgmPlayerReqs);
    if (result != SL_RESULT_SUCCESS) exit(-1);
    result = (*mBGMPlayerObj2)->Realize(mBGMPlayerObj2, SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS) exit(-1);
    result = (*mBGMPlayerObj2)->GetInterface(mBGMPlayerObj2, SL_IID_PLAY, &mBGMPlayer2);
    if (result != SL_RESULT_SUCCESS) exit(-1);
    result = (*mBGMPlayerObj2)->GetInterface(mBGMPlayerObj2, SL_IID_SEEK, &mBGMPlayerSeek2);
    if (result != SL_RESULT_SUCCESS) exit(-1);
    result = (*mBGMPlayerSeek2)->SetLoop(mBGMPlayerSeek2, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
    if (result != SL_RESULT_SUCCESS) exit(-1);
    result = (*mBGMPlayer2)->SetPlayState(mBGMPlayer2, SL_PLAYSTATE_PLAYING);
    if (result != SL_RESULT_SUCCESS) exit(-1);
    return true;
}

void Manager::stopBGM2() {
    if (mBGMPlayer2 != NULL) {
        SLuint32 bgmPlayerState;
        (*mBGMPlayerObj2)->GetState(mBGMPlayerObj2, &bgmPlayerState);
        if (bgmPlayerState == SL_OBJECT_STATE_REALIZED) {
            (*mBGMPlayer2)->SetPlayState(mBGMPlayer2, SL_PLAYSTATE_PAUSED);
            (*mBGMPlayerObj2)->Destroy(mBGMPlayerObj2);
            mBGMPlayerObj2 = NULL;
            mBGMPlayer2 = NULL;
            mBGMPlayerSeek2 = NULL;
        }
    }
}
