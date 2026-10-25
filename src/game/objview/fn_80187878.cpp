extern "C" {
extern const char lbl_80377328[];
extern const char lbl_8037734C[];
void DebugPrintf(const char *fmt, ...);
void Object_SetJObjPositionXYZ(void *jobj, float x, float y, float z);
}

struct clNormal3D {
    unsigned char data[0x5c];
    clNormal3D(const char *name, int arg);
};

struct ObjBase {
    ObjBase() {}
    virtual ~ObjBase();
};

struct ObjView : ObjBase {
    clNormal3D *jobj;
    float rot;
    ObjView();
    virtual ~ObjView();
};

ObjView::ObjView() {
    DebugPrintf(lbl_80377328);
    jobj = 0;
    rot = 0.0f;
    jobj = new clNormal3D(lbl_8037734C, 0);
    Object_SetJObjPositionXYZ(jobj, -1258.0f, 458.0f, -4584.0f);
}
