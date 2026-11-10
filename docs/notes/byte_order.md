# Byte order: files read from disc, and hand-written swaps

For a port to a little-endian host. The game is big-endian and lays C structs
straight over the bytes it reads from disc, so every multi-byte field of
those structs has to be swapped once, after the read and before the game
looks inside. Two headers carry this; both leave the MWCC objects unchanged.

## The load hook

`include/game/types/port_hooks.h`

```c
PORT_DATA_LOADED(kind, pointer, size)
```

Nothing under MWCC. Elsewhere it calls
`void mkgp2pc_data_loaded(int kind, void *data, unsigned int size)` (C
linkage), which the port provides. The line sits after the read (and after
inflating, for compressed files) and before the first use of the data,
including the pass that turns file offsets into pointers. `size` is the
number of bytes read, or 0 where the site does not have it.

When you rewrite a loader, keep the hook line where it is.

| kind | name | site | what `pointer` is | types the game lays over it |
|---|---|---|---|---|
| 1 | `PORT_DATA_TPL` | `src/game/TEXLoadPalette.cpp`, before `RelocatePalette(*out)` | whole .tpl file, inflated | `TEXPalette` (`include/game/types/TEXPalette.h`), `TEXDescriptor` (`include/game/types/TEXDescriptor.h`), then the SDK `TEXHeader` / `CLUTHeader` they point to. Offsets are from the file start. Image data: only the 16-bit formats (RGB565, RGB5A3, IA8, CI14) and palettes hold multi-byte values, and GX takes them big-endian, so leave them unless the renderer wants otherwise |
| 2 | `PORT_DATA_ARCHIVE_HEADER` | `src/game/DVDLoad_OpenAllocReadRelocSync.c`, after the first read | the first 0x20 bytes of an HSD archive (.dat) | `ArchiveHeader` in that file (the sysdolphin archive header; `src/sysdolphin/baselib/archive.c` reads the same fields): `file_size`, `data_size`, `nb_reloc`, `nb_public`, `nb_extern`, all u32. The game sizes the following reads from these, so this part has its own hook |
| 3 | `PORT_DATA_ARCHIVE` | same file, before `ArchiveRelocate(archive)` | the `Archive` (header already native; `data`, `reloc_info`, `public_info`, `extern_info`, `symbols` point at the blocks just read); `size` = `data_size` | `reloc_info`: `nb_reloc` u32 offsets into `data`, each naming a u32 offset to relocate. `public_info` / `extern_info`: pairs `{u32 offset; u32 symbol}`. `symbols`: characters. `data`: the HSD object graph; see below |
| 4 | `PORT_DATA_PATH_TABLE` | `src/game/CourseData_LoadPathTable.cpp`, `LoadFileData` | whole file | u32 offsets from the file start, ended by 0; each leads to a `Waypoint` list (`include/game/PathCursor.h`: `int flag; float x, y, z;`) ended by an entry with `flag < 0` |
| 5 | `PORT_DATA_GHOST` | `src/game/TaMode_FrameUpdate.cpp`, after `DVDFile_LoadSync(ghost->file)` | whole file, `size` = `ghost->size` | array of `TaGhostFrame` (`include/game/TaMode_FrameUpdate_private.h`: three floats, four signed bytes), 16 bytes each |
| 6 | `PORT_DATA_SPRITE_ANIM` | `src/game/sprite/fn_801A1494.c` | whole .bin file, size 0 | `SpriteAnimData` (`include/game/types/SpriteAnimData.h`; file view `SprFile` in `src/game/sprite/fn_801A0D90.c`): float `length` at 0x14, u32 offset `frames` at 0x18, u32 offset `params` at 0x1C. `frames` is an array of 0x54-byte nodes (`RelocNode`, `src/game/sprite/fn_801A0BE0.c`): flag byte at 0 (bit 0 = last of the array), u32 child offset at 8 (again an array of nodes); the other node fields are read by the `Sprite_*` units in `src/game/sprite/`. `params` is an s16 list ended by -1 |
| 7 | `PORT_DATA_COURSE_BGM` | `src/game/CourseBgm_Load.c` | whole file, size 0 | 16-byte records of four ints; the leading records have a zero first int |
| 8 | `PORT_DATA_COLLISION` | `src/game/CollisionFile_Load.cpp`, before `CollisionFile_FixupPointers` | whole file, `size` = rounded length | u32 at 0x28 = offset of a table of 16-byte entries ended by a zero first word; words 0 and 2 of each entry are offsets from the file start (`src/game/CollisionFile_FixupPointers.c`). The readers of what they point at are the collision units next to `CollisionFile_Load` |
| 9 | `PORT_DATA_DEMO_INPUT` | `src/game/Scene_80164614.cpp` | whole file | array of `TraceInput163` (`include/game/Scene_80163EF4Private.h`: three floats and an int), 16 bytes each |
| 10 | `PORT_DATA_SOUND_FILE` | `src/game/clsound/ClSound_InitSoundSystem.c`, two sites | a MusyX .pool, .proj, .sdir or .samp file | MusyX's own formats; the site does not say which of the four it is (the caller passes the path). A port that replaces MusyX can ignore this kind |
| 11 | `PORT_DATA_STREAM_HEADER` | `src/game/clstream/ClStream_UpdateAll.c` | 0x60-byte header of a streamed sound | `StreamInfo` in that file: u32 `unknown`, `byteLength`, `frequency`; u16 `loop`; u32 `loopStart`, `loopEnd`; then 0x44 bytes handed to `sndStreamADPCMParameter` (s16 coefficients and state) |

