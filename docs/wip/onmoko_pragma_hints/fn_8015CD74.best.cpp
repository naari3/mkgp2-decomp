#include "game/resultscene_private.h"
#include "game/singleton.h"

typedef struct {
    int pad0;
    int pad4;
    int anim8;
    int animC;
    int anim10;
    int anim14;
    int anim18;
} PopupAnim;

/* This TU owns its rodata (0x803682B0..0x80369238). Code reaches it through
 * the section anchor, which is what schedules the pool address early in the
 * ResultPartY ctor. */
extern "C" {
extern const char lbl_806D8798[];
extern const char lbl_806D879C[];
extern const char lbl_806D87A4[];
extern const char lbl_806D87AC[];
extern const char lbl_806D87B4[];
extern const char lbl_806D87BC[];
extern const unsigned char resultscene_rodata_803682B0[0x408] = {
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x33, 0x33, 0x33, 0x3F, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00, 0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00, 0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00, 0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00, 0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00, 0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00, 0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x44, 0xFA, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x7A, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x44, 0x7A, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x3B, 0x80, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x9C, 0x40, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x44, 0xFA, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x7A, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x44, 0x7A, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x3B, 0x80, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x9C, 0x40, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x44, 0xFA, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x7A, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x44, 0x7A, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x3B, 0x80, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x9C, 0x40, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
extern const int lbl_803686B8[13] = {0, 8, 12, 1, 5, 3, 6, 7, 9, 10, 2, 11, 4};
extern const float lbl_803686EC[3] = {0.0f, 0.0f, -5.0f};
extern const float lbl_803686F8[3] = {0.0f, 0.0f, -5.0f};
extern const float resultscene_rodata_80368704[3][4] = {
    {1.0f, 0.0f, 0.0f, 1.0f},
    {1.0f, 0.5f, 0.0f, 1.0f},
    {1.0f, 1.0f, 1.0f, 1.0f},
};
extern const char lbl_80368734[] = "BANDAI NAMCO GAMES";
extern const char lbl_80368748[] = " PRODUCTION STAFF";
extern const char lbl_8036875C[] = "PRODUCER";
extern const char lbl_80368768[] = "SHIN-ICHI ODAKE";
extern const char lbl_80368778[] = "DIRECTOR";
extern const char lbl_80368784[] = "TETSUYA SHINODA";
extern const char lbl_80368794[] = "PLANNING ADVISERS";
extern const char lbl_803687A8[] = "JYUN-ICHIRO KOYAMA";
extern const char lbl_803687BC[] = "PROCESS MANAGER";
extern const char lbl_803687CC[] = "YOSHIAKI NAKAUMA";
extern const char lbl_803687E0[] = "ELECTRICAL ENGINEERS";
extern const char lbl_803687F8[] = "KOUICHI ASANO";
extern const char lbl_80368808[] = "FUMIO MUNEKATA";
extern const char lbl_80368818[] = "MECHANICAL ENGINEERS";
extern const char lbl_80368830[] = "KAZUYA KUWASAWA";
extern const char lbl_80368840[] = "YASUHIRO WAKATSUKI";
extern const char lbl_80368854[] = "INDUSTRIAL &";
extern const char lbl_80368864[] = " GRAPHIC DESIGNERS";
extern const char lbl_80368878[] = "KAZUO UTSUKI";
extern const char lbl_80368888[] = "GRAPHIC SUPPORT";
extern const char lbl_80368898[] = "MISAO YOSHIDA";
extern const char lbl_803688A8[] = "SOUND STAFF";
extern const char lbl_803688B4[] = "YOSHIE ARAKAWA";
extern const char lbl_803688C4[] = "KOJI NAKAGAWA";
extern const char lbl_803688D4[] = "YURI MISUMI";
extern const char lbl_803688E0[] = "SOUND SUPPORT";
extern const char lbl_803688F0[] = "MASAKO OGAMI";
extern const char lbl_80368900[] = "PROGRAMMING ADVISER";
extern const char lbl_80368914[] = "YOSHIKAZU TAKENAKA";
extern const char lbl_80368928[] = "LOCALIZATION STAFF";
extern const char lbl_8036893C[] = "YUTA FUJISHIGE";
extern const char lbl_8036894C[] = "JASON ARNEY";
extern const char lbl_80368958[] = "CASEY UTSUNOMIYA";
extern const char lbl_8036896C[] = "     OTHER     ";
extern const char lbl_8036897C[] = "PRODUCTION STAFF";
extern const unsigned char data_8048FE08_rodata_80368990[0x10] = {
    0x4B, 0x41, 0x5A, 0x55, 0x4F, 0x81, 0x40, 0x53, 0x48, 0x49, 0x4F, 0x4D, 0x49, 0x00, 0x00, 0x00,
};
extern const char lbl_803689A0[] = "SAYAKA YAMATO";
extern const char lbl_803689B0[] = "SEIJI OOSHIMA";
extern const char lbl_803689C0[] = "MASAMI YAMANA";
extern const char lbl_803689D0[] = "AG+MM2+R+T+K+K+M+S";
extern const char lbl_803689E4[] = "MASAHIKO HIDAKA";
extern const char lbl_803689F4[] = "HIROSHI IMAMURA";
extern const char lbl_80368A04[] = "HIDEHIKO MOTONO";
extern const char lbl_80368A14[] = "DAISUKE MIYAHARA";
extern const char lbl_80368A28[] = "KAZUHITO USUI";
extern const char lbl_80368A38[] = "MASASHI KAJIKAWA";
extern const char lbl_80368A4C[] = "MIHO HAYASHI";
extern const char lbl_80368A5C[] = "SEIICHI FUDO";
extern const char lbl_80368A6C[] = "KAZUKI KAWAMURA";
extern const char lbl_80368A7C[] = "MEGUMI YAMASHITA";
extern const char lbl_80368A90[] = "SHIKANA KIMURA";
extern const char lbl_80368AA0[] = "NAOKI MATSUE";
extern const char lbl_80368AB0[] = "YUKI YAMAMOTO";
extern const char lbl_80368AC0[] = "SPECIAL THANKS";
extern const char lbl_80368AD0[] = "SHIGERU MIYAMOTO";
extern const char lbl_80368AE4[] = "(NINTENDO)";
extern const char lbl_80368AF0[] = "SHINJI HATANO";
extern const char lbl_80368B00[] = "HISASHI YUASA";
extern const char lbl_80368B10[] = "TADASHI SUGIYAMA";
extern const char lbl_80368B24[] = "JUN HIGASHIYAMA";
extern const char lbl_80368B34[] = "WATARU YAMAGUCHI";
extern const char lbl_80368B48[] = "AYA OYAMA";
extern const char lbl_80368B54[] = "YUSUKE NAKANO";
extern const char lbl_80368B64[] = "NARUHISA KAWANO";
extern const char lbl_80368B74[] = "KAZUE MURASE";
extern const char lbl_80368B84[] = "(BANDAI)";
extern const char lbl_80368B90[] = "MITSURU KATO";
extern const char lbl_80368BA0[] = "NAOKO KUBO";
extern const char lbl_80368BAC[] = "NINTENDO MARIOKART";
extern const char lbl_80368BC0[] = "PROJECT TEAM";
extern const char lbl_80368BD0[] = "WANGAN MIDNIGHT";
extern const char lbl_80368BE0[] = "AM SALES GROUP";
extern const char lbl_80368BF0[] = "AM PRODUCTION GROUP";
extern const char lbl_80368C04[] = "ALL MEMBERS OF";
extern const char lbl_80368C14[] = "AM COMPANY";
extern const char lbl_80368C20[] = "FONT PROVIDER";
extern const char lbl_80368C30[] = "?RYOBI LIMITED";
extern const char lbl_80368C40[] = "THE TYPEFACES";
extern const char lbl_80368C50[] = "INCLUDED HEREIN";
extern const char lbl_80368C60[] = "ARE DEVELOPED BY";
extern const char lbl_80368C74[] = "DYNACOMWARE.";
extern const unsigned char Scene_8015BF18_rodata_80368C84[0x18] = {
    0x00, 0x00, 0x00, 0x79, 0x00, 0x00, 0x00, 0x7D, 0x00, 0x00, 0x00, 0x77, 0x00, 0x00, 0x00, 0x7B,
    0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x7C,
};
extern const char lbl_80368C9C[] = "clCSSceneEnding";
extern const char lbl_80368CAC[0x14] = "clSceneInterface";
extern const char lbl_80368CC0[0xC] = "cone.dat";
extern const char lbl_80368CCC[0x14] = "it_l_00_star.dat";
extern const char lbl_80368CE0[0x10] = "k_kira13.dat";
extern const char lbl_80368CF0[] = "ERROR:csSceneEndeing  EndeingID is outside the range!!\n";
extern const char lbl_80368D28[] = "clStaffrollTask";
extern const char lbl_80368D38[] = "clCSSceneEnding::clTaskInterface";
extern const char lbl_80368D5C[] = "clAccoladeTask";
extern const char lbl_80368D6C[] = "clMessageTask";
extern const PopupAnim resultscene_nm1_rodata_80368D80[4] __attribute__((aligned(8))) = {
    {137, 135, 134, 136, 106, 436, 105},
    {141, 139, 138, 140, 108, 437, 107},
    {145, 143, 142, 144, 110, 438, 109},
    {149, 147, 146, 148, 112, 439, 111},
};
extern const unsigned char resultscene_rodata_80368DF0[0xC] = {
    0x83, 0x4A, 0x81, 0x5B, 0x83, 0x68, 0x82, 0xF0, 0x00, 0x00, 0x00, 0x00,
};
extern const unsigned char resultscene_rodata_80368DFC[0x10] = {
    0x93, 0xFC, 0x82, 0xEA, 0x82, 0xC4, 0x82, 0xAD, 0x82, 0xBE, 0x82, 0xB3, 0x82, 0xA2, 0x00, 0x00,
};
extern const unsigned char resultscene_rodata_80368E0C[0x10] = {
    0x8E, 0x9D, 0x82, 0xC1, 0x82, 0xC4, 0x82, 0xA2, 0x82, 0xC8, 0x82, 0xA2, 0x00, 0x00, 0x00, 0x00,
};
extern const unsigned char resultscene_rodata_80368E1C[0x10] = {
    0x83, 0x52, 0x83, 0x43, 0x83, 0x93, 0x82, 0xF0, 0x25, 0x64, 0x96, 0x87, 0x00, 0x00, 0x00, 0x00,
};
extern const unsigned char resultscene_rodata_80368E2C[0xC] = {
    0x8D, 0xEC, 0x82, 0xE7, 0x82, 0xC8, 0x82, 0xA2, 0x00, 0x00, 0x00, 0x00,
};
extern const unsigned char resultscene_rodata_80368E38[0xC] = {
    0x8D, 0x58, 0x90, 0x56, 0x82, 0xB7, 0x82, 0xE9, 0x00, 0x00, 0x00, 0x00,
};
extern const unsigned char resultscene_rodata_80368E44[0xC] = {
    0x8D, 0x58, 0x90, 0x56, 0x82, 0xB5, 0x82, 0xC8, 0x82, 0xA2, 0x00, 0x00,
};
extern const unsigned char resultscene_rodata_80368E50[0xC] = {
    0x8F, 0x91, 0x82, 0xAB, 0x82, 0xA9, 0x82, 0xA6, 0x82, 0xE9, 0x00, 0x00,
};
extern const unsigned char resultscene_rodata_80368E5C[0x10] = {
    0x8F, 0x91, 0x82, 0xAB, 0x82, 0xA9, 0x82, 0xA6, 0x82, 0xC8, 0x82, 0xA2, 0x00, 0x00, 0x00, 0x00,
};
extern const unsigned char resultscene_rodata_80368E6C[0x10] = {
    0x83, 0x52, 0x83, 0x93, 0x83, 0x65, 0x83, 0x42, 0x83, 0x6A, 0x83, 0x85, 0x81, 0x5B, 0x00, 0x00,
};
extern const unsigned char resultscene_rodata_80368E7C[0xC] = {
    0x91, 0xCE, 0x90, 0xED, 0x82, 0xB7, 0x82, 0xE9, 0x00, 0x00, 0x00, 0x00,
};
extern const unsigned char resultscene_rodata_80368E88[0xC] = {
    0x91, 0xCE, 0x90, 0xED, 0x82, 0xB5, 0x82, 0xC8, 0x82, 0xA2, 0x00, 0x00,
};
extern const unsigned char resultscene_rodata_80368E94[0xC] = {
    0x8B, 0x4C, 0x98, 0x5E, 0x82, 0xB7, 0x82, 0xE9, 0x00, 0x00, 0x00, 0x00,
};
extern const unsigned char resultscene_rodata_80368EA0[0xC] = {
    0x8B, 0x4C, 0x98, 0x5E, 0x82, 0xB5, 0x82, 0xC8, 0x82, 0xA2, 0x00, 0x00,
};
extern const void *const sdata_806CF750_rodata_80368EAC[96] = {
    (const void *)0x00000000,
    (const void *)0x00001CFB,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D05,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000002,
    (const void *)0x00001CFD,
    resultscene_rodata_80368DF0,
    resultscene_rodata_80368DFC,
    (const void *)0x00000001,
    (const void *)0x00001D05,
    resultscene_rodata_80368E0C,
    lbl_806D8798,
    (const void *)0x00000002,
    (const void *)0x00001CFE,
    resultscene_rodata_80368E1C,
    resultscene_rodata_80368DFC,
    (const void *)0x00000001,
    (const void *)0x00001D05,
    resultscene_rodata_80368E2C,
    lbl_806D8798,
    (const void *)0x00000002,
    (const void *)0x00001CFE,
    lbl_806D879C,
    resultscene_rodata_80368DFC,
    (const void *)0x00000001,
    (const void *)0x00001D05,
    resultscene_rodata_80368E2C,
    lbl_806D8798,
    (const void *)0x00000001,
    (const void *)0x00001CFB,
    lbl_806D87A4,
    lbl_806D8798,
    (const void *)0x00000001,
    (const void *)0x00001D05,
    resultscene_rodata_80368E2C,
    lbl_806D8798,
    (const void *)0x00000001,
    (const void *)0x00001D03,
    resultscene_rodata_80368E38,
    lbl_806D8798,
    (const void *)0x00000001,
    (const void *)0x00001D05,
    resultscene_rodata_80368E44,
    lbl_806D8798,
    (const void *)0x00000001,
    (const void *)0x00001D03,
    resultscene_rodata_80368E50,
    lbl_806D8798,
    (const void *)0x00000001,
    (const void *)0x00001D05,
    resultscene_rodata_80368E5C,
    lbl_806D8798,
    (const void *)0x00000002,
    (const void *)0x00001D02,
    resultscene_rodata_80368E6C,
    lbl_806D87AC,
    (const void *)0x00000002,
    (const void *)0x00001D05,
    resultscene_rodata_80368E6C,
    lbl_806D87B4,
    (const void *)0x00000001,
    (const void *)0x00001D02,
    resultscene_rodata_80368E7C,
    lbl_806D8798,
    (const void *)0x00000001,
    (const void *)0x00001D05,
    resultscene_rodata_80368E88,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D01,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D07,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000001,
    (const void *)0x00001D03,
    resultscene_rodata_80368E50,
    lbl_806D8798,
    (const void *)0x00000001,
    (const void *)0x00001D05,
    resultscene_rodata_80368E5C,
    lbl_806D8798,
    (const void *)0x00000001,
    (const void *)0x00001CFF,
    resultscene_rodata_80368E94,
    lbl_806D8798,
    (const void *)0x00000001,
    (const void *)0x00001D05,
    resultscene_rodata_80368EA0,
    lbl_806D8798,
};
extern const char lbl_8036902C[] = "insert card";
extern const char lbl_80369038[] = "Please insert";
extern const char lbl_80369048[] = "%d coin(s)";
extern const void *const sdata_806CF750_rodata_80369054[96] = {
    (const void *)0x00000000,
    (const void *)0x00001CFB,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D05,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000002,
    (const void *)0x00001CFD,
    lbl_806D87BC,
    lbl_8036902C,
    (const void *)0x00000000,
    (const void *)0x00001D05,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000002,
    (const void *)0x00001CFE,
    lbl_80369038,
    lbl_80369048,
    (const void *)0x00000000,
    (const void *)0x00001D05,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000002,
    (const void *)0x00001CFE,
    lbl_80369038,
    lbl_80369048,
    (const void *)0x00000000,
    (const void *)0x00001D05,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001CFB,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D05,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D03,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D05,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D03,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D05,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D02,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D05,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D02,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D05,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D01,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D07,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D03,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D05,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001CFF,
    lbl_806D8798,
    lbl_806D8798,
    (const void *)0x00000000,
    (const void *)0x00001D05,
    lbl_806D8798,
    lbl_806D8798,
};
extern const char lbl_803691D4[] = "clCSPartsGetTitle";
extern const char lbl_803691E8[] = "clYTaskInterface";
extern const char lbl_803691FC[] = "clCTaskInterface";
extern const char lbl_80369210[] = "clSceneInterface";
extern const char lbl_80369224[] = "clCSSceneGetTitle";

}

/* Result-scene objects, .text 0x8015C41C..0x8016219C.
 * This span's extabindex is not in ascending order, so dtk can't split it
 * further; it stays one NonMatching TU and gains functions as they match. */

struct VObj {
    virtual ~VObj();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
};

extern "C" {
extern void *Alloc(unsigned long size);
extern void HSD_StateInvalidate(int state);
}

struct SceneBase {
    SceneBase() { done = 0; }
    virtual ~SceneBase() {}
    virtual void Destroy() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    unsigned char done;
};



extern "C" {
extern unsigned char fn_8019083C(int id);
extern int fn_801909A4(int id);
}

extern "C" {
extern int g_cupId;
extern void DebugPrintf(const char *fmt, ...);
extern void fn_8014017C(void *p);
extern void fn_8011F994(int i);
}

struct ResultSceneX : SceneBase {
    ResultSceneX(int c) {
        cup = c;
        xc = 0;
        obj = 0;
        g_cupId = 0;
        if (cup < 0 || cup > 5) {
            DebugPrintf(lbl_80368CF0);
            cup = 0;
        }
    }
    virtual ~ResultSceneX();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    int cup;
    int xc;
    VObj *obj;
};

ResultSceneX::~ResultSceneX() {
    if (obj) delete obj;
    if (fn_8019083C(2)) fn_801909A4(2);
}

extern "C" {
extern void fn_8016219C(void *, int, void *);
extern char resultscene_nm1_data_806CF910[4];
}

struct ResultBuf {
    int a;
    int b;
    void **data;
    ResultBuf(int count) {
        a = 0; b = 0; data = 0;
        fn_8016219C(this, count, resultscene_nm1_data_806CF910);
    }
    ~ResultBuf() { if (data) delete data; }
};

struct ResultBufMid : ResultBuf {
    ResultBufMid(int n) : ResultBuf(n) {}
    ~ResultBufMid() {}
};

struct ResultBuf1 : ResultBufMid {
    ResultBuf1(int n) : ResultBufMid(n) {}
    ~ResultBuf1();
};

ResultBuf1::~ResultBuf1() {}

struct ResultBuf2 : ResultBufMid {
    ResultBuf2(int n) : ResultBufMid(n) {}
    ~ResultBuf2();
};

ResultBuf2::~ResultBuf2() {}

struct ResultInnerBase {
    char pad[0x14];
};

struct ResultInner : ResultInnerBase {
    virtual ~ResultInner();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
};

extern "C" {
extern void Sprite_Destroy(void *s, int flag);
extern void fn_80140810(void *p, int flag);
extern void fn_80121210(void);
}

struct ResultPart {
    virtual ~ResultPart() {}
    virtual void v0C() {}
    virtual void v10() {}
    virtual int v14() { return 1; }
};

struct ResultPartB : ResultPart {
    virtual ~ResultPartB();
    char pad4[0x1c - 4];
    void *p1c;
    ResultInner *inner;
    void *sprite;
};

ResultPartB::~ResultPartB() {
    Sprite_Destroy(sprite, 1);
    fn_80140810(p1c, 1);
    delete inner;
    fn_80121210();
}

extern "C" void fn_80192348(int id);

struct SpriteHolder {
    void *s;
    SpriteHolder(void *p) : s(p) {}
    ~SpriteHolder() throw();
};

SpriteHolder::~SpriteHolder() throw() {
    Sprite_Destroy(s, 1);
}

struct ResultPartC : ResultPart {
    virtual ~ResultPartC();
    int idx;
    char pad8[0x6c - 8];
    SpriteHolder spr;
};

ResultPartC::~ResultPartC() {
    if (idx % 2 == 0) {
        fn_80192348(0x20);
    } else {
        fn_80192348(0x21);
    }
}

extern "C" {
extern void LObjList_Destroy(void *l, int flag);
extern void KartDriver_Dtor(void *k, int flag);
}

struct ResultPair {
    char pad[0xc];
    VObj *a;
    VObj *b;
    ~ResultPair() {
        delete a;
        delete b;
    }
};

struct ResultKart {
    void *driver;
    ~ResultKart() { KartDriver_Dtor(driver, 1); }
};

struct ResultKarts {
    VObj *obj;
    void *lobj;
    ResultKart *karts[13];
    ~ResultKarts() {
        int i;
        delete obj;
        LObjList_Destroy(lobj, 1);
        for (i = 0; i < 13; i++) delete karts[i];
    }
};

struct ResCtrlR {
    ResCtrlR();
    ~ResCtrlR() {}
    int id;
    int pad4;
    int mode;
    int padc;
    unsigned char enable;
    unsigned char pad11[3];
    float x;
    float y;
    float z;
    float u;
    float v;
    char pad28[0x34 - 0x28];
    int c0;
    int c1;
    int c2;
    int c3;
    char pad44[0x58 - 0x44];
};

struct ResultPartY : ResultPart {
    ResultPartY(int idx);
    virtual ~ResultPartY();
    int mode;
    int half;
    int idx;
    float x10;
    unsigned char x14;
    char pad15[3];
    int x18;
    float x1c;
    int x20;
    float x24;
    float x28;
    ResultKarts *karts;
    char *buf;
    ResultPair *pair;
    ResCtrlR r38;
    ResCtrlR r90;
};

ResultPartY::~ResultPartY() {
    delete pair;
    if (buf) delete buf;
    delete karts;
    fn_80121210();
}

struct ItemMsgWnd {
    ItemMsgWnd();
    char body[0x5c];
};

struct CoinPrompt {
    CoinPrompt(int a, int b, int c, int d, int e);
    char body[0x20];
    ~CoinPrompt();
};

struct PtrVecBase {
    int cap;
    int n;
    void **data;
    ~PtrVecBase() { if (data) delete data; }
};

struct PtrVecMid : PtrVecBase {
    ~PtrVecMid() {}
};

struct PtrVec : PtrVecMid {
    ~PtrVec() {}
};

struct CoinPopupDetail {
    CoinPopupDetail(int mode, int active, int index);
    ~CoinPopupDetail();
    unsigned char active;
    char pad1[3];
    ResultBuf2 sprites;
    int state;
    int pad14;
    int mode;
    float ax;
    float ay;
    float bx;
    float by;
    int idxA;
    int idxB;
    int credits;
    unsigned char creditOn;
    unsigned char on;
    unsigned char extra;
    char pad3b;
    int nextIdx;
    int x40;
    int x44;
    int creditMgr;
    unsigned char changed;
    char pad4d[3];
    ResultBuf1 bufs;
    SpriteHolder h5c;
    SpriteHolder h60;
    SpriteHolder h64;
    SpriteHolder h68;
    float offs[4][2];
};


struct ResultText {
    ~ResultText() {}
};

extern "C" {
extern ItemMsgWnd *lbl_806D1A88;
extern void fn_80232284(ItemMsgWnd *wnd, float t);
extern void SpriteAnimHandle_Destroy(void *h, int flag);
extern void SpriteHandle_Destroy(void *h);
extern void fn_801699D8(int a, int b);
extern void fn_80169C44(void);
extern void fn_80120A08(int id);
}

static inline ItemMsgWnd *ItemMsg_Get() {
    return lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88 = new ItemMsgWnd);
}

