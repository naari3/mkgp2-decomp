/* Compute into a separate matrix so either input may alias the output. */
void Matrix4_Multiply(float *out, const float *left, const float *right)
{
    float result[16];
    int row;
    float *dest = result;
    int i;

    for (row = 0; row < 4; ++row) {
        float a, b, c, d;
        a = left[0] * right[0];
        b = left[0] * right[1];
        c = left[0] * right[2];
        d = left[0] * right[3];
        a += right[4] * left[1];
        b += right[5] * left[1];
        c += right[6] * left[1];
        d += right[7] * left[1];
        a += right[8] * left[2];
        b += right[9] * left[2];
        c += right[10] * left[2];
        d += right[11] * left[2];
        a += right[12] * left[3];
        b += right[13] * left[3];
        c += right[14] * left[3];
        d += right[15] * left[3];
        dest[0] = a;
        dest[1] = b;
        dest[2] = c;
        dest[3] = d;
        left += 4;
        dest += 4;
    }
    for (i = 0; i < 16; ++i) {
        out[i] = result[i];
    }
}
