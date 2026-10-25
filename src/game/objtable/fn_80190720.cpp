struct Singleton {
    unsigned char data[8];
    Singleton();
};

extern Singleton *lbl_806D16A8;

extern "C" void fn_80190720(void) {
    if (lbl_806D16A8 == 0) {
        lbl_806D16A8 = new Singleton();
    }
}