struct ResultTop {
    ResultTop(int id) : id(id), x8(0), xc(0) {}
    virtual ~ResultTop() {}
    int id, x8, xc;
};

struct ResultMid : ResultTop {
    ResultMid(int id) : ResultTop(id) {}
    virtual ~ResultMid() {}
};

struct ResultSub : ResultMid {
    ResultSub(int a, int b);
    virtual ~ResultSub();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    int mode;
    int state;
    float timer;
    unsigned char flag;
    char pad1d[3];
    float timer2;
    float scale;
    int resource;
    unsigned char hasTitle;
    bool titleChanged;
    char pad2e[2];
    int title, rank, character;
    void *sprite;
    ResultPopupText *texts[2];
    void *anims[3];
    CoinPrompt *prompt;
    CoinPopupDetail *detail;
    float alpha;
};

struct ResultScreenObj : ResultMid {
    virtual ~ResultScreenObj();
    char pad10[0x3c - 0x10];
    void *sprite;
    ResultText *texts[2];
    void *anims[3];
    CoinPrompt *prompt;
    CoinPopupDetail *detail;
};

ResultScreenObj::~ResultScreenObj() {
    int i;
    if (prompt) delete prompt;
    if (detail) delete detail;
    for (i = 0; i < 3; i++) {
        if (anims[i]) {
            SpriteAnimHandle_Destroy(anims[i], 1);
            anims[i] = 0;
        }
    }
    for (i = 0; i < 2; i++) {
        if (texts[i]) {
            delete texts[i];
            texts[i] = 0;
        }
    }
    SpriteHandle_Destroy(sprite);
    fn_801699D8(0, 0);
    fn_80169C44();
    fn_80120A08(0x971);
    fn_80120A08(0x972);
    fn_80120A08(0x1ad9);
    fn_80120A08(0x1ada);
    fn_80120A08(0x152c);
    fn_80232284(ItemMsg_Get(), -1.0f);
}

CoinPopupDetail::~CoinPopupDetail() {
    void **it;
    for (it = sprites.data; it != sprites.data + sprites.b; ++it) Sprite_Destroy(*it, 1);
    for (it = bufs.data; it != bufs.data + bufs.b; ++it) {
        if (*it) delete (char *)*it;
    }
}

struct InputPlayer {
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual float Stick();
    virtual void v1C();
    virtual unsigned char Held(int mask);
    virtual void v24();
    virtual unsigned int Pressed(int mask);
};

struct ResultPartE608Sprite {
    char pad[0x20];
    float alpha;
};

struct ResultPartE608 {
    void *vt;
    int idx;
    int timer;
    int phase;
    unsigned char done;
    char pad11[0x48 - 0x11];
    unsigned int col[4];
    char pad58[0x6c - 0x58];
    ResultPartE608Sprite *spr;
};

