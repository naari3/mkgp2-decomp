#include "game/types/c_region.h"
C_REGION_BEGIN
/* HUD_FrameUpdate @ 0x80253658: per-frame update of the race HUD manager.
 *
 * Updates every HUD part, adds the next start-countdown popup (digit, or the
 * "GO" flash at 0) when the global countdown phase reaches the manager's
 * own phase, runs the final-seconds time warning (digit popup + SE 3) while
 * the timer part exists, then updates the manager's scene list.
 */
C_REGION_END
#pragma cplusplus on

#include "game/HudManager.h"

#define HUD_PART_COUNT 23
#define HUD_PART_TIMER 6

extern "C" {
extern int g_countdownPhase;
extern unsigned char g_raceEnded;

void SoundMgr_PlaySE(int se);
unsigned char fn_8016C360(int se);
void fn_8016C394(int se);
void fn_8020EDB4(FlowSceneList *list, void *task, int mode);
void *fn_802518EC(int layer, int id);
void *fn_802512D0(int kind, int layer, int id);
void *fn_80215784(int kind, int layer, int id);
}

#pragma exceptions on
extern "C" void HUD_FrameUpdate(HudManager *self)
{
    FlowSceneList *list;
    int i;
    float next;

    for (i = 0; i < HUD_PART_COUNT; i++) {
        if (self->parts[i] != 0) {
            self->parts[i]->Update();
        }
    }

    if (self->phase == g_countdownPhase) {
        int id = self->phase + 50;
        if (g_countdownPhase == 0) {
            list = self->list.p;
            fn_8020EDB4(list, fn_802518EC(4, id), 0);
        } else {
            list = self->list.p;
            fn_8020EDB4(list, fn_802512D0(self->phase, 4, id), 0);
        }
        self->phase--;
    }

    if (self->parts[HUD_PART_TIMER] != 0) {
        next = self->field08 + 1;
        if (self->field70 <= next && next > 1.0f) {
            if (!g_raceEnded) {
                list = self->list.p;
                fn_8020EDB4(list, fn_80215784(self->field08, 4, self->field08 + 60), 0);
                self->field08--;
            }
            if (fn_8016C360(3) == 1) {
                fn_8016C394(3);
            }
            SoundMgr_PlaySE(3);
        }
    }

    self->list.p->Update();
}
#pragma exceptions reset
