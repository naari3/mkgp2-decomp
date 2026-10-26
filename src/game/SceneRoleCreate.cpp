/* Target-observed allocation size; no live Ghidra type lookup performed. */
void *operator new(unsigned long);
void operator delete(void *) throw();

struct SceneRoleAlloc {
    unsigned char body[0x14];
    SceneRoleAlloc();
};

extern "C" SceneRoleAlloc *fn_8024D140()
{
    return new SceneRoleAlloc;
}