extern "C" {
extern void *GetInputManager(void);
extern InputPlayer *InputMgr_GetPlayer(void *mgr, int index);
extern void Sprite_AdvanceAnim(void *s, float dt);
extern const float lbl_806D86A4;
extern const float lbl_806D86E8;
extern const float lbl_806D8674;
extern const float lbl_806D878C;
extern const float lbl_806D8790;

void fn_8015E608(ResultPartE608 *o) {
    InputPlayer *pl;
    if (o->done == 1) return;
    pl = InputMgr_GetPlayer(GetInputManager(), 0);
    switch (o->phase) {
    case 0: {
        float t = (float)o->timer / lbl_806D86A4;
        unsigned int c;
        o->spr->alpha = t;
        c = (0xFFFFFF00 | (unsigned char)((int)(lbl_806D86E8 * t)));
        o->col[0] = c;
        o->col[1] = c;
        o->col[2] = c;
        o->col[3] = c;
        if (o->timer >= 30) {
            o->timer = 0;
            o->phase++;
        }
        break;
    }
    case 1:
        if (o->timer >= 600 || pl->Pressed(0x2000) || pl->Stick() >= lbl_806D8790) {
            o->timer = 0;
            o->phase++;
        }
        break;
    case 2: {
        float t = lbl_806D8674 - (float)o->timer / lbl_806D86A4;
        unsigned int c;
        o->spr->alpha = t;
        c = (0xFFFFFF00 | (unsigned char)((int)(lbl_806D86E8 * t)));
        o->col[0] = c;
        o->col[1] = c;
        o->col[2] = c;
        o->col[3] = c;
        if (o->timer >= 30) {
            o->timer = 0;
            o->done = 1;
            o->phase++;
        }
        break;
    }
    }
    o->timer++;
    Sprite_AdvanceAnim(o->spr, lbl_806D878C);
}
}

struct ResultSceneA : SceneBase {
    ResultSceneA() {
        started = 0;
        sub = new ResultSub(0, 0);
    }
    virtual ~ResultSceneA() {
        if (sub) sub->Destroy();
    }
    virtual void Destroy() { delete this; }
    virtual void Update() {
        if (!started) started = 1;
        sub->Update();
        if (sub->state == 99) done = 1;
    }
    virtual void Draw() {
        if (started) {
            sub->Draw();
            HSD_StateInvalidate(-1);
        }
    }
    unsigned char started;
    ResultSub *sub;
};

extern "C" {

extern void MemoryManager_TimedFree(void *p);
extern void fn_8011FAFC(void *p, int n);
extern void fn_801A0004(void *p);
extern void fn_80160588(void *self, int n, bool confirm);
extern void fn_80161720(CoinPopupDetail *self);
extern char ResultPart_vtable_80490A58[];
extern const float lbl_806D86A4;
extern const float lbl_806D86D8;

void fn_8015CB24(VObj *p) {
    delete p;
}

typedef struct {
    char pad0[0x10];
    float a;
    char pad14[0x28 - 0x14];
    float b;
} Obj8015CD40;

int fn_8015CD40(Obj8015CD40 *o) {
    if (o->a > lbl_806D86D8 || o->b >= lbl_806D86A4) return 1;
    return 0;
}

typedef struct {
    char pad0[0x10];
    int state;
} Obj8015E1D4;

unsigned char fn_8015E1D4(Obj8015E1D4 *o) {
    return o->state == 6;
}

typedef struct {
    char pad0[0x10];
    unsigned char mode;
    char pad11[3];
    char sub[0x6c - 0x14];
    void *p6c;
} Obj8015E804;

void fn_8015E804(Obj8015E804 *o) {
    if (o->mode != 1) {
        fn_8011FAFC(o->sub, 3);
        fn_801A0004(o->p6c);
    }
}

unsigned char fn_8015E84C(Obj8015E804 *o) {
    return o->mode;
}


void fn_80160364(VObj *p) {
    delete p;
}

typedef struct {
    unsigned char active;
    char pad1[0x10 - 1];
    int ready;
    int cur;
    int next;
} Obj80161888;

int fn_801618CC(Obj80161888 *o, int v, bool unused);

void fn_80161888(Obj80161888 *o);

SceneBase *fn_80160238(void) {
    return new ResultSceneA;
}

SceneBase *fn_8015CB5C(int cup) {
    return new ResultSceneX(cup);
}

typedef struct {
    char pad0[0x10];
    int stage;
    char pad14[4];
    unsigned char on;
    char pad19[3];
    void *p1c;
    ResultInner *inner;
    void *p24;
    char res28[0x80 - 0x28];
    char res80[4];
} Obj8015E48C;

void fn_8015E48C(Obj8015E48C *o) {
    int i;
    if (o->on) {
        o->inner->v1C();
        fn_8014017C(o->p1c);
        fn_8011FAFC(o->res28, 0);
        fn_8011FAFC(o->res80, 7);
        if (o->stage >= 3) fn_801A0004(o->p24);
        for (i = 0; i < 8; i++) fn_8011F994(i);
        HSD_StateInvalidate(-1);
        o->on = 0;
    }
}

extern void fn_8023CD54(void *p);
extern void fn_8019FF8C(void *obj, int id, float *out);
extern void fn_801F93EC(void *t, float x, float y);
extern void *fn_801F8E58(void);
extern void fn_801F8A34(void *a, void *b, int c);
extern void fn_8016039C(CoinPopupDetail *p);
extern void fn_801678FC(int mode, float r, float g, float b, float a);

typedef struct {
    void *obj;
} ResultItem;

typedef struct {
    char pad0[0x14];
    int state;
    char pad18[0x40 - 0x18];
    void *texts[2];
    ResultItem *items[3];
    void *p54;
    void *p58;
    float alpha;
} ResultScreen;

void fn_8015F0FC(ResultScreen *s) {
    int i;
    if (s->state == 99) return;
    for (i = 0; i < 3; i++) {
        if (s->items[i]) fn_801A0004(s->items[i]->obj);
    }
    if (s->p54) fn_8023CD54(s->p54);
    if (s->items[0]) {
        float pos[14];
        void *mgr;
        int j;
        fn_8019FF8C(s->items[0]->obj, 0x23e5, pos);
        fn_801F93EC(s->texts[0], pos[0], 12.0f + pos[1]);
        mgr = fn_801F8E58();
        for (j = 0; j < 2; j++) fn_801F8A34(mgr, s->texts[j], 6);
    }
    if (s->p58) fn_8016039C((CoinPopupDetail *)s->p58);
    fn_801678FC(7, 0.0f, 0.0f, 0.0f, s->alpha);
}


extern void fn_80121E10(ResCtrlR *r);
extern void fn_8011FAFC_r(ResCtrlR *r, int n);
extern const float lbl_806D87CC;
extern const float lbl_806D87D0;
extern const float lbl_806D87D4;
extern const float lbl_806D87D8;
extern const float lbl_806D87DC;
extern const float lbl_806D87E0;
extern const float lbl_806D87E4;
extern const float lbl_806D87E8;
extern const float lbl_806D87EC;

void fn_8016039C(CoinPopupDetail *o) {
    void **it;
    void *mgr;
    if (o->on) {
        ResCtrlR r;
        r.mode = 2;
        r.u = lbl_806D87CC;
        r.v = lbl_806D87D0;
        r.enable = 1;
        r.x = lbl_806D87D4;
        r.y = lbl_806D87D8;
        r.z = lbl_806D87DC;
        r.c0 = 0x80;
        r.c1 = 0x80;
        r.c2 = 0x80;
        r.c3 = 0x80;
        fn_8011FAFC_r(&r, 4);
        fn_801A0004(o->h5c.s);
        if (o->extra) {
            fn_80121E10(&r);
            r.id = 0x1aea;
            r.enable = 1;
            r.x = lbl_806D87D4;
            r.y = lbl_806D87E0;
            r.z = lbl_806D87DC;
            fn_8011FAFC_r(&r, 4);
            fn_801A0004(o->h64.s);
            fn_80121E10(&r);
            r.id = 0x1875;
            r.enable = 1;
            r.x = lbl_806D87E4;
            r.y = lbl_806D87E8;
            r.z = lbl_806D87DC;
            fn_8011FAFC_r(&r, 4);
            fn_801A0004(o->h68.s);
            fn_80121E10(&r);
            r.id = 0x1874;
            r.enable = 1;
            r.x = lbl_806D87EC;
            r.y = lbl_806D87E8;
            r.z = lbl_806D87DC;
            fn_8011FAFC_r(&r, 4);
        }
    }
    for (it = o->sprites.data; it != o->sprites.data + o->sprites.b; ++it) fn_801A0004(*it);
    mgr = fn_801F8E58();
    {
        void **jt;
        for (jt = o->bufs.data; jt != o->bufs.data + o->bufs.b; ++jt) fn_801F8A34(mgr, *jt, 5);
    }
    fn_801A0004(o->h60.s);
}

typedef struct {
    int a;
    int a4;
    const char *textA;
    const char *textB;
    int b;
    int b14;
    const char *textC;
    const char *textD;
} PopupInfo;



extern PopupInfo *resultscene_nm1_data_806CF908[2];
extern const PopupAnim resultscene_nm1_rodata_80368D80[];
extern int isJapanese(void);
extern void **fn_80146000(void *v, int i);
extern unsigned char fn_801A024C(void *s);
extern void Sprite_SetupAnim(void *sprite, int anim, int loop, int arg);
extern void fn_80161128(CoinPopupDetail *o);

static inline PopupInfo *PopupInfo_Get(int k) {
    return &resultscene_nm1_data_806CF908[isJapanese()][k];
}

void fn_80161444(CoinPopupDetail *o) {
    int cnt = 0;
    void **it;
    for (it = o->sprites.data; it != o->sprites.data + o->sprites.b; ++it) {
        if (!fn_801A024C(*it)) cnt++;
    }
    if (cnt == 2) {
        if (o->mode == 0) {
            Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxA)->a].anim8, 1, 0);
        } else {
            Sprite_SetupAnim(*fn_80146000(&o->sprites, 1), resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxB)->b].anim8, 1, 0);
        }
        fn_80161128(o);
        o->x40 = 0x80;
        o->x44 = 0;
        o->state = 5;
        o->extra = 0;
        Sprite_SetupAnim(o->h5c.s, 0x11, 1, 0);
    }
}

void fn_80161720(CoinPopupDetail *o) {
    int anim;
    if (o->mode == 0) {
        anim = resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxA)->a].animC;
    } else {
        anim = resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxA)->a].anim14;
    }
    Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), anim, 1, 0);
    if (o->mode == 1) {
        anim = resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxB)->b].animC;
    } else {
        anim = resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxB)->b].anim14;
    }
    Sprite_SetupAnim(*fn_80146000(&o->sprites, 1), anim, 1, 0);
    fn_80161128(o);
    o->state = 3;
}

extern void fn_801FE348(void);
extern void fn_801A0500(void *s);
extern void TexMgr_SetTexture(void *tm, const char *fmt, ...);
extern const char lbl_806D884C[4];

void fn_801615A4(CoinPopupDetail *o) {
    if (o->active) {
        fn_801FE348();
        if (o->mode == 0) {
            Sprite_SetupAnim(*fn_80146000(&o->sprites, 1), resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxB)->b].anim18, 1, 0);
            TexMgr_SetTexture(*fn_80146000(&o->bufs, 2), lbl_806D884C);
            TexMgr_SetTexture(*fn_80146000(&o->bufs, 3), lbl_806D884C);
        } else {
            Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxA)->a].anim18, 1, 0);
            TexMgr_SetTexture(*fn_80146000(&o->bufs, 0), lbl_806D884C);
            TexMgr_SetTexture(*fn_80146000(&o->bufs, 1), lbl_806D884C);
        }
        fn_801A0500(o->h60.s);
        fn_80161128(o);
        o->state = 4;
    }
}

typedef struct {
    char pad[0xc];
    float x;
    float y;
    float sx;
    float sy;
} PopupSprite;

typedef struct {
    char pad[0x20];
    unsigned int col;
} PopupText;

extern void Sprite_SetAnimParam(void *spr, short from, short to);
extern unsigned char lbl_80598A60[0x2a];
extern void fn_80160A90(CoinPopupDetail *o);

static inline void PopupSprite_SetPos(PopupSprite *s, float x, float y) {
    s->x = x;
    s->y = y;
}

static inline void PopupSprite_SetScale(PopupSprite *s, float k) {
    s->sx = k;
    s->sy = k;
}

static inline void PopupText_SetCol(PopupText *t, unsigned int c) {
    t->col = c;
}

#define POPUP_SPR(o, i) ((PopupSprite *)*fn_80146000(&(o)->sprites, (i)))
#define POPUP_TXT(o, i) ((PopupText *)*fn_80146000(&(o)->bufs, (i)))

