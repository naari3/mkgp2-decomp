/* Link-error screen, 0x8008604C..0x80086170.
 * The shared string pool stays in PcbDebugOverlay.c. A single pool base
 * preserves the original references across this TU boundary.
 * FKTex's constructor and unwind destructor bridge to the existing TexMgr
 * implementation; its empty normal-path destructor is inlined away.
 */
typedef struct FKTex {
    unsigned char pad_00[0x18];
    int field18;
    int pad_1C;
    int field20;
    unsigned char pad_24[0x200];
    FKTex();
    ~FKTex() {}
} FKTex;

extern "C" {
extern unsigned char lbl_806D1191;
extern const unsigned int lbl_80311E38[255];
extern const float lbl_806D3180;
extern const float lbl_806D3184;
extern const float lbl_806D3188;
extern const float lbl_806D318C;
extern const float lbl_806D3190;
extern const float lbl_806D3194;

extern void TexMgr_SetTexture(FKTex *tex, const char *name, ...);
extern void fn_801F93EC(FKTex *tex, float x, float y);
extern void *fn_801F8E58(void);
extern void fn_801F8A34(void *list, FKTex *tex, int flags);
extern int isJapanese(void);
extern void fn_8011F994(int arg);

}

extern "C" {
int DrawLinkErrorOverlay(void)
{
    const char *pool = (const char *)lbl_80311E38;

    if (lbl_806D1191 == 0) {
        return 0;
    }
    FKTex tex;
    tex.field18 = 1;
    tex.field20 = -1;
    fn_801F93EC(&tex, lbl_806D3180, lbl_806D3184);
    if (isJapanese() == 0) {
        TexMgr_SetTexture(&tex, pool + 0x500);
    } else {
        TexMgr_SetTexture(&tex, pool + 0x518);
        fn_801F93EC(&tex, lbl_806D3188, lbl_806D3184);
    }
    fn_801F8A34(fn_801F8E58(), &tex, 0);
    fn_801F93EC(&tex, lbl_806D318C, lbl_806D3190);
    if (isJapanese() == 0) {
        TexMgr_SetTexture(&tex, pool + 0x534);
    } else {
        TexMgr_SetTexture(&tex, pool + 0x550);
        fn_801F93EC(&tex, lbl_806D3194, lbl_806D3190);
    }
    fn_801F8A34(fn_801F8E58(), &tex, 0);
    fn_8011F994(0);
    return 1;
}
}
