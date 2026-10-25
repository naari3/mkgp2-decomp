/*
 * 0x8021F088..0x80224ECC: csSceneCoinMilage.cpp, clCSSceneCoinMilage
 * (vtable lbl_804EDE44, base clSceneInterface lbl_803FE0C8).
 *
 * After a race the scene rains coins, adds up the coins earned this game
 * into the coin mileage, then walks through every item the new mileage
 * unlocks and finally shows how many coins are left to the next one.
 *
 * The menu nodes it draws (nsMenuUtil::clMenuNode, vtable lbl_8048EF34):
 * clGetCoinLine / clGetSumLine (one line of the coin breakdown),
 * clCoinPerfect (the "perfect" bonus) and clGetCoinSum (the mileage total).
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

struct InputState {
    char pad00[4];
    unsigned char enabled;
    char pad05[0xF];
    int dir;
    int held;
    int edge;
};

struct ResCtrl {
    int resId;
    int field4, mode, fieldc;
    unsigned char flag, pad11[3];
    float x, y, z, width, height, field28, scaleX, scaleY;
    unsigned int colors[4];
    bool flipX;
    bool flipY;
    char pad46[2];
    int tail[4];
    ResCtrl();
    ~ResCtrl() {}
    void Show(float px, float py, float pz) {
        flag = 1;
        x = px;
        y = py;
        z = pz;
    }
    void SetColor(unsigned int c) {
        colors[0] = c;
        colors[1] = c;
        colors[2] = c;
        colors[3] = c;
    }
};

/* 0x30-byte animated sprite (dtor Sprite_Destroy). */
struct Sprite {
    int x0;
    int layer;
    int x8;
    float x;
    float y;
    float sx;
    float sy;
    char pad1C[4];
    float alpha;
    char pad24[0x30 - 0x24];
    Sprite(int res, int a, int b);
    ~Sprite();
    void SetAnimParam(int key, short value);
    void SetPos(float px, float py) { x = px; y = py; }
};

template <class T> struct Own {
    T *p;
    Own(T *q) : p(q) {}
    ~Own() throw() { delete p; }
};

template <class T> struct PtrVecData {
    int cap;
    int count;
    T *data;
    PtrVecData() : cap(0), count(0), data(0) {}
    ~PtrVecData() {
        if (data) {
            operator delete(data);
        }
    }
};

template <class T> struct PtrVecBase : PtrVecData<T> {
    PtrVecBase() {}
    ~PtrVecBase() {}
};

extern "C" {
void PtrVec_InsertFill(void *v, void *pos, int n, const void *val);
void **fn_80146000(void *vec, int index);
}

template <class T> struct PtrVec : PtrVecBase<T> {
    PtrVec() {}
    ~PtrVec() {}
    T *begin() { return this->data; }
    T *end() { return this->data + this->count; }
    void push_back(const T &v) { PtrVec_InsertFill(this, end(), 1, &v); }
    T &at(int i) { return *(T *)fn_80146000(this, i); }
};

/* 0x230-byte text sprite (ctor TexMgr_Init). */
struct TextSprite {
    char pad000[0x18];
    int visible;
    char pad01C[4];
    unsigned int color;
    char pad024[0x22C - 0x24];
    float spacing;
    TextSprite();
};

/* 0x230-byte text manager (ctor fn_80149214, dtor dtor_800869D0). */
struct TextManager {
    char pad000[0x18];
    int visible;
    char pad01C[0x22C - 0x1C];
    float spacing;
    TextManager();
    ~TextManager();
};

/* 0x20-byte 3D model (ctor fn_8013D800). */
struct Model {
    virtual ~Model();
    virtual void Draw();
    char pad04[0x1C];
    Model(const void *res, int flag);
};

/* 0x64-byte item model group (ctor fn_8021ABFC). */
struct ItemModel {
    virtual ~ItemModel();
    char pad04[0x60];
    ItemModel(int id, int a, int b, int c);
};

struct KartPose {
    float pos[3];
    float rot[3];
    float scale;
};

struct ItemPose {
    float x, y;
    float rot[3];
    float scale;
};

/* One unlockable item of the coin mileage table. */
struct MilageItem {
    int coins;
    int type;
    int id;
};

struct Int5 {
    int v[5];
};

struct ItemDisplay {
    int x0;
    int state;
    int mode;
};

extern "C" {
extern InputState *g_pInputState;
extern int g_gameMode;
extern int g_cupId;
extern int g_characterId;
extern char g_playerData[];
extern void *lbl_806D1A60;
extern const float lbl_803C6A18[3];
extern const float lbl_803C6A24[];
extern const Int5 lbl_803C6B70;
extern const char lbl_803C6B84[0x40];
extern const int lbl_803C6BC4[4];
extern const float lbl_803C6BD4[3][4];
extern const char lbl_803C6C2C[];
extern const char lbl_803C6C58[];
extern const char lbl_803C6C70[];
extern const char lbl_803C6CBC[];
extern const char lbl_803C6CD0[];
extern const float lbl_806DB190;
extern const float lbl_806DB194;
extern const float lbl_806DB198;
extern const float lbl_806DB19C;
extern const float lbl_806DB1A0;
extern const float lbl_806DB1A4;
extern const float lbl_806DB1A8;
extern const float lbl_806DB1AC;
extern const float lbl_806DB1B0;
extern const float lbl_806DB1B4;
extern const float lbl_806DB1B8;
extern const float lbl_806DB1BC;
extern const float lbl_806DB1C0;
extern const float lbl_806DB1C4;
extern const float lbl_806DB1C8;
extern const float lbl_806DB1CC;
extern const float lbl_806DB1D0;
extern const float lbl_806DB1D4;
extern const float lbl_806DB1D8;
extern const float lbl_806DB1DC;
extern const float lbl_806DB1E0;
extern const float lbl_806DB1E4;
extern const float lbl_806DB1E8;
extern const float lbl_806DB1EC;
extern const float lbl_806DB1F0;
extern const float lbl_806DB1F4;
extern const float lbl_806DB1F8;
extern const float lbl_806DB1FC;
extern const float lbl_806DB200;
extern const float lbl_806DB204;
extern const float lbl_806DB208;
extern const float lbl_806DB20C;
extern const char lbl_806DB210[4];
extern const float lbl_806DB214;
extern const float lbl_806DB218;
extern const float lbl_806DB21C;
extern const char lbl_806DB220[4];
extern const float lbl_806DB224;
extern const float lbl_806DB228;
extern const float lbl_806DB22C;
extern const float lbl_806DB230;
extern const float lbl_806DB234;
extern const float lbl_806DB238;
extern const float lbl_806DB23C;
extern const float lbl_806DB240;
extern const float lbl_806DB244;
extern const float lbl_806DB248;
extern const float lbl_806DB24C;
extern const float lbl_806DB250;
extern const float lbl_806DB254;
extern const float lbl_806DB258;
extern const float lbl_806DB25C;
extern const float lbl_806DB260;
extern const float lbl_806DB264;
extern const float lbl_806DB270;
extern const float lbl_806DB274;
extern const float lbl_806DB278;
extern const float lbl_806DB27C;
extern const float lbl_806DB280;
extern const float lbl_806DB284;
extern const float lbl_806DB288;
extern const float lbl_806DB28C;
extern const float lbl_806DB290;
extern const float lbl_806DB294;
extern const float lbl_806DB298;
extern const float lbl_806DB29C;
extern const char lbl_806DB2A0[8];
extern const float lbl_806DB2A8;
extern const float lbl_806DB2AC;
extern const float lbl_806DB2B0;
extern const float lbl_806DB2B4;
extern const float lbl_806DB2B8;
extern const float lbl_806DB2BC;
extern const float lbl_806DB2C0;
extern const float lbl_806DB2C4;
extern const float lbl_806DB2C8;
extern const float lbl_806DB2CC;
extern const float lbl_806DB2D0;
extern const float lbl_806DB2D4;
extern const float lbl_806DB2D8;
extern const float lbl_806DB2DC;
extern const float lbl_806DB2E0;
extern const float lbl_806DB2E4;
extern const float lbl_806DB2E8;
extern const float lbl_806DB2EC;
extern const float lbl_806DB2F0;
extern const float lbl_806DB2F4;
extern const float lbl_806DB2F8;
extern const float lbl_806DB2FC;
extern const float lbl_806DB300;
extern const float lbl_806DB304;
extern const float lbl_806DB308;
extern const float lbl_806DB30C;
extern const float lbl_806DB310;
extern const float lbl_806DB314;
extern const float lbl_806DB318;
extern const float lbl_806DB31C;
int isJapanese(void);
int rand(void);
double cos(double x);
int sprintf(char *buf, const char *fmt, ...);
char *strcpy(char *dst, const char *src);
void DebugPrintf(const char *fmt, ...);
void fn_8011F994(int a);
void fn_8011FAB8(void);
void fn_8011FAFC(ResCtrl *r, int layer);
void fn_80121E10(ResCtrl *r);
KartPose *fn_8013BE98(void);
void fn_8013BEC8(int id);
const char *fn_8013C26C(int id, int lang);
void fn_8013D4B0(Model *m, float a);
void fn_8013D59C(Model *m, float x, float y, float z);
void fn_8013D608(Model *m, float x, float y, float z);
void fn_8013D634(Model *m, float x, float y, float z);
void fn_8013D660(Model *m, float x, float y);
void fn_8013D738(Model *m, float a, float b);
void fn_8013DAC8(Model *m, int layer);
void fn_8013DBF8(void);
void fn_801699D8(int a, int b);
void fn_80169C44(void);
void fn_80192688(int id, int a);
unsigned char fn_8019FE78(Sprite *s);
void fn_8019FF8C(Sprite *s, int key, float *out);
void fn_801A0004(Sprite *s);
void fn_801A0500(Sprite *s);
void fn_801A1280(void);
void Sprite_AdvanceAnim(Sprite *s, float step);
void Sprite_SetupAnim(Sprite *s, int a, int b, int c);
void Sprite_SetAnimTime(Sprite *s, float t);
void *fn_801F8E58(void);
void fn_801F8A34(void *mgr, void *t, int layer);
void fn_801F8E90(void *t);
void fn_801F8FCC(void *t, int mode);
void fn_801F93D0(void *t, float sx, float sy);
void fn_801F93EC(void *t, float x, float y);
void TexMgr_SetTexture(void *t, const char *s, ...);
void TexMgr_Apply(void *t);
const char *GetTextureByIdAndLang(int id, int lang);
ItemDisplay *ItemDisplay_GetOrCreate(void);
void ItemDisplay_Start(ItemDisplay *d, int id);
void ItemDisplay_Stop(ItemDisplay *d);
void ItemDisplay_Destroy(void);
void fn_8020F38C(int a);
void fn_8020F3F0(void);
int fn_80209338(int chara);
int fn_802161CC(void);
int fn_802161D4(void);
int fn_802161DC(void);
int fn_802161EC(void);
int fn_802161F4(void);
int fn_802161FC(void);
int fn_8021620C(void);
void fn_8021651C(void *pd);
short fn_80216908(int a);
const char *fn_8021691C(int id);
int fn_80216960(int id);
int fn_80216974(int id);
int fn_80216988(int coins);
MilageItem *fn_802169F4(int index);
void fn_8021A0B0(void *fx);
void fn_8021A430(ItemModel *m, float a);
void fn_8021A4B8(ItemModel *m, float r, float g, float b, float a);
void fn_8021A578(ItemModel *m, float x, float y, float z);
void fn_8021A660(ItemModel *m, float x, float y, float z);
void fn_8021A7BC(ItemModel *m, float x, float y);
int fn_8023D710(int id);
const char *fn_8023D938(int id, int idx);
const char *fn_8023DAA8(int id);
const void *ItemRes_LookupByKey_Thunk(int id);
int Item_GetDescriptorField8(int id);
int Item_GetDescriptorFieldC(int id);
short Item_GetDescriptorField0(int id, int a);
void SoundMgr_Play(int id);
void SetSyncTarget(int id);
unsigned char IsSyncReached(void);
void SetRumbleMode(int a, int b, int c);
void RumbleUpdate(void);
void InitRumbleController(int a);
unsigned char IsCardValid(void);
void AddCoinsFromExtraStage(void);
void CalcEarnedCoins(void);
int GetEarnedCoins(void);
int GetCoinCount(void);
int GetCoinMilage(void *pd);
void AddCoinMilage(void *pd, int coins);
}

