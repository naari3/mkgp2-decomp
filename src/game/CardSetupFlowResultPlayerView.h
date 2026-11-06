/* TU-private snapshot: the unlock index is a four-byte value object. */
#ifndef CARD_SETUP_FLOW_RESULT_PLAYER_VIEW_H
#define CARD_SETUP_FLOW_RESULT_PLAYER_VIEW_H
struct ResultUnlockIndex { unsigned int value; };
#pragma options align=packed
struct ResultPackedWords {
    unsigned int word1BA, word1BE, word1C2, word1C6, word1CA, word1CE;
};
#pragma options align=reset

struct ResultPlayerSnapshot {
    unsigned int word000, word004, word008;
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
    ResultUnlockIndex unlockIdx; /* +18C, also observed in clFlowItem's PlayerDataRec */
    unsigned int word190, word194;
    unsigned char byte198, byte199, byte19A, byte19B, byte19C;
    unsigned char byte19D, byte19E, byte19F, byte1A0;
    unsigned int word1A4;
    unsigned char byte1A8;
    unsigned int word1AC;
    unsigned char byte1B0, byte1B1;
    unsigned int word1B4;
    unsigned char byte1B8, byte1B9;
    struct ResultPackedWords words1BA;
    unsigned int word1D4;
    unsigned char byte1D8, byte1D9, byte1DA;
};

typedef char ResultSnapshotSize[sizeof(ResultPlayerSnapshot) == 0x1DC ? 1 : -1];
typedef char ResultUnlockIndexSize[sizeof(ResultUnlockIndex) == 4 ? 1 : -1];
#endif
