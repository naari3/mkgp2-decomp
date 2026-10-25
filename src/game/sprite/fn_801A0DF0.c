extern int lbl_80678A0C[];
extern int lbl_806D16E8;
extern void SpriteHandle_SetActiveFlag(int h, int flag);
extern void SpriteHandle_RecomputeCull(int h);

void fn_801A0DF0(void) {
    if (lbl_80678A0C[lbl_806D16E8] != -1) {
        SpriteHandle_SetActiveFlag(lbl_80678A0C[lbl_806D16E8], 1);
        SpriteHandle_RecomputeCull(lbl_80678A0C[lbl_806D16E8]);
        lbl_806D16E8++;
    }
}
