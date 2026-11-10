#include "game/types/GXTexObj.h"

extern GXTexObj BackupBuffer_InitAsTexture_bss_804FE060;
extern char g_backupBufferTexture[];
extern void GXInitTexObj(GXTexObj *, void *, unsigned short, unsigned short, int, int, int,
                        unsigned char);
extern void GXInitTexObjLOD(GXTexObj *, int, int, float, float, float, unsigned char,
                               unsigned char, int);

GXTexObj *BackupBuffer_InitAsTexture(void) {
    GXInitTexObj(&BackupBuffer_InitAsTexture_bss_804FE060, g_backupBufferTexture, 0x280, 0x1E0, 4, 0, 0, 0);
    GXInitTexObjLOD(&BackupBuffer_InitAsTexture_bss_804FE060, 0, 0, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    return &BackupBuffer_InitAsTexture_bss_804FE060;
}
