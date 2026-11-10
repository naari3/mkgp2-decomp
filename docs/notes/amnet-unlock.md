# amnet-unlock

Source: Codex worker c3_u5_amnet_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 22 fn / 2268 B.

Fine splitting C1B8/C644/D234 loses late static-bss pooling. Explicit C struct overlay folds offsets earlier and is not codegen-equivalent. Keep C158..D3E4 together with original data pools. D15C reaches 100% by c++ before i++ plus declaring c before sem. EF74 needs switch default grouped before case 0x29 with an immediate return. Original State size is 0xD8 (confirmed memset target immediates), target symbol/split includes 8 extra bytes at 0x80699218..0x80699220; no filler added; prefix remains NonMatching.

## c5_m1_amnet_20261105
Source: Codex worker c5_m1_amnet_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 92 B.

c5: fn_8028D870 becomes exact with u32 accumulator and explicit (u8) cast of (hwFlags & 7), preserving target clrlwi r0 followed by mr r3,r0. Isolated original name as Matching at D870..D8CC. Residual amnet_nm2_rest.c text 97.08827%; no EH/data ownership. Case-local buffers recover frame 0x650 versus target 0x660, but stack slots and inline trace registers still differ. Avoid repeating helper trace-argument/declaration permutations: no improvement.

## c13_u20_20261106
Source: Codex worker c13_u20_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u20: Indexed trace-ring field stores (u32 i = n & 7; amnet_nm3_bss_806937C0[i].field) improve both rest functions over pointer-local TraceAdd. Flattening ProbeDevSend into ProbeDevClear recovers EAA8 command-block stack positions. Final D8CC 97.92738%, EAA8 98.95766%, text 98.145515%. Third probe using base-pointer advancement and fully flattened DevWrite regressed both and was reverted. No flag/split changes; no exact run to rescue.

## c18_u51_20261107
Source: Codex worker c18_u51_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u51: fresh baseline D8CC 97.92738%, EAA8 98.95766%. D8CC 32-byte hdr workspace plus staged aligned transfer helpers and nested InitializeDevSend recover target 0x660 frame and stack-slot displacements; 98.02975%. Read helpers need one forwarding layer; word poke also needs forwarding; clear needs nested send rather than c13 flattened shape. These helpers differ from the flattened EAA8 shape. EAA8 loading command address inside helper (local addr; first clear only), keeping status-clear helper unchanged, removes all saved-GPR differences: 99.28339%. Trace Begin pointer helper worsens; indexed writer/counter decomposition invariant; explicit counter read-mask-store invariant. Switch immediate-return variants add comparisons; goto done retains the missing branch residual. Byte-swap helper still emits rlwimi versus slwi/or. Pool amnet_setup_nm_rodata_803F2798 belongs to sibling amnet.c; do not move under this claim. TU kept NonMatching, no native gain; coordinator build service SHA-1 OK.

## c18_u158_20261107
Source: Codex worker c18_u158_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 96 B.

c18_u158: C158 wrapper isolated as Matching (+1 fn/96 B), rest moved to amnet_nm3.c with every original data pool to preserve late BSS pooling. Fresh baseline C1B8 92.93633 (assignment report 93.14); final 94.397 using one packet pointer for idle status then TX and device-level SendPacket loading address/id inside. C644 99.11585 -> 99.69512 using nested clear helper with address loaded inside, packet-level HandlerFor computing swapped command internally, explicit function-array cursor and signed word callback index. CB64 95.70422 -> 96.54929: keep u8 kind but word callback index. D234 93.98148 -> 96.34259: pass retained channel base to nested FindChanFrom. Indexed traces regress; full allocation-return helper regresses; wait-status helper regresses C1B8; poll-return helper invariant CB64. C644 residual is handler volatile registers and trace base/index r3/r8 exchange. No other function/section regressed. State remains D8 vs target E0 including 8-byte tail 80699218..80699220; no filler. Larger split rescue deliberately avoided because c3 already established pooled-BSS loss. Coordinator build service exit 0, DOL SHA-1 OK.

