struct CelebVec { float x,y,z; };
/* Ghidra currently exposes an untyped parent; fields verified against target. */
struct CelebEffect { char pad00[0x10]; int index; char pad14[0x78]; CelebVec position; };
extern "C" {
void CelebPop17_Update(CelebEffect *);
CelebEffect *DrawEffect_SpawnDirect(void (*)(CelebEffect *));
void Vec3_Copy(CelebVec *, const CelebVec *);
void DrawEffect_Free(CelebEffect *);
void CelebPop17_SpawnAll(CelebEffect *parent) {
    for (int i = 0; i < 17; ++i) {
        CelebEffect *child = DrawEffect_SpawnDirect(CelebPop17_Update);
        if (child) { child->index = i; Vec3_Copy(&child->position, &parent->position); }
    }
    DrawEffect_Free(parent);
}
}