void fn_80161128(CoinPopupDetail *o) {
    PopupSprite_SetPos(POPUP_SPR(o, 0), o->ax, o->ay);
    PopupSprite_SetPos(POPUP_SPR(o, 1), o->bx, o->by);
    Sprite_SetAnimParam(*fn_80146000(&o->sprites, 0), 0x23e7, 0x1ecd);
    Sprite_SetAnimParam(*fn_80146000(&o->sprites, 1), 0x23e7, 0x1ecd);
    {
        PopupInfo *inf = PopupInfo_Get(o->idxA);
        Sprite_SetAnimParam(*fn_80146000(&o->sprites, 0), 0x1cfb, inf->a4);
    }
    {
        PopupInfo *inf = PopupInfo_Get(o->idxB);
        Sprite_SetAnimParam(*fn_80146000(&o->sprites, 1), 0x1cfb, inf->b14);
    }
    Sprite_SetAnimParam(*fn_80146000(&o->sprites, 1), 0x1565, 0x1566);
    Sprite_SetAnimParam(*fn_80146000(&o->sprites, 1), 0x1cf5, 0x1cf6);
    Sprite_SetAnimParam(*fn_80146000(&o->sprites, 1), 0x1563, 0x1564);
    if ((signed char)lbl_80598A60[0x20] == 2) {
        Sprite_SetAnimParam(*fn_80146000(&o->sprites, 0), 0x1cfb, 0x1d01);
    }
    if (o->mode == 0) {
        PopupSprite_SetScale(POPUP_SPR(o, 0), 1.0f);
        PopupSprite_SetScale(POPUP_SPR(o, 1), 0.8f);
        PopupText_SetCol(POPUP_TXT(o, 0), 0xFFFFFFFF);
        PopupText_SetCol(POPUP_TXT(o, 1), 0xFFFFFFFF);
        PopupText_SetCol(POPUP_TXT(o, 2), 0xC3D7F5FF);
        PopupText_SetCol(POPUP_TXT(o, 3), 0xC3D7F5FF);
    } else {
        PopupSprite_SetScale(POPUP_SPR(o, 0), 0.8f);
        PopupSprite_SetScale(POPUP_SPR(o, 1), 1.0f);
        PopupText_SetCol(POPUP_TXT(o, 0), 0xC3D7F5FF);
        PopupText_SetCol(POPUP_TXT(o, 1), 0xC3D7F5FF);
        PopupText_SetCol(POPUP_TXT(o, 2), 0xFFFFFFFF);
        PopupText_SetCol(POPUP_TXT(o, 3), 0xFFFFFFFF);
    }
    fn_80160A90(o);
}

}

struct RYScene {
    virtual ~RYScene();
    virtual unsigned char v0C();
    virtual void v10();
};

struct RYKart {
    void *driver;
    int x4;
    float z;
};

struct RYKarts {
    RYScene *scene;
    void *lobj;
    RYKart *karts[13];
    unsigned char on;
};

struct RYSub {
    int n;
    float x;
    float y;
    float z;
};

struct RYEntry {
    int on;
    float x;
    float y;
    float z;
    float rx;
    float ry;
    float rz;
    float scale;
    float vx, vy, vz;
    RYSub subs[10];
};

struct RYPair {
    unsigned char stopped;
    char pad1[3];
    int timer;
    int interval;
    VObj *a;
    VObj *b;
    RYEntry e[3];
};

struct ResultPartYD {
    void *vt;
    char pad4[0x14 - 4];
    unsigned char active;
    char pad15[0x2c - 0x15];
    RYKarts *karts;
    char *buf;
    RYPair *pair;
    char pad38[0x90 - 0x38];
    char res90[1];
};

extern "C" {
extern void fn_8013D660(VObj *p, float x, float y);
extern const float lbl_806D8760, lbl_806D86B8, lbl_806D86B4;
extern void fn_8013D4B0(VObj *p, float a);
extern void fn_8013D608(VObj *p, float x, float y, float z);
extern void fn_8013D59C(VObj *p, float x, float y, float z);
extern void fn_8011FAB8(void);
extern void SetCourseScene3D(RYScene *s);
extern void LObjList_ApplyForCObj(void *l);
extern void CObj_DebugVizPathFlush(RYScene *s);
extern void KartDriver_RenderTimed(void *d, int a, int b);

static inline void RYEntry_Draw(RYPair *p, RYEntry *e) {
        if (e->on >= 0) {
            int j;
            float sc;
            for (j = 0; j < 10; j++) {
                if (e->subs[j].n >= 0) {
                    float t = (float)e->subs[j].n / 15.0f;
                    float ssc;
                    t = lbl_806D8674 - t;
                    ssc = 0.035f * t;
                    VObj *b = p->b;
                    fn_8013D660(b, e->subs[j].x, e->subs[j].y);
                    fn_8013D4B0(p->b, t);
                    fn_8013D608(p->b, ssc, ssc, ssc);
                    p->b->v0C();
                }
            }
            sc = 0.05f * e->scale;
            fn_8013D660(p->a, e->x, e->y);
            fn_8013D59C(p->a, 0.017453292f * e->rx, 0.017453292f * e->ry, 0.017453292f * e->rz);
            fn_8013D608(p->a, sc, sc, sc);
            p->a->v0C();
        }
}

static inline void RYPair_Draw(RYPair *p) {
    int i;
    for (i = 0; i < 3; i++) RYEntry_Draw(p, &p->e[i]);
}

static inline void RYKarts_Draw(RYKarts *k) {
    if (k->on) {
        SetCourseScene3D(k->scene);
        if (k->scene->v0C()) {
            int i;
            LObjList_ApplyForCObj(k->lobj);
            CObj_DebugVizPathFlush(k->scene);
            for (i = 0; i < 13; i++) {
                RYKart *kt = k->karts[i];
                if (!(kt->z < -70.0f || kt->z > 70.0f)) {
                    KartDriver_RenderTimed(kt->driver, 0, 1);
                }
            }
            k->scene->v10();
        }
        SetCourseScene3D(0);
    }
}

static inline void RYBuf_Draw(char *buf) {
    fn_8011FAFC(buf + 0x58, 0);
    fn_8011FAFC(buf, 0);
}

void fn_8015DEBC(ResultPartYD *o) {
    if (o->active) {
        RYBuf_Draw(o->buf);
        fn_8011F994(0);
        RYPair_Draw(o->pair);
        fn_8011FAB8();
        RYKarts_Draw(o->karts);
        fn_8011FAFC(o->res90, 7);
        HSD_StateInvalidate(-1);
        o->active = 0;
    }
}

}

extern "C" {
extern void *lbl_806D10A0;
extern unsigned char g_playerData[];
extern unsigned char get_title_result(void *t, int *a, int *b, int *c);

static inline void *TitleTracker_Get(void) {
    return SINGLETON_INSTANCE(lbl_806D10A0);
}

int has_title_changed(void) {
    int a;
    int c;
    int b;
    void *t = TitleTracker_Get();
    if (!t || !get_title_result(t, &a, &b, &c)) return 0;
    if (a == 0) return 0;
    if (a == g_playerData[0x19b] && b == g_playerData[0x19c] && c == g_playerData[0x1b1]) return 0;
    return 1;
}
}

extern "C" {
extern const float lbl_806D87C8;
extern const float lbl_806D87C4;
extern const float lbl_806D8848;
extern const float lbl_806D87F4;
extern void fn_801F93D0(void *t, float sx, float sy);
extern void fn_801F93C8(void *t, float angle);

void fn_80160A90(CoinPopupDetail *o) {
    float offset = lbl_806D87C8;
    float scale = lbl_806D87DC;
    float pos[12];
    if (isJapanese()) {
        offset = lbl_806D87C4;
        scale = lbl_806D8848;
    }
    fn_8019FF8C(*fn_80146000(&o->sprites, 0), 0x23e5, pos);
    fn_801F93EC(*fn_80146000(&o->bufs, 0), (12.0f + pos[0]) + offset, 12.0f + pos[1]);
    fn_801F93D0(*fn_80146000(&o->bufs, 0), pos[2] * scale, pos[3] * scale);
    fn_801F93C8(*fn_80146000(&o->bufs, 0), pos[4]);
    {
        unsigned int c = POPUP_TXT(o, 0)->col;
        c = __rlwimi(c, (int)(lbl_806D87F4 * pos[8]), 0, 24, 31);
        POPUP_TXT(o, 0)->col = c;
    }
    fn_8019FF8C(*fn_80146000(&o->sprites, 0), 0x1ecd, pos);
    fn_801F93EC(*fn_80146000(&o->bufs, 1), pos[0] + offset, pos[1]);
    fn_801F93D0(*fn_80146000(&o->bufs, 1), pos[2] * scale, pos[3] * scale);
    fn_801F93C8(*fn_80146000(&o->bufs, 1), pos[4]);
    {
        unsigned int c = POPUP_TXT(o, 1)->col;
        c = __rlwimi(c, (int)(lbl_806D87F4 * pos[8]), 0, 24, 31);
        POPUP_TXT(o, 1)->col = c;
    }
    fn_8019FF8C(*fn_80146000(&o->sprites, 1), 0x23e5, pos);
    fn_801F93EC(*fn_80146000(&o->bufs, 2), (12.0f + pos[0]) + offset, 12.0f + pos[1]);
    fn_801F93D0(*fn_80146000(&o->bufs, 2), pos[2] * scale, pos[3] * scale);
    fn_801F93C8(*fn_80146000(&o->bufs, 2), pos[4]);
    {
        unsigned int c = POPUP_TXT(o, 2)->col;
        c = __rlwimi(c, (int)(lbl_806D87F4 * pos[8]), 0, 24, 31);
        POPUP_TXT(o, 2)->col = c;
    }
    fn_8019FF8C(*fn_80146000(&o->sprites, 1), 0x1ecd, pos);
    fn_801F93EC(*fn_80146000(&o->bufs, 3), pos[0] + offset, pos[1]);
    fn_801F93D0(*fn_80146000(&o->bufs, 3), pos[2] * scale, pos[3] * scale);
    fn_801F93C8(*fn_80146000(&o->bufs, 3), pos[4]);
    {
        unsigned int c = POPUP_TXT(o, 3)->col;
        c = __rlwimi(c, (int)(lbl_806D87F4 * pos[8]), 0, 24, 31);
        POPUP_TXT(o, 3)->col = c;
    }
}
}


extern "C" {
extern int CreditMgr_GetCreditCount(int slot);
extern int CreditMgr_GetCoinsPerCredit(int slot);
extern void fn_801F8E90(void *text);
extern void fn_8019FF6C(void *sprite, int enabled);
extern PopupInputState *g_pInputState;

static inline PopupInputState *PopupInput_Get() {
    return SINGLETON_INSTANCE(g_pInputState);
}

static inline PopupInputState *PopupInput_Peek() {
    return SINGLETON_INSTANCE(g_pInputState);
}

void fn_80160E04(CoinPopupDetail *o) {
    if (o->state < 2 && o->creditOn == 1) {
        bool unavailable;
        int credits = CreditMgr_GetCreditCount(o->creditMgr);
        unavailable = credits <= 0 || CreditMgr_GetCoinsPerCredit(o->creditMgr) == -1;
        if (!unavailable && o->credits != credits) {
            o->credits = credits;
            if (!isJapanese()) {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                void **text = fn_80146000(&o->bufs, 0);
                TexMgr_SetTexture(*text, info->textA, CreditMgr_GetCreditCount(o->creditMgr));
                fn_801F8E90(*fn_80146000(&o->bufs, 0));
            } else {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                void **text = fn_80146000(&o->bufs, 1);
                TexMgr_SetTexture(*text, info->textB, CreditMgr_GetCreditCount(o->creditMgr));
                fn_801F8E90(*fn_80146000(&o->bufs, 1));
            }
        } else if (unavailable == 1) {
            o->creditOn = 0;
            o->idxA = o->nextIdx;
            o->nextIdx = 0;
            o->mode = 0;
            {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                TexMgr_SetTexture(*fn_80146000(&o->bufs, 0), info->textA);
            }
            {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                TexMgr_SetTexture(*fn_80146000(&o->bufs, 1), info->textB);
            }
            fn_801F8E90(*fn_80146000(&o->bufs, 0));
            fn_801F8E90(*fn_80146000(&o->bufs, 1));
            if (o->state == 0) {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), resultscene_nm1_rodata_80368D80[info->a].pad0, 1, 0);
            } else {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), resultscene_nm1_rodata_80368D80[info->a].pad4, 1, 0);
                fn_8019FF6C(*fn_80146000(&o->sprites, 0), 1);
            }
            if (PopupInput_Peek()) {
                PopupInputState *input = PopupInput_Get();
                input->active = 1;
                input->x18 = 0;
                input->x1c = 0;
            }
            o->changed = 1;
            fn_80161128(o);
        }
    }
}
}


