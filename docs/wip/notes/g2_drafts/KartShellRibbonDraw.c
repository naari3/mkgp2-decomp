/* KartShellRibbonDraw (0x800B3250): draws the shell-ribbon board behind a
 * kart. It sets up a one-texture, vertex-colour GX pass, then draws the
 * back panel (texture 0x174) and the front ribbon (texture 0x170) as quads
 * through the effect's transposed world matrix. Front ribbons in the
 * "stretched" id ranges are rebuilt from the texture's own size, centred on
 * the panel. The local tables are copied from the shared .rodata block
 * that starts at rd-> */
typedef struct Vec { float x, y, z; } Vec;

typedef struct RibbonPts { Vec p[8]; } RibbonPts;
typedef struct RibbonSigns { int s[8][2]; } RibbonSigns;
typedef struct RibbonF4 { float v[4]; } RibbonF4;
typedef struct RibbonUvIdx { int i[4][2]; } RibbonUvIdx;

typedef struct RibbonRodata {
    unsigned char pad000[0x438];
    RibbonPts pts;      /* 0x438 */
    RibbonSigns signs;  /* 0x498 */
    RibbonF4 dims;      /* 0x4D8 */
    RibbonF4 ctr;       /* 0x4E8 */
    RibbonUvIdx uvIdx;  /* 0x4F8 */
} RibbonRodata;

extern RibbonRodata CelebPop17Update_rodata_80328EB8;
extern const float lbl_806D6DE4;
extern const float lbl_806D5028; /* 1.0f */
extern const float lbl_806D5034; /* 0.0f */
extern const float lbl_806D503C; /* lbl_806D503C */
extern const float lbl_806D5054; /* 10.0f */
extern const float lbl_806D50AC; /* 0.5f */
extern const float lbl_806D50DC; /* 1.4f */
extern const float lbl_806D5118; /* 1.0f / 64 */

extern void *HSD_CObjGetCurrent(void);
extern void *HSD_CObjGetViewingMtxPtr(void *cobj);
extern void HSD_StateSetCullMode(int mode);
extern void HSD_StateInvalidate(int state);
extern void GXLoadPosMtxImm(void *mtx, int id);
extern void GXSetCurrentMtx(int id);
extern void GXSetAlphaCompare(int comp0, int ref0, int op, int comp1, int ref1);
extern void GXSetChanCtrl(int chan, int enable, int amb, int mat, int lights, int diff, int attn);
extern void GXSetZMode(int enable, int func, int update);
extern void GXSetBlendMode(int type, int src, int dst, int op);
extern void GXSetNumTexGens(int n);
extern void GXSetTexCoordGen2(int dst, int func, int src, int mtx, int normalize, int ptmtx);
extern void GXSetNumChans(int n);
extern void GXSetNumTevStages(int n);
extern void GXSetTevOrder(int stage, int coord, int map, int color);
extern void GXSetTevOp(int stage, int mode);
extern void GXClearVtxDesc(void);
extern void GXSetVtxDesc(int attr, int type);
extern void GXSetVtxAttrFmt(int fmt, int attr, int cnt, int type, int frac);
extern void GXBegin(int prim, int fmt, int n);
extern unsigned int __cvt_fp2unsigned(float f);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec v);
extern float FAbs_FloatAsDouble(float f);
extern unsigned char fn_8011D890(int id, float uv[2][2], int flags);
extern void ResourceTable_GetSizeXY(int id, float *x, float *y);

typedef union {
    float f;
    unsigned int u;
} WGPipeWord;

#define GXWGFifo (*(volatile WGPipeWord *)0xCC008000)

