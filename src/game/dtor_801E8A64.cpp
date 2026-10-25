/* Owning holder whose throw() destructor deletes the held object. */
#pragma exceptions on
class Owned801E8A64 {
public:
    ~Owned801E8A64();
};

struct Holder801E8A64 {
    Owned801E8A64 *p;
    ~Holder801E8A64() throw();
};

Holder801E8A64::~Holder801E8A64() throw() { delete p; }
