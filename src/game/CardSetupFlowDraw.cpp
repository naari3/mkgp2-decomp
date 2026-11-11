#include "game/FlowScene.h"
#include "game/types/clSceneInterface.h"
struct SetupReceipt;

struct PrintKart {
    int busy, layout;
    char pad08[0x18];
    unsigned char visible, active;
    char pad22[0x68 - 0x22];
    PrintKart();
    ~PrintKart();
};
extern "C" void fn_801D9F88(PrintKart *, short);
struct PrintKartHolder {
    PrintKart *p;
    PrintKartHolder(PrintKart *q) : p(q) {}
    ~PrintKartHolder() throw() { fn_801D9F88(p, 1); }
};
struct PrintSprite { ~PrintSprite(); };
template <class T> struct PrintOwn {
    T *p;
    ~PrintOwn() throw() { delete p; }
};
template <class T> struct PrintVecData {
    int cap, count;
    T *data;
    ~PrintVecData() { if (data) operator delete(data); }
};
template <class T> struct PrintVecBase : PrintVecData<T> { ~PrintVecBase() {} };
template <class T> struct PrintVec : PrintVecBase<T> {
    ~PrintVec() {}
    T *begin() { return this->data; }
    T *end() { return this->data + this->count; }
};
struct PrintKeyData { int cap, count; void *data; ~PrintKeyData(); };
struct PrintKeyMid : PrintKeyData { ~PrintKeyMid() {} };
struct PrintKeyVec : PrintKeyMid { ~PrintKeyVec() {} };
struct PrintKeyboard {
    unsigned char english;
    PrintKeyVec groups;
    char tail[0x40 - 0x10];
};
struct SetupName {
    PrintKeyboard keyboard;
    PrintOwn<PrintSprite> cursor;
    char *bufs[4][15];
    int phase;
    char pad138[0x10];
    PrintVec<VObject *> objs;
    SetupName(bool english);
    ~SetupName();
    unsigned char Done() { return phase == 5 ? true : false; }
};
struct PrintMessage { ~PrintMessage(); };
extern "C" {
extern PrintMessage *lbl_806D1A88;
extern const int lbl_806D1AB0;
void fn_801699D8(int, int);
}
static inline void SetInput(unsigned char enabled) {
    InputState *in = GetInput();
    in->enabled = enabled;
    in->held = 0;
    in->edge = 0;
}
inline SetupName::~SetupName() {
    for (VObject **it = objs.begin(); it != objs.end(); it++) delete *it;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 15; j++) operator delete(bufs[i][j]);
    }
    SetInput(0);
    if (lbl_806D1A88) {
        delete lbl_806D1A88;
        lbl_806D1A88 = 0;
    }
    fn_801699D8(0, 0);
    fn_801699D8(1, 0);
}
struct clRsCard : clSceneInterface {
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> fader;
    int state, selection;
    SetupName *name;
    PrintKartHolder kart;
    SetupReceipt *receipt;
    clRsCard();
    ~clRsCard();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    void Receipt();
    void Result();
    void Name();
    void Select();
    void Initial();
};
struct SetupReceipt { int phase; char pad[0x1C]; unsigned char accepted; char tail[15]; SetupReceipt(int); unsigned char Done() { return phase == 5 ? true : false; } };
struct SetupDialog : FlowTask { char pad[0x48]; SetupDialog(int, int); };
struct SetupChoiceView { char pad[0x20]; int result; int selection; };
extern "C" {
extern char CardSetupFlowSelect_data_806D0920[8], lbl_806D0900[8], lbl_806D08F8[8], lbl_806D0910[8], lbl_806D0908[8];
void *fn_80271340(void *, int, const void *, const void *, int);
void fn_801FEF18(void *, int);
void fn_80201148(void *);
void fn_801FFFF4(void *);
void fn_802043B8(FlowSceneList *, int);
void PlayStats_AccumulatePlayTime(int);
void *ItemDisplay_GetOrCreate();
void ItemDisplay_Start(void *, int);
void fn_8020AAD4(void *);
void fn_801BDB60(SetupName *);
void fn_801BE170(SetupName *);
void fn_801D9A2C(PrintKart *);
void HSD_StateInvalidate(int);
void fn_8020F3F0();
void fn_8020F38C(int);
void fn_8020F35C();
void card_force_backup_now();
void PreloadResource(int);
}
struct CardPrintFlow : FlowTask {
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> fader;
    VHolder<PrintKart> kart;
    int phase;
    int error;
    virtual void _key4();
    ~CardPrintFlow();
};
extern "C" {
void fn_801D919C(PrintKart *);
void clFlowKart_SetupTextLayout(PrintKart *, int);
void fn_801D9B70(PrintKart *, int);
unsigned char fn_8020F278();
unsigned char fn_8020F280();
unsigned char fn_8020F288();
int Sci2Card_GetPrintErrorCode();
int fn_8020F270();
int fn_8020F268();
unsigned char card_is_ejected();
int card_rw_get_substate();
void fn_8024B924(CardPrintFlow *);
void fn_8024B77C(CardPrintFlow *);
void DebugPrintf(const char *, ...);
/* read-only for the card flow views (only CardPrintConfig writes it, with its own
   non-const declaration); const lets GC/2.6 hoist its load over self-> stores. */
extern const int lbl_806D1AB0;
}
struct SetupPrintTask : FlowTask {
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> fader;
    PrintKartHolder panel;
    int phase, error;
    virtual void Key();
    SetupPrintTask() : FlowTask(3), list(new SceneListImpl), fader(new FlowFaderI), panel(new PrintKart), phase(0) {
        PreloadResource(0x1ECD);
        PreloadResource(0x72F);
        PreloadResource(0x734);
        fader.p->Set(0, lbl_806D1AB0, (short)lbl_806D1AB0);
        panel.p->visible = 1;
        panel.p->active = 0;
        if (fn_8020F280() == 1) clFlowKart_SetupTextLayout((PrintKart *)panel.p, 2);
        else clFlowKart_SetupTextLayout((PrintKart *)panel.p, 5);
        fn_8020F3F0();
        fn_8020F38C(1);
        fn_8020F35C();
    }
};


