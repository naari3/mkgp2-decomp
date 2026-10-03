/* Observed communication-slot bytes only; all storage is external. */
typedef struct SnapshotHeader {
    unsigned char reserved7 : 1;
    unsigned char role : 3;
    unsigned char ready : 1;
    unsigned char reserved0 : 3;
} SnapshotHeader;

typedef struct SnapshotTrigger {
    unsigned char upper : 4;
    unsigned char pending : 1;
    unsigned char lower : 3;
} SnapshotTrigger;

typedef struct SnapshotSlot {
    SnapshotHeader header;
    unsigned char pad1[0xA33];
    SnapshotTrigger trigger;
    unsigned char tail[7];
} SnapshotSlot;

extern int g_localPcbRole, g_myPcbId;
extern unsigned char g_isCommHost;
extern unsigned char g_playerData[0x1DC];
extern unsigned char lbl_805A8A44[][0x45];
extern SnapshotSlot lbl_805A6154[];
/* The caller supplies an extra mode argument; the observed callee ignores it. */
extern void* card_pack(void* source, void* destination, int mode);

int PCBComm_PackAndTriggerCardSnapshot(void)
{
    if (g_localPcbRole == 0) return 0;
    card_pack(g_playerData, lbl_805A8A44[g_myPcbId - 1], 1);
    if (g_isCommHost == 0) {
        SnapshotSlot* slot = lbl_805A6154;
        int local = g_myPcbId - 1;
        int role = g_localPcbRole;
        int i;
        for (i = 0; i < 4; ++i, ++slot) {
            if (i != local && slot->header.role == role && slot->header.ready == 1)
                slot->trigger.pending = 1;
        }
    }
    return 1;
}
