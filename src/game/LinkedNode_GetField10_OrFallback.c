void *LinkedNode_GetField10_OrFallback(void *self, void *target)
{
    if (target == 0) {
        target = *(void **)((char *)self + 0x2C);
    }
    if (target == 0) {
        return 0;
    }
    return *(void **)((char *)target + 0x10);
}
