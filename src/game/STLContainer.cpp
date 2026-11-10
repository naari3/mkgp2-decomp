#include "game/STLContainerPrivate.h"

void *operator new(unsigned long);
void operator delete(void *);
extern "C" {
void MemoryManager_TimedFree(void *);
void MemoryManager_Free(void *);
void Stub_NoOp_38f54(void *);
void Stub_NoOp_38f58(void *);
void Stub_NoOp_38f80(void *, void *);
void Allocator_Deallocate(void *, void *, int);
void *STLContainer_GetAllocatorSlot(STLTree *);
void *Stub_NoOp_38dd0(STLTree *);
extern const char lbl_802E98D0[];
}

extern "C" void STLContainer_HeaderInit(STLTree *, const STLPolicy *, const STLCompare *);
inline STLTree::STLTree()
{
    STLPolicy policy;
    STLCompare compare;
    STLContainer_HeaderInit(this, &policy, &compare);
}
extern "C" void __register_global_object(void *obj, void *dtor, void *chain);
extern "C" void STLContainer_Dtor(void *, int);
static char sDtorChain[12];
extern "C" { int STLContainer_GlobalInit_854_bss_80598554[sizeof(STLTree) / 4]; }
#pragma push
extern "C" void STLContainer_GlobalInit_854()
{
    STLCompare compare;
    STLPolicy policy;
    STLContainer_HeaderInit((STLTree *)STLContainer_GlobalInit_854_bss_80598554, &policy, &compare);
    __register_global_object(STLContainer_GlobalInit_854_bss_80598554, (void *)STLContainer_Dtor, sDtorChain);
}
#pragma pop
__declspec(section ".ctors") static void (*const sInitEntry)(void) = STLContainer_GlobalInit_854;


#pragma dont_inline on
extern "C" void STLContainer_HeaderInit(STLTree *tree, const STLPolicy *p, const STLCompare *)
{
    tree->count = 0;
    unsigned char tag = p->tag;
    tree->root = 0;
    tree->policy = tag;
    tree->header = &tree->root;
}

#pragma dont_inline reset
STLTree::~STLTree()
{
    if (this) {
        if (root) dispose(root);
    }
}

static inline void DisposeLeaf(STLTree *tree, STLNode *node)
{
    if (node->left) tree->dispose(node->left);
    if (node->right) tree->dispose(node->right);
    Stub_NoOp_38f80(Stub_NoOp_38dd0(tree), node->value);
    Allocator_Deallocate(STLContainer_GetAllocatorSlot(tree), node, 1);
}
static inline void DisposeMiddle(STLTree *tree, STLNode *node)
{
    if (node->left) DisposeLeaf(tree, node->left);
    if (node->right) DisposeLeaf(tree, node->right);
    Stub_NoOp_38dd0(tree);
    STLContainer_GetAllocatorSlot(tree);
    MemoryManager_TimedFree(node);
}
static inline void DisposeBranch(STLTree *tree, STLNode *__restrict node)
{
    if (node->left) DisposeMiddle(tree, node->left);
    if (node->right) DisposeMiddle(tree, node->right);
    Stub_NoOp_38f58(tree);
    Stub_NoOp_38f54(&tree->root);
    MemoryManager_TimedFree(node);
}
void STLTree::dispose(STLNode *node)
{
    STLTree *tree = this;
    if (node->left) DisposeBranch(tree, node->left);
    if (node->right) DisposeBranch(tree, node->right);
    MemoryManager_TimedFree(node);
}
extern "C" void *STLContainer_GetAllocatorSlot(STLTree *tree) { return &tree->root; }
extern "C" void *Stub_NoOp_38dd0(STLTree *tree) { return tree; }
PcbBase::~PcbBase() {}
extern "C" const char *fn_80038E1C() { return lbl_802E98D0; }
extern "C" unsigned int *fn_80038E28(SharedPtr *self) { return self->count; }
SharedPtr::~SharedPtr()
{
    if (count && --*count == 0) {
        MemoryManager_Free(value);
        operator delete(count);
    }
}
SharedPtr::SharedPtr(void *p) : value(p), count(0)
{
    try {
        if (value) count = new unsigned int(1);
    } catch (...) {
        MemoryManager_Free(value);
        throw;
    }
}
