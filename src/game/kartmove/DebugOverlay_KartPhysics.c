/* 0x801998F8: debug overlay of a kart's terrain flags and grip values.
 * The TU owns its .rodata pool (an unused float table and the formats). */

extern char *Terrain_FlagsToDebugString(int flags);
void OverlayText(int layer, int x, int y, const char *fmt, ...);

typedef struct KartPhys {
    char pad0[0x40];
    float tnsX;
    char pad44[4];
    float tnsY;
    char pad4c[0x2c4 - 0x4c];
    int flagsL;
    int flagsR;
    char pad2cc[0x2f0 - 0x2cc];
    float mueScale;
    float spdScale;
} KartPhys;

const float lbl_8037DD78[3] = {1.0f, 0.7f, 0.9f};

void DebugOverlay_KartPhysics(KartPhys *k) {
    OverlayText(2, 2, 0x12, "left  %s", Terrain_FlagsToDebugString(k->flagsL));
    OverlayText(2, 2, 0x13, "right %s", Terrain_FlagsToDebugString(k->flagsR));
    OverlayText(2, 2, 0x14, "tns %f %f", k->tnsX, k->tnsY);
    OverlayText(2, 2, 0x15, "mue scale   %f", k->mueScale);
    OverlayText(2, 2, 0x16, "spd scale   %f", k->spdScale);
}