extern "C" {
extern const float lbl_806D880C;
extern const float lbl_806D8834;
extern const float lbl_806D87F0;
extern const float lbl_806D8838;
extern const float lbl_806D8830;
extern int Clamp_Int(int v, int lo, int hi);
extern void fn_801FE390(void);

static inline int Popup_CountIdle(CoinPopupDetail *o) {
    int cnt = 0;
    void **it;
    for (it = o->sprites.data; it != o->sprites.data + o->sprites.b; ++it) {
        if (!fn_801A024C(*it)) cnt++;
    }
    return cnt;
}

void fn_80160588(void *self, int step, bool confirm) {
    CoinPopupDetail *o = (CoinPopupDetail *)self;
    if (o->state == 0) {
        if (o->x44 <= 10) {
            o->x40 = (int)(lbl_806D8834 * ((float)o->x44 / lbl_806D880C));
            o->x44++;
        }
        int cnt = Popup_CountIdle(o);
        if (cnt == 2 && fn_801A024C(o->h60.s) != 1) {
            Sprite_SetupAnim(o->h60.s, 0x9c, 1, 0);
            fn_8019FF6C(o->h60.s, 1);
            o->state = 1;
            if (PopupInput_Peek()) {
                PopupInputState *input = PopupInput_Get();
                input->active = 1;
                input->x18 = 0;
                input->x1c = 0;
            }
            o->extra = 1;
            o->pad14 = -1;
        }
    } else if (o->state == 1) {
        if (!confirm) o->changed = 0;
        if (confirm == 1 && !o->changed) {
            o->state = 2;
            if (PopupInput_Peek()) {
                PopupInputState *input = PopupInput_Get();
                input->active = 0;
                input->x18 = 0;
                input->x1c = 0;
            }
        } else {
            int old = o->mode;
            o->mode = Clamp_Int(old + step, 0, 1);
            if (old != o->mode) fn_801FE390();
        }
    } else if (o->state == 2) {
        fn_80161720(o);
    } else if (o->state == 3) {
        fn_801615A4(o);
    } else if (o->state == 4) {
        fn_80161444(o);
    } else if (o->state == 5) {
        if (o->x44 <= 15) {
            o->x40 = (int)(lbl_806D8834 * (lbl_806D87DC - (float)o->x44 / lbl_806D87F0));
            o->x44++;
        }
        int cnt = Popup_CountIdle(o);
        if (cnt == 2) o->state = 6;
    }
    if (o->pad14 != o->mode && o->state < 3 && o->state > 0) {
        int anim;
        if (o->mode == 0) anim = resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxA)->a].pad4;
        else anim = resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxA)->a].anim14;
        Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), anim, 1, 0);
        if (o->mode == 1) anim = resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxB)->b].pad4;
        else anim = resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxB)->b].anim14;
        Sprite_SetupAnim(*fn_80146000(&o->sprites, 1), anim, 1, 0);
        fn_8019FF6C(*fn_80146000(&o->sprites, 0), 1);
        fn_8019FF6C(*fn_80146000(&o->sprites, 1), 1);
        ((PopupCursorSprite *)o->h60.s)->y = o->mode == 0 ? lbl_806D87C8 : lbl_806D8838;
        fn_80161128(o);
        o->pad14 = o->mode;
    }
    void **it;
    for (it = o->sprites.data; it != o->sprites.data + o->sprites.b; ++it) {
        Sprite_AdvanceAnim(*it, lbl_806D8830);
    }
    Sprite_AdvanceAnim(o->h5c.s, lbl_806D8830);
    Sprite_AdvanceAnim(o->h60.s, lbl_806D8830);
    Sprite_AdvanceAnim(o->h64.s, lbl_806D8830);
    Sprite_AdvanceAnim(o->h68.s, lbl_806D8830);
    fn_80160E04(o);
    fn_80160A90(o);
}
}


extern "C" {
extern unsigned char SoundMgr_Play(int id);
extern void Sprite_SetAnimTime(void *s, float time);
extern unsigned char fn_8019FE78(void *s);
extern void fn_80140344(void *p);
extern const float lbl_806D8678;
extern const float lbl_806D8784;
extern const float lbl_806D86F0;
extern const float lbl_806D8788;

void fn_8015E1E8(ResultPartBUpdate *o) {
    if (o->stage == 6) return;
    if (!o->soundStarted) {
        if (SoundMgr_Play(o->sound)) o->soundStarted = 1;
    }
    bool pressed = PopupInput_Get()->x18 == 1;
    switch (o->stage) {
    case 0: {
        unsigned int c = (unsigned char)(int)(lbl_806D86E8 * (lbl_806D8674 - o->timer / lbl_806D86A4));
        o->fadeCol[0] = c;
        o->fadeCol[1] = c;
        o->fadeCol[2] = c;
        o->fadeCol[3] = c;
        if (o->timer >= lbl_806D86A4) {
            o->timer = lbl_806D8678;
            o->stage = 1;
        }
        break;
    }
    case 1:
        if (o->timer >= lbl_806D8784 || (unsigned char)pressed) {
            o->timer = lbl_806D8678;
            o->stage = 2;
        }
        break;
    case 2: {
        unsigned int c = (unsigned char)(int)(lbl_806D8784 * (o->timer / lbl_806D86A4));
        o->innerCol[0] = c;
        o->innerCol[1] = c;
        o->innerCol[2] = c;
        o->innerCol[3] = c;
        if (o->timer >= lbl_806D86A4) {
            o->timer = lbl_806D8678;
            o->stage = 3;
            Sprite_SetAnimTime(o->sprite, lbl_806D8678);
        }
        break;
    }
    case 3:
        if (!fn_8019FE78(o->sprite)) {
            o->timer = lbl_806D8678;
            o->stage = 4;
        }
        break;
    case 4:
        if (o->timer >= lbl_806D86F0 || (unsigned char)pressed == 1) {
            o->timer = lbl_806D8678;
            o->stage = 5;
        }
        break;
    case 5: {
        unsigned int c = (unsigned char)(int)(lbl_806D86E8 * (o->timer / lbl_806D8788));
        o->fadeCol[0] = c;
        o->fadeCol[1] = c;
        o->fadeCol[2] = c;
        o->fadeCol[3] = c;
        if (o->timer >= lbl_806D8788) {
            o->timer = lbl_806D8678;
            o->stage = 6;
        }
        break;
    }
    }
    o->timer += lbl_806D8674;
    o->inner->v14();
    fn_80140344(o->p1c);
    if (o->stage >= 3) Sprite_AdvanceAnim(o->sprite, lbl_806D878C);
    if (!o->on) o->on = 1;
}
}



extern "C" {
extern const float lbl_806D8818, lbl_806D881C, lbl_806D8850, lbl_806D8854;
extern const float lbl_806D8804, lbl_806D87FC, lbl_806D8800;
extern void fn_801F8FCC(void *text, int mode);
}

CoinPopupDetail::CoinPopupDetail(int initialMode, int enabled, int index)
    : active(enabled), sprites(2), state(0), pad14(2), mode(initialMode),
      ax(lbl_806D8818), ay(lbl_806D8850), bx(lbl_806D881C), by(lbl_806D8850),
      idxA(index), idxB(index), credits(-1), creditOn(0), on(0), extra(0),
      nextIdx(0), x40(0), x44(0), creditMgr(-1), changed(1), bufs(4),
      h5c(new ResultPopupSprite(0x12, 1, 0)),
      h60(new ResultPopupSprite(0x9d, 1, 0)),
      h64(new ResultPopupSprite(0x4a, 1, 0)),
      h68(new ResultPopupSprite(0x74, 1, 0)) {
    if (idxA == 4 || idxA == 5 || idxA == 7 || idxA == 8) {
        creditOn = 1;
        nextIdx = idxA;
        int idx = 3;
        if (!lbl_80598A60[0x27]) idx = 2;
        idxA = idx;
        switch (nextIdx) {
        case 4: creditMgr = 2; break;
        case 5: creditMgr = 3; break;
        case 7: creditMgr = 1; break;
        case 8: creditMgr = 1; break;
        }
    }
    void **it;
    for (it = sprites.data; it != sprites.data + sprites.b; ++it) *it = 0;
    for (it = bufs.data; it != bufs.data + bufs.b; ++it) *it = 0;
    *fn_80146000(&sprites, 0) = new ResultPopupSprite(
        mode == 0 ? resultscene_nm1_rodata_80368D80[PopupInfo_Get(idxA)->a].pad0 : resultscene_nm1_rodata_80368D80[PopupInfo_Get(idxA)->a].anim10,
        1, 0);
    *fn_80146000(&sprites, 1) = new ResultPopupSprite(
        mode == 1 ? resultscene_nm1_rodata_80368D80[PopupInfo_Get(idxB)->b].pad0 : resultscene_nm1_rodata_80368D80[PopupInfo_Get(idxB)->b].anim10,
        1, 0);
    Sprite_SetAnimParam(*fn_80146000(&sprites, 0), 0x23e7, 0x1ecd);
    Sprite_SetAnimParam(*fn_80146000(&sprites, 1), 0x23e7, 0x1ecd);
    for (it = bufs.data; it != bufs.data + bufs.b; ++it) {
        *it = new ResultPopupText;
        TexMgr_SetTexture(*it, lbl_806D884C);
        ((ResultPopupText *)*it)->font = 1;
        fn_801F8FCC(*it, 1);
        ((ResultPopupText *)*it)->advance = lbl_806D8854;
    }
    {
        PopupInfo *info = PopupInfo_Get(idxA);
        TexMgr_SetTexture(*fn_80146000(&bufs, 0), info->textA);
    }
    {
        PopupInfo *info = PopupInfo_Get(idxA);
        TexMgr_SetTexture(*fn_80146000(&bufs, 1), info->textB);
    }
    {
        PopupInfo *info = PopupInfo_Get(idxB);
        TexMgr_SetTexture(*fn_80146000(&bufs, 2), info->textC);
    }
    {
        PopupInfo *info = PopupInfo_Get(idxB);
        TexMgr_SetTexture(*fn_80146000(&bufs, 3), info->textD);
    }
    for (it = bufs.data; it != bufs.data + bufs.b; ++it) fn_801F8E90(*it);
    fn_80160E04(this);
    PopupSprite_SetPos((PopupSprite *)h5c.s, lbl_806D87D4, lbl_806D8850);
    PopupSprite_SetPos((PopupSprite *)h60.s, lbl_806D87D4, lbl_806D8850);
    ((ResultPopupSprite *)h60.s)->angle = mode == 0 ? lbl_806D87C8 : lbl_806D8838;
    PopupSprite_SetPos((PopupSprite *)h64.s, lbl_806D8804, lbl_806D87E8);
    fn_8019FF6C(h64.s, 1);
    PopupSprite_SetPos((PopupSprite *)h68.s, lbl_806D87FC, lbl_806D8800);
    fn_8019FF6C(h68.s, 1);
    fn_80161128(this);
}

extern "C" {
extern unsigned char fn_80169DF0(void);
extern void InitRumbleController(int on);
extern void PreloadResource(int id);
extern const float lbl_806D8828, lbl_806D8858, lbl_806D885C;
extern const float lbl_806D8860, lbl_806D8864, lbl_806D8868, lbl_806D886C, lbl_806D8870;
extern const float lbl_806D8874, lbl_806D8878;
extern const char resultscene_nm1_data_806CF914[4], resultscene_nm1_data_806CF918[4], resultscene_nm1_data_806CF91C[4];
extern int g_characterId;
extern const char *get_title_name(void *, int, unsigned char, int, int);
extern const char *get_title_name_global(void *);
extern void SpriteGroup_CreateOrInit(void **, const char *, int, float, float);
extern void SpriteAnimParamBlock_SetAnimParamCached(void *, int, int);
extern void *SpriteHandle_CreateDefault(ResCtrlR *, int);
extern void SpriteHandle_SetActiveFlag(void *, int);
extern void fn_8011F804(void *, float, float);
extern void SpriteHandle_RecomputeCull(void *);
extern void fn_8023CD3C(CoinPrompt *, float, float);
extern void fn_8023CCF8(CoinPrompt *, float, float);
extern void fn_8023CCA0(CoinPrompt *, int);
}

ResultSub::ResultSub(int a, int b) : ResultMid(b) {
    mode = a;
    state = 0;
    timer = lbl_806D87C8;
    flag = fn_80169DF0();
    timer2 = lbl_806D87C8;
    hasTitle = 1;
    titleChanged = 0;
    resource = 0x1ad9;
    title = 0;
    rank = 0;
    character = 0;
    sprite = (void *)-1;
    scale = lbl_806D8828;
    alpha = lbl_806D87C8;
    detail = 0;
    if (!g_playerData[0x19b]) hasTitle = 0;
    void *tracker = TitleTracker_Get();
    if (tracker) get_title_result(tracker, &title, &rank, &character);
    InitRumbleController(1);
    PreloadResource(0x1ad9);
    PreloadResource(0x1ada);
    anims[0] = 0;
    anims[1] = 0;
    anims[2] = 0;
    SpriteGroup_CreateOrInit(&anims[0], resultscene_nm1_data_806CF914, 0, lbl_806D87D4, lbl_806D87D8);
    SpriteGroup_CreateOrInit(&anims[1], resultscene_nm1_data_806CF918, 0, lbl_806D87D4, lbl_806D87D8);
    SpriteGroup_CreateOrInit(&anims[2], resultscene_nm1_data_806CF91C, 0, lbl_806D8858, lbl_806D885C);
    SpriteAnimParamBlock_SetAnimParamCached(anims[2], 0x1ad4, 0x1ad9);
    ((ResultPopupSprite *)*(void **)anims[1])->alpha = lbl_806D87C8;
    fn_8019FF6C(*(void **)anims[1], 1);
    texts[0] = new ResultPopupText;
    int charId = g_characterId;
    TexMgr_SetTexture(texts[0], get_title_name(TitleTracker_Get(), title, rank, charId, character));
    texts[0]->color = 0xFFFFFF00;
    texts[0]->font = 1;
    fn_801F8FCC(texts[0], 1);
    if (isJapanese() == 1) {
        fn_801F93D0(texts[0], lbl_806D8860, lbl_806D8860);
        texts[0]->advance = lbl_806D8864;
    }
    fn_801F8E90(texts[0]);
    texts[1] = new ResultPopupText;
    TexMgr_SetTexture(texts[1], get_title_name_global(TitleTracker_Get()));
    texts[1]->color = 0xFFFFFF00;
    fn_801F8FCC(texts[1], 1);
    texts[1]->advance = lbl_806D8828;
    if (!isJapanese()) fn_801F93EC(texts[1], lbl_806D8868, lbl_806D886C);
    else fn_801F93EC(texts[1], lbl_806D8870, lbl_806D886C);
    fn_801F8E90(texts[1]);
    PreloadResource(0x152c);
    ResCtrlR r;
    r.id = 0x152c;
    sprite = SpriteHandle_CreateDefault(&r, 1);
    SpriteHandle_SetActiveFlag(sprite, 0);
    fn_8011F804(sprite, lbl_806D87D4, lbl_806D886C);
    SpriteHandle_RecomputeCull(sprite);
    prompt = new CoinPrompt(0x74, -1, 0x1872, -1, 5);
    fn_8023CD3C(prompt, lbl_806D8874, lbl_806D8800);
    fn_8023CCF8(prompt, lbl_806D8878, lbl_806D87E8);
    fn_8023CCA0(prompt, 0);
}

