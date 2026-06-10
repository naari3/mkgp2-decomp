void isink(int *p);
typedef struct I8 { int m[8]; } I8;
void i8_member(const I8 *src) {
    I8 x;
    x.m[0] = src->m[0];
    x.m[1] = src->m[1];
    x.m[2] = src->m[2];
    x.m[3] = src->m[3];
    x.m[4] = src->m[4];
    x.m[5] = src->m[5];
    x.m[6] = src->m[6];
    x.m[7] = src->m[7];
    isink(x.m);
}
typedef struct V3i { int x, y, z; } V3i;
void i3_member(const V3i *src) {
    V3i v;
    v.x = src->x;
    v.y = src->y;
    v.z = src->z;
    isink(&v.x);
}
