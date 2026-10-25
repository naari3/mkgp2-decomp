// Narrow target-derived views: HSD callback at +0x40, material field at +0x20.
struct MObjView { unsigned char base[0x20]; unsigned int field20; };
struct MObjClassView { unsigned char base[0x40]; int (*initMember)(MObjView*, void*); unsigned char tail[0x10]; };
extern "C" {
extern MObjClassView lbl_803F5834, lbl_804FC1C0;
extern const char lbl_802E9CC8[], lbl_802E9CEC[];
extern unsigned int lbl_806D1038[2];
void hsdInitClassInfo(MObjClassView*, MObjClassView*, const char*, const char*, unsigned int, unsigned int);
int MObj_InitMember(MObjView*, void*);
void MObj_ClassInit(void) {
    hsdInitClassInfo(&lbl_803F5834, &lbl_804FC1C0, lbl_802E9CC8, lbl_802E9CEC, 0x54, 0x24);
    lbl_803F5834.initMember = MObj_InitMember;
}
int MObj_InitMember(MObjView* self, void* arg) {
    int result = lbl_804FC1C0.initMember(self, arg);
    if (result != 0) return result;
    self->field20 = lbl_806D1038[0];
    return 0;
}
}
