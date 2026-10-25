/* Destructor of a path owner subclass (base destructor inlined). */
extern "C" {
extern void *lbl_804E4BEC[];
extern void *lbl_804E4C18[];
}

class PathUser {
public:
    ~PathUser();
};

struct PathUserHolder {
    PathUser *p;
    ~PathUserHolder() throw() {
        delete p;
    }
};

struct PathOwner {
    void *vt;
    PathUserHolder user;
    int unk8;
    int unkC;

    ~PathOwner() {
        vt = lbl_804E4C18;
        unkC = 0;
        unk8 = 0;
    }
};

struct PathOwner801EC404 : PathOwner {
    ~PathOwner801EC404();
};

PathOwner801EC404::~PathOwner801EC404() {
    vt = lbl_804E4BEC;
}