## c19_u8_20261107
Source: Codex worker c19_u8_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u8: D8CC improved 98.02975 -> 98.4182% with u16 high=BSWAP16(hdr[1]), u16 low=BSWAP16(hdr[0]), base=((u32)high<<16)|low. Source remains 4572B, frame0x660; EAA8 unchanged99.28339/1224B vs target1228B. In-place hdr swapping98.09099 introduces stores; narrow locals retain size and score better. Deferring config initializer after FindDev regresses97.81015. Typed TraceSlot accessor regresses both. EAA8 empty kind1 inline stub and macro-expanded indexed writer invariant; volatile trace view strongly regresses; whole mode-switch inline helper99.24756; u8 masked index invariant. All rejected probes reverted. Remaining reset20 trace scratch operand differences + missing unreachable switch branch8028EEE0. Current shared pool belongs to amnet_nm3.c after c18 split, outside claim. NonMatching retained, no A/B unlock; coordinator full build SHA-1 exact.

## c19_u55_20261107
Source: Codex worker c19_u55_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u55: fresh C1B8 94.397 ->94.62172 with word-sized local callback kind index; D234 96.34259 ->100 (432B) using NextChannelId(NetState*,NetChan*) owning increment/wrap/search, plus explicit state pointer initialized inside the free-slot branch and reused for lastId store. Helper without state parameter gives99.35185; state initialized before free-slot tests gives98.14815 due hoisted addi; branch-local initialization is exact. C644 remains99.69512 after six scoped probes; command reuse99.527435, decl/command boundary99.58842, table-parameter boundary99.55793, trace decl/slot helpers invariant. CB64 notify helper/named state invariant96.54929; whole IRQ helper96.1831. C1B8 byte channel87.40824 and whole transmit helper not inlined. All rejected probes restored. Shared late BSS pool prevents a no-regression contiguous split; real State D8 versus target E0 eight-byte tail unchanged, no filler. Whole TU stays NonMatching, native gain0; coordinator full SHA1 exact.

## c20_u36_20261108
Source: Codex worker c20_u36_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 14 fn / 2484 B.

c20_u36: ChannelFor(u32) local cursor advancement before FreeChan restores C1B8 target unfused pointer subtraction, 94.62172 ->98.2397%, 1060->1068 B. Prior no-safe-split conclusion was too broad: D3E4..D8CC (13 fns/1256 B) and EAA8..EF74 (1 fn/1228 B) are exact with external BSS. Keep full BSS with C1B8..D3E4; give full contiguous rodata 803F2798..803F2880 and sdata2 to D8CC setup TU; dispatch table extern access leaves C644 unchanged. Partitioning rodata at2828 causes cyclic order; full pool ownership by setup fixes it. Mechanism B +14/2484 B; coordinator full SHA1 exact. Remaining C64499.69512, CB6496.54929, D8CC99.972 unchanged. Existing State8-byte tail stays NonMatching; no filler.

## c21_u51_20261108
Source: Codex worker c21_u51_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u51: checkout C1B8 has opt_propagation/opt_lifetimes off (98.35206). Removing forbidden directives gives assignment natural98.23970. ChannelDevice(u32,u8*) owning channel-to-device ID resolution and FindDev gives natural98.29588, retained; raw assisted score decreases0.05618, all other functions/data unchanged. C644 long trace sequence and canonical TraceAdd invariant99.69512; unsigned handler index99.527435, named handler result invariant, canonical GetHandler99.35976; diagnostic CSE-off99.481705 not retained. CB64 restrict74.85915 (count-before-store70.91549), dispatch-return helper invariant96.54929, classifier-only helper92.95775; rejected. State align32 did not close existing eight-byte BSS tail. No safe new contiguous BSS-pool-preserving cut under no-regression rule. No Matching flags changed, native0; full build SHA1 exact.

