#include "game/VoiceBrowser_private.h"

extern "C" void fn_801B70EC(VoiceBrowser *self) {
    char *strings = lbl_803993A0;
    if (self->context) {
        float axis = InputMgr_GetPlayer(GetInputManager(), 0)->v2();
        if (axis < lbl_806D9848)
            DrawText(self->context, 60, 90, 4, lbl_806D984C, strings + 0x414);
        else if (axis < lbl_806D9850)
            DrawText(self->context, 60, 90, 4, lbl_806D984C, strings + 0x430);
        VoiceClip *clip;
        clip = fn_801B3A50(self->selection - 2);
        DrawText(self->context, 60, 110, 1, lbl_806D984C, strings + 0x44C, clip->path, clip->length);
        clip = fn_801B3A50(self->selection - 1);
        DrawText(self->context, 60, 130, 1, lbl_806D984C, strings + 0x44C, clip->path, clip->length);
        clip = fn_801B3A50(self->selection);
        DrawText(self->context, 60, 150, 7, lbl_806D984C, strings + 0x44C, clip->path, clip->length);
        clip = fn_801B3A50(self->selection + 1);
        DrawText(self->context, 60, 170, 1, lbl_806D984C, strings + 0x44C, clip->path, clip->length);
        clip = fn_801B3A50(self->selection + 2);
        DrawText(self->context, 60, 190, 1, lbl_806D984C, strings + 0x44C, clip->path, clip->length);
        if (axis > lbl_806D9854)
            DrawText(self->context, 60, 210, 4, lbl_806D984C, strings + 0x414);
        else if (axis > lbl_806D9858)
            DrawText(self->context, 60, 210, 4, lbl_806D984C, strings + 0x430);
        DrawText(self->context, 10, 320, 7, lbl_806D984C, strings + 0x45C,
            (float)OSTicksToMilliseconds(g_voiceStreamLastPollTime - g_voiceStreamStartTime) / lbl_806D985C);
        DisplayContext_Flush(self->context);
    }
}

