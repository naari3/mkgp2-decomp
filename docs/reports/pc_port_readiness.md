# PC port readiness (assessment, 2026-11-10)

Question: how much further does the decomp have to go before a native PC port
is realistic? Assessment only; no port work was started. Measured at main
`a66588b` (7513 / 7612 functions matched, MSL headers fetched).

Short answer: function matching is no longer what holds a port back. What
holds it back is (1) about 40 game functions that exist only as inline asm,
(2) roughly 700 KB of initialised data that no C source defines yet, and
(3) the code being matched but not yet *portable* (per-TU struct copies,
address-named symbols, 32-bit and big-endian assumptions). Platform layers
are mostly a solved problem thanks to Aurora, except the Triforce side.

## 1. Measured

### Code
| Item | Value |
|---|---|
| Functions matched (report) | 7513 / 7612 (98.70 %), fuzzy 99.89 % |
| Game code | 2,123,512 / 2,268,852 bytes matched, 5405 / 5487 functions |
| SDK code (dolphin, HSD, MusyX, MSL, TRK, zlib, triforce libs) | 594,004 / 610,752 bytes, 2108 / 2125 functions |
| Inline-asm functions in `src/game` | about 40 real functions (regex finds 78 `asm` bodies incl. small thunks), about 15,500 instructions = about 62 KB = 2.7 % of game code |
| Inline asm elsewhere | dolphin 128 fns / 1031 insns (PPCArch, OSCache, OSContext, PS matrix math: expected, replaced by a port anyway), MusyX 8 / 681, TRK 10 / 244, THP 14 blocks |
| Standalone `.s` files | 1 (`src/init/__exception.s`) |
| `fakematch` markers | 59 |

Largest asm-only game functions (instructions): CGameCoin_Update 2131,
VSMode_FrameUpdate 1254, card_read_state_machine 792, KartItem_PerFrameStep
783, KartDriver_InitFull 768, card_rw_state_machine 704, CarObject_MainUpdate
680, TornadoEffect compose/flight/launch 669/621/591, card_rw_state_machine_short
650, fn_8014E804 600, card_save_trigger 569, KartItem_Tick 533, fn_80148A44 458.
Several of these are core gameplay (kart item step, CarObject main update,
VS mode frame update), so a port cannot skip them.

The 99 functions that do not match are C at 99.87 % fuzzy: for a port they
are as good as done (register/ordering differences only).

### Data
| Section | Defined by a source unit | Still in auto-generated (binary) units |
|---|---|---|
| .data | 907 KB | 176 KB |
| .rodata | 629 KB | 472 KB |
| .sdata2 | 3.7 KB | 40.4 KB |
| .sdata | 1.9 KB | 6.9 KB |
| .bss / .sbss | 663 KB | 1,246 KB |

About 696 KB of initialised data is linked from the original binary, not
from C. A PC build needs every one of these objects defined in source with a
real type (a big-endian blob cannot be byte-swapped without knowing its
layout). .sdata2 is mostly float constants and is mechanical; .rodata/.data
tables and .bss objects need types. Not measured: how much of the 1.5 MB that
*is* source-owned is typed properly versus byte arrays.

### Naming and structure
| Item | Value |
|---|---|
| Function symbols | 7611: 4281 named, 3122 `fn_XXXXXXXX`, 208 partly named with an address suffix |
| Data symbols | 32,251: 971 named, 31,280 `lbl_`/anonymous |
| `lbl_8XXXXXXX` references in `src/game` | 64,809 |
| `fn_8XXXXXXX(` references in `src/game` | 12,590 |
| Game source files named by address (`fn_`, `auto_`, `anon_`, `*_8XXXXXXX`) | about 680 of 2101 |
| struct/class definitions in `src/game` | 4760 in 2448 files; shared headers in `include/game`: 354. Same type redefined per TU (Vec3 about 170 times, HSD_JObj 60, KartDriver 21, ...), often as `char _opaque[N]` |
| unk/pad style fields | about 6300 |
| raw `(char*)p + 0x..` accesses | 858 in 204 files |
| raw `(T*)0x8.......` addresses in all of `src` | 167 |
| `#pragma` lines | 3115 |

So about 59 % of functions by count have names, 3 % of data objects do.
Unnamed code still compiles and runs on a PC; naming limits debugging and
modding, not the first boot. The per-TU struct copies are the real structural
debt: they are fine at 32 bit with identical layout, and break silently as
soon as a pointer member changes size.

