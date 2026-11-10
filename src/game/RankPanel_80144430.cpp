#include "game/singleton.h"

/* sdata symbols referenced from asm */
extern unsigned char lbl_806D7B0C[1];
/*
 * 0x80144430..0x80146160: time attack ranking panel and its entry vector.
 */
#pragma cplusplus on

extern "C" void MemoryManager_TimedFree(void *p);
extern "C" void Sprite_Destroy(void *s, int flag);

struct SpriteObj {
    char pad0[4];
    int mode;
    char pad8[4];
    float fC, f10, f14, f18, f1C, f20;
};
struct Tween {
    unsigned char on;
    char pad1[3];
    float from, to, speed, t, value;
    Tween();
    float Get() { return value; }
    void Start(float a, float b, float s) {
        from = a;
        to = b;
        speed = s;
        t = 0.0f;
        value = a;
        on = 1;
    }
    void Update() {
        if (on == 1) {
            value = from * (1.0f - t) + to * t;
            t += speed;
            if (t > 1.0f) {
                t = 1.0f;
            }
        }
    }
};
class PanelItem {
public:
    PanelItem(SpriteObj *s, int d) : sprite(s), delay(d) {
        active = 0;
        flag85 = 0;
        for (int i = 0; i < 5; i++)
            tw[i].on = 0;
    }
    virtual ~PanelItem();
    virtual void Update();
    virtual void Draw();
    SpriteObj *sprite;
    int delay;
    Tween tw[5];
    unsigned char active;
    unsigned char flag85;
};

/* resource label (vtable lbl_8048EF20) */
class PanelIcon : public PanelItem {
public:
    PanelIcon(float x, float y, short id, int layer_, int delay = 0, unsigned char flip_ = 0)
        : PanelItem(0, delay), resId(id), layer(layer_), flip(flip_) {
        tw[3].Start(x, x, 1.0f);
        tw[4].Start(y, y, 1.0f);
    }
    virtual ~PanelIcon();
    short resId;
    char pad8A[2];
    int layer;
    unsigned char flip;
};
struct PanelEntry {
    char pad0[0xc];
    unsigned char on;
    char padD[3];
    float f10, f14, f18, f1c, f20;
};
struct PtrVecStorage {
    int cap;
    int size;
    PanelItem **data;
    ~PtrVecStorage() { if (data) MemoryManager_TimedFree(data); }
};
struct PtrVecBase : PtrVecStorage {
    ~PtrVecBase() {}
};
struct EntryVec : PtrVecBase {
    ~EntryVec() {}
    PanelItem **begin() { return data; }
    PanelItem **end() { return data + size; }
    void push_back(PanelItem *const &x);
};
struct Cursor {
    SpriteObj *sprite;
    unsigned char on;
    unsigned char state;
    char pad6[2];
    int timer;
};
struct CursorPtr {
    Cursor *p;
    Cursor *operator->() { return p; }
    ~CursorPtr() throw() {
        Cursor *c = p;
        if (c) {
            Sprite_Destroy(c->sprite, 1);
            MemoryManager_TimedFree(c);
        }
    }
};
struct RankPanel {
    char pad0[0x14];
    void **vt14;
    unsigned char visible;
    char pad19[3];
    float f1c;
    int state;
    unsigned char b24;
    char pad25[3];
    float xs[0x26];
    EntryVec vec;
    CursorPtr cursor;
};
struct Pair { char pad[0xc]; float a, b; };
struct SpriteHolder { void **vt; void *sprite; };
struct VecHolder { int pad0; int pad4; void *data; };

/* TOP-END */

