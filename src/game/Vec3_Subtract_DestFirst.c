extern void Vec3_Subtract(float *a, float *b, float *dst);
extern void PSVECAdd(float *a, float *b, float *dst);

#pragma exceptions on
void Vec3_Subtract_DestFirst(float *dst, float *a, float *b) {
    Vec3_Subtract(a, b, dst);
}

void Vec3_Add_DestFirst(float *dst, float *a, float *b) {
    PSVECAdd(a, b, dst);
}
#pragma exceptions reset

void GetSpawnPosition(float *dst, float x, float y, float z) {
    dst[0] = x;
    dst[1] = y;
    dst[2] = z;
}

void Vec3_Copy(float *__restrict dst, float *__restrict src) {
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}
