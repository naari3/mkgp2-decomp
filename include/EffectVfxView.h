/* Target-observed narrow layout; live Ghidra types unavailable. */
struct EffectVfxView {
    unsigned char flags;
    char pad01[3];
    void *slot;
    char pad08[12];
    signed char active;
    char pad15[3];
    float alpha;
    float x, y, z;
};
struct EffectVfxVec { float x,y,z; };