extern "C" {
void fn_8011FAB8(void);
void fn_801A0004(void *s);
extern unsigned char IsCardValid(void);
extern void Sprite_AdvanceAnim(SpriteObj *s, float dt);
extern void fn_801699D8(int a, int b);
extern int g_reverseRoundFlag;
extern const float lbl_806D7AE0;
extern const float lbl_806D7AE4;
extern unsigned int lbl_806D7AE8;
extern unsigned int lbl_806D7AEC;
extern const float lbl_806D7AF0;
extern unsigned int lbl_806D7AF4;
extern const float lbl_806D7AF8;
extern unsigned int lbl_806D7B00;
extern const float RankPanel_80144430_rodata_80361DCC[2][3];
extern const float lbl_806D7B08;
void MemoryManager_TimedFree(void *p);
void Sprite_Destroy(void *s, int flag);
extern void __unexpected();
extern unsigned int lbl_8048EB44[];
extern unsigned int clCSPartsResultRecord_vtable_8048EEF4[];
extern void Alloc();
extern void Sprite_InitWithAnim();
extern void __construct_array();
extern int g_cupId;
extern int g_longRoundFlag;
extern void *lbl_806D10A0;
extern const float lbl_806D7B10;
extern const float lbl_806D7B14;
extern const float lbl_806D7B18;
extern const float lbl_806D7B1C;
extern const float lbl_806D7B20;
extern const float lbl_806D7B24;
extern const float lbl_806D7B28;
extern const float lbl_806D7B2C;
extern const float lbl_806D7B30;
extern const float lbl_806D7B34;
extern const float lbl_806D7B38;
extern const float lbl_806D7B3C;
extern const short RankPanel_80144430_rodata_80361D60[][2];
extern void *lbl_8048EF20[];
extern void *lbl_8048EF34[];
extern void ResCtrl_Init();
void fn_8011FAFC(struct ResCtrl *ctrl, int layer);
extern const float lbl_806D7B4C;
extern void dtor_80082960();
void *FUN_8003b120(unsigned long n);
void SharedPtr_Init(void *sp, void *p);
extern unsigned int lbl_803F5700[];
extern unsigned int lbl_803F5710[];
extern unsigned int lbl_8048EF68[];
extern void dtor_80038DD4();
extern void dtor_80038E30(struct ExcString *s, int flag);
void fn_80144430(RankPanel *self);
void fn_80144500(RankPanel *self);
void fn_801449D4(RankPanel *self);
void fn_80144ADC(RankPanel *self);
RankPanel *fn_80144AF0(RankPanel *self, short flag);
void fn_80144C1C(RankPanel *self);
void fn_801458A4(Pair *p);
SpriteHolder *fn_80145D34(SpriteHolder *self, short flag);
void fn_80145DA8(void);
void fn_80145DAC(void);
SpriteHolder *dtor_80145DB0(SpriteHolder *self, short flag);
void fn_80145E14(struct PanelIcon *self);
struct SpriteBoxPtr *dtor_80145F04(struct SpriteBoxPtr *self, short flag) throw();
VecHolder *dtor_80145F9C(VecHolder *self, short flag);
struct PanelEntry **fn_80146000(struct EntryVec *v, unsigned long id);
struct ExcObj *fn_801460D0(struct ExcObj *self, short flag);














}

/* C++ view of the record panel for its constructors (fn_801458B4, fn_80145AF4). */
void *operator new(unsigned long size);
void operator delete(void *p);

struct Sprite {
    char pad0[0xc];
    float x, y;
    char pad14[0x1c];
    Sprite(int id, int a, int b);
    Sprite(int id, int a, float x, float y, float sx, float sy, float r, float rot);
    ~Sprite();
};
extern "C" {
extern const float lbl_806D7B40;
extern const float lbl_806D7B44;
extern const short RankPanel_80144430_rodata_80361D80[];
void fn_8019FF8C(Sprite *s, int id, struct SpriteNodeInfo *out);
int isJapanese(void);
}

