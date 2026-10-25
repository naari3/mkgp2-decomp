int Math_Segment2DIntersect(float *outT, float *outPos, float ax, float ay, float bx, float by,
                            float cx, float cy, float dx, float dy) {
    float abx = bx - ax;
    float aby = by - ay;
    float cdx = dx - cx;
    float cdy = dy - cy;
    float denom;
    float s;
    float t;
    float acx;
    float acy;

    if (ax == bx && ay == by) {
        return 0;
    }
    if (cx == dx && cy == dy) {
        return 0;
    }
    denom = abx * cdy - cdx * aby;
    if (0.0f == denom) {
        return 0;
    }
    acx = ax - cx;
    acy = ay - cy;
    s = abx * acy - aby * acx;
    t = cdx * acy - cdy * acx;
    if ((denom > 0.0f && 0.0f <= t && t <= denom) || (denom < 0.0f && denom <= t && t <= 0.0f)) {
        if ((denom > 0.0f && 0.0f <= s && s <= denom) ||
            (denom < 0.0f && denom <= s && s <= 0.0f)) {
            t /= denom;
            if (outT != 0) {
                *outT = t;
            }
            if (outPos != 0) {
                outPos[0] = abx * t + ax;
                outPos[1] = 0.0f;
                outPos[2] = aby * t + ay;
            }
            return 1;
        }
    }
    return 0;
}
