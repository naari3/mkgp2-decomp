#include "mkgp2_names.h"
#define HSD_JObjSetupMatrix jobj_header_setup_matrix
#include "jobj_unlock_private.h"
#undef HSD_JObjSetupMatrix
#define HSD_CObjGetViewingMtxPtrDirect jobj_header_viewing_matrix
#include "cobj.h"
#undef HSD_CObjGetViewingMtxPtrDirect
#include <dolphin/mtx.h>

extern void HSD_JObjSetupMatrix(HSD_JObj* jobj);
extern MtxPtr HSD_CObjGetViewingMtxPtrDirect(HSD_CObj* cobj);
extern void JObjMakeInstanceMtx(MtxPtr vmtx, HSD_JObj* jobj, Mtx mtx);

#pragma push
#pragma inline_max_size(700)
/* The last expanded level uses the original general instance helper. */
static inline void JObjDispLevel3(HSD_JObj* jobj, Mtx vmtx, u32 flags, u32 rendermode)
{
    HSD_JObj* child;
    if (jobj == NULL) {
        return;
    }
    if (jobj->flags & JOBJ_INSTANCE) {
        if (!(jobj->flags & JOBJ_HIDDEN)) {
            Mtx mtx;
            JObjMakeInstanceMtx(vmtx, jobj, mtx);
            HSD_JObjDispAll(jobj->child, mtx, flags, rendermode);
        }
    } else {
        if (jobj->flags & (flags << 18)) {
            HSD_JObjDisp(jobj, vmtx, flags, rendermode);
        }
        if (jobj->flags & (flags << 28)) {
            for (child = jobj->child; child != NULL; child = child->next) {
                HSD_JObjDispAll(child, vmtx, flags, rendermode);
            }
        }
    }
}
/* This path receives the enclosing instance matrix, which is always valid. */
static inline void JObjDispLevel2Instance(HSD_JObj* jobj, Mtx vmtx, u32 flags, u32 rendermode)
{
    HSD_JObj* child;
    if (jobj == NULL) {
        return;
    }
    if (jobj->flags & JOBJ_INSTANCE) {
        if (!(jobj->flags & JOBJ_HIDDEN)) {
            Mtx mtx;
            HSD_JObjSetupMatrix(jobj);
            HSD_JObjSetupMatrix(jobj->child);
            PSMTXInverse(jobj->child->mtx, mtx);
            PSMTXConcat(jobj->mtx, mtx, mtx);
            PSMTXConcat(vmtx, mtx, mtx);
            JObjDispLevel3(jobj->child, mtx, flags, rendermode);
        }
    } else {
        if (jobj->flags & (flags << 18)) {
            HSD_JObjDisp(jobj, vmtx, flags, rendermode);
        }
        if (jobj->flags & (flags << 28)) {
            for (child = jobj->child; child != NULL; child = child->next) {
                JObjDispLevel3(child, vmtx, flags, rendermode);
            }
        }
    }
}
static inline void JObjDispLevel2(HSD_JObj* jobj, Mtx vmtx, u32 flags, u32 rendermode)
{
    HSD_JObj* child;
    if (jobj == NULL) {
        return;
    }
    if (jobj->flags & JOBJ_INSTANCE) {
        if (!(jobj->flags & JOBJ_HIDDEN)) {
            Mtx mtx;
            HSD_CObj* cobj;
            HSD_JObjSetupMatrix(jobj);
            HSD_JObjSetupMatrix(jobj->child);
            PSMTXInverse(jobj->child->mtx, mtx);
            PSMTXConcat(jobj->mtx, mtx, mtx);
            if (vmtx != NULL) {
                PSMTXConcat(vmtx, mtx, mtx);
            } else {
                cobj = HSD_CObjGetCurrent();
                if (cobj != NULL) {
                    PSMTXConcat(HSD_CObjGetViewingMtxPtrDirect(cobj), mtx, mtx);
                }
            }
            JObjDispLevel3(jobj->child, mtx, flags, rendermode);
        }
    } else {
        if (jobj->flags & (flags << 18)) {
            HSD_JObjDisp(jobj, vmtx, flags, rendermode);
        }
        if (jobj->flags & (flags << 28)) {
            for (child = jobj->child; child != NULL; child = child->next) {
                JObjDispLevel3(child, vmtx, flags, rendermode);
            }
        }
    }
}
void HSD_JObjDispAll(HSD_JObj* jobj, Mtx vmtx, u32 flags, u32 rendermode)
{
    if (jobj == NULL) {
        return;
    }
    if (jobj->flags & JOBJ_INSTANCE) {
        if (!(jobj->flags & JOBJ_HIDDEN)) {
            Mtx mtx;
            HSD_CObj* cobj;
            jobj_header_setup_matrix(jobj);
            jobj_header_setup_matrix(jobj->child);
            PSMTXInverse(jobj->child->mtx, mtx);
            PSMTXConcat(jobj->mtx, mtx, mtx);
            if (vmtx != NULL) {
                PSMTXConcat(vmtx, mtx, mtx);
            } else {
                cobj = HSD_CObjGetCurrent();
                if (cobj != NULL) {
                    PSMTXConcat(cobj->view_mtx, mtx, mtx);
                }
            }
            JObjDispLevel2Instance(jobj->child, mtx, flags, rendermode);
        }
    } else {
        if (jobj->flags & (flags << 18)) {
            HSD_JObjDisp(jobj, vmtx, flags, rendermode);
        }
        if (jobj->flags & (flags << 28)) {
            for (jobj = jobj->child; jobj != NULL; jobj = jobj->next) {
                JObjDispLevel2(jobj, vmtx, flags, rendermode);
            }
        }
    }
}
#pragma pop
