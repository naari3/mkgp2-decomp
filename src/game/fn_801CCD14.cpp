/* Ticks every active entry in an intrusive list. */
class ListEntryfn_801CCD14 {
public:
    virtual void v8();
    virtual void vC();
    virtual void Update();

    void *anim;
    char pad_8[0x7C];
    unsigned char active;
    unsigned char mode;
};

struct ListNodefn_801CCD14 {
    ListNodefn_801CCD14 *prev;
    ListNodefn_801CCD14 *next;
    ListEntryfn_801CCD14 *entry;
};

struct Ownerfn_801CCD14 {
    char pad_0[8];
    ListNodefn_801CCD14 head;
};

extern "C" {
void fn_801A0004(void *anim);
void fn_8011FAB8(void);
}

extern "C" void fn_801CCD14(Ownerfn_801CCD14 *self) {
    ListEntryfn_801CCD14 *e;
    ListNodefn_801CCD14 *node;
    ListNodefn_801CCD14 *end;

    end = &self->head;
    for (node = self->head.next; node != end; node = node->next) {
        e = node->entry;
        if (e->active) {
            if (e->anim != 0) {
                fn_801A0004(e->anim);
            }
            e->Update();
            if (e->mode == 1) {
                fn_8011FAB8();
            }
        }
    }
}