Not hooked, on purpose:

- `src/game/clstream/ClStream_FillChunk.c` reads ADPCM sample bytes; there is
  nothing to swap.
- `src/triforce/amsys.c` reads a firmware image for the media board.
- `DVDFile_LoadSync`, `FUN_8007dfe4` (`DVDLoad_ReadFileTimed.c`) and
  `DVDLoad_ReadChunkHandle` are the generic readers under the sites above;
  they do not know the format, so the hooks are at their callers.

That is every read of game data in `src/game`: the list comes from a search
for callers of `DVDReadPrio`, `DVDReadAsyncPrio`, `FUN_8007dfe4`,
`DVDFile_LoadSync`, `DVDLoad_ReadChunkHandle` and
`DVDLoad_OpenAllocReadRelocSync`.

### HSD archive data (kind 3)

The relocation table gives every pointer field in `data`, which is enough to
swap the pointers but not the other fields. Those are typed by what the game
asks for: the public symbols name roots, the caller reads each root as a
struct, and the pointers lead on from there.

Roots the game looks up (`HSD_ArchiveGetPublicAddress`):

| symbol | caller | root type there |
|---|---|---|
| `scene_data` | `src/game/Scene3D.c`, `SceneDrawList.cpp` (`DrawArchive`), `SceneModel_Init.cpp` (`LObjScene`), `Normal3DLoad.c` (`PublicRows`, rows of `AssetRow`: descriptor, joint / material / shape animation lists) | the sysdolphin scene descriptor: pointers to null-ended lists of model sets, cameras, lights and fog |
| `<name>_joint` and the other per-object names | `src/game/ResolveJointByName.c` and the name tables in the autodata units | a joint descriptor tree |

