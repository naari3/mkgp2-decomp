/* Owning holder whose throw() destructor deletes the held object. */
#pragma exceptions on
class Owned801DC460 {
public:
    ~Owned801DC460();
};

struct Holder801DC460 {
    Owned801DC460 *p;
    ~Holder801DC460() throw();
};

Holder801DC460::~Holder801DC460() throw() { delete p; }
