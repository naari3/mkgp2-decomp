/* Dispatch views contain only fields observed by this callback.
 * The timer only enables the star variant; a zero timer does not clear it.
 */
/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct DispatchKart DispatchKart;
struct DispatchKart {
    /* 0x000 */ unsigned char pad_000[0x238];
    /* 0x238 */ int wingEnabled;
    /* 0x23C */ unsigned char pad_23C[0x94];
    /* 0x2D0 */ unsigned char mode2Enabled;
    /* 0x2D1 */ unsigned char pad_2D1[0x3];
};
#include "game/types/DispatchPayload.h"
#include "game/types/DispatchEffect.h"
extern "C" {
extern int g_gameMode;
void EffectVfx72_ItemStarAura_Tick(DispatchEffect *);
void EffectVfx83_ItemWingBurst_Tick(DispatchEffect *);
void EffectVfx55_HornBlastTrio_Tick(DispatchEffect *);
DispatchEffect *DrawEffect_SpawnDirect(void (*)(DispatchEffect *));

void KartFx_DispatchGroupB_AuxStarBurst(void *, DispatchPayload *payload, void *, int enabled) {
    int edge = 0;
    if (payload->previousActive == 0 && payload->active != 0) edge = 1;
    payload->previousActive = payload->active;
    if (payload->timer != 0) --payload->timer;
    if (enabled && payload->active) {
        for (int i = 0; i < 2; ++i) {
            DispatchEffect *effect = DrawEffect_SpawnDirect(EffectVfx72_ItemStarAura_Tick);
            if (effect) {
                effect->index = (unsigned char)i;
                effect->kart = payload->kart;
                if (payload->timer) effect->variant = 1;
            }
        }
    }
    if (g_gameMode == 2 && payload->kart->mode2Enabled == 0) return;
    if (enabled && edge) {
        for (int variant = 0; variant < 2; ++variant) {
            if (variant != 0 && payload->kart->wingEnabled == 0) continue;
            for (int side = 0; side < 2; ++side) {
                for (int count = 0; count < 8; ++count) {
                    DispatchEffect *effect = DrawEffect_SpawnDirect(EffectVfx83_ItemWingBurst_Tick);
                    if (effect) {
                        effect->index = (unsigned char)side;
                        effect->kart = payload->kart;
                        effect->variant = variant;
                    }
                }
            }
        }
    }
    if (enabled && edge) {
        for (int i = 0; i < 2; ++i) {
            DispatchEffect *effect = DrawEffect_SpawnDirect(EffectVfx55_HornBlastTrio_Tick);
            if (effect) {
                effect->index = (unsigned char)i;
                effect->kart = payload->kart;
            }
        }
    }
}
}
