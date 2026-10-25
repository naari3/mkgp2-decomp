void Mtx44_Scale_Uniform(float dst[4][4], float src[4][4], float s)
{
    dst[0][0] = s * src[0][0];
    dst[1][0] = s * src[1][0];
    dst[2][0] = s * src[2][0];
    dst[3][0] = s * src[3][0];
    dst[0][1] = s * src[0][1];
    dst[1][1] = s * src[1][1];
    dst[2][1] = s * src[2][1];
    dst[3][1] = s * src[3][1];
    dst[0][2] = s * src[0][2];
    dst[1][2] = s * src[1][2];
    dst[2][2] = s * src[2][2];
    dst[3][2] = s * src[3][2];
    dst[0][3] = src[0][3];
    dst[1][3] = src[1][3];
    dst[2][3] = src[2][3];
    dst[3][3] = src[3][3];
}

void Mtx44_Scale_PerAxis(float dst[4][4], float src[4][4], float sx, float sy, float sz)
{
    dst[0][0] = sx * src[0][0];
    dst[1][0] = sx * src[1][0];
    dst[2][0] = sx * src[2][0];
    dst[3][0] = sx * src[3][0];
    dst[0][1] = sy * src[0][1];
    dst[1][1] = sy * src[1][1];
    dst[2][1] = sy * src[2][1];
    dst[3][1] = sy * src[3][1];
    dst[0][2] = sz * src[0][2];
    dst[1][2] = sz * src[1][2];
    dst[2][2] = sz * src[2][2];
    dst[3][2] = sz * src[3][2];
    dst[0][3] = src[0][3];
    dst[1][3] = src[1][3];
    dst[2][3] = src[2][3];
    dst[3][3] = src[3][3];
}
