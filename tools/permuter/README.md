# decomp-permuter for this project

[decomp-permuter](https://github.com/simonlindholm/decomp-permuter) supports
MWCC (`compiler_type = "mwcc"`) and PowerPC objdump, so it works here. It is
not vendored: clone it anywhere (`git clone https://github.com/simonlindholm/decomp-permuter`).

`mkperm.py` builds a permuter directory for one function from the real ninja
command, so the flags, compiler version and pragmas match the build:

    ninja                                   # target objects must exist
    python3 tools/permuter/mkperm.py src/game/Foo.c FnName --check
    python3 <decomp-permuter>/permuter.py build/permuter/FnName -j4 --stop-on-zero

- `base.c`: the TU run through gcc `cpp -P` (MWCC's own `-E` drops `#pragma`
  lines, which change codegen here), other function bodies removed, `inline`
  helpers kept so they still inline and can be permuted.
- C++ TUs: pycparser can't read C++, so everything except the target
  function is wrapped in `PERM_IGNORE(...)` (left untouched, other bodies kept)
  and `PERM_PRETEND(typedef struct X X;)` lines declare the type names the
  function uses. Inline helpers are hidden too unless `--show-inlines` (they
  must then be C-parsable). Member functions (`Foo::Bar`) are hidden the same
  way, so only free functions can be permuted.
- `compile.sh`: the ninja mwcc command; for C++ the mangled symbol is renamed
  to the plain name so it lines up with `target.o`.
- `target.o`: dtk's split object `build/GNLJ82/obj/<unit>.o`; scoring uses
  `objdump --disassemble=<fn>` so the rest of the TU is ignored.
- `--check` compiles the base once (with the PERM macros expanded the way the
  permuter does) and prints the diff line count against the target. It should
  match the objdiff near-miss you started from.
- `--cc 2.6` overrides the compiler version.

Results must still pass the normal flow: put the found code into the real
source, `rm -f build/GNLJ82/main.dol && ninja`, check objdiff 100%, and mark
permuter-only shapes as `/* fakematch (permuter): ... natural code: ... */`.

Related tools: `cperm.py` (project files, text permuter that also handles C++),
`shapesweep.py` (beam search over source shapes, mwccdbg tie-break),
`autopipe.py`/autopipe99 (pragma -> decl order -> stmt order pipeline).
