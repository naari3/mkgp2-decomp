# The game uses the real Metrowerks MSL C++ library (2026-11-09)

Found by the n3 structure thread while working on `game/fn_801DEF94.cpp`.

## What

main.dol contains the MSL C++ error strings (`deque::push_front length error`,
`cdeque::reserve length error`, `vector::insert length error`, ...).  The
containers in the game are not hand-written: they are `std::deque`,
`Metrowerks::cdeque`, `std::vector`, `std::length_error` ... from MSL C++
(`__MSL_CPP__ 0x7200`), the library shipped with CodeWarrior for GameCube 2.5
(the 2.7 release has byte-identical headers).

Compiling the genuine headers with GC/2.6 reproduces the target code exactly.
Checked on the waypoint queue (`std::deque<{int,int}>`, 0x801E2BD0..0x801E5A18):
every function is identical except for the names of the callees, including
seven functions that had been stuck at 71-99.8% as hand-written C++
(fn_801E2FD4, fn_801E32C8, fn_801E35FC, fn_801E36A8, fn_801E435C,
fn_801E4AF4, fn_801E5454).

| address | MSL function |
| --- | --- |
| dtor_801E2BD0 | `std::deque<T>::~deque` |
| fn_801E2C40 / 2DF0 / 2F28 / 2FD4 | `deque::tear_down` / `clear` / `pop_front` / `push_front` |
| dtor_801E3200 | `Metrowerks::cdeque<T*>::~cdeque` |
| fn_801E3260 | `deque::deque(size_type)` (the `T()` temp is the 8-byte .sbss object at 0x806D1904) |
| fn_801E32C8 / 35FC / 36A8 / 3848 / 3A4C | `grow_buf_front` / `make_iterator` / `destroy` / `init` / `init_buf` |
| fn_801E40C0 / 40E8 / 411C / 435C | `cdeque<const void*>::operator[]` / `pop_front` / `reserve` / `resize` |
| fn_801E4504 / 4524 | `cdeque<T*>::reserve` / `resize` |
| fn_801E4544 / 4824 / 4AF4 / 5454 / 5724 / 5A00 | `cdeque<const void*>::do_assign` / `erase` / `insert` / `push_back` / `push_front` / `max_size` |
| lbl_806DA360 | `deque<T>::default_bufsize_s` |
| ClStrPcb_Dtor / ClStrPcb_Mid_Dtor / dtor_80038DD4 | `std::length_error` / `logic_error` / `exception` destructors |
| SharedPtr_Init / dtor_80038E30 | `std::_RefCountedPtr<char, _Array<char>>` ctor / dtor |
| FUN_8003b120 / MemoryManager_Free / Alloc / MemoryManager_TimedFree | `operator new[]` / `delete[]` / `new` / `delete` |

### std::list and std::vector (same day)

| address | MSL function |
| --- | --- |
| DoublyLinkedList_Init | `std::__list_deleter<const void*>::__list_deleter()` |
| DoublyLinkedList_PushBefore | `__list_deleter<const void*>::insert(iterator, const T&)` (what `push_back` calls) |
| fn_8012215C | `__list_deleter<const void*>::erase(iterator)` |
| PtrVec_InsertFill | `std::__vector_pod<unsigned long>::insert(pointer, size_type, const T&)` (every `vector<T*>::push_back`) |
| fn_80146000 | `__vector_pod<unsigned long>::at(size_type)` |
| fn_801460D0 | `std::out_of_range::~out_of_range` |
| dtor_80145F9C | `std::vector<FadeObj*>::~vector` |
| fn_801C1964 / 1AA8 / 1BD8, dtor_801C1B78 / 1CE8 | `__vector_imp<KeyGroup,...,0>::init` / `at`, `__vector_deleter::clear` / dtor, `vector<KeyGroup>` dtor |

Matched with the real headers after long hand sweeps had failed:

- `it = list.erase(it)` loops (fn_80204218, fn_8020F080, about 300 hand-written
  forms tried): the list<void const*> iterator is converted back to the
  list<T*> iterator, which is where the extra stack copies come from.
- `std::vector<KeyGroup> groups(5)` + `for (int i = 0; i < groups.size(); i++)
  groups.at(i) = table[i];` (fn_801BF644).  `T()` for a POD is copied from a
  zero .bss/.sbss object (`lbl_806792B8`), and the `int` index is what moves
  the `mr r4, r30` copy into the loop test.
- A ctor that `push_back`s panels into a `std::list` (clFlowGpPlease_Init):
  the hand-written `End()` sentinel caused an r0/r7 exchange; with the real
  list and the natural `table[i]`, `118 + i * 202` loop it matches.

Rule of thumb: once the container is real, write the user code in the most
ordinary way (`int i`, `operator[]`, `push_back`); the odd pointer/offset
loops in our sources were compensating for the hand-written container.

## Getting the headers

The headers are Metrowerks copyright and are **not** in the repository.

    apt install unshield && pip install pycdlib
    python3 tools/fetch_msl.py        # archive.org -> build/msl_cw25/

A unit that uses them adds `*cflags_msl_cpp` (and normally `-rostr`,
`-Cpp_exceptions on`) to its `extra_cflags` in configure.py.  Whether main may
depend on the fetched headers is being decided by naari3; until then use them
as a reference and for local experiments only.

## Rules learned

- Inlining inside template members depends on what was instantiated before:
  `deque::push_front` is 0x22C bytes (target) only when `cdeque::operator[]`
  was already instantiated (a `front()` call earlier in the TU); otherwise it
  is 0x294 with a live catch block.  Reproduce the uses of the original TU in
  their order (the natural order `clear, push_front, pop_front, size, front,
  ~T, T(1)` gives all target sizes).
- Include `<deque>` after the existing code of a unit: the header consumes
  `@N` numbers, so including it at the top shifts every number-based rename in
  `tools/extab_user_renames.json`.
- A unit can own a single instantiated function: put never-referenced users in
  it, rename the instantiation to the `fn_` name and let the linker strip the
  rest (weak copies renamed to names that have a strong definition elsewhere
  are dropped).  Literal strings are referenced with `"@N": "extern:lbl_X"`.
- `extab_padding` is consumed per padding slot across the whole object; with
  many template functions use a long repeat (`b"\x02\x55" * 40`).
- The MSL headers are not UTF-8; `fetch_msl.py` replaces the few non-ASCII
  comment bytes so sjiswrap accepts them.
- Open: in the target every weak function (deque members, the SteerPtr
  destructors, then the cdeque<const void*> members) sits after all normal
  functions of the TU; our compiles emit in-class inline functions right after
  the first function that needs them out of line.  The lever for that order
  is not known yet, so `game/fn_801DEF94.cpp` cannot flip.

## Where else to look

Any near miss around an error string from MSL, or with hand-written
`Ring` / `Vector` / `SharedPtr` / `length_error` helpers: fn_80204218
(iterator temps), fn_801BF644 / fn_801BE170 (`vector::at`), WarpZoneVector,
the list code in clItemBoxManager.  Compile the real header with the element
size of the target and compare (see the mangled-name mapping above).
