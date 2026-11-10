#ifndef SCI2CARD_SCORE_RECEIPT_PRIVATE_H
#define SCI2CARD_SCORE_RECEIPT_PRIVATE_H
/* Player record fields used by the printed score and encoded record. */
typedef struct ScoreReceiptPlayer {
    char name[13];
    unsigned char item;
    unsigned short wins;
    unsigned char pad10[4];
    unsigned int raceTime;
    unsigned char cup, longRound, reverse;
    unsigned char pad1B;
    int ccClass, character, kart;
    unsigned char pad28[0x199 - 0x28];
    unsigned char hasTitle;
    unsigned char pad19A;
    unsigned char b19B, b19C;
    unsigned char pad19D[0x1B1 - 0x19D];
    unsigned char b1B1;
} ScoreReceiptPlayer;
typedef struct ScoreReceiptFormat {
    const char *format;
    unsigned char line;
    unsigned char reserved[3];
} ScoreReceiptFormat;
extern ScoreReceiptPlayer g_playerData;
extern const ScoreReceiptFormat Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[10];
extern const char *Sci2Card_BuildRetryReceiptLine_data_803FFDF0[26];
extern const char *Sci2Card_BuildRetryReceiptLine_data_806CF0F0[2];
extern unsigned char lbl_806D1225;
extern char Sci2Card_BuildRetryReceiptLine_bss_806D1230[7];
extern int lbl_806D123C;
extern void *lbl_806D10A0;
extern const char lbl_806D3580[3], lbl_806D35BC[2], lbl_806D35C0[4];
extern const char lbl_806D35C4[3], lbl_806D35C8[7], lbl_806D35D0[4];
extern const char lbl_806D35D4[3], lbl_806D35D8[4], lbl_806D35DC[5];
extern const char lbl_806D35E4[4], lbl_806D35E8[5];
extern const char Sci2Card_BuildScoreReceiptLine_rodata_80318108[];
extern const float lbl_806D35F0;
extern void *Sci2Card_Singleton_Get(void);
extern unsigned char Sci2Card_SendCmdLedSet(void *, unsigned char, unsigned char);
extern unsigned char Sci2Card_SendCmdRegister(void *, char *, unsigned char, unsigned char, unsigned char);
extern void *memset(void *, int, unsigned long);
extern int sprintf(char *, const char *, ...);
extern char *strcat(char *, const char *);
extern int isJapanese(void);
extern char *Sci2Card_GetReceiptStringEntry(int);
extern int GetCoinMilage(ScoreReceiptPlayer *);
extern char *get_title_name_global(void *);
extern char *Sci2Card_BuildItemGetReceiptLine(void);
extern void Sci2Card_PopulateRankRowByMode(int *, unsigned char *, unsigned char *);
extern void fn_8018CC64(void);
extern char *fn_8018B2E4(void);
extern char *fn_8018B300(void);
extern void fn_8018B31C(ScoreReceiptPlayer *, int, int, int, int, int, int, int, int, int, int, int, float);
#endif
