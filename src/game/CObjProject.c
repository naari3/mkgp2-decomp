/* Only the fields observed in the camera projection callers are described. */
typedef struct Vec3 { float x, y, z; } Vec3;
typedef float Matrix3x4[3][4];
typedef struct CObjProjectView {
    char pad0[4];
    void *camera;
    char pad8[0x20];
    unsigned int ready;
    char pad2C[0x3034 - 0x2C];
    float projectionBuffer[18];
    float nearPlane;
    float farPlane;
} CObjProjectView;

extern int fn_802C8418(void *);
extern float fn_802C834C(void *);
extern float fn_802C8308(void *);
extern void fn_8013879C(float *, float, float, float, float);
extern void DebugPrintf(const char *, ...);
extern const float lbl_806D22E0;
extern const char lbl_802E96D0[], lbl_802E96FC[];
extern void fn_8026A2BC(float *);
extern void fn_8026A5BC(float *);
extern Matrix3x4 *fn_802C7E30(void *);
extern void fn_802C6BCC(void *);
extern void fn_8026A018(const Matrix3x4, const float *, const float *,
                       float *, float *, float *, float, float, float);
extern void fn_8025DF40(const Matrix3x4, const Vec3 *, Vec3 *);
extern const Vec3 lbl_802E96B8;

static inline Matrix3x4 *CObjProject_GetView(CObjProjectView *self)
{
    if (!self->ready) {
        return 0;
    }
    return fn_802C7E30(self->camera);
}

#ifndef COBJ_PROJECT_POINT_ONLY
int CObj_UpdatePerspParam(CObjProjectView *self, float farPlane)
{
    float aspect;
    if (!self->ready) {
        return 0;
    }
    self->farPlane = farPlane;
    if (fn_802C8418(self->camera) == 1) {
        aspect = fn_802C834C(self->camera);
        fn_8013879C(self->projectionBuffer, lbl_806D22E0 * fn_802C8308(self->camera),
                    aspect, self->nearPlane, self->farPlane);
    } else {
        DebugPrintf(lbl_802E96D0);
        DebugPrintf(lbl_802E96FC);
        DebugPrintf(lbl_802E96D0);
    }
    return 1;
}
#endif

#ifdef COBJ_PROJECT_POINT_ONLY
void CObj_ProjectPoint(CObjProjectView *self, float *outX, float *outY,
                       float *outZ, float *outDepth, float x, float y, float z)
{
    float projection[7];
    float viewport[6];
    Vec3 point;
    Vec3 transformed;
    Matrix3x4 *matrix;

    fn_8026A2BC(projection);
    fn_8026A5BC(viewport);
    matrix = CObjProject_GetView(self);
    fn_8026A018(*matrix, projection, viewport, outX, outY, outDepth, x, y, z);
    point = lbl_802E96B8;
    point.x = x;
    point.y = y;
    point.z = z;
    fn_802C6BCC(self->camera);
    matrix = CObjProject_GetView(self);
    fn_8025DF40(*matrix, &point, &transformed);
    *outZ = transformed.z;
}
#endif
