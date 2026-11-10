#ifndef GAME_TYPES_PORT_HOOKS_H
#define GAME_TYPES_PORT_HOOKS_H

/* PORT_DATA_LOADED(kind, pointer, size): a file (or a part of one) has just
 * been read into memory, and inflated if it was compressed; the game has not
 * looked inside yet and has not turned file offsets into pointers.
 *
 * Nothing under MWCC. Elsewhere it calls mkgp2pc_data_loaded(), where a port
 * to a little-endian host converts the big-endian fields in place. `size` is
 * the number of bytes read, or 0 where the load site does not know it (the
 * format then has its own terminator or count).
 *
 * The kinds are the formats the game tells apart by load site. The struct
 * types the game lays over each are listed in docs/notes/byte_order.md.
 */
#define PORT_DATA_TPL             1  /* texture palette file (.tpl), whole file */
#define PORT_DATA_ARCHIVE_HEADER  2  /* HSD archive (.dat): the 0x20-byte header alone, read first */
#define PORT_DATA_ARCHIVE         3  /* HSD archive: pointer is the Archive (header already converted,
                                        data / reloc_info / public_info / extern_info / symbols read),
                                        before relocation; size is the data block size */
#define PORT_DATA_PATH_TABLE      4  /* course path table: u32 offsets ended by 0, each to a waypoint list */
#define PORT_DATA_GHOST           5  /* time attack ghost recording */
#define PORT_DATA_SPRITE_ANIM     6  /* sprite animation .bin (SpriteAnimData) */
#define PORT_DATA_COURSE_BGM      7  /* course BGM cue table */
#define PORT_DATA_COLLISION       8  /* course collision file, before its offsets become pointers */
#define PORT_DATA_DEMO_INPUT      9  /* attract-mode input recording */
#define PORT_DATA_SOUND_FILE     10  /* MusyX pool / proj / sdir / samp files */
#define PORT_DATA_STREAM_HEADER  11  /* 0x60-byte DSP ADPCM header of a streamed sound */

#ifdef __MWERKS__
#define PORT_DATA_LOADED(kind, pointer, size)
#else
#ifdef __cplusplus
extern "C"
#endif
void mkgp2pc_data_loaded(int kind, void *data, unsigned int size);
#define PORT_DATA_LOADED(kind, pointer, size) mkgp2pc_data_loaded((kind), (void *)(pointer), (unsigned int)(size))
#endif

#endif
