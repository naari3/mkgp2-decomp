typedef float f32;

f32 Saturate_Double(f32 v, f32 lo, f32 hi) {
    if (v > hi) return hi;
    if (v < lo) return lo;
    return v;
}

int fn_80038798(int v, int lo, int hi) {
    if (v > hi) return hi;
    if (v < lo) return lo;
    return v;
}

int Clamp_Int(int v, int lo, int hi) {
    if (v > hi) return hi;
    if (v < lo) return lo;
    return v;
}
