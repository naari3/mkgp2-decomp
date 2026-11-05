#include "game/ObjectChainRenderPrivate.h"
static inline unsigned char NeedsEval(HSD_JObj *j) {
    unsigned char result;
    if (!j) __assert(lbl_806D2684, 0x25d, lbl_806D268C);
    result = 0;
    if (!(j->flags & 0x800000) && (j->flags & 0x40)) result = 1;
    return result;
}
void ObjectChain_RenderInZRange(ChainCamera *cam, void *arg, HSD_JObj *node, void *obj, float hi, float lo) {
    {
        ChainMtx *mtx;
        ChainVec pos;
        if (!node) __assert(lbl_806D2684, 0x47c, lbl_806D268C);
        if (node && NeedsEval(node)) HSD_JObjSetupMatrixSub(node);
        mtx = (ChainMtx *)((char *)node + 0x44);
        if (hi >= lbl_806D2680) {
            pos.x = (*mtx)[0][3] - cam->eye.x;
            pos.y = (*mtx)[1][3] - cam->eye.y;
            pos.z = (*mtx)[2][3] - cam->eye.z;
            PSMTXMultVec(cam->view, &pos, &pos);
        } else {
            pos.z = hi - lbl_806D2694;
            lo = hi - lbl_806D2698;
        }
        if (lo <= pos.z && pos.z <= hi) {
            Object_BindMatrixSource(obj, *mtx, 0);
            Object_DriveAnimMatrix(obj);
            Object_RenderJObjTree(obj, 7);
        }
        node = LinkedNode_GetField10_OrFallback(obj, node);
        if (node) {
            {
                ChainMtx *mtx;
                ChainVec pos;
                if (!node) __assert(lbl_806D2684, 0x47c, lbl_806D268C);
                if (node && JObj_NeedsEval(node)) HSD_JObjSetupMatrixSub(node);
                mtx = (ChainMtx *)((char *)node + 0x44);
                if (hi >= lbl_806D2680) {
                    pos.x = (*mtx)[0][3] - cam->eye.x;
                    pos.y = (*mtx)[1][3] - cam->eye.y;
                    pos.z = (*mtx)[2][3] - cam->eye.z;
                    PSMTXMultVec(cam->view, &pos, &pos);
                } else {
                    pos.z = hi - lbl_806D2694;
                    lo = hi - lbl_806D2698;
                }
                if (lo <= pos.z && pos.z <= hi) {
                    Object_BindMatrixSource(obj, *mtx, 0);
                    Object_DriveAnimMatrix(obj);
                    Object_RenderJObjTree(obj, 7);
                }
                node = LinkedNode_GetField10_OrFallback(obj, node);
                if (node) {
                    {
                        ChainMtx *mtx;
                        ChainVec pos;
                        if (!node) __assert(lbl_806D2684, 0x47c, lbl_806D268C);
                        JObj_EvalIfDirty(node);
                        mtx = (ChainMtx *)((char *)node + 0x44);
                        if (hi >= lbl_806D2680) {
                            pos.x = (*mtx)[0][3] - cam->eye.x;
                            pos.y = (*mtx)[1][3] - cam->eye.y;
                            pos.z = (*mtx)[2][3] - cam->eye.z;
                            PSMTXMultVec(cam->view, &pos, &pos);
                        } else {
                            pos.z = hi - lbl_806D2694;
                            lo = hi - lbl_806D2698;
                        }
                        if (lo <= pos.z && pos.z <= hi) {
                            Object_BindMatrixSource(obj, *mtx, 0);
                            Object_DriveAnimMatrix(obj);
                            Object_RenderJObjTree(obj, 7);
                        }
                        node = LinkedNode_GetField10_OrFallback(obj, node);
                        if (node) {
                            {
                                ChainMtx *mtx;
                                ChainVec pos;
                                mtx = (ChainMtx *)JObj_EvalIfDirtyAndGetMtxPtr(node);
                                if (hi >= lbl_806D2680) {
                                    pos.x = (*mtx)[0][3] - cam->eye.x;
                                    pos.y = (*mtx)[1][3] - cam->eye.y;
                                    pos.z = (*mtx)[2][3] - cam->eye.z;
                                    PSMTXMultVec(cam->view, &pos, &pos);
                                } else {
                                    pos.z = hi - lbl_806D2694;
                                    lo = hi - lbl_806D2698;
                                }
                                if (lo <= pos.z && pos.z <= hi) {
                                    Object_BindMatrixSource(obj, *mtx, 0);
                                    Object_DriveAnimMatrix(obj);
                                    Object_RenderJObjTree(obj, 7);
                                }
                                node = LinkedNode_GetField10_OrFallback(obj, node);
                                if (node) {
                                    ObjectChain_RenderInZRange(cam, arg, node, obj, hi, lo);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