extern "C" {
extern void SetRumbleMode(int a, int b, int c);
extern void RumbleUpdate(void);
extern void SpriteAnimParamBlock_Reload(void *, int);
extern void SpriteHandle_SetCornerAlpha(void *, int);
extern void fn_8023CD24(CoinPrompt *, float, float);
extern void fn_8023CCCC(CoinPrompt *, float, float);
extern void fn_8023CDA8(CoinPrompt *);
extern void fn_8021A0B0(void *);
extern void *lbl_806D1A60;
extern const float lbl_806D87F8, lbl_806D8808, lbl_806D8810, lbl_806D8814;
extern const float lbl_806D8820, lbl_806D8824, lbl_806D882C;

static inline bool RSInput_Pressed(PopupInputState *in) {
    return in->x18 == 1;
}

static inline void RSDetail_Layout(CoinPopupDetail *d) {
    PopupSprite_SetPos(POPUP_SPR(d, 0), d->ax, d->ay);
    PopupSprite_SetPos(POPUP_SPR(d, 1), d->bx, d->by);
    fn_801F93EC(*fn_80146000(&d->bufs, 0), d->ax + d->offs[0][0], d->ay + d->offs[0][1]);
    fn_801F93EC(*fn_80146000(&d->bufs, 1), d->ax + d->offs[1][0], d->ay + d->offs[1][1]);
    fn_801F93EC(*fn_80146000(&d->bufs, 2), d->bx + d->offs[2][0], d->by + d->offs[2][1]);
    fn_801F93EC(*fn_80146000(&d->bufs, 3), d->bx + d->offs[3][0], d->by + d->offs[3][1]);
    {
        float k = lbl_806D8820;
        PopupSprite_SetPos((PopupSprite *)d->h60.s, k * (d->bx - d->ax) + d->ax, k * (d->by - d->ay) + d->ay);
    }
}

static inline void RSDetail_SetPos(CoinPopupDetail *d, float ax, float ay, float bx, float by) {
    d->ax = ax;
    d->ay = ay;
    d->bx = bx;
    d->by = by;
    RSDetail_Layout(d);
}

static inline int RSDetail_Mode(CoinPopupDetail *d) {
    return d->state < 2 ? 2 : d->mode;
}

static inline bool RSDetail_Accept(CoinPopupDetail *d) {
    return RSDetail_Mode(d) == 0;
}

static inline unsigned char RSDetail_Done(CoinPopupDetail *d) {
    return d->state == 6;
}

static inline void RSSub_SaveTitle(ResultSub *s) {
    void *t = TitleTracker_Get();
    if (s->titleChanged == 1 && t && get_title_result(t, &s->title, &s->rank, &s->character) == 1) {
        g_playerData[0x19b] = s->title;
        g_playerData[0x19c] = s->rank;
        g_playerData[0x1b1] = s->character;
    }
}

static inline void RSSub_DeletePrompt(ResultSub *s) {
    if (s->prompt) {
        delete s->prompt;
        s->prompt = 0;
    }
}

/* ResultSub::Update (vtable slot of resultscene_nm1_data_80490A90). NonMatching: only the
 * input pointer (r29) and the ItemMsgWnd singleton temp (r30) are swapped. */
void result_screen_update(ResultSub *s) {
    PopupInputState *in = PopupInput_Get();
    bool pressed = RSInput_Pressed(in);
    int i;
    if (pressed == 1) SetRumbleMode(0, 1, 1);
    switch (s->state) {
    case 0:
        if (lbl_806D87C8 == s->timer) fn_8023CCA0(s->prompt, 1);
        {
            float a = s->timer / lbl_806D87F0;
            ((ResultPopupSprite *)*(void **)s->anims[1])->alpha = a;
            s->texts[0]->color = (0xFFFFFF00 | (unsigned char)((int)(lbl_806D87F4 * a)));
        }
        if (s->timer >= lbl_806D87F0) {
            SpriteAnimParamBlock_Reload(s->anims[2], 0x1dd);
            SpriteAnimParamBlock_SetAnimParamCached(s->anims[2], 0x1ad4, 0x1ad9);
            SpriteAnimParamBlock_Reload(s->anims[0], 0x1c1);
            ((ResultPopupSprite *)*(void **)s->anims[1])->alpha = lbl_806D87DC;
            s->texts[0]->color = 0xFFFFFFFF;
            s->state = 1;
            s->timer = lbl_806D87C8;
        }
        break;
    case 1:
        fn_801699D8(0, 1);
        s->state = 2;
        s->timer = lbl_806D87C8;
        break;
    case 2:
        if (s->timer >= lbl_806D87F8 || pressed) {
            RSSub_DeletePrompt(s);
            if (s->hasTitle) {
                s->state = 5;
                SpriteHandle_SetCornerAlpha(s->sprite, 0);
                SpriteHandle_SetActiveFlag(s->sprite, 1);
                SpriteAnimParamBlock_Reload(s->anims[2], 0xc7);
                SpriteAnimParamBlock_SetAnimParamCached(s->anims[2], 0x1ad4, 0x1ad9);
                s->prompt = new CoinPrompt(0x74, 0x4a, 0x1874, 0x1875, 5);
                fn_8023CD3C(s->prompt, lbl_806D87FC, lbl_806D8800);
                fn_8023CCF8(s->prompt, lbl_806D87EC, lbl_806D87E8);
                fn_8023CD24(s->prompt, lbl_806D8804, lbl_806D87E8);
                fn_8023CCCC(s->prompt, lbl_806D87E4, lbl_806D87E8);
            } else {
                s->state = 3;
            }
            s->timer = lbl_806D87C8;
        }
        break;
    case 3:
        s->alpha = s->timer / lbl_806D8808;
        if (s->timer >= lbl_806D8808) {
            s->state = 4;
            fn_8021A0B0(lbl_806D1A60);
        }
        break;
    case 4:
        s->titleChanged = 1;
        s->state = 99;
        s->timer = lbl_806D87C8;
        RSSub_SaveTitle(s);
        break;
    case 5:
        if (s->timer <= lbl_806D880C) {
            float y = lbl_806D8810 * (s->timer / lbl_806D880C) + lbl_806D87D8;
            ((ResultPopupSprite *)*(void **)s->anims[0])->y = y;
            ((ResultPopupSprite *)*(void **)s->anims[1])->y = y;
        }
        if (lbl_806D87F0 == s->timer) {
            SpriteAnimParamBlock_Reload(s->anims[2], 0xc8);
            SpriteAnimParamBlock_SetAnimParamCached(s->anims[2], 0x1ad4, 0x1ada);
        }
        if (s->timer >= lbl_806D8808) {
            int v = (int)(lbl_806D87F4 * ((s->timer - lbl_806D8808) / lbl_806D880C));
            s->texts[1]->color = (0xFFFFFF00 | (unsigned char)(v));
            SpriteHandle_SetCornerAlpha(s->sprite, v);
        }
        if (s->timer >= lbl_806D8814) {
            s->state = 6;
            s->timer = lbl_806D87C8;
            SpriteAnimParamBlock_Reload(s->anims[2], 0x1dd);
            SpriteAnimParamBlock_SetAnimParamCached(s->anims[2], 0x1ad4, 0x1ada);
            s->detail = new CoinPopupDetail(0, 1, 0);
            RSDetail_SetPos(s->detail, lbl_806D8818, lbl_806D87D4, lbl_806D881C, lbl_806D87D4);
            s->scale = lbl_806D880C;
        }
        break;
    case 6:
        if (!s->detail) {
            s->detail = new CoinPopupDetail(0, 1, 0);
            RSDetail_SetPos(s->detail, lbl_806D8818, lbl_806D87D4, lbl_806D881C, lbl_806D87D4);
        }
        s->scale -= lbl_806D8824;
        if (s->scale <= lbl_806D87C8) {
            s->scale = lbl_806D8828;
            fn_801618CC((Obj80161888 *)s->detail, 1, 0);
            fn_80161888((Obj80161888 *)s->detail);
        }
        if (RSDetail_Mode(s->detail) != 2 || s->scale <= lbl_806D87C8) {
            s->titleChanged = RSDetail_Accept(s->detail);
            s->state = 7;
            s->timer = lbl_806D87C8;
            s->scale = lbl_806D8828;
            RSSub_SaveTitle(s);
        }
        break;
    case 7:
        if (s->timer >= lbl_806D882C && RSDetail_Done(s->detail) == 1) {
            s->state = 8;
            s->timer = lbl_806D87C8;
        }
        break;
    case 8:
        s->alpha = s->timer / lbl_806D8808;
        if (s->timer >= lbl_806D8808) {
            SpriteHandle_SetActiveFlag(s->sprite, 0);
            s->state = 99;
            s->timer = lbl_806D87C8;
            fn_8021A0B0(lbl_806D1A60);
            RSSub_DeletePrompt(s);
            s->scale = lbl_806D8828;
        }
        break;
    }
    s->timer += lbl_806D87DC;
    for (i = 0; i < 3; i++) {
        if (s->anims[i]) Sprite_AdvanceAnim(*(void **)s->anims[i], lbl_806D8830);
    }
    if (s->prompt) fn_8023CDA8(s->prompt);
    if (s->detail) {
        if (s->state == 6) fn_80160588(s->detail, in->x14, RSInput_Pressed(in));
        else fn_80160588(s->detail, 0, 0);
    }
    SpriteHandle_RecomputeCull(s->sprite);
    RumbleUpdate();
    fn_80232284(ItemMsg_Get(), s->scale);
}

void fn_80161888(Obj80161888 *o) {
    o->active = 1;
    fn_801618CC(o, o->next, 1);
    fn_80161720((CoinPopupDetail *)o);
}

int fn_801618CC(Obj80161888 *o, int v, bool unused) {
    if (o->ready == 0) return 0;
    o->next = v;
    o->cur = -1;
    fn_80160588(o, 0, unused);
    return 1;
}
}

extern "C" {
extern int rand(void);
extern const float lbl_806D86EC, lbl_806D8770, lbl_806D8774, lbl_806D8778, lbl_806D877C, lbl_806D8780;

static inline void RYSub_Reset(RYSub *sub) {
    sub->n = -1;
    sub->x = sub->y = sub->z = lbl_806D8678;
}

static inline void RYEntry_Reset(RYEntry *entry) {
    entry->on = -1;
    entry->x = entry->y = entry->z = lbl_806D8678;
    entry->rx = entry->ry = entry->rz = lbl_806D8678;
    entry->vx = entry->vy = entry->vz = lbl_806D8678;
    entry->scale = lbl_806D8674;
    for (int j = 0; j < 10; ++j) RYSub_Reset(&entry->subs[j]);
}

static inline void RYEntry_AdvanceSubs(RYEntry *entry) {
    for (int j = 0; j < 10; ++j) {
        RYSub *sub = &entry->subs[j];
        if (sub->n >= 0) {
            if (++sub->n >= 15) RYSub_Reset(sub);
        }
    }
}

static inline void RYPair_Spawn(RYPair *p) {
    for (int i = 0; i < 3; ++i) {
        if (p->e[i].on < 0) {
            p->e[i].on = 0;
            p->e[i].vx = lbl_806D86EC * (float)-(rand() % 20 + 40);
            p->e[i].vy = lbl_806D8678;
            p->e[i].vz = lbl_806D8678;
            p->e[i].x = lbl_806D8770 + (float)(rand() % 600);
            p->e[i].y = lbl_806D8774;
            break;
        }
    }
}

void fn_8015D9F0(RYPair *p) {
    if (!p->stopped) {
        if (++p->timer >= p->interval) {
            RYPair_Spawn(p);
            p->timer = 0;
            p->interval = rand() % 100 + 60;
        }
    }
    for (int i = 0; i < 3; ++i) {
        if (p->e[i].on >= 0) {
            p->e[i].vy += lbl_806D86EC;
            p->e[i].x += p->e[i].vx;
            p->e[i].y += p->e[i].vy;
            p->e[i].on++;
            if ((p->e[i].on & 3) == 0) {
                RYEntry *entry = &p->e[i];
                for (int j = 0; j < 10; ++j) {
                    RYSub *sub = &entry->subs[j];
                    if (sub->n < 0) {
                        sub->n = 0;
                        sub->x = (lbl_806D86EC * (float)(rand() % 70) + p->e[i].x) + lbl_806D8778;
                        sub->y = (p->e[i].y - lbl_806D86EC * (float)(rand() % 150)) - lbl_806D877C;
                        sub->z = p->e[i].z;
                        break;
                    }
                }
            }
            RYEntry_AdvanceSubs(&p->e[i]);
            if (p->e[i].y >= lbl_806D8780) RYEntry_Reset(&p->e[i]);
        }
    }
}
}

