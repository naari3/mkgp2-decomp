# amnet-unlock

Source: Codex worker c3_u5_amnet_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 22 fn / 2268 B.

Fine splitting C1B8/C644/D234 loses late static-bss pooling. Explicit C struct overlay folds offsets earlier and is not codegen-equivalent. Keep C158..D3E4 together with original data pools. D15C reaches 100% by c++ before i++ plus declaring c before sem. EF74 needs switch default grouped before case 0x29 with an immediate return. Original State size is 0xD8 (confirmed memset target immediates), target symbol/split includes 8 extra bytes at 0x80699218..0x80699220; no filler added; prefix remains NonMatching.

## c5_m1_amnet_20261105
Source: Codex worker c5_m1_amnet_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 92 B.

c5: fn_8028D870 becomes exact with u32 accumulator and explicit (u8) cast of (hwFlags & 7), preserving target clrlwi r0 followed by mr r3,r0. Isolated original name as Matching at D870..D8CC. Residual amnet_nm2_rest.c text 97.08827%; no EH/data ownership. Case-local buffers recover frame 0x650 versus target 0x660, but stack slots and inline trace registers still differ. Avoid repeating helper trace-argument/declaration permutations: no improvement.

## c13_u20_20261106
Source: Codex worker c13_u20_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u20: Indexed trace-ring field stores (u32 i = n & 7; lbl_806937C0[i].field) improve both rest functions over pointer-local TraceAdd. Flattening ProbeDevSend into ProbeDevClear recovers EAA8 command-block stack positions. Final D8CC 97.92738%, EAA8 98.95766%, text 98.145515%. Third probe using base-pointer advancement and fully flattened DevWrite regressed both and was reverted. No flag/split changes; no exact run to rescue.

## c18_u51_20261107
Source: Codex worker c18_u51_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u51: fresh baseline D8CC 97.92738%, EAA8 98.95766%. D8CC 32-byte hdr workspace plus staged aligned transfer helpers and nested InitializeDevSend recover target 0x660 frame and stack-slot displacements; 98.02975%. Read helpers need one forwarding layer; word poke also needs forwarding; clear needs nested send rather than c13 flattened shape. These helpers differ from the flattened EAA8 shape. EAA8 loading command address inside helper (local addr; first clear only), keeping status-clear helper unchanged, removes all saved-GPR differences: 99.28339%. Trace Begin pointer helper worsens; indexed writer/counter decomposition invariant; explicit counter read-mask-store invariant. Switch immediate-return variants add comparisons; goto done retains the missing branch residual. Byte-swap helper still emits rlwimi versus slwi/or. Pool lbl_803F2798 belongs to sibling amnet.c; do not move under this claim. TU kept NonMatching, no native gain; coordinator build service SHA-1 OK.

## c18_u158_20261107
Source: Codex worker c18_u158_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 96 B.

c18_u158: C158 wrapper isolated as Matching (+1 fn/96 B), rest moved to amnet_nm3.c with every original data pool to preserve late BSS pooling. Fresh baseline C1B8 92.93633 (assignment report 93.14); final 94.397 using one packet pointer for idle status then TX and device-level SendPacket loading address/id inside. C644 99.11585 -> 99.69512 using nested clear helper with address loaded inside, packet-level HandlerFor computing swapped command internally, explicit function-array cursor and signed word callback index. CB64 95.70422 -> 96.54929: keep u8 kind but word callback index. D234 93.98148 -> 96.34259: pass retained channel base to nested FindChanFrom. Indexed traces regress; full allocation-return helper regresses; wait-status helper regresses C1B8; poll-return helper invariant CB64. C644 residual is handler volatile registers and trace base/index r3/r8 exchange. No other function/section regressed. State remains D8 vs target E0 including 8-byte tail 80699218..80699220; no filler. Larger split rescue deliberately avoided because c3 already established pooled-BSS loss. Coordinator build service exit 0, DOL SHA-1 OK.
