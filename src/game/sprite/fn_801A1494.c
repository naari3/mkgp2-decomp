#include "game/types/port_hooks.h"
#include "game/types/SpriteAnimData.h"

extern int lbl_806D16EC;
extern int lbl_806D16E8;
extern int lbl_80678A0C[200];
extern int g_spriteSystemInited;
extern short lbl_80678D2C[];
extern SpriteAnimData *DVDFile_LoadSync(const char *name);
extern int fn_801A0D90(SpriteAnimData *d, unsigned int params);
extern void PreloadResource(short id);

static inline void PreloadParams(SpriteAnimData *d) {
    int i;
    if (d == 0) return;
    for (i = 0; d->params[i] != -1; i++) {
        int n = g_spriteSystemInited;
        unsigned char isNew = 1;
        if (n != -1) {
            int j;
            for (j = 0; j < n; j++) {
                if (lbl_80678D2C[j] == d->params[i]) {
                    isNew = 0;
                    break;
                }
            }
        }
        if (isNew) {
            if (n != -1) {
                lbl_80678D2C[n] = d->params[i];
                g_spriteSystemInited++;
            }
            PreloadResource(d->params[i]);
        }
    }
}

SpriteAnimData *fn_801A1494(const char *name, unsigned char preload, unsigned int params) {
    SpriteAnimData *d;
    if (lbl_806D16EC == 0) {
        int i;
        for (i = 0; i < 200; i++) lbl_80678A0C[i] = -1;
        lbl_806D16E8 = 0;
    }
    lbl_806D16EC++;
    if (name == 0) return 0;
    d = DVDFile_LoadSync(name);
    PORT_DATA_LOADED(PORT_DATA_SPRITE_ANIM, d, 0);
    fn_801A0D90(d, params);
    if (preload) PreloadParams(d);
    return d;
}