void clRsCard::Draw() {
    if (!this->done) {
        if (this->state == 4) fn_801BDB60(this->name);
        this->list.p->Draw();
        fn_801D9A2C(this->kart.p);
        HSD_StateInvalidate(-1);
    }
}

extern "C" {


void fn_801BB6D4(SetupReceipt *);
}
void clRsCard::Update() {
    if (!this->done) {
        InputState *input = GetInput();
        switch (this->state) {
        case 0: Initial(); break;
        case 2:
            this->fader.p->Step();
            if (this->fader.p->Done() || input->held == 1) {
                fn_801D919C(this->kart.p);
                this->state = 13;
            }
            break;
        case 3: Select(); break;
        case 4: Name(); break;
        case 5: Result(); break;
        case 6:
            if (!fn_801F4DC0(this->list.p, 3)) this->state = 13;
            break;
        case 12: Receipt(); break;
        case 13: {
            FlowTask *task = fn_801F4DC0(this->list.p, 6);
            if (task) fn_80201148(fn_80271340(task, 0, lbl_806D0910, lbl_806D08F8, 0));
            task = fn_801F4DC0(this->list.p, 5);
            if (task) fn_801FFFF4(fn_80271340(task, 0, lbl_806D0908, lbl_806D08F8, 0));
            fn_802043B8(this->list.p, 4);
            this->state = 14;
            fn_8020AAD4(ItemDisplay_GetOrCreate());
            break;
        }
        case 14:
            if (this->list.p->entries.count <= 0 && this->kart.p->busy == 0) {
                this->done = 1;
                this->state = -1;
            }
            break;
        }
        this->list.p->Update();
        if (this->receipt) fn_801BB6D4(this->receipt);
        fn_801D9B70(this->kart.p, 0);
    }
}


extern "C" {
void fn_801BBAF0(SetupReceipt *);
void fn_801BB940(SetupReceipt *, int);
int Sci2Card_GetUnpackStatusCode();
unsigned char Sci2Card_GetReceiptTestFlag();
}
void clRsCard::Receipt() {
    if (!this->receipt) this->receipt = new SetupReceipt(1);
    fn_801BBAF0(this->receipt);
    if (this->receipt->Done() == 1) {
        if (this->receipt->accepted == 1) {
            if (Sci2Card_GetUnpackStatusCode() == 5) {
                FlowSceneList *list = this->list.p;
                fn_801F4DF0(list, new SetupDialog(1, 2), 40);
                if (Sci2Card_GetReceiptTestFlag()) {
                    this->fader.p->Set(0, lbl_806D1AB0, (short)lbl_806D1AB0);
                    this->state = 2;
                } else this->state = 5;
            } else {
                FlowSceneList *list = this->list.p;
                fn_801F4DF0(list, new SetupPrintTask, 0);
                this->state = 6;
            }
        } else this->state = 13;
        fn_801BB940(this->receipt, 1);
        this->receipt = 0;
    }
}


