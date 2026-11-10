
/* sdata symbols referenced from asm */
extern unsigned char lbl_806D8574[4];
extern unsigned char lbl_806D859C[4];
extern unsigned char lbl_806D83D8[4];
extern unsigned char lbl_806D83E4[5];
extern unsigned char lbl_806D83F0[8];
extern unsigned char lbl_806D8438[3];
extern unsigned char lbl_806D8440[5];
extern unsigned char lbl_806D8450[4];
extern unsigned char lbl_806D8468[5];
extern unsigned char lbl_806D8474[5];
extern unsigned char lbl_806D847C[4];
extern unsigned char lbl_806D8480[4];
extern unsigned char lbl_806D8498[8];
extern unsigned char lbl_806D84A4[8];
extern unsigned char lbl_806D84AC[4];
extern unsigned char lbl_806D84D8[4];
/*
 * 0x80157940..0x8015A6E4: list helpers and the scene updates that use them.
 */
#pragma cplusplus on

#include "game/types/ListNode.h"

#include "game/types/ListIter.h"

#include "game/types/List.h"

#include "game/types/DataBuf.h"

#include "game/types/DrawObj.h"

#include "game/types/DrawScene.h"

struct InputView {
    char pad[0x14];
    int dir;
};

struct MenuTarget {
    char pad0[0xc];
    unsigned char sel;
    char padD[0xa8 - 0xd];
    unsigned char unlocked[60];
    char padE4[0x19d - 0xe4];
    unsigned char flag;
};

struct InputPlayer {
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual float Stick();
    virtual unsigned char Pressed(int mask);
};

struct WidgetBase {
    char pad0[0x14];
};

class Widget : public WidgetBase {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void Update();
    virtual void Draw();
};

#include "game/types/OptionMenu.h"

/* TOP-END */

extern "C" {
void MemoryManager_TimedFree(void *p);
extern void Alloc();
extern void __throw();
extern void fn_801F7DAC();
void HSD_StateInvalidate(int state);
void fn_8011F994(int i);
void fn_8013D940(int i);
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int index);
void RumbleUpdate(void);
void SetRumbleMode(int a, int b, int c);
void SetSyncTarget(int id);
int WeatherSystem_PickVariant(int sel);
void clStream_setVolume(int ch, int vol);
void fn_8015A6E4(OptionMenu *self, int layer, float x, float y, float alpha);
void fn_801678FC(int layer, float r, float g, float b, float a);
void fn_801698B4(int layer, int id, int flag, float x, float y);
unsigned char fn_8019083C(int ch);
int fn_801932F8(void);
void fn_801FE27C(int t);
void fn_801FE348(void);
void fn_801FE390(void);
void fn_801FEF18(void *obj, int t);
extern const float lbl_806D8390;
extern const float lbl_806D8394;
extern const float lbl_806D8398;
extern const float lbl_806D839C;
extern const float lbl_806D83A0;
extern const float lbl_806D83A4;
extern const float lbl_806D83A8;
extern const float lbl_806D83AC;
extern const float lbl_806D83B0;
extern const float lbl_806D83B4;
extern const float lbl_806D83B8;
extern const float lbl_806D83BC;
extern const float lbl_806D83C0;
void fn_801FE36C(void);
extern struct InputView *g_pInputState;
extern const float lbl_806D83C4;
extern const float lbl_806D83C8;
const char *GetTextureByIdAndLang(int id, int lang);
int fn_80167744(int digit, float v);
void fn_80168798(int layer, const void *s, float x, float y, float a, ...);
void fn_80168D84(int layer, const void *s, float x, float y, float a, ...);
void fn_80169334(int layer, int id, int f, float x, float y, float sx, float sy, float a);
void fn_801695E0(int layer, int id, int f, float x, float y, float a);
int isJapanese(void);
extern const float lbl_806D83CC;
extern const float lbl_806D83D0;
extern const float lbl_806D83D4;
extern const float lbl_806D83DC;
extern const float lbl_806D83E0;
extern const float lbl_806D83EC;
extern const float lbl_806D83F8;
extern const float lbl_806D83FC;
extern const float lbl_806D8400;
extern const float lbl_806D8404;
extern const float lbl_806D8408;
extern const float lbl_806D840C;
extern const float lbl_806D8410;
extern const float lbl_806D8414;
extern const float lbl_806D8418;
extern const float lbl_806D841C;
extern const float lbl_806D8420;
extern const float lbl_806D8424;
extern const float lbl_806D8428;
extern const float lbl_806D842C;
extern const float lbl_806D8430;
extern const float lbl_806D8434;
extern const float lbl_806D843C;
extern unsigned int lbl_806D8448;
void fn_80168404(int layer, const void *s, float x, float y, float sx, float sy, float a, ...);
extern const float lbl_806D8454;
extern const float lbl_806D8458;
extern const float lbl_806D845C;
extern const float lbl_806D8460;
extern const float lbl_806D8464;
extern const float lbl_806D8470;
extern const float lbl_806D8484;
extern const float lbl_806D8488;
extern const float lbl_806D848C;
extern const float lbl_806D8490;
extern const float lbl_806D8494;
extern const float lbl_806D84A0;
extern const float lbl_806D84B0;
extern const float lbl_806D84B4;
extern const float lbl_806D84B8;
extern const float lbl_806D84BC;
extern const float lbl_806D84C0;
extern const float lbl_806D84C4;
extern const float lbl_806D84C8;
extern const float lbl_806D84CC;
extern const float lbl_806D84D0;
extern const float lbl_806D84D4;
extern int Item_GetDescriptorField0(int, int);
extern int Item_GetDescriptorField8(int);
extern int Item_GetDescriptorFieldC(int);
extern unsigned char PlayerData_GetUnlockedItemIdByIndex_U8(int);
struct ItemColor;
extern ItemColor *fn_8013BEC8(int);
void fn_80168B90(int layer, const void *s, float x, float y, float r, float g, float b, float a, ...);
void fn_8016918C(int layer, int id, int f, float x, float y, float sx, float sy, float r, float g, float b, float a);
extern const char *fn_8023D938(int, int);
extern const char *fn_8023DAA8(int);
extern const float lbl_806D84DC;
extern const float lbl_806D84E0;
extern const float lbl_806D84E4;
extern const float lbl_806D84E8;
extern const float lbl_806D84EC;
extern const float lbl_806D84F0;
extern const float lbl_806D84F4;
extern const float lbl_806D84F8;
extern const float lbl_806D84FC;
extern const float lbl_806D8500;
extern const float lbl_806D8504;
extern const float lbl_806D8508;
extern const float lbl_806D850C;
extern const float lbl_806D8510;
extern const float lbl_806D8514;
extern const float lbl_806D8518;
extern const float lbl_806D851C;
extern const float lbl_806D8520;
extern const float lbl_806D8524;
extern const float lbl_806D8528;
extern const float lbl_806D852C;
extern const float lbl_806D8530;
extern const float lbl_806D8534;
extern const float lbl_806D8538;
extern const float lbl_806D853C;
extern const float lbl_806D8540;
extern const float lbl_806D8544;
extern const float lbl_806D8548;
extern const float lbl_806D854C;
extern const float lbl_806D8550;
extern const float lbl_806D8554;
extern const float lbl_806D8558;
extern const float lbl_806D855C;
extern const float lbl_806D8560;
extern const float lbl_806D8564;
extern const float lbl_806D8568;
extern const float lbl_806D856C;
extern const float lbl_806D8570;
void fn_80157940(void);
void fn_801579F0(ListIter *ret, List *l, ListIter *it);
void fn_80157A68(void);
void fn_80157B20(List *l);
void fn_80157B38(void);
void fn_80157BE8(ListIter *ret, List *l, ListIter *it);
void fn_80157C60(void);
void fn_80157D18(List *l);
void fn_80157D30(void);
void fn_80157DE0(void);
void fn_80157EA8(List *l);
DataBuf *dtor_80157EC0(DataBuf *self, short flag);
void fn_80157F1C(DrawScene *self);
void fn_80157FB4(OptionMenu *self);
void fn_801589BC(OptionMenu *self, int mode);
void fn_80158CE4(OptionMenu *self, int layer, float x, float y, float alpha);
void fn_8015915C(OptionMenu *self, int layer, float x, float y, float alpha);
void fn_801596D4(OptionMenu *self, int layer, float x, float y, float alpha);
void fn_80159BD0(OptionMenu *self, int layer, float x, float y, float alpha);

