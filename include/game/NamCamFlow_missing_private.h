#ifndef GAME_NAMCAMFLOW_MISSING_PRIVATE_H
#define GAME_NAMCAMFLOW_MISSING_PRIVATE_H
extern "C" {
void *memcpy(void *, const void *, unsigned long);
void DCFlushRange(void *, unsigned long);
unsigned long GXGetTexBufferSize(unsigned short, unsigned short, unsigned long, unsigned char, unsigned char);
void GXInitTexObj(void *, void *, unsigned short, unsigned short, int, int, int, unsigned char);
void GXInitTexObjLOD(void *, int, int, float, float, float, unsigned char, unsigned char, int);
void GXLoadTexObj(void *, int);
void GXTexModeSync();
void GXSetZCompLoc(unsigned char);
void GXSetZMode(unsigned char, int, unsigned char);
void GXSetNumTexGens(unsigned char);
void GXSetTexCoordGen2(int, int, int, unsigned long, unsigned char, unsigned long);
void GXSetNumChans(unsigned char);
void GXSetNumTevStages(unsigned char);
void GXSetTevOrder(int, int, int, int);
void GXSetTevOp(int, int);
void GXClearVtxDesc();
void GXSetVtxAttrFmt(int, int, int, int, unsigned char);
void GXSetVtxDesc(int, int);
void GXSetArray(int, void *, unsigned char);
void GXBegin(int, int, unsigned short);
}

static inline void NamCamPosition(short x, short y) {
    *(volatile short *)0xCC008000 = x;
    *(volatile short *)0xCC008000 = y;
}
static inline void NamCamTexCoord(unsigned char index) {
    *(volatile unsigned char *)0xCC008000 = index;
}

extern "C" {
struct NamCamSettings { char pad[0x48]; int height, width; };
extern NamCamSettings lbl_80598A60;
struct NamCamSyncState { char pad[8]; int state; };
NamCamSyncState *fn_801DAEC0();
unsigned char IsSyncReached();
void GX_BeginDraw();
void GX_EndDraw(int);
void *GetDisplayContext(int);
void DrawNamCamImage(void *, void *, int, int, int,
    unsigned short, unsigned short, unsigned short, unsigned short, int, int, int);
void ResetIOPorts();
int NamCam_GetImageHandle(void **, int);
int NamCam_LoadImage(void *, void *, void *);
extern int NamCamFlow_bss_806D1960;
extern signed char NamCamFlow_bss_806D1964;
extern const float lbl_806DA580, lbl_806DA584, lbl_806DA58C;
extern const float lbl_806DA5B4, lbl_806DA5B8, lbl_806DA5BC, lbl_806DA5C0;
extern const float lbl_806DA5E0, lbl_806DA5E4, lbl_806DA5E8, lbl_806DA5EC;
extern const float lbl_806DA5F0, lbl_806DA5F4, lbl_806DA5F8;
#ifdef __MWERKS__ /* elsewhere kNamCamBorderA/B are defined under these names (NamCamFlow_layout_private.h) */
extern const float NamCamFlow_rodata_803BE3C4[4][2], NamCamFlow_rodata_803BE3E4[4][2];
#endif
extern short NamCamFlow_data_804E52E0[8], NamCamFlow_data_804E52C0[8];
extern short NamCamFlow_data_806D0010, NamCamFlow_data_806D0012;
extern float NamCamFlow_data_806D0014;
void fn_801F6804(void *);
void fn_801F6588(int);
void fn_801F6790(void *);
void fn_801F32BC(NamCamFlow *);
void fn_801F36D0(NamCamFlow *);
void fn_801F3198(NamCamFlow *);
ListIter DoublyLinkedList_EraseRange(void *, const ListIter &, const ListIter &);
}

struct NamCamListStorage {
    int count;
    ListNode *last, *first;
    void EraseAll() {
        ListNode *end = (ListNode *)&last;
        DoublyLinkedList_EraseRange(this, ListIter(end->next), ListIter(end));
    }
    ~NamCamListStorage() { EraseAll(); }
};
struct NamCamListBase : NamCamListStorage { ~NamCamListBase() {} };
struct NamCamListEntries : NamCamListBase { ~NamCamListEntries() {} };
struct NamCamList {
    virtual void _key();
    virtual ~NamCamList();
    NamCamListEntries entries;
};
struct NamCamListImpl : NamCamList {
    virtual void _key2();
    ~NamCamListImpl();
};
#endif