extern "C" {
extern unsigned long strlen(const char *text);
extern ResultMessageRecord lbl_80490080[98];
extern const char lbl_806D8650[4];
extern const char lbl_806D8654[4];
extern const char lbl_806D865C[4];

/* Initialize cached lengths for the existing result-message records. */
void fn_8015E928(void) {
    const char *pool = (const char *)resultscene_rodata_803682B0;
    lbl_80490080[0].length = strlen(pool + 0x484);
    lbl_80490080[1].length = strlen(pool + 0x498);
    lbl_80490080[2].length = strlen(pool + 0x4ac);
    lbl_80490080[3].length = strlen(pool + 0x4b8);
    lbl_80490080[4].length = strlen(pool + 0x4c8);
    lbl_80490080[5].length = strlen(pool + 0x4d4);
    lbl_80490080[6].length = strlen(pool + 0x4e4);
    lbl_80490080[7].length = strlen(pool + 0x4f8);
    lbl_80490080[8].length = strlen(pool + 0x50c);
    lbl_80490080[9].length = strlen(pool + 0x51c);
    lbl_80490080[10].length = strlen(pool + 0x530);
    lbl_80490080[11].length = strlen(pool + 0x548);
    lbl_80490080[12].length = strlen(pool + 0x558);
    lbl_80490080[13].length = strlen(pool + 0x568);
    lbl_80490080[14].length = strlen(lbl_806D8650);
    lbl_80490080[15].length = strlen(pool + 0x580);
    lbl_80490080[16].length = strlen(pool + 0x590);
    lbl_80490080[17].length = strlen(pool + 0x5a4);
    lbl_80490080[18].length = strlen(pool + 0x5b4);
    lbl_80490080[19].length = strlen(pool + 0x5c8);
    lbl_80490080[20].length = strlen(pool + 0x5d8);
    lbl_80490080[21].length = strlen(pool + 0x5e8);
    lbl_80490080[22].length = strlen(pool + 0x5f8);
    lbl_80490080[23].length = strlen(pool + 0x604);
    lbl_80490080[24].length = strlen(pool + 0x614);
    lbl_80490080[25].length = strlen(pool + 0x624);
    lbl_80490080[26].length = strlen(pool + 0x630);
    lbl_80490080[27].length = strlen(pool + 0x640);
    lbl_80490080[28].length = strlen(pool + 0x650);
    lbl_80490080[29].length = strlen(pool + 0x664);
    lbl_80490080[30].length = strlen(pool + 0x678);
    lbl_80490080[31].length = strlen(pool + 0x68c);
    lbl_80490080[32].length = strlen(pool + 0x69c);
    lbl_80490080[33].length = strlen(pool + 0x6a8);
    lbl_80490080[34].length = strlen(pool + 0x6bc);
    lbl_80490080[35].length = strlen(pool + 0x6cc);
    lbl_80490080[36].length = strlen(pool + 0x6e0);
    lbl_80490080[37].length = strlen(pool + 0x6f0);
    lbl_80490080[38].length = strlen(pool + 0x700);
    lbl_80490080[39].length = strlen(pool + 0x710);
    lbl_80490080[40].length = strlen(pool + 0x720);
    lbl_80490080[41].length = strlen(pool + 0x734);
    lbl_80490080[42].length = strlen(pool + 0x744);
    lbl_80490080[43].length = strlen(pool + 0x754);
    lbl_80490080[44].length = strlen(pool + 0x764);
    lbl_80490080[45].length = strlen(pool + 0x778);
    lbl_80490080[46].length = strlen(pool + 0x788);
    lbl_80490080[47].length = strlen(pool + 0x79c);
    lbl_80490080[48].length = strlen(pool + 0x7ac);
    lbl_80490080[49].length = strlen(pool + 0x7bc);
    lbl_80490080[50].length = strlen(pool + 0x7cc);
    lbl_80490080[51].length = strlen(pool + 0x7e0);
    lbl_80490080[52].length = strlen(pool + 0x7f0);
    lbl_80490080[53].length = strlen(pool + 0x800);
    lbl_80490080[54].length = strlen(pool + 0x810);
    lbl_80490080[55].length = strlen(pool + 0x820);
    lbl_80490080[56].length = strlen(pool + 0x834);
    lbl_80490080[57].length = strlen(pool + 0x840);
    lbl_80490080[58].length = strlen(pool + 0x834);
    lbl_80490080[59].length = strlen(pool + 0x850);
    lbl_80490080[60].length = strlen(pool + 0x834);
    lbl_80490080[61].length = strlen(pool + 0x860);
    lbl_80490080[62].length = strlen(pool + 0x834);
    lbl_80490080[63].length = strlen(pool + 0x874);
    lbl_80490080[64].length = strlen(pool + 0x834);
    lbl_80490080[65].length = strlen(pool + 0x884);
    lbl_80490080[66].length = strlen(pool + 0x834);
    lbl_80490080[67].length = strlen(pool + 0x898);
    lbl_80490080[68].length = strlen(pool + 0x834);
    lbl_80490080[69].length = strlen(pool + 0x8a4);
    lbl_80490080[70].length = strlen(pool + 0x834);
    lbl_80490080[71].length = strlen(pool + 0x8b4);
    lbl_80490080[72].length = strlen(pool + 0x834);
    lbl_80490080[73].length = strlen(pool + 0x8c4);
    lbl_80490080[74].length = strlen(pool + 0x8d4);
    lbl_80490080[75].length = strlen(pool + 0x8e0);
    lbl_80490080[76].length = strlen(lbl_806D8654);
    lbl_80490080[77].length = strlen(pool + 0x8f0);
    lbl_80490080[78].length = strlen(lbl_806D8654);
    lbl_80490080[79].length = strlen(lbl_806D865C);
    lbl_80490080[80].length = strlen(pool + 0x8fc);
    lbl_80490080[81].length = strlen(pool + 0x910);
    lbl_80490080[82].length = strlen(pool + 0x484);
    lbl_80490080[83].length = strlen(pool + 0x920);
    lbl_80490080[84].length = strlen(pool + 0x910);
    lbl_80490080[85].length = strlen(pool + 0x484);
    lbl_80490080[86].length = strlen(pool + 0x930);
    lbl_80490080[87].length = strlen(pool + 0x484);
    lbl_80490080[88].length = strlen(pool + 0x940);
    lbl_80490080[89].length = strlen(pool + 0x954);
    lbl_80490080[90].length = strlen(pool + 0x484);
    lbl_80490080[91].length = strlen(pool + 0x964);
    lbl_80490080[92].length = strlen(pool + 0x970);
    lbl_80490080[93].length = strlen(pool + 0x980);
    lbl_80490080[94].length = strlen(pool + 0x990);
    lbl_80490080[95].length = strlen(pool + 0x9a0);
    lbl_80490080[96].length = strlen(pool + 0x9b0);
    lbl_80490080[97].length = strlen(pool + 0x9c4);
}
}

__declspec(section ".ctors") static void (*const resultMessageInit)(void) = fn_8015E928;


