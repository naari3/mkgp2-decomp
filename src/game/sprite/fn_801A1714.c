extern void ResCtrl_Init(void *);
extern void __register_global_object(void *, void *, void *);
extern void fn_801A175C(void);
extern char lbl_8067897C[];
extern char lbl_80678970[];

void fn_801A1714(void) {
    ResCtrl_Init(lbl_8067897C + 0x38);
    __register_global_object(lbl_8067897C, fn_801A175C, lbl_80678970);
}

__declspec(section ".ctors") static void (*const sprite_ctor)(void) = fn_801A1714;