/* .rodata 0x80361D60..0x80361ED0 is owned by this TU. */
extern "C" {
extern const short RankPanel_80144430_rodata_80361D60[8][2] = {
    {0x1AB6, 0x1AB7}, {0x1ABA, 0x1ABB}, {0x1AC4, 0x1AC5}, {0x1AC6, 0x1AC7},
    {0x1AC8, 0x1AC9}, {0x1ACA, 0x1ACB}, {0x1AB4, 0x1AB5}, {0x1AB8, 0x1AB9},
};
extern const short RankPanel_80144430_rodata_80361D80[0x26] = {
    0x1CDE, 0x1D23, 0x2467, 0x2469, 0x246B, 0x246D, 0x246F,
    0x1F4D, 0x1F4F, 0x1F51, 0x1F53, 0x1F55, 0x1F57, 0x1F59, 0x1F5B, 0x1F5D, 0x1F5F, 0x1F61,
    0x1F4D, 0x1F4F, 0x1F51, 0x1F53, 0x1F55, 0x1F57, 0x1F59, 0x1F5B, 0x1F5D, 0x1F5F, 0x1F61,
    0x1CE8, 0x1CE9, 0x1CEA, 0x1CF3, 0x1CEB, 0x1CEC, 0x1CF2, 0x1CED, 0x1CEE,
};
extern const float RankPanel_80144430_rodata_80361DCC[2][3] = {
    {960.0f, 320.0f, -320.0f},
    {1180.0f, 410.0f, -360.0f},
};
extern const char lbl_80361DE4[0x14] = "clCSPartsTARanking";
extern const char lbl_80361DF8[0x14] = "clCSPartsInerface";
extern const char lbl_80361E0C[0x1C] = "nsMenuUtil::clSpriteNode";
extern const char lbl_80361E28[0x18] = "nsMenuUtil::clMenuNode";
}
#include "game/types/SpriteNodeInfo.h"
struct RecCursor {
    Sprite *sprite;
    unsigned char on;
    unsigned char state;
    int timer;
    RecCursor() {
        on = 0;
        state = 0;
        timer = 0;
        sprite = new Sprite(0x9e, 1, 394.0f, 394.0f, 1.0f, 1.0f, 0.0f, 0.0f);
    }
};
struct RecCursorPtr {
    RecCursor *p;
    RecCursorPtr(RecCursor *c) : p(c) {}
    ~RecCursorPtr() throw();
};
struct RecVec {
    int cap;
    int size;
    void **data;
    RecVec() : cap(0), size(0), data(0) {}
    ~RecVec();
};
struct clCSPartsInerface {
    int obj;
    unsigned char active;
    float x, y;
    float alpha;
    clCSPartsInerface() {
        obj = 0;
        active = 0;
        x = lbl_806D7AE4;
        y = lbl_806D7AE4;
        alpha = lbl_806D7AF0;
    }
    virtual ~clCSPartsInerface();
    virtual void m0C();
    virtual void m10();
    virtual void Update();
    virtual void Draw();
    virtual void m1C();
};
struct clCSPartsResultRecord : clCSPartsInerface {
    unsigned char visible;
    float f1c;
    int state;
    unsigned char b24;
    float xs[0x26];
    RecVec vec;
    RecCursorPtr cursor;
    virtual ~clCSPartsResultRecord();
    clCSPartsResultRecord();
    clCSPartsResultRecord(int a, int b, int c);
    void LoadColumns(Sprite *s) {
        for (int i = 0; i < 0x26; i++) {
            SpriteNodeInfo info;
            fn_8019FF8C(s, RankPanel_80144430_rodata_80361D80[i], &info);
            xs[i] = info.x;
        }
    }
};

static inline void DrawItem(PanelItem *p)
{
    if (p->active) {
        if (p->sprite) {
            fn_801A0004(p->sprite);
        }
        p->Draw();
        if (p->flag85 == 1) {
            fn_8011FAB8();
        }
    }
}
static inline void SetEntry(PanelEntry *e, float y)
{
    e->f10 = lbl_806D7AF0;
    e->f14 = lbl_806D7AE4;
    e->f18 = y;
    e->f1c = lbl_806D7AE4;
    e->f20 = lbl_806D7AF0;
    e->on = 1;
}



extern "C" void fn_80144430(RankPanel *self)
{
    if (self->state != 0 && self->visible) {
        for (PanelItem **it = self->vec.data; it != self->vec.data + self->vec.size; it++) {
            DrawItem(*it);
        }
        if (self->cursor->on) {
            fn_801A0004(self->cursor->sprite);
        }
    }
}

