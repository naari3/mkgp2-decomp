/* Course object set owned by lbl_806D19B0; deleted through its inline dtor. */
struct HSD_Obj;
struct ObjEntry {
    int id;
    int arg;
};
extern "C" {
extern const char lbl_803BFB30[];
extern ObjEntry *lbl_804EBD50[3];
extern ObjEntry *lbl_804EBD5C[3];
void Object_DtorWithGXSync(HSD_Obj *obj, int del);
unsigned char ServiceEnable_Get(void);
unsigned char ServiceValue_Get(void);
void DebugPrintf(const char *fmt, ...);
}

struct CourseObjSet {
    HSD_Obj *objs[3][30];
    HSD_Obj *extra[3];
    ~CourseObjSet();
};

inline CourseObjSet::~CourseObjSet()
{
    ObjEntry *e;
    HSD_Obj **o;
    int i;
    for (i = 0; i < 3; i++) {
        Object_DtorWithGXSync(extra[i], 1);
        extra[i] = 0;
        if (ServiceEnable_Get() && !ServiceValue_Get()) {
            e = lbl_804EBD50[i];
        } else {
            e = lbl_804EBD5C[i];
        }
        for (o = objs[i]; e->id != -1; o++, e++) {
            if (*o != 0) {
                Object_DtorWithGXSync(*o, 1);
                *o = 0;
            }
        }
    }
    DebugPrintf(lbl_803BFB30);
}

extern "C" {
extern CourseObjSet *lbl_806D19B0;
}

void operator delete(void *p);

extern "C" void fn_801F9CA8(void)
{
    if (lbl_806D19B0 != 0) {
        delete lbl_806D19B0;
        lbl_806D19B0 = 0;
    }
}
