extern void __register_global_object(void *obj, void *dtor, void *link);
extern void fn_801F6804(void *obj);
extern void dtor_80080330(void);
extern char lbl_806796F0[];
extern char lbl_806796FC[];

void fn_801F89F0(void) {
    fn_801F6804(lbl_806796FC);
    __register_global_object(lbl_806796FC, dtor_80080330, lbl_806796F0);
}

__declspec(section ".ctors") static void (*const s_fn_801F89F0_ctor)(void) = fn_801F89F0;