extern "C" {
extern const float resultscene_rodata_80368704[][4];
extern const float lbl_806D8758, lbl_806D875C, lbl_806D8760;
extern void fn_80169468(int mode, int resource, int flags, float x, float y,
                        float r, float g, float b, float alpha);

void fn_8015D4F8(void *unused, int color, const char *text, float x, float y) {
    if (!text) return;
    unsigned long length = strlen(text);
    float alpha = lbl_806D8674;
    if (y >= lbl_806D8758) { float d = y - lbl_806D8758; alpha -= d * lbl_806D875C; }
    const float *b;
    const float *g;
    const float *r = resultscene_rodata_80368704[color];
    b = r + 2;
    g = r + 1;
    for (unsigned int i = 0; i < length; ++i, ++text) {
        if (!*text) return;
        if (*text == 'i') {
            fn_80169468(1, 0x1dc5, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text >= 'A' && *text <= 'Z') {
            fn_80169468(1, *text + 0x1d60, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text >= 'a' && *text <= 'z') {
            fn_80169468(1, *text + 0x1d40, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '.') {
            fn_80169468(1, 0x1dbb, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '<') {
            fn_80169468(1, 0x1dbc, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '>') {
            fn_80169468(1, 0x1dbd, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '(') {
            fn_80169468(1, 0x1dbe, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == ')') {
            fn_80169468(1, 0x1dbf, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '2') {
            fn_80169468(1, 0x1dc0, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '?') {
            fn_80169468(1, 0x1dc1, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '+') {
            fn_80169468(1, 0x1dc2, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '-') {
            fn_80169468(1, 0x1dc3, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '&') {
            fn_80169468(1, 0x1dc4, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        }
    }
}
}

struct ResultFlake;
struct ResultVec { float x, y, z; };
extern "C" {
extern void KartMovement_ResetOnGoal(void *drv);
extern void PSMTXScale(float m[3][4], float x, float y, float z);
extern void PSMTXIdentity(float m[3][4]);
extern void PSMTXConcat(float a[3][4], float b[3][4], float ab[3][4]);
extern void PSMTXRotRad(float m[3][4], char axis, float rad);
extern void PSMTXTrans(float m[3][4], float x, float y, float z);
extern void CObj_LoadIntoGX(VObj *cam, ResultVec *v);
extern void CObj_ApplyViewport(VObj *cam, ResultVec *v);
extern void ProcessSystemTick(int);
extern int fn_80169E20(void);
extern void fn_8013D738(VObj *f, float a, float b);
extern void fn_8013D634(VObj *f, float x, float y, float z);
extern void ClSound_PlayBgmStream(int ch, int n);
extern unsigned char fn_801932F8(void);
extern void clStream_setVolume(int ch, unsigned char vol);
extern const short lbl_806D8664[4];
extern const float lbl_806D866C, lbl_806D8670, lbl_806D867C, lbl_806D8680, lbl_806D8684, lbl_806D8688;
extern const float lbl_806D868C, lbl_806D8690, lbl_806D8694, lbl_806D8698, lbl_806D869C, lbl_806D86A0;
extern const float lbl_806D86A8, lbl_806D86AC, lbl_806D86B0, lbl_806D86B4, lbl_806D86B8, lbl_806D86BC;
extern const float lbl_806D86C0, lbl_806D86C4, lbl_806D86C8;
}

struct ResultCam { char d[0x3084]; ResultCam(const char *path); };
struct ResultModel { char d[0x28]; ResultModel(const char *path, unsigned char flag); };
struct ResultDriver { char d[0x384]; ResultDriver(int a, int id, float *mtx, int b, int c, int d); };
struct ResultFlake { char d[0x20]; ResultFlake(const char *path, int flag); };


struct ResultKartSlot {
    ResultKartSlot(int n) {
        float t[3][4];
        float s[3][4];
        float r[3][4];
        driver = new ResultDriver(6, n, &out[0][0], 0, 0, 0);
        id = n;
        x = lbl_806D868C;
        KartMovement_ResetOnGoal(driver);
        PSMTXScale(s, lbl_806D8674, lbl_806D8674, lbl_806D8674);
        PSMTXIdentity(m);
        PSMTXConcat(s, m, m);
        PSMTXRotRad(r, 'Z', lbl_806D8690);
        PSMTXConcat(r, m, m);
        PSMTXRotRad(r, 'Y', lbl_806D8694);
        PSMTXConcat(r, m, m);
        PSMTXTrans(t, lbl_806D8698, lbl_806D8698, lbl_806D869C);
        PSMTXConcat(t, m, out);
    }
    ResultDriver *driver;
    int id;
    float x;
    float out[3][4];
    float m[3][4];
};

static inline void KartSlot_Place(ResultKartSlot *k, int i) {
    float t[3][4];
    k->x = lbl_806D86A4 * (float)i + lbl_806D86A0;
    PSMTXTrans(t, k->x, lbl_806D86A8, lbl_806D869C);
    PSMTXConcat(t, k->m, k->out);
}
static inline void KartSlot_Init(ResultKartSlot **slot, int id, int i) {
    float t[3][4];
    ResultKartSlot *k;
    *slot = new ResultKartSlot(id);
    (*slot)->x = lbl_806D86A4 * (float)i + lbl_806D86A0;
    k = *slot;
    PSMTXTrans(t, k->x, lbl_806D86A8, lbl_806D869C);
    PSMTXConcat(t, k->m, k->out);
}
static inline void KartSlot_Init2(ResultKartSlot **karts, int i) {
    float t[3][4];
    ResultKartSlot *k;
    karts[i] = new ResultKartSlot(lbl_803686B8[i]);
    karts[i]->x = lbl_806D86A4 * (float)i + lbl_806D86A0;
    k = karts[i];
    PSMTXTrans(t, k->x, lbl_806D86A8, lbl_806D869C);
    PSMTXConcat(t, k->m, k->out);
}
struct ResultKartSet {
    ResultKartSet() {
        int i;
        ResultVec v;
        cam = (VObj *)new ResultCam(lbl_80368CC0);
        model = new ResultModel(lbl_80368CC0, 0);
        on = 0;
        on2 = 0;
        v.x = lbl_806D8678;
        v.y = lbl_806D8678;
        v.z = lbl_806D8688;
        CObj_LoadIntoGX(cam, &v);
        v.z = lbl_806D8678;
        CObj_ApplyViewport(cam, &v);
        for (i = 0; i < 13; i++) {
            KartSlot_Init2(karts, i);
            ProcessSystemTick(0);
        }
    }
    VObj *cam;
    void *model;
    ResultKartSlot *karts[13];
    unsigned char on;
    unsigned char on2;
};

struct ResultFade {
    ResultFade(int h) {
        xb0 = 0;
        xb4 = 0;
        xb8 = 0;
        half = h;
        a.enable = 1;
        a.x = lbl_806D86AC;
        a.y = lbl_806D86B0;
        a.z = lbl_806D8674;
        a.c0 = -0x100;
        a.c1 = -0x100;
        a.c2 = -0x100;
        a.c3 = -0x100;
        b.enable = 1;
        b.x = lbl_806D86AC;
        b.y = lbl_806D86B0;
        b.z = lbl_806D8674;
        b.c0 = -0x100;
        b.c1 = -0x100;
        b.c2 = -0x100;
        b.c3 = -0x100;
    }
    ResCtrlR a;
    ResCtrlR b;
    int xb0, xb4, xb8;
    int half;
};


static inline void Flake_SetPos(VObj *f, const ResultVec &v) {
    fn_8013D634(f, v.x, v.y, v.z);
}


struct ResultFlakes : RYPair {
    ResultFlakes() {
        int i;
        stopped = 0;
        timer = 0;
        interval = 0x78;
        a = (VObj *)new ResultFlake(lbl_80368CCC, 1);
        b = (VObj *)new ResultFlake(lbl_80368CE0, 1);
        fn_8013D738(a, lbl_806D8678, lbl_806D8674);
        { const ResultVec *v = (const ResultVec *)lbl_803686EC; fn_8013D634(a, lbl_803686EC[0], v->y, v->z); }
        fn_8013D608(a, lbl_806D86B4, lbl_806D86B4, lbl_806D86B4);
        fn_8013D738(b, lbl_806D8678, lbl_806D8674);
        { const ResultVec *v = (const ResultVec *)lbl_803686F8; fn_8013D634(b, lbl_803686F8[0], v->y, v->z); }
        fn_8013D608(b, lbl_806D86B8, lbl_806D86B8, lbl_806D86B8);
        for (i = 0; i < 3; i++) RYEntry_Reset(&e[i]);
    }
};

ResultPartY::ResultPartY(int n) {
    fn_80121210();
    mode = fn_80169E20();
    half = n / 2;
    idx = n;
    x10 = lbl_806D8678;
    x14 = 0;
    x18 = 0;
    x1c = lbl_806D8678;
    x20 = -1;
    x24 = lbl_806D8678;
    x28 = lbl_806D8684;
    karts = (ResultKarts *)new ResultKartSet;
    buf = (char *)new ResultFade(half);
    pair = (ResultPair *)new ResultFlakes;
    r38.mode = 2;
    r38.u = lbl_806D86BC;
    r38.v = lbl_806D86C0;
    r38.enable = 1;
    r38.x = lbl_806D86C4;
    r38.y = lbl_806D86C8;
    r38.z = lbl_806D8674;
    r38.c1 = 0;
    r38.c2 = 0;
    r38.c0 = 0xff;
    r38.c3 = 0xff;
    r90.mode = 2;
    r90.u = lbl_806D867C;
    r90.v = lbl_806D8680;
    r90.enable = 1;
    r90.x = lbl_806D866C;
    r90.y = lbl_806D8670;
    r90.z = lbl_806D8674;
    r90.c0 = 0;
    r90.c1 = 0;
    r90.c2 = 0;
    r90.c3 = 0;
    int i;
    for (i = 0; i < 13; i++) PreloadResource(lbl_806D8664[half] + i);
    for (i = 0x1da1; i <= 0x1de9; i++) PreloadResource(i);
    if (mode == 2) {
        PreloadResource(0x358);
        PreloadResource(0x359);
        PreloadResource(0x8d9);
    } else {
        PreloadResource(0x8d7);
        PreloadResource(0x8d8);
        PreloadResource(0x35a);
    }
    PreloadResource(0x50a);
    ClSound_PlayBgmStream(2, 0);
    clStream_setVolume(2, fn_801932F8());
}

struct ResultFadeV {
    int idA;
    char pad04[0x2c - 0x04];
    float sx, sy;
    unsigned int colA[4];
    char pad44[0x58 - 0x44];
    int idB;
    char pad5c[0x8c - 0x5c];
    unsigned int colB[4];
    char pad9c[0xb0 - 0x9c];
    int timer;
    int state;
    int step;
    int half;
};

struct ResultPartYU {
    void *vt;
    int mode;
    int half;
    int idx;
    float timer;
    unsigned char started;
    char pad15[3];
    int x18;
    float wait;
    int x20;
    float x24;
    float fade;
    ResultKartSet *karts;
    ResultFadeV *fadeObj;
    RYPair *pair;
    char pad38[0x6c - 0x38];
    unsigned int colA[4];
    char pad7c[0xc4 - 0x7c];
    unsigned int colB[4];
};

extern "C" {
extern void KartDriver_TriggerSlotC3Action(ResultDriver *d, float t);
extern void KartDriver_TickAction_79234(ResultDriver *d, float t);
extern void RenderObj_ItemStateMachine_Timed(ResultDriver *d, int n, float a, float b);
extern float Saturate_Double(float v, float lo, float hi);
extern void fn_801695E0(int obj, int id, int flag, float x, float y, float a);
extern void fn_80169334(int obj, int id, int flag, float x, float y, float z, float a, float b);
extern void fn_80190A70(int a, int b);
extern const float lbl_806D86DC, lbl_806D86E0, lbl_806D86E4, lbl_806D86F4, lbl_806D86F8, lbl_806D86FC;
extern const float lbl_806D8700, lbl_806D8704, lbl_806D8708, lbl_806D870C, lbl_806D8710, lbl_806D8714;
extern const float lbl_806D8718, lbl_806D871C, lbl_806D8720, lbl_806D8724, lbl_806D8728, lbl_806D872C;
extern const float lbl_806D8730, lbl_806D8734, lbl_806D8738, lbl_806D873C, lbl_806D8740, lbl_806D8744;
extern const float lbl_806D8748, lbl_806D874C, lbl_806D8750, lbl_806D8754;

static inline void Slot_ResetPose(ResultKartSlot *k) {
    float s[3][4];
    float r[3][4];
    PSMTXScale(s, lbl_806D8674, lbl_806D8674, lbl_806D8674);
    PSMTXIdentity(k->m);
    PSMTXConcat(s, k->m, k->m);
    PSMTXRotRad(r, 'Z', lbl_806D8690);
    PSMTXConcat(r, k->m, k->m);
    PSMTXRotRad(r, 'Y', lbl_806D8694);
    PSMTXConcat(r, k->m, k->m);
}

static inline void Slot_Tilt(ResultKartSlot *k) {
    float x = k->x;
    if (x < lbl_806D86A0) {
        float s[3][4];
        float r[3][4];
        PSMTXScale(s, lbl_806D8674, lbl_806D8674, lbl_806D8674);
        PSMTXIdentity(k->m);
        PSMTXConcat(s, k->m, k->m);
        PSMTXRotRad(r, 'Z', lbl_806D8690);
        PSMTXConcat(r, k->m, k->m);
        PSMTXRotRad(r, 'Y', lbl_806D8700 * (lbl_806D8704 * (lbl_806D8674 - (x - lbl_806D86FC) / lbl_806D8708)) + lbl_806D8694);
        PSMTXConcat(r, k->m, k->m);
    }
}

static inline void Slot_Place(ResultKartSlot *k) {
    float t[3][4];
    PSMTXTrans(t, k->x, lbl_806D86A8, lbl_806D869C);
    PSMTXConcat(t, k->m, k->out);
}

static inline void Slot_Tick(ResultKartSlot *k) {
    KartDriver_TriggerSlotC3Action(k->driver, lbl_806D870C);
    KartDriver_TickAction_79234(k->driver, lbl_806D870C);
    RenderObj_ItemStateMachine_Timed(k->driver, 0, lbl_806D8678, lbl_806D8678);
}

static inline void KartSet_Update(ResultKartSet *ks) {
    int i;
    if (ks->on) {
        for (i = 0; i < 13; i++) {
            ResultKartSlot *k;
            if (ks->on2 == 1 && ks->karts[i]->x >= lbl_806D86A0) continue;
            ks->karts[i]->x -= lbl_806D86F8;
            k = ks->karts[i];
            if (k->x < lbl_806D86FC && ks->on2 == 0) {
                int j = i - 1;
                if (j < 0) j = 12;
                k->x = lbl_806D86A4 + ks->karts[j]->x;
                Slot_ResetPose(ks->karts[i]);
            }
            Slot_Tilt(ks->karts[i]);
            Slot_Place(ks->karts[i]);
            Slot_Tick(ks->karts[i]);
        }
    }
}

static inline void Fade_Next(ResultFadeV *f) {
    if (f->half == 0 && f->step == 1) f->step++;
    f->timer = 0;
    f->state = 1;
    f->idB = f->idA;
    f->colB[0] = -1;
    f->colB[1] = -1;
    f->colB[2] = -1;
    f->colB[3] = -1;
    f->colA[0] = -0x100;
    f->colA[1] = -0x100;
    f->colA[2] = -0x100;
    f->colA[3] = -0x100;
    if (f->step >= 13) {
        f->idA = 0x1ecd;
    } else {
        f->idA = f->step++ + lbl_806D8664[f->half];
    }
}

static inline void Col_SetAlpha(unsigned int *col, int a) {
    unsigned int c = (0xFFFFFF00 | (unsigned char)(a));
    col[0] = c;
    col[1] = c;
    col[2] = c;
    col[3] = c;
}

static inline void Fade_Update(ResultFadeV *f) {
    if (f->state == 1) {
        float t = (float)f->timer / lbl_806D86A4;
        int a = (int)(lbl_806D86E8 * t);
        float sc = lbl_806D86EC * (lbl_806D8674 - t) + lbl_806D8674;
        f->sx = sc;
        f->sy = sc;
        Col_SetAlpha(f->colA, a);
        Col_SetAlpha(f->colB, 0xff - a);
        if ((float)f->timer >= lbl_806D86A4) f->state = 2;
        f->timer++;
    }
}

#pragma push
#pragma opt_common_subs off
void fn_8015CD74(ResultPartYU *o) {
    int i;
    float a;
    o->timer += lbl_806D8674;
    if (o->timer > lbl_806D86DC) {
        float lim;
        if (o->half == 0) {
            lim = lbl_806D86E0;
        } else {
            lim = lbl_806D86E4;
        }
        if ((o->wait += lbl_806D8674) > lim) {
            Fade_Next(o->fadeObj);
            o->wait = lbl_806D8678;
        }
        Fade_Update(o->fadeObj);
    }
    if (lbl_806D86F0 == o->timer) o->karts->on = 1;
    if (lbl_806D86F4 == o->timer) o->karts->on2 = 1;
    KartSet_Update(o->karts);
    if (lbl_806D8710 == o->timer) o->pair->stopped = 1;
    fn_8015D9F0(o->pair);
    {
        float base = lbl_806D8718 * (o->timer - lbl_806D871C) + lbl_806D8714;
        for (i = 0;; i++) {
            const char *text = lbl_80490080[i].text;
            float y;
            if (!text) break;
            y = lbl_80490080[i].y - base;
            if (y > lbl_806D8720 && y < lbl_806D8724) {
                float x = lbl_80490080[i].big == 1 ? lbl_806D8728 : lbl_806D872C;
                fn_8015D4F8(o, lbl_80490080[i].color, text, x, y);
            }
        }
    }
    if (lbl_806D8730 == o->timer) {
        o->colA[0] = -0x100;
        o->colA[1] = -0x100;
        o->colA[2] = -0x100;
        o->colA[3] = -0x100;
    }
    if (o->timer > lbl_806D8730) {
        a = lbl_806D8680 - Saturate_Double(lbl_806D8734 * (o->timer - lbl_806D8730), lbl_806D8678, lbl_806D8680);
        if (o->fade < lbl_806D8678 && o->timer - lbl_806D8730 - lbl_806D8738 >= lbl_806D8678) {
            o->fade = lbl_806D8678;
        }
        if (o->mode != 0) {
            fn_801695E0(5, 0xfc1, 0, lbl_806D866C, lbl_806D873C + a, lbl_806D8674);
            fn_801695E0(5, 0xfc2, 0, lbl_806D866C, lbl_806D8740 + a, lbl_806D8674);
            fn_801695E0(5, 0x2afc, 0, lbl_806D8744, lbl_806D8748 + a, lbl_806D8674);
        } else {
            fn_801695E0(5, 0x17a1, 0, lbl_806D866C, lbl_806D873C + a, lbl_806D8674);
            fn_801695E0(5, 0x17a2, 0, lbl_806D866C, lbl_806D8740 + a, lbl_806D8674);
            fn_80169334(5, 0x2afc, 0, lbl_806D874C, lbl_806D8750 + a, lbl_806D8754, 1.0f, 1.0f);
        }
    }
    if ((InputMgr_GetPlayer(GetInputManager(), 0)->Held(0x2000) || InputMgr_GetPlayer(GetInputManager(), 0)->Held(0x100)) &&
        o->fade < lbl_806D8678) {
        if (fn_8019083C(2)) fn_80190A70(2, 1);
        o->fade = lbl_806D8678;
    }
    float fd = o->fade;
    if (fd >= lbl_806D8678) {
        unsigned int c;
        if ((o->fade = fd + lbl_806D8674) > 30.0f) o->fade = 30.0f;
        fn_801678FC(0, lbl_806D8678, lbl_806D8678, lbl_806D8678, o->fade / lbl_806D86A4);
        c = (unsigned char)(int)(lbl_806D86E8 * (o->fade / lbl_806D86A4));
        o->colB[0] = c;
        o->colB[1] = c;
        o->colB[2] = c;
        o->colB[3] = c;
    }
    if (!o->started) o->started = 1;
}
#pragma pop

}
