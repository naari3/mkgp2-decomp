/* PCB id to IP address lookups, 0x800740BC..0x80074190. */

typedef struct PcbIpEntry {
    unsigned int ip;
    const char *text;
} PcbIpEntry;

extern PcbIpEntry g_pcbIpTable[4];
extern signed char lbl_80598A60[0x2A];
extern unsigned char lbl_806D1120;
extern unsigned int fn_80292934(unsigned int ip);

static inline int PcbIdToIp_ResolveId(int id)
{
    if (id <= 0) {
        id = lbl_80598A60[0x21];
    }
    return id;
}

#pragma exceptions on
unsigned int PcbIdToIp_GetCached(int id)
{
    unsigned int ip;

    if (lbl_806D1120 == 0) {
        ip = 0;
    } else if (id > 4) {
        ip = 0;
    } else {
        ip = g_pcbIpTable[PcbIdToIp_ResolveId(id) - 1].ip;
    }
    if (ip != 0) {
        return fn_80292934(ip);
    }
    return 0;
}
#pragma exceptions reset

const char *PcbIdToIpString(int id)
{
    if (lbl_806D1120 == 0) {
        return 0;
    }
    if (id > 4) {
        return 0;
    }
    return g_pcbIpTable[PcbIdToIp_ResolveId(id) - 1].text;
}
