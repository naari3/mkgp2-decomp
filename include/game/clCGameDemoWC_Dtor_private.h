#ifndef DEMOWC_DTOR_PRIVATE_H
#define DEMOWC_DTOR_PRIVATE_H
struct DemoWCVirtual { virtual void Destroy(int); };
struct DemoWCDtorView {
    void *vptr;
    unsigned char unknown04[8];
    DemoWCVirtual *camera;
    int owner;
    void *object, *driver, *effects;
    unsigned char unknown20[0x38];
    DemoWCVirtual *other;
};
#endif
