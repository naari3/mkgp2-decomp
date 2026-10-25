/* HitMessageOverlay_FrameUpdate (0x800AC1C4): per-frame update and draw of
 * the "hit" message overlay. Steps the two tweens, bobs the banner, blinks
 * the second layer every 10 frames, and draws the banner, the attacker /
 * victim lines and the blinking prompt. Returns 1 while it is visible. */

/* Sprite draw request (ResCtrl_Init / dtor_80082960). */
struct ResCtrl {
    ResCtrl();
    ~ResCtrl() {}
    int resId;
    int field4;
    int mode;
    int fieldc;
    unsigned char flag;
    unsigned char pad11[3];
    float x;
    float y;
    float z;
    float width;
    float height;
    float rot;
    float scaleX;
    float scaleY;
    unsigned int colors[4];
    unsigned char flipX;
    unsigned char flipY;
    unsigned char pad46[2];
    int tail[4];
    void Show(float px, float py, float pz) {
        flag = 1;
        x = px;
        y = py;
        z = pz;
    }
    void SetScaleXY(float sx, float sy) {
        scaleX = sx;
        scaleY = sy;
    }
    void SetScale(float s) {
        scaleX = s;
        scaleY = s;
    }
    void SetColor(unsigned int col) {
        colors[0] = col;
        colors[1] = col;
        colors[2] = col;
        colors[3] = col;
    }
};

struct TweenInterp {
    void *vtable;
    short from;
    short to;
    float t;
    float value;
    float speed;
};

extern "C" {
extern unsigned char lbl_806D1478;
extern unsigned char lbl_806CF270;
extern int lbl_806CF274;
extern int lbl_806CF278;
extern int lbl_806D147C;
extern int lbl_806D1480;
extern float lbl_806D1484;
extern float lbl_806D1488;
extern TweenInterp *lbl_806D148C;
extern TweenInterp *lbl_806D1490;
extern int lbl_806D1494;
extern int lbl_806D1498;
extern const float lbl_80328BC4[];

extern const float lbl_806D4E90; /* 0.0 */
extern const float lbl_806D4E94; /* 1.0 */
extern const float lbl_806D4E98;
extern const float lbl_806D4E9C;
extern const float lbl_806D4EA0;
extern const float lbl_806D4EA4;
extern const float lbl_806D4EA8;
extern const float lbl_806D4EAC;
extern const float lbl_806D4EB0;
extern const float lbl_806D4EB4;
extern const float lbl_806D4EB8;
extern const float lbl_806D4EBC;
extern const float lbl_806D4EC0;
extern const float lbl_806D4EC4;
extern const float lbl_806D4EC8;
extern const float lbl_806D4ECC;
extern const float lbl_806D4ED0;
extern const float lbl_806D4ED4;
extern const float lbl_806D4ED8;
extern const float lbl_806D4EDC;

void fn_8020A734(TweenInterp *t, int frames, float from, float to);
float fn_8020A6CC(TweenInterp *t);
void fn_80121E10(ResCtrl *c);
void fn_8011FAFC(ResCtrl *c, int layer);
}

static inline void Tween_Tick(TweenInterp *t)
{
    short lim;
    t->to++;
    lim = t->from;
    if (t->to >= lim) {
        t->to = lim;
    }
}

extern "C" int HitMessageOverlay_FrameUpdate(void)
{
    ResCtrl c;
    float off;

    if (!lbl_806CF270) {
        return 0;
    }
    if (!lbl_806D1478) {
        return 0;
    }
    if (lbl_806CF274 == -1) {
        return 0;
    }

    lbl_806D147C++;
    Tween_Tick(lbl_806D148C);
    if (lbl_806D147C == 0xA6) {
        fn_8020A734(lbl_806D148C, 0x10, lbl_806D4E90, lbl_806D4E98);
    }
    if (lbl_806D147C == 0xB6) {
        lbl_806CF274 = -1;
    }

    lbl_806D1484 += lbl_806D1488;
    if (lbl_806D1488 > lbl_806D4E90) {
        if (lbl_806D1484 > lbl_806D4E9C) {
            lbl_806D1488 = lbl_806D4EA0;
        }
    } else if (lbl_806D1484 < lbl_806D4EA4) {
        lbl_806D1488 = lbl_806D4E94;
    }

    Tween_Tick(lbl_806D1490);
    lbl_806D1480 = (lbl_806D1480 + 1) % 20;
    if (lbl_806D1480 == 0) {
        fn_8020A734(lbl_806D1490, 10, lbl_806D4E90, lbl_806D4E94);
    } else if (lbl_806D1480 == 10) {
        fn_8020A734(lbl_806D1490, 10, lbl_806D4E94, lbl_806D4E90);
    }

    if (lbl_806CF274 == -1) {
        return 0;
    }

    fn_80121E10(&c);
    c.resId = 0xC6E;
    c.tail[0] = 1;
    c.tail[1] = 4;
    c.tail[2] = 1;
    c.Show(lbl_806D4EB0, lbl_806D4EA8 + (lbl_806D4EAC - fn_8020A6CC(lbl_806D148C)), lbl_806D4E94);
    c.SetScaleXY(lbl_806D4EB4, lbl_806D4EB8);
    c.rot = lbl_806D4EBC * lbl_806D1484;
    fn_8011FAFC(&c, 4);

    if (lbl_806CF278 != -1) {
        fn_80121E10(&c);
        c.resId = lbl_806CF278;
        c.Show(lbl_806D4EB0, lbl_806D4EA8 + (lbl_806D4EAC - fn_8020A6CC(lbl_806D148C)), lbl_806D4E94);
        c.SetScaleXY(lbl_806D4EC0, lbl_806D4EC4);
        c.rot = lbl_806D4EBC * lbl_806D1484;
        fn_8011FAFC(&c, 4);
    }

    if (lbl_806D1494 != -1) {
        fn_80121E10(&c);
        c.resId = lbl_806D1494;
        c.Show(lbl_806D4EB0, lbl_806D4EA8 + (lbl_806D4EAC - fn_8020A6CC(lbl_806D148C)), lbl_806D4E94);
        c.scaleY = c.scaleX = lbl_806D4EC8;
        c.rot = lbl_806D4EBC * lbl_806D1484;
        fn_8011FAFC(&c, 4);
    }

    if (lbl_806CF274 != -1) {
        fn_80121E10(&c);
        off = lbl_806D4E90;
        c.resId = lbl_806CF274;
        if (lbl_806D1498 == 1) {
            off = lbl_806D4ECC;
        }
        c.Show(lbl_806D4EB0, off + (lbl_806D4EA8 + (lbl_806D4EAC - fn_8020A6CC(lbl_806D148C))), lbl_806D4E94);
        c.SetScale(lbl_80328BC4[lbl_806D1498]);
        c.rot = lbl_806D4EBC * lbl_806D1484;
        fn_8011FAFC(&c, 4);
    }

    {
        float blink = fn_8020A6CC(lbl_806D1490);
        unsigned int col = (unsigned int)(lbl_806D4ED0 * blink) | 0xFFFFFF00;
        fn_80121E10(&c);
        c.resId = 0xC6C;
        c.Show(lbl_806D4EB0, lbl_806D4ED4 + (lbl_806D4EAC - fn_8020A6CC(lbl_806D148C)), lbl_806D4E94);
        c.SetScale(lbl_806D4EDC * blink + lbl_806D4ED8);
        c.SetColor(col);
        fn_8011FAFC(&c, 4);
    }
    return 1;
}
