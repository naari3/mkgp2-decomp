/* ShadowAreaMgr constructor: real C++ ctor (base ctor registers the
 * singleton, member array of 0x40 ShadowAreaEntry). Mangled names are
 * bridged to the existing symbols via tools/extab_user_renames.json. */
#pragma cplusplus on

extern "C" {
extern void DebugPrintf(const char *, ...);
extern char lbl_803285A0[];
}

struct ShadowAreaEntry {
    unsigned char opaque[0x1B4];
    ShadowAreaEntry();
    ~ShadowAreaEntry();
};

struct ShadowAreaBase;
extern "C" ShadowAreaBase *lbl_806D1060;

struct ShadowAreaBase {
    ShadowAreaBase() { lbl_806D1060 = this; }
    virtual ~ShadowAreaBase();
};

struct ShadowAreaMgr : ShadowAreaBase {
    ShadowAreaEntry entries[0x40];
    int count;

    ShadowAreaMgr(void *archive);
    virtual ~ShadowAreaMgr();
};

extern "C" int ShadowAreaMgr_BuildFromArchive(ShadowAreaMgr *, void *);

#pragma exceptions on
ShadowAreaMgr::ShadowAreaMgr(void *archive)
{
    count = 0;
    count = ShadowAreaMgr_BuildFromArchive(this, archive);
    DebugPrintf(lbl_803285A0, count);
}
#pragma exceptions reset
#pragma cplusplus off
