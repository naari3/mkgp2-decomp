#include "game/FlowDispatcher_private.h"
extern "C" {
float MetricsTable_Get(int);
float Profiler_DrawBar(int, int, int);
void OverlayText(int, int, int, const char *, ...);
int clRom_GetActiveCount();
int cLNormal3DWrap_Mgr_GetPeakActiveCount();
void MemoryHeap_GetStats(void *, int *, int *, int *);
extern void *lbl_806CF010;
extern float lbl_806D2268, lbl_806D226C, lbl_806D2270;
extern const char *lbl_806D2260;
extern signed char g_playerData[];
void fn_801934F4();
void DebugOverlay_DumpPcbState();
void DebugOverlay_KartPhysicsForLocalPlayer();
}
extern "C" void DebugOverlay_Dispatch(FlowDispatcher *self)
{
    const char *text = lbl_802E89A0;
    float frame;
    float update;
    float draw;
    float other;
    int total, used, count;
    switch (self->overlay) {
    case 1:
        frame = MetricsTable_Get(0);
        update = MetricsTable_Get(6);
        draw = MetricsTable_Get(2);
        other = MetricsTable_Get(21);
        ++self->frames;
        self->total[0] += update;
        self->total[1] += draw;
        self->total[2] += frame - (update + draw);
        OverlayText(1, 0, 2, text + 0x478, self->average[0]);
        OverlayText(1, 0, 3, text + 0x488, self->average[1]);
        OverlayText(1, 0, 4, text + 0x498, self->average[2]);
        OverlayText(1, 0, 5, text + 0x4a8, other);
        OverlayText(1, 0, 6, text + 0x4b8, frame);
        if (self->frames >= 60) {
            self->average[0] = self->total[0] / self->frames;
            self->average[1] = self->total[1] / self->frames;
            self->average[2] = self->total[2] / self->frames;
            self->frames = 0;
            self->total[0] = 0.0f;
            self->total[1] = 0.0f;
            self->total[2] = 0.0f;
        }
        break;
    case 2:
        Profiler_DrawBar(2, 0, 16);
        Profiler_DrawBar(2, 1, 21);
        Profiler_DrawBar(2, 2, 20);
        Profiler_DrawBar(2, 5, 36);
        Profiler_DrawBar(2, 6, 37);
        Profiler_DrawBar(2, 7, 13);
        Profiler_DrawBar(2, 8, 38);
        Profiler_DrawBar(2, 9, 40);
        Profiler_DrawBar(2, 10, 39);
        Profiler_DrawBar(2, 11, 19);
        Profiler_DrawBar(2, 12, 15);
        OverlayText(1, 2, 16, text + 0x4c8, clRom_GetActiveCount());
        OverlayText(1, 2, 17, text + 0x4dc, cLNormal3DWrap_Mgr_GetPeakActiveCount());
        break;
    case 3:
        Profiler_DrawBar(2, 0, 22);
        Profiler_DrawBar(2, 1, 23);
        Profiler_DrawBar(2, 2, 24);
        break;
    case 4:
        Profiler_DrawBar(2, 0, 25);
        Profiler_DrawBar(2, 1, 26);
        Profiler_DrawBar(2, 2, 27);
        Profiler_DrawBar(2, 4, 43);
        Profiler_DrawBar(2, 5, 44);
        Profiler_DrawBar(2, 6, 45);
        Profiler_DrawBar(2, 8, 41);
        Profiler_DrawBar(2, 9, 42);
        Profiler_DrawBar(2, 11, 46);
        break;
    case 5:
        Profiler_DrawBar(2, 0, 28);
        Profiler_DrawBar(2, 1, 29);
        Profiler_DrawBar(2, 2, 30);
        break;
    case 6:
        Profiler_DrawBar(2, 0, 31);
        Profiler_DrawBar(2, 1, 32);
        Profiler_DrawBar(2, 2, 33);
        Profiler_DrawBar(2, 3, 34);
        Profiler_DrawBar(2, 4, 35);
        break;
    case 7:
        MemoryHeap_GetStats(lbl_806CF010, &total, &used, &count);
        total /= 1024;
        used /= 1024;
        OverlayText(1, 0, 2, text + 0x4f0, total);
        OverlayText(1, 0, 3, text + 0x508, used);
        OverlayText(1, 0, 4, text + 0x520, count);
        break;
    case 8:
        Profiler_DrawBar(2, 0, 7);
        Profiler_DrawBar(2, 1, 8);
        Profiler_DrawBar(2, 2, 11);
        Profiler_DrawBar(2, 3, 9);
        Profiler_DrawBar(2, 4, 10);
        break;
    case 9:
        other = lbl_806D2268;
        Profiler_DrawBar(2, 0, 16);
        other += Profiler_DrawBar(2, 1, 21);
        other += Profiler_DrawBar(2, 2, 20);
        other += Profiler_DrawBar(2, 3, 36);
        other += Profiler_DrawBar(2, 4, 37);
        other += Profiler_DrawBar(2, 5, 13);
        other += Profiler_DrawBar(2, 6, 38);
        other += Profiler_DrawBar(2, 7, 31);
        other += Profiler_DrawBar(2, 8, 32);
        other += Profiler_DrawBar(2, 9, 33);
        draw = Profiler_DrawBar(2, 10, 22);
        other += draw;
        other += Profiler_DrawBar(2, 11, 23);
        other += Profiler_DrawBar(2, 12, 25);
        other += Profiler_DrawBar(2, 13, 26);
        other += Profiler_DrawBar(2, 14, 28);
        other += Profiler_DrawBar(2, 15, 29);
        other += Profiler_DrawBar(2, 16, 40);
        other += Profiler_DrawBar(2, 17, 39) - lbl_806D226C * (lbl_806D2270 * draw);
        OverlayText(1, 2, 20, text + 0x534, other);
        break;
    case 10: fn_801934F4(); break;
    case 11: DebugOverlay_DumpPcbState(); break;
    case 12: DebugOverlay_KartPhysicsForLocalPlayer(); break;
    case 13:
        OverlayText(1, 2, 2, lbl_806D2260);
        OverlayText(1, 2, 3, text + 0x540, g_playerData[0x198]);
        break;
    }
}
