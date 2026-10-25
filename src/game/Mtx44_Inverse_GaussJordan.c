/* Mtx44_Inverse_GaussJordan (0x800D4B0C): 4x4 matrix inverse by
 * Gauss-Jordan elimination with partial pivoting (same algorithm as the
 * SDK's C_MTX44Inverse, but dst-first and without a return value). Leaves
 * dst partially reduced if src is singular. */

typedef float Mtx44[4][4];

extern const float lbl_806D592C; /* 0.0 */
extern const float lbl_806D5930; /* 1.0 */
extern void PSMTX44Copy(Mtx44 src, Mtx44 dst);
extern void PSMTX44Identity(Mtx44 m);


#define SWAPF(a, b) \
    {               \
        float t = a; \
        a = b;      \
        b = t;      \
    }

void Mtx44_Inverse_GaussJordan(Mtx44 inv, Mtx44 src)
{
    Mtx44 gjm;
    int i;
    int j;
    int k;
    float w;

    PSMTX44Copy(src, gjm);
    PSMTX44Identity(inv);
    for (i = 0; i < 4; i++) {
        float max = lbl_806D592C;
        int swp = i;

        for (k = i; k < 4; k++) {
            float ftmp = __fabs(gjm[k][i]);
            if (ftmp > max) {
                max = ftmp;
                swp = k;
            }
        }
        if (lbl_806D592C == max) {
            return;
        }
        if (swp != i) {
            for (k = 0; k < 4; k++) {
                SWAPF(gjm[i][k], gjm[swp][k]);
                SWAPF(inv[i][k], inv[swp][k]);
            }
        }
        w = lbl_806D5930 / gjm[i][i];
        for (j = 0; j < 4; j++) {
            gjm[i][j] *= w;
            inv[i][j] *= w;
        }
        for (k = 0; k < 4; k++) {
            if (k == i) {
                continue;
            }
            w = gjm[k][i];
            for (j = 0; j < 4; j++) {
                gjm[k][j] -= gjm[i][j] * w;
                inv[k][j] -= inv[i][j] * w;
            }
        }
    }
}
