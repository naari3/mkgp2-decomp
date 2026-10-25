/* Owning holder whose throw() destructor deletes the held object. */
#pragma exceptions on
class Owned801E8B70 {
public:
    virtual ~Owned801E8B70();
};

struct Holder801E8B70 {
    Owned801E8B70 *p;
    ~Holder801E8B70() throw();
};

Holder801E8B70::~Holder801E8B70() throw() { delete p; }
