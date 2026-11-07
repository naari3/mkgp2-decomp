/* Same compiler setup as Vec3_ToYawPitch.c: GC/2.7; the const source lets the
 * loads schedule ahead of the LR save. */
extern double atan2(double, double);

#pragma exceptions on
float Vec3_ToYaw(const float *v) {
    return atan2(v[0], v[2]);
}
#pragma exceptions reset