const char *fn_8013C26C(int,int);
void fn_8013C4A4(void *,float);
void fn_8013C5FC(void *,float);
void fn_8013C674(void *,float);
void fn_8013C6EC(void *,float,float,float);
void fn_8013C7B0(void *,float,float);
void fn_8013C91C(void *);
void fn_8013DAC8(void *,int);
void fn_80167C60(int,const void *,float,float,float,...);
struct RankLog;
const char *get_title_name_global(RankLog *log);
extern unsigned int lbl_806D10A0;
extern unsigned int lbl_806D8578;
extern unsigned int lbl_806D857C;
extern unsigned int lbl_806D8580;
extern unsigned int lbl_806D8584;
extern unsigned int lbl_806D8588;
extern unsigned int lbl_806D858C;
extern unsigned int lbl_806D8590;
extern unsigned int lbl_806D8594;
extern unsigned int lbl_806D8598;
extern unsigned int lbl_806D85A0;
extern unsigned int lbl_806D85A4;
extern unsigned int lbl_806D85A8;
extern unsigned int lbl_806D85AC;
extern unsigned int lbl_806D85B0;
extern unsigned int lbl_806D85B4;
extern unsigned int lbl_806D85B8;
extern unsigned int lbl_806D85BC;
extern unsigned int lbl_806D85C0;
extern unsigned int lbl_806D85C4;
extern unsigned int lbl_806D85C8;
extern unsigned int lbl_806D85CC;

}

#pragma push
#pragma force_active on
/* ---- formerly OptionMenuDraw.cpp: the TU .rodata 0x803678D8..0x80367F68 ---- */
// Shared curve, color and layout tables, followed by the scene text pool.
extern "C" const float SceneList_80157EA8_rodata_803678D8[255] = {
    1.0f, 0.699999988f, 0.899999976f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f,
    66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f, 66.6666718f, 5000.0f,
    66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f,
    66.6666718f, 3000.0f, 66.6666718f, 4000.0f, 66.6666718f, 5000.0f, 66.6666718f, 0.0f,
    0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f,
    66.6666718f, 4000.0f, 66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f,
    66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f,
    66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f, 66.6666718f, 5000.0f,
    66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f,
    66.6666718f, 3000.0f, 66.6666718f, 4000.0f, 66.6666718f, 5000.0f, 66.6666718f, 0.0f,
    0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f,
    66.6666718f, 4000.0f, 66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f,
    66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f,
    66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f, 66.6666718f, 5000.0f,
    66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f,
    66.6666718f, 3000.0f, 66.6666718f, 4000.0f, 66.6666718f, 5000.0f, 66.6666718f, 0.0f,
    0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f,
    66.6666718f, 4000.0f, 66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f,
    66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 83.3333359f, 1000.0f,
    83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f, 83.3333359f, 5000.0f,
    83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f, 1000.0f, 83.3333359f, 2000.0f,
    83.3333359f, 3000.0f, 83.3333359f, 4000.0f, 83.3333359f, 5000.0f, 83.3333359f, 0.0f,
    0.0f, 500.0f, 83.3333359f, 1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f,
    83.3333359f, 4000.0f, 83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f,
    83.3333359f, 1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f, 1000.0f,
    83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f, 83.3333359f, 5000.0f,
    83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f, 1000.0f, 83.3333359f, 2000.0f,
    83.3333359f, 3000.0f, 83.3333359f, 4000.0f, 83.3333359f, 5000.0f, 83.3333359f,
};

static const unsigned int optionColors[42] = {
    96, 255, 0, 200, 64, 0, 0, 96,
    255, 0, 96, 255, 0, 96, 255, 0,
    96, 255, 0, 96, 255, 0, 96, 255,
    0, 96, 255, 0, 96, 255, 0, 96,
    255, 0, 96, 255, 0, 96, 255, 0,
    96, 255,
};

static const float optionPositions[5] = {
    -153.0f, -105.0f, -59.0f, -15.0f, 32.0f,
};

static const float optionIconX[5] = {
    -17.0f, 69.0f, 155.0f, 241.0f, 337.0f,
};

static const float optionMarkX[5] = {
    -17.0f, 49.0f, 135.0f, 221.0f, 307.0f,
};

static const int optionThresholds[17] = {
    3, 5, 7, 10, 15, 20, 25, 30,
    35, 40, 45, 50, 60, 70, 80, 90,
    100,
};

extern "C" const char lbl_80367DFC[] = "clCSSceneCardBrowse";

extern "C" const char lbl_80367E10[] = "clSceneInterface";

extern "C" const char lbl_80367E24[] = "Time attack record";

extern "C" const char lbl_80367E38[] = "\203^\203C\203\200\203A\203^\203b\203N\201@\203f\201[\203^";

static const char optionText578[] = "Versus race result";

static const char optionText58C[] = "\221\316\220\355\220\254\220\321\201@\203f\201[\203^";

static const char optionText5A0[] = "Versus Race count %03d";

static const char optionText5B8[] = "Number of Wins %03d";

static const char optionText5CC[] = "\221\316\220\355\203\214\201[\203X\220\224";

static const char optionText5DC[] = "\227D\217\237\211\361\220\224";

static const char optionText5E8[] = "Grand Prix mode";

static const char optionText5F8[] = "\203O\203\211\203\223\203v\203\212\203\202\201[\203h\201@\203f\201[\203^";

static const char optionText614[] = "Number of item(s) received %02d/%d";

static const char optionText638[] = "\203A\203C\203e\203\200\212l\223\276\220\224%02d";

