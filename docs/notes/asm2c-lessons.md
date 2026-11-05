# asm2c-lessons

Source: Codex worker c10_ou_asm2c_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 9 fn / 4220 B.

MWCC GC/2.6 -Cpp_exceptions: a function that destroys a member whose class has an IMPLICIT (compiler-generated) destructor is deferred to the end of the TU .text. Declare the dtors (even `~X() {}`) to keep definition order. `x >= N` after `x += 1` without reload comes from `if ((x += 1.0f) >= N)`. rlwnm r0,1,cntlzw,31,31 is `v <= 0` as bool.
