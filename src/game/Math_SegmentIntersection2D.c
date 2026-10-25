/* 2D (XZ) segment intersection, 0x80036154..0x80036278. */

unsigned char Math_SegmentIntersection2D(void *self, float ax, float az, float bx, float bz, float cx, float cz, float dx,
                               float dz, float *out)
{
    float abx = bx - ax;
    float abz = bz - az;
    float cdx = dx - cx;
    float cdz = dz - cz;
    float den;
    float ex;
    float ez;
    float t;
    float u;

    if (ax == bx && az == bz) {
        return 0;
    }
    if (cx == dx && cz == dz) {
        return 0;
    }
    den = abx * cdz - cdx * abz;
    if (0.0f == den) {
        return 0;
    }
    ex = ax - cx;
    ez = az - cz;
    t = abx * ez - abz * ex;
    u = cdx * ez - cdz * ex;
    if ((den > 0.0f && 0.0f <= u && u <= den) ||
        (den < 0.0f && den <= u && u <= 0.0f)) {
        if ((den > 0.0f && 0.0f <= t && t <= den) ||
            (den < 0.0f && den <= t && t <= 0.0f)) {
            u /= den;
            out[0] = ax + abx * u;
            out[2] = az + abz * u;
            return 1;
        }
    }
    return 0;
}
