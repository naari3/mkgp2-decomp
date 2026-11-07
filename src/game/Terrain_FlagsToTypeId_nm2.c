extern int g_cupId;
extern int g_courseVariantIdx;
extern const float lbl_806D48B0;
extern const float lbl_806D48B4;
extern const float lbl_806D48B8;
extern const float lbl_806D48BC;
extern const float lbl_806D48C0;

static inline unsigned int Terrain_PatchHi(unsigned int flags)
{
    unsigned int mask = 0;
    unsigned int add = 0;
    if (flags & 0x800000) {
        mask |= 0x800000;
        add |= 0x100000;
    }
    flags &= mask;
    flags |= add;
    return flags;
}

static inline float Terrain_SlipForFlags(unsigned int flags, int cup)
{
    unsigned int f = flags & 0xA00000;
    float v = lbl_806D48B8;
    if (cup == 2 && g_courseVariantIdx == 1) {
        v = lbl_806D48BC;
    }
    if (f & 0x200000) {
        v *= lbl_806D48C0;
    }
    if (f & 0x800000) {
        v *= lbl_806D48B0;
    }
    return v;
}

/* Matches with common-subexpression elimination off for this function: the
 * cup id is read once into a local and shared with the slip helper. */
#pragma opt_common_subs off
float Terrain_GetSlipFactor(unsigned int flags)
{
    unsigned int hi = flags;
    unsigned int f = flags & 0xFF0FFFFF;
    int cup = g_cupId;
    if (cup == 2 && (f & 0x80)) {
        f &= ~0x80;
        f |= 0x40;
        hi = Terrain_PatchHi(flags);
    }
    f |= hi & 0xF00000;
    return Terrain_SlipForFlags(f, cup);
}
#pragma opt_common_subs reset
