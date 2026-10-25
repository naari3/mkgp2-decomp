typedef struct GXTexObj {
    unsigned int dummy[8];
} GXTexObj;

extern GXTexObj lbl_804FE060;
extern char lbl_804FE080[];
extern void GXInitTexObj(GXTexObj *, void *, unsigned short, unsigned short, int, int, int,
                        unsigned char);
extern void GXInitTexObjLOD(GXTexObj *, int, int, float, float, float, unsigned char,
                               unsigned char, int);

GXTexObj *BackupBuffer_InitAsTexture(void) {
    GXInitTexObj(&lbl_804FE060, lbl_804FE080, 0x280, 0x1E0, 4, 0, 0, 0);
    GXInitTexObjLOD(&lbl_804FE060, 0, 0, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    return &lbl_804FE060;
}
