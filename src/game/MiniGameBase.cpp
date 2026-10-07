/* Actual target/callee ASM audited; Ghidra unavailable. */
void operator delete(void*);
extern "C" {
void fn_802C8B48(int);
void fn_801DE6E8();
void SetCourseScene3D(void*);
}
struct MBRoot {
    virtual void identity();
    virtual ~MBRoot();
};
struct MBOwner : MBRoot {
    float phase;
    virtual void identity();
    virtual ~MBOwner();
};
MBOwner::~MBOwner() {
    fn_802C8B48(0);
    fn_801DE6E8();
    SetCourseScene3D(0);
}
