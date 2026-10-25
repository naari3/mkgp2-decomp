class Obj {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void Draw();
};

extern "C" {
extern Obj *lbl_806D15FC;
void fn_802029EC(void);
void fn_8011FAB8(void);
void fn_80180B34(void);
void fn_8018005C(void);
void HSD_StateInvalidate(int);
}

extern "C" void fn_8017FAFC(void) {
    if (lbl_806D15FC != 0) {
        fn_802029EC();
        lbl_806D15FC->Draw();
    }
    fn_8011FAB8();
    fn_80180B34();
    if (lbl_806D15FC == 0) {
        fn_8018005C();
    }
    HSD_StateInvalidate(0x7F);
}
