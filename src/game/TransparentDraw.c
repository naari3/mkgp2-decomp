/*
 * TransparentDraw @ 0x80065990..0x8006609C (.text)
 *
 * Transparent-draw entry registration / destruction / sort-and-dispatch.
 * A global slot table (lbl_805987E0, 32 slots of 0x14 bytes in .bss) holds
 * registered entries; SortAndDispatch links their draw objects into a chain
 * (head in lbl_806D10F8) ordered by squared XZ camera distance.
 *
 * Functions:
 *   0x80065990 TransparentDraw_InitEntry        (0x1E4)
 *   0x80065B74 TransparentDraw_DestroyEntry     (0xE8)
 *   0x80065C5C TransparentDraw_ResetEntry       (0x40)
 *   0x80065C9C TransparentDraw_SortAndDispatch  (0x33C)
 *   0x80065FD8 TransparentDraw_RemoveByOwner    (0xC4)
 */

#include "game/types/Vec3.h"

/* draw object: vtable + refcount + intrusive draw chain + position block */
typedef struct TDrawObjVtbl TDrawObjVtbl;

typedef struct TDrawPos {
    unsigned char pad0[0xC];
    float x;    /* 0x0C */
    float y;    /* 0x10 */
    float z;    /* 0x14 */
} TDrawPos;

typedef struct TDrawObj {
    TDrawObjVtbl *vt;         /* 0x00 */
    unsigned short refcount;  /* 0x04 */
    unsigned char pad6[6];
    struct TDrawObj *next;    /* 0x0C */
    unsigned char pad10[8];
    TDrawPos *pos;            /* 0x18 */
} TDrawObj;

struct TDrawObjVtbl {
    unsigned char pad0[0x30];
    void (*fn30)(TDrawObj *); /* 0x30 */
    void (*fn34)(TDrawObj *); /* 0x34 */
};

/* five-word vector attachment block: {head, x, y, z, tail} */
typedef struct TDrawVecBlk {
    unsigned int head;  /* 0x00 */
    float x;            /* 0x04 */
    float y;            /* 0x08 */
    float z;            /* 0x0C */
    unsigned int tail;  /* 0x10 */
} TDrawVecBlk;

/* registered entry (0x6C bytes) */
typedef struct TDrawEntry {
    TDrawObj *handle;     /* 0x00 (result of HSD_LObjLoadDesc) */
    /* params block passed to HSD_LObjLoadDesc starts here (0x04) */
    void *p04;            /* 0x04 */
    void *p08;            /* 0x08 */
    unsigned short mode;  /* 0x0C */
    unsigned short p0E;   /* 0x0E */
    unsigned char r;      /* 0x10 */
    unsigned char g;      /* 0x11 */
    unsigned char b;      /* 0x12 */
    unsigned char a;      /* 0x13 */
    TDrawVecBlk *vecA;    /* 0x14 -> &blkA or 0 */
    TDrawVecBlk *vecB;    /* 0x18 -> &blkB or 0 */
    void *variant;        /* 0x1C -> one of the case blocks below or 0 */
    TDrawVecBlk blkA;     /* 0x20..0x30 */
    TDrawVecBlk blkB;     /* 0x34..0x44 */
    float c1_value;       /* 0x48 (mode&3 == 1) */
    float c2_f0;          /* 0x4C (mode&3 == 2) */
    float c2_f1;          /* 0x50 */
    unsigned int c2_u2;   /* 0x54 */
    float c3_f0;          /* 0x58 (mode&3 == 3) */
    unsigned int c3_u1;   /* 0x5C */
    float c3_f2;          /* 0x60 */
    float c3_f3;          /* 0x64 */
    unsigned int c3_u4;   /* 0x68 */
} TDrawEntry;

/* descriptor passed to InitEntry */
typedef struct TDrawDesc {
    unsigned char pad0[8];
    unsigned short mode;  /* 0x08 */
    unsigned short p0A;   /* 0x0A */
    unsigned char r;      /* 0x0C */
    unsigned char g;      /* 0x0D */
    unsigned char b;      /* 0x0E */
    unsigned char a;      /* 0x0F */
    TDrawVecBlk *vecA;    /* 0x10 */
    TDrawVecBlk *vecB;    /* 0x14 */
    void *variant;        /* 0x18 */
} TDrawDesc;

typedef struct TDrawCase1 {
    float f0;             /* 0x0 */
} TDrawCase1;

typedef struct TDrawCase2 {
    float f0;             /* 0x0 */
    float f1;             /* 0x4 */
    unsigned int u2;      /* 0x8 */
} TDrawCase2;

typedef struct TDrawCase3 {
    float f0;             /* 0x00 */
    unsigned int u1;      /* 0x04 */
    float f2;             /* 0x08 */
    float f3;             /* 0x0C */
    unsigned int u4;      /* 0x10 */
} TDrawCase3;

