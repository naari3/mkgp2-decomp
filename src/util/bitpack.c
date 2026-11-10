/*
 * bitpack: schema-driven bitstream packer.
 *
 * Layout of the bitpack context (param_1 in Ghidra; 0x18 bytes wide):
 *   0x00  void *schema      schema entry table, 0x10 bytes / entry
 *                            +0x00  tag (u32, fed to FUN_80278FD8 for match)
 *                            +0x04  bit-width per slot
 *                            +0x08  slot count
 *                            +0x0C  per-entry bit offset (filled by init)
 *   0x04  int   schema_count
 *   0x08  void *dest        output byte buffer
 *   0x0C  u8    return_one_on_success / "options" byte
 *   0x10  u32   total_bits  (init result)
 *   0x14  u32   total_bytes (init result, ceil(total_bits/8) + sign-bit)
 *
 * The four routines in this TU are:
 *   bitpack_write_field   - write a value into a named field by tag/index
 *   bitpack_get_used_bytes - accessor
 *   bitpack_get_used_bits  - accessor
 *   bitpack_init          - populate per-entry offsets, derive totals,
 *                            optionally zero the destination buffer
 *
 * dtk reversed-extab group: bitpack_write_field and bitpack_init each own
 * one extab/extabindex entry (frame-bearing functions). The two leaf
 * accessors have no extab. extab/extabindex entries are manually emitted
 * via `.extab_user`/`.extabindex_user` sections (this TU builds with -lang=c
 * and no -Cpp_exceptions; tools/postprocess_extab_user.py renames them).
 *
 * bitpack_write_field is C: the tag lookup and the per-bit write loop are
 * static inline helpers (the inlined helper parameters give the target's
 * register assignment: entry r3 / dest r4 / value copy r11); the 6-GPR
 * save uses stmw, hence `#pragma use_lmw_stmw on` around it.
 *
 * bitpack_init walks the schema by byte offset: the target's offset IV
 * (r8) is live before the parameter stores, which only an explicit offset
 * variable declared ahead of `bits`/`i` reproduces.
 */

#include "game/types/BitpackEntry.h"

#include "game/types/Bitpack.h"

extern int strcmp(const char *a, const char *b);
extern void *memset(void *dst, int c, unsigned long n);

/* --- forward decls (so extabindex can reference them) --- */
int bitpack_write_field(Bitpack *self, unsigned int value, const char *tag, int index);
Bitpack *bitpack_init(Bitpack *self, BitpackEntry *schema, int count, unsigned char *dest, unsigned char clear);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_bitpack_write_field[8] = {
    0x30, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const unsigned char extab_bitpack_init[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_bitpack_write_field = {
    (void *)&bitpack_write_field, 0x0000014C, (void *)extab_bitpack_write_field
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_bitpack_init = {
    (void *)&bitpack_init, 0x000000C4, (void *)extab_bitpack_init
};

static inline unsigned char bitpack_tag_equal(const char *a, const char *b) {
    return strcmp(a, b) == 0;
}

static inline int bitpack_find(Bitpack *self, const char *tag) {
    int i;

    for (i = 0; i < self->count; i++) {
        if (bitpack_tag_equal(tag, self->schema[i].name) == 1) {
            return i;
        }
    }
    return -1;
}

static inline void bitpack_put_bits(BitpackEntry *entry, unsigned char *dest, int bit, unsigned int value) {
    int byte;
    int i;
    unsigned char mask;

    for (i = 0; i < entry->width; i++) {
        bit--;
        byte = bit / 8;
        mask = 1 << (7 - bit % 8);
        if ((value & 1) == 1) {
            dest[byte] |= mask;
        } else {
            dest[byte] &= ~mask;
        }
        value >>= 1;
    }
}

/* --- C function: bitpack_write_field @ 0x80088A5C, size 0x14C --- */
#pragma use_lmw_stmw on
int bitpack_write_field(Bitpack *self, unsigned int value, const char *tag, int index) {
    int idx;
    BitpackEntry *entry;
    unsigned char *dest;

    idx = bitpack_find(self, tag);
    if (idx < 0) {
        return 0;
    }
    entry = &self->schema[idx];
    dest = self->dest;
    if (index < entry->slots) {
        bitpack_put_bits(entry, dest, entry->offset + (index + 1) * entry->width, value);
    }
    if (self->options == 0) {
        return 0;
    }
    return 1;
}
#pragma use_lmw_stmw reset

/* --- C function: bitpack_get_used_bytes @ 0x80088BA8 (leaf accessor) --- */
unsigned int bitpack_get_used_bytes(int self) {
    return *(unsigned int *)(self + 0x14);
}

/* --- C function: bitpack_get_used_bits @ 0x80088BB0 (leaf accessor) --- */
unsigned int bitpack_get_used_bits(int self) {
    return *(unsigned int *)(self + 0x10);
}

/* --- C function: bitpack_init @ 0x80088BB8, size 0xC4 --- */
#define BITPACK_ENTRY_AT(self, ofs) ((BitpackEntry *)((char *)(self)->schema + (ofs)))

/* fakematch (byte-offset walk): natural form is the self->schema[i] loop. */
Bitpack *bitpack_init(Bitpack *self, BitpackEntry *schema, int count, unsigned char *dest, unsigned char clear) {
    int ofs;
    int bits;
    int i;

    bits = 0;
    i = 0;
    ofs = 0;
    self->schema = schema;
    self->count = count;
    self->dest = dest;
    self->options = clear;
    for (; i < self->count; i++, ofs += sizeof(BitpackEntry)) {
        BITPACK_ENTRY_AT(self, ofs)->offset = bits;
        bits += BITPACK_ENTRY_AT(self, ofs)->width * BITPACK_ENTRY_AT(self, ofs)->slots;
    }
    self->total_bits = bits;
    self->total_bytes = self->total_bits / 8 + (self->total_bits != 0 ? 1 : 0);
    if (self->options == 1) {
        memset(self->dest, 0, self->total_bytes);
    }
    return self;
}
