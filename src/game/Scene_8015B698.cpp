/* 0x8015B698..0x8015B6D0: virtual-delete thunk. */

struct VObj {
    virtual ~VObj();
};

extern "C" {

#pragma exceptions on

void fn_8015B698(VObj *p) {
    delete p;
}

#pragma exceptions reset
}
