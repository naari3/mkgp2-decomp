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

BBox *fn_8018A2E8(BBox *box) {
    lbl_806D1694++;
    box->min.x = 0.0f;
    box->min.y = 0.0f;
    box->min.z = 0.0f;
    box->max.x = 0.0f;
    box->max.y = 0.0f;
    box->max.z = 0.0f;
    box->x28 = 0;
    box->x2c = 0;
    box->x30 = 0;
    box->x34 = 0;
    box->x38 = 0;
    return box;
}
