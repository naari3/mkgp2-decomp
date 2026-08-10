/*
 * SceneFlow cleanup state helpers @ 0x8003B2D8 - 0x8003B314.
 *
 * The cleanup list consists of the two sentinel nodes in BSS.
 */

typedef struct SceneCleanupNode {
    struct SceneCleanupNode *next;
    struct SceneCleanupNode *prev;
    char _pad8[0xC];
} SceneCleanupNode;

extern SceneCleanupNode lbl_805987B8;
extern SceneCleanupNode lbl_805987CC;
extern int lbl_806D1040;
extern unsigned char lbl_806D1048;

int SceneFlow_DefaultGetZero(void) {
    return 0;
}

void SceneFlow_SetCleanupTag(int tag) {
    lbl_806D1040 = tag;
}

void SceneFlow_InitCleanupList(void) {
    SceneCleanupNode *first = &lbl_805987B8;
    SceneCleanupNode *last = &lbl_805987CC;

    first->next = 0;
    first->prev = last;
    last->next = first;
    last->prev = 0;
}

void SceneFlow_SetFlag1048(unsigned char flag) {
    lbl_806D1048 = flag;
}