#pragma inline_max_size(1000)
#include "CardSetupFlowResultPlayerView.h"
extern "C" { extern ResultPlayerSnapshot g_playerData, SetCourseParams_bss_805D275C; extern char CardSetupFlowResult_data_806D0928[8]; }
void clRsCard::Result() {
    FlowTask *task = fn_801F4DC0(this->list.p, 2);
    if (task) {
        this->selection = ((SetupChoiceView *)fn_80271340(task, 0, CardSetupFlowResult_data_806D0928, lbl_806D08F8, 0))->selection;
        int result = ((SetupChoiceView *)fn_80271340(task, 0, CardSetupFlowResult_data_806D0928, lbl_806D08F8, 0))->result;
        task = fn_801F4DC0(this->list.p, 4);
        if (task) fn_801FEF18(fn_80271340(task, 0, lbl_806D0900, lbl_806D08F8, 0), result);
    } else {
        task = fn_801F4DC0(this->list.p, 6);
        if (task) fn_80201148(fn_80271340(task, 0, lbl_806D0910, lbl_806D08F8, 0));
        fn_802043B8(this->list.p, 4);
        task = fn_801F4DC0(this->list.p, 5);
        if (task) fn_801FFFF4(fn_80271340(task, 0, lbl_806D0908, lbl_806D08F8, 0));
        if (this->selection == 0) {
            FlowSceneList *list = this->list.p;
            fn_801F4DF0(list, new SetupPrintTask, 0);
            this->state = 6;
        } else if ((int)g_playerData.byte1D9 == 2) {
            this->state = 13;
        } else {
            ResultPlayerSnapshot *player = &g_playerData;
            *player = SetCourseParams_bss_805D275C;
            FlowSceneList *list = this->list.p;
            fn_801F4DF0(list, new SetupPrintTask, 0);
            this->state = 6;
        }
    }
}

void clRsCard::Name() {
    fn_801BE170(this->name);
    if (this->name->Done() == 1) {
        FlowSceneList *list = this->list.p;
        fn_801F4DF0(list, new SetupPrintTask, 0);
        this->state = 6;
        card_force_backup_now();
        fn_8020AAD4(ItemDisplay_GetOrCreate());
        fn_8020F3F0();
    }
}

void clRsCard::Select() {
    FlowTask *task = fn_801F4DC0(this->list.p, 1);
    if (task) {
        this->selection = ((SetupChoiceView *)fn_80271340(task, 0, CardSetupFlowSelect_data_806D0920, lbl_806D08F8, 0))->selection;
        int result = ((SetupChoiceView *)fn_80271340(task, 0, CardSetupFlowSelect_data_806D0920, lbl_806D08F8, 0))->result;
        task = fn_801F4DC0(this->list.p, 4);
        if (task) fn_801FEF18(fn_80271340(task, 0, lbl_806D0900, lbl_806D08F8, 0), result);
    } else {
        task = fn_801F4DC0(this->list.p, 6);
        if (task) fn_80201148(fn_80271340(task, 0, lbl_806D0910, lbl_806D08F8, 0));
        fn_802043B8(this->list.p, 4);
        task = fn_801F4DC0(this->list.p, 5);
        if (task) fn_801FFFF4(fn_80271340(task, 0, lbl_806D0908, lbl_806D08F8, 0));
        fn_802043B8(this->list.p, 1);
        PlayStats_AccumulatePlayTime(1);
        if (this->selection == 0) {
            this->state = 4;
            ItemDisplay_Start(ItemDisplay_GetOrCreate(), 0x1AD8);
        } else this->state = 13;
    }
}