static inline const ItemPose *ItemPoses() {
    return (const ItemPose *)(lbl_803C6A24 + 5);
}

static inline InputState *GetInput() {
    return g_pInputState == 0 ? (InputState *)0 : g_pInputState;
}

static inline void SetInput(unsigned char en) {
    InputState *in = GetInput();
    in->enabled = en;
    in->held = 0;
    in->edge = 0;
}

static inline unsigned int PackColor(int r, int g, int b, int a) {
    return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
}

struct FadeTrack {
    unsigned char active;
    float from;
    float to;
    float speed;
    float t;
    float value;
    FadeTrack() : speed(lbl_806DB190), t(lbl_806DB190) {}
    void Set(float f, float e, float s) {
        from = f;
        to = e;
        speed = s;
        t = lbl_806DB190;
        value = f;
        active = 1;
    }
    void Step() {
        if (active == 1) {
            value = from * (lbl_806DB194 - t) + to * t;
            t += speed;
            if (t > lbl_806DB194) {
                t = lbl_806DB194;
            }
        }
    }
};

/* nsMenuUtil::clMenuNode */
struct FadeObj {
    virtual ~FadeObj() { delete sprite; }
    virtual void Update();
    virtual void Draw();
    Sprite *sprite;
    int delay;
    FadeTrack tracks[5];
    unsigned char shown;
    unsigned char flush;
    FadeObj() : sprite(0), delay(0) {
        shown = 0;
        flush = 0;
        tracks[0].active = 0;
        tracks[1].active = 0;
        tracks[2].active = 0;
        tracks[3].active = 0;
        tracks[4].active = 0;
    }
    void Tick() {
        if (delay > 0) {
            delay--;
        } else {
            if (delay <= 0) {
                shown = 1;
            }
            for (int i = 0; i < 5; i++) {
                tracks[i].Step();
            }
            Update();
            if (sprite != 0) {
                if (tracks[0].active == 1) {
                    sprite->alpha = tracks[0].value;
                }
                if (tracks[1].active == 1) {
                    sprite->sx = tracks[1].value;
                }
                if (tracks[2].active == 1) {
                    sprite->sy = tracks[2].value;
                }
                if (tracks[3].active == 1) {
                    sprite->x = tracks[3].value;
                }
                if (tracks[4].active == 1) {
                    sprite->y = tracks[4].value;
                }
                Sprite_AdvanceAnim(sprite, lbl_806DB280);
            }
        }
    }
    void Render() {
        if (shown) {
            if (sprite != 0) {
                fn_801A0004(sprite);
            }
            Draw();
            if (flush == 1) {
                fn_8011FAB8();
            }
        }
    }
};

/* nsMenuUtil::clFilterNode: a full screen colour fill (vtable lbl_8049B1AC). */
struct FilterNode : FadeObj {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    int layer;
    FilterNode() {
        r = 0;
        g = 0;
        b = 0;
        layer = 7;
    }
    ~FilterNode();
    void Draw();
};

/* clGetCoinLine (0x4E8): one line of the coin breakdown. */
struct clGetCoinLine : FadeObj {
    int value;
    int add;
    Model *model;
    float rot;
    Own<Sprite> spr;
    ResCtrl digits[3];
    ResCtrl glow[3];
    TextSprite text;
    int timer;
    int flashTimer;
    unsigned char flash;
    clGetCoinLine(const char *label, int n, float y, Model *m);
    ~clGetCoinLine();
    void Layout(float y);
    void Update() {
        rot += lbl_806DB2DC;
        if (rot >= lbl_806DB270) {
            rot -= lbl_806DB270;
        }
        Sprite_AdvanceAnim(spr.p, lbl_806DB280);
        if (timer < 80) {
            timer++;
        }
        if (timer == 70) {
            SoundMgr_Play(0x1B);
        }
        if (flash) {
            flashTimer++;
        }
    }
    void Draw() {
        float x = tracks[3].value;
        float y = tracks[4].value;
        spr.p->SetPos(x, y);
        fn_801A0004(spr.p);
        fn_8011F994(1);
        if (model != 0) {
            fn_8013D660(model, x - lbl_806DB2E0, lbl_806DB2E4 + y);
            fn_8013D634(model, lbl_806DB190, lbl_806DB190, lbl_806DB248);
            fn_8013D59C(model, lbl_806DB190, lbl_806DB1D8 * rot, lbl_806DB190);
            fn_8013D608(model, lbl_806DB2E8, lbl_806DB2E8, lbl_806DB2E8);
            model->Draw();
        }
        Layout(y);
        for (int i = 0; i < 3; i++) {
            fn_8011FAFC(&digits[i], 1);
        }
        if (flash) {
            for (int i = 0; i < 3; i++) {
                fn_8011FAFC(&glow[i], 1);
            }
        }
        void *mgr = fn_801F8E58();
        fn_801F93EC(&text, x - lbl_806DB2EC, y - lbl_806DB2F0);
        fn_801F8A34(mgr, &text, 1);
    }
    void Bump(int n) {
        add = n;
        flash = 1;
        flashTimer = 0;
    }
};

/* clGetSumLine (0x548): the total line. */
struct clGetSumLine : clGetCoinLine {
    unsigned char perfect;
    ResCtrl label;
    Own<Sprite> bar;
    clGetSumLine(int n, unsigned char p, float y);
    void Draw() {
        float x = tracks[3].value;
        float y = tracks[4].value;
        clGetCoinLine::Draw();
        if (perfect) {
            bar.p->SetPos(x - lbl_806DB288, y - lbl_806DB2F4);
        } else {
            bar.p->SetPos(x - lbl_806DB288, y - lbl_806DB2F8);
        }
        fn_801A0004(bar.p);
        if (isJapanese() == 0) {
            label.Show(lbl_806DB2FC + x, y - lbl_806DB194, lbl_806DB194);
        } else {
            label.Show(lbl_806DB300 + x, y - lbl_806DB194, lbl_806DB194);
        }
        fn_8011FAFC(&label, 1);
    }
};

