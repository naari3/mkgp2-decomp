/* Joint matrix as a 4x4 row-vector matrix: the transposed 3x4 rotation and
 * the translation in the last row. */
typedef struct KartDriver KartDriver;

extern float (*KartDriver_GetJointByIdx(KartDriver *self, int idx))[4];
extern void PSMTX44Identity(float m[4][4]);

void KartDriver_GetJointMatrix4x3(KartDriver *self, int idx, float out[4][4])
{
    float (*m)[4] = KartDriver_GetJointByIdx(self, idx);

    PSMTX44Identity(out);
    out[0][0] = m[0][0];
    out[0][1] = m[1][0];
    out[0][2] = m[2][0];
    out[1][0] = m[0][1];
    out[1][1] = m[1][1];
    out[1][2] = m[2][1];
    out[2][0] = m[0][2];
    out[2][1] = m[1][2];
    out[2][2] = m[2][2];
    out[3][0] = m[0][3];
    out[3][1] = m[1][3];
    out[3][2] = m[2][3];
}
