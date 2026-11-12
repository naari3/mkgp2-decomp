#ifndef GAME_TYPES_CLKPCHARADATA_H
#define GAME_TYPES_CLKPCHARADATA_H
#include "game/types/CoursePropData.h"

class clKPCharaData {
public:
    clKPCharaData *next;
    int reserved;
    CoursePropData *data;
    float frame;
    virtual void Update();
    clKPCharaData(CoursePropData *d) : next(0), reserved(0), data(d), frame(0.0f) {}
    ~clKPCharaData();
};
class clKPCharaData_MKoopa : public clKPCharaData {
public:
    virtual void Update();
    clKPCharaData_MKoopa(CoursePropData *d) : clKPCharaData(d) {}
};
class clKPCharaData_NokoPata : public clKPCharaData {
public:
    virtual void Update();
    clKPCharaData_NokoPata(CoursePropData *d) : clKPCharaData(d) {}
};
#endif
