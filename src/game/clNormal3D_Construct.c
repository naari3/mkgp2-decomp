/*
 * clNormal3D_Construct @ 0x80034798 (size 0x9C).
 *
 * NonMatching (~79% via objdiff). All 22 store instructions match target byte
 * for byte; the only difference is a 2-instruction prologue schedule swap that
 * the CW 1.3.2 scheduler refuses to reproduce from this source form.
 *
 * Target prologue (8 instr): li r8 / stw r0 / li r7 / **lfs f0** / **li r0,1**
 *                              / stw r31 / mr r31 / **li r5,0**
 * My prologue   (8 instr): li r8 / stw r0 / li r7 / **li r0,1** / **li r5,0**
 *                              / stw r31 / mr r31 / **lfs f0**
 *
 * Same 8 instructions, target hoists the lfs and sinks li r5 (mode for the
 * tail call). 6 attempts exhausted (split decl init, separate mode local,
 * register hint, scheduling pragma toggle): the swap is sticky.  Held as
 * NonMatching to keep the dtk auto-blob fallback while preserving the C
 * source for a future retry once the scheduler quirk is understood.
 *
 * Constructor for clNormal3D (~90 callers, e.g. LakituStart_Init @ 0x8003DB40).
 * Caller pattern: self = Alloc(0x5C); clNormal3D_Construct(self, name, useSkin);
 * ptr[slot] = self;
 *
 * The body zero-clears most pointer / vec3 / flag fields, primes four "alpha"
 * floats and the scale-speed slot with 1.0f (the shared sda2 constant at
 * lbl_806D237C), seeds jobjCount with the -1 "uncomputed" sentinel, marks the
 * instance enabled, then tail-calls clNormal3D_Load to populate everything
 * else. r3 (self) is preserved across the call via callee-saved r31 so the
 * function can return self (classic C++ ctor-chain idiom).
 *
 * Notable store ordering observations (locked to the target asm):
 *   - scaleSpeed (stfs @ 0x08) is emitted after the first three ptr stores
 *     but before the byte/vec3 stores; matches statement ordering below.
 *   - jobjRoot (stw @ 0x2c) is written twice (double-store; preserved here
 *     by writing self->jobjRoot = NULL again on the second slot).
 *   - animIdx (stw @ 0x3c) is emitted after jobjCount (stw @ 0x44); this is
 *     the order that fell out of the Ghidra plate and matches the target.
 *
 * Struct layout (size 0x60, derived from offsets observed in the asm; pads
 * are explicit so CW does not get creative with field gaps):
 *   +0x00 _pad_00       1 byte
 *   +0x01 flag_01       u8
 *   +0x02 _pad_02       1 byte
 *   +0x03 flag_03       u8     (called "loaded" in the Ghidra plate)
 *   +0x04 _pad_04       4 bytes
 *   +0x08 scaleSpeed    float  (was incorrectly labelled 0x14 in the plate)
 *   +0x0c _pad_0c       12 bytes
 *   +0x18 pos_18, +0x1c pos_1c, +0x20 pos_20   3 ints (vec3-like)
 *   +0x24 archive, +0x28 sceneData, +0x2c jobjRoot   3 ptrs
 *   +0x30 modelM        ptr
 *   +0x34 _pad_34       4 bytes
 *   +0x38 flag_38, +0x39 flag_39                u8 x2
 *   +0x3a _pad_3a       2 bytes
 *   +0x3c animIdx       int
 *   +0x40 jobjList      ptr
 *   +0x44 jobjCount     int   (signed; stores -1 as sentinel)
 *   +0x48 enabled       u8
 *   +0x49 _pad_49       3 bytes
 *   +0x4c alpha_4c, +0x50 alpha_50, +0x54 alpha_54, +0x58 alpha_58   floats
 *   +0x5c _pad_5c       4 bytes (tail pad to size 0x60)
 */

typedef unsigned char u8;

struct clNormal3D_Partial {
    u8    _pad_00;        /* +0x00 */
    u8    flag_01;        /* +0x01 */
    u8    _pad_02;        /* +0x02 */
    u8    flag_03;        /* +0x03 (Ghidra plate "loaded") */
    u8    _pad_04[4];     /* +0x04 */
    float scaleSpeed;     /* +0x08 */
    u8    _pad_0c[12];    /* +0x0c */
    int   pos_18;         /* +0x18 */
    int   pos_1c;         /* +0x1c */
    int   pos_20;         /* +0x20 */
    void *archive;        /* +0x24 */
    void *sceneData;      /* +0x28 */
    void *jobjRoot;       /* +0x2c */
    void *modelM;         /* +0x30 */
    u8    _pad_34[4];     /* +0x34 */
    u8    flag_38;        /* +0x38 */
    u8    flag_39;        /* +0x39 */
    u8    _pad_3a[2];     /* +0x3a */
    int   animIdx;        /* +0x3c */
    void *jobjList;       /* +0x40 */
    int   jobjCount;      /* +0x44 */
    u8    enabled;        /* +0x48 */
    u8    _pad_49[3];     /* +0x49 */
    float alpha_4c;       /* +0x4c */
    float alpha_50;       /* +0x50 */
    float alpha_54;       /* +0x54 */
    float alpha_58;       /* +0x58 */
    u8    _pad_5c[4];     /* +0x5c */
};

extern float lbl_806D237C;  /* sda2-resident 1.0f shared default */

extern void clNormal3D_Load(struct clNormal3D_Partial *self, void *filename,
                            int mode, char useSkinModel);

#pragma exceptions on
struct clNormal3D_Partial *clNormal3D_Construct(struct clNormal3D_Partial *self,
                                                void *filename,
                                                char useSkinModel) {
    float defaultF = lbl_806D237C;

    self->archive    = (void *)0;
    self->sceneData  = (void *)0;
    self->jobjRoot   = (void *)0;
    self->scaleSpeed = defaultF;
    self->flag_03    = 0;
    self->pos_18     = 0;
    self->pos_1c     = 0;
    self->pos_20     = 0;
    self->flag_01    = 0;
    self->jobjRoot   = (void *)0;   /* intentional double-store */
    self->modelM     = (void *)0;
    self->flag_38    = 0;
    self->flag_39    = 0;
    self->jobjList   = (void *)0;
    self->jobjCount  = -1;
    self->animIdx    = 0;
    self->enabled    = 1;
    self->alpha_4c   = defaultF;
    self->alpha_50   = defaultF;
    self->alpha_54   = defaultF;
    self->alpha_58   = defaultF;
    clNormal3D_Load(self, filename, 0, useSkinModel);
    return self;
}
