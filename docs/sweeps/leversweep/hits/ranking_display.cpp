#include "game/RankingFlow_private.h"
#include "game/clFlowCourse.h"
#include "game/singleton.h"
extern "C" {
extern const char lbl_8039C5BC[];
extern const float ranking_display_rodata_8039C55C[];
extern const float lbl_806D9FC4, lbl_806D9FC8, lbl_806D9FCC, lbl_806D9FD0, lbl_806D9FD4;
extern const float lbl_806D9FD8, lbl_806D9FDC, lbl_806D9FE0, lbl_806D9FE4, lbl_806D9FE8;
extern const char lbl_806D9FEC[4];
extern int g_cupId, g_longRoundFlag, g_reverseRoundFlag, g_localPcbRole;
extern const char lbl_806D9F70[];
extern const char ranking_display_rodata_8039C384[];
extern const char lbl_806D9F78[];
extern const char lbl_806D9F80[];
extern const char lbl_806D9F88[];
extern const char ranking_display_rodata_8039C390[];
extern const char ranking_display_rodata_8039C39C[];
extern const char ranking_display_rodata_8039C3A8[];
extern const char ranking_display_rodata_8039C3B4[];
extern const char ranking_display_rodata_8039C3C0[];
extern const char ranking_display_rodata_8039C3CC[];
extern const char ranking_display_rodata_8039C3D8[];
extern const char ranking_display_rodata_8039C3E4[];
extern const char ranking_display_rodata_8039C3F0[];
extern const char ranking_display_rodata_8039C3FC[];
extern const char ranking_display_rodata_8039C408[];
extern const char ranking_display_rodata_8039C414[];
extern const char ranking_display_rodata_8039C420[];
extern const char ranking_display_rodata_8039C42C[];
extern const char lbl_806D9F90[];
extern const char ranking_display_rodata_8039C438[];
extern const char lbl_806D9F98[];
extern const char ranking_display_rodata_8039C444[];
extern const char lbl_806D9FA0[];
extern const char ranking_display_rodata_8039C450[];
extern const char ranking_display_rodata_8039C45C[];
static const char *rankingEnglish[13] = {
    lbl_806D9F70, ranking_display_rodata_8039C384, lbl_806D9F78, lbl_806D9F80,
    lbl_806D9F88, ranking_display_rodata_8039C390, ranking_display_rodata_8039C39C, ranking_display_rodata_8039C3A8,
    ranking_display_rodata_8039C3B4, ranking_display_rodata_8039C3C0, ranking_display_rodata_8039C3CC, ranking_display_rodata_8039C3D8,
    ranking_display_rodata_8039C3E4
};
static const char *rankingJapanese[13] = {
    ranking_display_rodata_8039C3F0, ranking_display_rodata_8039C3FC, ranking_display_rodata_8039C408, ranking_display_rodata_8039C414,
    ranking_display_rodata_8039C420, ranking_display_rodata_8039C42C, lbl_806D9F90, ranking_display_rodata_8039C438,
    lbl_806D9F98, ranking_display_rodata_8039C444, lbl_806D9FA0, ranking_display_rodata_8039C450,
    ranking_display_rodata_8039C45C
};

#include "game/RankingDisplayDispatch_private.h"
extern const char ranking_display_data_806CFE78[], ranking_display_data_806CFE80[];
void *fn_801D1D9C(void *, short);
int fn_801D1890(void *);
void fn_801D1800(void *);
#pragma force_active on
static RankingBaseRecord rankingBase = {ranking_display_data_806CFE78, 0, 0};
static RankingDispatch rankingDispatch = {
    ranking_display_data_806CFE80, 0, fn_801D1D9C, fn_801D1890, fn_801D1800
};
#pragma force_active reset

extern void *lbl_806D10A0;
void CObj_LoadIntoGX(void *, const float *);
void CObj_ApplyViewport(void *, const float *);
void SetSyncTarget(int);
void SetupBgSprites(unsigned char);
short fn_801D8DB4(int, int, int);
short fn_801D8DA0(int);
void Sprite_SetAnimParam(CourseSprite *, int, short);
const char *fn_8013C100(int, int, int);
void fn_801F9014(void *, const char *, ...);
unsigned char IsCardValid();
unsigned char fn_802315F8(int);
const char *get_title_name(void *, int, int, int, int);
unsigned char *PcbSlot_GetByIndex(int);
}
#pragma cplusplus off
static inline const char *RankingCharacterName(int character) {
    if (isJapanese() == 0) return rankingEnglish[character];
    return rankingJapanese[character];
}
#pragma cplusplus reset
struct RankingWorld {
    char data[0x3084];
    RankingWorld(const char *);
};
struct RankingLights {
    char data[0x28];
    RankingLights(const char *, int);
};
struct RankingLabel : RankingAnim {
    virtual void _keyLabel();
    short resource;
    short pad8A;
    int layer;
    unsigned char flag;
    char pad91[3];
    RankingLabel(short id, float y) : RankingAnim(0, 20), resource(id), layer(7), flag(0) {
        tracks[3].from = lbl_806D9FC8;
        tracks[3].to = lbl_806D9FC8;
        tracks[3].speed = lbl_806D9FAC;
        tracks[3].time = lbl_806D9FA8;
        tracks[3].value = lbl_806D9FC8;
        tracks[3].active = 1;
        tracks[4].from = y;
        tracks[4].to = y;
        tracks[4].speed = lbl_806D9FAC;
        tracks[4].time = lbl_806D9FA8;
        tracks[4].value = y;
        tracks[4].active = 1;
    }
};
struct RankingText : RankingAnim {
    virtual void _keyText();
    TextManager text;
    int layer;
    unsigned char red, green, blue;
    char pad2BF;
    float scale;
    RankingText(const char *str) : RankingAnim(0, 20), text() {
        tracks[3].from = lbl_806D9FC8;
        tracks[3].to = lbl_806D9FC8;
        tracks[3].speed = lbl_806D9FAC;
        tracks[3].time = lbl_806D9FA8;
        tracks[3].value = lbl_806D9FC8;
        tracks[3].active = 1;
        tracks[4].from = lbl_806D9FD0;
        tracks[4].to = lbl_806D9FD0;
        tracks[4].speed = lbl_806D9FAC;
        tracks[4].time = lbl_806D9FA8;
        tracks[4].value = lbl_806D9FD0;
        tracks[4].active = 1;
        text.visible = 1;
        fn_801F8FCC(&text, 1);
        fn_801F9014(&text, str);
        fn_801F8E90(&text);
        red = 255; green = 255; blue = 255;
        scale = lbl_806D9FAC;
        layer = 7;
    }
};
struct RankingFlow;
struct RankingPanel {
    char data[0x7A8];
    RankingPanel(RankingFlow *, int, unsigned char *, const char *, int, const char *);
    void Init(int, int, int, int, unsigned char, int, const char *, int, const char *, int,
              RankingWorld *, RankingLights *, float, float, float);
};
#include "game/RankingDisplayBase_private.h"
struct RankingFlow : RankingDisplayBase {
    int state;
    RankingFlowList list;
    RankingPanel *players[4];
    RankingWorld *world;
    RankingLights *lights;
    int count, delay, timer;
    unsigned char phase;
    RankingFlow();
};
inline RankingPanel::RankingPanel(RankingFlow *owner, int i, unsigned char *slot, const char *name,
                                  int number, const char *title) {
    int label = !fn_802315F8(i) ? -1 : ((*(unsigned short *)(slot + 6) >> 5) & 15);
    unsigned int flag = (slot[6] >> 1) & 3;
    int variant = flag >= 2;
    int position = owner->count;
    int y = position / 2 == 0 ? 206 : 346;
    int target = (position & 1) == 0 ? 174 : 466;
    Init(15, position, slot[4] & 15, (slot[4] >> 4) & 15, variant != 0, (slot[6] >> 6) & 3,
        name, number, title, label, owner->world, owner->lights,
        (float)((position & 1) == 0 ? -146 : 768), (float)target, (float)y);
}
static inline RankingFlowIter RankingInsertAt(RankingFlowList *list, const RankingFlowIter &last, RankingAnim *const &entry) {
    return DoublyLinkedList_PushBefore(list, &last, &entry);
}
static inline void RankingAdd(RankingFlowList *list, RankingAnim *const &entry) {
    RankingInsertAt(list, RankingFlowIter(list->End()), entry);
}
static inline void SetTrack(RankingFlowTrack *t, float from, float to, float speed) {
    t->from = from; t->to = to; t->speed = speed; t->time = lbl_806D9FA8; t->value = from; t->active = 1;
}
static inline void *RankingTitleSource() {
    return SINGLETON_INSTANCE(lbl_806D10A0);
}
static inline bool RankingIsLongRound() {
    return g_longRoundFlag != 0;
}
#pragma inline_max_size(10000)
RankingFlow::RankingFlow() : RankingDisplayBase(), list() {
    RankingFlowTrack *t;
    world = new RankingWorld(lbl_8039C5BC);
    lights = new RankingLights(lbl_8039C5BC, 0);
    count = 0;
    delay = 300;
    timer = 0;
    phase = 0;
    float pos[3];
    pos[0] = lbl_806D9FA8; pos[1] = lbl_806D9FA8; pos[2] = lbl_806D9FC4;
    CObj_LoadIntoGX(world, pos);
    pos[0] = lbl_806D9FA8; pos[1] = lbl_806D9FA8; pos[2] = lbl_806D9FA8;
    CObj_ApplyViewport(world, pos);
    SetSyncTarget(0x27);
    SetupBgSprites(0);
    state = -1;
    CourseSprite *sprite = new CourseSprite(0x14F, 1, 0);
    bool longRound = RankingIsLongRound();
    Sprite_SetAnimParam(sprite, 0xA9C, fn_801D8DB4(g_cupId, longRound, 0));
    Sprite_SetAnimParam(sprite, 0xA9D, fn_801D8DB4(g_cupId, longRound, 1));
    sprite->x = lbl_806D9FC8;
    sprite->y = lbl_806D9FCC;
    sprite->layer = 0;
    RankingAdd(&list, new RankingAnim((RankingSprite *)sprite, 0));
    RankingAnim *entry;
    if (g_reverseRoundFlag == 1) {
        CourseSprite *mirror = new CourseSprite(0x9E, 1, ranking_display_rodata_8039C55C[(g_cupId-1)*2+g_longRoundFlag],
            lbl_806D9FD0, lbl_806D9FAC, lbl_806D9FAC, lbl_806D9FA8, lbl_806D9FAC);
        mirror->layer = 6;
        entry = new RankingAnim((RankingSprite *)mirror, 20);
        t = &entry->tracks[0];
        t->from = lbl_806D9FA8;
        t->to = lbl_806D9FAC;
        t->speed = lbl_806D9FD4;
        t->time = lbl_806D9FA8;
        t->value = lbl_806D9FA8;
        t->active = 1;
        RankingAdd(&list, entry);
    }
    entry = new RankingLabel(fn_801D8DA0(g_cupId), lbl_806D9FD8);
    SetTrack(&entry->tracks[0], lbl_806D9FA8, lbl_806D9FAC, lbl_806D9FD4);
    RankingAdd(&list, entry);
    entry = new RankingLabel(0x17AE, lbl_806D9FDC);
    SetTrack(&entry->tracks[1], lbl_806D9FA8, lbl_806D9FE0, lbl_806D9FE4);
    SetTrack(&entry->tracks[2], lbl_806D9FAC, lbl_806D9FAC, lbl_806D9FAC);
    SetTrack(&entry->tracks[0], lbl_806D9FA8, lbl_806D9FAC, lbl_806D9FD4);
    RankingAdd(&list, entry);
    RankingText *text = new RankingText(fn_8013C100(g_cupId, g_longRoundFlag, -1));
    text->layer = 5;
    RankingAdd(&list, text);
    /* The entry color and delay are supplied by this constructor variant. */
    entry = new RankingFade(10, 60, 40, 10, 1);
    SetTrack(&entry->tracks[0], lbl_806D9FA8, lbl_806D9FE8, lbl_806D9FD4);
    RankingAdd(&list, entry);
    for (int i = 0; i < 4; ++i) {
        players[i] = 0;
        unsigned char *slot = PcbSlot_GetByIndex(i);
        if ((int)((slot[0] >> 4) & 7) == g_localPcbRole) {
            int character = (slot[4] >> 4) & 15;
            const char *name = RankingCharacterName(character);
            if ((slot[3] >> 7) & 1) name = (const char *)(slot + 0x16);
            int number = *(unsigned short *)(slot + 0x22);
            void *titleSource = RankingTitleSource();
            const char *title = get_title_name(titleSource, slot[0x26], slot[0x27], (slot[4] >> 4) & 15, slot[0x28]);
            if (!IsCardValid()) title = lbl_806D9FEC;
            RankingPanel *panel = new RankingPanel(this, i, slot, name, number, title);
            players[i] = panel;
            RankingAdd(&list, (RankingAnim *)panel);
            ++count;
        }
    }
}
typedef char RankingFlowSizeCheck[sizeof(RankingFlow) == 0x3C ? 1 : -1];
typedef char RankingTextSizeCheck[sizeof(RankingText) == 0x2C4 ? 1 : -1];
typedef char RankingLabelSizeCheck[sizeof(RankingLabel) == 0x94 ? 1 : -1];
