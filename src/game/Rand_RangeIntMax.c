extern int Rand15(void);

#pragma exceptions on
int Rand_RangeIntMax(int max)
{
    int value = ((max + 1) * Rand15()) / 32767;

    if (max < value) {
        value = max;
    }
    return value;
}
#pragma exceptions reset
