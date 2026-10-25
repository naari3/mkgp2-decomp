/* Owning holder whose throw() destructor deletes the held object. */
#pragma exceptions on
class Owned801CCA30 {
public:
    ~Owned801CCA30();
};

struct Holder801CCA30 {
    Owned801CCA30 *p;
    ~Holder801CCA30() throw();
};

Holder801CCA30::~Holder801CCA30() throw() { delete p; }
