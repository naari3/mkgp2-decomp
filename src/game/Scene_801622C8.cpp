/* clCSSceneNextRace: deferred source order; vtable and RTTI emitted by MWCC. */

#include "game/Scene_8016234CPrivate.h"
#include "game/types/clSceneInterface.h"
#include "game/types/VObjPad.h"
struct Model : VObjPad {
    virtual ~Model();
    virtual void M1(); virtual void M2(); virtual void M3(); virtual void M4();
    virtual void Draw();
};
struct clCSSceneNextRace : clSceneInterface {
    virtual ~clCSSceneNextRace();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    CreditBase162 *panel;
    int padC;
    unsigned char active;
    unsigned char pad11[3];
    int phase;
    float timer;
    unsigned char service;
    unsigned char pad1D[3];
    int a, b, c, d, item;
    clCSSceneNextRace();
};
extern "C" {
void fn_8011F994(int); void HSD_StateInvalidate(int);
void fn_80121210(); void fn_80169C44();
void MemoryManager_TimedFree(void *);
}
extern "C" {
extern const float lbl_806D8894;
unsigned char ServiceEnable_Get(void);
unsigned char ServiceValue_Get(void);
int *fn_8024F588(void);
void *fn_801F98CC(void);
int fn_801F9868(void *p, int a, int b);
int fn_801F9844(void *p, int a, int b);
int fn_80209AC4(int a, int b);
void fn_801F9888(void);
void CreditMgr_SetActiveSlot(int slot);
void InitRumbleController(int on);
}

extern "C" clCSSceneNextRace *fn_80162C3C() { return new clCSSceneNextRace; }
inline clCSSceneNextRace::clCSSceneNextRace() {
    void *p;
    panel = 0;
    active = 0;
    phase = 0;
    timer = lbl_806D8894;
    service = 1;
    if (!ServiceEnable_Get() || ServiceValue_Get() == 1) service = 0;
    a = fn_8024F588()[1];
    b = fn_8024F588()[2];
    c = -1;
    d = -1;
    item = 0;
    p = fn_801F98CC();
    if (p != 0) {
        c = fn_801F9868(p, a, b);
        d = fn_801F9844(p, a, b);
        item = fn_80209AC4(a, b);
        if (item <= 0 || item >= 0x115) {
            item = 0;
        } else if (service == 0) {
            item = 0;
        }
        fn_801F9888();
    }
    CreditMgr_SetActiveSlot(1);
    InitRumbleController(1);
}
void clCSSceneNextRace::Destroy() { delete this; }
struct CreditHolder {
    char pad00[0x14];
    void *vtable;
};

extern "C" {
extern char CreditChild162_vtable_80490B34[];
void dtor_80147584(void *, int);
CreditHolder *fn_80162B98(CreditHolder *self, short flag) {
    if (self) {
        self->vtable = CreditChild162_vtable_80490B34;
        CreditMgr_SetActiveSlot(0);
        dtor_80147584(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

}
clCSSceneNextRace::~clCSSceneNextRace() {
    fn_80121210();
    if (panel) delete panel;
    fn_80169C44();
}
static inline void DrawCredit162(clCSSceneNextRace *s, float alpha) {
    fn_801695E0(0, fn_8013BEF4(s->a, s->c, s->d), 0, 104.0f, 113.0f, alpha);
    const char *first = fn_8013C100(s->a, s->c, -1);
    const char *second = fn_8013C204(s->b, -1);
    fn_80168798(0, lbl_806D88A8, 185.0f, 93.0f, alpha, second, first);
    if (s->service && s->item != 0) {
        int special = (s->item >= 159) ? 1 : 0;
        int descriptor = Item_GetDescriptorField8(s->item);
        Item_GetDescriptorFieldC(s->item);
        ItemTransform162 *transform = fn_8013BEC8(descriptor);
        fn_801695E0(0, Item_GetDescriptorField0(s->item, 0), 0, 281.0f, 134.0f, alpha);
        if (special) fn_801695E0(0, 0x7c5, 0, 301.0f, 120.0f, alpha);
        fn_80168D84(0, GetTextureByIdAndLang(0x4c, -1), 332.0f, 121.0f, alpha);
        if (transform) {
            fn_80168B90(0, fn_8023DAA8(s->item), 332.0f, 141.0f, transform->x, transform->y, transform->z, transform->scale * alpha);
        } else {
            fn_80168D84(0, fn_8023DAA8(s->item), 332.0f, 141.0f, alpha);
        }
    }
}

void clCSSceneNextRace::Update() {
    clCSSceneNextRace *s = this;
    float t;
    if (s->done) return;
    if (s->phase == 99) { s->done = 1; return; }
    switch (s->phase) {
    case 0:
        fn_801698B4(0, 0x8a9, 0, 640.0f * (1.0f - s->timer / 30.0f) + 284.0f, 46.0f);
        if (s->timer >= 30.0f) { s->phase = 1; s->timer = 0.0f; }
        break;
    case 1:
        {
            t = s->timer / 30.0f;
            DrawCredit162(s, t);
        }
        fn_801698B4(0, 0x8a9, 0, 284.0f, 46.0f);
        if (s->timer >= 30.0f) {
            s->phase = 2;
            s->timer = 0.0f;
            if (!s->panel) {
                fn_801699D8(0, 1);
                s->panel = new CreditChild162;
            }
        }
        break;
    case 2:
        {
            DrawCredit162(s, lbl_806D8888);
        }
        fn_801698B4(0, 0x8a9, 0, 284.0f, 46.0f);
        if (s->panel) {
            s->panel->Update();
            if (s->panel->done) { s->phase = 3; s->timer = 0.0f; }
        } else { s->phase = 3; s->timer = 0.0f; }
        break;
    case 3: {
        t = s->timer / 30.0f;
        DrawCredit162(s, 1.0f - t);
        fn_801698B4(0, 0x8a9, 0, 284.0f - 640.0f * t, 46.0f);
        if (s->timer >= 30.0f) { s->phase = 99; s->timer = 0.0f; }
        break;
    }
    }
    if (s->panel) s->panel->Draw();
    RumbleUpdate();
    s->timer += 1.0f;
    if (!s->active) s->active = 1;
}
void clCSSceneNextRace::Draw() {
    clCSSceneNextRace *self = this;
    int i;
    if (!self->done && self->active == 1) {
        for (i = 0; i < 8; i++) {
            fn_8011F994(i);
        }
        if (self->panel) {
            ((Model *)self->panel)->Draw();
        }
        HSD_StateInvalidate(-1);
    }
}
