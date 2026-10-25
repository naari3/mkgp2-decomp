typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct BBox {
    Vec3 min;
    Vec3 max;
    Vec3 center;
    float radius;
    int x28;
    int x2c;
    int x30;
    int x34;
    int x38;
} BBox;

extern int lbl_806D1694;
extern void fn_80189FD8(BBox *box, Vec3 *min, Vec3 *max);

BBox *fn_8018A278(BBox *box, Vec3 *min, Vec3 *max, int a, int b) {
    lbl_806D1694++;
    box->min.x = 0.0f;
    box->min.y = 0.0f;
    box->min.z = 0.0f;
    box->max.x = 0.0f;
    box->max.y = 0.0f;
    box->max.z = 0.0f;
    box->x28 = b;
    box->x2c = a;
    box->x30 = 0;
    box->x34 = 0;
    box->x38 = 0;
    fn_80189FD8(box, min, max);
    return box;
}
