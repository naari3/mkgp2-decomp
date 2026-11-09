#pragma push
#pragma opt_propagation off
#pragma opt_lifetimes off
void fn_8019EB9C(Matrix44 *a, Vec3 *out, const Vec3 *v) {
    float vx;
    float vy;
    float vz;
    float x;
    float z;
    float tx;
    float tz;
    float y;
    float ty;
    vx = v->x;
    vy = v->y;
    vz = v->z;
    x = vz * a->m[2][0] + (a->m[0][0] * vx + vy * a->m[1][0]);
    tx = a->m[3][0];
    x = tx + x;
    y = vz * a->m[2][1] + (a->m[0][1] * vx + vy * a->m[1][1]);
    ty = a->m[3][1];
    y = ty + y;
    tz = a->m[2][2];
    z = vz * tz + (vx * a->m[0][2] + vy * a->m[1][2]);
    tz = a->m[3][2];
    z = tz + z;
    out->x = x; out->y = y; out->z = z;
}
#pragma pop

