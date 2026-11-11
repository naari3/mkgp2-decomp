#ifndef GAME_TYPES_PCB_LINK_H
#define GAME_TYPES_PCB_LINK_H

/* Fields of the cabinet-link slot that span a byte boundary.
 *
 * The slot is sent between cabinets as bytes, and most of its fields are
 * read through byte views. A few fields cross a byte boundary and are read
 * through a 16- or 32-bit view of the same bytes, which only matches the
 * byte views on a big-endian machine. Those accesses go through the macros
 * below: the plain expressions by default (MWCC), bytes on a host that
 * predefines them. With b = (unsigned char *)&(the union or word):
 *
 *   scene  header bytes 1-2    get: (b[1] & 0x7F) << 1 | b[2] >> 7
 *   wins   class bytes 0-1     get: (b[0] & 0x01) << 3 | b[1] >> 5
 *   track  choice bytes 0-1    get: (b[0] & 0x07) << 4 | b[1] >> 4
 *   id     flags bytes 0-1     get: (b[0] & 0x03) << 1 | b[1] >> 7
 *
 * The setters replace only those bits. Notes: docs/notes/port_abi.md. */

/* w: the header's 32-bit view (an lvalue of the first four bytes) */
#ifndef PCB_HDR_SCENE
#define PCB_HDR_SCENE(w) (((w) >> 15) & 0xFF)
#endif
/* h: the header union (BroadcastHeader) */
#ifndef PCB_HDR_SET_SCENE
#define PCB_HDR_SET_SCENE(h, v) ((h).word.scene = (v))
#endif
/* c: the class union (ClassHeader) */
/* s: pointer to a whole slot; field: the name its view gives the wins bit-field
 * (bytes 6-7 of the slot) */
#ifndef PCB_SLOT_WINS
#define PCB_SLOT_WINS(s, field) ((s)->field)
#endif
#ifndef PCB_CLASS_SET_WINS
#define PCB_CLASS_SET_WINS(c, v) ((c).half.wins = (v))
#endif
/* c: the vote result union (SyncOutput.choice) */
#ifndef PCB_CHOICE_SET_TRACK
#define PCB_CHOICE_SET_TRACK(c, v) ((c).half.track = (v))
#endif
/* f: the slot flags union; view: its 16-bit bit-field member (half or ids) */
#ifndef PCB_FLAGS_ID
#define PCB_FLAGS_ID(f, view) ((f).view.id)
#endif
#ifndef PCB_FLAGS_SET_ID
#define PCB_FLAGS_SET_ID(f, view, v) ((f).view.id = (v))
#endif
/* h: the slot flags as an unsigned short lvalue */
#ifndef PCB_FLAGS16_ID
#define PCB_FLAGS16_ID(h) (((h) >> 7) & 7)
#endif

#endif