/* clCoinPerfect (0x3C0): the "perfect" bonus label. */
struct clCoinPerfect : FadeObj {
    TextSprite text;
    ResCtrl r[3];
    clCoinPerfect(int n) {
        tracks[0].Set(lbl_806DB190, lbl_806DB194, lbl_806DB1F8);
        r[0].resId = (short)(n % 10 + 0x14BA);
        r[0].Show(lbl_806DB1FC, lbl_806DB200, lbl_806DB194);
        r[0].scaleX = lbl_806DB204;
        r[0].scaleY = lbl_806DB204;
        r[2].resId = 0x14C9;
        r[2].Show(lbl_806DB208, lbl_806DB200, lbl_806DB194);
        r[2].scaleX = lbl_806DB20C;
        r[2].scaleY = lbl_806DB20C;
        TexMgr_SetTexture(&text, lbl_806DB210, GetTextureByIdAndLang(0x72, -1));
        text.visible = 1;
        fn_801F93D0(&text, lbl_806DB214, lbl_806DB214);
        fn_801F93EC(&text, lbl_806DB218, lbl_806DB200);
        fn_801F8FCC(&text, 2);
        fn_801F8E90(&text);
        SoundMgr_Play(0x1B);
    }
    void Update() {
        int a = (int)(lbl_806DB24C * tracks[0].value);
        text.color = PackColor(0xE0, 0x20, 0x20, a);
        unsigned int c = PackColor(0xFF, 0x55, 0x55, a);
        r[0].SetColor(c);
        r[1].SetColor(c);
        r[2].SetColor(c);
    }
    void Draw() {
        fn_801F8A34(fn_801F8E58(), &text, 1);
        for (int i = 0; i < 3; i++) {
            fn_8011FAFC(&r[i], 1);
        }
    }
};

/* clGetCoinSum (0x6E8): the coin mileage total. */
struct clGetCoinSum : FadeObj {
    int value;
    Own<Sprite> spr;
    ResCtrl r[2];
    ResCtrl digits[5];
    TextSprite text;
    ResCtrl glow[5];
    unsigned char flash;
    unsigned char done;
    int timer;
    clGetCoinSum();
    void Layout();
    void Update() {
        float x = tracks[3].value;
        float y = tracks[4].value;
        if (isJapanese() == 0) {
            r[0].Show(x - lbl_806DB304, y - lbl_806DB308, lbl_806DB194);
        } else {
            fn_801F93EC(&text, x - lbl_806DB30C, y - lbl_806DB308);
        }
        r[1].Show(lbl_806DB310 + x, lbl_806DB314 + y, lbl_806DB194);
        Layout();
        spr.p->SetPos(tracks[3].value, tracks[4].value);
        Sprite_AdvanceAnim(spr.p, lbl_806DB280);
        if (timer < 240) {
            timer++;
        }
    }
    void Draw() {
        fn_801A0004(spr.p);
        if (isJapanese() == 0) {
            fn_8011FAFC(&r[0], 1);
        } else {
            fn_801F8A34(fn_801F8E58(), &text, 1);
        }
        fn_8011FAFC(&r[1], 1);
        for (int i = 0; i < 5; i++) {
            fn_8011FAFC(&digits[i], 1);
            fn_8011FAFC(&glow[i], 1);
        }
    }
    void Flash() {
        flash = 1;
        done = 0;
        timer = 0;
    }
};

inline void clGetCoinSum::Layout() {
    float px = tracks[3].value;
    float py = tracks[4].value;
    int n = 1;
    Int5 d = lbl_803C6B70;
    d.v[0] = value % 10;
    d.v[1] = value / 10 % 10;
    d.v[2] = value / 100 % 10;
    d.v[3] = value / 1000 % 10;
    d.v[4] = value / 10000 % 10;
    if (d.v[4] != 0) {
        n = 5;
    } else if (d.v[3] != 0) {
        n = 4;
    } else if (d.v[2] != 0) {
        n = 3;
    } else if (d.v[1] != 0) {
        n = 2;
    }
    float x = lbl_806DB200 + px;
    float y = lbl_806DB314 + py;
    for (int i = 0; i < 5; i++) {
        fn_80121E10(&digits[i]);
        digits[i].Show(x, y, lbl_806DB194);
        digits[i].scaleX = lbl_806DB318;
        digits[i].scaleY = lbl_806DB318;
        digits[i].resId = i >= n ? 0x1ECD : d.v[i] + 0x14BA;
        x -= lbl_806DB31C;
    }
    if (flash == 1) {
        int a = 0;
        if (timer <= 20) {
            a = 0;
        } else if (timer <= 40) {
            a = (int)(lbl_806DB260 * ((timer - 20) / lbl_806DB288));
        } else if (timer <= 60) {
            a = (int)(lbl_806DB260 * (lbl_806DB194 - (timer - 40) / lbl_806DB288));
        }
        if (a > 0xFF) {
            a = 0xFF;
        }
        for (int i = 0; i < 5; i++) {
            glow[i] = digits[i];
            glow[i].mode = 3;
            glow[i].SetColor(PackColor(0xFF, 0xFF, 0xFF, a));
        }
        if (timer >= 110) {
            timer = 0;
            flash = 0;
            done = 1;
        }
    }
}

/* Window that shows one unlocked item (0x1190). */
struct ItemWnd {
    int coins;
    int state;
    int timer;
    int sub;
    MilageItem *entry;
    int itemId;
    Model *kart;
    ItemModel *item;
    Sprite *spr[3];
    TextManager texts[7];
    ResCtrl label;
    int labelLayer;
    ResCtrl digits[4];
    ResCtrl fade;
    ItemWnd()
        : state(0), timer(0), sub(0), entry(0), itemId(0), kart(0), item(0), labelLayer(5) {
        spr[0] = 0;
        spr[1] = 0;
        spr[2] = 0;
        spr[0] = new Sprite(0x192, 1, 0);
        spr[0]->SetPos(lbl_806DB1E8, lbl_806DB290);
        spr[0]->layer = 4;
        spr[0]->alpha = lbl_806DB190;
        label.resId = 0x1ECD;
        fade.mode = 2;
        fade.width = lbl_806DB224;
        fade.height = lbl_806DB274;
        fade.Show(lbl_806DB1E8, lbl_806DB2AC, lbl_806DB194);
        fade.SetColor(0);
        for (int i = 0; i < 3; i++) {
            texts[i].spacing = lbl_806DB2A8;
            texts[i].visible = 1;
            fn_801F8FCC(&texts[i], 1);
        }
        if (isJapanese() == 0) {
            fn_801F93EC(&texts[0], lbl_806DB1E8, lbl_806DB2C8);
            fn_801F93EC(&texts[1], lbl_806DB1E8, lbl_806DB2CC);
            fn_801F93EC(&texts[2], lbl_806DB1E8, lbl_806DB2D0);
        } else {
            fn_801F93EC(&texts[0], lbl_806DB2D4, lbl_806DB2C8);
            fn_801F93EC(&texts[1], lbl_806DB2D4, lbl_806DB2CC);
            fn_801F93EC(&texts[2], lbl_806DB2D4, lbl_806DB2D0);
        }
        texts[3].spacing = lbl_806DB2D8;
        texts[4].spacing = lbl_806DB2D8;
        texts[5].spacing = lbl_806DB2D8;
        texts[6].spacing = lbl_806DB2D8;
    }
    ~ItemWnd() {
        for (int i = 0; i < 3; i++) {
            if (spr[i] != 0) {
                delete spr[i];
                spr[i] = 0;
            }
        }
        if (kart) {
            delete kart;
            kart = 0;
        }
        if (item) {
            delete item;
            item = 0;
        }
    }
    void Setup(int n, MilageItem *e);
    void Update();
    void Open();
    void ShowKart();
    void ShowItem();
    void ShowTicket();
    void ShowOther();
    void SetTextAlpha(unsigned int c) {
        digits[0].SetColor(c);
        digits[1].SetColor(c);
        digits[2].SetColor(c);
        digits[3].SetColor(c);
    }
    void Draw() {
        for (int i = 0; i < 3; i++) {
            if (spr[i] != 0) {
                fn_801A0004(spr[i]);
            }
        }
        void *mgr = fn_801F8E58();
        for (int i = 0; i < 7; i++) {
            fn_801F8A34(mgr, &texts[i], 5);
        }
        for (int i = 0; i < 4; i++) {
            fn_8011FAFC(&digits[i], 5);
        }
        fn_8011FAFC(&label, labelLayer);
        fn_8011FAFC(&fade, 3);
    }
};

/* "N more coins to the next item" window (0x1CC). */
struct NextWnd {
    Sprite *spr[2];
    ResCtrl back;
    ResCtrl label;
    ResCtrl digits[3];
    int value;
    int state;
    int timer;
    NextWnd() : value(0), state(0), timer(0) {
        spr[0] = 0;
        spr[1] = 0;
        spr[0] = new Sprite(0x12, 1, 0);
        spr[1] = new Sprite(0x149, 1, 0);
        spr[0]->alpha = lbl_806DB190;
        spr[1]->alpha = lbl_806DB190;
        spr[0]->layer = 4;
        spr[1]->layer = 5;
        spr[0]->SetPos(lbl_806DB1E8, lbl_806DB290);
        spr[1]->SetPos(lbl_806DB1E8, lbl_806DB2AC);
        spr[1]->SetAnimParam(0x1931, 0x1ECD);
        spr[1]->SetAnimParam(0x1932, 0x1ECD);
        back.mode = 2;
        back.width = lbl_806DB224;
        back.height = lbl_806DB274;
        back.Show(lbl_806DB1E8, lbl_806DB2AC, lbl_806DB194);
        back.SetColor(0);
        label.Show(lbl_806DB1E8, lbl_806DB290, lbl_806DB194);
        label.resId = 0x1E88;
        label.SetColor(0xFFFFFF00);
    }
    ~NextWnd() {
        for (int i = 0; i < 2; i++) {
            if (spr[i] != 0) {
                delete spr[i];
                spr[i] = 0;
            }
        }
    }
    void Start(int n);
    void Update();
    void Count();
    void SetDigitColor(unsigned int c) {
        digits[0].SetColor(c);
        digits[1].SetColor(c);
        digits[2].SetColor(c);
    }
    void Draw() {
        if (state != 0) {
            fn_8011FAFC(&back, 3);
            fn_8011FAFC(&label, 4);
            for (int i = 0; i < 3; i++) {
                fn_8011FAFC(&digits[i], 5);
            }
            for (int i = 0; i < 2; i++) {
                if (spr[i] != 0) {
                    fn_801A0004(spr[i]);
                }
            }
        }
    }
};

