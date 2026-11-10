/*
 * Tornado item-state unit: exact target asm_fn bodies and extab data.
 *
 * These singleton reversed-extab groups share the Tornado item-state range.
 * Keep both the include order and the manual extab metadata in target order.
 */

typedef struct TIVec3 {
    float x, y, z;
} TIVec3;

extern float *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(float *out, float *mtx);
extern void SpriteSlot_Container_Free(void *self);
extern void Vec3_Add_DestFirst(float *dst, float *a, float *b);
extern void Vec3_Copy(float *dst, float *src);
extern void Vec3_Subtract_DestFirst(float *dst, float *a, float *b);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_AdvanceTrackedHomingState(void *target, float *pos, float speed);

#define TI_S8(p, o) (*(signed char *)((char *)(p) + (o)))
#define TI_U8(p, o) (*(unsigned char *)((char *)(p) + (o)))
#define TI_U32(p, o) (*(unsigned int *)((char *)(p) + (o)))
#define TI_F32(p, o) (*(float *)((char *)(p) + (o)))
#define TI_PTR(p, o) (*(char **)((char *)(p) + (o)))

#ifndef __MWERKS__ /* this unit passes the position as the address of its own copy (SoundMgr_PlaySE_Positional.c) */
#define SoundMgr_PlaySE_Positional SoundMgr_PlaySE_Positional_ByAddress
#endif
#include "src/game/tornado_fragments/ti_active.inc"
#include "src/game/tornado_fragments/ti_launch.inc"
#include "src/game/tornado_fragments/ti_homing_child.inc"
#include "src/game/tornado_fragments/ti_lock_on.inc"
#include "src/game/tornado_fragments/ti_flight.inc"
#include "src/game/tornado_fragments/ti_hold.inc"
