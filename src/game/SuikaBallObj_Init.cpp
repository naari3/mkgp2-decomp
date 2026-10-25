/* SuikaBallObj_Init (0x80124984): loads the suika ball model and sizes it
 * from its bounding box. The bounds are copied as words like the target. */
#pragma cplusplus on
void *operator new(unsigned long size);
typedef struct Vec3 { float x, y, z; } Vec3;
struct W3 { int a, b, c; };
struct SuikaNormal {
    unsigned char opaque[0x5C];
    SuikaNormal(void *res, int flags);
};
extern "C" {

typedef struct SuikaBallObj {
    SuikaNormal *obj;
    float scale;
    float mtx[3][4];
    float f38[10];
    unsigned char b60;
    unsigned char b61;
    float f64[6];
} SuikaBallObj;

extern void *Archive_GetRootJObj(void *obj);
extern unsigned char fn_801847DC(void *jobj, Vec3 *min, Vec3 *max);
extern void PSMTXIdentity(float m[3][4]);
extern void Object_BindMatrixSource(void *obj, float m[3][4], int flag);

extern const Vec3 lbl_80355900;
extern const Vec3 lbl_8035590C;
}

extern "C" SuikaBallObj *SuikaBallObj_Init(SuikaBallObj *self, void *res)
{
    Vec3 min;
    Vec3 max;

    self->obj = 0;
    self->f38[0] = 0.0f;
    self->f38[1] = 0.0f;
    self->f38[2] = 0.0f;
    self->f38[3] = 0.0f;
    self->f38[4] = 0.0f;
    self->f38[5] = 0.0f;
    self->f38[7] = 0.0f;
    self->f38[8] = 0.0f;
    self->f38[9] = 0.0f;
    self->scale = 5.0f;
    self->f38[6] = 0.0f;
    self->b60 = 0;
    self->b61 = 0;
    self->f64[0] = 0.3f;
    self->f64[1] = 0.4f;
    self->f64[2] = 0.8f;
    self->f64[3] = 0.1f;
    self->f64[4] = 0.98f;
    self->f64[5] = 0.96f;
    SuikaNormal *p = new SuikaNormal(res, 0);
    self->obj = p;
    if (p != 0) {
        *(W3 *)&min = *(const W3 *)&lbl_80355900;
        *(W3 *)&max = *(const W3 *)&lbl_8035590C;
        if (fn_801847DC(Archive_GetRootJObj(self->obj), &min, &max)) {
            self->scale = 0.5f * (max.x - min.x);
        }
        PSMTXIdentity(self->mtx);
        Object_BindMatrixSource(self->obj, self->mtx, 0);
    }
    return self;
}
