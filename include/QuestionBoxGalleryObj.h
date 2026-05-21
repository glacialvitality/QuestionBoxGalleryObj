#pragma once
#include "Syati.h"

#include "Game/MapObj/MapObjActor.h"

/*
extern "C" {
    //isRailMoverReachedEnd__15MapObjActorUtilFPC11MapObjActor=0x801F7F3C
    MapObjActor* __kAutoMap_801F7F3C();
};
*/
class StageEffect;
class QuestionBoxGalleryObj : public MapObjActor {
public:
    QuestionBoxGalleryObj(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void control();
    virtual void initCaseUseSwitchA(const MapObjActorInitInfo&);
    virtual void initCaseUseSwitchB(const MapObjActorInitInfo&);

    void startSwitchOn();
    void startSwitchOff();

    void exeOnWait();
    void exeOnStart();
    void exeOffWait();
    void exeOffStart();

};

namespace MapObjActorUtil {
    bool isRailMoverReachedEnd(const MapObjActor *);
};