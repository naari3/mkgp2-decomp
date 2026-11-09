/* Binary-tree postorder cleanup (same shape as the matched
 * STLContainer_DisposeRecursive): the allocator operations are expanded to
 * the recursion depth of the original template instantiation. */
#include "game/AssocTreeFreeAll.h"

static inline void FreeLeaf(void *tree, AssocNode *node)
{
    if (node->left) AssocTree_FreeAll(tree, node->left);
    if (node->right) AssocTree_FreeAll(tree, node->right);
    Allocator_DestroyEntry_Noop(Allocator_Identity_VoidVoid(tree), node->entry);
    fn_80089C30(AssocTree_GetHeaderField4(tree), node, 1);
}
static inline void FreeBranch(void *tree, AssocNode *node)
{
    if (node->left) FreeLeaf(tree, node->left);
    if (node->right) FreeLeaf(tree, node->right);
    Allocator_Identity_VoidVoid(tree);
    AssocTree_GetHeaderField4(tree);
    MemoryManager_TimedFree(node);
}
static inline void FreeSubtree(void *tree, AssocNode *__restrict node)
{
    if (node->left) FreeBranch(tree, node->left);
    if (node->right) FreeBranch(tree, node->right);
    Allocator_DestroyValue_Noop(tree);
    Allocator_DestroyKey_Noop((char *)tree + 4);
    MemoryManager_TimedFree(node);
}
void AssocTree_FreeAll(void *tree, AssocNode *node)
{
    if (node->left) FreeSubtree(tree, node->left);
    if (node->right) FreeSubtree(tree, node->right);
    MemoryManager_TimedFree(node);
}
