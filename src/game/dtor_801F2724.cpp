/* Owning holder whose throw() destructor deletes the held object. */
#pragma exceptions on
class Owned801F2724 {
public:
    virtual ~Owned801F2724();
};

struct Holder801F2724 {
    Owned801F2724 *p;
    ~Holder801F2724() throw();
};

Holder801F2724::~Holder801F2724() throw() { delete p; }
