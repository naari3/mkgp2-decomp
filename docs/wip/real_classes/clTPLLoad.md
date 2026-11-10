# clTPLLoad / clTPLexp as real classes: parked 2026-11-10

`clTPLLoad.cpp` here is one unit for 0x801F6860..0x801F6BD0 (today's
`fn_801F6860.cpp`, `PaletteBufferCtor.cpp`, `dtor_801F6B44.cpp`) with
`.rodata` 0x803BED98..0x803BEDB0, `.data` 0x804E54F0..0x804E5518 and `.sdata`
0x806D0090..0x806D00A0. Flags: `-Cpp_exceptions on -use_lmw_stmw on -RTTI on
-rostr -inline deferred`, `extab_padding=b""`.

What matches: all three functions, the vtables, base list, RTTI records and
name strings, each in the target order. Found on the way:

- `count` is a member of clTPLexp, not of clTPLLoad: the constructor stores
  it before it stores clTPLLoad's vtable pointer.
- The virtual destructor is declared before the data members so that the
  vtable pointer is at offset 0 (MWCC puts it where the first virtual
  function is declared).
- Not deferred gives weak base vtable, base list, vtable and the base name
  string first; deferred gives the target order.

What does not: **mwld puts the constructor's exception table entry at
0x80017518 instead of 0x80017514**, 4 bytes of zero after the 8-byte entry
of the destructor, and everything after it moves. It is the only gap of
this kind in the whole linked extab. The object itself has the three
entries back to back (0, 8, 0x24), `.comment` alignment 4 on each.

Tried, no change (the entry always lands at 0x80017518):

- base destructor as an ordinary function instead of weak;
- the same order declared in `tools/extab_order.json`;
- an extra uncalled function whose 8-byte entry is first in the object
  (entries at 8, 0x10, 0x2C);
- an uncalled second constructor with a 0x1C entry between the two
  (constructor entry at 0x24), and first in the object (destructor entry at
  0x1C, constructor entry at 0x24).

So the offset of the entry in the object does not matter. Ruled out from
the rest of the binary: "entries after the first are 8-aligned", "entries
of size 4 modulo 8 are 8-aligned", "entries with a relocation are
8-aligned" (66 linked entries with a relocation sit at 4 modulo 8, e.g.
`EnemyFace_exact3.cpp` 0x8001BEB4). `InputCmdLifetime.cpp` has the same
shape (8-byte entry, then a 0x1C entry with one relocation) and links
without a gap, but starts at an 8-aligned address, so it does not tell.

Open: what makes mwld align this one entry. Until that is known the class
stays as three units. The draft keeps the uncalled second constructor of
the last test; without it and with the base destructor inline in the class
the object is the same except for those entries.
