/* === extracted from auto_Tornado_HomingChildT_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */

/* --- extern decls: sda21-referenced data --- */
extern const float lbl_806D6260;

/* --- function index (1 fns, .text 0x800F8FD8..0x800F9148) ---
 * [  0] 0x800F8FD8 size:0x170   global Tornado_HomingChildTick
 */

/* --- forward decls --- */
void Tornado_HomingChildTick(char *self);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Tornado_HomingChildTick[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Tornado_HomingChildTick = {
    (void *)&Tornado_HomingChildTick, 0x00000170, (void *)extab_Tornado_HomingChildTick
};

/* --- asm function bodies (.text order = fn address order) --- */
static inline void TI_SetVec3(float *v, float x, float y, float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

void Tornado_HomingChildTick(char *self)
{
    TIVec3 kartPos;
    TIVec3 prev;
    TIVec3 moved;
    TIVec3 toTarget;
    TIVec3 sum;
    char *ctrl;

    switch (TI_S8(self, 0xc8)) {
    case 0:
        Mtx44_GetTranslation_RowMajor((float *)&kartPos, KartDriver_GetKartRootMtx(TI_PTR(self, 0x184)));
        Vec3_Subtract_DestFirst((float *)(self + 0x120), (float *)&kartPos, (float *)(TI_PTR(self, 0x148) + 0xa0));
        Vec3_Copy((float *)(self + 0x12c), (float *)(TI_PTR(self, 0x148) + 0xa0));
        TI_U8(self, 0xec) = 0;
        TI_U8(self, 0xc8) = TI_U8(self, 0xc8) + 1;
        break;
    case 1:
        break;
    }
    ctrl = TI_PTR(TI_PTR(self, 0x184), 0x304);
    if ((*(unsigned long long *)(ctrl + 0x10) & 0x0100000000000000ULL) == 0) {
        TI_U8(self, 0xec) = 1;
    }
    Vec3_Copy((float *)&prev, (float *)(self + 0x120));
    if (Item_AdvanceTrackedHomingState(TI_PTR(self, 0x148), (float *)(self + 0x120), lbl_806D6260) != 0) {
        TI_U8(self, 0xec) = 1;
    }
    Vec3_Subtract_DestFirst((float *)&moved, (float *)(self + 0x120), (float *)&prev);
    Vec3_Subtract_DestFirst((float *)&toTarget, (float *)(TI_PTR(self, 0x148) + 0xa0), (float *)(self + 0x12c));
    Vec3_Add_DestFirst((float *)&sum, (float *)&moved, (float *)&toTarget);
    TI_SetVec3((float *)(ctrl + 0x30), sum.x, sum.y, sum.z);
    Vec3_Copy((float *)(self + 0x12c), (float *)(TI_PTR(self, 0x148) + 0xa0));
    if (TI_U8(self, 0xec) != 0) {
        SpriteSlot_Container_Free(self);
    }
}

