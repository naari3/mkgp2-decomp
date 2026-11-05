#ifndef OBJVIEW_S22_PRIVATE_H
#define OBJVIEW_S22_PRIVATE_H
struct clNormal3D {
    unsigned char data[0x5c];
    clNormal3D(const char *, int);
};
struct S22Base {
    S22Base() {}
    virtual ~S22Base();
};
#endif
