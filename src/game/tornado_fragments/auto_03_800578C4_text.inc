/* === extracted from auto_03_800578C4_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- function index (3 fns, .text 0x800578C4..0x80057960) ---
 * [  0] 0x800578C4 size:0x10    global TornadoEffect_SetMatrixRow0_5c
 * [  1] 0x800578D4 size:0x8     global TornadoEffect_SetFieldAc
 * [  2] 0x800578DC size:0x84    global TornadoEffect_SetMatrix1c
 */

/* --- forward decls --- */

/* --- asm function bodies (.text order = fn address order) --- */
/* 0x800578C4 size:0x10 */
void TornadoEffect_SetMatrixRow0_5c(void *e, float x, float y, float z) {
    TE_F(e, 0x5C) = x;
    TE_F(e, 0x60) = y;
    TE_F(e, 0x64) = z;
}

/* 0x800578D4 size:0x8 */
void TornadoEffect_SetFieldAc(void *e, float v) {
    TE_F(e, 0xAC) = v;
}

/* 0x800578DC size:0x84: copies a 4x4 matrix to e+0x1C. __restrict on both
 * pointers gives the target's load-ahead (f1/f0 pipelined) schedule. */
void TornadoEffect_SetMatrix1c(float *__restrict e, const float *__restrict m) {
    e[7] = m[0];
    e[8] = m[1];
    e[9] = m[2];
    e[10] = m[3];
    e[11] = m[4];
    e[12] = m[5];
    e[13] = m[6];
    e[14] = m[7];
    e[15] = m[8];
    e[16] = m[9];
    e[17] = m[10];
    e[18] = m[11];
    e[19] = m[12];
    e[20] = m[13];
    e[21] = m[14];
    e[22] = m[15];
}

