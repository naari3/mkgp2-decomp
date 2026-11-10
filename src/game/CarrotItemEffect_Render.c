/* CarrotItemEffect_Render (0x800B23CC): draws the carrot item effect. Three
 * carrot models are placed at spawn points projected through the course
 * camera and rendered, then the two trailing ribbons are drawn as quads
 * through each carrot's matrix. The local tables are copied from the
 * shared .rodata block that starts at CelebPop17Update_rodata_80328EB8 (see KartShellRibbonDraw). */
#include "game/types/Vec.h"

typedef struct CarrotF3 { float v[3]; } CarrotF3;
typedef struct CarrotPts { Vec p[8]; } CarrotPts;
typedef struct CarrotUvIdx { int i[4][2]; } CarrotUvIdx;

typedef struct CarrotRodata {
    unsigned char pad000[0x530];
    CarrotF3 depth;     /* 0x530 */
    CarrotPts pts;      /* 0x53C */
    CarrotUvIdx uvIdx;  /* 0x59C */
} CarrotRodata;

typedef struct CarrotSub {
    unsigned char pad00[0x8];
    int ids[2];         /* 0x08 */
    unsigned char pad10[0x10];
    float pos[3][2];    /* 0x20 */
} CarrotSub;

typedef struct CarrotEffect {
    unsigned char pad000[0x18];
    void *model;        /* 0x18 */
    unsigned char pad01C[0xEC - 0x1C];
    CarrotSub sub;      /* 0xEC */
} CarrotEffect;

extern CarrotRodata CelebPop17Update_rodata_80328EB8;
extern void *g_courseScene3D;
extern const float lbl_806D5020;
extern const float lbl_806D5024;
extern const float lbl_806D5028;
extern const float lbl_806D509C;
extern const float lbl_806D50A0;
extern const float lbl_806D50D4;
extern const float lbl_806D50D8;
extern const float lbl_806D50DC;
extern const float lbl_806D50E0;

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
extern void GetSpawnPosition(Vec *out, float x, float y, float z);
extern float (*CObj_GetProjMatrix_Cached(void *cobj))[4];
extern void PSMTXMultVec(float m[3][4], Vec *src, Vec *dst);
extern void Vec3_Copy(Vec *dst, Vec *src);
extern void CObj_LoadProjMatrix(void *cobj, Vec *out);
extern void CObj_ApplyScissor(void *cobj, Vec *out);
extern float Vec3_PitchTo(Vec *from, Vec *to);
extern float Vec3_HorizontalYawTo(Vec *from, Vec *to);
extern void Matrix4_Identity(float m[4][4]);
extern void Mtx44_Scale_Uniform(float dst[4][4], float src[4][4], float s);
extern void Matrix4_PreMultiplyRotX(float dst[4][4], float src[4][4], float angle);
extern void Matrix4_PreMultiplyRotY(float dst[4][4], float src[4][4], float angle);
#ifdef __MWERKS__
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec v);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec *);
static inline void Mtx44_Translate_ByValue(float dst[4][4], float src[4][4], Vec v) { Mtx44_Translate(dst, src, &v); }
#define Mtx44_Translate Mtx44_Translate_ByValue
#endif
extern void DbgScene_CopyMatrix3x4Transpose(float dst[3][4], float src[4][4]);
extern void Object_BindMatrixSource(void *obj, float m[3][4], int flag);
extern void Object_DriveAnimMatrix(void *obj);
extern void Object_RenderJObjTree(void *obj, int flags);
extern unsigned char fn_80231B74(int id);
extern unsigned char fn_8011D890(int id, float uv[2][2], int flags);
#ifdef __MWERKS__
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec v);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_TransformVec3(Vec *, float m[4][4], Vec *);
static inline void Mtx44_TransformVec3_ByValue(Vec *out, float m[4][4], Vec v) { Mtx44_TransformVec3(out, m, &v); }
#define Mtx44_TransformVec3 Mtx44_TransformVec3_ByValue
#endif

#include "game/types/WGPipeWord.h"

