#include "mkgp2_names.h"
#define HSD_CObjGetViewingMtxPtrDirect jobj_header_viewing_matrix
#include "cobj.h"
#undef HSD_CObjGetViewingMtxPtrDirect

MtxPtr HSD_CObjGetViewingMtxPtrDirect(HSD_CObj* cobj)
{
    return cobj->view_mtx;
}

#define MKGP2_JOBJ_DEFINE_SETUP
#include "jobj_rescue_private.h"
