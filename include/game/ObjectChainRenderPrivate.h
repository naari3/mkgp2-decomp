#ifndef OBJECT_CHAIN_RENDER_PRIVATE_H
#define OBJECT_CHAIN_RENDER_PRIVATE_H
#include "sysdolphin/baselib/jobj.h"
typedef float ChainMtx[3][4];
typedef struct ChainVec { float x, y, z; } ChainVec;
typedef struct ChainCamera { char pad[0x74]; ChainMtx view; ChainVec eye; } ChainCamera;
extern void __assert(const char *, int, const char *);
extern const char lbl_806D2684[7], lbl_806D268C[5];
extern const float lbl_806D2680, lbl_806D2694, lbl_806D2698;
extern void HSD_JObjSetupMatrixSub(HSD_JObj *);
extern int JObj_NeedsEval(HSD_JObj *);
extern void JObj_EvalIfDirty(HSD_JObj *);
extern float (*JObj_EvalIfDirtyAndGetMtxPtr(HSD_JObj *))[4];
extern void PSMTXMultVec(ChainMtx, ChainVec *, ChainVec *);
extern void Object_BindMatrixSource(void *, ChainMtx, int);
extern void Object_DriveAnimMatrix(void *);
extern void Object_RenderJObjTree(void *, int);
extern HSD_JObj *LinkedNode_GetField10_OrFallback(void *, HSD_JObj *);
#endif
