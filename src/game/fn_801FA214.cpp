/* Card scene destructor: tears down its sequence and owned step object. */
class Owned801FA214 {
public:
    virtual ~Owned801FA214();
};

extern "C" {
extern void *lbl_804EBE38[];
extern void *lbl_803FE0C8[];
void fn_801F4D3C(void *seq);
void fn_802040B0(void);
void fn_80207D38(void);
void fn_801F8E54(void);
}

struct Holder801FA214 {
    Owned801FA214 *p;
    ~Holder801FA214() throw() {
        delete p;
    }
};

struct Base801FA214 {
    void *vt;
    ~Base801FA214() {
        vt = lbl_803FE0C8;
    }
};

struct Scene801FA214 : Base801FA214 {
    int unk4;
    Holder801FA214 seq;

    ~Scene801FA214();
};

Scene801FA214::~Scene801FA214() {
    vt = lbl_804EBE38;
    fn_801F4D3C(seq.p);
    fn_802040B0();
    fn_80207D38();
    fn_801F8E54();
}
