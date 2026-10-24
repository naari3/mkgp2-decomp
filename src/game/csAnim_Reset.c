/*
 * clCSAnim (csAnim.cpp): out-of-line Reset, 0x8013BA78.
 * See csAnim.c; the same body is inlined into the callers there.
 */

typedef struct CSAnimHead {
    int id;
    void *next;
    int flags;
    int frame;
    int index;
} CSAnimHead;

void fn_8013BA78(CSAnimHead *n) {
    n->flags = 2;
    n->frame = 0;
    n->index = 0;
}
