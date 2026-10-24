/* 0x8015BED4..0x8015BF18: forward a draw call to the child object unless disabled. */

struct Child {
    virtual ~Child();
    virtual void Update();
    virtual void Draw();
};

struct Owner {
    void *vtable;
    unsigned char disabled;
    char pad[0xB];
    Child *child;
};

extern "C" {

#pragma exceptions on

void fn_8015BED4(Owner *self) {
    if (!self->disabled && self->child) {
        self->child->Draw();
    }
}

#pragma exceptions reset
}
