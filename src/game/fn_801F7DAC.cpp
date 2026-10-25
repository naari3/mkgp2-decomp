/* Copy-assignment for a draw-node description (name, params and matrix). */
extern "C" {
void *memcpy(void *dst, const void *src, unsigned long n);
void PSMTXCopy(const float src[3][4], float dst[3][4]);
}

struct Vec2f {
    float x, y;
};

struct Vec3f {
    float x, y, z;
};

struct Rect4f {
    float a, b, c, d;
};

struct Pair16 {
    unsigned short a, b;
};

struct Quad32 {
    int a, b, c, d;
};

struct NodeDesc {
    char name[16];
    float f10;
    int i14;
    Pair16 h18;
    Rect4f r1C;
    int i2C;
    Vec2f v30;
    Vec3f v38;
    char tag[16];
    Quad32 q54;
    float mtx[3][4];

    NodeDesc &operator=(const NodeDesc &o);
};

NodeDesc &NodeDesc::operator=(const NodeDesc &o) {
    i2C = o.i2C;
    v38 = o.v38;
    v30 = o.v30;
    memcpy(name, o.name, 16);
    f10 = o.f10;
    i14 = o.i14;
    h18 = o.h18;
    r1C = o.r1C;
    memcpy(tag, o.tag, 16);
    q54 = o.q54;
    PSMTXCopy(o.mtx, mtx);
    return *this;
}
