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

extern const float lbl_806D9360;
extern void fn_80189C10(BBox *box);
extern void Vec3_Subtract(Vec3 *a, Vec3 *b, Vec3 *out);
extern float Vec3_Magnitude(Vec3 *v);

void fn_80189FD8(BBox *box, Vec3 *min, Vec3 *max) {
    Vec3 d;
    fn_80189C10(box);
    box->min.x = min->x;
    box->min.y = min->y;
    box->min.z = min->z;
    box->max.x = max->x;
    box->max.y = max->y;
    box->max.z = max->z;
    box->center.x = 0.5f * (box->max.x + box->min.x);
    box->center.y = 0.5f * (box->max.y + box->min.y);
    box->center.z = 0.5f * (box->max.z + box->min.z);
    Vec3_Subtract(&box->max, &box->center, &d);
    box->radius = Vec3_Magnitude(&d);
}
