extern "C" {
    struct __eti_init_info;
    extern struct __eti_init_info _eti_init_info;
    int __register_fragment(struct __eti_init_info *info, char *r2);
    void __unregister_fragment(int fragmentID);
    void __destroy_global_chain(void);

    void __init_cpp_exceptions(void);
    void __fini_cpp_exceptions(void);
}

static int fragmentID = -2;

asm char *GetR2(void) {
    nofralloc
    mr r3, r2
    blr
}

void __fini_cpp_exceptions(void) {
    if ((int)fragmentID != -2) {
        __unregister_fragment(fragmentID);
        fragmentID = -2;
    }
}

void __init_cpp_exceptions(void) {
    if ((int)fragmentID == -2) {
        char *R2 = GetR2();
        fragmentID = __register_fragment(&_eti_init_info, R2);
    }
}

__declspec(section ".ctors") extern void *const __init_cpp_exceptions_reference  = (void *)__init_cpp_exceptions;
__declspec(section ".dtors") extern void *const __destroy_global_chain_reference = (void *)__destroy_global_chain;
__declspec(section ".dtors") extern void *const __fini_cpp_exceptions_reference  = (void *)__fini_cpp_exceptions;
