#ifndef GAME_ASSOCTREEFREEALL_H
#define GAME_ASSOCTREEFREEALL_H
typedef struct AssocNode {
    struct AssocNode *left, *right;
    unsigned int parent;
    unsigned char entry[1];
} AssocNode;
extern void *Allocator_Identity_VoidVoid(void *);
extern void Allocator_DestroyEntry_Noop(void *, void *);
extern void *AssocTree_GetHeaderField4(void *);
extern void fn_80089C30(void *, AssocNode *, int);
extern void Allocator_DestroyValue_Noop(void *);
extern void Allocator_DestroyKey_Noop(void *);
extern void MemoryManager_TimedFree(void *);
void AssocTree_FreeAll(void *tree, AssocNode *node);

#endif