static const char optionText64C[] = "\201^%d\214\302\222\206";

static const char optionText658[] = "\212\356\226{\203f\201[\203^";

static const char optionText664[] = "\211\271\227\312\202\360\225\317\215X\202\305\202\253\202\334\202\267\201B";

static const char optionText67C[] = "clCSPartsInerface";
#pragma pop

static inline InputView *input_state(void)
{
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
}



extern "C" void fn_80157EA8(List *l)
{
    ListNode *h = &l->head;
    l->size = 0;
    h->next = h;
    h->prev = h;
}

extern "C" DataBuf *dtor_80157EC0(DataBuf *self, short flag)
{
    if (self) {
        if (self->data) {
            MemoryManager_TimedFree(self->data);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void fn_80157F1C(DrawScene *self)
{
    if (self->hidden == 0 && self->state == 1) {
        self->a->Draw();
        self->b->Draw();
        HSD_StateInvalidate(-1);
        for (int i = 0; i < 8; i++) {
            fn_8013D940(i);
            fn_8011F994(i);
        }
        HSD_StateInvalidate(-1);
    }
}

static inline InputPlayer *player0(void)
{
    return InputMgr_GetPlayer(GetInputManager(), 0);
}

static inline void DrawPage(OptionMenu *self, int page, int layer, float x, float y, float alpha)
{
    switch (page) {
    case 0:
        fn_8015A6E4(self, layer, x, y, alpha);
        break;
    case 1:
        fn_80159BD0(self, layer, x, y, alpha);
        break;
    case 2:
        fn_801596D4(self, layer, x, y, alpha);
        break;
    case 3:
        fn_8015915C(self, layer, x, y, alpha);
        break;
    case 4:
        fn_80158CE4(self, layer, x, y, alpha);
        break;
    }
}

extern "C" void fn_80157FB4(OptionMenu *self)
{
    float t;

    if (self->done != 0) {
        return;
    }
    fn_801FE27C(self->timeout);
    fn_801FEF18(self->bg, self->timeout);
    if (self->timeout != 0) {
        self->timeout--;
    }
    if (player0()->Stick() > lbl_806D8390) {
        if (self->stickHeld == 0) {
            self->stickHeld = 1;
            self->toggleEnabled = 1;
        } else {
            self->toggleEnabled = 0;
        }
    } else {
        self->stickHeld = 0;
        self->toggleEnabled = 0;
    }
    if (self->state == 1) {
        if (self->timeout == 0 || player0()->Pressed(0x100) || player0()->Pressed(0x2000)) {
            SetRumbleMode(0, 4, 10);
            fn_801FE348();
            SetSyncTarget(14);
            self->state = 8;
        } else if (player0()->Pressed(0x400)) {
            fn_801FE390();
            self->nextPage = self->page + 1;
            if (self->nextPage >= 5) {
                self->nextPage = 0;
            }
            self->state = 2;
            self->timer = lbl_806D8394;
            switch (self->nextPage) {
            case 0: {
                self->blink = lbl_806D8394;
                self->fade50 = lbl_806D8398;
                self->fade54 = lbl_806D839C;
                unsigned char v = self->sel;
                if (fn_8019083C(1)) {
                    clStream_setVolume(1, WeatherSystem_PickVariant(v));
                }
                break;
            }
            case 1:
                self->blink2 = lbl_806D8394;
                int k;
                self->count = self->value = k = 0;
                for (; k < 60; k++) {
                    if (self->target->unlocked[k]) {
                        self->count++;
                        if (self->value < 0) {
                            self->value = k;
                        }
                    }
                }
                if (fn_8019083C(1)) {
                    clStream_setVolume(1, fn_801932F8());
                }
                break;
            case 2:
                break;
            case 3:
                self->scroll = -1;
                self->scrollTimer = 0;
                break;
            case 4:
                break;
            }
        }
    }
    fn_801698B4(0, 0x640, 0, lbl_806D83A0, lbl_806D83A4);
    fn_801698B4(0, 0x63f, 0, lbl_806D83A8, lbl_806D83AC);
    self->bg->v10();
    self->frame->v10();
    self->w34->Update();
    self->w34->Draw();
    self->w38->Update();
    self->w3C->Update();
    self->w40->Update();
    switch (self->state) {
    case 0:
        self->timer += lbl_806D83B0;
        t = self->timer / lbl_806D83B4;
        DrawPage(self, self->page, 1, lbl_806D8394, lbl_806D8394, lbl_806D83B0);
        fn_801678FC(2, lbl_806D8394, lbl_806D8394, lbl_806D8394, lbl_806D83B0 - t);
        if (self->timer >= lbl_806D83B4) {
            self->state = 1;
            self->timer = lbl_806D8394;
        }
        break;
    case 1:
        fn_801589BC(self, self->page);
        DrawPage(self, self->page, 1, lbl_806D8394, lbl_806D8394, lbl_806D83B0);
        break;
    case 2:
        self->timer += lbl_806D83B0;
        t = self->timer / lbl_806D83B8;
        DrawPage(self, self->nextPage, 1, lbl_806D8394, lbl_806D8394, t);
        fn_801698B4(1, 0x63f, 0, lbl_806D83A8 - lbl_806D83BC * t, lbl_806D83AC);
        DrawPage(self, self->page, 2, lbl_806D83C0 * t, lbl_806D8394, lbl_806D83B0);
        if (self->timer >= lbl_806D83B8) {
            self->page = self->nextPage;
            self->state = 1;
            self->timer = lbl_806D8394;
        }
        break;
    case 8:
        DrawPage(self, self->page, 1, lbl_806D8394, lbl_806D8394, lbl_806D83B0);
        self->state = 9;
        self->timer = lbl_806D8394;
        break;
    case 9:
        self->timer += lbl_806D83B0;
        t = self->timer / lbl_806D83B4;
        DrawPage(self, self->page, 1, lbl_806D8394, lbl_806D8394, lbl_806D83B0);
        fn_801678FC(2, lbl_806D8394, lbl_806D8394, lbl_806D8394, t);
        if (self->timer >= lbl_806D83B4) {
            self->done = 1;
        }
        break;
    }
    RumbleUpdate();
    if (self->started == 0) {
        self->started = 1;
    }
}

extern "C" void fn_801589BC(OptionMenu *self, int mode) {
    switch (mode) {
    case 0:
        if (input_state()) {
            int dir = input_state()->dir;
            if (dir == 1) {
                if (self->sel < 4) {
                    fn_801FE36C();
                    self->sel++;
                    self->target->sel = self->sel;
                    self->fade50 = lbl_806D8394;
                    self->fade54 = lbl_806D8394;
                    unsigned char v = self->sel;
                    if (fn_8019083C(1)) clStream_setVolume(1, WeatherSystem_PickVariant(v));
                }
            } else if (dir == -1) {
                if (self->sel != 0) {
                    fn_801FE36C();
                    self->sel--;
                    self->target->sel = self->sel;
                    self->fade50 = lbl_806D8394;
                    self->fade54 = lbl_806D8394;
                    unsigned char v = self->sel;
                    if (fn_8019083C(1)) clStream_setVolume(1, WeatherSystem_PickVariant(v));
                }
            }
        }
        if (self->toggleEnabled) {
            fn_801FE36C();
            self->toggle = !self->toggle;
            self->target->flag = self->toggle;
        }
        if (self->fade50 < lbl_806D8398) self->fade50 += lbl_806D83B0;
        if (self->fade54 < lbl_806D839C) self->fade54 += lbl_806D83B0;
        if ((self->blink += lbl_806D83B0) >= lbl_806D83C4) self->blink = lbl_806D8394;
        break;
    case 1:
        if (input_state()) {
            int dir = input_state()->dir;
            if (dir == 1) {
                fn_801FE36C();
                self->value++;
                if (self->value >= 60) self->value = 0;
                self->blink2 = lbl_806D8394;
            } else if (dir == -1) {
                fn_801FE36C();
                self->value--;
                if (self->value < 0) self->value = 59;
                self->blink2 = lbl_806D8394;
            }
        }
        if ((self->blink2 += lbl_806D83B0) >= lbl_806D83C8) self->blink2 = lbl_806D8394;
        break;
    case 2:
        break;
    case 3:
        if (self->scroll < 0) {
            if (self->scrollTimer > 0) self->scrollTimer--;
            else { self->scroll = 0; self->scrollTimer = 0; }
        } else if (++self->scrollTimer >= 4) {
            if (++self->scroll < 31) self->scrollTimer = 0;
            else { self->scroll = -1; self->scrollTimer = 120; }
        }
        break;
    case 4:
        break;
    }
}

/* Same C symbol as fn_801695E0(layer, id, x, y, alpha, flag), declared with the
 * floats before the id. GPR and FPR arguments are numbered separately, so the
 * registers are identical; only the evaluation order changes (the target
 * evaluates x/y/alpha before the id). The real prototype is probably
 * float-first. See docs/regalloc_patterns.md section 74. */
namespace alt { extern "C" void fn_801695E0(int, float, float, float, int, int); }
static inline void DrawSpriteScaled(int layer, int id, float x, float y, float scale, float alpha)
{
    fn_80169334(layer, id, 0, x, y, scale, scale, alpha);
}

#pragma push
#pragma opt_loop_invariants off
extern "C" void fn_80158CE4(OptionMenu *self, int layer, float x, float y, float alpha)
{
    float bx;
    float by;
    float px;
    float dy;
    int i;
    int j;

    if (isJapanese() == 1) {
        float rowY;
        fn_80168D84(layer, lbl_80367E24, 35.0f + x, rowY = 112.0f + y, alpha);
        fn_80168798(layer, lbl_806D83D8, 388.0f + x, rowY, alpha);
        fn_80168D84(layer, lbl_806D83E4, 436.0f + x, 114.0f + y, alpha);
    } else {
        float rowY;
        fn_80168798(layer, lbl_80367E38, 35.0f + x, rowY = 112.0f + y, alpha);
        fn_80168798(layer, lbl_806D83D8, 366.0f + x, rowY, alpha);
        fn_80168D84(layer, lbl_806D83F0, 436.0f + x, 114.0f + y, alpha);
    }
    bx = 80.0f + x;
    by = 238.0f + y;
    for (i = 0; i < 4; i++) {
        px = 60.0f + (120.0f * (float)i + bx);
        DrawSpriteScaled(layer, 0x7db, px, by, 0.85f, alpha);
        if (self->time[i] > 0.0f) {
            fn_801695E0(layer, 0x7dc, 0, px - 14.0f, by - 52.0f, alpha);
            fn_801695E0(layer, i + 0x7dd, 0, 33.0f + px, by - 52.0f, alpha);
            DrawSpriteScaled(layer, self->course[i] + 0x76c, px - 1.0f, by - 15.0f, 0.5f, alpha);
            if (self->kind[i] == 2) {
                DrawSpriteScaled(layer, 0x7b0, 30.0f + px, by - 5.0f, 0.4f, alpha);
            }
            alt::fn_801695E0(layer, px - 1.0f,
                        15.0f + by, alpha, 0x7e4 + self->course[i] * 2 + self->mode[i], 0);
            if (self->isNew[i] != 0) {
                if (isJapanese() == 1) {
                    fn_80168D84(layer, GetTextureByIdAndLang(0x39, -1), px - 28.0f, 32.0f + by,
                                alpha);
                } else {
                    fn_80168D84(layer, GetTextureByIdAndLang(0x39, -1), px - 10.0f, 32.0f + by,
                                alpha);
                }
            }
            dy = 48.0f + by;
            px -= 32.0f;
            for (j = 0; j < 8; j++) {
                fn_801695E0(layer, fn_80167744(7 - j, self->time[i]) + 0x1ecd, 0, 10.0f * (float)j + px, dy,
                            alpha);
            }
        } else {
            fn_80168D84(layer, lbl_806D8438, px - 6.0f, by - 8.0f, alpha);
            fn_80168D84(layer, lbl_806D8440, px - 18.0f, 10.0f + by, alpha);
        }
    }
}
#pragma pop

static inline void DrawDigits(int layer, signed char *digits, float x, float y, float alpha)
{
    int i;
    for (i = 0; i < 3; i++) {
        alt::fn_801695E0(layer, 64.0f * i + x, y, alpha, digits[i] + 0x3F7, 0);
    }
}
extern "C" void fn_8015915C(OptionMenu *self, int layer, float x, float y, float alpha)
{
    float colX;
    float gridY;
    float rowY;
    int i;
    int id;

    if (isJapanese() == 1) {
        float rowY;
        fn_80168D84(layer, optionText578, 35.0f + x, rowY = 112.0f + y, alpha);
        fn_80168798(layer, lbl_806D8450, 388.0f + x, rowY, alpha);
        fn_80168D84(layer, lbl_806D83E4, 436.0f + x, 114.0f + y, alpha);
    } else {
        float rowY;
        fn_80168798(layer, optionText58C, 35.0f + x, rowY = 112.0f + y, alpha);
        fn_80168798(layer, lbl_806D8450, 366.0f + x, rowY, alpha);
        fn_80168D84(layer, lbl_806D83F0, 436.0f + x, 114.0f + y, alpha);
    }
    rowY = 184.0f + y;
    DrawDigits(layer, self->digitsA, 100.0f + x, rowY, alpha);
    DrawDigits(layer, self->digitsB, 388.0f + x, rowY, alpha);
    if (isJapanese() == 1) {
        float rowY;
        fn_80168798(layer, lbl_806D8468, 272.0f + x, rowY = 204.0f + y, alpha);
        fn_80168798(layer, lbl_806D8474, 560.0f + x, rowY, alpha);
    } else {
        float rowY;
        fn_80168798(layer, lbl_806D847C, 272.0f + x, rowY = 204.0f + y, alpha);
        fn_80168798(layer, lbl_806D8480, 560.0f + x, rowY, alpha);
    }
    colX = 35.0f + x;
    gridY = 232.0f + y;
    for (i = 0; i < 100; i++) {
        int col = i % 20;
        int row = i / 20;
        float px = 30.0f * col + colX;
        float py = 32.0f * row + gridY;
        id = 0x647;
        if (i < self->wins) {
            int k = col + row;
            id = 0x654;
            if (k <= self->scroll) {
                int v = ((self->scroll - k) * 4 + self->scrollTimer) / 4;
                if (v < 6) {
                    id = v + 0x654;
                }
            }
        } else {
            if (row & 1) {
                id = 0x649;
            }
            const int *p = optionThresholds;
            for (int j = 0; j < 17; j++, p++) {
                if (i + 1 == *p) {
                    id--;
                    if ((i + 1) % 10 == 0) {
                        id = i / 10 + 0x64A;
                    }
                    break;
                }
            }
        }
        fn_801695E0(layer, id, 0, px, py, alpha);
    }
    if (isJapanese() == 1) {
        float rowY;
        fn_80168404(layer, optionText5A0, 56.0f + x, rowY = 392.0f + y, 0.7f, 1.0f, alpha,
                    self->wins + self->losses);
        fn_80168404(layer, optionText5B8, 368.0f + x, rowY, 0.7f, 1.0f, alpha, self->wins);
    } else {
        float rowY;
        fn_80168798(layer, optionText5CC, 56.0f + x, rowY = 392.0f + y, alpha);
        fn_80168798(layer, lbl_806D8498, 248.0f + x, rowY, alpha, self->wins + self->losses);
        fn_80168798(layer, optionText5DC, 368.0f + x, rowY, alpha);
        fn_80168798(layer, lbl_806D84A4, 512.0f + x, rowY, alpha, self->wins);
    }
}


extern "C" void fn_801596D4(OptionMenu *self, int layer, float x, float y, float alpha)
{
    float rowY;

    if (isJapanese() == 1) {
        fn_80168D84(layer, optionText5E8, lbl_806D83CC + x, rowY = lbl_806D83D0 + y, alpha);
        fn_80168798(layer, lbl_806D84AC, lbl_806D83D4 + x, rowY, alpha);
        fn_80168D84(layer, lbl_806D83E4, lbl_806D83DC + x, lbl_806D83E0 + y, alpha);
    } else {
        fn_80168798(layer, optionText5F8, lbl_806D83CC + x, rowY = lbl_806D83D0 + y, alpha);
        fn_80168798(layer, lbl_806D84AC, lbl_806D83EC + x, rowY, alpha);
        fn_80168D84(layer, lbl_806D83F0, lbl_806D83DC + x, lbl_806D83E0 + y, alpha);
    }
    float colX = lbl_806D84B0 + x;
    float baseY = lbl_806D84B4 + y;
    unsigned char allSet = 1;
    for (int i = 0; i < 6; i++) {
        float lineY = lbl_806D842C * i + baseY;
        if ((self->flags[i] & 0x1F) == 0x1F) {
            fn_801695E0(layer, 0x665, 0, colX, lineY, alpha);
            fn_801695E0(layer, 0x666, 0, lbl_806D84B8 + colX, lineY, alpha);
        } else {
            if (i < 5 && (self->flags[i] & 0xF) != 0xF) {
                allSet = 0;
            }
            fn_801695E0(layer, 0x667, 0, colX, lineY, alpha);
            fn_801695E0(layer, 0x668, 0, lbl_806D84B8 + colX, lineY, alpha);
        }
        if (i == 5 && !allSet) {
            fn_801695E0(layer, 0x66F, 0, colX - lbl_806D84BC, lineY - lbl_806D84C0, alpha);
        } else {
            fn_801695E0(layer, i + 0x669, 0, colX - lbl_806D84BC, lineY - lbl_806D84C0, alpha);
            if ((self->rule & 1) == 1) {
                fn_801695E0(layer, 0x670, 0, colX - lbl_806D84C4, lbl_806D84C8 + lineY, alpha);
            }
        }
        float iconY = lbl_806D84CC + lineY;
        float markY = lbl_806D84D0 + lineY;
        for (int j = 0; j < 4; j++) {
            if (i == 5 && !allSet) {
                fn_801695E0(layer, j + 0x65A, 0, colX + optionIconX[j], iconY, alpha);
            } else {
                if (j < 1 || (self->flags[i] & (1 << (j - 1)))) {
                    fn_801695E0(layer, j + 0x65F, 0, colX + optionIconX[j], iconY, alpha);
                } else {
                    fn_801695E0(layer, j + 0x65A, 0, colX + optionIconX[j], iconY, alpha);
                }
                if (self->flags[i] & (1 << j)) {
                    fn_801695E0(layer, 0x664, 0, colX + optionMarkX[j], markY, alpha);
                }
            }
        }
        if (self->rule < 2) {
            if ((self->flags[i] & 0xF) == 0xF) {
                fn_801695E0(layer, 0x663, 0, colX + optionIconX[4], iconY, alpha);
                if (self->flags[i] & 0x10) {
                    fn_801695E0(layer, 0x664, 0, colX + optionMarkX[4], markY, alpha);
                }
            } else {
                fn_801695E0(layer, 0x65E, 0, colX + optionIconX[4], iconY, alpha);
            }
        } else {
            fn_801695E0(layer, 0x680, 0, lbl_806D84D4 + colX, lineY, alpha);
        }
    }
}

struct ItemColor {
    float r;
    float g;
    float b;
    float a;
};

struct WidgetView {
    int layer;
    char pad4[4];
    float x;
    float y;
    float alpha;
};

static inline void Widget_SetLayer(Widget *w, int layer)
{
    if (layer >= 0 && layer < 8) {
        ((WidgetView *)w)->layer = layer;
    }
}

static inline void Widget_SetPos(Widget *w, float x, float y)
{
    ((WidgetView *)w)->x = x;
    ((WidgetView *)w)->y = y;
}

static inline void Widget_SetAlpha(Widget *w, float a)
{
    ((WidgetView *)w)->alpha = a;
}

static inline int Item_IsSpecial(int id)
{
    return id >= 0x9f;
}

static inline unsigned int Item_NameSprite(int n)
{
    int r;
    if (n < 0) {
        r = -1;
    } else {
        r = n + 0x4f3;
    }
    return r;
}

extern "C" void fn_80159BD0(OptionMenu *self, int layer, float x, float y, float alpha)
{
    float rowY;
    float rowY2;

    if (isJapanese() == 1) {
        fn_80168D84(layer, optionText614, 35.0f + x, rowY = 112.0f + y, alpha, self->count, 0x3c);
        fn_80168798(layer, lbl_806D84D8, 388.0f + x, rowY, alpha);
        fn_80168D84(layer, lbl_806D83E4, 436.0f + x, 114.0f + y, alpha);
    } else {
        fn_80168798(layer, optionText638, 35.0f + x, rowY = 112.0f + y, alpha, self->count);
        fn_80168D84(layer, optionText64C, (280.0f + x) - 16.0f, rowY2 = 114.0f + y, alpha, 0x3c);
        fn_80168798(layer, lbl_806D84D8, 366.0f + x, rowY, alpha);
        fn_80168D84(layer, lbl_806D83F0, 436.0f + x, rowY2, alpha);
    }
    int idx;
    int j;
    int i;
    int page = self->value / 12;
    unsigned char special;
    for (i = 0; i < 5; i++) {
        float cy = y + (34.0f * i + 155.0f);
        for (j = 0; j < 12; j++) {
            idx = i * 12 + j;
            float cx = x + (46.0f * j + 65.0f);
            fn_801695E0(layer, 0x7cf, 0, cx, cy, alpha);
            int id = PlayerData_GetUnlockedItemIdByIndex_U8(idx);
            special = Item_IsSpecial(id);
            if (i == page) {
                if (self->value != idx) {
                    if (self->target->unlocked[idx]) {
                        fn_80169334(layer, Item_GetDescriptorField0(id, 0), 0, cx, cy, 0.75f, 0.75f, alpha);
                        if (special) {
                            fn_80169334(layer, 0x7c5, 0, 15.0f + cx, cy - 10.5f, 0.75f, 0.75f, alpha);
                        }
                    } else {
                        fn_80169334(layer, Item_GetDescriptorField0(0, 0), 0, cx, cy, 0.75f, 0.75f, alpha);
                    }
                }
            } else {
                if (self->target->unlocked[idx]) {
                    fn_8016918C(layer, Item_GetDescriptorField0(id, 0), 0, cx, cy, 0.75f, 0.75f, 0.5f, 0.5f, 0.5f, alpha);
                    if (special) {
                        fn_8016918C(layer, 0x7c5, 0, 15.0f + cx, cy - 10.5f, 0.75f, 0.75f, 0.5f, 0.5f, 0.5f, alpha);
                    }
                } else {
                    fn_8016918C(layer, Item_GetDescriptorField0(0, 0), 0, cx, cy, 0.75f, 0.75f, 0.5f, 0.5f, 0.5f, alpha);
                }
            }
        }
    }
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 12; j++) {
            idx = i * 12 + j;
            if (self->value != idx && self->target->unlocked[idx]) {
                if (self->equipped == PlayerData_GetUnlockedItemIdByIndex_U8(idx)) {
                    float rx = 46.0f * j + 65.0f;
                    float ry = 34.0f * i + 155.0f;
                    if (i == page) {
                        fn_8016918C(layer, 0x7d3, 0, x + rx, y + ry, 0.75f, 0.75f, 1.0f, 1.0f, 1.0f, alpha);
                    } else {
                        fn_8016918C(layer, 0x7d3, 0, x + rx, y + ry, 0.75f, 0.75f, 0.5f, 0.5f, 0.5f, alpha);
                    }
                }
            }
        }
    }
    float py;
    float px = 317.0f + x;
    py = 368.0f + y;
    fn_801695E0(layer, 0x641, 0, px, py, alpha);
    if (self->value >= 0) {
        float selX;
        float selY;
        float sx;
        float cy2;
        float cx2;
        float tx;
        float sy;
        int id = PlayerData_GetUnlockedItemIdByIndex_U8(self->value);
        special = Item_IsSpecial(id);
        selX = 46.0f * (self->value % 12) + 65.0f;
        selY = 34.0f * (self->value / 12) + 155.0f;
        int nameId = Item_GetDescriptorFieldC(id);
        int kind = Item_GetDescriptorField8(id);
        int spr = Item_NameSprite(nameId);
        ItemColor *col = fn_8013BEC8(kind);
        Widget_SetLayer(self->w40, layer);
        Widget_SetPos(self->w40, 599.0f + x, 356.0f + y);
        Widget_SetAlpha(self->w40, alpha);
        self->w40->Draw();
        float t = self->blink2;
        if (t < 10.0f) {
            sx = 0.75f + 0.28f * t / 10.0f;
            sy = 0.75f + 0.58f * t / 10.0f;
        } else if (t < 14.0f) {
            float d = t - 10.0f;
            sx = 0.12f * d / 4.0f + 1.03f;
            sy = 1.33f - 0.3f * d / 4.0f;
        } else if (t < 18.0f) {
            float d = t - 14.0f;
            sx = 1.15f - 0.12f * d / 4.0f;
            sy = 0.3f * d / 4.0f + 1.03f;
        } else if (t < 24.0f) {
            float d = t - 18.0f;
            sx = 1.03f - 0.28f * d / 6.0f;
            sy = 1.33f - 0.09f * d / 6.0f;
        } else if (t < 30.0f) {
            float d = t - 24.0f;
            sx = 0.75f - 0.1f * d / 6.0f;
            sy = 1.24f - 0.09f * d / 6.0f;
        } else if (t < 42.0f) {
            float d = t - 30.0f;
            sx = 0.65f + 0.03f * d / 12.0f;
            sy = 1.15f - 0.34f * d / 12.0f;
        } else {
            float d = t - 42.0f;
            sx = 0.68f + 0.12f * d / 3.0f;
            sy = 0.71f + 0.04f * d / 3.0f;
        }
        cx2 = x + selX;
        cy2 = y + selY;
        fn_80169334(layer, 0x7cf, 0, cx2, cy2, sx, sy, alpha);
        if (self->target->unlocked[self->value]) {
            fn_80169334(layer, Item_GetDescriptorField0(id, 0), 0, cx2, cy2, sx, sy, alpha);
            if (special) {
                fn_80169334(layer, 0x7c5, 0, 20.0f * sx + cx2, cy2 - 14.0f * sy, sx, sy, alpha);
            }
            if (self->equipped == id) {
                fn_80169334(layer, 0x7d3, 0, cx2, cy2, sx, sy, alpha);
            }
            fn_801695E0(layer, spr, 0, px - 104.0f, 1.0f + py, alpha);
            fn_801695E0(layer, Item_GetDescriptorField0(id, 0), 0, px - 40.0f, 8.0f + py, alpha);
            if (special) {
                fn_801695E0(layer, 0x7c5, 0, px - 20.0f, py - 6.0f, alpha);
            }
            if (col) {
                fn_80168B90(layer, fn_8023DAA8(id), px - 192.0f, py - 29.0f, col->r, col->g, col->b, col->a * alpha);
            } else {
                fn_80168D84(layer, fn_8023DAA8(id), px - 192.0f, py - 29.0f, alpha);
            }
            fn_80168D84(layer, fn_8023D938(id, 0), tx = 12.0f + px, py - 25.0f, alpha);
            fn_80168D84(layer, fn_8023D938(id, 1), tx, py - 3.0f, alpha);
            fn_80168D84(layer, fn_8023D938(id, 2), tx, 19.0f + py, alpha);
        } else {
            fn_80169334(layer, Item_GetDescriptorField0(0, 0), 0, cx2, cy2, sx, sy, alpha);
        }
    }
}

/* ---- formerly OptionMenuDraw.cpp ---- */
#include "game/types/OptionDrawPrefix.h"
#include "game/types/OptionDrawPanel.h"
#include "game/types/OptionDrawTarget.h"
#include "game/types/OptionDrawScene.h"
struct OptionDrawPoint { float x, y; };
static inline RankLog *GetRankLog() { RankLog **pp = (RankLog **)&lbl_806D10A0; return (*pp == 0 ? 0 : *pp); }
extern "C" void fn_8015A6E4(OptionMenu *self_, int layer, float x, float y, float alpha) {
    OptionDrawScene *self = (OptionDrawScene *)self_;
    OptionDrawPoint rowOrigin;
    float nameX, rowY, imageX, nameY, titleY; OptionDrawPoint tp;
    float pulseScale, pulseAlpha;
    const float *positions;
    int count, i;
    const char *title;
    if (isJapanese() == 1) {
        fn_80168798(layer, (const char *)lbl_806D8574, 388.0f+x, 112.0f+y, alpha);
        fn_80168D84(layer, (const char *)lbl_806D83E4, 436.0f+x, 114.0f+y, alpha);
    } else {
        fn_80168798(layer, optionText658, 35.0f+x, rowOrigin.y=112.0f+y, alpha);
        fn_80168798(layer, (const char *)lbl_806D8574, 366.0f+x, rowOrigin.y, alpha);
        fn_80168D84(layer, (const char *)lbl_806D83F0, 436.0f+x, 114.0f+y, alpha);
    }
    const char *texture = GetTextureByIdAndLang(0x46,-1);
    fn_80168D84(layer, texture, 30.0f+x, tp.y=156.0f+y, alpha);
    texture = fn_8013C26C(self->texture,-1);
    fn_80168798(layer, texture, 34.0f+x, nameY=184.0f+y, alpha);
    fn_8013C7B0(self->preview,140.0f+x,370.0f+y);
    fn_8013C5FC(self->preview,-0.13962634f);
    fn_8013C674(self->preview,0.17453292f);
    fn_8013C6EC(self->preview,0.018f,0.018f,0.018f);
    fn_8013C4A4(self->preview,alpha);
    fn_8013C91C(self->preview);
    fn_8013DAC8(self->preview,layer);
    texture=GetTextureByIdAndLang(0x44,-1);
    imageX=268.0f+x;
    fn_80168D84(layer,texture,imageX,tp.y,alpha);
    nameX=388.0f+x;
    fn_80167C60(layer,self->target,nameX,152.0f+y,alpha);
    fn_80168D84(layer,GetTextureByIdAndLang(0x45,-1),imageX,188.0f+y,alpha);
    RankLog *global=GetRankLog();
    title=(const char *)lbl_806D859C;
    if (global) title=get_title_name_global(global);
    if (isJapanese()==1)
        fn_80168404(layer,title,nameX,nameY,1.0f,1.0f,alpha);
    else
        fn_80168404(layer,title,nameX,nameY,0.9f,1.0f,alpha);
    fn_80168D84(layer,GetTextureByIdAndLang(0x48,-1),imageX,220.0f+y,alpha);
    count=self->target->count-1;
    count=count & (((unsigned int)count >> 31)-1);
    fn_80168798(layer,GetTextureByIdAndLang(0x49,-1),nameX,216.0f+y,alpha,count);
    rowOrigin.x=435.0f+x;
    fn_801695E0(layer,0x643,0,rowOrigin.x,256.0f+y,alpha);
    if (self->toggle) {
        fn_801695E0(layer,0x67D,0,301.0f+x,rowY=308.0f+y,alpha);
        fn_801695E0(layer,0x67C,0,444.0f+x,rowY,alpha);
    } else {
        fn_801695E0(layer,0x67B,0,301.0f+x,rowY=308.0f+y,alpha);
        fn_801695E0(layer,0x67E,0,444.0f+x,rowY,alpha);
    }
    OptionDrawPanel *panel=self->panel38;
    if(layer>=0 && layer<8)panel->layer=layer;
    panel=self->panel38; panel->x=591.0f+x;panel->y=305.0f+y;
    self->panel38->alpha=alpha;
    self->panel38->Draw();
    rowY=356.0f+y;
    fn_801695E0(layer,0x642,0,rowOrigin.x,rowY,alpha);
    rowOrigin.y=33.0f+rowY;
    positions=optionPositions;
    for(i=0;i<5;i++,positions++) {
        if(self->selection==i)
            fn_801695E0(layer,0x676+i,0,rowOrigin.x+*positions,rowOrigin.y,alpha);
        else
            fn_801695E0(layer,0x671+i,0,rowOrigin.x+*positions,rowOrigin.y,alpha);
    }
    if(self->fade50<60.0f) {
        texture=GetTextureByIdAndLang(0x4B,-1);
        fn_80168B90(layer,texture,428.0f+x,rowY,1.0f,0.0f,0.0f,alpha);
    } else if(isJapanese()==0)
        fn_80168D84(layer,optionText664,428.0f+x,rowY,alpha);
    panel=self->panel3C;
    if(layer>=0 && layer<8)panel->layer=layer;
    panel=self->panel3C;panel->x=526.0f+x;panel->y=388.0f+y;
    self->panel3C->alpha=alpha;
    self->panel3C->Draw();
    if(self->fade54<25.0f) {
        float t=self->fade54;
        if(t<10.0f) {
            pulseAlpha=t/10.0f;
            pulseScale=0.5f+(0.5f*t)/10.0f;
        } else if(t<20.0f) {
            pulseScale=1.0f+(t-10.0f)/10.0f;
            pulseAlpha=1.0f-(t-10.0f)/10.0f;
        }
        fn_80169334(layer,0x67F,0,rowOrigin.x+optionPositions[self->selection],rowOrigin.y,pulseScale,pulseScale,pulseAlpha*alpha);
        t=self->fade54;
        if(t>5.0f) {
            if(t<15.0f) {
                float d=t-5.0f;
                pulseScale=0.5f+(0.5f*d)/10.0f;
                pulseAlpha=d/10.0f;
            } else if(t<25.0f) {
                pulseScale=1.0f+(t-15.0f)/10.0f;
                pulseAlpha=1.0f-(t-15.0f)/10.0f;
            }
            fn_80169334(layer,0x67F,0,rowOrigin.x+optionPositions[self->selection],rowOrigin.y,pulseScale,pulseScale,pulseAlpha*alpha);
        }
    }
}

/* ---- formerly game/Scene_8015AE3C.cpp ---- */
/*
 * 0x8015AE3C..0x8015AFCC: deleting destructor of the scene object built by
 * fn_8015AFCC (vtable Scene8015AFCC_vtable_8049003C, base vtable lbl_803FE0C8).
 */

struct VObj {
    virtual ~VObj();
    virtual void Update();
};

#include "game/types/VObjPad.h"

struct VObj14 : VObjPad {
    virtual ~VObj14();
};

struct Scene8015AE3CView {
    void *vtable;
    char pad04[0x20];
    VObj *obj24;
    char pad28[4];
    VObj *obj2C;
    VObj *obj30;
    VObj14 *obj34;
    VObj14 *obj38;
    VObj14 *obj3C;
    VObj14 *obj40;
};

extern "C" {
extern char Scene8015AFCC_vtable_8049003C[];
extern char lbl_803FE0C8[];
extern void MemoryManager_TimedFree(void *);
extern void fn_80121210(void);
extern void fn_8013DB9C(void);
extern unsigned char fn_8019083C(int);
extern int fn_801932F8(void);
extern void clStream_setVolume(int, int);
extern void fn_801699D8(int, int);
extern void fn_80169C44(void);

#pragma exceptions on

Scene8015AE3CView *fn_8015AE3C(Scene8015AE3CView *self, short flag) {
    if (self) {
        self->vtable = Scene8015AFCC_vtable_8049003C;
        fn_80121210();
        fn_8013DB9C();
        if (fn_8019083C(1)) {
            clStream_setVolume(1, fn_801932F8());
        }
        if (self->obj2C) {
            self->obj2C->Update();
        }
        if (self->obj30) {
            self->obj30->Update();
        }
        if (self->obj34) {
            delete self->obj34;
        }
        if (self->obj38) {
            delete self->obj38;
        }
        if (self->obj3C) {
            delete self->obj3C;
        }
        if (self->obj40) {
            delete self->obj40;
        }
        if (self->obj24) {
            delete self->obj24;
        }
        fn_801699D8(1, 0);
        fn_80169C44();
        if (self) {
            self->vtable = lbl_803FE0C8;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

#pragma exceptions reset
}

/* ---- formerly game/Scene_8015AFCC.cpp ---- */
#include "game/Scene_8015AFCC_private.h"
extern "C" {
extern PlayerDataRecord g_playerData;
extern const float lbl_806D8394,lbl_806D8398,lbl_806D839C;
extern const float lbl_806D85D0,lbl_806D85D4,lbl_806D85D8,lbl_806D85DC,lbl_806D85E0;
void fn_80121210(); void fn_8013DBF8();
void *fn_801FF00C(int,int); void fn_801FEF34(void *,float,float);
SelectPanel *fn_8020007C(int,int,int);
void InitRumbleController(int); void fn_801699D8(int,int); void SetRumbleMode(int,int,int);
void PreloadResource(int); int Item_GetDescriptorField0(int,int); int Item_GetDescriptorFieldC(int);
unsigned char PlayerData_GetUnlockedItemIdByIndex_U8(int);
unsigned char fn_8019083C(int); int WeatherSystem_PickVariant(int); int fn_801932F8();
void clStream_setVolume(int,int);
}
#pragma exceptions on
Scene8015AFCC::Scene8015AFCC() {
    int i; int itemId; int extra;
    fn_80121210(); fn_8013DBF8();
    active = 0; state = 0; timer = lbl_806D8394; mode = 0;
    driver = 0; player = &g_playerData; flag1c = 0; flag1d = 0; resource = 0x708;
    panel = fn_801FF00C(0,0);
    fn_801FEF34(panel,lbl_806D85D0,lbl_806D85D4);
    panel2 = fn_8020007C(2,0,0);
    panel2->SetPos(lbl_806D85D8,lbl_806D85DC);
    badge = new SelectBadge;
    badge->mode = 0; badge->SetPos(lbl_806D85E0,lbl_806D85DC);
    prompt = new SelectPrompt;
    item = new SelectItem(0);
    character = (signed char)player->variant;
    card = ((unsigned char *)player)[0x19d];
    track = player->prefix[0xc];
    if (character >= 13) character = 0;
    if (character < 0) character = 0;
    driver = new SelectDriver(character,1);
    extraItem = new SelectItem(1);
    kind = player->prefix[0xd];
    valueA = *(unsigned short *)&player->prefix[0xe];
    valueB = *(unsigned short *)&player->prefix[0x10];
    hundredsA = (int)valueA / 100;
    tensA = ((int)valueA - hundredsA*100)/10;
    onesA = (int)valueA - (unsigned char)hundredsA*100 - (unsigned char)tensA*10;
    hundredsB = (int)valueB / 100;
    tensB = ((int)valueB - hundredsB*100)/10;
    onesB = (int)valueB - (unsigned char)hundredsB*100 - (unsigned char)tensB*10;
    for (int i=0;i<4;++i) {
        values[i] = lbl_806D8394;
        arrayA[i] = 0; arrayB[i] = 0; arrayC[i] = 0; arrayD[i] = 0;
    }
    InitRumbleController(1);
    fn_801699D8(0,1); fn_801699D8(1,1); SetRumbleMode(1,2,-1);
    PreloadResource(0x63f); PreloadResource(0x640); PreloadResource(0x642);
    for(i=0;i<5;++i) { PreloadResource(i+0x676); PreloadResource(i+0x671); }
    PreloadResource(0x67f); PreloadResource(0x7cf);
    PreloadResource(Item_GetDescriptorField0(0,0)); PreloadResource(0x7c5);
    for(i=0;i<60;++i) {
        itemId = PlayerData_GetUnlockedItemIdByIndex_U8(i);
        extra = Item_GetDescriptorFieldC(itemId);
        PreloadResource(Item_GetDescriptorField0(itemId,0));
        if (extra >= 0) PreloadResource(extra+0x4f3);
    }
    PreloadResource(0x641); PreloadResource(0x665); PreloadResource(0x666);
    PreloadResource(0x667); PreloadResource(0x668);
    for(i=0;i<7;++i) PreloadResource(i+0x669);
    PreloadResource(0x670);
    for(i=0;i<5;++i) { PreloadResource(i+0x65f); PreloadResource(i+0x65a); }
    PreloadResource(0x664);
    for(i=0;i<10;++i) PreloadResource(i+0x3f7);
    PreloadResource(0x645); PreloadResource(0x644); PreloadResource(0x7db);
    PreloadResource(0x7dc); PreloadResource(0x7f0);
    for(i=0;i<6;++i) PreloadResource(i+0x7dd);
    for(i=0;i<6;++i) PreloadResource(i+0x76c);
    for(i=0;i<12;++i) PreloadResource(i+0x7e4);
    switch(mode) {
    case 0:
        f44 = lbl_806D8394; f50 = lbl_806D8398; f54 = lbl_806D839C;
        { i = track; if(fn_8019083C(1)) clStream_setVolume(1,WeatherSystem_PickVariant(i)); }
        break;
    case 1:
        i=0; f5c=lbl_806D8394; first=i; count=i;
        for(;i<60;++i) {
            if(player->unlockFlags[i]) { ++count; if(first<0) first=i; }
        }
        if(fn_8019083C(1)) clStream_setVolume(1,fn_801932F8());
        break;
    case 3: index=-1; other=0; break;
    case 2: case 4: break;
    }
}
#pragma exceptions reset
