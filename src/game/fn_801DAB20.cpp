/* clAdjustment: compiler-owned vtable and RTTI. */
void operator delete(void *) throw();
extern "C" void fn_80121210(void);
extern "C" void PreloadResource(int);

class clAdjustment {
public:
    virtual ~clAdjustment();
    clAdjustment(int value);
    int count;
    int arg;
};

extern "C" const int resourceIds[4] = {0, 1, 3, 2};

clAdjustment::~clAdjustment() {
    fn_80121210();
}

clAdjustment::clAdjustment(int value) {
    count = 4;
    arg = value;
    for (int i = 0; i < count; ++i) {
        PreloadResource(resourceIds[i]);
    }
}
