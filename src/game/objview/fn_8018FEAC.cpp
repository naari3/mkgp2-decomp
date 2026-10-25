struct HSD_JObj;

extern "C" {
extern const char lbl_803785DC[];
extern int g_cupId;
extern int g_courseVariantIdx;
extern const char *lbl_806CFC78;
extern const char *lbl_806CFC7C;
extern const char *lbl_806CFC80;
extern const char *lbl_806CFC84;
extern const char *lbl_806CFC88;
extern const char *lbl_806CFC8C;
extern const float lbl_806D94CC;
extern const float lbl_806D94D0;
extern const float lbl_806D94D4;
extern const float lbl_806D94D8;
extern const float lbl_806D94DC;
void DebugPrintf(const char *fmt, ...);
}

struct clNormal3D {
    unsigned char data[0x5c];
    clNormal3D(const char *name, int arg);
};

extern "C" {
HSD_JObj *Archive_GetRootJObj(clNormal3D *model);
HSD_JObj *ResolveJointByName(clNormal3D *model, const char *name);
void fn_80182954(HSD_JObj *jobj, int flag);
}

struct ObjBase {
    ObjBase() {}
    virtual ~ObjBase();
};

struct WaveTex {
    float x0, x4, x8, xc, x10, x14, x18, x1c;
    unsigned char pad[0x4c - 0x20];
    WaveTex(HSD_JObj *jobj);
};

struct Obj8018FEAC : ObjBase {
    clNormal3D *model;
    WaveTex *wave;
    Obj8018FEAC();
    virtual ~Obj8018FEAC();
};

Obj8018FEAC::Obj8018FEAC() {
    const char *name;
    const char *joint;
    DebugPrintf(lbl_803785DC);
    model = 0;
    wave = 0;
    name = 0;
    joint = 0;
    switch (g_cupId) {
    case 1:
        switch (g_courseVariantIdx) {
        case 0:
            name = lbl_806CFC78;
            joint = lbl_806CFC7C;
            break;
        case 1:
            name = lbl_806CFC80;
            joint = lbl_806CFC84;
            break;
        case 2:
            name = lbl_806CFC88;
            joint = lbl_806CFC8C;
            break;
        }
        break;
    case 9:
        name = lbl_806CFC78;
        joint = lbl_806CFC7C;
        break;
    }
    if (name == 0 || joint == 0) return;
    model = new clNormal3D(name, 0);
    fn_80182954(Archive_GetRootJObj(model), 1);
    wave = new WaveTex(ResolveJointByName(model, joint));
    wave->x0 = lbl_806D94CC;
    wave->x4 = lbl_806D94D0;
    wave->x8 = lbl_806D94D4;
    wave->xc = lbl_806D94D4;
    wave->x10 = lbl_806D94D8;
    wave->x14 = lbl_806D94D8;
    wave->x18 = lbl_806D94DC;
    wave->x1c = lbl_806D94DC;
}
