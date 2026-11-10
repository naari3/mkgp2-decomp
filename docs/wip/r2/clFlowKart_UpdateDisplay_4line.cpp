/* WIP 2026-11-07 (thread B): clFlowKart_UpdateDisplay, 8 diff lines left.
 * Compile with clFlowKart_Init's flags + -use_lmw_stmw on (C++). Loops written as three
 * separate for(int a/b/d) fixed all loop regalloc. Left: target 'addi r4,r31,0x3fc; lwzx r0,r4,r30'
 * vs ours 'add r4,r31,r30; lwz r0,0x3fc(r4)' (both need tables). Direct pooled objects in a
 * merged TU give the right addressing but shift regalloc (kart*4 goes r27 not r30). */
/* clFlowKart_UpdateDisplay @ 0x801D7920: rebuilds the three kart-select
 * rank sprites. The display level comes from the player's coin mileage
 * against two per-kart thresholds (level 1 without a valid card), then
 * each sprite hides (5 - count) of its five anim params, with the counts
 * from the level/kart table clFlowKart_UpdateDisplay_data_8049BB30. The thresholds and the param
 * list live in clFlowKart_Init.c's pooled .rodata (clFlowKart_Init_rodata_8039E508).
 * Compiled as C++ (-lang=c++) for the `new` cleanups in the extab. */

void *operator new(unsigned long);
void operator delete(void *);

typedef struct FKParams { int v[5]; } FKParams;

typedef struct FKRodata {
    unsigned char pad000[0x3FC];
    int need1[13];       /* 0x3FC */
    int need2[13];       /* 0x430 */
    unsigned char pad464[0x4B0 - 0x464];
    FKParams params;     /* 0x4B0 */
} FKRodata;

typedef struct FKSprite {
    unsigned char data[0x30];
    FKSprite(int id, float x, float y, int flag);
} FKSprite;

typedef struct FKDisplay {
    unsigned char pad00[0x4];
    int unlocked;        /* 0x04 */
    unsigned char pad08[0x74 - 0x08];
    FKSprite *rank[3];   /* 0x74 */
} FKDisplay;

extern "C" {
int GetCoinMilage(void *data);
unsigned char IsCardValid(void);
void Sprite_Destroy(FKSprite *sprite, int flag);
void Sprite_SetAnimParam(FKSprite *sprite, short param, short key);

extern const float lbl_806DA120;
extern const float lbl_806DA124;
extern const float lbl_806DA128;
extern const float lbl_806DA12C;
extern unsigned char g_playerData[];
extern FKRodata clFlowKart_Init_rodata_8039E508;
extern signed char clFlowKart_UpdateDisplay_data_8049BB30[][13][3];
}

static inline void HideParams(FKDisplay *self, int idx, int *p, signed char *n) {
    for (int i = 0; i < 5 - *n; i++) {
        Sprite_SetAnimParam(self->rank[idx], p[i], -1);
    }
}
/* fakematch (pragma): the natural code is the same body without the pragma;
 * the original TU owned clFlowKart_Init_rodata_8039E508, so CW kept the base + offset addi. */



extern "C" void clFlowKart_UpdateDisplay(FKDisplay *self, int kart)
{
    FKRodata *rd = &clFlowKart_Init_rodata_8039E508;
    int level = 0;
    FKParams params;
    signed char *count;
    signed char *c;
    int *base;
    int *p;
    int i;

    if (self->unlocked >= 1) {
        int *need;
        int m = GetCoinMilage(g_playerData);
        need = rd->need1;
        if (m >= need[kart]) {
            level = 1;
        }
        m = GetCoinMilage(g_playerData);
        need = rd->need2;
        if (m >= need[kart]) {
            level = 2;
        }
        if (!IsCardValid()) {
            level = 1;
        }
    }
    Sprite_Destroy(self->rank[0], 1);
    Sprite_Destroy(self->rank[1], 1);
    Sprite_Destroy(self->rank[2], 1);
    self->rank[0] = new FKSprite(0x16B, lbl_806DA120, lbl_806DA124, 1);
    self->rank[1] = new FKSprite(0x16B, lbl_806DA120, lbl_806DA128, 1);
    self->rank[2] = new FKSprite(0x16B, lbl_806DA120, lbl_806DA12C, 1);
    params = rd->params;
    for (int a = 0; a < 5 - clFlowKart_UpdateDisplay_data_8049BB30[level][kart][0]; a++) Sprite_SetAnimParam(self->rank[0], params.v[a], -1);
    for (int b = 0; b < 5 - clFlowKart_UpdateDisplay_data_8049BB30[level][kart][1]; b++) Sprite_SetAnimParam(self->rank[1], params.v[b], -1);
    for (int d = 0; d < 5 - clFlowKart_UpdateDisplay_data_8049BB30[level][kart][2]; d++) Sprite_SetAnimParam(self->rank[2], params.v[d], -1);
}

#pragma opt_propagation reset
