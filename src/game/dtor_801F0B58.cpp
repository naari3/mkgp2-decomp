/* Owning holder whose throw() destructor deletes the held object. */
#pragma exceptions on
class Owned801F0B58 {
public:
    ~Owned801F0B58();
};

struct Holder801F0B58 {
    Owned801F0B58 *p;
    ~Holder801F0B58() throw();
};

Holder801F0B58::~Holder801F0B58() throw() { delete p; }
