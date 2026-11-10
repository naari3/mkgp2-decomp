#ifndef SCENE_8015BF18_PRIVATE_H
#define SCENE_8015BF18_PRIVATE_H
#include "game/FlowScene.h"
#include "game/PlayerDataProgressPrivate.h"
struct ResultPart {
    virtual ~ResultPart();
    virtual void v0C(); virtual void v10(); virtual unsigned char v14();
};
struct ResultDialog : ResultPart { char data[0xe8-4]; ResultDialog(int); };
struct ResultParamsSprite {
    char data[0x30];
    ResultParamsSprite();
};
#include "game/types/SpriteHolder.h"
struct ResultInnerModel { char data[0x48]; ResultInnerModel(int); };
struct ResultEnvironment { char data[0x24]; ResultEnvironment(); };
struct ResultAward : ResultPart {
    virtual void key();
    int idx, timer, phase;
    unsigned char done; char pad11[3];
    ResCtrl resource;
    SpriteHolder sprite;
    ResultAward(int);
};
struct ResultIntro : ResultPart {
    virtual void key();
    int idx, sound; unsigned char soundStarted; char padd[3];
    int stage; float timer; unsigned char on; char pad19[3];
    ResultEnvironment *env; ResultInnerModel *model; void *sprite;
    ResCtrl inner,fade;
    ResultIntro(int);
};
struct ResultSequence {
    void *vtable;
    unsigned char done; char pad5[3]; int idx,state;
    ResultPart *part;
};
#endif
