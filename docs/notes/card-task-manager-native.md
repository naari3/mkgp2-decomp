# card-task-manager-native

Source: Codex worker c15_a24_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 512 B.

card_task_manager_create8008A0A0 native512B matches with TU-private CardTask virtual Render/dtor/Start ABI, CardTaskEntry{task,kind}, CardTaskFactory{create,other}. Inline AddTask(self, factory(), kind) independently indexes task and kind then increments count, reproducing alias-sensitive pointer/count reloads. A separate inline Initialize resets queue count, allocates32B, and initializes four task pointers; caller initializes manager state and linger60 first. Three unsigned-char flags are compared to1. This first structured implementation reaches text/extab/extabindex100, superseding prior54.265625% probes in per_fn_matching_strategy19.9. No mangled bridges or config edits needed. Two coordinator full links preserve target SHA1.
