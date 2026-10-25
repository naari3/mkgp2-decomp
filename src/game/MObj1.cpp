// Narrow target-derived views for the derived material TEV callback.
struct Tev;
struct MObj1View { unsigned char base[0x20]; unsigned char* color; };
struct MObj1ClassView { unsigned char base[0x44]; Tev* (*tevInit)(MObj1View*, void*, void*); unsigned char tail[0xc]; };
extern "C" {
extern MObj1ClassView lbl_803F5888, lbl_803F5834;
extern const char lbl_802E9CC8[], lbl_802E9CDC[];
void hsdInitClassInfo(MObj1ClassView*, MObj1ClassView*, const char*, const char*, unsigned int, unsigned int);
Tev* HSD_TExpCnst(unsigned char*, int, int, void*);
Tev* HSD_TExpTev(void*);
void HSD_TExpOrder(Tev*, int, int);
void HSD_TExpColorOp(Tev*, int, int, int, int);
void HSD_TExpColorIn(Tev*, int, Tev*, int, int, int, Tev*, int, Tev*);
void HSD_TExpAlphaOp(Tev*, int, int, int, int);
void HSD_TExpAlphaIn(Tev*, int, Tev*, int, int, int, Tev*, int, Tev*);
Tev* MObj1_TEVStateInit(MObj1View*, void*, void*);
void MObj1_ClassInit(void) {
    hsdInitClassInfo(&lbl_803F5888, &lbl_803F5834, lbl_802E9CC8, lbl_802E9CDC, 0x54, 0x24);
    lbl_803F5888.tevInit = MObj1_TEVStateInit;
}
Tev* MObj1_TEVStateInit(MObj1View* self, void* arg, void* list) {
    Tev* parent = lbl_803F5834.tevInit(self, arg, list);
    Tev* color = HSD_TExpCnst(self->color, 1, 0, list);
    Tev* result;
    Tev* alpha = HSD_TExpCnst(self->color + 3, 6, 0, list);
    result = HSD_TExpTev(list);
    HSD_TExpOrder(result, 0, 4);
    HSD_TExpColorOp(result, 1, 0, 1, 1);
    HSD_TExpColorIn(result, 1, parent, 7, 0, 1, color, 1, parent);
    HSD_TExpAlphaOp(result, 1, 0, 0, 1);
    HSD_TExpAlphaIn(result, 5, parent, 7, 0, 5, alpha, 5, parent);
    return result;
}
}
