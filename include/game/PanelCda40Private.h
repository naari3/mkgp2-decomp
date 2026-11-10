#ifndef GAME_PANEL_CDA40_PRIVATE_H
#define GAME_PANEL_CDA40_PRIVATE_H
#include "game/FlowScene.h"
extern "C" {
void Sprite_Destroy(void *, int);
void MemoryManager_TimedFree(void *);
extern void *lbl_8049B1AC[];
extern void *lbl_8048EF34[];
extern void *GpTextPanel_vtable_8049B18C[];
void fn_801D895C(void *, float);
void fn_801D878C(void *);
void fn_8011FAFC(ResCtrl *, int);
extern const float lbl_806D9E20, lbl_806D9E24, lbl_806D9E30, lbl_806D9E34;
extern const float lbl_806D9E78, lbl_806D9E7C, lbl_806D9E80;
}
struct CdaSpriteSlot {
    void *sprite;
    ~CdaSpriteSlot() throw() { Sprite_Destroy(sprite, 1); }
};
struct CdaOwnedSprite {
    int flags;
    CdaSpriteSlot slot;
};
struct CdaHolder {
    CdaOwnedSprite *p;
    ~CdaHolder() throw();
};
struct CdaSpriteBase {
    void *vt;
    void *sprite;
    char opaque08[0x80];
    ~CdaSpriteBase() { vt = lbl_8048EF34; Sprite_Destroy(sprite, 1); }
};
struct CdaSpriteDerived : CdaSpriteBase { ~CdaSpriteDerived(); };
struct CdaHolderDerived : CdaSpriteBase {
    CdaHolder holder;
    ~CdaHolderDerived();
};
struct CdaPanelView {
    char opaque00[0xC];
    float x,y;
    char opaque14[0xC];
    float scale;
    char opaque24[0x64];
    union { void *object; unsigned char rgb[4]; } payload;
    int layer;
};
struct CdaNode { CdaNode *prev,*next; void *obj; };
struct CdaIter {
    CdaNode *node;
    CdaIter(CdaNode *p):node(p) {}
    CdaIter &operator++(){node=node->next; return *this;}
};
struct CdaListImpl {
    int size; CdaNode head;
#ifdef PANEL_CDA40_DIRECT_BEGIN
    CdaIter begin(){return CdaIter(head.next);}
#else
    CdaIter begin(){return ++end();}
#endif
    CdaIter end(){return CdaIter(&head);}
    CdaIter EraseRange(const CdaIter &,const CdaIter &);
    ~CdaListImpl(){EraseRange(begin(),end());}
};
struct CdaListBase:CdaListImpl { ~CdaListBase(){} };
struct CdaList:CdaListBase { ~CdaList(); };
static inline unsigned int CdaColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    return (r<<24)|(g<<16)|(b<<8)|a;
}
#endif
