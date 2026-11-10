#include "game/types/ClStreamSlot.h"
typedef struct ClBgmFiles { const char* left; const char* right; } ClBgmFiles;
extern unsigned char ClSound_Initialized;
extern ClStreamSlot ClSound_ActiveStreams[4];
extern const unsigned char ClSound_rodata_80379100[];
extern void DebugPrintf(const char*, ...);
extern unsigned char ClStream_Stop(unsigned int);
extern unsigned char ClStream_IsActive(unsigned int);
extern unsigned int ClStream_PlayStereo(const char*, const char*, unsigned int);
extern unsigned int ClStream_PlayMono(const char*, unsigned int, unsigned int);
static inline unsigned char StopBgm(unsigned int id, const unsigned char* resources) {
    int i;
    if (!ClSound_Initialized) return 1;
    for (i=0;i<4;i++) {
        if (ClSound_ActiveStreams[i].handle != -1 && id==ClSound_ActiveStreams[i].id) {
            if (!ClStream_Stop(ClSound_ActiveStreams[i].handle)) {
                DebugPrintf((const char*)resources+0x3e50,ClSound_ActiveStreams[i].handle);
                return 0;
            }
            ClSound_ActiveStreams[i].handle=-1;
        }
    }
    return 1;
}
int ClSound_PlayBgmStream(unsigned int id, unsigned int arg) {
    const unsigned char* resources=ClSound_rodata_80379100;
    int i;
    const ClBgmFiles* files;
    if (!ClSound_Initialized) return 0;
    if (id>=21) return 0;
    if (!StopBgm(id,resources)) return 0;
    for (i=0;i<4;i++) {
        if (ClSound_ActiveStreams[i].handle != -1) {
            if (ClStream_IsActive(ClSound_ActiveStreams[i].handle)) continue;
            ClSound_ActiveStreams[i].handle=-1;
        }
        files=(const ClBgmFiles*)(resources+0x3d1c);
        if (files[id].right) {
            ClSound_ActiveStreams[i].handle=ClStream_PlayStereo(files[id].left,files[id].right,arg);
        } else {
            ClSound_ActiveStreams[i].handle=ClStream_PlayMono(files[id].left,arg,0);
        }
        ClSound_ActiveStreams[i].id=id;
        if (ClSound_ActiveStreams[i].handle != -1) return 1;
        DebugPrintf((const char*)resources+0x3e98,id);
        return 0;
    }
    DebugPrintf((const char*)resources+0x3ec4,id);
    return 0;
}
