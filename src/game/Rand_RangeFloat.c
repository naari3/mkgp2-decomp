/* Uniform random float in [min, max). */
extern int Rand15(void);
extern const float lbl_806D5950;

float Rand_RangeFloat(float min, float max)
{
    return (max - min) * ((float)Rand15() / lbl_806D5950) + min;
}
