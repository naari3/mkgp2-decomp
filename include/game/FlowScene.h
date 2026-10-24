#ifndef GAME_FLOWSCENE_H
#define GAME_FLOWSCENE_H

/*
 * Card / continue / result flow scene hierarchy (0x801FC1E0..0x80207324).
 *
 *   FlowRoot (vtable lbl_8048ECF8, inline dtor)
 *     FlowTask (ctor fn_80204448, dtor dtor_802043EC, vtable lbl_804EC424)
 *       FlowScene (ctor fn_801FD41C, dtor dtor_801FD32C, vtable lbl_804EC098)
 *
 * Every class carries an undefined `_key` virtual so CW never emits the
 * vtables here; the vptr stores resolve to the real lbl_* tables through
 * tools/extab_user_renames.json.
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();
void *operator new[](unsigned long size);
void operator delete[](void *p) throw();

struct VObject {
    virtual ~VObject();
};

struct InputState {
    char pad00[4];
    unsigned char enabled;
    char pad05[0x13];
    int held;
    int edge;
};

extern "C" InputState *g_pInputState;

static inline InputState *GetInput() {
    return g_pInputState == 0 ? (InputState *)0 : g_pInputState;
}

/* Owning pointer whose dtor deletes through the virtual dtor. */
template <class T> struct VHolder {
    T *p;
    VHolder(T *q) : p(q) {}
    ~VHolder() throw() { delete p; }
};

struct FlowRoot {
    virtual void _key();
    ~FlowRoot() {}
};

struct FlowTask : FlowRoot {
    int id;
    int field08;
    int field0C;
    FlowTask(int id);
    ~FlowTask();
    virtual void _key2();
};

/* 0x230-byte text manager (ctor fn_80149214, dtor dtor_800869D0). */
struct TextManager {
    char pad000[0x18];
    int visible;
    char pad01C[0x22C - 0x1C];
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

/* Scene list owned by FlowScene+0x10 (dtor dtor_801F4B10). */
struct DoublyLinkedList {
    void *head;
    void *tail;
    void *cur;
    DoublyLinkedList();
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
    virtual void _key2();
};

extern "C" {
FlowTask *fn_801F4DC0(FlowSceneList *list, int id);
void fn_801F4DF0(FlowSceneList *list, FlowTask *task, int mode);
void fn_801F4D3C(FlowSceneList *list);
}

/* Fade helper owned by FlowScene+0x14 (dtor dtor_801F2724). */
struct FlowFader {
    virtual ~FlowFader();
    short a;
    short b;
    FlowFader() : a(0), b(0) {}
    void Step() {
        b++;
        if (b >= a) {
            b = a;
        }
    }
    bool Done() { return b >= a; }
};

/* Fade helper variant with three floats (vtable lbl_80419DE0). */
struct FlowFaderF : FlowFader {
    float x;
    float y;
    float z;
    FlowFaderF(float v) : x(v), y(v), z(v) {}
    virtual void _key2();
};

struct FlowFaderI : FlowFader {
    int x;
    int y;
    int z;
    FlowFaderI() : x(0), y(0), z(0) {}
    virtual void _key2();
};

struct FlowScene : FlowTask {
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> fader;
    int state;
    int subState;
    int timer;
    int cursor;
    FlowScene(int id);
    ~FlowScene();
    virtual void _key3();
};

struct ResCtrl {
    int resId;
    int field4, mode, fieldc;
    unsigned char flag, pad11[3];
    float x, y, z, width, height, field28, scaleX, scaleY;
    unsigned int colors[4];
    int tail[5];
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
