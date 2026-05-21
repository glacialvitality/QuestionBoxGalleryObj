#include "QuestionBoxGalleryObj.h"

extern "C" {
    //tryStageEffectStart__Q22MR11StageEffectFP9LiveActorPCc=0x8023CD30
    StageEffect* __kAutoMap_8023CD30(LiveActor*, const char*);

    //tryStageEffectMoving__Q22MR11StageEffectFP9LiveActorPCc=0x8023CE74
    LiveActor* __kAutoMap_8023CE74(LiveActor*, const char*);

    //tryStageEffectStop__Q22MR11StageEffectFP9LiveActorPCc=0x8023CF40
    LiveActor* __kAutoMap_8023CF40(LiveActor*, const char*);
};

namespace NrvQuestionBoxGalleryObj {
    FULL_NERVE(QuestionBoxGalleryObjNrvOnStart, QuestionBoxGalleryObj, OnStart);
    FULL_NERVE(QuestionBoxGalleryObjNrvOnWait, QuestionBoxGalleryObj, OnWait);
    FULL_NERVE(QuestionBoxGalleryObjNrvOffStart, QuestionBoxGalleryObj, OffStart);
    FULL_NERVE(QuestionBoxGalleryObjNrvOffWait, QuestionBoxGalleryObj, OffWait);
};  // namespace NrvQuestionBoxGalleryObj

QuestionBoxGalleryObj::QuestionBoxGalleryObj(const char* pName) : MapObjActor(pName) {}

void QuestionBoxGalleryObj::init(const JMapInfoIter& rIter) {
    MapObjActor::init(rIter);
    MapObjActorInitInfo rInitInfo;

    if (MR::isEqualSubString(mObjName, "Planet")) {
        rInitInfo.setupHioNode("惑星");
    } else {
        rInitInfo.setupHioNode("地形オブジェ");
    }

    rInitInfo.setupDefaultPos();
    rInitInfo.setupConnectToScene();
    rInitInfo.setupGroupClipping(8);
    rInitInfo.setupEffect(nullptr, nullptr);
    rInitInfo.setupSound(4, nullptr);

    if (MR::isEqualSubString(mObjName, "PlanetA")) {
        rInitInfo.setupFarClipping(-1.0f);
    } else {
        rInitInfo.setupFarClipping(100.0f);
    }

    f32 rRotateSpeedArg = 3.4028235e38f;
    MR::getMapPartsArgRotateSpeed(&rRotateSpeedArg, rIter);

    if (MR::isConnectedWithRail(rIter)) {
        rInitInfo.setupRailMover();
    } else if (rRotateSpeedArg != 0.0f && rRotateSpeedArg != 3.4028235e38f) {
        rInitInfo.setupRotator();
        rInitInfo.setupProjmapMtx(false, false);
    }

    initialize(rIter, rInitInfo);
    startMapPartsFunctions();

    bool v6 = false;
    MR::getJMapInfoArg0NoInit(rIter, &v6);

    if (v6) {
        initNerve(&NrvQuestionBoxGalleryObj::QuestionBoxGalleryObjNrvOnWait::sInstance, 0);
    } else {
        initNerve(&NrvQuestionBoxGalleryObj::QuestionBoxGalleryObjNrvOffWait::sInstance, 0);
    }
}

void QuestionBoxGalleryObj::exeOnStart() {
    if (MR::isFirstStep(this)) {
        MR::tryStartAllAnim(this, "On");
    }

    if (MR::isBckStopped(this)) {
        setNerve(&NrvQuestionBoxGalleryObj::QuestionBoxGalleryObjNrvOnWait::sInstance);
    }
}

void QuestionBoxGalleryObj::exeOnWait() {
    if (MR::isFirstStep(this)) {
        MR::tryStartAllAnim(this, "On");
        MR::setBckFrameAndStop(this, MR::getBckFrameMax(this));
    }
}

void QuestionBoxGalleryObj::exeOffStart() {
    if (MR::isFirstStep(this)) {
        MR::tryStartAllAnim(this, "Off");
    }

    if (MR::isBckStopped(this)) {
        setNerve(&NrvQuestionBoxGalleryObj::QuestionBoxGalleryObjNrvOffWait::sInstance);
    }
}

void QuestionBoxGalleryObj::exeOffWait() {
    if (MR::isFirstStep(this)) {
        MR::tryStartAllAnim(this, "Off");
        MR::setBckFrameAndStop(this, MR::getBckFrameMax(this));
    }
}

void QuestionBoxGalleryObj::initCaseUseSwitchA(const MapObjActorInitInfo& pInitInfo) {
    MR::FunctorV0M< QuestionBoxGalleryObj*, void (QuestionBoxGalleryObj::*)() > SwitchOnFunc =
        MR::Functor< QuestionBoxGalleryObj >(this, &QuestionBoxGalleryObj::startSwitchOn);
    MR::listenStageSwitchOnA(this, SwitchOnFunc);
}

void QuestionBoxGalleryObj::initCaseUseSwitchB(const MapObjActorInitInfo& pInitInfo) {
    MR::FunctorV0M< QuestionBoxGalleryObj*, void (QuestionBoxGalleryObj::*)() > SwitchOnFunc =
        MR::Functor< QuestionBoxGalleryObj >(this, &QuestionBoxGalleryObj::startSwitchOff);
    MR::listenStageSwitchOnB(this, SwitchOnFunc);
}

void QuestionBoxGalleryObj::control() {
    MapObjActor::control();

    if (mRotator && MapObjActorUtil::isRotatorMoving(this)) {
        //MR::StageEffect::tryStageEffectMoving(this, mObjName);
        __kAutoMap_8023CE74(this,  mObjName);
        
    }

    if (mRailMover) {
        if (MapObjActorUtil::isRailMoverWorking(this)) {
            //MR::StageEffect::tryStageEffectMoving(this, mObjName);
            __kAutoMap_8023CE74(this, mObjName);
        }

        if (MapObjActorUtil::isRailMoverReachedEnd(this)) {
            //MR::StageEffect::tryStageEffectStop(this, mObjName);
            __kAutoMap_8023CF40(this, mObjName);
        }
    }
}

void QuestionBoxGalleryObj::startSwitchOn() {
    MR::startSound(this, "SE_OJ_Q_BOX_LIGHT_ON", -1, -1);
    setNerve(&NrvQuestionBoxGalleryObj::QuestionBoxGalleryObjNrvOnStart::sInstance);
}

void QuestionBoxGalleryObj::startSwitchOff() {
    MR::startSound(this, "SE_OJ_Q_BOX_LIGHT_OFF", -1, -1);
    setNerve(&NrvQuestionBoxGalleryObj::QuestionBoxGalleryObjNrvOffStart::sInstance);
}