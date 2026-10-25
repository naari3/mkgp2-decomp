typedef struct RibbonVec3 {
    float x, y, z;
} RibbonVec3;

typedef struct KartShellRibbon {
    unsigned char pad000[0x8C];
    RibbonVec3 pos;              /* 0x08C */
} KartShellRibbon;

extern unsigned char lbl_805DF3D0[];
extern void *lbl_806D10AC;
extern void KartShellRibbonDraw(void *);
extern void Vec3_Subtract_DestFirst(RibbonVec3 *out, const RibbonVec3 *a, const RibbonVec3 *b);
extern float Vec3_Magnitude_Wrapper(const RibbonVec3 *v);
extern void Vec3_Scale(RibbonVec3 *out, const RibbonVec3 *v, float s);
extern void Vec3_Add_DestFirst(RibbonVec3 *out, const RibbonVec3 *a, const RibbonVec3 *b);
extern void clDrawMan_AddSorted_DepthRange(void *man, void (*draw)(void *), void *obj,
                                           float x, float y, float z, float depth);

static inline void *DrawMan_Get(void)
{
    void *man = lbl_806D10AC;
    if (man == 0) {
        man = 0;
    }
    return man;
}

void KartShellRibbon_DrawCb(KartShellRibbon *self)
{
    RibbonVec3 at;
    RibbonVec3 dir;

    Vec3_Subtract_DestFirst(&dir, (RibbonVec3 *)(lbl_805DF3D0 + 0x80), &self->pos);
    Vec3_Scale(&dir, &dir, 1.0f / Vec3_Magnitude_Wrapper(&dir));
    Vec3_Add_DestFirst(&at, &self->pos, &dir);
    clDrawMan_AddSorted_DepthRange(DrawMan_Get(), KartShellRibbonDraw, self, at.x, at.y, at.z, 0.0f);
}
