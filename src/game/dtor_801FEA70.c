/* Observed lifetime views only: vptr at zero for the first class;
 * one owned polymorphic pointer at zero for each nonvirtual holder.
 * Real deleting destructors and throw() emit all exception metadata.
 * The existing TU declaration controls exception-entry placement. */
#pragma cplusplus on
#pragma exceptions on
void operator delete(void *);

class Lifetime801FEA70 {
public:
    virtual void ExternalKey();
    virtual ~Lifetime801FEA70();
};
class Owned801FEA {
public:
    virtual ~Owned801FEA();
};
struct Holder801FEAB8 {
    Owned801FEA *p;
    ~Holder801FEAB8() throw();
};
struct Holder801FEB48 {
    Owned801FEA *p;
    ~Holder801FEB48() throw();
};

Lifetime801FEA70::~Lifetime801FEA70() {}
Holder801FEAB8::~Holder801FEAB8() throw() { delete p; }
Holder801FEB48::~Holder801FEB48() throw() { delete p; }
#pragma exceptions reset
#pragma cplusplus off

