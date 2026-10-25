typedef struct ZProbe {
    unsigned char active;
    unsigned short x;
    unsigned short y;
    unsigned int z;
    struct ZProbe *next;
} ZProbe;

extern ZProbe *lbl_806D16A0;
extern void GXPeekZ(unsigned short x, unsigned short y, unsigned int *z);

void fn_8018F14C(void) {
    ZProbe *p;
    for (p = lbl_806D16A0; p != 0; p = p->next) {
        p->z = 0;
        if (p->active) {
            GXPeekZ(p->x, p->y, &p->z);
        }
    }
}
