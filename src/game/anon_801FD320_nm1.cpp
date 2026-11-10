/*
 * FlowScene base and the card-eject result task @ 0x801FD320..0x801FD924.
 */

#include "game/FlowScene.h"

#include "game/types/FlowController.h"

extern "C" {
extern int lbl_806D19C8;
extern const int lbl_806DA848;
extern int lbl_806D19D0;
extern int lbl_806D19D4;

extern const float lbl_806DA830;
extern const float lbl_806DA834;
extern const float lbl_806DA838;
extern const float lbl_806DA83C;
extern unsigned char g_playerData[];
void fn_8020A7CC(FlowFader *fader, int a, int b, int c);
void *fn_801F8E58(void);
void fn_801F8A34(void *a, TextManager *tm, int mode);
void card_eject_init(void);
void fn_801D7610(unsigned char *data, int mode);
}


/* Original card-error type names and localized messages share one pool. */
#include "game/types/shared_data.h"
#ifndef __MWERKS__ /* the names other units use (tools/alias_census.py) */
#define cardEjectBaseName lbl_803BFE68
#define cardEjectName lbl_803BFE48
#define cardEjectTaskName lbl_803BFE54
#endif
SHARED_STATIC const char cardEjectName[0xc] = "clMnCardErr";
SHARED_STATIC const char cardEjectTaskName[0x11] = "clYTaskInterface";
SHARED_STATIC const char cardEjectBaseName[0x12] = "clMnTaskInterface";
static const char callAttendantJ[0x15] = "\214W\210\365\202\360\214\304\202\361\202\305\202\255\202\276\202\263\202\242";
static const char callAttendantE[0x19] = "Please call an attendant";
static const char cardEmptyJ[0x13] = "\203J\201[\203h\202\252\202\240\202\350\202\334\202\271\202\361";
static const char cardEmptyE[0xb] = "CARD EMPTY";
static const char cardErrorJ[0x14] = "\203G\203\211\201[\203R\201[\203h\201FE%02d";
static const char cardErrorE[0x12] = "ERROR CODE\201FE%02d";

#include "game/types/CardEjectTask.h"

CardEjectTask::CardEjectTask(int id) : FlowTask(id) {
    float x;
    texts = new TextManager[2];
    texts[0].visible = 1;
    if (isJapanese() == 0) {
        x = lbl_806DA830;
        TexMgr_SetTexture(&texts[0], callAttendantJ);
    } else {
        x = lbl_806DA834;
        fn_801F8FCC(&texts[0], 1);
        TexMgr_SetTexture(&texts[0], callAttendantE);
        fn_801F8E90(&texts[0]);
    }
    fn_801F93EC(&texts[0], x, lbl_806DA830);
    texts[1].visible = 1;
    if (lbl_806D19D4 == 5) {
        if (isJapanese() == 0) {
            x = lbl_806DA838;
            TexMgr_SetTexture(&texts[1], cardEmptyJ);
        } else {
            x = lbl_806DA834;
            fn_801F8FCC(&texts[1], 1);
            TexMgr_SetTexture(&texts[1], cardEmptyE);
            fn_801F8E90(&texts[1]);
        }
        fn_801F93EC(&texts[1], x, lbl_806DA83C);
    } else {
        if (isJapanese() == 0) {
            x = lbl_806DA830;
            TexMgr_SetTexture(&texts[1], cardErrorJ, lbl_806D19D0);
        } else {
            x = lbl_806DA834;
            fn_801F8FCC(&texts[1], 1);
            TexMgr_SetTexture(&texts[1], cardErrorE, lbl_806D19D0);
            fn_801F8E90(&texts[1]);
        }
        fn_801F93EC(&texts[1], x, lbl_806DA83C);
    }
}

