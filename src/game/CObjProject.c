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

extern int HSD_CObjGetProjectionType(void *);
extern float HSD_CObjGetAspect(void *);
extern float HSD_CObjGetFov(void *);
extern void fn_8013879C(float *, float, float, float, float);
extern void DebugPrintf(const char *, ...);
extern const float lbl_806D22E0;
extern const char lbl_802E96D0[], lbl_802E96FC[];
extern void GXGetProjectionv(float *);
extern void GXGetViewportv(float *);
extern Matrix3x4 *HSD_CObjGetViewingMtxPtr(void *);
extern void HSD_CObjSetupViewingMtx(void *);
extern void GXProject(const Matrix3x4, const float *, const float *,
                       float *, float *, float *, float, float, float);
extern void PSMTXMultVec(const Matrix3x4, const Vec3 *, Vec3 *);
extern const Vec3 lbl_802E96B8;

static inline Matrix3x4 *CObjProject_GetView(CObjProjectView *self)
{
    if (!self->ready) {
        return 0;
    }
    return HSD_CObjGetViewingMtxPtr(self->camera);
}

#ifndef COBJ_PROJECT_POINT_ONLY
int CObj_UpdatePerspParam(CObjProjectView *self, float farPlane)
{
    float aspect;
    if (!self->ready) {
        return 0;
    }
    self->farPlane = farPlane;
    if (HSD_CObjGetProjectionType(self->camera) == 1) {
        aspect = HSD_CObjGetAspect(self->camera);
        fn_8013879C(self->projectionBuffer, lbl_806D22E0 * HSD_CObjGetFov(self->camera),
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

    GXGetProjectionv(projection);
    GXGetViewportv(viewport);
    matrix = CObjProject_GetView(self);
    GXProject(*matrix, projection, viewport, outX, outY, outDepth, x, y, z);
    point = lbl_802E96B8;
    point.x = x;
    point.y = y;
    point.z = z;
    HSD_CObjSetupViewingMtx(self->camera);
    matrix = CObjProject_GetView(self);
    PSMTXMultVec(*matrix, &point, &transformed);
    *outZ = transformed.z;
}
#endif
