/* Owning holder whose throw() destructor deletes the held object. */
#pragma exceptions on
class Owned801E8C00 {
public:
    ~Owned801E8C00();
};

struct Holder801E8C00 {
    Owned801E8C00 *p;
    ~Holder801E8C00() throw();
};

Holder801E8C00::~Holder801E8C00() throw() { delete p; }
