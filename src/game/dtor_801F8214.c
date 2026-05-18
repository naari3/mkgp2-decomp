extern void dtor_8003AFB8(void *this);

#pragma exceptions on
void *dtor_801F8214(void *this, short flag) {
    if (this != 0 && flag > 0) {
        dtor_8003AFB8(this);
    }
    return this;
}
#pragma exceptions reset
