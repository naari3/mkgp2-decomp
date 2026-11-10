/*
 * Shared menu constants: .rodata 803BE6C0..803BED88 and
 * .data 804E53B0..804E5430. Defining the original pools here lets MWCC
 * retain one base register for each pool throughout the overlay.
 * String arrays include their terminators; inter-string gaps are alignment.
 */
#define DebugOverlay_RaceConfig_rodata_803BE6C0 lbl_803BE6C0_legacy_declaration
#include "game/RaceConfig801FPrivate.h"
#undef DebugOverlay_RaceConfig_rodata_803BE6C0

extern "C" {
extern const float DebugOverlay_RaceConfig_rodata_803BE6C0[255] = {
    1.0f, 0.699999988079071f, 0.8999999761581421f, 0.0f, 0.0f, 500.0f, 66.66667f,
    1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f,
    1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f,
    1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f,
    1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f,
    1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f,
    1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f,
    1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f,
    1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f,
    1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f,
    1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f,
    1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f,
    1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 83.333336f,
    1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f,
    83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f,
    1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f,
    83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f,
    1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f,
    83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f,
    1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f,
    83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f,
    1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f,
    83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f,
    1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f,
    83.333336f, 5000.0f, 83.333336f,
};
extern const char lbl_803BEABC[17] = "clEzTopInterface";
extern const char lbl_803BEAD0[17] = "clSceneInterface";
extern const char lbl_803BEAE4[9] = "STRAIGHT";
extern const char lbl_803BEAF0[9] = "ORIGINAL";
extern const char lbl_803BEAFC[18] = "ORIGINAL ENHANCED";
extern const char lbl_803BEB10[11] = "THROWFRONT";
extern const char lbl_803BEB1C[10] = "THROWBACK";
extern const char lbl_803BEB28[11] = "GRAND PRIX";
extern const char lbl_803BEB34[12] = "TIME ATTACK";
extern const char lbl_803BEB40[10] = "INTRUSION";
extern const char lbl_803BEB4C[16] = "ACCEL And BRAKE";
extern const char lbl_803BEB5C[16] = "ACCEL Add BRAKE";
extern const char lbl_803BEB6C[13] = "DOUBLE ACCEL";
extern const char *const lbl_803BEB7C[3] = {lbl_803BEB4C, lbl_803BEB5C, lbl_803BEB6C};
extern const char lbl_803BEB88[15] = "clEzTopForText";
extern const char lbl_803BEB98[24] = "stage       : %02d : %s";
extern const char lbl_803BEBB0[24] = "stage type  : %02d : %s";
extern const char lbl_803BEBC8[24] = "direction   : %02d : %s";
extern const char lbl_803BEBE0[24] = "time zone   : %02d : %s";
extern const char lbl_803BEBF8[24] = "play chara  : %02d : %s";
extern const char lbl_803BEC10[24] = "kart type   : %02d : %s";
extern const char lbl_803BEC28[24] = "game mode   : %02d : %s";
extern const char lbl_803BEC40[30] = "enemy max   : %02d : MAX %02d";
extern const char lbl_803BEC60[24] = "time count  : %02d : %s";
extern const char lbl_803BEC78[32] = "round       : %02d : Round %02d";
extern const char lbl_803BEC98[24] = "class       : %02d : %s";
extern const char lbl_803BECB0[25] = "jump type   : %02d : %s\n";
extern const char lbl_803BECCC[25] = "EnemyLevel  : %02d : %s\n";
extern const char lbl_803BECE8[28] = "Item-0      :%03d : %s : %s";
extern const char lbl_803BED04[28] = "Item-1      :%03d : %s : %s";
extern const char lbl_803BED20[28] = "Item-2      :%03d : %s : %s";
extern const char lbl_803BED3C[19] = "[SELECT ITEM NAME]";
extern const char lbl_803BED50[11] = "Item0 : %s";
extern const char lbl_803BED5C[11] = "Item1 : %s";
extern const char lbl_803BED68[11] = "Item2 : %s";
extern const char lbl_803BED74[19] = "ITEM SELECT TEST->";
extern const char lbl_806DA608[];
extern const char lbl_806DA610[];
extern const char lbl_806DA618[];
extern const char lbl_806DA620[];
extern const char lbl_806DA628[];
extern const char lbl_806DA630[];
extern const char lbl_806DA640[];
extern const char lbl_806DA648[];
extern const char lbl_806DA650[];
extern const char lbl_806DA654[];
extern const char lbl_806DA658[];
extern const char lbl_806DA660[];
extern const char lbl_806DA668[];
extern const char lbl_806DA670[];
extern const char lbl_806DA678[];
extern const char lbl_806DA67C[];
extern const char lbl_806DA680[];
int DebugOverlay_RaceConfig_data_804E53B0[3] = {114, 115, 115};
const char *DebugOverlay_RaceConfig_data_804E53BC[3] = {lbl_806D0054, 0, 0};
const char *lbl_804E53C8[3] = {lbl_806DA610, lbl_806DA618, lbl_806DA620};
const char *lbl_804E53D4[4] = {lbl_806DA628, lbl_806DA630, lbl_803BEAF0, lbl_803BEAFC};
const char *lbl_804E53E4[12] = {lbl_806DA640, lbl_806DA648, lbl_806DA650, lbl_806DA654, lbl_806DA658, lbl_803BEB10, lbl_803BEB1C, lbl_806DA660, lbl_806DA660, lbl_806DA668, lbl_806DA670, lbl_806DA678};
const char *lbl_804E5414[4] = {lbl_803BEB28, lbl_803BEB34, lbl_806DA608, lbl_803BEB40};
const char *lbl_804E5424[3] = {lbl_806DA67C, lbl_806DA628, lbl_806DA680};
}