struct Coin {
    float x;
    float y;
    float z;
    float vy;
    float vx;
    float rot;
    float vrot;
    unsigned char bounced;
};

struct SceneBase {
    virtual ~SceneBase() {}
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    unsigned char done;
    SceneBase() : done(false) {}
};

struct clCSSceneCoinMilage : SceneBase {
    Coin coins[30];
    int numCoins;
    Model *model;
    int x3d0;
    int milage;
    int earned;
    int bonus1;
    int bonus2;
    int x3e4;
    int perfectCoins;
    unsigned char hasPerfect;
    unsigned char hasBonus1;
    unsigned char hasBonus2;
    int counter;
    int itemIndex;
    int state;
    int sub;
    int timer;
    int wait;
    int tick;
    clGetCoinSum *sum;
    ItemWnd *wnd;
    NextWnd *next;
    clGetCoinLine *lines[4];
    clCoinPerfect *perfect;
    PtrVec<FadeObj *> nodes;
    clCSSceneCoinMilage();
    ~clCSSceneCoinMilage();
    void Destroy();
    void Update();
    void Draw();
    void StateNext();
    void StateItems();
    void StateSum();
    void StateLines();
    void StateCoins();
    int Total() {
        int n = earned;
        if (hasBonus1 == 1) {
            n += bonus1;
        }
        if (hasBonus2 == 1) {
            n += bonus2;
        }
        if (hasPerfect == 1) {
            n += perfectCoins;
        }
        return n;
    }
};

#pragma auto_inline off
void clCSSceneCoinMilage::StateNext() {
    if (timer == 1) {
        int i = fn_80216988(milage);
        if (i >= 0) {
            unsigned char found = 0;
            MilageItem *e;
            for (;;) {
                e = fn_802169F4(i);
                if (e == 0) {
                    break;
                }
                if (e->type != 1) {
                    found = 1;
                    break;
                }
                if (fn_80209338(g_characterId) > 0) {
                    found = 1;
                    break;
                }
                i++;
            }
            if (found == 1) {
                DebugPrintf(lbl_803C6C2C, e->coins - milage, e->coins, milage);
                next->Start(e->coins - milage);
            }
        }
    }
    if (next->state == 0) {
        int s = 7;
        timer = 0;
        wait = 0;
        if (g_gameMode == 2) {
            s = 6;
        }
        state = s;
    }
}
#pragma auto_inline reset

void NextWnd::Start(int n) {
    if (n > 0) {
        value = n;
        timer = 0;
        state = 1;
        for (int i = 0; i < 3; i++) {
            fn_80121E10(&digits[i]);
            digits[i].SetColor(0xFFFFFF00);
        }
        digits[0].resId = value % 10 + 0x1931;
        digits[1].resId = value / 10 % 10 + 0x1931;
        digits[2].resId = value / 100 % 10 + 0x1931;
        if (value < 100) {
            if (isJapanese() == 0) {
                digits[0].Show(lbl_806DB19C, lbl_806DB1A0, lbl_806DB194);
                digits[1].Show(lbl_806DB1A4, lbl_806DB1A0, lbl_806DB194);
            } else {
                digits[0].Show(lbl_806DB1A8, lbl_806DB1AC, lbl_806DB194);
                digits[1].Show(lbl_806DB1B0, lbl_806DB1AC, lbl_806DB194);
            }
            fn_80121E10(&digits[2]);
            digits[2].resId = 0x1ECD;
        } else if (isJapanese() == 0) {
            digits[0].Show(lbl_806DB1B4, lbl_806DB1A0, lbl_806DB194);
            digits[1].Show(lbl_806DB1B8, lbl_806DB1A0, lbl_806DB194);
            digits[2].Show(lbl_806DB1BC, lbl_806DB1A0, lbl_806DB194);
        } else {
            digits[0].Show(lbl_806DB1C0, lbl_806DB1AC, lbl_806DB194);
            digits[1].Show(lbl_806DB1C4, lbl_806DB1AC, lbl_806DB194);
            digits[2].Show(lbl_806DB1C8, lbl_806DB1AC, lbl_806DB194);
        }
    }
}

#pragma auto_inline off
void clCSSceneCoinMilage::StateItems() {
    if (wnd->state == 0) {
        unsigned char end = 0;
        if (itemIndex != fn_80216988(milage)) {
            MilageItem *e = fn_802169F4(itemIndex);
            if (e != 0) {
                wnd->Setup(e->coins, e);
                itemIndex++;
                SoundMgr_Play(0x22);
            } else {
                DebugPrintf(lbl_803C6C58);
                end = 1;
            }
        } else {
            DebugPrintf(lbl_803C6C70);
            end = 1;
        }
        if (end == 1) {
            timer = 0;
            wait = 0;
            if (fn_802169F4(fn_80216988(milage)) == 0) {
                int s = 7;
                if (g_gameMode == 2) {
                    s = 6;
                }
                state = s;
            } else {
                state = 5;
            }
        }
    }
}
#pragma auto_inline reset

void ItemWnd::Setup(int n, MilageItem *e) {
    if (e != 0) {
        coins = n;
        entry = e;
        state = 1;
        timer = 0;
        sub = 0;
        if (e->type == 1) {
            itemId = fn_8021620C();
            if (itemId <= 0) {
                DebugPrintf(lbl_803C6C70 + 0x10, lbl_803C6C70 + 0x34, 950);
                state = 0;
                return;
            }
            KartPose *pose = fn_8013BE98();
            if (kart) {
                delete kart;
                kart = 0;
            }
            kart = new Model(ItemRes_LookupByKey_Thunk(itemId), 1);
            fn_8013D738(kart, lbl_806DB190, lbl_806DB194);
            fn_8013D660(kart, lbl_806DB1CC, lbl_806DB1D0);
            fn_8013D634(kart, lbl_806DB1D4 * pose->pos[0], lbl_806DB1D4 * pose->pos[1], lbl_806DB1D4 * pose->pos[2]);
            fn_8013D59C(kart, lbl_806DB1D8 * pose->rot[0], lbl_806DB1D8 * pose->rot[1], lbl_806DB1D8 * pose->rot[2]);
            float s = lbl_806DB1D4 * pose->scale;
            fn_8013D608(kart, s, s, s);
            TextSprite tmp;
            tmp.visible = 0;
            TexMgr_SetTexture(&tmp, fn_8023DAA8(itemId));
            TexMgr_Apply(&tmp);
            TexMgr_SetTexture(&tmp, fn_8023D938(itemId, 0));
            TexMgr_Apply(&tmp);
            TexMgr_SetTexture(&tmp, fn_8023D938(itemId, 1));
            TexMgr_Apply(&tmp);
            TexMgr_SetTexture(&tmp, fn_8023D938(itemId, 2));
            TexMgr_Apply(&tmp);
        } else if (e->type == 3 || e->type == 4) {
            int k = fn_80216960(entry->id);
            if (item) {
                delete item;
                item = 0;
            }
            item = new ItemModel(k, 2, 0, 1);
            fn_8021A7BC(item, ItemPoses()[k].x, ItemPoses()[k].y);
            fn_8021A578(item, lbl_806DB1D8 * ItemPoses()[k].rot[0], lbl_806DB1D8 * ItemPoses()[k].rot[1],
                        lbl_806DB1D8 * ItemPoses()[k].rot[2]);
            fn_8021A660(item, ItemPoses()[k].scale, ItemPoses()[k].scale, ItemPoses()[k].scale);
            fn_8021A430(item, lbl_806DB190);
        }
    }
}

#pragma auto_inline off
void clCSSceneCoinMilage::StateSum() {
    bool pressed = GetInput()->held == 1;
    switch (sub) {
    case 0:
        sum = new clGetCoinSum;
        nodes.push_back((FadeObj *&)sum);
        timer = 0;
        sub++;
        break;
    case 1:
        if (timer >= 120 || pressed == 1) {
            sub++;
            timer = 0;
            wait = 11;
            tick = 0;
        }
        break;
    case 2:
        if (pressed) {
            timer = 0;
            counter = milage;
            sum->Flash();
            sub++;
        } else {
            if (++tick % 50 == 0) {
                if (wait > 4) {
                    wait--;
                }
            }
            if (timer >= wait) {
                timer = 0;
                SoundMgr_Play(0x19);
                if (++counter >= milage) {
                    counter = milage;
                    sum->Flash();
                    sub++;
                }
            }
        }
        break;
    case 3:
        if (sum->done == 1) {
            timer = 0;
            sub = 0;
            wait = 0;
            state = 4;
        }
        break;
    }
    sum->value = counter;
}
#pragma auto_inline reset

clGetCoinSum::clGetCoinSum() : value(0), spr(new Sprite(0x13F, 1, 0)) {
    flash = 0;
    done = 0;
    timer = 0;
    spr.p->layer = 1;
    tracks[4].Set(lbl_806DB1DC, lbl_806DB1DC, lbl_806DB1E0);
    tracks[3].Set(lbl_806DB1E4, lbl_806DB1E8, lbl_806DB1EC);
    r[0].resId = 0x16D6;
    if (isJapanese() == 0) {
        r[1].resId = 0x16D8;
    } else {
        r[1].resId = 0x1924;
        r[1].scaleX = lbl_806DB1F0;
        r[1].scaleY = lbl_806DB1F0;
    }
    TexMgr_SetTexture(&text, lbl_803C6CBC);
    text.visible = 1;
    text.spacing = lbl_806DB1F4;
    fn_801F93D0(&text, lbl_806DB1F0, lbl_806DB1F0);
    glow[0].resId = 0x1ECD;
    glow[1].resId = 0x1ECD;
    glow[2].resId = 0x1ECD;
    glow[3].resId = 0x1ECD;
    glow[4].resId = 0x1ECD;
}

