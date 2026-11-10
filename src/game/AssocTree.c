void *AssocTree_GetHeaderField4(void *tree)
{
    return (char *)tree + 4;
}

void *Allocator_Identity_VoidVoid(void *self)
{
    return self;
}

void AssocTree_Init(char *__restrict tree, const unsigned char *__restrict flags)
{
    *(unsigned int *)(tree + 0) = 0;
    *(unsigned int *)(tree + 4) = 0;
    tree[8] = *flags;
    *(void **)(tree + 12) = tree + 4;
}

void Allocator_DestroyKey_Noop(void)
{
}

void Allocator_DestroyValue_Noop(void)
{
}
