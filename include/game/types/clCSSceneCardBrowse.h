#ifndef GAME_TYPES_CLCSCENECARDBROWSE_H
#define GAME_TYPES_CLCSCENECARDBROWSE_H
#include "game/PlayerDataProgressPrivate.h"
#include "game/types/clSceneInterface.h"
struct SelectPanel { char prefix[0x1c]; float x,y; void SetPos(float a,float b) { x=a; y=b; } };
struct SelectBadge {
    int mode; int field4; float x,y; char tail[0x10];
    SelectBadge();
    void SetPos(float a,float b) { x=a; y=b; }
};
struct SelectPrompt { char data[0x20]; SelectPrompt(); };
struct SelectItem { char data[0x20]; SelectItem(int); };
struct SelectDriver { char data[0x90]; SelectDriver(int,int); };
struct clCSSceneCardBrowse : clSceneInterface {
    virtual ~clCSSceneCardBrowse();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    unsigned char active; char pad9[3];
    int state; float timer; int mode; int nextPage;
    unsigned char flag1c,flag1d; char pad1e[2];
    PlayerDataRecord *player;
    SelectDriver *driver; int resource;
    void *panel; SelectPanel *panel2;
    SelectBadge *badge; SelectPrompt *prompt; SelectItem *item,*extraItem;
    float f44; int character; unsigned char card; char pad4d[3];
    float f50,f54; unsigned char track; char pad59[3];
    float f5c; int count,first,kind; char pad6c[12];
    unsigned short valueA,valueB; signed char hundredsA,tensA; unsigned char onesA;
    signed char hundredsB,tensB; unsigned char onesB; char pad82[2];
    int index,other;
    float values[4]; char pad9c[8];
    int arrayA[4]; char padb4[8]; int arrayB[4]; char padcc[8];
    int arrayC[4]; char pade4[8]; int arrayD[4]; char padfc[8];
    void PrintPartsInterfaceName();
    clCSSceneCardBrowse();
};
#endif