The on-disc descriptor structs are in the vendored sysdolphin headers,
`libs/melee/src/sysdolphin/baselib/*.h` (`HSD_ArchiveHeader` and
`HSD_ArchivePublicInfo` in `archive.h`, `HSD_Joint` in `jobj.h`,
`HSD_DObjDesc` in `dobj.h`, `HSD_MObjDesc`, `HSD_Material`, `HSD_PEDesc`,
`HSD_MatAnimJoint` in `mobj.h`, `HSD_TObjDesc`, `HSD_ImageDesc`,
`HSD_TlutDesc`, `HSD_TObjTevDesc`, `HSD_TexAnim` in `tobj.h`, `HSD_PObjDesc`,
`HSD_VtxDescList`, `HSD_ShapeSetDesc`, `HSD_EnvelopeDesc`,
`HSD_ShapeAnimJoint` in `pobj.h`, `HSD_AnimJoint`, `HSD_AObjDesc` in
`aobj.h`, `HSD_FObjDesc` in `fobj.h`, `HSD_RObjDesc` in `robj.h`,
`HSD_LightDesc` in `lobj.h`, `HSD_WObjDesc` in `wobj.h`,
`HSD_CameraDescPerspective` in `cobj.h`, `HSD_FogDesc` in `fog.h`,
`HSD_Spline` in `spline.h`). The matched baselib units in
`src/sysdolphin/baselib/` compile against them. `include/sysdolphin/baselib/`
and the game units only hold small local views of the runtime objects and of
the fields they touch. The scene root has no header: from the callers it is
four pointers to null-ended lists, model sets at 0 (`AssetRow` in
`Normal3DLoad.c`: joint, joint / material / shape animation lists), cameras
at 4 (`Scene3DDesc`), lights at 8 (`LObjScene`), fog at 0xC.

The PC port's converter walks the graph with these types and accounts for
98.8 % of the pointer fields named by the relocation tables of all 1,917
archives (port thread, 2026-11-10).

A converter has to walk that graph from each root, marking visited blocks,
because blocks are shared. Vertex buffers are typed by the vertex
description list that points at them (component type and count), display
lists are GX command streams (big-endian by definition, parsed by the GX
replacement), and texture images follow the rule in the TPL row.

## Hand-written swaps

`include/game/types/le.h`

| macro | meaning | big-endian (MWCC) | little-endian |
|---|---|---|---|
| `LE32(x)`, `LE16(x)` | `x` was stored little-endian in a file | swap | `x` |

Sites, which is all of them outside the SDK and MusyX:

| site | what is swapped | on a little-endian host |
|---|---|---|
| `src/game/TEXLoadPalette.cpp` | size word at the end of the 0x20-byte header of a compressed .tpl: the inflated size, little-endian | `LE32`: no swap |
| `src/game/NamCam_GetImageHandle.c` (`NAMCAM_SWAP32`) | fd_set bit words passed to the media board's `select` | swap stays |
| `src/game/TCPConnSend.c` (`TCPConn_SendMask`), `src/game/TCPConnRecv.c` (`TCPConn_SelectMask`) | same | swap stays |
| `include/triforce/acsocket_private.h`, `amnet_priv.h`, `amsrv_private.h`, `src/triforce/amsock.c` (`BSWAP16` / `BSWAP32`) | words exchanged with the media board (socket addresses, fd_sets, packet flags) | swap stays |

Do not make the media-board swaps conditional on the host. The am* code
mixes swapped accesses with raw constants on the same fields
(`amnet_nm3.c`: `pkt->flags != 0x180`, `pkt->flags & 0x80`; `amsock.c`:
`p->flags = 0x100` next to `BSWAP16(p->flags) == 0x8000`), so it is only
self-consistent when every swap happens. On a little-endian host the library
then runs as a mirror image of the console, and the port's media board
emulation is written against exactly that. (An earlier revision, 1dd95f3,
wrapped these in a `LE_AS_WRITTEN` macro that dropped the swap off-target;
that was wrong and was taken back out.)

Things that look like swaps and are not: `(r << 24) | (g << 16) | (b << 8) | a`
is colour packing, and `src/util/bitpack_read.c` builds values from single
bytes, so both give the same result on either host.

## Not files, same problem

Data that reaches the game as bytes from somewhere other than the disc is
laid out big-endian too and has no hook yet: the magnetic card image, the
backup RAM (SRAM) records, and the packets the cabinets exchange. A port that
only talks to itself can leave them in host order; one that must read real
cards or talk to real cabinets needs converters at those boundaries.
