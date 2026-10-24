/* 0x8015BE0C..0x8015BE44: virtual-delete thunk. */

struct VObj {
    virtual ~VObj();
};

extern "C" {

#pragma exceptions on

void fn_8015BE0C(VObj *p) {
    delete p;
}

#pragma exceptions reset
}
