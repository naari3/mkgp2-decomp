/*
 * clCSAnim (csAnim.cpp): keyframed sprite animation node list.
 * .text 0x8013AB74..0x8013BA90
 *
 * fn_8013BA78 (Reset) is inlined into its callers here; the weak
 * out-of-line copy CW emits is superseded by the strong definition in
 * csAnim_Reset.c, which sits at the address following this TU.
 *
 * fn_8013B87C is the CSAnim destructor: deleting `next` inlines the dtor
 * recursively up to the inline depth limit, and only the innermost level
 * calls the ResCtrl member dtor out of line (weak copy dtor_80082960).
 *
 * fn_8013AE20 (fp register count) does not match from C yet; it stays as
 * asm with manual extab, ordered via tools/extab_order.json.
 */

typedef struct CSVec2 {
    float u;
    float v;
} CSVec2;

typedef struct CSAnimKey {
    int type;
    int count;
    float x;
    float y;
    CSVec2 uv;
    float u18;
    float r;
    float g;
    float b;
    float a;
} CSAnimKey;

#pragma cplusplus on
struct ResCtrl {
    int res;
    int pad1C;
    int res20;
    int pad24;
    ~ResCtrl() {}
};

struct CSAnim {
    int id;
    CSAnim *next;
    int flags;
    int frame;
    int index;
    CSAnimKey *keys;
    /* 0x18: ResCtrl sprite resource */
    ResCtrl res;
    unsigned char visible;
    float x;
    float y;
    float z;
    int pad38;
    int pad3C;
    float u40;
    CSVec2 uv;
    unsigned int color[4];
    int pad5C;
    int u60;
    int u64;
    int u68;
    ~CSAnim();
};
#pragma cplusplus off
typedef struct CSAnim CSAnim;

extern const int lbl_806D7480;
extern const int lbl_806D7498;
extern char lbl_8035C678[];
extern char lbl_8035C684[];
extern const int lbl_806D7484;
extern const int lbl_806D7488;
extern const int lbl_806D7490;

extern void fn_8011FAFC(void *res, void *arg);
extern void OSPanic(const char *file, int line, const char *msg, ...);
extern void ResCtrl_Init(void *res);

void fn_8013AE20(CSAnim *n, float x, float y, float alpha);

inline void fn_8013BA78(CSAnim *n) {
    n->flags = 2;
    n->frame = 0;
    n->index = 0;
}

void fn_8013AB74(CSAnim *n, void *arg, int id) {
    if ((id < 0 || n->id == id) && n->keys && (n->flags & 4)) {
        fn_8011FAFC(&n->res, arg);
    }
    if (n->next) {
        fn_8013AB74(n->next, arg, id);
    }
}

static inline unsigned int CSAnim_PackColor(float r, float g, float b, float a, float alpha) {
    return ((unsigned char)(int)(255.0f * r) << 24) | ((unsigned char)(int)(255.0f * g) << 16) |
           ((unsigned char)(int)(255.0f * b) << 8) | (unsigned char)(int)(255.0f * a * alpha);
}

