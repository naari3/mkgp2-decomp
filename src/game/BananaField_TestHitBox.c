/* BananaField_TestHitBox (0x80196F60): oriented-box test of a point against the kart
 * matrix, using the per-character half extents in lbl_8037D9E0. */

typedef struct { float x, y, z; } Vec;

extern Vec lbl_8037D9E0[];
extern const float lbl_806D95B8;
extern const float lbl_806D95BC;
extern float Vec3_Dot(const Vec *a, const Vec *b);
extern float Vec3_Magnitude(const Vec *v);
extern void PSVECScale(const Vec *src, Vec *dst, float s);

#pragma exceptions on
int BananaField_TestHitBox(int chara, float (*mtx)[4], Vec *pos, float radius) {
    Vec *ext = &lbl_8037D9E0[chara];
    Vec rel;
    Vec axis;
    float mag;
    float d;
    float lim;

    rel.x = pos->x - mtx[0][3];
    rel.y = pos->y - mtx[1][3];
    rel.z = pos->z - mtx[2][3];
    axis.x = mtx[0][1];
    axis.y = mtx[1][1];
    axis.z = mtx[2][1];
    if (Vec3_Dot(&rel, &axis) < -radius) {
        return 0;
    }
    axis.x = mtx[0][0];
    axis.y = mtx[1][0];
    axis.z = mtx[2][0];
    mag = Vec3_Magnitude(&axis);
    if (lbl_806D95B8 != mag) {
        PSVECScale(&axis, &axis, lbl_806D95BC / mag);
    }
    d = Vec3_Dot(&rel, &axis);
    lim = ext->z * mag + radius;
    if (d > lim) {
        return 0;
    }
    if (d < -lim) {
        return 0;
    }
    axis.x = mtx[0][2];
    axis.y = mtx[1][2];
    axis.z = mtx[2][2];
    mag = Vec3_Magnitude(&axis);
    if (lbl_806D95B8 != mag) {
        PSVECScale(&axis, &axis, lbl_806D95BC / mag);
    }
    d = Vec3_Dot(&rel, &axis);
    if (d > ext->x * mag + radius) {
        return 0;
    }
    return !(d < -(ext->y * mag));
}
#pragma exceptions reset
