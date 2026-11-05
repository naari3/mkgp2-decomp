# triforce-jvsio-unlock

Source: Codex worker c3_u4_jvsio_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 7 fn / 104 B.

JVS original static cmd and tx BSS use common-section base addressing. Converting storage to external globals changes BSS emission order; extracting request builders with extern state changes stbx into add+stb and register allocation. Nested aggregate extern state did not repair it; explicit local state pointers improved shape but did not reach exact. These broad split probes were reverted. The seven leaf getters use independent named storage relocations and split exactly. Missing fn_80283154 had only a declaration in the original source; report omission concealed its absence.
