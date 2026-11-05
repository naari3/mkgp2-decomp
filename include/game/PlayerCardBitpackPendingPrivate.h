#ifndef PLAYER_CARD_BITPACK_PENDING_PRIVATE_H
#define PLAYER_CARD_BITPACK_PENDING_PRIVATE_H
typedef unsigned char u8;
extern "C" void *bitpack_init(void *, void *, int, void *, u8);
class PlayerCardBitpack {
    u8 opaque[0x18];
public:
    inline PlayerCardBitpack(void *table, int count, void *raw, u8 options) {
        bitpack_init(this, table, count, raw, options);
    }
};
#endif
