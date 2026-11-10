/* === extracted from auto_TornadoLaunch_Tick_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */


extern void ItemObject_DecrementCategoryBudget();
extern signed char ItemObject_GetGroundTypeAt(void *, void *, int);
extern int Item_AdvanceTetherToJoint13(void *, void *, float, float, float);
extern void Item_DecayVelocityScalar(void *, float);
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetTransform(void *, void *, void *, float);
extern void TornadoItem_TickActive();


/* --- extern decls: sda21-referenced data --- */
extern const float lbl_806D61F0;
extern const float lbl_806D61F4;
extern const float lbl_806D61F8;
extern const float lbl_806D61FC;
extern const float lbl_806D6200;
extern const float lbl_806D6204;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_804217D8[];

/* --- function index (1 fns, .text 0x800F869C..0x800F8FD8) ---
 * [  0] 0x800F869C size:0x93C   global TornadoLaunch_Tick
 */

/* --- function bodies --- */
void TornadoLaunch_Tick(char *self);

#pragma exceptions on
static inline void TornadoLaunch_FadeOut(char *self, char *sub)
{
    TIVec3 initialPos;
    TIVec3 pos;
    float groundY;

    switch (TI_S8(self, 0xc9)) {
    case 0:
        initialPos = *(TIVec3 *)(self + 0xa0);
        ItemObject_GetGroundTypeAt(&initialPos, sub + 0x14, 0);
        if ((int)TI_U8(self, 0xcb) != 5) {
            TI_U32(sub, 4) = 10;
        } else {
            TI_U32(sub, 4) = 0;
        }
        TI_U8(self, 0xc9) = TI_U8(self, 0xc9) + 1;
        /* fall through */
    case 1:
        break;
    }
    if (TI_U32(sub, 4) == 0) {
        TI_F32(self, 0x2c) = TI_F32(self, 0x2c) - lbl_806D61F8;
        if (TI_F32(self, 0x2c) < lbl_806D61F0) {
            TI_U8(self, 0x28) = 0;
            TI_U8(self, 0xc8) = 3;
            TI_U8(self, 0xc9) = 0;
            return;
        }
    }
    TI_F32(self, 0xbc) = TI_F32(self, 0xbc) + lbl_806D61FC;
    pos = *(TIVec3 *)(self + 0xa0);
    if (ItemObject_GetGroundTypeAt(&pos, &groundY, 0) != 0) {
        TI_F32(self, 0xa4) = TI_F32(self, 0xa4) + (groundY - TI_F32(sub, 0x14));
        TI_F32(sub, 0x14) = groundY;
    }
    switch (TI_S8(self, 0xcb)) {
    case 4:
        TI_F32(self, 0xac) = BuildOrientationFromYaw(TI_F32(self, 0xac) - lbl_806D6200);
        break;
    case 7:
        TI_F32(self, 0xac) = BuildOrientationFromYaw(TI_F32(self, 0xac) - lbl_806D6200);
        break;
    case 9:
        TI_F32(self, 0xac) = AngleStepTowards_Shortest(TI_F32(self, 0xac), Vec3_ToPitch(self + 0xb8), lbl_806D61F4);
        break;
    case 5:
        TI_F32(self, 0xac) = AngleStepTowards_Shortest(TI_F32(self, 0xac), Vec3_ToPitch(self + 0xb8), lbl_806D61F4);
        break;
    }
    Item_DecayVelocityScalar(self, lbl_806D6204);
}

void TornadoLaunch_Tick(char *self)
{
    TIVec3 pos;
    TIVec3 rot;
    char *sub = self + 0xec;

    switch (TI_S8(self, 0xc8)) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x4e);
        TI_U8(self, 0x8c) = 4;
        TI_U8(self, 0x8d) = 0;
        TI_U8(self, 0xc8) = 1;
        TI_U8(self, 0xc9) = 0;
        /* fall through */
    case 1:
        TornadoItem_TickActive(self, sub);
        break;
    case 2:
        switch (TI_S8(self, 0xcb)) {
        case 3:
            switch (TI_S8(self, 0xc9)) {
            case 0:
                GetSpawnPosition(self + 0xb8, lbl_806D61F0, lbl_806D61F0, lbl_806D61F0);
                TI_U8(self, 0x3c) = 0;
                TI_F32(sub, 0x14) = lbl_806D61F0;
                TI_F32(sub, 0x18) = TI_F32(self, 0xc4);
                TI_U8(self, 0xc9) = TI_U8(self, 0xc9) + 1;
                /* fall through */
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(self, sub + 0x14, TI_F32(sub, 0x18), lbl_806D61F4, lbl_806D61F4) != 0) {
                TI_U8(self, 0x28) = 0;
                TI_U8(self, 0xc8) = 3;
                TI_U8(self, 0xc9) = 0;
            }
            break;
        case 4:
            TornadoLaunch_FadeOut(self, sub);
            break;
        case 7:
            TornadoLaunch_FadeOut(self, sub);
            break;
        case 9:
            TornadoLaunch_FadeOut(self, sub);
            break;
        case 5:
            TornadoLaunch_FadeOut(self, sub);
            break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }

    Vec3_Add_DestFirst((float *)(self + 0xa0), (float *)(self + 0xa0), (float *)(self + 0xb8));
    rot = *(TIVec3 *)(self + 0xac);
    pos = *(TIVec3 *)(self + 0xa0);
    SpriteSlot_SetTransform(self + 0x14, &pos, &rot, TI_F32(self, 0xc4));
    if (TI_U32(sub, 4) != 0) {
        TI_U32(sub, 4) = TI_U32(sub, 4) - 1;
    }
    if (TI_U32(sub, 8) != 0) {
        TI_U32(sub, 8) = TI_U32(sub, 8) - 1;
    }
    if (TI_U32(sub, 0xc) != 0) {
        TI_U32(sub, 0xc) = TI_U32(sub, 0xc) - 1;
    }
    if (TI_U32(sub, 0x10) != 0) {
        TI_U32(sub, 0x10) = TI_U32(sub, 0x10) - 1;
    }
}
#pragma exceptions reset
