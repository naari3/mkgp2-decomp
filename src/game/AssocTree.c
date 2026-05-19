void *AssocTree_GetHeaderField4(void *tree)
{
    return (char *)tree + 4;
}

void Allocator_Identity_VoidVoid(void)
{
}

asm void AssocTree_Init(char *tree, const unsigned char *flags)
{
    nofralloc
    li r5, 0x0
    lbz r4, 0x0(r4)
    stw r5, 0x0(r3)
    addi r0, r3, 0x4
    stw r5, 0x4(r3)
    stb r4, 0x8(r3)
    stw r0, 0xc(r3)
    blr
}

void Allocator_DestroyKey_Noop(void)
{
}

void Allocator_DestroyValue_Noop(void)
{
}
