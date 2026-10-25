/* Card scene destructor with two owned step objects. */
class Owned801FAA18 {
public:
    virtual ~Owned801FAA18();
};

extern "C" {
extern void *lbl_804EBE78[];
void fn_801F4D3C(void *seq);
void fn_80120A08(int id);
}

struct Holder801FAA18 {
    Owned801FAA18 *p;
    ~Holder801FAA18() throw() {
        delete p;
    }
};

struct Base801FAA18 {
    void *vt;
    ~Base801FAA18();
};

struct StepHolder801FAA18 {
    Owned801FAA18 *p;
    ~StepHolder801FAA18() throw() {
        delete p;
    }
};

struct Scene801FAA18 : Base801FAA18 {
    char pad_4[0xC];
    Holder801FAA18 seq;
    StepHolder801FAA18 step;

    ~Scene801FAA18();
};

Scene801FAA18::~Scene801FAA18() {
    vt = lbl_804EBE78;
    fn_801F4D3C(seq.p);
    fn_80120A08(0x72F);
    fn_80120A08(0x734);
    fn_80120A08(0x730);
}
