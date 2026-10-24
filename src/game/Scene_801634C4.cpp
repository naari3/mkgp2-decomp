/* 0x801634C4..0x80163554: draw / update forwarders of a loader holder. */

struct Holder801634C4 {
    void *vtable;
    void *child;
    unsigned char done;
};

extern "C" {
extern void fn_80163C68(void *);
extern unsigned char fn_80163EF4(void *);

#pragma exceptions on

void fn_801634C4(Holder801634C4 *self) {
    if (!self->done && self->child) {
        fn_80163C68(self->child);
    }
}

void fn_801634FC(Holder801634C4 *self) {
    if (!self->done && self->child) {
        if (fn_80163EF4(self->child) == 1) {
            self->done = 1;
        }
    }
}

#pragma exceptions reset
}
