extern void Vec3_Subtract(float *a, float *b, float *dst);
extern void fn_8025E264(float *a, float *b, float *dst);

#pragma exceptions on
void Vec3_Subtract_DestFirst(float *dst, float *a, float *b) {
    Vec3_Subtract(a, b, dst);
}

void Vec3_Add_DestFirst(float *dst, float *a, float *b) {
    fn_8025E264(a, b, dst);
}
#pragma exceptions reset

void GetSpawnPosition(float *dst, float x, float y, float z) {
    dst[0] = x;
    dst[1] = y;
    dst[2] = z;
}

/* C form `x = src[0]; y = src[1]; dst[0] = x; z = src[2]; ...` reaches 98.29%
 * but CW schedules the y load before x; kept as asm. */
asm void Vec3_Copy(float *dst, float *src) {
    nofralloc
    lfs f0, 0x0(r4)
    lfs f1, 0x4(r4)
    stfs f0, 0x0(r3)
    lfs f0, 0x8(r4)
    stfs f1, 0x4(r3)
    stfs f0, 0x8(r3)
    blr
}
