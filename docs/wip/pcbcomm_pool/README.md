# PCBComm .bss pool (mid-range thread, 2026-11-08)

Target code addresses the PCB comm buffers through one pooled base
(`lis/addi PCBCheckRecv_bss_805A5EC0` then `addi rX, base, 0x294` / `addi rY, base, 0x6398; addi rY, rY, 0x1c`).
So the .bss objects 0x805A5EC0..0x805AC290 are separate objects owned by ONE TU (the pcbcomm
module, .text ~0x8008299C..0x800862xx, ~35 split TUs today, 6 NonMatching:
PCBCommBroadcast, PCBCheckProcess, PCBCheckRecv, PCBCommSendPeers, PCBCommCompute, PCBCommLifecycle).

Proof: PCBCommSendPeers_pooled_match.c here = PCBComm_SendToAllPeers with the objects defined
in the file (in address order) -> fd.py shows only the `...bss.0` symbol-name lines, i.e. the
code matches. Before: 92.40%.

Objects (address order = definition order; CW lays .bss out by first reference, so the
`OrderProbe` function in the file forces the order for this experiment only):
  805A5EC0 BlockMsg {int index; u8 data[0x200]}   0x204
  805A60C4 broadcast slot                          0x54
  805A6118 g_pcbSyncTable                          0x1C
  805A6134 ?                                       0x20
  805A6154 PeerSlot[4] (0xA3C each)                0x28F0
  805A8A44 cards[4][0x45]                          0x114
  805A8B58 g_ringBufferBase                        0x3700
  805AC258 snapshot {header[0x1C]; body[0x1C]}     0x38  (dtk split it into 805AC258/260/261)
  (check what follows up to 0x805AC290 g_mediaBuffers)

Landing needs the whole module merged into one TU that owns this .bss (and its other data),
and the merged TU must match fully or it demotes ~29 Matching TUs. Big job: do it on a branch.
In the winning SendToAllPeers version the locals are declared peer, snapshot, block, scene, i.

## 2026-11-08 06:15 status: PARKED (blocked)
onmokoworks holds claims on PCBCommCompute (#2896), PCBCheckRecv (#2865), PCBCheckProcess (#2807),
so we will not merge the module. Hint for them (relay via user):
- ComputeSyncState: defining the objects for real (BlockMsg PCBCheckRecv_bss_805A5EC0, u8 PCBComm_BuildBroadcastSlot_bss_805A60C4[0x54], g_pcbSyncTable[0x1C],
  PCBCheck_ProcessLinks_bss_805A6134[0x20], PeerSlot PCBCheckRecv_bss_805A6154[4], CardRow PCBComm_PackAndTriggerCardSnapshot_bss_805A8A44[4], g_ringBufferBase[0x3700],
  SnapshotMsg PCBCheckRecv_bss_805AC258 {SyncOutput header, body}) + using them directly instead of the CommStorage overlay
  takes it from 92.15% to 94.9% (remaining = PeersReady reg colouring r5/r6 vs r6/r5).
- The same applies to every PCBComm function that does `addi rX, base, off` off PCBCheckRecv_bss_805A5EC0.
