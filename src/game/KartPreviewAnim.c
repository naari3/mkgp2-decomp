/* 0x8012B924..0x8012BDA4: kart preview animation requests. Each one picks
 * the next animation and its camera framing, and fails while another
 * request is still pending. */
typedef struct KartPreviewParts {
    void *kart;
    void *tires;
    void *driver;
    void *extraA;
    void *extraB;
    void *parts[49];
    int fD8;
    float fDC[3];
    int characterId;
    int animCur;
    int animNext;
    int animBase;
    float fF8;
    float fFC;
    float f100;
    int f104;
    float f108;
    float f10C;
    float f110;
    float f114;
    float f118;
    float f11C;
    float f120;
    void *attach;
    void *attachJoint;
    char pad12C[0x144 - 0x12C];
    int f144;
    int f148;
    int f14C;
    int f150;
    int f154;
    int f158;
    int f15C;
    int f160;
    int f164;
} KartPreviewParts;

extern float lbl_806CF01C, lbl_806CF020, lbl_806CF024, lbl_806CF028, lbl_806CF04C, lbl_806CF050, lbl_806CF054, lbl_806CF058, lbl_806CF06C, lbl_806CF070, lbl_806CF074, lbl_806CF078, lbl_806CF07C, lbl_806CF080, lbl_806CF084, lbl_806CF088, lbl_806CF08C, lbl_806CF090, lbl_806CF094, lbl_806CF098;

static inline void KartPreview_SetAnim(KartPreviewParts *self, int anim)
{
    int cur = self->animNext;
    if (cur == 0) {
        self->animCur = cur + self->animBase;
    } else if (cur == -1) {
        self->animCur = cur + self->animBase;
    } else {
        self->animCur = cur;
    }
    self->animNext = anim;
}

int fn_8012B924(KartPreviewParts *self)
{
    int base = self->animBase;
    int cur;
    if (base == 0) {
        return 0;
    }
    cur = self->animNext;
    if (cur == 0) {
        self->animCur = cur + base;
    } else if (cur == -1) {
        self->animCur = cur + base;
    } else {
        self->animCur = cur;
    }
    self->animNext = -1;
    self->f10C = 1.0f;
    self->f118 = 1.0f;
    self->f120 = 0.1f;
    self->f110 = -1.0f;
    self->f114 = 0.0f;
    self->f11C = 0.0f;
    self->f108 = 0.0f;
    self->animBase = 0;
    return 1;
}

int fn_8012B9AC(KartPreviewParts *self)
{
    int base = self->animBase;
    int cur;
    if (base == 0) {
        return 0;
    }
    cur = self->animNext;
    if (cur == 0) {
        self->animCur = cur + base;
    } else if (cur == -1) {
        self->animCur = cur + base;
    } else {
        self->animCur = cur;
    }
    self->animNext = 0x17;
    self->f10C = lbl_806CF08C;
    self->f118 = lbl_806CF090;
    self->f120 = lbl_806CF094;
    self->f110 = lbl_806CF098;
    self->f114 = 0.0f;
    self->f11C = 0.0f;
    self->f108 = 0.0f;
    self->animBase = 0;
    return 1;
}

int fn_8012BA38(KartPreviewParts *self)
{
    if (self->animNext != 0) {
        return 0;
    }
    KartPreview_SetAnim(self, 1);
    self->f10C = lbl_806CF07C;
    self->f118 = lbl_806CF080;
    self->f120 = lbl_806CF084;
    self->f110 = lbl_806CF088;
    self->f114 = 0.0f;
    self->f11C = 0.0f;
    self->f108 = 0.0f;
    self->animBase = 1;
    self->f154 = 1;
    return 1;
}

int fn_8012BAC4(KartPreviewParts *self)
{
    if (self->animNext != 0) {
        return 0;
    }
    if (self->animBase != 0) {
        return 0;
    }
    KartPreview_SetAnim(self, 0x25);
    self->f10C = lbl_806CF06C;
    self->f118 = lbl_806CF070;
    self->f120 = lbl_806CF074;
    self->f110 = lbl_806CF078;
    self->f114 = 0.0f;
    self->f11C = 0.0f;
    self->f108 = 0.0f;
    return 1;
}

int fn_8012BB58(KartPreviewParts *self)
{
    if (self->animNext != 0) {
        return 0;
    }
    if (self->animBase == 0) {
        KartPreview_SetAnim(self, 0x18);
        self->f10C = lbl_806CF04C;
        self->f118 = lbl_806CF050;
        self->f120 = lbl_806CF054;
        self->f110 = lbl_806CF058;
        self->f114 = 0.0f;
        self->f11C = 0.0f;
        self->f108 = 0.0f;
    } else if (self->animBase == 3) {
        KartPreview_SetAnim(self, 0x1A);
        self->f10C = lbl_806CF04C;
        self->f118 = lbl_806CF050;
        self->f120 = lbl_806CF054;
        self->f110 = lbl_806CF058;
        self->f114 = 0.0f;
        self->f11C = 0.0f;
        self->f108 = 0.0f;
    } else if (self->animBase == 4) {
        KartPreview_SetAnim(self, 0x1B);
        self->f10C = lbl_806CF04C;
        self->f118 = lbl_806CF050;
        self->f120 = lbl_806CF054;
        self->f110 = lbl_806CF058;
        self->f114 = 0.0f;
        self->f11C = 0.0f;
        self->f108 = 0.0f;
    } else {
        KartPreview_SetAnim(self, 0x19);
        self->f10C = lbl_806CF04C;
        self->f118 = lbl_806CF050;
        self->f120 = lbl_806CF054;
        self->f110 = lbl_806CF058;
        self->f114 = 0.0f;
        self->f11C = 0.0f;
        self->f108 = 0.0f;
    }
    return 1;
}

int fn_8012BD2C(KartPreviewParts *self)
{
    KartPreview_SetAnim(self, 0x14);
    self->f10C = lbl_806CF01C;
    self->f118 = lbl_806CF020;
    self->f120 = lbl_806CF024;
    self->f110 = lbl_806CF028;
    self->f114 = 0.0f;
    self->f11C = 0.0f;
    self->f108 = 0.0f;
    return 1;
}
