#include "game/types/RenderObj.h"

extern void *g_carObjects[4];
extern int RaceScene_PlayerSlots_bss_805D2B00[4];
extern RenderObj *CarObject_GetRenderObj(void *);

RenderObj *CarObjects_FindByEventType(int type, int *outIndex) {
    int i;

    for (i = 0; i < 4; i++) {
        if (g_carObjects[i] != 0) {
            RenderObj *render = CarObject_GetRenderObj(g_carObjects[i]);

            if (type == render->eventType) {
                if (outIndex != 0) {
                    *outIndex = RaceScene_PlayerSlots_bss_805D2B00[i];
                }
                return render;
            }
        }
    }
    if (outIndex != 0) {
        *outIndex = -1;
    }
    return 0;
}
