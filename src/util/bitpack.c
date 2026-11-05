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
 * bitpack_init stays asm_fn: the best C (below) is instruction-identical
 * except the coloring of the strength-reduced schema-offset IV (target
 * off=r8/bits=r9/i=r10, C off=r4 after the param stores die; ~12 natural
 * variants of decl order / init placement / for-while / inline param-setter
 * did not move it). Best C:
 *
 *   int i; int bits;
 *   bits = 0;
 *   self->schema = schema; self->count = count;
 *   self->dest = dest; self->clear = clear;
 *   for (i = 0; i < self->count; i++) {
 *       self->schema[i].offset = bits;
 *       bits += self->schema[i].width * self->schema[i].slots;
 *   }
 *   self->total_bits = bits;
 *   self->total_bytes = self->total_bits / 8 + (self->total_bits != 0 ? 1 : 0);
 *   if (self->clear == 1) memset(self->dest, 0, self->total_bytes);
 *   return self;
 */

typedef struct BitpackEntry {
    const char *tag; /* 0x00 */
    int width;       /* 0x04 bits per slot */
    int slots;       /* 0x08 slot count */
    int offset;      /* 0x0C bit offset (filled by bitpack_init) */
} BitpackEntry;

typedef struct Bitpack {
    BitpackEntry *schema;  /* 0x00 */
    int count;             /* 0x04 */
    unsigned char *dest;   /* 0x08 */
    unsigned char clear;   /* 0x0C */
    int total_bits;        /* 0x10 */
    int total_bytes;       /* 0x14 */
} Bitpack;

extern int strcmp(const char *a, const char *b);
extern void *memset(void *dst, int c, unsigned long n);

/* --- forward decls (so extabindex can reference them) --- */
int bitpack_write_field(Bitpack *self, unsigned int value, const char *tag, int index);
asm void bitpack_init(void);

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
        if (bitpack_tag_equal(tag, self->schema[i].tag) == 1) {
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
    if (self->clear == 0) {
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

/* --- asm function: bitpack_init @ 0x80088BB8, size 0xC4 --- */
asm void bitpack_init(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r9, 0x0
    li r10, 0x0
    stw r0, 0x14(r1)
    li r8, 0x0
    stw r31, 0xc(r1)
    mr r31, r3
    stw r4, 0x0(r3)
    stw r5, 0x4(r3)
    stw r6, 0x8(r3)
    stb r7, 0xc(r3)
    b bitpack_init_L_80088C18
bitpack_init_L_80088BEC:
    lwz r3, 0x0(r31)
    addi r0, r8, 0xc
    addi r10, r10, 0x1
    stwx r9, r3, r0
    lwz r0, 0x0(r31)
    add r4, r0, r8
    addi r8, r8, 0x10
    lwz r3, 0x4(r4)
    lwz r0, 0x8(r4)
    mullw r0, r3, r0
    add r9, r9, r0
bitpack_init_L_80088C18:
    lwz r0, 0x4(r31)
    cmpw r10, r0
    blt bitpack_init_L_80088BEC
    stw r9, 0x10(r31)
    lwz r4, 0x10(r31)
    neg r3, r4
    srawi r0, r4, 3
    or r3, r3, r4
    srwi r3, r3, 31
    addze r0, r0
    add r0, r0, r3
    stw r0, 0x14(r31)
    lbz r0, 0xc(r31)
    cmplwi r0, 0x1
    bne bitpack_init_L_80088C64
    lwz r3, 0x8(r31)
    li r4, 0x0
    lwz r5, 0x14(r31)
    bl memset
bitpack_init_L_80088C64:
    lwz r0, 0x14(r1)
    mr r3, r31
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
