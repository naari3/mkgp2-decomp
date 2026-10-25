typedef struct Obj8018E000 {
    void *vt;
    void *buf4;
    int pad8;
    void **objs;
    void *buf10;
} Obj8018E000;

extern char lbl_80495E68[];
extern char lbl_80490FE0[];
extern char lbl_80378038[];
extern unsigned char fn_8016C360(int id);
extern void fn_8016C394(int id);
extern void MemoryManager_Free(void *p);
extern void MemoryManager_TimedFree(void *p);
extern void Object_DtorWithGXSync(void *p, int flag);
extern void DebugPrintf(const char *fmt, ...);

Obj8018E000 *fn_8018E000(Obj8018E000 *p, short flag) {
    int i;
    if (p != 0) {
        p->vt = lbl_80495E68;
        if (fn_8016C360(0x38)) fn_8016C394(0x38);
        if (p->buf4 != 0) MemoryManager_Free(p->buf4);
        if (p->objs != 0) {
            for (i = 0; i < 3; i++) {
                if (p->objs[i] != 0) Object_DtorWithGXSync(p->objs[i], 1);
            }
            MemoryManager_Free(p->objs);
        }
        if (p->buf10 != 0) MemoryManager_Free(p->buf10);
        DebugPrintf(lbl_80378038);
        if (p != 0) p->vt = lbl_80490FE0;
        if (flag > 0) MemoryManager_TimedFree(p);
    }
    return p;
}
