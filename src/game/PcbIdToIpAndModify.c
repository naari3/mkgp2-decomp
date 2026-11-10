/*
 * PcbIdToIpAndModify, 0x80073F6C..0x800740BC.
 */

#include "game/types/PcbIpEntry.h"

#include "game/types/SmallObj.h"

extern const char lbl_80310DE0[]; /* string pool */
extern PcbIpEntry g_pcbIpTable[4];
extern signed char lbl_80598A60[0x2A];
extern unsigned char lbl_806D1120;

void DebugPrintf(const char *fmt, ...);
void MemoryManager_TimedFree(void *p);
int acModifyMyIPaddr(unsigned int ip, unsigned int mask);

#pragma exceptions on

int PcbIdToIpAndModify(int id)
{
    const char *strings = lbl_80310DE0;
    int result;

    if (lbl_806D1120 == 0) {
        return 0;
    }
    if (id > 4) {
        return 0;
    }
    if (id <= 0) {
        id = lbl_80598A60[0x21];
    }
    DebugPrintf(strings + 0x4D0, g_pcbIpTable[id - 1].ip);
    result = acModifyMyIPaddr(g_pcbIpTable[id - 1].ip, 0xFFFFFF00);
    DebugPrintf(strings + 0x500, id, result, g_pcbIpTable[id - 1].ip);
    if (result == 0) {
        DebugPrintf(strings + 0x540);
    }
    if (result == -1) {
        DebugPrintf(strings + 0x560);
    }
    if (result == -2) {
        DebugPrintf(strings + 0x58C);
    }
    if (result == -3) {
        DebugPrintf(strings + 0x5E4);
    }
    if (result == -4) {
        DebugPrintf(strings + 0x620);
    }
    if (result == -6) {
        DebugPrintf(strings + 0x64C);
    }
    DebugPrintf(strings + 0x688, result);
    return 1;
}

#pragma exceptions reset
