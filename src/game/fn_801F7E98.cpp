/* Default constructor for a draw-node description. */
extern "C" {
void *memset(void *dst, int c, unsigned long n);
void PSMTXIdentity(float m[3][4]);
extern const float lbl_806DA710;
extern const float lbl_806DA718;
}

struct NodeDesc {
    float color[4];
    float f10;
    int i14;
    unsigned short h18;
    unsigned short h1A;
    float f1C;
    float f20;
    float f24;
    float f28;
    int i2C;
    float f30;
    float f34;
    float f38;
    float f3C;
    float f40;
    char tag[16];
    int i54;
    int i58;
    int i5C;
    int i60;
    float mtx[3][4];

    NodeDesc();
};

NodeDesc::NodeDesc() {
    i2C = 0;
    f38 = lbl_806DA718;
    f3C = lbl_806DA710;
    f40 = lbl_806DA710;
    i54 = 1;
    i58 = 4;
    i5C = 5;
    i60 = 15;
    f34 = lbl_806DA710;
    f30 = lbl_806DA710;
    color[3] = lbl_806DA718;
    color[2] = lbl_806DA718;
    color[1] = lbl_806DA718;
    color[0] = lbl_806DA718;
    f10 = lbl_806DA718;
    i14 = 0;
    h1A = 1;
    h18 = 1;
    f20 = lbl_806DA718;
    f1C = lbl_806DA718;
    f28 = lbl_806DA710;
    f24 = lbl_806DA710;
    memset(tag, -1, 16);
    PSMTXIdentity(mtx);
}
