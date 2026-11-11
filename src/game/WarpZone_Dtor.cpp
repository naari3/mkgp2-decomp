/* clHitReaction: abstract hit-response interface, target 0x800AA888..0x800AA8FC.
 * Deferred generation preserves the original reverse method-definition order.
 * Vtable, RTTI record and class name are emitted by the compiler.
 */
class clHitReaction {
public:
    virtual int Method0();
    virtual void Method1();
    virtual int Method2();
    virtual int Method3();
    virtual void Method4() = 0;
    virtual void Method5() = 0;
    virtual ~clHitReaction();
    clHitReaction();
};

int clHitReaction::Method0() { return 0; }
void clHitReaction::Method1() {}
int clHitReaction::Method2() { return 0; }
int clHitReaction::Method3() { return 0; }
clHitReaction::clHitReaction() {}
clHitReaction::~clHitReaction() {}