static inline unsigned char Ribbon_SetupGX(void)
{
    void *cobj = HSD_CObjGetCurrent();
    if (cobj == 0) {
        return 0;
    }
    GXLoadPosMtxImm(HSD_CObjGetViewingMtxPtr(cobj), 0);
    GXSetCurrentMtx(0);
    GXSetAlphaCompare(4, 0, 1, 4, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    HSD_StateSetCullMode(0);
    GXSetZMode(1, 3, 1);
    GXSetBlendMode(1, 4, 5, 15);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevOp(0, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxDesc(11, 1);
    GXSetVtxAttrFmt(0, 11, 1, 5, 0);
    GXSetVtxDesc(13, 1);
    GXSetVtxAttrFmt(0, 13, 1, 4, 0);
    return 1;
}

static inline int Ribbon_GetKind(int id)
{
    switch (id) {
    case 0xC32: case 0xC33: case 0xC34: case 0xC35: case 0xC36: case 0xC37: case 0xC38:
    case 0xC39: case 0xC3A: case 0xC3B: case 0xC3C: case 0xC3D: case 0xC3E:
        return 1;
    case 0xC49: case 0xC4A: case 0xC4B: case 0xC4C:
    case 0xC51: case 0xC52: case 0xC53: case 0xC54:
    case 0xC59: case 0xC5A: case 0xC5B: case 0xC5C:
    case 0xC5E:
    case 0xC61: case 0xC62:
        return 0;
    default:
        return 2;
    }
}

void KartShellRibbonDraw(unsigned char *self)
{
    RibbonRodata *rd = &CelebPop17Update_rodata_80328EB8;

    if (Ribbon_SetupGX()) {
        int color;
        Vec pts[8];
        float m[4][4];
        int signs[8][2];
        Vec out[4];
        int uvIdx[4][2];
        float dims[4];
        float ctr[4];
        float uv0[2][2];
        Vec v;
        Vec p;
        float uv1[2][2];
        int i;

        color = __cvt_fp2unsigned(lbl_806D503C * *(float *)(self + 0x2C)) | -0x100;
        Mtx_TransposeToMtx44(m, self + 0x48);
        *(RibbonPts *)pts = rd->pts;
        *(RibbonSigns *)signs = rd->signs;
        *(RibbonF4 *)dims = rd->dims;
        dims[0] = FAbs_FloatAsDouble(pts[0].x - pts[1].x);
        dims[1] = FAbs_FloatAsDouble(pts[1].y - pts[2].y);
        dims[2] = FAbs_FloatAsDouble(pts[4].x - pts[5].x);
        dims[3] = FAbs_FloatAsDouble(pts[5].y - pts[6].y);
        *(RibbonF4 *)ctr = rd->ctr;
        ctr[0] = (pts[0].x + pts[1].x) * lbl_806D50AC;
        ctr[1] = (pts[1].y + pts[2].y) * lbl_806D50AC;
        ctr[2] = (pts[4].x + pts[5].x) * lbl_806D50AC;
        ctr[3] = (pts[5].y + pts[6].y) * lbl_806D50AC;
        *(RibbonUvIdx *)uvIdx = rd->uvIdx;

        if (*(int *)(self + 0x174) != -1) {
            if (!fn_8011D890(*(int *)(self + 0x174), uv0, 0)) {
                return;
            }
            GXBegin(0x80, 0, 4);
            for (i = 0; i < 4; i++) {
                Mtx44_TransformVec3(&v, m, pts[i + 4]);
                GXWGFifo.f = v.x;
                GXWGFifo.f = v.y;
                GXWGFifo.f = v.z;
                GXWGFifo.u = color;
                GXWGFifo.f = uv0[uvIdx[i][0]][0];
                GXWGFifo.f = uv0[uvIdx[i][1]][1];
            }
        }

        if (*(int *)(self + 0x170) != -1) {
            int id = *(int *)(self + 0x170);
            int kind = Ribbon_GetKind(id);

            if (kind == 0) {
                for (i = 0; i < 4; i++) {
                    Mtx44_TransformVec3(&out[i], m, pts[i]);
                }
            } else {
                float sx;
                float sy;
                float scale = lbl_806D5028 / (lbl_806D50DC * lbl_806D6DE4);
                float off = lbl_806D5034;
                float halfW;
                float h;
                float cy;

                if (kind == 1) {
                    off = lbl_806D5054;
                }
                ResourceTable_GetSizeXY(id, &sx, &sy);
                halfW = dims[0] * lbl_806D50AC * lbl_806D5118;
                h = dims[1];
                cy = ctr[1];
                for (i = 0; i < 4; i++) {
                    p = pts[i];
                    p.x = scale * (halfW * (sx * lbl_806D50AC));
                    if (signs[i][0] == 1) {
                        p.x = ctr[0] + p.x;
                    } else {
                        p.x = ctr[0] - p.x;
                    }
                    if (signs[i][1] == 1) {
                        p.y = scale * (h * lbl_806D50AC * lbl_806D5118 * (sy * lbl_806D50AC + off));
                    } else {
                        p.y = scale * (h * lbl_806D50AC * lbl_806D5118 * (sy * lbl_806D50AC - off));
                    }
                    if (signs[i][1] == 1) {
                        p.y = cy + p.y;
                    } else {
                        p.y = cy - p.y;
                    }
                    Mtx44_TransformVec3(&out[i], m, p);
                }
            }

            if (!fn_8011D890(*(int *)(self + 0x170), uv1, 0)) {
                return;
            }
            GXBegin(0x80, 0, 4);
            for (i = 0; i < 4; i++) {
                GXWGFifo.f = out[i].x;
                GXWGFifo.f = out[i].y;
                GXWGFifo.f = out[i].z;
                GXWGFifo.u = color;
                GXWGFifo.f = uv1[uvIdx[i][0]][0];
                GXWGFifo.f = uv1[uvIdx[i][1]][1];
            }
        }
        HSD_StateInvalidate(-1);
    }
}
