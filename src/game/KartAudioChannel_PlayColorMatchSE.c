/* KartAudioChannel_PlayColorMatchSE @ 0x8005967C (size 0x1B0).
 * Picks the surface SE for the two ground types under the kart (the lower
 * table index wins; speed <= 0 means "no surface"), and when it changed,
 * stops the previous loop and starts the new one (plus its positional copy
 * at the kart when the channel has a source and is not muted). */
#include "game/types/Vec.h"

#include "game/types/SoundSource.h"

#include "game/types/KartAudioChannel.h"

typedef struct SurfaceSE {
    unsigned int ground;
    int se;
} SurfaceSE;

extern const float lbl_806D2940;
extern SurfaceSE KartAudioChannel_PlayColorMatchSE_rodata_802EDCBC[13];
extern const Vec KartItemAudio_PlaySEByItemId_rodata_802EDD24;
extern unsigned int Terrain_ApplyCup2FlagPatch(int flags);
extern void SoundMgr_PlaySE(unsigned int id);
extern void fn_8016C394(unsigned int id);
extern void fn_8016C288(unsigned int id, Vec *pos);

void KartAudioChannel_PlayColorMatchSE(KartAudioChannel *self, int ground0, int ground1, float speed)
{
    unsigned int type0;
    unsigned int type1;
    int idx0;
    int idx1;
    int i;
    int idx;
    int se;
    SoundSource *src;

    if (self->enabled == 0) {
        return;
    }
    if (speed <= lbl_806D2940) {
        ground0 = 0;
        ground1 = 0;
    }
    type0 = Terrain_ApplyCup2FlagPatch(ground0);
    type1 = Terrain_ApplyCup2FlagPatch(ground1);

    idx0 = 12;
    idx1 = 12;
    for (i = 0; i < 13; i++) {
        if (type0 == KartAudioChannel_PlayColorMatchSE_rodata_802EDCBC[i].ground) {
            idx0 = i;
            break;
        }
    }
    for (i = 0; i < 13; i++) {
        if (type1 == KartAudioChannel_PlayColorMatchSE_rodata_802EDCBC[i].ground) {
            idx1 = i;
            break;
        }
    }
    idx = (idx0 < idx1) ? idx0 : idx1;

    if (self->surfaceSE == KartAudioChannel_PlayColorMatchSE_rodata_802EDCBC[idx].se) {
        return;
    }
    if (self->surfaceSE >= 0) {
        fn_8016C394(self->surfaceSE | ((self->channel & 0xf) << 27));
    }
    self->surfaceSE = KartAudioChannel_PlayColorMatchSE_rodata_802EDCBC[idx].se;
    se = self->surfaceSE;
    if (se >= 0) {
        SoundMgr_PlaySE(se | ((self->channel & 0xf) << 27));
        if (self->muted == 0) {
            src = self->source;
            if (src != 0) {
                Vec pos = KartItemAudio_PlaySEByItemId_rodata_802EDD24;
                pos.x = src->x;
                pos.y = src->y;
                pos.z = src->z;
                fn_8016C288(se | ((self->channel & 0xf) << 27), &pos);
            }
        }
    }
}
