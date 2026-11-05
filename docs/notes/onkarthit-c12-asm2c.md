# onkarthit-c12-asm2c

Source: Codex worker c12_oad_asm2c_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 944 B.

# auto_ONKARTHIT asm-to-C c12 (2026-11-06)

- Exceptions on (compiler-emitted extab, hand .extab_user entry deleted, existing extab_order key orders it) fixes the approach-B late-web register pick: CarObject_HandleObstacleHit went from 99.76% to 100%.
- `const T *src` + `*dst = *src` struct copy: CW hoists a later `src->field` load above the copy tail store. Dropping const keeps source order (lwz r0 after the tail stw).
- Out-param getter `{*out = self->f; return self->b;}` needs `__restrict` on both params to get lfs/lbz/stfs order with the r3 coalesce.
- A hand-written deleting dtor as `extern "C" void *X(void *self, short flag) throw()` that does `delete ((H*)self)->p; if (flag > 0) ::operator delete(self);` reproduces MWCC dtor codegen and extab and needs no rename key. The C-side forward decl must sit in a `#pragma cplusplus on` block with the same throw() spec.
- list::insert with a node guard: the EH frame/stw r1 after the null check comes from a try region inside the element ctor (function-try-block). Reading guard.node directly instead of a Release() temp fixes the at/node register pair.
- Inline erase returning a value keeps the branch-over-branch shape (inline-return); returning void folds it to beq.

