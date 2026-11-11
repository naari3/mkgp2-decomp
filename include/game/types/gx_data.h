#ifndef GAME_TYPES_GX_DATA_H
#define GAME_TYPES_GX_DATA_H

/* CPU-side access to GX stream data: display lists (the vertex count of a
 * primitive, 16-bit vertex indices) and vertex buffers (position floats).
 * This data is big-endian by format; the GX layer of a port consumes it that
 * way, so it is the one part of a model file that is not converted to host
 * order when the file is loaded. On the console these are plain loads and
 * stores. A little-endian host predefines the macros to swap, for example
 *   #define GXDATA_U16(p) ((unsigned short)(((const unsigned char *)(p))[0] << 8 | ((const unsigned char *)(p))[1]))
 * Notes: docs/notes/port_abi.md. */
#ifndef GXDATA_U16
#define GXDATA_U16(p) (*(unsigned short *)(p))
#endif
#ifndef GXDATA_SET_U16
#define GXDATA_SET_U16(p, v) (*(unsigned short *)(p) = (v))
#endif
#ifndef GXDATA_F32
#define GXDATA_F32(p) (*(float *)(p))
#endif

#endif