#define GXWGFifo (*(volatile WGPipeWord *)0xCC008000)

static inline unsigned char Carrot_SetupGX(void)
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

static inline void Carrot_ToCamera(Vec *pos, Vec in)
{
    Vec v;
    v.x = lbl_806D509C * (in.x - lbl_806D5020);
    v.y = lbl_806D50A0 * (in.y - lbl_806D5024);
    v.z = in.z - lbl_806D5028;
    PSMTXMultVec((float (*)[4])CObj_GetProjMatrix_Cached(g_courseScene3D), &v, &v);
    Vec3_Copy(pos, &v);
}

static inline void Carrot_Billboard(float m[4][4])
{
    Vec eye, at;
    float yaw;
    float pitch;
    CObj_LoadProjMatrix(g_courseScene3D, &eye);
    CObj_ApplyScissor(g_courseScene3D, &at);
    pitch = Vec3_PitchTo(&at, &eye);
    yaw = Vec3_HorizontalYawTo(&at, &eye);
    Matrix4_Identity(m);
    Mtx44_Scale_Uniform(m, m, lbl_806D50D4);
    Matrix4_PreMultiplyRotX(m, m, pitch);
    Matrix4_PreMultiplyRotY(m, m, yaw);
}

void CarrotItemEffect_Render(CarrotEffect *self)
{
    int i;
    int k;
    int j;
    CarrotRodata *rd = &CelebPop17Update_rodata_80328EB8;
    CarrotSub *sub = &self->sub;
    Vec out[2][3][4];
    float m34[3][3][4];
    float m[3][4][4];
    Vec pts[8];
    int uvIdx[4][2];
    CarrotF3 depth;
    Vec pos;
    float uv[2][2];

    for (i = 0; i < 3; i++) {
        depth = rd->depth;
        GetSpawnPosition(&pos, sub->pos[i][0], sub->pos[i][1], depth.v[i]);
        Carrot_ToCamera(&pos, pos);
        Carrot_Billboard(m[i]);
        Mtx44_Translate(m[i], m[i], pos);
        DbgScene_CopyMatrix3x4Transpose(m34[i], m[i]);
    }
    for (i = 0; i < 3; i++) {
        Object_BindMatrixSource(self->model, m34[i], 0);
        Object_DriveAnimMatrix(self->model);
        Object_RenderJObjTree(self->model, 7);
    }

    if (Carrot_SetupGX()) {
        *(CarrotPts *)pts = rd->pts;
        *(CarrotUvIdx *)uvIdx = rd->uvIdx;
        if (sub->ids[1] != -1) {
            if (!fn_80231B74(sub->ids[0])) {
                pts[0].y += lbl_806D50D8;
                pts[1].y += lbl_806D50D8;
                pts[2].y += lbl_806D50D8;
                pts[3].y += lbl_806D50D8;
            } else {
                float s = lbl_806D50DC;
                for (k = 0; k < 4; k++) {
                    Vec *p = &pts[k];
                    p->x *= s;
                    p->y *= s;
                    p->y -= lbl_806D50E0;
                }
            }
        }
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 4; k++) {
                Mtx44_TransformVec3(&out[0][j][k], m[j], pts[k]);
                Mtx44_TransformVec3(&out[1][j][k], m[j], pts[k + 4]);
            }
        }
        for (i = 1; i >= 0; i--) {
            if (sub->ids[i] != -1) {
                if (!fn_8011D890(sub->ids[i], uv, 0)) {
                    return;
                }
                for (j = 0; j < 3; j++) {
                    GXBegin(0x80, 0, 4);
                    for (k = 0; k < 4; k++) {
                        GXWGFifo.f = out[i][j][k].x;
                        GXWGFifo.f = out[i][j][k].y;
                        GXWGFifo.f = out[i][j][k].z;
                        GXWGFifo.u = -1;
                        GXWGFifo.f = uv[uvIdx[k][0]][0];
                        GXWGFifo.f = uv[uvIdx[k][1]][1];
                    }
                }
            }
        }
        HSD_StateInvalidate(-1);
    }
}
