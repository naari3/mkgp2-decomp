extern int Rand15(void);

#pragma exceptions on
int Rand_RangeInt(int min, int max) {
    int value = min + ((max - min + 1) * Rand15()) / 32767;
    if (max < value) {
        value = max;
    }
    return value;
}
#pragma exceptions reset
