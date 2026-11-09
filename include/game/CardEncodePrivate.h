#ifndef GAME_CARD_ENCODE_PRIVATE_H
#define GAME_CARD_ENCODE_PRIVATE_H

/* Bit offsets and the six sentinel-terminated scrambling schedules. */
extern const unsigned char lbl_80377BC0[32];
extern const unsigned char lbl_80377BE0[32];
extern const unsigned char lbl_80377C00[32]; /* field bit offsets */
extern const int lbl_80377C20[6][12][2];   /* byte swap schedules */
extern unsigned char lbl_80677EE8[28], lbl_80677F04[28], lbl_80677F20[28];
extern unsigned char lbl_806D1698, lbl_806D1699;
extern unsigned short wchar_to_card_char(const unsigned short *);

#endif
