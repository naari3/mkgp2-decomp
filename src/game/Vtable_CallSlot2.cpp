struct VtableSlot2 {
    virtual int f0();
};

#pragma exceptions on
extern "C" int Vtable_CallSlot2(VtableSlot2 *self) {
    return self->f0();
}
#pragma exceptions reset