#pragma auto_inline off
void clCSSceneCoinMilage::StateLines() {
    bool pressed = GetInput()->held == 1;
    switch (sub) {
    case 0:
        if (timer == 10) {
            lines[0] = new clGetCoinLine(GetTextureByIdAndLang(0x6C, -1), earned, lbl_803C6A24[0], model);
            nodes.push_back((FadeObj *&)lines[0]);
        }
        if (timer >= 140) {
            timer = 0;
            sub = hasPerfect == 1 ? 1 : 2;
        }
        break;
    case 1:
        if (timer == 1) {
            perfect = new clCoinPerfect(perfectCoins);
            nodes.push_back((FadeObj *&)perfect);
            lines[0]->Bump(perfectCoins);
        }
        if (timer == 75) {
            perfect->tracks[0].Set(lbl_806DB194, lbl_806DB190, lbl_806DB1F8);
        }
        if (timer >= 100) {
            timer = 0;
            sub++;
        }
        break;
    case 2:
        if (timer == 1) {
            if (hasBonus1 == 0) {
                timer = 0;
                sub = hasBonus2 == 1 ? 3 : 4;
                break;
            }
            const char *tex = g_gameMode == 1 ? GetTextureByIdAndLang(0x70, -1) : GetTextureByIdAndLang(0x6E, -1);
            lines[1] = new clGetCoinLine(tex, bonus1, lbl_803C6A24[1], model);
            lines[1]->rot = ((clGetCoinLine *)nodes.at(1))->rot;
            nodes.push_back((FadeObj *&)lines[1]);
        }
        if (timer >= 140) {
            timer = 0;
            sub = hasBonus2 == 1 ? 3 : 4;
        }
        break;
    case 3:
        if (timer == 1) {
            const char *tex = g_gameMode == 1 ? GetTextureByIdAndLang(0x71, -1) : GetTextureByIdAndLang(0x6F, -1);
            lines[2] = new clGetCoinLine(tex, bonus2, lbl_803C6A24[2], model);
            lines[2]->rot = ((clGetCoinLine *)nodes.at(1))->rot;
            nodes.push_back((FadeObj *&)lines[2]);
        }
        if (timer >= 140) {
            timer = 0;
            sub++;
        }
        break;
    case 4:
        if (timer == 1) {
            int n = Total();
            lines[3] = new clGetSumLine(n, hasPerfect, lbl_803C6A24[(hasBonus2 == 1 ? -1 : 0) + 4]);
            nodes.push_back((FadeObj *&)lines[3]);
        }
        if (timer >= 140) {
            timer = 0;
            sub++;
        }
        break;
    case 5:
        if (timer >= 60 || pressed == 1) {
            timer = 0;
            wait = 0;
            sub = 0;
            state = 3;
        }
        return;
    }
    if (GetInput()->held == 1) {
        if (lines[0] == 0) {
            lines[0] = new clGetCoinLine(GetTextureByIdAndLang(0x6C, -1), earned, lbl_803C6A24[0], model);
            nodes.push_back((FadeObj *&)lines[0]);
        }
        if (hasPerfect == 1) {
            if (perfect == 0) {
                lines[0]->Bump(perfectCoins);
            } else {
                perfect->tracks[0].Set(lbl_806DB190, lbl_806DB190, lbl_806DB194);
            }
        }
        if (hasBonus1 == 1 && lines[1] == 0) {
            const char *tex = g_gameMode == 1 ? GetTextureByIdAndLang(0x70, -1) : GetTextureByIdAndLang(0x6E, -1);
            lines[1] = new clGetCoinLine(tex, bonus1, lbl_803C6A24[1], model);
            lines[1]->rot = lines[0]->rot;
            nodes.push_back((FadeObj *&)lines[1]);
        }
        if (hasBonus2 == 1 && lines[2] == 0) {
            const char *tex = g_gameMode == 1 ? GetTextureByIdAndLang(0x71, -1) : GetTextureByIdAndLang(0x6F, -1);
            lines[2] = new clGetCoinLine(tex, bonus2, lbl_803C6A24[2], model);
            lines[2]->rot = lines[0]->rot;
            nodes.push_back((FadeObj *&)lines[2]);
        }
        if (lines[3] == 0) {
            int n = Total();
            lines[3] = new clGetSumLine(n, hasPerfect, lbl_803C6A24[(hasBonus2 == 1 ? -1 : 0) + 4]);
            nodes.push_back((FadeObj *&)lines[3]);
        }
        for (int i = 0; i < 4; i++) {
            clGetCoinLine *l = lines[i];
            if (l != 0) {
                l->tracks[3].Set(lbl_806DB21C, lbl_806DB21C, lbl_806DB1E0);
                l->timer = 80;
                l->value += l->add;
                l->add = 0;
                l->flash = 0;
            }
        }
        timer = 0;
        wait = 0;
        sub = 0;
        state = 3;
    }
}
#pragma auto_inline reset

clGetSumLine::clGetSumLine(int n, unsigned char p, float y)
    : clGetCoinLine(lbl_806DB220, n, y, 0), perfect(p), bar(new Sprite(0x140, 1, 0)) {
    bar.p->SetPos(lbl_806DB224, lbl_806DB228);
    bar.p->layer = 1;
    fn_80121E10(&label);
    label.resId = 0x16D7;
    if (isJapanese() == 0) {
        label.Show(lbl_806DB22C, lbl_806DB230, lbl_806DB194);
    } else {
        label.Show(lbl_806DB234, lbl_806DB238, lbl_806DB194);
    }
}

clGetCoinLine::~clGetCoinLine() {}

clGetCoinLine::clGetCoinLine(const char *label, int n, float y, Model *m)
    : value(n), add(0), model(m), rot(lbl_806DB190), spr(new Sprite(0x13E, 1, 0)) {
    timer = 0;
    flashTimer = 0;
    flash = 0;
    tracks[4].Set(y, y, lbl_806DB1E0);
    tracks[3].Set(lbl_806DB23C, lbl_806DB21C, lbl_806DB1EC);
    spr.p->SetPos(lbl_806DB23C, y);
    spr.p->layer = 1;
    TexMgr_SetTexture(&text, label);
    text.visible = 1;
    fn_801F93EC(&text, lbl_806DB240, lbl_806DB244 + y);
    text.spacing = lbl_806DB248;
    Layout(y);
}

void clGetCoinLine::Layout(float y) {
    int a = (int)(lbl_806DB24C * ((timer - 70) / lbl_806DB250));
    if (timer < 70) {
        a = 0;
    }
    for (int i = 0; i < 3; i++) {
        fn_80121E10(&digits[i]);
        digits[i].scaleX = lbl_806DB1F0;
        digits[i].scaleY = lbl_806DB1F0;
        digits[i].SetColor(PackColor(0xFF, 0xFF, 0xFF, a));
    }
    int h = value / 100 % 10;
    digits[2].resId = h != 0 ? (short)(h + 0x14BA) : 0x1ECD;
    digits[2].Show(lbl_806DB254, y - lbl_806DB194, lbl_806DB194);
    int t = value / 10 % 10;
    unsigned char blank = 0;
    if (t == 0 && h == 0) {
        blank = 1;
    }
    digits[1].resId = !blank ? (short)(t + 0x14BA) : 0x1ECD;
    digits[1].Show(lbl_806DB258, y - lbl_806DB194, lbl_806DB194);
    digits[0].resId = (short)(value % 10 + 0x14BA);
    digits[0].Show(lbl_806DB1FC, y - lbl_806DB194, lbl_806DB194);
    if (flash == 1) {
        if (flashTimer < 12) {
            a = 0;
        } else if (flashTimer <= 19) {
            float f = (flashTimer - 12) / lbl_806DB25C;
            int v = (int)(lbl_806DB260 * f);
            if (v > 0xFF) {
                v = 0xFF;
            }
            a = (unsigned char)v;
            float s = lbl_806DB20C * f + lbl_806DB1F0;
            digits[0].scaleX = s;
            digits[0].scaleY = s;
            digits[1].scaleX = s;
            digits[1].scaleY = s;
            digits[2].scaleX = s;
            digits[2].scaleY = s;
        } else if (flashTimer <= 23) {
            a = 0xFF;
            digits[0].scaleX = lbl_806DB264;
            digits[0].scaleY = lbl_806DB264;
            digits[1].scaleX = lbl_806DB264;
            digits[1].scaleY = lbl_806DB264;
            digits[2].scaleX = lbl_806DB264;
            digits[2].scaleY = lbl_806DB264;
        } else if (flashTimer <= 30) {
            float f = lbl_806DB194 - (flashTimer - 23) / lbl_806DB25C;
            int v = (int)(lbl_806DB260 * f);
            if (v > 0xFF) {
                v = 0xFF;
            }
            a = (unsigned char)v;
            float s = lbl_806DB1F8 * f + lbl_806DB1F0;
            digits[0].scaleX = s;
            digits[0].scaleY = s;
            digits[1].scaleX = s;
            digits[1].scaleY = s;
            digits[2].scaleX = s;
            digits[2].scaleY = s;
        }
        if (flashTimer == 19) {
            value += add;
            add = 0;
        }
        if (flashTimer >= 30) {
            flash = 0;
        }
        for (int i = 0; i < 3; i++) {
            glow[i] = digits[i];
            glow[i].mode = 3;
            glow[i].SetColor(PackColor(0xFF, 0xFF, 0xFF, a));
        }
    }
}

