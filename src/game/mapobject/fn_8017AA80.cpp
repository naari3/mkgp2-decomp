struct Def {
    unsigned char pad[0x18];
    int mask;
};

class Obj {
public:
    Obj *next;
    Def *def;
    unsigned char pad[0x14];
    virtual void Update();
    virtual void Draw();
};

struct Group {
    Group *next;
    int pad;
    Obj *objs;
    void Update() {
        for (Obj *o = objs; o != 0; o = o->next) {
            o->Update();
        }
    }
    void Draw(int mask) {
        for (Obj *o = objs; o != 0; o = o->next) {
            if (o->def->mask & mask) {
                o->Draw();
            }
        }
    }
};

struct Cam {
    unsigned char pad[0xC];
    int index;
};

struct Mgr {
    Cam *cam;
    Group *groups;
};

extern "C" void fn_8017AA80(Mgr *mgr) {
    int mask;
    if (mgr->cam != 0 && mgr->cam->index >= 0) {
        mask = 1 << mgr->cam->index;
    } else {
        mask = -1;
    }
    for (Group *g = mgr->groups; g != 0; g = g->next) {
        g->Draw(mask);
    }
}
