typedef struct TObjView {
    unsigned char pad[0x74];
    float mtx[3][4];
} TObjView;

extern const float lbl_806D927C;
extern void PSMTXTrans(float m[3][4], float x, float y, float z);
extern void PSMTXConcat(float a[3][4], float b[3][4], float ab[3][4]);

void fn_80182A5C(TObjView *tobj, float x, float y) {
    float m[3][4];
    if (tobj != 0) {
        PSMTXTrans(m, x, y, lbl_806D927C);
        PSMTXConcat(m, tobj->mtx, tobj->mtx);
    }
}
