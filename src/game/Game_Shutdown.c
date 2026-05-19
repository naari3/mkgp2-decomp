extern void GX_DrawDoneAndWait(void);
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

void Game_Shutdown(void)
{
    char *arena_tail;

    GX_DrawDoneAndWait();
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

    /*
     * Pseudo-C:
     *
     *   if (lbl_806D12DC != 0) {
     *       void **obj = (void **)lbl_806D12DC;
     *       void (**vtable)(void *, int) = (void (**)(void *, int))obj[0];
     *       vtable[2](lbl_806D12DC, 1);
     *   }
     *
     * The natural C form emits the same call but uses an extra temporary GPR
     * for the vtable load. Target keeps the object in r3 and routes both
     * vtable loads through r12, so pin this small virtual-call sequence.
     */
    asm {
        opword 0x806DA5BC
        opword 0x28030000
        opword 0x41820018
        opword 0x81830000
        opword 0x38800001
        opword 0x818C0008
        opword 0x7D8903A6
        opword 0x4E800421
    }

    lbl_806D12DC = 0;
    fn_80255620();

    arena_tail = (char *)OSGetArenaHi() - 0x100;
    memset(arena_tail, 0, 0x100);
    *(int *)arena_tail = 1;
    fn_80287EE4(0, arena_tail);
}
