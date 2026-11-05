#include "game/RaceConfig801FPrivate.h"
extern "C" void DebugOverlay_RaceConfig(RaceConfig801F *self) {
    const char *strings = lbl_803BE6C0;
    const char *tables = (const char *)lbl_804E53B0;
    OverlayText(2, 0, self->state, lbl_806DA68C);
    OverlayText(2, 3, 0, strings + 0x4D8, self->cup, DebugOverlay_GetCupLabel(self->cup));
    OverlayText(2, 3, 1, strings + 0x4F0, self->course, DebugOverlay_GetLongRoundLabel(self->course));
    OverlayText(2, 3, 2, strings + 0x508, self->round, lbl_806D0064[self->round]);
    OverlayText(2, 3, 3, strings + 0x520, self->variant, DebugOverlay_GetDaytimeLabel(self->variant));
    OverlayText(2, 3, 4, strings + 0x538, self->character, GetCharacterName(self->character));
    OverlayText(2, 3, 5, strings + 0x550, self->kart, ((const char **)(tables + 0x24))[self->kart]);
    OverlayText(2, 3, 6, strings + 0x568, self->mode, ((const char **)(tables + 0x64))[self->mode]);
    OverlayText(2, 3, 7, strings + 0x580, self->itemCount, 7);
    OverlayText(2, 3, 8, strings + 0x5A0, self->gate, lbl_806D006C[self->gate]);
    OverlayText(2, 3, 9, strings + 0x5B8, self->roundIndex, self->roundIndex + 1);
    OverlayText(2, 3, 10, strings + 0x5D8, self->cc, ((const char **)(tables + 0x18))[self->cc]);
    OverlayText(2, 3, 11, strings + 0x5F0, self->input, ((const char **)(strings + 0x4bc))[(int)self->input]);
    OverlayText(2, 3, 12, strings + 0x60C, self->selection, ((const char **)(tables + 0x74))[self->selection]);
    OverlayText(2, 3, 13, strings + 0x628, self->items[0],
                ((const char **)(tables + 0x34))[GetItemDataEntry_Bounded(self->items[0])->category],
                GetItemDataEntry_Bounded(self->items[0])->name);
    OverlayText(2, 3, 14, strings + 0x644, self->items[1],
                ((const char **)(tables + 0x34))[GetItemDataEntry_Bounded(self->items[1])->category],
                GetItemDataEntry_Bounded(self->items[1])->name);
    OverlayText(2, 3, 15, strings + 0x660, self->items[2],
                ((const char **)(tables + 0x34))[GetItemDataEntry_Bounded(self->items[2])->category],
                GetItemDataEntry_Bounded(self->items[2])->name);
    OverlayText(2, 3, 17, strings + 0x67C);
    OverlayText(2, 3, 18, strings + 0x690, GetItemDataEntry_Bounded(self->items[0])->name);
    OverlayText(2, 3, 19, strings + 0x69C, GetItemDataEntry_Bounded(self->items[1])->name);
    OverlayText(2, 3, 20, strings + 0x6A8, GetItemDataEntry_Bounded(self->items[2])->name);
    OverlayText(2, 3, 22, strings + 0x6B4);
    fn_8023E2F8(self->widgets[0]);
    if (self->modeFlag == 1) {
        fn_8023E2F8(self->widgets[1]);
        fn_8023E2F8(self->widgets[2]);
    }
}