### Platform layers called from game code (`src/game`, `ui`, `sound`, `util`)
| Layer | Call sites | Distinct functions | Files |
|---|---|---|---|
| GX | about 1650 | a few hundred | 88 (17 write the FIFO directly) |
| HSD / sysdolphin | 1420 | 153 | 250 |
| MTX / PS math | 817 | | 148 |
| OS | 692 | | 111 |
| DVD | 195 | | 31 |
| SI | 132 | 1 | 49 |
| MusyX (snd*/sal*/synth*) | 54 | 21 | 7 |
| AI / DSP | 32 | | 9 |
| VI | 11 | 3 | 5 |
| THP | 8 | 4 | 1 |
| CARD, PAD, EXI | 0 | | |
| Triforce am*/ac*/al* | 78 | 15 | 14 |
| JVS | 46 | 14 | 14 |
| Magnetic card (Sci2Card/card_rw...) | about 1040 | | 66 |
| PCB link | 89 | 23 | 17 |

The game never uses PAD or CARD: input is JVS over SI, saves are the magnetic
card, multiplayer is the PCB link over the Triforce network stack.

### Assets (ISO, 8618 files, 444 MB)
tpl 5358 files / 69 MB, HSD `.dat` 1918 / 210 MB, `.dsp` 684 / 114 MB,
`.bin` (UI animation) 640 / 39 MB, one MusyX group (samp/sdir/pool/proj, 11 MB).
All are standard or already-understood formats loaded at run time; nothing
has to be extracted into the repo. All are big-endian, and HSD `.dat` files
are relocated in place with 32-bit pointers.

## 2. How other GameCube ports got there
- Twilight Princess (Dusklight, TwilitRealm): decomp started 2020-08, reached
  100 % matching for the GameCube builds 2025-12-23, port work started late
  February 2026, v1.0.0 released 2026-05-09. Built on Aurora. About ten weeks
  from a finished, well-named decomp to a release, by a team that includes
  the Aurora authors. (Dates from a third-party timeline site quoting the
  release post.)
- Aurora (encounter/aurora, MIT): source-level GameCube/Wii compatibility
  layer: GX on WebGPU/Dawn (D3D12, Vulkan, Metal), PAD via SDL, DVD reading
  disc images directly, CARD. Written for Metaforce (Metroid Prime). Its
  README lists no audio layer.
- OpenGP (GPL-3): already runs MKGP1 and MKGP2 (US) on PC by static
  recompilation, without a decomp. Never copy its code; its hardware notes
  are usable as facts.

The lesson from TP: with matching finished and the code clean, the port is
months, not years, because GX/DVD/input already exist. TP had shared headers
and named everything long before 100 %; we match faster than we clean.

## 3. What remains, staged (estimates, not measurements)

Stage A, finish what only the decomp can do:
1. C for the about 40 asm-only game functions (about 15.5k instructions).
   Non-matching C is enough for a port; the repo rule (land only at 100 %)
   would need an exception such as a `NONMATCHING` build flag.
2. Source definitions with real types for the about 700 KB of data still in
   auto units, and for the .bss objects.

Stage B, make the code portable (largest block of work):
3. One definition per type in shared headers instead of 4760 per-TU copies;
   remove `_opaque` blobs where fields are touched.
4. Replace the 858 raw offset accesses and 167 absolute addresses.
5. A second build target (clang/gcc, 32-bit little-endian first) that
   compiles `src/game` only, with CW pragmas and `asm` behind macros. A 32-bit
   target keeps struct layouts and HSD in-place relocation valid, so only
   endianness has to be solved at first; 64-bit can follow.
6. Byte-swap at load for `.dat` (HSD archive walker), TPL, `.bin` UI
   animation, DSP headers, MusyX data, and the card image.

Stage C, platform:
7. Aurora for GX, VI, DVD and windowing. HSD stays as our own C on top of GX.
8. Audio: MusyX stays as C; replace its hardware back end (AI/DSP/ARAM) with
   a software mixer. Not covered by Aurora, so this is ours to write.
9. Triforce: stub the media board and am* services, map JVS to SDL input
   (wheel, pedals, item button, coin, test/service), card reader to a file
   (the 69-byte track format is already documented in `notes/card`), PCB link
   to UDP/TCP sockets or single-cabinet only at first.

Stage D: boot to attract mode, then one race, then card and link play.

Rough size: A is weeks at the current pace. B is the long one, on the order
of the effort already spent on the last several hundred matches, but it is
mechanical and parallelisable. C+D is a few months for someone who knows
Aurora. The first on-screen frame can come early (title/attract uses a small
slice of the code) if B is done subsystem by subsystem instead of everywhere
at once.

## 4. Recommendation
The last 99 functions add nothing for a port. If a port is the goal, redirect
effort in this order: asm-only functions to C, data ownership, shared headers,
then a small 32-bit little-endian "does it compile" target for a growing
subset of `src/game` in CI, so portability is measured the way matching is.
