extern void PSMTX44Identity(float dst[4][4]);

void Mtx_TransposeToMtx44(float dst[4][4], float src[3][4])
{
    PSMTX44Identity(dst);
    dst[0][0] = src[0][0];
    dst[0][1] = src[1][0];
    dst[0][2] = src[2][0];
    dst[1][0] = src[0][1];
    dst[1][1] = src[1][1];
    dst[1][2] = src[2][1];
    dst[2][0] = src[0][2];
    dst[2][1] = src[1][2];
    dst[2][2] = src[2][2];
    dst[3][0] = src[0][3];
    dst[3][1] = src[1][3];
    dst[3][2] = src[2][3];
}