#pragma auto_inline off
void clCSSceneCoinMilage::StateCoins() {
    unsigned char end = 0;
    if (timer == 1) {
        SoundMgr_Play(0x72);
    }
    int landed = 0;
    for (int i = 0; i < numCoins; i++) {
        Coin *c = &coins[i];
        if (c->y >= lbl_806DB224) {
            landed++;
        } else {
            c->x += c->vx;
            c->y += c->vy;
            c->rot += c->vrot;
            c->vy += lbl_806DB1F0;
            if (c->rot > lbl_806DB270) {
                c->rot -= lbl_806DB270;
            }
            if (c->rot < lbl_806DB190) {
                c->rot += lbl_806DB270;
            }
            if (c->bounced == 0 && c->y >= lbl_806DB274) {
                c->bounced = 1;
                c->vy = lbl_806DB20C * -c->vy;
                c->vx = rand() % 2 ? lbl_806DB278 : lbl_806DB27C;
            }
        }
    }
    if (--wait < 0) {
        if (numCoins < 30) {
            numCoins++;
            wait = rand() % 2 + 2;
        } else {
            wait = 0;
            if (landed == 30) {
                end = 1;
            }
        }
    }
    if (GetInput()->held == 1) {
        end = 1;
    }
    if (end == 1) {
        fn_80192688(0x72, 1);
        timer = 0;
        sub = 0;
        wait = 0;
        state = 2;
        fn_8013D634(model, lbl_806DB190, lbl_806DB190, lbl_806DB190);
        fn_8013D59C(model, lbl_806DB190, lbl_806DB190, lbl_806DB190);
    }
}
#pragma auto_inline reset

void clCSSceneCoinMilage::Draw() {
    fn_8011FAB8();
    fn_801A1280();
    if (state == 4) {
        wnd->Draw();
    }
    if (state == 5) {
        next->Draw();
    }
    for (FadeObj **it = nodes.begin(); it != nodes.end(); it++) {
        (*it)->Render();
    }
    if (state == 1) {
        for (int i = 0; i < numCoins; i++) {
            fn_8013D634(model, lbl_806DB190, lbl_806DB190, coins[i].z);
            fn_8013D660(model, coins[i].x, coins[i].y);
            fn_8013D59C(model, lbl_806DB190, lbl_806DB1D8 * coins[i].rot, lbl_806DB190);
            model->Draw();
        }
    }
}

void clCSSceneCoinMilage::Update() {
    switch (state) {
    case 0:
        if (timer == 30) {
            ItemDisplay_Start(ItemDisplay_GetOrCreate(), 0x1ADB);
        }
        if (ItemDisplay_GetOrCreate()->state == 2) {
            timer = 0;
            state = 1;
        }
        break;
    case 1:
        StateCoins();
        break;
    case 2:
        StateLines();
        break;
    case 3:
        StateSum();
        break;
    case 4:
        StateItems();
        break;
    case 5:
        StateNext();
        break;
    case 6:
        SetSyncTarget(0x2F);
        if (IsSyncReached() == 1) {
            timer = 0;
            wait = 0;
            state = 7;
        }
        break;
    case 7:
        if (timer == 90) {
            nodes.at(0)->tracks[0].Set(lbl_806DB190, lbl_806DB194, lbl_806DB198);
        }
        if (timer >= 120) {
            timer = 0;
            wait = 0;
            state = 8;
            done = 1;
            ItemDisplay_Stop(ItemDisplay_GetOrCreate());
            fn_8021A0B0(lbl_806D1A60);
        }
        break;
    case 8:
        done = 1;
        break;
    }
    timer++;
    if (state == 4) {
        wnd->Update();
    }
    if (state == 5) {
        next->Update();
    }
    for (FadeObj **it = nodes.begin(); it != nodes.end(); it++) {
        (*it)->Tick();
    }
    if (GetInput()->held == 1) {
        SetRumbleMode(0, 1, 1);
    }
    RumbleUpdate();
}

void NextWnd::Update() {
    switch (state) {
    case 1: {
        int a = (int)(lbl_806DB284 * (timer / lbl_806DB250));
        back.SetColor((unsigned char)a);
        if (timer >= 10) {
            state = 2;
            timer = 0;
            Sprite_SetupAnim(spr[0], 0x12, 1, 0);
            spr[0]->alpha = lbl_806DB194;
        }
        break;
    }
    case 2:
        if (fn_8019FE78(spr[0]) == 0) {
            fn_801A0500(spr[0]);
            state = 3;
            timer = 0;
            Sprite_SetAnimTime(spr[1], lbl_806DB190);
            spr[1]->alpha = lbl_806DB190;
            label.SetColor(0xFFFFFFFF);
        }
        break;
    case 3:
        Count();
        break;
    case 4:
        if (fn_8019FE78(spr[0]) == 0) {
            timer = 0;
            state = 5;
            spr[0]->alpha = lbl_806DB190;
        }
        break;
    case 5: {
        int a = (int)(lbl_806DB284 * (lbl_806DB194 - timer / lbl_806DB250));
        back.SetColor((unsigned char)a);
        if (timer >= 10) {
            state = 0;
            timer = 0;
        }
        break;
    }
    }
    timer++;
    for (int i = 0; i < 2; i++) {
        if (spr[i] != 0) {
            Sprite_AdvanceAnim(spr[i], lbl_806DB280);
        }
    }
}

void NextWnd::Count() {
    InputState *in = GetInput();
    if (timer <= 10) {
        float f = timer / lbl_806DB250;
        spr[1]->alpha = f;
        SetDigitColor(PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f)));
    }
    if (timer > 10 && timer < 250 && in->held == 1) {
        timer = 250;
    }
    if (timer >= 250 && timer >= 260) {
        float f = lbl_806DB194 - timer / lbl_806DB250;
        spr[1]->alpha = f;
        SetDigitColor(PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f)));
    }
    if (timer >= 260) {
        state = 4;
        timer = 0;
        Sprite_SetupAnim(spr[0], 0x11, 1, 0);
        spr[1]->alpha = lbl_806DB190;
        label.SetColor(0xFFFFFF00);
        SetDigitColor(0xFFFFFF00);
    }
}

void ItemWnd::Update() {
    switch (state) {
    case 0:
        return;
    case 1:
        Open();
        break;
    case 2:
        switch (entry->type) {
        case 1:
            ShowItem();
            break;
        case 0:
            ShowTicket();
            break;
        case 3:
        case 4:
            ShowOther();
            break;
        case 2:
            ShowKart();
            break;
        }
        break;
    case 3:
        switch (sub) {
        case 0:
            sub++;
            timer = 0;
            if (spr[2] != 0) {
                delete spr[2];
                spr[2] = 0;
            }
            break;
        case 1: {
            float f = lbl_806DB194 - timer / lbl_806DB288;
            float a = lbl_806DB284 * (f * f);
            fade.SetColor((unsigned char)(int)a);
            spr[0]->alpha = f;
            float c = lbl_806DB194 - (float)cos(lbl_806DB1D8 * (lbl_806DB28C * f));
            c = c * c;
            spr[0]->sx = c;
            spr[0]->sy = c;
            if (timer >= 20) {
                sub = 0;
                timer = 0;
                state = 0;
            }
            break;
        }
        }
        break;
    }
    timer++;
    for (int i = 0; i < 3; i++) {
        if (spr[i] != 0) {
            Sprite_AdvanceAnim(spr[i], lbl_806DB280);
        }
    }
}

void ItemWnd::ShowKart() {
    InputState *in = GetInput();
    switch (sub) {
    case 0:
        fn_80121E10(&label);
        label.resId = 0x1D5D;
        label.SetColor(0xFFFFFF00);
        label.Show(lbl_806DB1E8, lbl_806DB290, lbl_806DB194);
        labelLayer = 5;
        TexMgr_SetTexture(&texts[0], GetTextureByIdAndLang(0x65, -1));
        fn_801F8E90(&texts[0]);
        TexMgr_SetTexture(&texts[1], GetTextureByIdAndLang(0x66, -1));
        fn_801F8E90(&texts[1]);
        sub++;
        timer = 0;
        break;
    case 1: {
        float f = timer / lbl_806DB294;
        spr[2]->alpha = f;
        unsigned int c = PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f));
        label.SetColor(c);
        SetTextAlpha(c);
        if (timer >= 15) {
            label.SetColor(0xFFFFFFFF);
            spr[2]->alpha = lbl_806DB194;
            timer = 0;
            sub++;
        }
        break;
    }
    case 2:
        if (timer >= 200 || in->held == 1) {
            sub++;
            timer = 0;
        }
        break;
    case 3: {
        float f = lbl_806DB194 - timer / lbl_806DB250;
        spr[2]->alpha = f;
        unsigned int c = PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f));
        label.SetColor(c);
        SetTextAlpha(c);
        if (timer >= 10) {
            state = 3;
            sub = 0;
            TexMgr_SetTexture(&texts[0], lbl_806DB220);
            TexMgr_SetTexture(&texts[1], lbl_806DB220);
            fn_80121E10(&label);
            label.resId = 0x1ECD;
            label.SetColor(0xFFFFFF00);
        }
        break;
    }
    }
}

