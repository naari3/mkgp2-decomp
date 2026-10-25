#ifndef GAME_CSPARTS_H
#define GAME_CSPARTS_H

/*
 * Result-screen model parts (clCSParts family). clCSPartsInerface is the
 * effect base whose vtable (lbl_8048EB44) and dtor live in SpriteEffects.c;
 * clCSParts owns a chain of clCSModel instances and forwards its virtuals to
 * the head model. Built with RTTI on: every TU carries its own type-info
 * names in .rodata and records in .sdata.
 */

void *operator new(unsigned long);
void operator delete(void *);

struct clCSModel {
    char pad[0x70];
    clCSModel(int res, int a, int b, const void *params, int c);
    ~clCSModel();
};

extern "C" {
extern int g_cupId;
extern int g_gameMode;
extern void PreloadResource(int id);
extern void fn_8013B7A8(clCSModel *head, clCSModel *next);
}

struct clCSPartsInerface {
    int obj;
    unsigned char active;
    float x, y;
    float alpha;

    clCSPartsInerface() {
        obj = 0;
        active = 0;
        x = 0.0f;
        y = 0.0f;
        alpha = 1.0f;
    }
    virtual ~clCSPartsInerface() {}
    virtual void m0C();
    virtual void m10();
    virtual void Update();
    virtual void Draw();
    virtual void m1C();
};

/*
 * CSPartsResultRank.c defines the dtor out of line; the other users define
 * CSPARTS_INLINE_DTOR and see it inline in the class.
 */
struct clCSParts : clCSPartsInerface {
    clCSModel *model;

    clCSParts() { model = 0; }
#ifdef CSPARTS_INLINE_DTOR
    virtual ~clCSParts() {
        if (model) {
            delete model;
        }
    }
#else
    virtual ~clCSParts();
#endif
    virtual void m0C();
    virtual void m10();
    virtual void Update();
    virtual void Draw();
    void Add(clCSModel *m) {
        if (model) {
            fn_8013B7A8(model, m);
        } else {
            model = m;
        }
    }
};

#endif
