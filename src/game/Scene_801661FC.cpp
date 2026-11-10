#include "game/TestMenuPage.h"
#include "game/Scene_801661FC_private.h"
/* --- owned .rodata 0x80369D78..0x8036A390 (tools/own_data.py) --- */
#pragma force_active on
extern "C" const unsigned int Scene_801661FC_rodata_80369D78[255] = { 0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB };
extern "C" const char lbl_8036A174[] = "clCSSceneTest";
extern "C" const char lbl_8036A184[] = "clSceneInterface";
extern "C" const char lbl_8036A198[] = "clCSPartsTest";
extern "C" const char lbl_8036A1A8[] = "clYTaskInterface";
extern "C" const unsigned int Scene_801661FC_rodata_8036A1BC[10] = { 0x636C4354, 0x61736B49, 0x6E746572, 0x66616365, 0x00000000, 0x636C4353, 0x50617274, 0x73496E65, 0x72666163, 0x65000000 };
extern "C" const char lbl_8036A1E4[] = "clCSPartsRankTest";
extern "C" const char lbl_8036A1F8[] = "clCSPartsGetItemTest";
extern "C" const char lbl_8036A210[] = "static const stCSItemData CSData_ItemData[ SI_END ] = {\n";
extern "C" const unsigned int lbl_8036A24C[12] = { 0x20204954, 0x454D5F44, 0x41544128, 0x20256666, 0x2C256666, 0x2C256666, 0x2C202566, 0x662C2566, 0x662C2566, 0x662C2025, 0x66662029, 0x2C0A0000 };
#pragma force_active reset
extern "C" {
extern char lbl_806D8958[4];
extern int g_cupId;
void GXDrawDone();
void fn_8013DB2C();
void *ItemRes_LookupByKey_Thunk(int);
void fn_8013D738(ParamModel *, float, float);
void fn_8013D660(ParamModel *, float, float);
void fn_8013D634(ParamModel *, float, float, float);
void fn_8013D59C(ParamModel *, float, float, float);
void fn_8013D608(ParamModel *, float, float, float);
void fn_8013D4B0(ParamModel *, float);
void fn_8013DAC8(ParamModel *, int);
void fn_80168A4C(int, const char *, float, float, ...);
unsigned int Item_GetDescriptorField8(unsigned int);
unsigned int Item_GetDescriptorFieldC(unsigned int);
float *fn_8013BEC8(int);
int fn_8013BF70(int, int);
int Item_GetDescriptorField0(int, int);
char *fn_8023DAA8(int);
char *fn_8023D938(int, int);
void fn_8016918C(int, int, float,float,float,float,float,float,float,float,int);
void fn_80169468(int, int, float,float,float,float,float,float,int);
void fn_801685A4(int, const char *, float,float,float,float,float,float,...);
void fn_801681E8(int, const char *, float,float,float,float,...);
void fn_80168B90(int, const char *, float,float,float,float,float,float,...);
}
#pragma readonly_strings on
static const char itemNumberFormat[] = "\203A\203C\203e\203\200\202m\202n %03d";
static const char translateXFormat[] = "\202s\202w\201F%f";
static const char translateYFormat[] = "\202s\202x\201F%f";
static const char translateZFormat[] = "\202s\202y\201F%f";
static const char rotateXFormat[] = "\202q\202w\201F%f";
static const char rotateYFormat[] = "\202q\202x\201F%f";
static const char rotateZFormat[] = "\202q\202y\201F%f";
static const char scaleFormat[] = "\202r\201@\201F%f";
static const char newItemMessage[] = "\220V\202\265\202\242\203A\203C\203e\203\200\202\360\212l\223\276\202\265\202\334\202\265\202\275\201I\201I";
void ParamEditScene::Update() {
    ParamValues *p;
    int next;
    int field8;
    int fieldC;
    int icon8;
    int iconC;
    float *params;
    if (this->quit == 1) { this->done = 1; return; }
    if (InputMgr_GetPlayer(GetInputManager(), 0)->StickRight() > 0.7f) {
        if (this->repeat < 0) this->repeat = 0;
        else if (++this->repeat > 20) this->repeat = 18;
    } else if (InputMgr_GetPlayer(GetInputManager(), 0)->StickLeft() > 0.7f) {
        if (this->repeat > 0) this->repeat = 0;
        else if (--this->repeat < -20) this->repeat = -18;
    } else this->repeat = 0;
    if (InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x400)) {
        if (++this->cursor >= 7) this->cursor = 0;
        this->editRepeat = 0;
    } else {
        float axis = InputMgr_GetPlayer(GetInputManager(), 0)->v2();
        if (axis > 0.2f) {
            if (this->editRepeat < 0) this->editRepeat = 0;
            else if (++this->editRepeat > 20) this->editRepeat = 18;
        } else if (axis < -0.2f) {
            if (this->editRepeat > 0) this->editRepeat = 0;
            else if (--this->editRepeat < -20) this->editRepeat = -18;
        } else this->editRepeat = 0;
    }
    next = this->item;
    if (this->repeat == 1) next = this->item + 1;
    else if (this->repeat == -1) next = this->item - 1;
    if (next != this->item) {
        GXDrawDone();
        fn_8013DB2C();
        if (this->model) { delete this->model; this->model = 0; }
        if (next >= 0x115) this->item = 1;
        else if (next <= 0) this->item = 0x114;
        else this->item = next;
    }
    p = &this->table[this->item];
    float step = 0.05f;
    if (InputMgr_GetPlayer(GetInputManager(), 0)->Held(0x2000)) step = 1.0f;
    if (this->editRepeat == 1 || this->editRepeat == 20) {
        switch (this->cursor) {
        case 0: p->v[0] += step; break;
        case 1: p->v[1] += step; break;
        case 2: p->v[2] += step; break;
        case 3: p->v[3] += step; break;
        case 4: p->v[4] += step; break;
        case 5: p->v[5] += step; break;
        case 6: p->v[6] += step; break;
        }
    }
    if (this->editRepeat == -1 || this->editRepeat == -20) {
        switch (this->cursor) {
        case 0: p->v[0] -= step; break;
        case 1: p->v[1] -= step; break;
        case 2: p->v[2] -= step; break;
        case 3: p->v[3] -= step; break;
        case 4: p->v[4] -= step; break;
        case 5: p->v[5] -= step; break;
        case 6: p->v[6] -= step; break;
        }
    }
    if (p->v[3] < 0.0f) p->v[3] += 360.0f;
    if (p->v[3] >= 360.0f) p->v[3] -= 360.0f;
    if (p->v[4] < 0.0f) p->v[4] += 360.0f;
    if (p->v[4] >= 360.0f) p->v[4] -= 360.0f;
    if (p->v[5] < 0.0f) p->v[5] += 360.0f;
    if (p->v[5] >= 360.0f) p->v[5] -= 360.0f;
    if (!this->model) {
        this->model = new ParamModel(ItemRes_LookupByKey_Thunk(this->item), 1);
        fn_8013D738(this->model, 0.0f, 1.0f);
    }
    if (this->model) {
        fn_8013D660(this->model, 114.0f, 358.0f);
        fn_8013D634(this->model, 0.02f * p->v[0], 0.02f * p->v[1], 0.02f * p->v[2]);
        fn_8013D59C(this->model, 0.017453292f * p->v[3], 0.017453292f * p->v[4], 0.017453292f * p->v[5]);
        float scale = 0.02f * p->v[6];
        fn_8013D608(this->model, scale, scale, scale);
        fn_80168A4C(this->text, lbl_806D8958, 70.0f, 24.0f * (this->cursor + 1) + 50.0f);
        fn_80168A4C(this->text, itemNumberFormat, 100.0f, 50.0f, this->item);
        fn_80168A4C(this->text, translateXFormat, 100.0f, 74.0f, p->v[0]);
        fn_80168A4C(this->text, translateYFormat, 100.0f, 98.0f, p->v[1]);
        fn_80168A4C(this->text, translateZFormat, 100.0f, 122.0f, p->v[2]);
        fn_80168A4C(this->text, rotateXFormat, 100.0f, 146.0f, p->v[3]);
        fn_80168A4C(this->text, rotateYFormat, 100.0f, 170.0f, p->v[4]);
        fn_80168A4C(this->text, rotateZFormat, 100.0f, 194.0f, p->v[5]);
        fn_80168A4C(this->text, scaleFormat, 100.0f, 218.0f, p->v[6]);
        field8 = Item_GetDescriptorField8(this->item);
        fieldC = Item_GetDescriptorFieldC(this->item);
        if (field8 < 0) icon8 = -1;
        else icon8 = field8 + 0x503;
        iconC = fieldC < 0 ? -1 : fieldC + 0x4f3;
        params = fn_8013BEC8(field8);
        fn_8016918C(this->text, 0x8c7, 320.0f, 373.0f, 1.1f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0);
        fn_80169468(this->text, 0x8c9, 114.0f, 373.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0);
        int icon = fn_8013BF70(g_cupId, 0);
        fn_80169468(this->text + 1, icon, 114.0f, 418.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0);
        fn_80169468(this->text, icon8, 313.0f, 389.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0);
        fn_80169468(this->text, iconC, 313.0f, 389.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0);
        icon = Item_GetDescriptorField0(this->item, 0);
        fn_80169468(this->text, icon, 377.0f, 395.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0);
        fn_801685A4(this->text, newItemMessage, 206.0f, 319.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        if (params) {
            char *name = fn_8023DAA8(this->item);
            fn_801681E8(this->text, name, 224.0f, 362.0f, 0.66f, 0.66f, params[0], params[1], params[2], params[3]);
        }
        { char *name = fn_8023D938(this->item, 0);
        fn_80168B90(this->text, name, 416.0f, 362.0f, 1.0f, 1.0f, 1.0f, 1.0f); }
        { char *name = fn_8023D938(this->item, 1);
        fn_80168B90(this->text, name, 416.0f, 382.0f, 1.0f, 1.0f, 1.0f, 1.0f); }
        { char *name = fn_8023D938(this->item, 2);
        fn_80168B90(this->text, name, 416.0f, 402.0f, 1.0f, 1.0f, 1.0f, 1.0f); }
        fn_8013D4B0(this->model, 1.0f);
        fn_8013DAC8(this->model, 0);
    }
}
#pragma readonly_strings reset
#pragma force_active on
extern "C" const unsigned int sdata_806CF750_rodata_8036A308[24] = { 0x636C4353, 0x50617274, 0x73546974, 0x6C655465, 0x73740000, 0x82628267, 0x82608271, 0x82602081, 0x46202573, 0x00000000, 0x82738268, 0x8273826B, 0x82642081, 0x46202564, 0x00000000, 0x826F8260, 0x82718260, 0x826C2081, 0x46202564, 0x00000000, 0x8FCC8D86, 0x81752025, 0x73208176, 0x00000000 };
extern "C" const char lbl_8036A368[] = "clCSPartsSpriteTest";
extern "C" const unsigned int Scene_801670FC_rodata_8036A37C[5] = { 0x83588376, 0x83898343, 0x83674944, 0x20253034, 0x64000000 };
#pragma force_active reset
