// Target-derived virtual base and shared-pointer wrapper at offset 4.
struct PcbBase {
    virtual void key();
    virtual ~PcbBase() {}
};
struct SharedPtr { void* value; ~SharedPtr(); };
struct SharedPtrMember { SharedPtr value; ~SharedPtrMember() {} };
// Inline base view preserves the original inherited destructor expansion.
struct PcbMidInline : PcbBase {
    SharedPtrMember member;
    virtual void key();
    virtual ~PcbMidInline() {}
};
struct ClStrPcb : PcbMidInline {
    virtual void key();
    virtual ~ClStrPcb();
};
struct PcbMid : PcbBase {
    SharedPtrMember member;
    virtual void key();
    virtual ~PcbMid();
};
ClStrPcb::~ClStrPcb() {}
PcbMid::~PcbMid() {}

