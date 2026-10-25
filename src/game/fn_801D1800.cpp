/* Ticks every active entry in an intrusive list. */
class ListEntryfn_801D1800 {
public:
    virtual void v8();
    virtual void vC();
    virtual void Update();

    void *anim;
    char pad_8[0x7C];
    unsigned char active;
    unsigned char mode;
};

struct ListNodefn_801D1800 {
    ListNodefn_801D1800 *prev;
    ListNodefn_801D1800 *next;
    ListEntryfn_801D1800 *entry;
};

struct Ownerfn_801D1800 {
    char pad_0[0xC];
    ListNodefn_801D1800 head;
};

extern "C" {
void fn_801A0004(void *anim);
void fn_8011FAB8(void);
}

extern "C" void fn_801D1800(Ownerfn_801D1800 *self) {
    ListEntryfn_801D1800 *e;
    ListNodefn_801D1800 *node;
    ListNodefn_801D1800 *end;

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
