int WrapInRange(int value, int lo, int hi) {
    if (value > hi) {
        return lo;
    }
    if (value < lo) {
        return hi;
    }
    return value;
}