void ItemWnd::ShowOther() {
    InputState *in = GetInput();
    switch (sub) {
    case 0: {
        if (spr[1] != 0) {
            delete spr[1];
            spr[1] = 0;
        }
        fn_80121E10(&label);
        const char *name = fn_8013C26C(fn_80216960(entry->id), -1);
        if (entry->type == 3) {
            TexMgr_SetTexture(&texts[0], GetTextureByIdAndLang(0x61, -1), name);
            TexMgr_SetTexture(&texts[1], GetTextureByIdAndLang(0x62, -1));
            label.resId = 0x1ECD;
        } else {
            TexMgr_SetTexture(&texts[0], GetTextureByIdAndLang(0x63, -1), name);
            TexMgr_SetTexture(&texts[1], GetTextureByIdAndLang(0x64, -1));
            label.resId = 0x1D5C;
            if (spr[1] != 0) {
                delete spr[1];
                spr[1] = 0;
            }
            spr[1] = new Sprite(0x21, 1, 0);
            spr[1]->SetPos(lbl_806DB1E8, lbl_806DB290);
            spr[1]->layer = 6;
            spr[1]->alpha = lbl_806DB194;
        }
        if (item != 0) {
            fn_8021A4B8(item, lbl_806DB194, lbl_806DB194, lbl_806DB194, lbl_806DB190);
        }
        fn_801F8E90(&texts[0]);
        fn_801F8E90(&texts[1]);
        label.SetColor(0xFFFFFF00);
        label.Show(lbl_806DB1E8, lbl_806DB290, lbl_806DB194);
        labelLayer = 6;
        sub++;
        timer = 0;
        break;
    }
    case 1: {
        float f = timer / lbl_806DB294;
        spr[2]->alpha = f;
        if (item != 0) {
            fn_8021A430(item, f);
        }
        SetTextAlpha(PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f)));
        if (timer >= 15) {
            spr[2]->alpha = lbl_806DB194;
            timer = 0;
            sub++;
            if (item != 0) {
                fn_8021A430(item, lbl_806DB194);
            }
        }
        break;
    }
    case 2: {
        float s = lbl_806DB194;
        float f = timer / lbl_806DB294;
        if (entry->type == 4) {
            s = s - lbl_806DB20C * f;
        }
        if (item != 0) {
            fn_8021A4B8(item, s, s, s, lbl_806DB194);
        }
        label.SetColor(PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f)));
        if (timer >= 15) {
            label.SetColor(0xFFFFFFFF);
            timer = 0;
            sub++;
        }
        break;
    }
    case 3:
        if (timer >= 200 || in->held == 1) {
            sub++;
            timer = 0;
        }
        break;
    case 4: {
        float f = lbl_806DB194 - timer / lbl_806DB250;
        spr[2]->alpha = f;
        unsigned int c = PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f));
        label.SetColor(c);
        SetTextAlpha(c);
        if (item != 0) {
            if (entry->type == 4) {
                fn_8021A4B8(item, lbl_806DB204, lbl_806DB204, lbl_806DB204, f);
            } else {
                fn_8021A4B8(item, lbl_806DB194, lbl_806DB194, lbl_806DB194, f);
            }
        }
        if (timer >= 10) {
            state = 3;
            sub = 0;
            label.SetColor(0xFFFFFF00);
            label.resId = 0x1ECD;
            TexMgr_SetTexture(&texts[0], lbl_806DB220);
            TexMgr_SetTexture(&texts[1], lbl_806DB220);
            TexMgr_SetTexture(&texts[2], lbl_806DB220);
            if (spr[1] != 0) {
                delete spr[1];
                spr[1] = 0;
            }
        }
        break;
    }
    }
    if (item != 0) {
        fn_8013DAC8((Model *)item, 5);
    }
}

void ItemWnd::ShowTicket() {
    InputState *in = GetInput();
    switch (sub) {
    case 0: {
        if (spr[1] != 0) {
            delete spr[1];
            spr[1] = 0;
        }
        spr[1] = new Sprite(0x1B3, 1, 0);
        spr[1]->SetPos(lbl_806DB1E8, lbl_806DB1A4);
        spr[1]->SetAnimParam(0xC3F, fn_80216908(fn_80216974(entry->id)));
        spr[1]->layer = 5;
        spr[1]->alpha = lbl_806DB190;
        const char *name = fn_8021691C(entry->id);
        TexMgr_SetTexture(&texts[0], GetTextureByIdAndLang(0x5F, -1), name);
        fn_801F8E90(&texts[0]);
        TexMgr_SetTexture(&texts[1], GetTextureByIdAndLang(0x60, -1));
        fn_801F8E90(&texts[1]);
        sub++;
        timer = 0;
        break;
    }
    case 1: {
        float f = timer / lbl_806DB294;
        spr[1]->alpha = f;
        spr[2]->alpha = f;
        SetTextAlpha(PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f)));
        if (timer >= 15) {
            spr[2]->alpha = lbl_806DB194;
            spr[1]->alpha = lbl_806DB194;
            SetTextAlpha(0xFFFFFFFF);
            timer = 0;
            sub++;
        }
        break;
    }
    case 2:
        if (timer >= 200 || in->held == 1) {
            sub++;
            timer = 0;
        }
        break;
    case 3: {
        float f = lbl_806DB194 - timer / lbl_806DB250;
        spr[1]->alpha = f;
        spr[2]->alpha = f;
        SetTextAlpha(PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f)));
        if (timer >= 10) {
            state = 3;
            sub = 0;
            timer = 0;
            if (spr[1] != 0) {
                delete spr[1];
                spr[1] = 0;
            }
            SetTextAlpha(0xFFFFFF00);
            TexMgr_SetTexture(&texts[0], lbl_806DB220);
            TexMgr_SetTexture(&texts[1], lbl_806DB220);
            TexMgr_SetTexture(&texts[2], lbl_806DB220);
        }
        break;
    }
    }
}

void ItemWnd::ShowItem() {
    InputState *in = GetInput();
    float f = lbl_806DB190;
    switch (sub) {
    case 0: {
        int a = Item_GetDescriptorField8(itemId);
        int b = Item_GetDescriptorFieldC(itemId);
        short ra = -1;
        if (a >= 0) {
            ra = a + 0x17A3;
        }
        short rb = -1;
        if (b >= 0) {
            rb = b + 0x1E1D;
        }
        fn_8013BEC8(a);
        if (spr[1] != 0) {
            delete spr[1];
            spr[1] = 0;
        }
        spr[1] = new Sprite(0x19F, 1, 0);
        spr[1]->SetPos(lbl_806DB298, lbl_806DB29C);
        spr[1]->SetAnimParam(0x1E1D, rb);
        spr[1]->SetAnimParam(0x17A4, ra);
        spr[1]->SetAnimParam(0x13B9, Item_GetDescriptorField0(itemId, 0));
        spr[1]->layer = 5;
        spr[1]->alpha = lbl_806DB190;
        float pos[2];
        fn_8019FF8C(spr[1], 0x1ECD, pos);
        fn_801F93EC(&texts[3], pos[0], pos[1]);
        fn_8019FF8C(spr[1], 0x1ECF, pos);
        fn_801F93EC(&texts[4], pos[0], pos[1]);
        fn_8019FF8C(spr[1], 0x1ED1, pos);
        fn_801F93EC(&texts[5], pos[0], pos[1]);
        fn_8019FF8C(spr[1], 0x1ED3, pos);
        fn_801F93EC(&texts[6], pos[0], pos[1]);
        TexMgr_SetTexture(&texts[3], fn_8023DAA8(itemId));
        TexMgr_SetTexture(&texts[4], fn_8023D938(itemId, 0));
        TexMgr_SetTexture(&texts[5], fn_8023D938(itemId, 1));
        TexMgr_SetTexture(&texts[6], fn_8023D938(itemId, 2));
        char buf[0x40];
        *(struct Buf40 { char c[0x40]; } *)buf = *(const struct Buf40 *)lbl_803C6B84;
        int kind = fn_8023D710(itemId);
        switch (kind) {
        case -1:
            break;
        case 0:
        case 1: {
            const char *b2 = fn_8013C26C(1, -1);
            sprintf(buf, lbl_806DB2A0, fn_8013C26C(0, -1), b2);
            break;
        }
        case 8:
        case 9: {
            const char *b2 = fn_8013C26C(9, -1);
            sprintf(buf, lbl_806DB2A0, fn_8013C26C(8, -1), b2);
            texts[1].spacing = lbl_806DB1F4;
            break;
        }
        default:
            strcpy(buf, fn_8013C26C(kind, -1));
            break;
        }
        if (kind == -1) {
            TexMgr_SetTexture(&texts[1], GetTextureByIdAndLang(0x5E, -1));
        } else {
            TexMgr_SetTexture(&texts[1], GetTextureByIdAndLang(0x5D, -1), buf);
        }
        fn_801F8E90(&texts[1]);
        spr[1]->SetAnimParam(0x1ECF, 0x1ECD);
        spr[1]->SetAnimParam(0x1ED1, 0x1ECD);
        spr[1]->SetAnimParam(0x1ED3, 0x1ECD);
        *(unsigned int *)((char *)&texts[3] + 0x20) = 0xE0202000;
        *(unsigned int *)((char *)&texts[4] + 0x20) = 0xFFFFFF00;
        *(unsigned int *)((char *)&texts[5] + 0x20) = 0xFFFFFF00;
        *(unsigned int *)((char *)&texts[6] + 0x20) = 0xFFFFFF00;
        fn_80121E10(&label);
        label.resId = 0x1D5E;
        label.Show(lbl_806DB1CC, lbl_806DB290, lbl_806DB194);
        label.SetColor(0xFFFFFF00);
        labelLayer = 5;
        sub++;
        timer = 0;
        break;
    }
    case 1: {
        f = timer / lbl_806DB294;
        spr[1]->alpha = f;
        spr[2]->alpha = f;
        int a = (int)(lbl_806DB24C * f);
        *(unsigned int *)((char *)&texts[3] + 0x20) = PackColor(0xE0, 0x20, 0x20, a);
        unsigned int c = PackColor(0xFF, 0xFF, 0xFF, a);
        *(unsigned int *)((char *)&texts[4] + 0x20) = c;
        *(unsigned int *)((char *)&texts[5] + 0x20) = c;
        *(unsigned int *)((char *)&texts[6] + 0x20) = c;
        label.SetColor(c);
        SetTextAlpha(c);
        if (timer >= 15) {
            spr[2]->alpha = lbl_806DB194;
            spr[1]->alpha = lbl_806DB194;
            timer = 0;
            sub++;
        }
        break;
    }
    case 2:
        f = lbl_806DB194;
        if (timer >= 200 || in->held == 1) {
            sub++;
            timer = 0;
        }
        break;
    case 3: {
        f = lbl_806DB194 - timer / lbl_806DB250;
        spr[1]->alpha = f;
        spr[2]->alpha = f;
        int a = (int)(lbl_806DB24C * f);
        *(unsigned int *)((char *)&texts[3] + 0x20) = PackColor(0xE0, 0x20, 0x20, a);
        unsigned int c = PackColor(0xFF, 0xFF, 0xFF, a);
        *(unsigned int *)((char *)&texts[4] + 0x20) = c;
        *(unsigned int *)((char *)&texts[5] + 0x20) = c;
        *(unsigned int *)((char *)&texts[6] + 0x20) = c;
        label.SetColor(c);
        SetTextAlpha(c);
        if (timer >= 10) {
            label.resId = -1;
            sub = 0;
            timer = 0;
            state = 3;
            if (spr[1] != 0) {
                delete spr[1];
                spr[1] = 0;
            }
            TexMgr_SetTexture(&texts[0], lbl_806DB220);
            TexMgr_SetTexture(&texts[1], lbl_806DB220);
            TexMgr_SetTexture(&texts[2], lbl_806DB220);
            texts[1].spacing = lbl_806DB2A8;
        }
        break;
    }
    }
    if (kart != 0) {
        fn_8013D4B0(kart, f);
        fn_8013DAC8(kart, 5);
    }
}