#define RP_F(x) (*(float *)&(x))
static inline void PanelItem_Tick(PanelItem *p)
{
    if (p->delay > 0) {
        p->delay--;
        return;
    }
    if (p->delay <= 0) {
        p->active = 1;
    }
    for (int i = 0; i < 5; i++) {
        p->tw[i].Update();
    }
    p->Update();
    if (p->sprite) {
        if (p->tw[0].on == 1) p->sprite->f20 = p->tw[0].Get();
        if (p->tw[1].on == 1) p->sprite->f14 = p->tw[1].Get();
        if (p->tw[2].on == 1) p->sprite->f18 = p->tw[2].Get();
        if (p->tw[3].on == 1) p->sprite->fC = p->tw[3].Get();
        if (p->tw[4].on == 1) p->sprite->f10 = p->tw[4].Get();
        Sprite_AdvanceAnim(p->sprite, RP_F(lbl_806D7AF4));
    }
}

extern "C" void fn_80144500(RankPanel *self)
{
    if (self->state != 0 && self->visible) {
        int row = IsCardValid() == 1 ? 0 : 1;
        switch (self->state) {
        case 1:
            for (int i = 0; i < 10; i++) {
                if ((int)self->f1c == i * 2) {
                    int off = i * 0x26;
                    for (int k = 0; k < 0x26; k++) {
                        ((PanelItem *)*fn_80146000(&self->vec, off + k))->tw[3].Start(self->xs[k] + RankPanel_80144430_rodata_80361DCC[row][0], self->xs[k] + RankPanel_80144430_rodata_80361DCC[row][1], lbl_806D7AE0);
                    }
                    break;
                }
            }
            if (self->f1c >= RP_F(lbl_806D7AE8)) {
                self->f1c = 0.0f;
                self->state = 2;
                if (g_reverseRoundFlag == 1) {
                    Cursor *c = self->cursor.p;
                    if (c->on != 1 || c->state != 0) {
                        c->on = 1;
                        c->state = 0;
                        c->timer = 0;
                    }
                }
            }
            break;
        case 3:
            fn_801699D8(0, 0);
            for (int i = 0; i < 10; i++) {
                if ((int)self->f1c == i * 2) {
                    int off = i * 0x26;
                    for (int k = 0; k < 0x26; k++) {
                        ((PanelItem *)*fn_80146000(&self->vec, off + k))->tw[3].Start(self->xs[k] + RankPanel_80144430_rodata_80361DCC[row][1], self->xs[k] + RankPanel_80144430_rodata_80361DCC[row][2], lbl_806D7AE0);
                    }
                    break;
                }
            }
            if (self->f1c >= RP_F(lbl_806D7AEC)) {
                self->f1c = 0.0f;
                self->state = 0;
                self->b24 = 1;
            }
            break;
        }
        self->f1c += 1.0f;
        for (PanelItem **it = self->vec.data; it != self->vec.data + self->vec.size; it++) {
            PanelItem_Tick(*it);
        }
        Cursor *c = self->cursor.p;
        if (c->on) {
            if (c->timer <= 8) {
                float a;
                if (c->state == 0) {
                    a = (float)c->timer * lbl_806D7AF8;
                } else {
                    a = 1.0f - (float)c->timer * lbl_806D7AF8;
                }
                c->sprite->f20 = a;
                if (c->timer++ == 8 && c->state != 0) {
                    c->on = 0;
                    c->state = 0;
                }
            }
            Sprite_AdvanceAnim(c->sprite, RP_F(lbl_806D7AF4));
        }
    }
}

