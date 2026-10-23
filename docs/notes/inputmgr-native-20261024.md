# InputMgr native C++ retrofit

InputMgr_Shutdown (0x80039084, 100 bytes) and InputMgr_Init (0x800390E8,
108 bytes) now use native C++ ownership and compiler-generated exception data.
The 4-byte manager owns a 0x28-byte input object with a virtual destructor.
Nested new expressions reproduce both allocation cleanup actions; delete
reproduces the virtual destructor dispatch and manager teardown.

The existing .c filename and `#pragma cplusplus on` retain the existing build
route. Per-TU symbol aliases connect the constructor, new and delete to the
original functions. No manual exception tables or inline assembly remain.

Independent main verification: all_source, report, progress and DOL SHA-1 pass.
Direct objdiff matches .text (216 bytes), extab (48 bytes) and extabindex
(24 bytes) at 100%. The source object is linked into main.elf. This promotes
two ASM functions to native source; aggregate matching counts do not change.
