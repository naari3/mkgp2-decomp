extern "C" void fn_801DB8F0(void);
extern const float lbl_806DA2D0;
extern const float lbl_806DA2DC;
extern const float lbl_806D18FC;

struct PathCursor {
    PathCursor(int mode);
    ~PathCursor();
    char pad[0x18];
};

struct Mtx44 {
    float m[4][4];

    void Identity() {
        m[0][0] = lbl_806DA2D0; m[0][1] = lbl_806DA2D0; m[0][2] = lbl_806DA2D0; m[0][3] = lbl_806DA2D0;
        m[1][0] = lbl_806DA2D0; m[1][1] = lbl_806DA2D0; m[1][2] = lbl_806DA2D0; m[1][3] = lbl_806DA2D0;
        m[2][0] = lbl_806DA2D0; m[2][1] = lbl_806DA2D0; m[2][2] = lbl_806DA2D0; m[2][3] = lbl_806DA2D0;
        m[3][0] = lbl_806DA2D0; m[3][1] = lbl_806DA2D0; m[3][2] = lbl_806DA2D0; m[3][3] = lbl_806DA2D0;
        m[3][3] = lbl_806DA2DC;
        m[2][2] = lbl_806DA2DC;
        m[1][1] = lbl_806DA2DC;
        m[0][0] = lbl_806DA2DC;
    }
};

struct PathTracker {
    void *owner;
    void *path;
    int unk8;
    int unkC;
    int unk10;
    unsigned char unk14;
    unsigned char unk15;
    float unk18;
    float unk1C;
    float unk20;
    char pad24[0xC];
    Mtx44 mtx;
    PathCursor cursor;

    PathTracker(void *owner, void *path);
};

PathTracker::PathTracker(void *owner, void *path) : cursor(1) {
    this->owner = owner;
    this->path = path;
    fn_801DB8F0();
    unk10 = 0;
    unk14 = 0;
    unk15 = 0;
    unk18 = lbl_806DA2D0;
    unk20 = lbl_806DA2DC;
    unk1C = lbl_806D18FC;
    unk8 = 0;
    unkC = 0;
    mtx.Identity();
}
