/* Owning holder whose throw() destructor deletes the held object. */
#pragma exceptions on
class Owned801E8AE0 {
public:
    virtual ~Owned801E8AE0();
};

struct Holder801E8AE0 {
    Owned801E8AE0 *p;
    ~Holder801E8AE0() throw();
};

Holder801E8AE0::~Holder801E8AE0() throw() { delete p; }
