/* Vec2_RotateZ / Vec2_RotateY / Vec2_RotateX (0x800D6188..0x800D6338, 0x90 each).
 *
 * Rotate a Vec3 about one axis using the 16-bit binary-angle LUT helpers
 * (LUT_Sine / LUT_Cosine, game/LUT_Sine.c). Each fn rotates the two
 * off-axis components and passes the on-axis component through. Each has
 * an extab/extabindex entry (compiled with -Cpp_exceptions on, CW
 * auto-emit, same as sibling Vec3_Scale.c).
 *
 * Load-bearing idioms for the fp scratch register assignment
 * (target: passthrough=f0, t=b*c temp=f2, b=f3, a=f4, fmadds result=f1):
 * (1) `__restrict` on both pointer params (same as sibling Vec3_ScaleXZ.c)
 *     -- without it CW reloads in->x/in->y after the first out-> store and
 *     the passthrough load cannot join the pre-store load group;
 * (2) passthrough component read directly (`out->z = in->z;` as last
 *     statement, no named local) -- its web then takes f0 ahead of the
 *     product temps; a named local instead lands it in f4;
 * (3) rotated results computed into named locals (rx/ry) stored before the
 *     passthrough -- naming them merges the result web with the b*c fmuls
 *     temp so the temp takes f2 before b/a (direct expression stores give
 *     t=f3/b=f2 swap instead).
 */

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern float LUT_Sine(float angle);
extern float LUT_Cosine(float angle);

void Vec2_RotateZ(Vec3 *__restrict out, const Vec3 *__restrict in, float angle) {
    float s = LUT_Sine(angle);
    float c = LUT_Cosine(angle);
    float rx = in->x * s - in->y * c;
    float ry = in->x * c + in->y * s;
    out->x = rx;
    out->y = ry;
    out->z = in->z;
}

void Vec2_RotateY(Vec3 *__restrict out, const Vec3 *__restrict in, float angle) {
    float s = LUT_Sine(angle);
    float c = LUT_Cosine(angle);
    float rz = in->z * s - in->x * c;
    float rx = in->z * c + in->x * s;
    out->z = rz;
    out->x = rx;
    out->y = in->y;
}

void Vec2_RotateX(Vec3 *__restrict out, const Vec3 *__restrict in, float angle) {
    float s = LUT_Sine(angle);
    float c = LUT_Cosine(angle);
    float ry = in->y * s - in->z * c;
    float rz = in->y * c + in->z * s;
    out->y = ry;
    out->z = rz;
    out->x = in->x;
}
