// Narrow target-derived views for the derived material TEV callback.
struct Tev;
struct MObj1View { unsigned char base[0x20]; unsigned char* color; };
struct MObj1ClassView { unsigned char base[0x44]; Tev* (*tevInit)(MObj1View*, void*, void*); unsigned char tail[0xc]; };
extern "C" {
extern MObj1ClassView lbl_803F5888, lbl_803F5834;
extern const char lbl_802E9CC8[], lbl_802E9CDC[];
void hsdInitClassInfo(MObj1ClassView*, MObj1ClassView*, const char*, const char*, unsigned int, unsigned int);
Tev* fn_802DF044(unsigned char*, int, int, void*);
Tev* fn_802DEF84(void*);
void fn_802DFEF4(Tev*, int, int);
void fn_802DF164(Tev*, int, int, int, int);
void fn_802DF8EC(Tev*, int, Tev*, int, int, int, Tev*, int, Tev*);
void fn_802DF24C(Tev*, int, int, int, int);
void fn_802DFDEC(Tev*, int, Tev*, int, int, int, Tev*, int, Tev*);
Tev* MObj1_TEVStateInit(MObj1View*, void*, void*);
void MObj1_ClassInit(void) {
    hsdInitClassInfo(&lbl_803F5888, &lbl_803F5834, lbl_802E9CC8, lbl_802E9CDC, 0x54, 0x24);
    lbl_803F5888.tevInit = MObj1_TEVStateInit;
}
Tev* MObj1_TEVStateInit(MObj1View* self, void* arg, void* list) {
    Tev* parent = lbl_803F5834.tevInit(self, arg, list);
    Tev* color = fn_802DF044(self->color, 1, 0, list);
    Tev* result;
    Tev* alpha = fn_802DF044(self->color + 3, 6, 0, list);
    result = fn_802DEF84(list);
    fn_802DFEF4(result, 0, 4);
    fn_802DF164(result, 1, 0, 1, 1);
    fn_802DF8EC(result, 1, parent, 7, 0, 1, color, 1, parent);
    fn_802DF24C(result, 1, 0, 0, 1);
    fn_802DFDEC(result, 5, parent, 7, 0, 5, alpha, 5, parent);
    return result;
}
}
