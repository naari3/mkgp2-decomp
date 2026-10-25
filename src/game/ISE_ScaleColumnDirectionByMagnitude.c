typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct IseMatrixHolder {
    unsigned char pad[0x70];
    float *mtx;
} IseMatrixHolder;

extern void Vec3_Normalize(Vec3 *dst, Vec3 *src);

int ISE_ScaleColumnDirectionByMagnitude(IseMatrixHolder *self, void *unused, Vec3 *out, float scale)
{
    float *m = self->mtx;
    Vec3 dir;

    dir.x = m[2];
    dir.y = m[6];
    dir.z = m[10];
    Vec3_Normalize(&dir, &dir);
    out->x = dir.x * scale;
    out->y = dir.y * scale;
    out->z = dir.z * scale;
    return 1;
}