void ItemWnd::Open() {
    switch (sub) {
    case 0: {
        int a = (int)(lbl_806DB284 * (timer / lbl_806DB250));
        fade.SetColor((unsigned char)a);
        if (timer >= 10) {
            sub++;
            timer = 0;
            spr[0]->alpha = lbl_806DB194;
            spr[0]->sx = lbl_806DB190;
            spr[0]->sy = lbl_806DB190;
        }
        return;
    }
    case 1: {
        float f = timer / lbl_806DB294;
        float c = lbl_806DB194 - (float)cos(lbl_806DB1D8 * (lbl_806DB28C * f));
        c = c * c;
        spr[0]->sx = c;
        spr[0]->sy = c;
        spr[0]->alpha = f * f;
        if (timer >= 15) {
            sub = 0;
            timer = 0;
            state = 2;
            if (spr[2] != 0) {
                delete spr[2];
                spr[2] = 0;
            }
            spr[2] = new Sprite(0x14A, 1, 0);
            spr[2]->SetPos(lbl_806DB1E8, lbl_806DB2AC);
            spr[2]->layer = 5;
            spr[2]->alpha = lbl_806DB190;
            spr[2]->SetAnimParam(0x1931, 0x1ECD);
            spr[2]->SetAnimParam(0x1932, 0x1ECD);
            spr[2]->SetAnimParam(0x1933, 0x1ECD);
            spr[2]->SetAnimParam(0x1934, 0x1ECD);
            int d[4] = {0, 0, 0, 0};
            d[3] = coins / 1000 % 10;
            d[0] = coins % 10;
            d[1] = coins / 10 % 10;
            d[2] = coins / 100 % 10;
            if (d[3] == 0) {
                d[3] = -1;
            }
            if (d[2] == 0 && d[3] < 0) {
                d[2] = -1;
            }
            int row = 0;
            if (isJapanese() == 1) {
                if (d[3] < 0) {
                    row = 1;
                } else {
                    row = 2;
                }
            }
            const float *xs = lbl_803C6BD4[row];
            for (int i = 0; i < 4; i++) {
                fn_80121E10(&digits[i]);
                if (d[i] < 0) {
                    digits[i].resId = 0x1ECD;
                } else {
                    digits[i].resId = (short)(d[i] + 0x1931);
                }
                digits[i].Show(xs[i], lbl_806DB2B0, lbl_806DB194);
                digits[i].SetColor(0xFFFFFF00);
            }
        }
        break;
    }
    }
}

void clCSSceneCoinMilage::Destroy() {
    delete this;
}

extern "C" clCSSceneCoinMilage *fn_80223500(void) {
    return new clCSSceneCoinMilage;
}

clCSSceneCoinMilage::~clCSSceneCoinMilage() {
    delete wnd;
    delete next;
    for (FadeObj **it = nodes.begin(); it != nodes.end(); it++) {
        delete *it;
    }
    delete model;
    SetInput(0);
    ItemDisplay_Destroy();
    fn_8021A0B0(lbl_806D1A60);
    fn_801699D8(0, 0);
    fn_80169C44();
}

clCSSceneCoinMilage::clCSSceneCoinMilage()
    : numCoins(0), model(new Model(lbl_803C6CD0, 1)), x3d0(0), perfectCoins(0), hasPerfect(0), hasBonus1(0),
      hasBonus2(0), counter(0), itemIndex(-1), state(0), sub(0), timer(0), wait(0), sum(0), wnd(0), next(0) {
    if (!IsCardValid()) {
        state = 8;
        done = 1;
        return;
    }
    if (g_cupId >= 9) {
        AddCoinsFromExtraStage();
    } else if (g_gameMode != 1) {
        CalcEarnedCoins();
    }
    fn_8021651C(g_playerData);
    AddCoinMilage(g_playerData, GetEarnedCoins());
    SetInput(1);
    ItemDisplay_GetOrCreate();
    ItemDisplay_GetOrCreate()->mode = 2;
    fn_8013DBF8();
    lines[0] = 0;
    lines[1] = 0;
    lines[2] = 0;
    lines[3] = 0;
    perfect = 0;
    for (int i = 0; i < 30; i++) {
        coins[i].x = (rand() % 6400) / lbl_806DB250;
        coins[i].y = lbl_806DB2B4;
        coins[i].z = (rand() % 500) / lbl_806DB2B8;
        coins[i].vy = lbl_806DB2C0 * (rand() % 300) + lbl_806DB2BC;
        coins[i].rot = rand() % 360;
        coins[i].bounced = 0;
        coins[i].vx = lbl_806DB190;
        float v = lbl_806DB2C0 * (rand() % 1600 - 800);
        if (v >= lbl_806DB190) {
            v += lbl_806DB194;
        } else {
            v -= lbl_806DB194;
        }
        coins[i].vrot = v;
    }
    int c = fn_802161CC();
    counter = c;
    x3d0 = c;
    milage = GetCoinMilage(g_playerData);
    perfectCoins = fn_802161F4();
    earned = fn_802161FC();
    if (g_gameMode == 1) {
        bonus1 = fn_802161DC();
        bonus2 = fn_802161D4();
    } else if (g_gameMode == 0) {
        bonus1 = fn_802161EC();
        bonus2 = GetCoinCount();
    } else {
        bonus1 = fn_802161EC();
        bonus2 = -1;
    }
    if (bonus1 >= 0) {
        hasBonus1 = 1;
    }
    if (bonus2 >= 0) {
        hasBonus2 = 1;
    }
    if (perfectCoins > 0) {
        hasPerfect = 1;
    }
    fn_8013D59C(model, lbl_806DB1D8 * lbl_803C6A18[0], lbl_806DB1D8 * lbl_803C6A18[1], lbl_806DB1D8 * lbl_803C6A18[2]);
    fn_8013D608(model, lbl_806DB2C4, lbl_806DB2C4, lbl_806DB2C4);
    fn_8013D4B0(model, lbl_806DB194);
    fn_8013D738(model, lbl_806DB190, lbl_806DB194);
    FadeObj *fill = new FilterNode;
    fill->tracks[0].Set(lbl_806DB194, lbl_806DB190, lbl_806DB198);
    nodes.push_back(fill);
    itemIndex = fn_80216988(x3d0);
    wnd = new ItemWnd;
    next = new NextWnd;
    TextSprite tmp;
    tmp.visible = 1;
    TexMgr_SetTexture(&tmp, GetTextureByIdAndLang(0x6C, -1));
    TexMgr_Apply(&tmp);
    TexMgr_SetTexture(&tmp, GetTextureByIdAndLang(0x72, -1));
    TexMgr_Apply(&tmp);
    if (g_gameMode == 1) {
        TexMgr_SetTexture(&tmp, GetTextureByIdAndLang(0x71, -1));
        TexMgr_Apply(&tmp);
        TexMgr_SetTexture(&tmp, GetTextureByIdAndLang(0x70, -1));
        TexMgr_Apply(&tmp);
    } else {
        TexMgr_SetTexture(&tmp, GetTextureByIdAndLang(0x6E, -1));
        TexMgr_Apply(&tmp);
        TexMgr_SetTexture(&tmp, GetTextureByIdAndLang(0x6F, -1));
        TexMgr_Apply(&tmp);
    }
    InitRumbleController(1);
    fn_801699D8(0, 1);
    fn_8020F3F0();
    fn_8020F38C(0);
}
#pragma inline_max_size(240)
