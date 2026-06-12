/* Isolation test: can CW 1.3.2 emit the exact dtor_8005278C shape from C++?
 * Target __dt shape: null-check this; delete member ptr (__dt(p,1) direct);
 * if (flags>0) MemoryManager_TimedFree(this); return this; + throw() spec
 * (SPECIFICATION extab, __unexpected island, back-chain epilogue). */
extern "C" void *MemoryManager_TimedFree(void *ptr);

struct Pointee {
    char pad;
    ~Pointee() throw();   /* defined elsewhere (= Free_IfOwnedShort) */
    static void operator delete(void *p) { MemoryManager_TimedFree(p); }
};

struct Holder {
    Pointee *p;
    ~Holder() throw();
    static void operator delete(void *q) { MemoryManager_TimedFree(q); }
};

Holder::~Holder() throw() {
    delete p;
}
