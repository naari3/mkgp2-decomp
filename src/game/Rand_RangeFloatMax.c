/* Uniform random float in [0, max). */
extern int Rand15(void);
extern const float lbl_806D5950;

float Rand_RangeFloatMax(float max)
{
    return max * ((float)Rand15() / lbl_806D5950);
}
