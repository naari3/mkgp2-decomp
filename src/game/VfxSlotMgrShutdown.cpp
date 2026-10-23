/* Standalone pool shutdown, real C++ virtual delete. */
struct Slot { signed char active; char reserved[0x1CB]; };
class Resource { public: virtual ~Resource(); };
extern "C" { void VfxSlot_Release(void*); void fn_8022B1C8();
extern Slot lbl_805DF468[512]; extern Resource *lbl_806D14A8; }
extern "C" void VfxSlotMgr_Shutdown() {
    for(int i=0;i<512;++i) {
        Slot *slot=&lbl_805DF468[i];
        VfxSlot_Release((char*)slot+0x14);
        slot->active=0;
    }
    delete lbl_806D14A8;
    lbl_806D14A8=0;
    fn_8022B1C8();
}