/* slot table row (0x14 bytes) */
#include "game/types/TDrawSlot.h"

extern unsigned char lbl_806D10F0;  /* .sbss: transparent draw system active */
extern TDrawObj *lbl_806D10F8;      /* .sbss: draw chain head */
extern TDrawSlot lbl_805987E0[32];  /* .bss: slot table */
extern const float lbl_806D2C68;    /* .sdata2: 0.0f */

extern TDrawObj *HSD_LObjLoadDesc(void *);
extern void MemoryManager_TimedFree(void *);
extern void *GetCourseScene3D(void);
extern void *CObj_GetViewMatrix_Cached(void *);
extern void CObj_LoadProjMatrix(void *, Vec3 *);
extern void PSMTXCopy(void *, float (*)[4]);
extern void PSMTXMultVec(float (*)[4], Vec3 *, Vec3 *);
extern void HSD_LObjDeleteCurrentAll(int);
extern void HSD_LObjAddCurrent(TDrawObj *);

#pragma exceptions on

int TransparentDraw_InitEntry(TDrawEntry *self, TDrawDesc *desc) {
    if (self->handle != 0) {
        return 0;
    }

    self->p04 = 0;
    self->p08 = 0;
    self->mode = desc->mode;
    self->p0E = desc->p0A;
    self->r = desc->r;
    self->g = desc->g;
    self->b = desc->b;
    self->a = desc->a;

    if (desc->vecA != 0) {
        self->vecA = &self->blkA;
        self->blkA.head = 0;
        self->blkA.x = desc->vecA->x;
        self->blkA.y = desc->vecA->y;
        self->blkA.z = desc->vecA->z;
        self->blkA.tail = 0;
    } else {
        self->vecA = 0;
    }

    if (desc->vecB != 0) {
        self->vecB = &self->blkB;
        self->blkB.head = 0;
        self->blkB.x = desc->vecB->x;
        self->blkB.y = desc->vecB->y;
        self->blkB.z = desc->vecB->z;
        self->blkB.tail = 0;
    } else {
        self->vecB = 0;
    }

    switch (self->mode & 3) {
    case 1:
        self->variant = &self->c1_value;
        self->c1_value = ((TDrawCase1 *)desc->variant)->f0;
        break;
    case 2:
        self->variant = &self->c2_f0;
        self->c2_f0 = ((TDrawCase2 *)desc->variant)->f0;
        self->c2_f1 = ((TDrawCase2 *)desc->variant)->f1;
        self->c2_u2 = ((TDrawCase2 *)desc->variant)->u2;
        break;
    case 3:
        self->variant = &self->c3_f0;
        self->c3_f0 = ((TDrawCase3 *)desc->variant)->f0;
        self->c3_u1 = ((TDrawCase3 *)desc->variant)->u1;
        self->c3_f2 = ((TDrawCase3 *)desc->variant)->f2;
        self->c3_f3 = ((TDrawCase3 *)desc->variant)->f3;
        self->c3_u4 = ((TDrawCase3 *)desc->variant)->u4;
        break;
    default:
        self->variant = 0;
        break;
    }

    self->handle = HSD_LObjLoadDesc(&self->p04);
    return 1;
}

#pragma exceptions reset

/* DestroyEntry is the CW deleting destructor of the entry (hidden short
 * flag, `delete this` when flag > 0). The handle release mirrors the
 * canonical HSD ref_DEC / hsdDelete inlines (object.h / class.h). The
 * mangled names are bridged in tools/extab_user_renames.json:
 * __dt__15TDrawEntryOwnerFv -> TransparentDraw_DestroyEntry.
 */
#pragma cplusplus on
#pragma exceptions on

static inline int TDraw_RefDec(TDrawObj *obj) {
    unsigned char unreferenced;
    if ((unreferenced = (obj->refcount == (unsigned short)0xFFFF))) {
        return unreferenced;
    }
    return obj->refcount-- == 0;
}

static inline void TDraw_Delete(TDrawObj *obj) {
    if (obj != 0) {
        obj->vt->fn30(obj);
        obj->vt->fn34(obj);
    }
}

static inline void TDraw_Unref(TDrawObj *obj) {
    if (obj != 0 && TDraw_RefDec(obj)) {
        TDraw_Delete(obj);
    }
}

struct TDrawEntryOwner {
    TDrawObj *handle;
    ~TDrawEntryOwner();
};

TDrawEntryOwner::~TDrawEntryOwner() {
    if (handle != 0) {
        handle->next = 0;
        TDraw_Unref(handle);
        handle = 0;
    }
}

#pragma exceptions reset
#pragma cplusplus reset

