/* Observed 92-byte storage only. Real constructor preserves implicit return-this.
 * Prior six plain-C schedule/local/register probes are not repeated.
 * Ghidra unavailable: authoritative target and full Load ASM establish the ABI.
 * filename and the full incoming useSkin word are forwarded; Load masks its byte.
 */
#pragma cplusplus on
#pragma exceptions on

typedef unsigned char u8;

struct Normal3D {
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
    Normal3D(void *filename, int useSkinModel);
};

extern "C" const float lbl_806D237C; /* Original DOL BF800000: -1.0f. */

extern "C" int clNormal3D_Load(Normal3D *self, void *filename, int mode, int useSkinModel);

Normal3D::Normal3D(void *filename, int useSkinModel) {
    float defaultF = lbl_806D237C;

    archive    = (void *)0;
    sceneData  = (void *)0;
    jobjRoot   = (void *)0;
    scaleSpeed = defaultF;
    flag_03    = 0;
    pos_18     = 0;
    pos_1c     = 0;
    pos_20     = 0;
    flag_01    = 0;
    jobjRoot   = (void *)0;   /* intentional double-store */
    modelM     = (void *)0;
    flag_38    = 0;
    flag_39    = 0;
    jobjList   = (void *)0;
    jobjCount  = -1;
    animIdx    = 0;
    enabled    = 1;
    alpha_4c   = defaultF;
    alpha_50   = defaultF;
    alpha_54   = defaultF;
    alpha_58   = defaultF;
    clNormal3D_Load(this, filename, 0, useSkinModel);
}