extern "C" {
unsigned char Sci2Card_GetByteFlag1224();
unsigned char Sci2Card_GetReceiptTestFlag();
unsigned char ServiceValue_Get();
int Sci2Card_GetUnpackStatusCode();

extern int lbl_806D19B8;
FlowTask *fn_801FC1E0(int);
}
void clRsCard::Initial() {
    if (!Sci2Card_GetByteFlag1224()) {
        if (ServiceValue_Get()) {
            this->state = 2;
            int duration = lbl_806D1AB0;
            this->fader.p->Set(0, duration, (short)duration);
            clFlowKart_SetupTextLayout(this->kart.p, 6);
        } else if (Sci2Card_GetReceiptTestFlag()) {
            this->state = 2;
            int duration = lbl_806D1AB0;
            this->fader.p->Set(0, duration, (short)duration);
            clFlowKart_SetupTextLayout(this->kart.p, 7);
        } else {
            lbl_806D19B8 = 5;
            FlowSceneList *list = this->list.p;
            fn_801F4DF0(list, fn_801FC1E0(1), 40);
            ItemDisplay_Start(ItemDisplay_GetOrCreate(), 0x1AD5);
            this->state = 3;
        }
    } else if ((int)g_playerData.byte1D9 != 2) this->state = 12;
    else if (Sci2Card_GetUnpackStatusCode() == 5) {
        if (Sci2Card_GetReceiptTestFlag()) {
            FlowSceneList *list = this->list.p;
            fn_801F4DF0(list, new SetupDialog(1, 2), 40);
            this->fader.p->Set(0, lbl_806D1AB0, (short)lbl_806D1AB0);
            this->state = 2;
        } else {
            FlowSceneList *list = this->list.p;
            fn_801F4DF0(list, new SetupDialog(1, 2), 40);
            this->state = 5;
        }
    } else {
        FlowSceneList *list = this->list.p;
        fn_801F4DF0(list, new SetupPrintTask, 0);
        this->state = 6;
    }
}


void clRsCard::Destroy() { delete this; }
extern "C" clRsCard *fn_8024B0D8() { return new clRsCard; }
clRsCard::~clRsCard() {
    if (GetInput()) SetInput(0);
    delete name;
    fn_801F4D3C(list.p);
}
clRsCard::clRsCard() : list(new SceneListImpl), fader(new FlowFaderI),
    state(0), selection(0), name(0), kart(new PrintKart), receipt(0) {
    if (GetInput()) SetInput(1);
    fader.p->Set(0, lbl_806D1AB0, (short)lbl_806D1AB0);
    name = new SetupName(!isJapanese());
    kart.p->visible = 1;
    kart.p->active = 0;
}

extern "C" void fn_8024B544(CardPrintFlow *self) {
    fn_801D9A2C(self->kart.p);
}

extern "C" {
extern const char lbl_803EFDE8[], lbl_803EFE0C[];

void fn_8024B568(CardPrintFlow *self) {
    InputState *input = GetInput();
    switch (self->phase) {
    case 0:
        if (!fn_8020F288()) DebugPrintf(lbl_803EFDE8);
        else { DebugPrintf(lbl_803EFE0C); self->phase = 7; }
        break;
    case 7: fn_8024B924(self); break;
    case 8:
        if (card_rw_get_substate() == 5) {
            fn_801D919C(self->kart.p);
            self->fader.p->Set(0, lbl_806D1AB0, (short)lbl_806D1AB0);
            self->phase = 9;
        }
        break;
    case 9:
        self->fader.p->Step();
        if (self->fader.p->Done()) {
            fn_801D919C(self->kart.p);
            self->phase = 10;
        }
        break;
    case 10:
        if (self->kart.p->busy == 0) {
            if ((signed char)g_playerData.byte198 <= 0) {
                clFlowKart_SetupTextLayout(self->kart.p, 8);
                self->fader.p->Set(0, lbl_806D1AB0, (short)lbl_806D1AB0);
                self->phase = 11;
            } else { fn_801D919C(self->kart.p); self->phase = 14; }
        }
        break;
    case 11:
        self->fader.p->Step();
        if (self->fader.p->Done() || input->held == 1) {
            fn_801D919C(self->kart.p);
            self->phase = 14;
        }
        break;
    case 14:
        if (self->kart.p->busy == 0) { self->field0C = 1; self->phase = -1; }
        break;
    case -1: fn_8024B77C(self); break;
    }
    fn_801D9B70(self->kart.p, 0);
}
}
