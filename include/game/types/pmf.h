#ifndef GAME_TYPES_PMF_H
#define GAME_TYPES_PMF_H

/* Pointers to member functions, in MWCC's layout on every compiler.
 *
 *   PMF_TYPE(Name, Class, Ret, Args);      typedef Ret (Class::*Name) Args;
 *   PMF_CALL(obj, pmf)(args)               ((obj)->*(pmf))(args), obj a pointer
 *   PMF_OF(&Class::Method)                 the constant
 *   PMF_IS_SET(pmf)                        (pmf) as a condition: not null
 *
 * Under MWCC these are exactly the plain C++ forms. MWCC's pointer to member
 * function is 12 bytes:
 *
 *   { long thisDelta; long vtableOffset; union { void *func; long vptrOffset; }; }
 *
 * with vtableOffset == -1 for a non-virtual function (what __ptmf_scall in
 * src/Runtime reads). The game's data tables are written in that layout by
 * hand (`void *x[3] = { 0, (void *)-1, fn }` in src/game/autodata) and the
 * objects that hold one are laid out for 12 bytes. Clang and GCC use 8 bytes
 * with another meaning, so elsewhere the type is a 12-byte struct that keeps
 * MWCC's layout, and the call is done by hand.
 *
 * Always declare, call and take such pointers through these macros.
 * See docs/notes/port_abi.md.
 */
#ifdef __MWERKS__

#define PMF_TYPE(Name, Class, Ret, Args) typedef Ret (Class::*Name) Args
#define PMF_CALL(obj, pmf) ((obj)->*(pmf))
#define PMF_OF(method) (method)
#define PMF_IS_SET(pmf) (pmf)

#else

struct PortPmfRaw {
    int thisDelta;
    int vtableOffset; /* < 0: not virtual */
    union {
        void *func;      /* not virtual: the function */
        int vptrOffset;  /* virtual: where the object keeps its vtable pointer */
    } u;
};

/* F is the host's pointer-to-member type; it only carries the signature. */
template <class F> struct PortPmf {
    PortPmfRaw raw;
};

/* The function a PortPmf names, with `this` as an explicit first argument,
 * bound to the adjusted object. One specialisation per argument count. */
template <class F> struct PortPmfBound;
template <class C, class R> struct PortPmfBound<R (C::*)()> {
    typedef C Class;
    typedef R (*Fn)(C *);
    Fn fn;
    C *self;
    R operator()() const { return fn(self); }
};
template <class C, class R, class A1> struct PortPmfBound<R (C::*)(A1)> {
    typedef C Class;
    typedef R (*Fn)(C *, A1);
    Fn fn;
    C *self;
    R operator()(A1 a1) const { return fn(self, a1); }
};
template <class C, class R, class A1, class A2> struct PortPmfBound<R (C::*)(A1, A2)> {
    typedef C Class;
    typedef R (*Fn)(C *, A1, A2);
    Fn fn;
    C *self;
    R operator()(A1 a1, A2 a2) const { return fn(self, a1, a2); }
};
template <class C, class R, class A1, class A2, class A3> struct PortPmfBound<R (C::*)(A1, A2, A3)> {
    typedef C Class;
    typedef R (*Fn)(C *, A1, A2, A3);
    Fn fn;
    C *self;
    R operator()(A1 a1, A2 a2, A3 a3) const { return fn(self, a1, a2, a3); }
};

/* What MWCC's call sequence does: adjust `this`, then take the function from
 * the record or from the object's vtable (the port build keeps MWCC-layout
 * vtables whose entries are plain function addresses). The object pointer is
 * reinterpreted, not converted: the game often calls through a view struct
 * that is unrelated to the class in the pointer's type. */
template <class F> inline PortPmfBound<F> port_pmf_bind(void *obj, const PortPmf<F> &pmf) {
    PortPmfBound<F> bound;
    char *self = (char *)obj + pmf.raw.thisDelta;
    void *fn;
    if (pmf.raw.vtableOffset < 0) {
        fn = pmf.raw.u.func;
    } else {
        char *vtable = *(char **)(self + pmf.raw.u.vptrOffset);
        fn = *(void **)(vtable + pmf.raw.vtableOffset);
    }
    bound.fn = (typename PortPmfBound<F>::Fn)fn;
    bound.self = (typename PortPmfBound<F>::Class *)self;
    return bound;
}

/* A constant, built from the host's own representation. Only the Itanium
 * C++ ABI is understood ({ function or 1 + vtable offset, this adjustment });
 * a virtual function gets vptrOffset 0, which is right only for classes
 * whose vtable pointer comes first. */
template <class F> inline PortPmf<F> port_pmf_of(F method) {
    struct Host {
        void *ptr;
        long adj;
    };
    typedef char HostPmfIsTwoWords[sizeof(F) == sizeof(Host) ? 1 : -1];
    union {
        F method;
        Host host;
    } view;
    PortPmf<F> pmf;
    view.method = method;
    pmf.raw.thisDelta = (int)view.host.adj;
    if ((unsigned long)view.host.ptr & 1) {
        pmf.raw.vtableOffset = (int)((unsigned long)view.host.ptr - 1);
        pmf.raw.u.vptrOffset = 0;
    } else {
        pmf.raw.vtableOffset = -1;
        pmf.raw.u.func = view.host.ptr;
    }
    return pmf;
}

#define PMF_TYPE(Name, Class, Ret, Args) typedef PortPmf< Ret (Class::*) Args > Name
#define PMF_CALL(obj, pmf) (port_pmf_bind((void *)(obj), (pmf)))
#define PMF_OF(method) (port_pmf_of(method))
/* MWCC's test (__ptmf_test): null is all three words zero. */
#define PMF_IS_SET(pmf) ((pmf).raw.thisDelta != 0 || (pmf).raw.vtableOffset != 0 || (pmf).raw.u.func != 0)

#endif

#endif
