/* FinalLapBanner ctor @ 0x80088700..0x80088880. Builds the final-lap banner
 * model (Japanese or overseas variant) used by LapBannerScene.c and places
 * its root JObj. */
void *operator new(unsigned long size);
void operator delete(void *ptr);

/* The word overlay keeps the copy in integer registers. */
union Vec3 {
    struct { float x, y, z; } f;
    unsigned int words[3];
};

struct HSD_JObj {
    unsigned char pad[0x14];
    unsigned int flags;
    unsigned char pad_18[0x14];
    Vec3 translate; /* 0x2C */
};

class Normal3D {
public:
    Normal3D(void *desc, int flags);
    unsigned char data[0x5C];
};

extern "C" {
extern const float lbl_806D3250;
extern const float lbl_806D3254;
extern const float lbl_806D3258;
extern char lbl_806D325C[7];
extern char lbl_806D3264[5];
extern unsigned char lbl_803123B0[];
int isJapanese(void);
void clNormal3D_SetScale(void *, int, float, float, float, float);
HSD_JObj *Archive_GetRootJObj(void *);
void __assert(char *, int, char *);
void HSD_JObjSetMtxDirtySub(HSD_JObj *);
}

static inline unsigned char matrix_is_clean(HSD_JObj *jobj)
{
    unsigned int flags;
    unsigned char clean;
    if (jobj == 0) __assert(lbl_806D325C, 0x25D, lbl_806D3264);
    flags = jobj->flags;
    clean = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) clean = 1;
    return clean;
}

static inline void dirty_matrix(HSD_JObj *jobj)
{
    if (jobj != 0) {
        if (!matrix_is_clean(jobj)) HSD_JObjSetMtxDirtySub(jobj);
    }
}

static inline void set_translate(HSD_JObj *jobj, Vec3 *v)
{
    if (jobj == 0) __assert(lbl_806D325C, 0x316, lbl_806D3264);
    jobj->translate.f.x = v->f.x;
    jobj->translate.f.y = v->f.y;
    jobj->translate.f.z = v->f.z;
    if (!(jobj->flags & 0x02000000)) dirty_matrix(jobj);
}

struct FinalLapBanner {
    Normal3D *obj;
    void *driver;
    unsigned char active;

    FinalLapBanner(void *driver);
};

FinalLapBanner::FinalLapBanner(void *drv)
{
    unsigned char *data;
    Vec3 pos;

    obj = 0;
    data = lbl_803123B0;
    active = 0;
    if (isJapanese() == 0) {
        obj = new Normal3D(data + 0x430, 0);
    } else {
        obj = new Normal3D(data + 0x444, 0);
    }
    if (obj == 0) {
        return;
    }
    clNormal3D_SetScale(obj, 0, lbl_806D3250, lbl_806D3254, lbl_806D3250, lbl_806D3258);
    pos = *(Vec3 *)(data + 0x3FC);
    set_translate(Archive_GetRootJObj(obj), &pos);
    driver = drv;
}
