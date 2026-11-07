#ifndef CARD_LOAD_SHADOW_MATCH_PRIVATE_H
#define CARD_LOAD_SHADOW_MATCH_PRIVATE_H
/* TU-private snapshot view. The 12-byte player name is copied as three
 * words; PCBCommBroadcast observes the same storage as six UTF-16 units.
 * The unlock index is the value object used by CardSetupFlowResult.
 * Packed tail words at +1BA..+1CE are deliberately not aligned to four. */
#pragma options align=packed
struct ShadowPackedWords {
    unsigned int word1BA, word1BE, word1C2, word1C6, word1CA, word1CE;
};
#pragma options align=reset

struct ShadowUnlockIndex { unsigned int value; };
struct ShadowPlayerName { unsigned int word000, word004, word008; };
struct ShadowPlayerSnapshot {
    struct ShadowPlayerName name;
    unsigned char byte00C, byte00D;
    unsigned short half00E, half010;
    unsigned int word014;
    unsigned char byte018, byte019, byte01A;
    unsigned int word01C, word020, word024, word028, word02C;
    unsigned int word030, word034, word038, word03C, word040;
    unsigned int word044, word048, word04C, word050, word054;
    unsigned int word058, word05C, word060, word064, word068;
    unsigned int word06C, word070, word074, word078, word07C;
    unsigned int word080, word084, word088, word08C, word090;
    unsigned int word094, word098, word09C, word0A0, word0A4;
    unsigned char bytes0A8[0x79];
    unsigned char bytes121[0x69];
    struct ShadowUnlockIndex unlockIdx; /* +18C, also observed in clFlowItem's PlayerDataRec */
    unsigned int word190, word194;
    unsigned char byte198, byte199, byte19A, byte19B, byte19C;
    unsigned char byte19D, byte19E, byte19F, byte1A0;
    unsigned int word1A4;
    unsigned char byte1A8;
    unsigned int word1AC;
    unsigned char byte1B0, byte1B1;
    unsigned int word1B4;
    unsigned char byte1B8, byte1B9;
    struct ShadowPackedWords words1BA;
    unsigned int word1D4;
    unsigned char byte1D8, byte1D9, byte1DA;
};
struct ShadowBackupSnapshot {
    unsigned char prefix000[0x64];
    unsigned char captured;
    unsigned char prefix065[0x90 - 0x65];
    struct ShadowPlayerSnapshot player;
};

typedef char CheckSnapshotSize[sizeof(struct ShadowPlayerSnapshot) == 0x1DC ? 1 : -1];
typedef char CheckPackedSize[sizeof(struct ShadowPackedWords) == 0x18 ? 1 : -1];
typedef char CheckShadowNameSize[sizeof(struct ShadowPlayerName) == 12 ? 1 : -1];
typedef char CheckShadowIndexSize[sizeof(struct ShadowUnlockIndex) == 4 ? 1 : -1];

extern struct ShadowPlayerSnapshot g_playerData;
extern struct ShadowBackupSnapshot lbl_80598A60;


#endif
