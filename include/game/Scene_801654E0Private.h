#ifndef GAME_SCENE_801654E0_PRIVATE_H
#define GAME_SCENE_801654E0_PRIVATE_H
#include "game/types/size_t.h"

void *operator new(size_t);
void operator delete(void *) throw();
extern "C" {
void fn_80121210();
void fn_80252D6C();
void fn_8013DBF8();
void *FUN_8003b120(unsigned long);
extern char g_playerData[];
extern int g_characterId, g_ccClass;
extern const float lbl_806D8918;
void TaRecord_InsertResult(void *, int, int, int, int, float);
unsigned char fn_801D5C88(void *, int);
void SetCourseParams(unsigned int, int, int, int);
}
struct DebugPair163 {
    int a, b;
};
struct DebugEntry163 {
    DebugPair163 first;
    int c;
    DebugPair163 second;
    int f;
    float g;
};
extern "C" DebugEntry163 *fn_8013BE98(int);

struct SceneRoot163 {
    virtual ~SceneRoot163();
    unsigned char done;
    unsigned char pad5[3]; /* tail padding, named so a derived class cannot use it */
    SceneRoot163() { done = 0; }
};
struct PanelRoot163 {
    virtual ~PanelRoot163();
    int a, b, done;
    PanelRoot163() { a = 0; b = 0; done = 0; }
};
struct Panel163 : PanelRoot163 {
    Panel163() {}
    virtual ~Panel163();
};
struct DebugTitle163 : Panel163 {
    unsigned char quit;
    int text, title, variant;
    DebugTitle163() { quit = 0; text = 0; title = 0x32e; variant = 0; fn_80121210(); }
    virtual ~DebugTitle163();
};
struct DebugName163 : Panel163 {
    int a10, a14, a18, a1c, a20, a24, a28;
    DebugName163() {
        a10 = 0; a14 = 0; a18 = 0; a1c = 0; a20 = 0; a24 = 0; a28 = 0;
        fn_80121210();
        fn_80252D6C();
    }
    virtual ~DebugName163();
};
struct DebugTable163 : Panel163 {
    unsigned char active;
    int text, page, a1c, a20, a24, a28;
    DebugEntry163 *entries;
    DebugTable163() {
        fn_8013DBF8();
        active = 0; text = 0; page = 1; a1c = 0;
        entries = (DebugEntry163 *)FUN_8003b120(0x1e4c);
        a24 = 0; a28 = 0;
        for (int i = 0; i < 277; i++) entries[i] = *fn_8013BE98(i);
    }
    virtual ~DebugTable163();
};
struct DebugOther163 : Panel163 {
    unsigned char quit;
    int a14, a18, a1c, a20;
    DebugOther163() { quit = 0; a14 = 0; a18 = 0; a1c = 0; a20 = 0; fn_80121210(); }
    virtual ~DebugOther163();
};
struct ModelPrefix163 { char pad0[0x14]; };
struct DebugModel163 : ModelPrefix163 {
    virtual ~DebugModel163();
    virtual void Start();
};
struct DebugPayloadA163 { char bytes[0x44]; DebugPayloadA163(); };
struct DebugPayloadB163 { char bytes[0x84]; DebugPayloadB163(int); };
struct DebugPayloadC163 { char bytes[0x48]; DebugPayloadC163(); };
struct DebugPayloadD163 { char bytes[0xd0]; DebugPayloadD163(int, int, int); };
struct DebugModelPage163 : Panel163 {
    int type;
    DebugModel163 *model;
    DebugModelPage163(int t) {
        type = t; model = 0;
        switch (t) {
        case 0: model = (DebugModel163 *)new DebugPayloadA163; break;
        case 1: model = (DebugModel163 *)new DebugPayloadB163(0); break;
        case 2: model = (DebugModel163 *)new DebugPayloadC163; break;
        case 3:
            model = (DebugModel163 *)new DebugPayloadD163(1, 0, 0);
            model->Start();
            break;
        }
        if (!model) done = 1;
    }
    virtual ~DebugModelPage163();
};
struct DebugFirst163 { char bytes[0x78]; DebugFirst163(int, int); };
struct DebugRecord163 { char bytes[0x7c]; DebugRecord163(int, int); };
struct DebugCup163 { char bytes[0xa0]; DebugCup163(int, int, int, int); };
struct Obj801654E0 : SceneRoot163 {
    unsigned char active;
    unsigned int kind;
    void *panel;
    Obj801654E0(unsigned int, unsigned int);
    virtual ~Obj801654E0();
};
#endif
