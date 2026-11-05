/* Keep the canonical vtable external: its RTTI entry is owned elsewhere. */
void operator delete(void *p) throw();
struct clEFaceModel { virtual ~clEFaceModel(); };
struct clEFace3D {
    virtual void _key();
    virtual ~clEFace3D();
    char pad04[0x2C - 4];
    clEFaceModel *model;
};

clEFace3D::~clEFace3D() {
    delete model;
}
