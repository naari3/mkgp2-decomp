/* Owning holder whose throw() destructor deletes the held object. */
#pragma exceptions on
class Owned801E89E8 {
public:
    ~Owned801E89E8();
};

struct Holder801E89E8 {
    Owned801E89E8 *p;
    ~Holder801E89E8() throw();
};

Holder801E89E8::~Holder801E89E8() throw() { delete p; }
