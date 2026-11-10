/*
 * TornadoEffect reversed-extab bundle.
 *
 * The included fragments are generated from the target assembly with
 * tools/extract_fn_asm.py.  Keep their order in lockstep with .text.
 */

/* Helpers for the functions already converted to C. */
extern const float lbl_806D28C8; /* 0.0f */
extern const float lbl_806D28CC; /* 1.0f */
extern const float lbl_806D28D0;
extern const float lbl_806D28F8;
extern unsigned int TornadoEffect_rodata_802EDC30[];
#define TE_F(p, o) (*(float *)((char *)(p) + (o)))
#define TE_U8(p, o) (*(unsigned char *)((char *)(p) + (o)))
#define TE_S32(p, o) (*(int *)((char *)(p) + (o)))
#define TE_PTR(p, o) (*(void **)((char *)(p) + (o)))
typedef struct { float x, y, z; } TornadoSpawnPos;
typedef struct { float a0, a1, a2, a3, b0, b1, b2, b3, c0, c1, c2, c3, d0, d1, d2, d3; } TornadoMtx16;
#define TE_SPAWN_POS (*(const TornadoSpawnPos *)TornadoEffect_rodata_802EDC30)
void DrawEffect_SetBytePairD4D5(void *, signed char, signed char);
void DrawEffect_SetByte10C(void *, int);
unsigned int Terrain_ApplyCup2FlagPatch(unsigned int);
int Terrain_FlagsToTypeId(unsigned int);
float Saturate_Double(float, float, float);
void *DrawEffect_SpawnWithDescriptor(int, TornadoSpawnPos);
void Object_RenderJObjTree(void *, int);

#include "tornado_fragments/auto_TornadoEffect_InitDe_text.inc"
#include "tornado_fragments/auto_TornadoEffect_Ctor_text.inc"
#include "tornado_fragments/auto_TornadoEffect_Render_text.inc"
#include "tornado_fragments/auto_TornadoEffect_Submit_text.inc"
#include "tornado_fragments/auto_TornadoEffect_Tick_text.inc"
#include "tornado_fragments/auto_TornadoEffect_Trigge_text.inc"
#include "tornado_fragments/KartBody.inc"
#include "tornado_fragments/auto_TornadoEffect_SetCol_text.inc"
#include "tornado_fragments/auto_03_8005778C_text.inc"
#include "tornado_fragments/auto_TornadoEffect_SetFla_text.inc"
#include "tornado_fragments/auto_TornadoEffect_SetSca_text.inc"
#include "tornado_fragments/auto_TireEffect_ResetSpin_text.inc"
#include "tornado_fragments/auto_03_800578C4_text.inc"
#include "tornado_fragments/auto_fn_80057960_text.inc"
#include "tornado_fragments/auto_03_800579D8_text.inc"
#include "tornado_fragments/auto_TornadoEffect_Compos_text.inc"
#include "tornado_fragments/auto_03_80058510_text.inc"
#include "tornado_fragments/auto_TornadoEffect_ApplyI_text.inc"
#include "tornado_fragments/auto_TornadoEffect_ApplyI_text_1.inc"
#include "tornado_fragments/auto_TornadoEffect_ApplyI_text_2.inc"
#include "tornado_fragments/auto_03_80058DDC_text.inc"
