# pcbcomm-sendpeers-c16-u60-20261106

Source: Codex worker c16_u60_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Fresh production baseline at d225fda0 measures text 79.44218%, extab 87.5%, index 91.66667% (source 600 B vs target 588 B). All control flow/call order/bitfields match; main structural residual is snapshot/block pointer folding, which drops saved GPR count from six to four. Flattening inline helper to direct public body gives 79.61224% with storage r31; retained NonMatching. Typed packet subobjects give 79.37415%, genuine inline C++ member gives baseline 79.44218%; both reverted. Card base/index address association also differs. Single-function TU cannot use mechanism B. No source-linked/native gain; no final full build requested because config and fallback edge unchanged.
