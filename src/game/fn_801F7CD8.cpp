/* Holder destructor: deletes the owned object through its virtual destructor. */
class Owned801F7CD8 {
public:
    virtual ~Owned801F7CD8();
};

struct Holder801F7CD8 {
    Owned801F7CD8 *p;
    ~Holder801F7CD8();
};

Holder801F7CD8::~Holder801F7CD8() {
    if (p != 0) {
        delete p;
        p = 0;
    }
}
