/* Contiguous observed Matrix4/Vec3 leaf operations. Shared constants stay external. */
extern const float lbl_806D592C;
extern const float lbl_806D5930;

void Matrix4_Identity(float *matrix)
{
    matrix[0] = lbl_806D5930;
    matrix[1] = lbl_806D592C;
    matrix[2] = lbl_806D592C;
    matrix[3] = lbl_806D592C;
    matrix[4] = lbl_806D592C;
    matrix[5] = lbl_806D5930;
    matrix[6] = lbl_806D592C;
    matrix[7] = lbl_806D592C;
    matrix[8] = lbl_806D592C;
    matrix[9] = lbl_806D592C;
    matrix[10] = lbl_806D5930;
    matrix[11] = lbl_806D592C;
    matrix[12] = lbl_806D592C;
    matrix[13] = lbl_806D592C;
    matrix[14] = lbl_806D592C;
    matrix[15] = lbl_806D5930;
}

void Matrix4_Copy(float *destination, const float *source)
{
    int i;
    for (i = 0; i < 16; ++i) destination[i] = source[i];
}

static inline float Lerp1(float a, float b, float t)
{
    return a * t + b * (lbl_806D5930 - t);
}

void Vec3_Lerp(float *out, const float *first, const float *second, float t)
{
    float x = Lerp1(first[0], second[0], t);
    float y = Lerp1(first[1], second[1], t);
    float z = Lerp1(first[2], second[2], t);
    out[0] = x;
    out[1] = y;
    out[2] = z;
}
