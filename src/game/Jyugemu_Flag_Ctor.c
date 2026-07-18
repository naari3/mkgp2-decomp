/*
 * Jyugemu_Flag_Ctor @ 0x80080A74 (size 0xAC) - real C++ ctor retrofit
 * (2026-07-19, docs/notes/cpp-ctor-retrofit-mangled-bridge.md recipe).
 *
 * The target extab (0x28 bytes) carries a live DELETEPOINTER(r29 ->
 * operator delete) guard over the clNormal3D construction (a genuine
 * new-expression), and the branch shape (bne/b over the early exit +
 * per-return-site `mr r3, r30` materialization) is the implicit
 * `return this` of a constructor with early returns.
 *
 * Mangled references bridged via tools/extab_user_renames.json:
 *   __ct__11JyugemuFlagFi   -> Jyugemu_Flag_Ctor       (this definition)
 *   __ct__10clNormal3DFPUii -> clNormal3D_Construct    (new clNormal3D)
 *   __nw__FUl               -> Alloc                   (shared mapping)
 *   __dl__FPv               -> MemoryManager_TimedFree (shared mapping)
 */

struct clNormal3D {
    char _opaque[0x5C];
    clNormal3D(unsigned int *shape, int flag);
};

extern "C" {
extern void clNormal3D_SetScale(clNormal3D *n, int mode, float a, float b,
                                float c, float d);
extern unsigned int lbl_80311DD8[];
extern float lbl_806CEFB8;           /* .sdata  */
extern float lbl_806CEFBC;           /* .sdata  */
extern const float lbl_806D3074;     /* .sdata2 */
}

struct JyugemuFlag {
    clNormal3D *normal;  /* 0x0 */
    int mode;            /* 0x4 */
    int counter;         /* 0x8 */
    JyugemuFlag(int mode);
};

#pragma exceptions on

JyugemuFlag::JyugemuFlag(int mode_) {
    clNormal3D *n;

    this->normal = 0;
    if (mode_ == 0) {
        return;
    }
    this->normal = new clNormal3D(lbl_80311DD8, 0);
    n = this->normal;
    if (n == 0) {
        return;
    }
    clNormal3D_SetScale(n, 0, lbl_806D3074, lbl_806CEFB8,
                        lbl_806D3074, lbl_806CEFBC);
    this->mode = mode_;
    this->counter = 0;
}

#pragma exceptions reset
