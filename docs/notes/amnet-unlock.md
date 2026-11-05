# amnet-unlock

Source: Codex worker c3_u5_amnet_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 22 fn / 2268 B.

Fine splitting C1B8/C644/D234 loses late static-bss pooling. Explicit C struct overlay folds offsets earlier and is not codegen-equivalent. Keep C158..D3E4 together with original data pools. D15C reaches 100% by c++ before i++ plus declaring c before sem. EF74 needs switch default grouped before case 0x29 with an immediate return. Original State size is 0xD8 (confirmed memset target immediates), target symbol/split includes 8 extra bytes at 0x80699218..0x80699220; no filler added; prefix remains NonMatching.

## c5_m1_amnet_20261105
Source: Codex worker c5_m1_amnet_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 92 B.

c5: fn_8028D870 becomes exact with u32 accumulator and explicit (u8) cast of (hwFlags & 7), preserving target clrlwi r0 followed by mr r3,r0. Isolated original name as Matching at D870..D8CC. Residual amnet_nm2_rest.c text 97.08827%; no EH/data ownership. Case-local buffers recover frame 0x650 versus target 0x660, but stack slots and inline trace registers still differ. Avoid repeating helper trace-argument/declaration permutations: no improvement.
