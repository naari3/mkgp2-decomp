// Narrow target-derived views: HSD callback at +0x40, material field at +0x20.
struct MObjView { unsigned char base[0x20]; unsigned int field20; };
#include "game/types/MObjClassView.h"
extern "C" {
extern MObjClassView MObj_data_803F5834, hsdMObj;
extern const char lbl_802E9CC8[], lbl_802E9CEC[];
extern unsigned int lbl_806D1038[2];
void hsdInitClassInfo(MObjClassView*, MObjClassView*, const char*, const char*, unsigned int, unsigned int);
int MObj_InitMember(MObjView*, void*);
void MObj_ClassInit(void) {
    hsdInitClassInfo(&MObj_data_803F5834, &hsdMObj, lbl_802E9CC8, lbl_802E9CEC, 0x54, 0x24);
    MObj_data_803F5834.load = MObj_InitMember;
}
int MObj_InitMember(MObjView* self, void* arg) {
    int result = hsdMObj.load(self, arg);
    if (result != 0) return result;
    self->field20 = lbl_806D1038[0];
    return 0;
}
}
