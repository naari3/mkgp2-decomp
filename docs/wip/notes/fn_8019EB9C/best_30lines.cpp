void fn_8019EB9C(Matrix44 *a, Vec3 *out, const Vec3 *v) {
    float vx = v->x;
    float vz = v->z;
    float vy = v->y;
    float x, y, z;
    x = a->m[0][0] * vx + vy * a->m[1][0];
    x = a->m[3][0] + (vz * a->m[2][0] + x);
    y = a->m[0][1] * vx + vy * a->m[1][1];
    y = a->m[3][1] + (vz * a->m[2][1] + y);
    z = vx * a->m[0][2] + vy * a->m[1][2];
    z = a->m[3][2] + (vz * a->m[2][2] + z);
    out->x = x; out->y = y; out->z = z;
}
