/* Destructor of an object that owns one path user. */
extern "C" {
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

struct PathOwner801F05A8 {
    void *vt;
    PathUserHolder user;
    int unk8;
    int unkC;

    ~PathOwner801F05A8();
};

PathOwner801F05A8::~PathOwner801F05A8() {
    vt = lbl_804E4C18;
    unkC = 0;
    unk8 = 0;
}
