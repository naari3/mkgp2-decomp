#ifndef GAME_STLCONTAINER_PRIVATE_H
#define GAME_STLCONTAINER_PRIVATE_H
struct STLNode { STLNode *left, *right; unsigned int state; unsigned char value[4]; };
struct STLPolicy { unsigned char tag; STLPolicy() {} };
struct STLCompare { STLCompare() {} };
struct STLTree {
    unsigned int count;
    STLNode *root;
    unsigned char policy;
    void *header;
    unsigned int end;
    STLTree();
    ~STLTree();
    void dispose(STLNode *);
};
struct PcbBase {
    virtual void key();
    virtual ~PcbBase();
};
struct SharedPtr {
    void *value;
    unsigned int *count;
    SharedPtr(void *);
    ~SharedPtr();
};
#endif
