extern "C" {
extern void GXDrawDone(void);
extern void PcbComm_Shutdown(void);
extern void FreeMediaBuffers(void);
extern void CardTaskManager_Dtor(void *self, int free_flag);
extern void Sci2Card_Shutdown(void);
extern void fn_80193838(void);
extern void InputMgr_Shutdown(void);
extern void StrPcb_Shutdown(void);
extern void MemoryManager_TimedFree(void *ptr);
extern void MemoryManager_Free(void *ptr);
extern void PlayStats_ShutdownStub(void);
extern void Backup_Shutdown(void);
extern void fn_80255620(void);
extern void *OSGetArenaHi(void);
extern void *memset(void *dst, int value, unsigned int size);
extern void fn_80287EE4(int, void *);

extern void *lbl_806D0F90;
extern void *lbl_806D0FC8;
extern void *lbl_806D0FD8;
extern void *lbl_806D12DC;
}

/* C++ object with a virtual deleting dtor in vtable slot 0 (+8). */
struct ShutdownObj {
    virtual void Destroy(int free_flag);
};

extern "C" {

void Game_Shutdown(void)
{
    char *arena_tail;

    GXDrawDone();
    PcbComm_Shutdown();
    FreeMediaBuffers();
    CardTaskManager_Dtor(lbl_806D0F90, 1);
    lbl_806D0F90 = 0;
    Sci2Card_Shutdown();
    fn_80193838();
    InputMgr_Shutdown();
    StrPcb_Shutdown();

    if (lbl_806D0FD8 != 0) {
        MemoryManager_TimedFree(lbl_806D0FD8);
    }

    lbl_806D0FD8 = 0;
    MemoryManager_Free(lbl_806D0FC8);
    lbl_806D0FC8 = 0;
    PlayStats_ShutdownStub();
    Backup_Shutdown();

    /* A C++ virtual call: the object stays in r3 and both vtable loads go through r12. */
    if (lbl_806D12DC != 0) {
        ((ShutdownObj *)lbl_806D12DC)->Destroy(1);
    }

    lbl_806D12DC = 0;
    fn_80255620();

    arena_tail = (char *)OSGetArenaHi() - 0x100;
    memset(arena_tail, 0, 0x100);
    *(int *)arena_tail = 1;
    fn_80287EE4(0, arena_tail);
}

}