## c21_p1_20261108
Source: Codex worker c21_p1_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p1: amnet_setup_nm already owns complete rodata803F2798..803F2880 and sdata2806DC930..806DC940; no missing function or pool repair. Starting99.972 includes opt_propagation/opt_loop_invariants off. Removing these forbidden directives gives natural98.66317 (4572B/frame660), retained as compliance cleanup. Local-static pool regresses object order, canonical trace pointer97.665794, whole-body inline helper not inlined, u16 header halves98.61505, helper-local address and four file-static arrays invariant98.66317. All probes rejected; owned rodata/sdata2 remain100. Sole function prevents B split. Full coordinator build exit0 exact DOL SHA, native gain0; fallback remains linked.

## c21_p10_20261108
Source: Codex worker c21_p10_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p10: fresh C1B8 baseline98.29588 ->98.37079 with ChannelDeviceId(u32) returning valid channel device ID or zero, called inside existing ChannelDevice before FindDev; all other functions/sections invariant. Explicit txCount state pointer invariant; separate idle/TX packet locals invariant. C644 trace base parameter and integer+pointer expression invariant99.69512; command-boundary/declaration changes99.58842; word cmd99.51219 (unsigned compare mismatch). CB64 word kind with byte tests92.53521, byte callback index restores96.54929; sem-before-kind declaration96.1831. Standalone exact tail CC80..D3E4 with extern BSS preserves seven small methods but D00078.45977/D15C75.111115/D23471.296295, so no no-regression cut. Existing eight-byte State tail unchanged. No flags/splits/symbols edited; native0; coordinator full build exit0 and DOL SHA-1 exact.

## c22_u11_20261109
Source: Codex worker c22_u11_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u11: natural D8CC98.66317 ->98.851265 (4572B/frame660), owned rodata/sdata2 remain100. FindSetupDevice(u8 id) { NetDev* dev=FindDev(id); return dev; } forwarding inline with named result fixes target pool r30/device r31 homes. Caller search with goto found also fixes those homes but collapses one branch (98.70691); break/end-index test98.571304. Trace int index invariant; unsigned-int counter/u8 index34.301838; separate trace-record helper not inlined34.301838; small sequence getter invariant98.851265. Retained named finder only; remaining98 aligned rows are first-clear saved-register rotation, trace scratch homes, header byte-swap and case0x29 scheduling. Pool already owned, no missing function, no A/B unlock. Full coordinator build exit0 exact DOL SHA; NonMatching fallback remains linked.

## c23_u30_20261109
Source: Codex worker c23_u30_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u30: natural D8CC98.851265 ->99.253716%,4572B/frame660, owned rodata/sdata2 exact100. Index trace slot with counter&7 before slot.seq=counter++ removes repeated trace scratch mismatches (99.16623). Mapped-device first command clear with helper-local buffer/address/id, declared in that order and loading cmdAddr inside, removes first-clear r27/r28/r29 rotation (99.253716). Applying helper to all command sites regresses other clear register homes, so retained only mapped-device call. Single header OR99.15311, explicit word low temp invariant, typed config helper invariant, base-decoder inline98.97813, restricted local device invariant; rejected. Remaining18 aligned rows: header low scratch/shift/argument schedule, case29 prio1/size32 order, kind2/state-base register swap and memset args. Pool already owned; no missing functions; no A/B rescue possible in sole-function TU. Full coordinator build exit0 exact DOL SHA1; fallback remains linked, native gain0.

## c23_u49_20261109
Source: Codex worker c23_u49_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u49: OWN-SELF BSS pool already defined/owned; all 14 functions present. Corrected amnet_nm3_bss_80699140 size E0->D8 and amnet_nm3 .bss end 80699220->80699218, excluding eight-byte trailing target tail rather than adding filler. BSS99.51591->100; data/sbss100; all function scores unchanged (C1B898.37079/C64499.69512/CB6496.54929). Trace increment-at-seq/direct-slot96.08614/99.481705 regresses; named ChannelDevice result invariant; handler mask invariant, invoke helper97.789635, for-carried array98.73476, byte index99.527435; output local invariant96.54929. All source probes reverted. Existing pooled-BSS split constraints still prevent safe B rescue. Full coordinator build exit0 exact DOL SHA1, fallback retained, native0. The old eight-byte owned-BSS mismatch is now resolved without a source padding object.
