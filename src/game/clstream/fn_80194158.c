unsigned char fn_80194158(unsigned char v, unsigned char lo, unsigned char hi) {
    if (v > hi) {
        return hi;
    }
    if (v < lo) {
        return lo;
    }
    return v;
}
