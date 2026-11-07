# pcbcomm-compute-c16-u22-20261106

Source: Codex worker c16_u22_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Fresh production compile of untouched PCBCommCompute.c at base c63dabfc measures text 87.11573%, extab 100%, index 91.66667%; target 2212 B, source 2204 B. Trivial output/peer base inline accessors produce identical code. Factoring readiness scan into nontrivial PeersReady helper corrects initialization position and yields 87.486435% without size/EH changes. Indexed traversal worsens to 83.110306%; reverted. Remaining first-peer pointer folding, two-stage output add and register identity differ. Retained NonMatching; no native gain.

## c19_u180_20261107
Source: Codex worker c19_u180_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 2320 B.

c19_u180 retry: fresh raw CLI87.486435 (historical report88.31) ->91.32912, final report92.1519. RoleCount(sync,role) in normal for condition restores target loop branch shape and first yields89.25859/2212B/EH+index100. Native unsigned packed VoteByte(track:7,option:1) removes four unwanted arithmetic shifts,90.16094/2196B. Reusable firstPeer declared before out, initialized only inside scene26/commonItem==-1 branch, fixes persistent out=r29/peer=r30,91.32912/2200B. Initializing RoleCount count after guard regresses91.23147; reverted. Remaining folded HostOutput +0x6398/+0x1C, first peer/sync subbases and volatile/winner/final character GPR homes. extab100/index91.66667. Singleton/pool mechanism not applicable; one-function TU precludes B. Final coordinator full fallback SHA1ea30f3b1 exact, no native gain.
