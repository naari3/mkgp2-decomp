/* bitpack_read_field_by_name @ 0x80088880..0x80088A5C: reads slot `index`
 * of the named field from a bitpack context (layout in util/bitpack.c). */

typedef struct BitpackEntry {
    const char *name;
    int width;
    int count;
    int offset;
} BitpackEntry;

typedef struct Bitpack {
    BitpackEntry *schema;
    int count;
    unsigned char *buf;
    unsigned char options;
} Bitpack;

extern char lbl_806D3278[7]; /* "UPDATE" */
int strcmp(const char *a, const char *b);
void *memset(void *dst, int c, unsigned long n);

static inline unsigned char bitpack_name_equal(const char *a, const char *b)
{
    return strcmp(a, b) == 0;
}

static inline int bitpack_find(Bitpack *ctx, const char *name)
{
    int i;

    for (i = 0; i < ctx->count; i++) {
        if (bitpack_name_equal(name, ctx->schema[i].name) == 1) {
            return i;
        }
    }
    return -1;
}

static inline unsigned char bitpack_read_slot(Bitpack *ctx, int i, unsigned int *out, int index)
{
    unsigned char *buf;
    BitpackEntry *e;
    int bit;
    int j;
    int bytes[4];

    *out = 0;
    e = &ctx->schema[i];
    buf = ctx->buf;
    if (index >= e->count) {
        return 0;
    }
    bit = e->offset + (index + 1) * e->width;
    memset(bytes, 0, sizeof(bytes));
    for (j = 0; j < e->width; j++) {
        bit--;
        if ((unsigned char)((1 << (7 - bit % 8)) & buf[bit / 8])) {
            bytes[3 - j / 8] |= 1 << (j % 8);
        }
    }
    *out = (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
    *out &= (1 << e->width) - 1;
    return 1;
}

#pragma exceptions on
int bitpack_read_field_by_name(Bitpack *ctx, const char *name, unsigned int *out, int index)
{
    int i;

    i = bitpack_find(ctx, name);
    if (i < 0) {
        return 0;
    }
    if (!bitpack_read_slot(ctx, i, out, index)) {
        return 0;
    }
    strcmp(name, lbl_806D3278);
    return ctx->options != 1;
}
#pragma exceptions reset
