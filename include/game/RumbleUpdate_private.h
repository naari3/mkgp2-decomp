struct RumbleUpdateState {
    unsigned char useJvs;
    bool base[2];
    bool out[2];
    char pad05[3];
    unsigned int mode[2];
    int duration[2];
    int timer[2];
    ~RumbleUpdateState();
    static void operator delete(void *p);
};
struct RumbleDisplay {
    int pad[2]; unsigned int out[2];
    void SetFirst(unsigned int on) { out[0] = on; }
    void SetSecond(unsigned int on) { out[1] = on; }
};
extern "C" {
extern RumbleUpdateState *lbl_806D15B0;
RumbleDisplay *fn_801DAEC0();
void fn_801DABFC(RumbleDisplay *);
void *StrPcb_GetInstance();
void StrPcb_SetStatusBits(void *, unsigned char, int);
void StrPcb_ClearStatusBits(void *, unsigned char);
void MemoryManager_TimedFree(void *);
}
static inline void RumbleApply(RumbleUpdateState *r) {
    if (r->useJvs) {
        fn_801DAEC0()->SetFirst(r->out[0]);
        fn_801DAEC0()->SetSecond(r->out[1]);
        fn_801DABFC(fn_801DAEC0());
    } else {
        unsigned char on = 0, off = 0;
        if (r->out[0]) on |= 4;
        if (!r->out[0]) off |= 4;
        if (r->out[1]) on |= 8;
        if (!r->out[1]) off |= 8;
        if (StrPcb_GetInstance()) {
            if (on) StrPcb_SetStatusBits(StrPcb_GetInstance(), on, 0);
            if (off) StrPcb_ClearStatusBits(StrPcb_GetInstance(), off);
        }
    }
}

inline RumbleUpdateState::~RumbleUpdateState() {
    out[0] = base[0];
    out[1] = base[1];
    RumbleApply(this);
}
inline void RumbleUpdateState::operator delete(void *p) { MemoryManager_TimedFree(p); }
