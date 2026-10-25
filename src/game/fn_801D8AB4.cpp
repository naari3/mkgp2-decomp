/* Output of fn_8019FF8C; only the leading position is read here. */
struct SpriteNodeInfo {
    float x, y;
    char rest[0x28];
};
class Sprite {
public:
    Sprite(int id, int a, int b);
    char pad0[4];
    int layer;
    char pad8[4];
    float x;
    float y;
    char pad14[0xC];
    float alpha;
    char pad24[0xC];
    void SetLayer(int l) { layer = l; }
    void SetPos(float px, float py) { x = px; y = py; }
    void SetAlpha(float a) { alpha = a; }
};
struct SpritePtr {
    Sprite *p;
    SpritePtr(Sprite *s) : p(s) {}
    ~SpritePtr();
    Sprite *operator->() { return p; }
};
struct KartInfoEntry {
    int res;
    short v[3];
    short name;
    short text[3];
    char pad12[2];
};
struct KartInfoLabel {
    const wchar_t *text;
    wchar_t buf[0x21];
    char pad46[2];
    float x;
    float y;
};
extern "C" {
extern KartInfoEntry lbl_8039E9F8[];
extern const float lbl_806DA198, lbl_806DA19C;
float fn_8019FED8(Sprite *);
float fn_8019FEBC(Sprite *);
void Sprite_SetAnimTime(Sprite *, float);
unsigned char fn_8019FF8C(Sprite *, int, SpriteNodeInfo *);
void Sprite_SetAnimParam(Sprite *, int, int);
wchar_t *wmemset(wchar_t *, wchar_t, unsigned long);
}

static unsigned char HasText(short v) { return v >= 0; }

class KartInfoPanel {
public:
    int kind;
    SpritePtr sprite;
    int layer;
    float x;
    float y;
    KartInfoLabel name;
    KartInfoLabel subs[3];
    short v[3];
    char pad15A[2];
    float alpha;
    KartInfoPanel(int k);
};

KartInfoPanel::KartInfoPanel(int k) : kind(k), sprite(new Sprite(lbl_8039E9F8[k].res, 1, 0))
{
    int t;
    int i;
    SpriteNodeInfo pos;
    Sprite *spr;

    v[0] = lbl_8039E9F8[kind].v[0];
    v[1] = lbl_8039E9F8[kind].v[1];
    v[2] = lbl_8039E9F8[kind].v[2];
    layer = 7;
    sprite->SetLayer(layer);
    x = lbl_806DA19C;
    y = lbl_806DA19C;
    sprite->SetPos(x, y);
    sprite->SetAlpha(lbl_806DA198);
    alpha = lbl_806DA198;
    t = fn_8019FED8(sprite.p);
    spr = sprite.p;
    Sprite_SetAnimTime(spr, fn_8019FEBC(spr));
    wmemset(name.buf, 0, 0x21);
    if (HasText(lbl_8039E9F8[kind].name) == 1) {
        if (fn_8019FF8C(sprite.p, lbl_8039E9F8[kind].name, &pos) == 1) {
            name.x = pos.x;
            name.y = pos.y;
        }
    }
    for (i = 0; i < 3; i++) {
        wmemset(subs[i].buf, 0, 0x21);
        if (HasText(lbl_8039E9F8[kind].text[i]) == 1) {
            if (fn_8019FF8C(sprite.p, lbl_8039E9F8[kind].text[i], &pos) == 1) {
                subs[i].x = pos.x;
                subs[i].y = pos.y;
            }
        }
    }
    Sprite_SetAnimParam(sprite.p, lbl_8039E9F8[kind].name, 0x1ECD);
    for (int j = 0; j < 3; j++) {
        Sprite_SetAnimParam(sprite.p, lbl_8039E9F8[kind].text[j], 0x1ECD);
    }
    Sprite_SetAnimTime(sprite.p, t);
}
