# pcbcomm-compute-c16-u22-20261106

Source: Codex worker c16_u22_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Fresh production compile of untouched PCBCommCompute.c at base c63dabfc measures text 87.11573%, extab 100%, index 91.66667%; target 2212 B, source 2204 B. Trivial output/peer base inline accessors produce identical code. Factoring readiness scan into nontrivial PeersReady helper corrects initialization position and yields 87.486435% without size/EH changes. Indexed traversal worsens to 83.110306%; reverted. Remaining first-peer pointer folding, two-stage output add and register identity differ. Retained NonMatching; no native gain.

## c19_u180_20261107
Source: Codex worker c19_u180_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 2320 B.

c19_u180 retry: fresh raw CLI87.486435 (historical report88.31) ->91.32912, final report92.1519. RoleCount(sync,role) in normal for condition restores target loop branch shape and first yields89.25859/2212B/EH+index100. Native unsigned packed VoteByte(track:7,option:1) removes four unwanted arithmetic shifts,90.16094/2196B. Reusable firstPeer declared before out, initialized only inside scene26/commonItem==-1 branch, fixes persistent out=r29/peer=r30,91.32912/2200B. Initializing RoleCount count after guard regresses91.23147; reverted. Remaining folded HostOutput +0x6398/+0x1C, first peer/sync subbases and volatile/winner/final character GPR homes. extab100/index91.66667. Singleton/pool mechanism not applicable; one-function TU precludes B. Final coordinator full fallback SHA1ea30f3b1 exact, no native gain.

## c20_u131_20261108
Source: Codex worker c20_u131_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1432 B.

c20_u131: scoped CountModeVotes/CountTrackVotes/CountOptionVotes(peer,votes,role) helpers improve CLI91.32912 ->91.726944 and report92.1519 ->92.58589,2200B/EH100/index91.66667. Header-plus-Payload output view is instruction-invariant. Returning winner from helpers regresses91.44123/2188B; native packed scene/character/mode fields are invariant. Retained A2 NonMatching, no native gain, coordinator full fallback SHA1ea30f3b1 OK. Possible next mechanism (inference, UNTESTED): storage is currently modeled as one external CommStorage, but symbols show separate BSS objects:805A5EC0 size204,805A60C4 size54,g_pcbSyncTable805A6118 size1C,805A6134 size20,peer805A6154 size28F0,card805A8A44 size114,g_ringBufferBase805A8B58 size3700, snapshot fields805AC258..805AC290. No explicit splits.txt owner intersects this range. Target r31 may be original TU BSS section anchor; owning and defining natural separate objects could prevent folded first-peer/sync/output offsets. Revalidate claims and exact pool boundaries before any ownership change; no extra attempt taken after three-hypothesis budget.

## c21_u118_20261108
Source: Codex worker c21_u118_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u118: fresh raw91.726944/report92.58589 -> raw93.07957/report93.938515. Initialize track/option winner before Count*Votes to extend target winner lifetime (92.58047,2192B); use distinct characterCount declared before storage and initialized before clearing/scanning usedCharacters (93.07957), fixing final random-character counter/table/magic register cycle. Late-init distinct counter alone regresses91.65461; position-reservation inline helper on best regresses93.052444; reverted. extab100/index91.66667 unchanged. IMPORTANT: c20 note that BSS is unowned is now stale: PCBCheckRecv.c owns805A5EC0..805AC290 and defines its separate buffer objects. Likely original common TU anchor requires expanded coordinator claims/merge; no out-of-scope change attempted. One function prevents B. Final fallback build SHA1ea30f3b1 exact; zero native gain.

## c21_p54_20261108
Source: Codex worker c21_p54_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p54: raw93.07957/report93.938515 -> raw93.22423/report94.08318. SelectRoleCards inline helper for existing four-peer filtering fixes all 13 card/role r8/r9 operand differences 80083F08..80083FA4, all other target instruction diff statuses unchanged, size2192/extab100/index91.66667. Random-position loop helper93.052444 and explicit positions pointer92.339966(extab87.5) rejected. Pool audit UNOWNED is stale: Matching PCBCheckRecv.c owns805A5EC0..805AC290. Requires coordinator-expanded claims/merge; no ownership change attempted. Only one function so no B. Full fallback build SHA1ea30f3b1 exact; zero native gain.
