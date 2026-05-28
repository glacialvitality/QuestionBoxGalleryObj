#include "QuestionBoxGalleryObj.h"

/*
tryStageEffectStart__Q22MR11StageEffectFP9LiveActorPCc=0x80310960
tryStageEffectMoving__Q22MR11StageEffectFP9LiveActorPCc=0x803109D0
tryStageEffectStop__Q22MR11StageEffectFP9LiveActorPCc=0x80310B70
*/

extern "C" {
    StageEffect* __kAutoMap_80310960(LiveActor*, const char*); //tryStageEffectStart__Q22MR11StageEffectFP9LiveActorPCc=0x80310960

    
    StageEffect* __kAutoMap_803109D0(LiveActor*, const char*); //tryStageEffectMoving__Q22MR11StageEffectFP9LiveActorPCc=0x803109D0

    
    StageEffect* __kAutoMap_80310B70(LiveActor*, const char*); //tryStageEffectStop__Q22MR11StageEffectFP9LiveActorPCc=0x80310B70

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

    if (mRotator && mRotator->isMoving()) {
        MR::startLevelSound(this, "SE_OJ_LV_Q_BOX_ROTATE", -1, -1, -1);
        __kAutoMap_803109D0(this,  mObjName); //MR::StageEffect::tryStageEffectMoving(this, mObjName);
        
    }

    if (mRailMover) {

        //TODO: see if I can be faithful to G1 code without implementing a hacky solution.
        if (MR::isFirstStep(this)) {
            MapObjActorUtil::startRailMover(this);
            if (mRailMover->isWorking()) {
                MR::startLevelSound(this, "SE_OJ_LV_ABEKOBE_LIFT_MV", -1, -1, -1);
                __kAutoMap_803109D0(this, mObjName); //MR::StageEffect::tryStageEffectMoving(this, mObjName);
            }

            if (mRailMover->isReachedEnd()) { //MapObjActorUtil::isRailMoverReachedEnd(this)
                MR::startLevelSound(this, "SE_OJ_LV_ABEKOBE_LIFT_ED", -1, -1, -1);
                __kAutoMap_80310B70(this, mObjName); //MR::StageEffect::tryStageEffectStop(this, mObjName);
            }
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