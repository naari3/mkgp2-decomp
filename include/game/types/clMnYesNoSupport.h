#ifndef GAME_CLMNYESNO_SUPPORT_H
#define GAME_CLMNYESNO_SUPPORT_H
#include "game/types/size_t.h"



void *operator new(size_t size);
void operator delete(void *p) throw();
void *operator new[](size_t size);
void operator delete[](void *p) throw();

#include "game/types/VObject.h"

#include "game/types/InputState.h"

extern "C" InputState *g_pInputState;

static inline InputState *GetInput() {
    return g_pInputState == 0 ? (InputState *)0 : g_pInputState;
}


template <class T> struct VHolder {
    T *p;
    VHolder() : p(0) {}
    VHolder(T *q) : p(q) {}
    ~VHolder() throw() { delete p; }
    void Reset(T *q) throw() {
        if (p != q) {
            delete p;
            p = q;
        }
    }
};

#include "game/types/clMnTaskInterface.h"

struct TextManager {
    char pad000[0x18];
    int visible;
    char pad01C[4];
    unsigned int color;
    char pad024[0x22C - 0x24];
    float scale;
    TextManager();
    ~TextManager();
};

extern "C" {
int isJapanese(void);
void TexMgr_SetTexture(TextManager *tm, const char *fmt, ...);
void fn_801F93EC(TextManager *tm, float x, float y);
void fn_801F8FCC(TextManager *tm, int mode);
void fn_801F8E90(TextManager *tm);
void CreditMgr_SetActiveSlot(int slot);
int CreditMgr_GetCoinCount(int slot, int mode);
}


struct ListNode {
    ListNode *prev;
    ListNode *next;
    clMnTaskInterface *task;
};

struct ListIter {
    ListNode *node;
    ListIter() {}
    ListIter(ListNode *n) : node(n) {}
    ListIter &operator=(const ListIter &o) {
        node = o.node;
        return *this;
    }
};


struct DoublyLinkedList {
    int count;
    ListNode *last;
    ListNode *first;
    DoublyLinkedList();
    ListIter Erase(ListIter it);
    ListNode *End() { return (ListNode *)&last; }
};

struct FlowSceneList {
    virtual ~FlowSceneList();
    virtual void Update();
    virtual void Draw();
    DoublyLinkedList entries;
    FlowSceneList() {}
};

struct SceneListImpl : FlowSceneList {
    SceneListImpl() {}
#ifdef SCENELISTIMPL_EXTERNAL_VTABLE
    virtual void _key2();
#endif
    virtual void Update();
    virtual void Draw();
#ifndef SCENELISTIMPL_EXTERNAL_VTABLE
    virtual void _key2();
#endif
    void Sort();
    void Kill(unsigned int id);
    ListIter Remove(ListIter it) { return entries.Erase(it); }
};

extern "C" {
clMnTaskInterface *fn_801F4DC0(FlowSceneList *list, int id);
void fn_801F4DF0(FlowSceneList *list, clMnTaskInterface *task, int mode);
void fn_801F4D3C(FlowSceneList *list);
}


struct FlowFader {
    virtual ~FlowFader();
    short a;
    short b;
    FlowFader() : a(0), b(0) {}
    void Step() {
        b++;
        short lim = a;
        if (b >= lim) {
            b = lim;
        }
    }
    bool Done() { return b >= a; }
};

extern "C" const float lbl_806DA880;


struct FlowFaderF : FlowFader {
    float x;
    float y;
    float z;
    FlowFaderF(float v) : x(v), y(v), z(v) {}
#ifdef GAME_FLOWFADERF_DEFAULT_CTOR_OUT_OF_LINE
    FlowFaderF();
#else
    FlowFaderF() : x(lbl_806DA880), y(lbl_806DA880), z(lbl_806DA880) {}
#endif
    virtual void _key2();
    float Value();                       
    void Set(float from, float to, short dur); 
};

struct FlowFaderI : FlowFader {
    int x;
    int y;
    int z;
#ifdef GAME_FLOWFADERI_CTOR_OUT_OF_LINE
    FlowFaderI();                        
#else
    FlowFaderI() : x(0), y(0), z(0) {}
#endif
    virtual void _key2();
    int Value();                         
    void Set(int from, int to, short dur); 
};

struct ResCtrl {
    int resId;
    int field4, mode, fieldc;
    unsigned char flag, pad11[3];
    float x, y, z, width, height, field28, scaleX, scaleY;
    unsigned int colors[4];
    bool flipX;
    bool flipY;
    char pad46[2];
    int tail[4];
    ResCtrl();
    ~ResCtrl() {}
    void Show(float px, float py, float pz) {
        flag = 1;
        x = px;
        y = py;
        z = pz;
    }
    void SetScale(float s) {
        scaleX = s;
        scaleY = s;
    }
    void SetScaleXY(float sx, float sy) {
        scaleX = sx;
        scaleY = sy;
    }
    void SetSize(float w, float h) {
        width = w;
        height = h;
    }
    void SetColor(unsigned int c) {
        colors[0] = c;
        colors[1] = c;
        colors[2] = c;
        colors[3] = c;
    }
    void SetPos(float px, float py, float pz) {
        x = px;
        y = py;
        z = pz;
    }
};

#endif
