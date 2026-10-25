extern "C" {
extern char lbl_80491880[];
void fn_801DAE54(void);
void fn_8018137C(void);
void fn_8018013C(void);
void dtor_8002CDF4(void *self, short flag);
void MemoryManager_TimedFree(void *p);
}

struct VRel {
    virtual void v0();
    virtual void Release();
};

struct VDel {
    virtual ~VDel();
};

extern VRel *lbl_806D15FC;
extern VDel *g_pInputState;

extern "C" void *fn_8017FCAC(void **self, short flag) {
    if (self != 0) {
        *self = lbl_80491880;
        fn_801DAE54();
        if (lbl_806D15FC != 0) {
            lbl_806D15FC->Release();
            lbl_806D15FC = 0;
        }
        fn_8018137C();
        fn_8018013C();
        delete g_pInputState;
        g_pInputState = 0;
        dtor_8002CDF4(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
