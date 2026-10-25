/* 0x80193300: refresh the fog basis vectors and eye point from the course
 * scene camera. The TU owns the vectors (.data 0x80495F20..0x80495F48). */

typedef struct Vec3f {
    float x, y, z;
} Vec3f;

typedef struct FogEye {
    Vec3f pos;
    float w;
} FogEye;

Vec3f lbl_80495F20 = {0.0f, 0.0f, 0.0f};

Vec3f lbl_80495F2C = {0.0f, 0.0f, 0.0f};
FogEye lbl_80495F38 = {{0.0f, 0.0f, 0.0f}, 0.0f};

extern void *GetCourseScene3D(void);
extern float *CObj_GetViewMatrix_Cached(void *cobj);
extern void CObj_LoadProjMatrix(void *cobj, Vec3f *pos);
void Fog_UpdateFromCourseScene3D(void) {
    if (GetCourseScene3D()) {
        float *m = CObj_GetViewMatrix_Cached(GetCourseScene3D());
        lbl_80495F20.x = m[0];
        lbl_80495F20.y = m[4];
        lbl_80495F20.z = m[8];
        lbl_80495F2C.x = m[2];
        lbl_80495F2C.y = m[6];
        lbl_80495F2C.z = m[10];
        CObj_LoadProjMatrix(GetCourseScene3D(), &lbl_80495F38.pos);
        lbl_80495F38.pos.x += 50.0f * lbl_80495F2C.x;
        lbl_80495F38.pos.y += 50.0f * lbl_80495F2C.y;
        lbl_80495F38.pos.z += 50.0f * lbl_80495F2C.z;
    }
}