extern "C" void DebugOverlay_RaceConfig(RaceConfig801F *self) {
    OverlayText(2, 0, self->state, lbl_806DA68C);
    OverlayText(2, 3, 0, lbl_803BEB98, self->cup, DebugOverlay_GetCupLabel(self->cup));
    OverlayText(2, 3, 1, lbl_803BEBB0, self->course, DebugOverlay_GetLongRoundLabel(self->course));
    OverlayText(2, 3, 2, lbl_803BEBC8, self->round, DebugOverlay_RaceConfig_data_806D0064[self->round]);
    OverlayText(2, 3, 3, lbl_803BEBE0, self->variant, DebugOverlay_GetDaytimeLabel(self->variant));
    OverlayText(2, 3, 4, lbl_803BEBF8, self->character, GetCharacterName(self->character));
    OverlayText(2, 3, 5, lbl_803BEC10, self->kart, lbl_804E53D4[self->kart]);
    OverlayText(2, 3, 6, lbl_803BEC28, self->mode, lbl_804E5414[self->mode]);
    OverlayText(2, 3, 7, lbl_803BEC40, self->itemCount, 7);
    OverlayText(2, 3, 8, lbl_803BEC60, self->gate, DebugOverlay_RaceConfig_data_806D006C[self->gate]);
    OverlayText(2, 3, 9, lbl_803BEC78, self->roundIndex, self->roundIndex + 1);
    OverlayText(2, 3, 10, lbl_803BEC98, self->cc, lbl_804E53C8[self->cc]);
    OverlayText(2, 3, 11, lbl_803BECB0, self->input, lbl_803BEB7C[(int)self->input]);
    OverlayText(2, 3, 12, lbl_803BECCC, self->selection, lbl_804E5424[self->selection]);
    OverlayText(2, 3, 13, lbl_803BECE8, self->items[0],
                lbl_804E53E4[GetItemDataEntry_Bounded(self->items[0])->category],
                GetItemDataEntry_Bounded(self->items[0])->name);
    OverlayText(2, 3, 14, lbl_803BED04, self->items[1],
                lbl_804E53E4[GetItemDataEntry_Bounded(self->items[1])->category],
                GetItemDataEntry_Bounded(self->items[1])->name);
    OverlayText(2, 3, 15, lbl_803BED20, self->items[2],
                lbl_804E53E4[GetItemDataEntry_Bounded(self->items[2])->category],
                GetItemDataEntry_Bounded(self->items[2])->name);
    OverlayText(2, 3, 17, lbl_803BED3C);
    OverlayText(2, 3, 18, lbl_803BED50, GetItemDataEntry_Bounded(self->items[0])->name);
    OverlayText(2, 3, 19, lbl_803BED5C, GetItemDataEntry_Bounded(self->items[1])->name);
    OverlayText(2, 3, 20, lbl_803BED68, GetItemDataEntry_Bounded(self->items[2])->name);
    OverlayText(2, 3, 22, lbl_803BED74);
    fn_8023E2F8(self->widgets[0]);
    if (self->modeFlag == 1) {
        fn_8023E2F8(self->widgets[1]);
        fn_8023E2F8(self->widgets[2]);
    }
}
