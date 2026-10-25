typedef struct ZProbe {
    unsigned char active;
    unsigned short x;
    unsigned short y;
    unsigned int z;
    struct ZProbe *next;
} ZProbe;

extern ZProbe *lbl_806D16A0;
extern void MemoryManager_TimedFree(void *p);

ZProbe *dtor_8018F088(ZProbe *self, short flag) {
    ZProbe *it;
    if (self != 0) {
        if (lbl_806D16A0 == self) {
            lbl_806D16A0 = self->next;
        } else {
            for (it = lbl_806D16A0; it->next != self; it = it->next) {
            }
            it->next = self->next;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