extern "C" void fn_801449D4(RankPanel *self)
{
    self->state = 3;
    self->f1c = lbl_806D7AE4;
    PanelEntry *e;
    e = *fn_80146000(&self->vec, 0x17d);
    e->f10 = lbl_806D7AF0; e->f14 = lbl_806D7AE4; e->f18 = lbl_806D7AF8; e->f1c = lbl_806D7AE4; e->f20 = lbl_806D7AF0; e->on = 1;
    e = *fn_80146000(&self->vec, 0x17e);
    e->f10 = lbl_806D7AF0; e->f14 = lbl_806D7AE4; e->f18 = lbl_806D7B08; e->f1c = lbl_806D7AE4; e->f20 = lbl_806D7AF0; e->on = 1;
    e = *fn_80146000(&self->vec, 0x17f);
    e->f10 = lbl_806D7AF0; e->f14 = lbl_806D7AE4; e->f18 = lbl_806D7B08; e->f1c = lbl_806D7AE4; e->f20 = lbl_806D7AF0; e->on = 1;
    Cursor *c = self->cursor.p;
    if (c->on && c->state != 1) {
        c->state = 1;
        c->timer = 0;
    }
}

extern "C" void fn_80144ADC(RankPanel *self)
{
    self->state = 1;
    self->f1c = lbl_806D7AE4;
}

