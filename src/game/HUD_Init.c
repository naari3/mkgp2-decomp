/* Constructor-only observed lifetime views; no complete HUD class claimed.
 * Nontrivial owner and new expression generate the original cleanup actions. */
#pragma cplusplus on
void *operator new(unsigned long);
void operator delete(void *);
extern "C" {
void DoublyLinkedList_Init(void *list);
void *memset(void *destination, int value, unsigned long size);
void fn_801477BC(void);
void fn_80149CD8(void);
void fn_8020E3AC(void);
void fn_80215708(void);
void fn_80215DB0(void);
void fn_80217E9C(void);
void fn_8021819C(void);
void fn_8022B9B0(void);
void fn_80243958(void);
void fn_802512AC(void);
void fn_802518C8(void);
void fn_80252D6C(void);
extern int g_cupId;
extern int g_gameMode;
extern const float lbl_806DC1DC;
extern const float lbl_806DC1E0;
}

struct HUDListBase {
    virtual void key();
    unsigned int list[3];
    HUDListBase() { DoublyLinkedList_Init(list); }
};
struct HUDList : HUDListBase {
    virtual void key();
    HUDList() {}
};
struct HUDListOwner {
    HUDList *pointer;
    HUDListOwner(HUDList *p) : pointer(p) {}
    ~HUDListOwner() throw();
};
struct HUDInitView {
    HUDListOwner owner;
    int field04;
    int field08;
    int mode;
    unsigned char entries[0x5c];
    int field6c;
    float field70;
    float field74;
    float field78;
    int field7c;
    HUDInitView(int);
};

HUDInitView::HUDInitView(int value) : owner(new HUDList)
{
    field04 = 3;
    field08 = 5;
    mode = value;
    field6c = 0;
    field70 = lbl_806DC1DC;
    field78 = lbl_806DC1E0;
    field74 = lbl_806DC1E0;
    field7c = -1;
    memset(entries, 0, sizeof(entries));
    if (g_cupId >= 9 && g_cupId <= 16) {
        fn_802518C8();
        fn_80217E9C();
        fn_8021819C();
        fn_801477BC();
    } else {
        fn_802512AC();
        fn_802518C8();
        fn_80215708();
        fn_8020E3AC();
        fn_8022B9B0();
        fn_80252D6C();
        fn_80243958();
        fn_80215DB0();
    }
    if (g_gameMode == 2) {
        fn_80149CD8();
    }
}
#pragma cplusplus off