void TransparentDraw_ResetEntry(TDrawEntry *self) {
    self->handle = 0;
    self->p04 = 0;
    self->p08 = 0;
    self->mode = 0xD;
    self->p0E = 0;
    self->r = 0x7F;
    self->g = 0x7F;
    self->b = 0x7F;
    self->a = 0;
    self->vecA = 0;
    self->vecB = 0;
    self->variant = 0;
}

int TransparentDraw_SortAndDispatch(void) {
    TDrawObj *chain;
    int i;
    float mtx[3][4];
    Vec3 cam;
    Vec3 v;

    if (lbl_806D10F0 == 0) {
        return 0;
    }

    lbl_806D10F8 = 0;

    {
        int n;
        for (n = 0; n < 32; n++) {
            if (lbl_805987E0[n].owner != -1 && lbl_805987E0[n].state == 0) {
                lbl_806D10F8 = lbl_805987E0[n].entry->handle;
                chain = lbl_806D10F8;
                break;
            }
        }
    }

    HSD_LObjDeleteCurrentAll(0);

    if (lbl_806D10F8 == 0) {
        return 0;
    }

    PSMTXCopy(CObj_GetViewMatrix_Cached(GetCourseScene3D()), mtx);
    mtx[2][3] = lbl_806D2C68;
    mtx[1][3] = lbl_806D2C68;
    mtx[0][3] = lbl_806D2C68;
    CObj_LoadProjMatrix(GetCourseScene3D(), &cam);

    for (i = 0; i < 32; i++) {
        TDrawPos *pos;
        if (lbl_805987E0[i].owner != -1 && (pos = lbl_805987E0[i].entry->handle->pos) != 0) {
            v.x = pos->x - cam.x;
            v.y = lbl_806D2C68;
            v.z = pos->z - cam.z;
            PSMTXMultVec(mtx, &v, &v);
            lbl_805987E0[i].dist = v.x * v.x + v.z * v.z;
            lbl_805987E0[i].rank = 0;
        } else {
            lbl_805987E0[i].rank = -1;
        }
    }

    {
        int k;
        for (k = 0; k < 31; k++) {
            TDrawSlot *a = &lbl_805987E0[k];
            if (a->rank != -1) {
                if (a->state == 2 || a->state == 3 || a->state == 4) {
                    int j;
                    for (j = k + 1; j < 32; j++) {
                        if (lbl_805987E0[j].rank != -1) {
                            if (a->dist > lbl_805987E0[j].dist) {
                                a->rank = a->rank + 1;
                            } else {
                                lbl_805987E0[j].rank = lbl_805987E0[j].rank + 1;
                            }
                        }
                    }
                } else {
                    a->rank = -1;
                }
            }
        }
    }

    for (i = 0; i < 32; i++) {
        if (lbl_805987E0[i].owner != -1 && lbl_805987E0[i].state == 1) {
            chain->next = lbl_805987E0[i].entry->handle;
            chain = lbl_805987E0[i].entry->handle;
            break;
        }
    }

    {
        int count = 1;
        int order;
        for (order = 0; order < 7; order++) {
            if (order >= count) {
                break;
            }
            for (i = 0; i < 32; i++) {
                if (lbl_805987E0[i].owner != -1 && order == lbl_805987E0[i].rank) {
                    count++;
                    chain->next = lbl_805987E0[i].entry->handle;
                    chain = lbl_805987E0[i].entry->handle;
                    break;
                }
            }
        }
    }

    chain->next = 0;
    HSD_LObjAddCurrent(lbl_806D10F8);
    return 1;
}

int TransparentDraw_RemoveByOwner(int owner) {
    int i;

    if (lbl_806D10F0 == 0) {
        return 0;
    }
    if (owner == -1) {
        return 0;
    }

    for (i = 0; i < 32; i++) {
        if (owner == lbl_805987E0[i].owner && lbl_805987E0[i].owner != -1) {
            lbl_805987E0[i].owner = -1;
            lbl_805987E0[i].state = 5;
        }
    }
    return 1;
}

/* --- manual extab/extabindex emit (approach B) ---
 * SortAndDispatch is C compiled with exceptions off (auto emit
 * suppressed). InitEntry and the DestroyEntry destructor keep CW auto emit
 * (approach A) and their extab/extabindex sort first in link order, so the
 * final section order matches the target: InitEntry(0x800080B0),
 * DestroyEntry(0x800080B8), SortAndDispatch(0x800080C0) / extabindex
 * 0x80020F84 / 0x80020F90 / 0x80020F9C. Renames via
 * tools/extab_user_renames.json + tools/postprocess_extab_user.py
 * (extab_padding=b"  " routes the postprocess).
 */
#pragma section R ".extab_user"

__declspec(section ".extab_user") static const unsigned char extab_TransparentDraw_SortAndDispatch[8] = {
    0x20, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TransparentDraw_SortAndDispatch = {
    (void *)&TransparentDraw_SortAndDispatch, 0x0000033C, (void *)extab_TransparentDraw_SortAndDispatch
};
