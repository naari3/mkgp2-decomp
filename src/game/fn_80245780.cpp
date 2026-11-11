extern "C" void fn_80120A08(int);
extern "C" void PreloadResource(int);
extern "C" const float lbl_806DBEDC;

class clMslDisp {
public:
    virtual ~clMslDisp();
    clMslDisp();
    unsigned char flag;
    float x, y;
};

clMslDisp::~clMslDisp() {
    fn_80120A08(0x1CB6);
}

clMslDisp::clMslDisp() {
    flag = 0;
    x = lbl_806DBEDC;
    y = lbl_806DBEDC;
    PreloadResource(0x1CB6);
}
