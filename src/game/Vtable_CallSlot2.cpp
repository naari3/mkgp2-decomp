struct VtableSlot2 {
    virtual void f0();
};

#pragma exceptions on
extern "C" void Vtable_CallSlot2(VtableSlot2 *self) {
    self->f0();
}
#pragma exceptions reset