extern "C" RankPanel *fn_80144AF0(RankPanel *self, short flag)
{
    if (self) {
        self->vt14 = (void **)clCSPartsResultRecord_vtable_8048EEF4;
        for (PanelItem **it = self->vec.begin(); it != self->vec.end(); it++) {
            delete *it;
        }
        self->cursor.~CursorPtr();
        self->vec.~EntryVec();
        if (self) self->vt14 = (void **)lbl_8048EB44;
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

extern "C" void PtrVec_InsertFill(EntryVec *v, PanelItem **pos, int n, PanelItem *const *val);
inline void EntryVec::push_back(PanelItem *const &x) { PtrVec_InsertFill(this, end(), 1, &x); }

/* time attack record row (TaRecord_GetEntry_Current) */
#include "game/types/TaEntry.h"

extern "C" {
int TaRecord_GetLastInsertedRank(void);
float TaRecord_GetTime_Current(int row);
TaEntry *TaRecord_GetEntry_Current(int row);
int fn_8013BFCC(int chara);
int fn_801F96D0(unsigned short part);
int fn_801F9628(unsigned short ch);
int fn_80167744(int digit, float time);
void PreloadResource(int res);
const char *get_title_name(void *mgr, int a, int b, int chara, int c);
void *memcpy(void *dst, const void *src, unsigned long n);
float fn_801D8D3C(int cup, int longRound);
void fn_8019FF6C(Sprite *s, int a);
}

extern "C" void fn_80144C1C(RankPanel *self)
{
    float time;
    TaEntry *entry;
    int res;
    const char *title;
    int row;
    float y;
    int rank;
    void *mgr;

    if (self->visible == 1)
        return;
    self->visible = 1;
    title = (const char *)lbl_806D7B0C;
    PanelItem *item = 0;
    mgr = SINGLETON_INSTANCE(lbl_806D10A0);
    rank = TaRecord_GetLastInsertedRank();
    y = lbl_806D7B10;
    for (row = 0; row < 10; row++) {
        time = TaRecord_GetTime_Current(row);
        entry = TaRecord_GetEntry_Current(row);
        self->vec.push_back(new PanelIcon(lbl_806D7B14 + self->xs[0], y, 0x1cde + row, 7));
        self->vec.push_back(new PanelIcon(lbl_806D7B14 + self->xs[1], y, fn_8013BFCC(entry->chara), 7));
        for (int part = 0; part < 5; part++) {
            res = fn_801F96D0(entry->parts[part]);
            self->vec.push_back(new PanelIcon(lbl_806D7B14 + self->xs[2 + part], y, res, 7));
            PreloadResource(res);
        }
        if (mgr)
            title = get_title_name(mgr, entry->titleA, entry->titleB, entry->chara, entry->titleC);
        if (!IsCardValid())
            title = (const char *)lbl_806D7B0C;
        /* title: one label per character (2-byte SJIS or 1-byte ASCII), padded with blanks */
        int pos = 0;
        int n;
        for (n = 0; n < 0x16; n++) {
            const char *c = title + pos;
            unsigned short ch;
            int wide;
            if (*c == 0)
                break;
            memcpy(&ch, c, 2);
            wide = ch & 0x8000;
            if (wide)
                pos++;
            if (!wide)
                ch = *c;
            pos++;
            res = fn_801F9628(ch);
            self->vec.push_back(new PanelIcon(lbl_806D7B14 + self->xs[7 + n], y, res, 7));
            PreloadResource(res);
        }
        for (; n < 0x16; n++)
            self->vec.push_back(new PanelIcon(lbl_806D7B14 + self->xs[7 + n], y, 0x1ecd, 7));
        for (int d = 0; d < 9; d++) {
            int digit = fn_80167744(d, time);
            self->vec.push_back(new PanelIcon(lbl_806D7B14 + self->xs[0x1d + d], y, 0x1ce8 + digit, 7));
        }
        y += lbl_806D7B18;
    }

    item = new PanelIcon(lbl_806D7B1C, lbl_806D7B20, RankPanel_80144430_rodata_80361D60[g_cupId - 1][g_longRoundFlag], 5);
    item->tw[0].Start(0.0f, 1.0f, lbl_806D7AE0);
    self->vec.push_back(item);

    item = new PanelIcon(lbl_806D7B24, 36.0f * rank + 90.0f, 0x1cf4, 3, 0x23, 1);
    item->tw[0].Start(0.0f, 1.0f, lbl_806D7AF8);
    item->tw[1].Start(lbl_806D7B28, lbl_806D7B28, lbl_806D7B2C);
    self->vec.push_back(item);

    Sprite *sprite = new Sprite(0x74, 1, 0);
    sprite->x = lbl_806D7B30;
    sprite->y = lbl_806D7B34;
    fn_8019FF6C(sprite, 1);
    item = new PanelItem((SpriteObj *)sprite, 0x2d);
    item->tw[0].Start(0.0f, 1.0f, lbl_806D7B08);
    self->vec.push_back(item);

    item = new PanelIcon(lbl_806D7B38, lbl_806D7B3C, 0x1872, 7, 0x2d);
    item->tw[0].Start(0.0f, 1.0f, lbl_806D7B08);
    self->vec.push_back(item);

    self->cursor->sprite->mode = 6;
    float cursorX = fn_801D8D3C(g_cupId, g_longRoundFlag);
    self->cursor->sprite->fC = cursorX;
    self->cursor->sprite->f10 = lbl_806D7B20;
    fn_801699D8(0, 1);
}

extern "C" void fn_801458A4(Pair *p)
{
    p->a = lbl_806D7AE4;
    p->b = lbl_806D7AE4;
}

clCSPartsResultRecord::clCSPartsResultRecord() : visible(0), f1c(lbl_806D7AE4), state(0), b24(0), cursor(new RecCursor)
{
    Sprite *s = new Sprite(0x1c5, 0, 0);
    LoadColumns(s);
    if (isJapanese()) {
        float x = xs[7];
        for (int i = 0; i < 0x16; i++) {
            xs[7 + i] = x;
            x += lbl_806D7B40;
        }
    } else {
        xs[0x12] = lbl_806D7B44 + xs[0x11];
    }
    delete s;
}

clCSPartsResultRecord::clCSPartsResultRecord(int, int, int) : visible(0), f1c(lbl_806D7AE4), state(0), b24(0), cursor(new RecCursor)
{
    Sprite *s = new Sprite(0x1c5, 0, 0);
    LoadColumns(s);
    if (isJapanese()) {
        float x = xs[7];
        for (int i = 0; i < 0x16; i++) {
            xs[7 + i] = x;
            x += lbl_806D7B40;
        }
    } else {
        xs[0x12] = lbl_806D7B44 + xs[0x11];
    }
    delete s;
}

extern "C" SpriteHolder *fn_80145D34(SpriteHolder *self, short flag)
{
    if (self) {
        self->vt = lbl_8048EF20;
        if (self) {
            self->vt = lbl_8048EF34;
            Sprite_Destroy(self->sprite, 1);
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

extern "C" void fn_80145DA8(void) {}

extern "C" void fn_80145DAC(void) {}

extern "C" SpriteHolder *dtor_80145DB0(SpriteHolder *self, short flag)
{
    if (self) {
        self->vt = lbl_8048EF34;
        Sprite_Destroy(self->sprite, 1);
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

struct ResCtrl {
    int resId;
    int field4;
    int mode;
    int fieldc;
    unsigned char flag;
    char pad11[3];
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
    void SetColor(unsigned int c) {
        colors[0] = c;
        colors[1] = c;
        colors[2] = c;
        colors[3] = c;
    }
};

extern "C" void fn_80145E14(PanelIcon *self)
{
    ResCtrl rc;
    rc.resId = self->resId;
    rc.Show(self->tw[3].Get(), self->tw[4].Get(), 1.0f);
    if (self->tw[0].on == 1) {
        rc.SetColor(0xFFFFFF00 | ((int)(255.0f * self->tw[0].Get()) & 0xFF));
    }
    float sx = 1.0f;
    float sy = 1.0f;
    if (self->tw[1].on == 1) {
        sx = self->tw[1].Get();
    }
    if (self->tw[2].on == 1) {
        sy = self->tw[2].Get();
    }
    rc.scaleX = sx;
    rc.scaleY = sy;
    if (self->flip) {
        rc.tail[0] = 1;
        rc.tail[1] = 4;
        rc.tail[2] = 1;
    }
    fn_8011FAFC(&rc, self->layer);
}

#include "game/types/SpriteBox.h"
struct SpriteBoxPtr { SpriteBox *p; };

/* deleting destructor of a sprite owner pointer: ~SpriteBoxPtr() throw() { delete p; } */
extern "C" SpriteBoxPtr *dtor_80145F04(SpriteBoxPtr *self, short flag) throw()
{
    if (self) {
        SpriteBox *box = self->p;
        if (box) {
            Sprite_Destroy(box->sprite, 1);
            MemoryManager_TimedFree(box);
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

extern "C" VecHolder *dtor_80145F9C(VecHolder *self, short flag)
{
    if (self) {
        if (self) {
            if (self) {
                if (self->data) MemoryManager_TimedFree(self->data);
            }
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

extern "C" {
unsigned long strlen(const char *s);
char *strcpy(char *d, const char *s);
extern const char lbl_80361E40[0x20] = "vector::at index out of range";
}

struct ExcStrRef {
    char *ptr;
    unsigned long *refs;
    ExcStrRef(void *p) { SharedPtr_Init(this, p); }
    ~ExcStrRef();
};
struct ExcStr {
    ExcStrRef value;
    ExcStr(const char *s) : value(FUN_8003b120(strlen(s) + 1)) {
        strcpy(value.ptr, s);
    }
    ~ExcStr();
};
namespace std {
struct exception {
    exception() {}
    virtual ~exception();
};
struct logic_error : exception {
    ExcStr msg;
    logic_error(const char *s) : msg(s) {}
    virtual ~logic_error();
};
struct out_of_range : logic_error {
    out_of_range(const char *s) : logic_error(s) {}
    virtual ~out_of_range();
};

}
using namespace std;

#pragma push
#pragma readonly_strings on
extern "C" struct PanelEntry **fn_80146000(struct EntryVec *v, unsigned long id) {
    if (id >= v->size) {
        throw out_of_range(lbl_80361E40);
    }
    return (struct PanelEntry **)&v->data[id];
}
#pragma pop

extern "C" {
extern const char lbl_80361E98[0x14] = "std::out_of_range";
extern const char lbl_80361EAC[0x10] = "std::exception";
extern const char lbl_80361EBC[0x14] = "std::logic_error";
}

struct ExcString { char *p; };
struct ExcObj { void **vt; ExcString str; };

extern "C" ExcObj *fn_801460D0(ExcObj *self, short flag)
{
    if (self) {
        self->vt = (void **)lbl_8048EF68;
        if (self) {
            self->vt = (void **)lbl_803F5700;
            if (&self->str) dtor_80038E30(&self->str, -1);
            if (self) self->vt = (void **)lbl_803F5710;
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

