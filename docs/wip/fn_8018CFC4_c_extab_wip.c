/* fn_8018CFC4: S22Single ctor (ObjView S22 variant with one model + joint).
 * Written in C with explicit vtable stores (base lbl_80490FE0, then derived
 * S22Single_vtable_80495DDC): the C++ ctor form computes the string-pool base after both
 * vtable stores instead of between them. The extab (DELETEPOINTER for the
 * new'd clNormal3D, DESTROYBASE dtor_8016A270) is emitted by hand. */
extern void *lbl_80490FE0[];
extern void *S22Single_vtable_80495DDC[];
extern const char lbl_80377E60[];
extern void DebugPrintf(const char *, ...);
extern void *Alloc(unsigned long);
extern void *clNormal3D_Construct(void *, const char *, int);
extern void *ResolveJointByName(void *, const char *);
extern void MemoryManager_TimedFree(void *);
extern void dtor_8016A270(void);

typedef struct S22Single {
    void **vt;
    void *model;
    void *joint;
} S22Single;

S22Single *fn_8018CFC4(S22Single *self);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct {
    unsigned int w[9]; void *f9; unsigned int w10; unsigned int w11; void *f12;
} extab_fn_8018CFC4 = {
    { 0x18080000, 0x00000048, 0x00050028, 0x00000070, 0x00000020,
      0x00000080, 0x00000028, 0x00000000, 0x0A80001D },
    (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&dtor_8016A270
};
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn; unsigned int fn_size; const void *extab;
} extabindex_fn_8018CFC4 = { (void *)&fn_8018CFC4, 0x000000A4, &extab_fn_8018CFC4 };

S22Single *fn_8018CFC4(S22Single *self) {
    const char *data;
    void *m;

    data = lbl_80377E60;
    self->vt = lbl_80490FE0;
    self->vt = S22Single_vtable_80495DDC;
    DebugPrintf(data + 0x40);
    self->model = 0;
    self->joint = 0;
    m = Alloc(0x5c);
    if (m != 0) {
        clNormal3D_Construct(m, data + 0x60, 0);
    }
    self->model = m;
    self->joint = ResolveJointByName(self->model, data + 0x74);
    return self;
}