void fn_8013AE20(CSAnim *n, float x, float y, float alpha) {
    CSAnimKey *k;
    CSAnimKey *k2;
    int i;
    float t;
    unsigned int c;
    float px;
    float py;
    float r;
    float g;
    float b;
    float a;
    float u10;
    float u14;
    float u18;

    if (n->next) {
        fn_8013AE20(n->next, x, y, alpha);
    }
    if (n->keys && (n->flags & 1)) {
        k = &n->keys[n->index];
        for (;;) {
            if (k->type == 0) {
                n->index++;
                n->frame = 0;
                k = &n->keys[n->index];
            } else if (k->type == 1) {
                if (n->frame < k->count) {
                    n->flags &= ~4;
                    if (n->flags & 2) {
                        n->flags &= ~2;
                    } else {
                        n->frame++;
                    }
                    return;
                }
                n->index++;
                n->frame = 0;
                k = &n->keys[n->index];
            } else if (k->type == 2) {
                if (n->frame < k->count) {
                    if (n->flags & 2) {
                        n->flags &= ~2;
                    } else {
                        n->frame++;
                    }
                    break;
                }
                n->index++;
                n->frame = 0;
                k = &n->keys[n->index];
            } else if (k->type == 3) {
                for (i = 0;; i++) {
                    if (n->keys[i].type == 5) {
                        OSPanic(lbl_8035C678, 0x86, lbl_8035C684);
                    }
                    if (n->keys[i].type == 0 && k->count == n->keys[i].count) {
                        n->index = i;
                        n->frame = 0;
                        k = &n->keys[n->index];
                        goto next;
                    }
                }
            } else if (k->type == 4) {
                n->flags |= lbl_806D7480;
                px = k->x;
                py = k->y;
                n->visible = 1;
                n->x = px + x;
                n->y = py + y;
                n->z = 1.0f;
                u10 = k->uv.u;
                u14 = k->uv.v;
                n->uv.u = u10;
                n->uv.v = u14;
                g = k->g;
                a = k->a;
                r = k->r;
                b = k->b;
                c = ((unsigned char)(int)(255.0f * r) << 24) | ((unsigned char)(int)(255.0f * g) << 16) | ((unsigned char)(int)(255.0f * b) << 8) | (unsigned char)(int)(255.0f * a * alpha);
                n->color[0] = c;
                n->color[1] = c;
                n->color[2] = c;
                n->color[3] = c;
                return;
            } else {
                fn_8013BA78(n);
                return;
            }
        next:;
        }
        n->flags |= lbl_806D7480;
        t = (float)n->frame / (float)k->count;
        k2 = &n->keys[n->index + 1];
        py = k->y + t * (k2->y - k->y);
        u14 = k->uv.v + t * (k2->uv.v - k->uv.v);
        g = k->g + t * (k2->g - k->g);
        a = k->a + t * (k2->a - k->a);
        u18 = k->u18 + t * (k2->u18 - k->u18);
        r = k->r + t * (k2->r - k->r);
        b = k->b + t * (k2->b - k->b);
        u10 = k->uv.u + t * (k2->uv.u - k->uv.u);
        px = k->x + t * (k2->x - k->x);
        n->visible = 1;
        n->x = px + x;
        n->y = py + y;
        n->z = 1.0f;
        n->uv.u = u10;
        n->uv.v = u14;
        n->u40 = u18;
        c = ((unsigned char)(int)(255.0f * r) << 24) | ((unsigned char)(int)(255.0f * g) << 16) |
            ((unsigned char)(int)(255.0f * b) << 8) | (unsigned char)(int)(alpha * (255.0f * a));
        n->color[0] = c;
        n->color[1] = c;
        n->color[2] = c;
        n->color[3] = c;
    }
}

void fn_8013B300(CSAnim *n, int id) {
    if (id < 0 || n->id == id) {
        fn_8013BA78(n);
    }
    if (n->next) {
        fn_8013B300(n->next, id);
    }
}

void fn_8013B4FC(CSAnim *n, int id) {
    if ((id < 0 || n->id == id) && n->keys && !(n->flags & 1)) {
        fn_8013BA78(n);
        n->flags |= lbl_806D7498;
    }
    if (n->next) {
        fn_8013B4FC(n->next, id);
    }
}

void fn_8013B7A8(CSAnim *n, CSAnim *add) {
    if (n->next) {
        fn_8013B7A8(n->next, add);
        return;
    }
    n->next = add;
}

#pragma cplusplus on
#pragma exceptions on
void operator delete(void *p);

CSAnim::~CSAnim() {
    if (next) {
        delete next;
    }
}
#pragma exceptions reset
#pragma cplusplus off

CSAnim *fn_8013B9A0(CSAnim *n, int res, int res20, int mode, CSAnimKey *keys, int id) {
    n->id = id;
    n->keys = 0;
    ResCtrl_Init(&n->res);
    fn_8013BA78(n);
    n->next = 0;
    if (keys == 0) {
        return n;
    }
    n->keys = keys;
    n->res.res = res;
    n->res.res20 = res20;
    if (res20 <= -1 || res20 >= 5) {
        n->res.res20 = 0;
    }
    switch (mode) {
    case 1:
        n->u60 = 1;
        n->u64 = 4;
        n->u68 = 1;
        break;
    default:
        n->u60 = 1;
        n->u64 = 4;
        n->u68 = 5;
        break;
    }
    return n;
}
