#ifndef CARD_SAVE_PARSER_PRIVATE_H
#define CARD_SAVE_PARSER_PRIVATE_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
/* Bitpack state is initialized and consumed exclusively by the bitpack API. */
typedef struct CardBitpackState { u32 opaque[6]; } CardBitpackState;
typedef struct CardUnlockRule {
    int id, category, savedFlag, group, slot;
} CardUnlockRule;
extern u8 bitpack_read_field_by_name(void *, const char *, u32 *, int);
extern void DebugPrintf(const char *, ...);
#endif
