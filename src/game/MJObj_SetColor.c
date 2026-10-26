/* Set an MJObj's RGBA colour, clamping each channel to 0..255. */
typedef struct MJObj {
    unsigned char pad00[0x88];
    unsigned char rgba[4]; /* 0x88 */
} MJObj;

extern unsigned char lbl_806D24A0[8]; /* source file name */
extern char lbl_802E9D04[];           /* assert condition */
extern unsigned int lbl_803F57E0[];   /* MJObj class info */
extern int hsdObjIsDescendantOf(void *obj, void *info);
extern void __assert(const char *file, int line, const char *cond);

#define CLAMP_U8(dst, v)      \
    if ((v) > 0xff) {         \
        (dst) = 0xff;         \
    } else if ((v) < 0) {     \
        (dst) = 0;            \
    } else {                  \
        (dst) = (v);          \
    }

void MJObj_SetColorRGBA(MJObj *self, int r, int g, int b, int a)
{
    if (!hsdObjIsDescendantOf(self, lbl_803F57E0)) {
        __assert((const char *)lbl_806D24A0, 0x31, lbl_802E9D04);
    }
    CLAMP_U8(self->rgba[0], r);
    CLAMP_U8(self->rgba[1], g);
    CLAMP_U8(self->rgba[2], b);
    CLAMP_U8(self->rgba[3], a);
}
