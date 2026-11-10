/* Overlay slots are created lazily, then attached to the active display. */
typedef struct OverlayRegistry {
    char pad[0xc];
    void *display;
    void *overlays[13];
} OverlayRegistry;

extern void *fn_80253294(OverlayRegistry *, int, int);
extern void *fn_80271340(void *, int, void *, void *, int);
extern void fn_8021984C(void *, void *);
extern void fn_802437AC(void *, void *);
extern unsigned int HUD_RegisterOverlay_data_806D0A60[2];
extern unsigned int HUD_RegisterOverlay_data_806D0A68[2];
extern unsigned int s_clCDispInterface[2];

void HUD_RegisterOverlay(OverlayRegistry *self, int kind, int flag)
{
    void *display;
    if (!self->overlays[kind]) {
        self->overlays[kind] = fn_80253294(self, kind, flag);
    }
    if (!self->overlays[kind]) {
        return;
    }
    display = self->display;
    if (!display) {
        return;
    }
    switch (kind) {
    case 10:
        fn_8021984C(fn_80271340(self->overlays[kind], 0, HUD_RegisterOverlay_data_806D0A68,
                              s_clCDispInterface, 0), display);
        break;
    case 11:
        break;
    case 12:
        fn_802437AC(fn_80271340(self->overlays[kind], 0, HUD_RegisterOverlay_data_806D0A60,
                              s_clCDispInterface, 0), display);
        break;
    }
}
