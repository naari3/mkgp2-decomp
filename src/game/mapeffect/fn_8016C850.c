typedef struct { float x, y, z; } Vec;
typedef struct PointList {
    int count;
    Vec *pts;
} PointList;

extern const float lbl_806D8B00;
extern const float lbl_806D8B04;
extern float PSVECSquareMag(const Vec *v);

int fn_8016C850(PointList *l, Vec *pos) {
    int i;
    float lim, pz, py, px;
    Vec d;
    if (l->count == 0) return -1;
    px = pos->x;
    py = lbl_806D8B00;
    pz = pos->z;
    lim = lbl_806D8B04;
    for (i = 0; i < l->count; i++) {
        d.x = px - l->pts[i].x;
        d.y = py;
        d.z = pz - l->pts[i].z;
        if (PSVECSquareMag(&d) < lim) return i;
    }
    return -1;
}
