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

static inline unsigned char HasAttr(int attr) {
    int i;
    if (lbl_806D1678 == 0) {
        return 0;
    }
    for (i = 0; i < 22; i++) {
        if (lbl_80677E18[i].desc == 0 || lbl_80677E18[i].desc->attr == 0xff) {
            break;
        }
        if (attr == lbl_80677E18[i].desc->attr) {
            return 1;
        }
    }
    return 0;
}

static inline unsigned char SetIndex(int attr, unsigned char *vtx, int idx) {
    int i;
    for (i = 0; i < 22; i++) {
        if (lbl_80677E18[i].desc == 0 || lbl_80677E18[i].desc->attr == 0xff) {
            break;
        }
        if (attr == lbl_80677E18[i].desc->attr) {
            if (lbl_80677E18[i].desc->type == 3) {
                *(unsigned short *)(vtx + lbl_80677E18[i].offset) = idx;
                return 1;
            } else {
                *(unsigned char *)(vtx + lbl_80677E18[i].offset) = idx;
                return 1;
            }
        }
    }
    return 0;
}

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

int fn_80182ED0(PObjView *pobj, int attr) {
    int idx;
    unsigned char *p;
    unsigned char *end;
    unsigned int size;
    unsigned int n;
    unsigned int j;

    if (pobj == 0) {
        return 0;
    }
    fn_801866DC(pobj->verts);
    if (lbl_806D1678 == 0) {
        return 0;
    }
    if (!HasAttr(attr)) {
        return 0;
    }
    idx = 0;
    p = pobj->display;
    end = p + pobj->n_display * 32;
    while (p < end) {
        size = CmdSize(p);
        if (size != 0) {
            p += size;
            continue;
        }
        n = *(unsigned short *)(p + 1);
        p += 3;
        for (j = 0; j < n; j++) {
            if (SetIndex(attr, p, idx)) {
                idx++;
            } else {
                return 0;
            }
            p += lbl_806D1678;
        }
    }
    return 1;
}
