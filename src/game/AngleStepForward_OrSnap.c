static inline float Angle_Wrap(float a)
{
    while (a > 3.1415920f) {
        a -= 6.2831840f;
    }
    while (a <= -3.1415920f) {
        a += 6.2831840f;
    }
    return a;
}

static inline float Angle_Abs(float a)
{
    return a < 0.0f ? -a : a;
}

float AngleStepForward_OrSnap(float cur, float target, float step)
{
    float diff = Angle_Wrap(target - cur);

    if (Angle_Abs(diff) < step) {
        return target;
    }
    if (0.0f < diff) {
        cur = cur + step;
    } else {
        cur = cur + step;
    }
    return Angle_Wrap(cur);
}

float AngleStepTowards_Shortest(float cur, float target, float step)
{
    float diff = Angle_Wrap(target - cur);

    if (Angle_Abs(diff) < step) {
        return target;
    }
    if (0.0f < diff) {
        cur = cur + step;
    } else {
        cur = cur - step;
    }
    return Angle_Wrap(cur);
}
