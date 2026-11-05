/* Binary-tree postorder cleanup. The allocator operations are expanded to
 * the same recursion depth as the original template instantiation. */
#include "game/AssocTreeFreeAll.h"

#define FREE_LEAF(n) do { \
    AssocNode *leaf = (n); \
    if (leaf) { \
        if (leaf->left) AssocTree_FreeAll(tree, leaf->left); \
        if (leaf->right) AssocTree_FreeAll(tree, leaf->right); \
        Allocator_DestroyEntry_Noop(Allocator_Identity_VoidVoid(tree), leaf->entry); \
        fn_80089C30(AssocTree_GetHeaderField4(tree), leaf, 1); \
    } \
} while (0)
#define FREE_BRANCH(n) do { \
    AssocNode *branch = (n); \
    if (branch) { \
        FREE_LEAF(branch->left); \
        FREE_LEAF(branch->right); \
        Allocator_Identity_VoidVoid(tree); \
        AssocTree_GetHeaderField4(tree); \
        MemoryManager_TimedFree(branch); \
    } \
} while (0)
#define FREE_SUBTREE(n) do { \
    AssocNode *subtree = (n); \
    if (subtree) { \
        FREE_BRANCH(subtree->left); \
        FREE_BRANCH(subtree->right); \
        Allocator_DestroyValue_Noop(tree); \
        Allocator_DestroyKey_Noop((char *)tree + 4); \
        MemoryManager_TimedFree(subtree); \
    } \
} while (0)
void AssocTree_FreeAll(void *tree, AssocNode *node)
{
    FREE_SUBTREE(node->left);
    FREE_SUBTREE(node->right);
    MemoryManager_TimedFree(node);
}
