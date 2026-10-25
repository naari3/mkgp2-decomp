typedef struct VtxDesc {
    int attr;
    int type;
} VtxDesc;

typedef struct VtxAttrEntry {
    VtxDesc *desc;
    unsigned int offset;
} VtxAttrEntry;

typedef struct PObjView {
    unsigned char pad[0x8];
    VtxDesc *verts;
    unsigned char pad2[0x2];
    unsigned short n_display;
    unsigned char *display;
} PObjView;

extern VtxAttrEntry lbl_80677E18[22];
extern unsigned int lbl_806D1678;
extern const char lbl_80376F9C[];
extern const char lbl_80376FB0[];
extern void fn_801866DC(VtxDesc *verts);
extern void OSPanic(const char *file, int line, const char *msg, ...);

static inline unsigned int CmdSize(unsigned char *p) {
    switch (*p) {
    case 0x00:
        return 1;
    case 0x61:
        return 5;
    case 0x08:
        return 6;
    case 0x10:
        return ((unsigned int)(*(unsigned short *)(p + 1) + 1) * 32 + 40) / 8;
    case 0x20:
        return 5;
    case 0x28:
        return 5;
    case 0x30:
        return 5;
    case 0x38:
        return 5;
    }
    switch (*p & 0xf8) {
    case 0x80:
    case 0x90:
    case 0x98:
    case 0xa0:
    case 0xa8:
    case 0xb0:
    case 0xb8:
        return 0;
    }
    OSPanic(lbl_80376F9C, 0x103, lbl_80376FB0);
    return 0;
}

unsigned int fn_80183A5C(PObjView *pobj) {
    unsigned int count;
    unsigned char *p;
    unsigned char *start;
    unsigned char *end;
    unsigned int size;
    unsigned int n;
    int prim;

    if (pobj == 0) {
        return 0;
    }
    fn_801866DC(pobj->verts);
    if (lbl_806D1678 == 0) {
        return 0;
    }
    count = 0;
    start = pobj->display;
    p = start;
    end = start + pobj->n_display * 32;
    while (p < end) {
        size = CmdSize(p);
        if (size != 0) {
            p += size;
            continue;
        }
        n = *(unsigned short *)(p + 1);
        prim = *p & 0xf8;
        p += lbl_806D1678 * n + 3;
        switch (prim) {
        case 0x80:
            count += n / 4;
            break;
        case 0x90:
            count += n / 3;
            break;
        case 0x98:
            count += n - 2;
            break;
        case 0xa0:
        case 0xa8:
        case 0xb0:
        case 0xb8:
            break;
        }
    }
    return count;
}
