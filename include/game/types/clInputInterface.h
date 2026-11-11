#ifndef GAME_TYPES_CLINPUTINTERFACE_H
#define GAME_TYPES_CLINPUTINTERFACE_H
class clInputInterface {
public:
    virtual ~clInputInterface();
    virtual int Update();
    virtual float GetValue0();
    virtual float GetDefaultFloat();
    virtual float GetValue1();
    virtual float GetValue2();
    virtual int GetState0();
    virtual int GetState1();
    virtual int GetState2();
    virtual int GetState3();
    virtual void Clear();
    clInputInterface();
};
#endif
