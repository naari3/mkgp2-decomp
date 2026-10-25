extern const float lbl_806D2F20;
extern const float lbl_806D2F24;

typedef struct DrawNode {
    struct DrawNode *a;
    struct DrawNode *b;
    float z;
    struct DrawNode *prev;
    struct DrawNode *next;
} DrawNode;

typedef struct DrawNodeList {
    DrawNode head;
    DrawNode tail;
} DrawNodeList;

static inline void DrawNode_Init(DrawNode *n)
{
    n->a = 0;
    n->b = 0;
    n->z = lbl_806D2F24;
    n->prev = 0;
    n->next = 0;
}

/* 0x80079C48 */
void fn_80079C48(DrawNode *n)
{
    DrawNode_Init(n);
}

/* 0x80079C68: init a sorted list with head and tail sentinels. */
void fn_80079C68(DrawNodeList *l)
{
    DrawNode_Init(&l->head);
    DrawNode_Init(&l->tail);
    DrawNode_Init(&l->head);
    DrawNode_Init(&l->tail);
    l->head.z = lbl_806D2F20;
    l->tail.z = lbl_806D2F24;
    l->head.next = &l->tail;
    l->tail.prev = &l->head;
}
