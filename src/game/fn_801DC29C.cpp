/* Destructor of an object owning one path cursor. */
class Owned801DC29C {
public:
    ~Owned801DC29C();
};

struct Holder801DC29C {
    Owned801DC29C *p;
    ~Holder801DC29C() throw() {
        delete p;
    }
};

struct PathUser801DC29C {
    char pad0[0xC];
    Holder801DC29C cursor;

    ~PathUser801DC29C();
};

PathUser801DC29C::~PathUser801DC29C() {
}
