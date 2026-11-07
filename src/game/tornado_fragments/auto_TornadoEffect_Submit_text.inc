/* TornadoEffect_SubmitRender @ 0x80056F40: queue TornadoEffect_RenderCallback
 * at the effect's joint position unless the kart is in the final-lap coin jump. */
typedef struct TornadoVec3 {
    float x, y, z;
} TornadoVec3;

extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void Object_GetJObjPositionVec(void *obj, TornadoVec3 *out);
extern void clDrawMan_AddSorted(void *mgr, void (*fn)(), void *obj,
                                float x, float y, float z, float bias);
extern void TornadoEffect_RenderCallback();

extern void *lbl_806D10AC;
extern const float lbl_806D28E4;

#pragma exceptions on

void TornadoEffect_SubmitRender(char *self) {
    TornadoVec3 pos;

    if (FinalLapCoinJump_CheckActiveForObject(*(void **)(self + 0xC)) == 0 &&
        *(int *)(self + 0x100) > 0) {
        Object_GetJObjPositionVec(*(void **)(self + 0xA8), &pos);
        clDrawMan_AddSorted(lbl_806D10AC == 0 ? 0 : lbl_806D10AC,
                            TornadoEffect_RenderCallback, *(void **)(self + 0xA8),
                            pos.x, pos.y, pos.z, lbl_806D28E4);
    }
}

#pragma exceptions reset
