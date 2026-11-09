static inline float Add2(float a, float b) { return a + b; }
#pragma push
#pragma opt_propagation off
void fn_8019EB9C(Matrix44 *a, Vec3 *out, const Vec3 *v) {
    float vx = v->x;
    float vy = v->y;
    float vz = v->z;
    float x, y, z;
    x = Add2(vz * a->m[2][0] + (a->m[0][0] * vx + vy * a->m[1][0]), a->m[3][0]);
    y = Add2(vz * a->m[2][1] + (a->m[0][1] * vx + vy * a->m[1][1]), a->m[3][1]);
    z = Add2(vz * a->m[2][2] + (vx * a->m[0][2] + vy * a->m[1][2]), a->m[3][2]);
    out->x = x; out->y = y; out->z = z;
}
#pragma pop
