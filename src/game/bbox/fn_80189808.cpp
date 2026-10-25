/* 0x80189808: add the octant `oct` child box of an octree node, unless it
 * already exists. */

typedef struct Vec3 {
    float x, y, z;
} Vec3;

struct BBox {
    BBox(Vec3 *min, Vec3 *max, BBox *parent, int oct);
    Vec3 min;
    Vec3 max;
    Vec3 center;
    float radius;
    int x28;
    int x2c;
    BBox *next;
    BBox *child;
    int x38;
    int pad3c;
};

extern "C" {
extern Vec3 lbl_80495D48[8];

void fn_80189808(BBox *box, int oct) {
    BBox *c;
    BBox *nb;
    Vec3 lo;
    Vec3 hi;
    float hx, hy, hz;
    float cx, cy, cz;
    for (c = box->child; c != 0; c = c->next) {
        if ((c->x28 & 0xf) == oct) return;
    }
    hx = 0.25f * (box->max.x - box->min.x);
    hy = 0.25f * (box->max.y - box->min.y);
    hz = 0.25f * (box->max.z - box->min.z);
    cx = hx * lbl_80495D48[oct].x + box->center.x;
    cy = hy * lbl_80495D48[oct].y + box->center.y;
    cz = hz * lbl_80495D48[oct].z + box->center.z;
    lo.x = cx - hx;
    lo.y = cy - hy;
    lo.z = cz - hz;
    hi.x = cx + hx;
    hi.y = cy + hy;
    hi.z = cz + hz;
    nb = new BBox(&lo, &hi, box, oct);
    if (box->child == 0) {
        box->child = nb;
    } else {
        for (c = box->child; c->next != 0; c = c->next) {
        }
        c->next = nb;
    }
}
}
