float BuildOrientationFromYaw(float angle)
{
    while (angle > 3.1415920f) {
        angle -= 6.283184f;
    }
    while (angle <= -3.1415920f) {
        angle += 6.283184f;
    }
    return angle;
}

float FAbs_FloatAsDouble(float x)
{
    if (x < 0.0f) {
        return -x;
    }
    return x;
}
