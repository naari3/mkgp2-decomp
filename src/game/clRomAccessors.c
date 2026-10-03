/* Observed link fields only; these are not complete SDK object layouts. */
typedef struct JObjLinkView {
    unsigned char pad00[8];
    struct JObjLinkView* next;
    unsigned char pad0C[4];
    struct JObjLinkView* child;
} JObjLinkView;

typedef struct DObjLinkView {
    unsigned char pad00[4];
    struct DObjLinkView* next;
} DObjLinkView;

extern unsigned int lbl_806D0FEC;

JObjLinkView* JObj_GetNext(JObjLinkView* self)
{
    if (self == 0) {
        return 0;
    }
    return self->next;
}

JObjLinkView* JObj_GetChild(JObjLinkView* self)
{
    if (self == 0) {
        return 0;
    }
    return self->child;
}

DObjLinkView* DObj_GetNext(DObjLinkView* self)
{
    if (self != 0) {
        return self->next;
    }
    return 0;
}

unsigned int clRom_GetActiveCount(void)
{
    return lbl_806D0FEC;
}
