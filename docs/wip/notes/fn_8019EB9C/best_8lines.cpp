#pragma push
#pragma opt_propagation off
void fn_8019EB9C(Matrix44 *a, Vec3 *out, const Vec3 *v) {
    float vx = v->x;
    float vy = v->y;
    float vz = v->z;
    float x, y, z;
    float tx, ty, tz;
    x = vz * a->m[2][0] + (a->m[0][0] * vx + vy * a->m[1][0]);
    tx = a->m[3][0];
    x = x + tx;
    y = vz * a->m[2][1] + (a->m[0][1] * vx + vy * a->m[1][1]);
    ty = a->m[3][1];
    y = y + ty;
    z = vz * a->m[2][2] + (vx * a->m[0][2] + vy * a->m[1][2]);
    tz = a->m[3][2];
    z = z + tz;
    out->x = x; out->y = y; out->z = z;
}
#pragma pop
