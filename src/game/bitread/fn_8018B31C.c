extern signed long long OSGetTime(void);
#define OSTicksToMilliseconds(ticks) ((ticks) / ((*(unsigned long *)0x800000F8 / 4) / 1000))
#include "game/CardEncodePrivate.h"

const unsigned char lbl_80377BC0[32] = "ztj6bkc9nh5v1sa2uwx47epymd08fgr3";
const unsigned char lbl_80377BE0[32] = {8, 8, 8, 8, 8, 4, 1, 2, 3, 1, 1, 4, 3, 4, 4, 4, 4, 1, 8, 8, 8, 3, 6, 3, 3, 2, 2, 2, 0, 0, 0, 0};
const unsigned char lbl_80377C00[32] = {27, 82, 15, 41, 52, 90, 36, 2, 49, 23, 106, 70, 12, 107, 102, 37, 111, 35, 4, 60, 94, 24, 76, 120, 117, 115, 68, 74, 0, 0, 0, 0};
const int lbl_80377C20[6][12][2] = {
        {{2, 5}, {8, 6}, {18, 1}, {16, 7}, {21, 17}, {3, 14}, {-1, -1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
        {{7, 1}, {16, 19}, {3, 15}, {22, 11}, {5, 18}, {2, 14}, {8, 4}, {20, 13}, {-1, -1}, {0, 0}, {0, 0}, {0, 0}},
        {{5, 1}, {11, 20}, {10, 17}, {14, 21}, {7, 16}, {2, 15}, {8, 18}, {19, 13}, {-1, -1}, {0, 0}, {0, 0}, {0, 0}},
        {{7, 17}, {16, 10}, {3, 20}, {8, 22}, {6, 12}, {-1, -1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
        {{7, 16}, {18, 21}, {3, 20}, {5, 19}, {1, 4}, {9, 14}, {6, 10}, {17, 15}, {-1, -1}, {0, 0}, {0, 0}, {0, 0}},
        {{16, 10}, {12, 1}, {9, 11}, {5, 17}, {4, 18}, {6, 21}, {2, 14}, {20, 13}, {-1, -1}, {0, 0}, {0, 0}, {0, 0}},
};
unsigned char lbl_80677EE8[28];
unsigned char lbl_80677F04[28];
unsigned char lbl_80677F20[28];


static inline unsigned char EncodeNameChar(const unsigned short *name) {
    return (unsigned char)wchar_to_card_char(name);
}

static inline void WriteBits(int start, int n, int value) {
    int i;
    for (i = 0; i < n && i + start < 125; i++) {
        lbl_80677EE8[(start + i) / 5] &= ~(1 << (4 - (start + i) % 5));
        lbl_80677EE8[(start + i) / 5] |= ((value >> (n - (i + 1))) & 1) << (4 - (start + i) % 5);
    }
}

static inline void WriteField(int field, int value) {
    WriteBits(lbl_80377C00[field], lbl_80377BE0[field], value);
}

static inline unsigned char ReadBits(int start, int n) {
    unsigned char result = 0;
    int i;
    for (i = 0; i < n && i + start < 125; i++) {
        result |= ((lbl_80677EE8[(start + i) / 5] >> (4 - (start + i) % 5)) & 1) << (n - (i + 1));
    }
    return result;
}

static inline unsigned char PackedChecksum(void) {
    unsigned int sum = 0;
    int i;
    for (i = 0; i < 128; i += 4) {
        sum += ReadBits(i, 4);
    }
    while (sum >> 4) {
        sum = (sum & 15) + (sum >> 4);
    }
    return (unsigned char)sum;
}

static inline void EncodeText(unsigned char *dst) {
    unsigned char text[26];
    int i, j;
    for (i = 0; i < 25; i++) {
        for (j = 0; j < 32; j++) {
            if (j == lbl_80677EE8[i]) {
                text[i] = lbl_80377BC0[j];
                break;
            }
        }
    }
    text[25] = 0;
    for (i = 0; i < 26; i++) {
        dst[i] = text[i];
    }
}

static inline void ClearPacked(void) {
    unsigned int i;
    for (i = 0; i < 25; i++) lbl_80677EE8[i] = 0;
}

#pragma exceptions on
#pragma use_lmw_stmw on
void fn_8018B31C(const unsigned short *name, int item, int ccClass,
                 int character, int kart, int cup, int longRound, unsigned int flags,
                 unsigned char a, unsigned char b, unsigned char c,
                 unsigned char saveBackup, float time) {
    unsigned int seed;
    int i;
    unsigned char rotation;
    unsigned char schedule;
    const int (*swap)[2];
    unsigned char checksum;

    int encodedClass = ccClass >= 2 ? ccClass - 1 : ccClass;
    seed = (unsigned int)(1000.0f * (float)OSTicksToMilliseconds(OSGetTime()));
    ClearPacked();
    for (i = 0; i < 5 && i < 5; i++) WriteField(i, EncodeNameChar(name + i));
    WriteField(5, (unsigned char)item);
    WriteField(6, (unsigned char)(character - 1));
    WriteField(7, (unsigned char)encodedClass);
    WriteField(8, (unsigned char)(kart - 1));
    WriteField(9, (unsigned char)cup);
    WriteField(10, (unsigned char)longRound);
    WriteField(11, (unsigned char)((int)(time / 60.0f) % 10));
    WriteField(12, (unsigned char)((int)(time / 10.0f) % 6));
    WriteField(13, (unsigned char)((int)time % 10));
    WriteField(14, (unsigned char)((int)(10.0f * time) % 10));
    WriteField(15, (unsigned char)((int)(100.0f * time) % 10));
    WriteField(16, (unsigned char)((int)(1000.0f * time) % 10));
    WriteField(17, (unsigned char)((flags >> 16) & 1));
    WriteField(18, (unsigned char)(flags >> 8));
    WriteField(19, (unsigned char)flags);
    WriteField(20, a);
    WriteField(21, b);
    WriteField(22, c);
    WriteField(25, (unsigned char)(seed & 8));
    WriteField(26, (unsigned char)(seed & 0x30));
    WriteField(27, (unsigned char)(seed & 0xC0));
    WriteField(28, (unsigned char)(seed & 0x300));
    WriteField(29, (unsigned char)(seed & 0xC00));

    schedule = seed % 6;
    swap = lbl_80377C20[schedule];
    while ((*swap)[0] != -1) {
        unsigned char tmp = lbl_80677EE8[(*swap)[0]];
        lbl_80677EE8[(*swap)[0]] = lbl_80677EE8[(*swap)[1]];
        lbl_80677EE8[(*swap)[1]] = tmp;
        swap++;
    }
    rotation = seed % 5;
    {
    int i;
    unsigned char *p = lbl_80677EE8;
    for (i = 1; i < 24; i++) {
        unsigned short value = p[i] << rotation;
        p[i] = (value | ((value & 0x3E0) >> 5)) & 31;
    }
    }
    WriteField(23, rotation);
    WriteField(24, schedule);

    checksum = PackedChecksum();
    WriteBits(0, 2, checksum >> 2);
    WriteBits(123, 2, checksum);
    EncodeText(lbl_80677F04);
    lbl_806D1698 = 1;
    if (saveBackup == 1) {
        lbl_806D1699 = 1;
        EncodeText(lbl_80677F20);
    }
}

#pragma use_lmw_stmw reset
#pragma exceptions reset
