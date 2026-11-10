#include "game/MsgPopupTables_rescue.h"

/* Message strings and pointer tables share the original read-only pool. */
extern "C" {
extern const char lbl_803C0390[];
extern const char lbl_803C039C[];
extern const char msgTable_803C03EC_rodata_803C03A8[];
extern const char lbl_803C03B8[];
extern const char lbl_803C03C4[];
extern const char msgTable_803C03EC_rodata_803C03D0[];
extern const char lbl_803C03E0[];
extern const char msgTable_803C0430_rodata_803C0418[];
extern const char msgTable_803C0430_rodata_803C0424[];
extern const char msgTable_803C04CC_rodata_803C045C[];
extern const char lbl_803C0478[];
extern const char lbl_803C0494[];
extern const char lbl_803C04B0[];
extern const char msgTable_803C04F8_rodata_803C04DC[];
extern const char msgTable_803C0604_rodata_803C0560[];
extern const char msgTable_803C0604_rodata_803C056C[];
extern const char msgTable_803C0604_rodata_803C0584[];
extern const char msgTable_803C0604_rodata_803C0598[];
extern const char msgTable_803C0604_rodata_803C05B0[];
extern const char msgTable_803C0604_rodata_803C05C8[];
extern const char msgTable_803C0604_rodata_803C05D4[];
extern const char msgTable_803C0604_rodata_803C05EC[];
extern const char msgTable_803C0728_rodata_803C0628[];
extern const char msgTable_803C0728_rodata_803C0648[];
extern const char msgTable_803C0728_rodata_803C0670[];
extern const char msgTable_803C0728_rodata_803C0694[];
extern const char msgTable_803C0728_rodata_803C06B8[];
extern const char msgTable_803C0728_rodata_803C06D8[];
extern const char msgTable_803C0728_rodata_803C0700[];
extern const char lbl_803C0784[];
extern const char lbl_803C07A8[];
extern const char msgTable_803C0814_rodata_803C07DC[];
extern const char msgTable_803C0954_rodata_803C0888[];
extern const char msgTable_803C0954_rodata_803C0894[];
extern const char msgTable_803C0954_rodata_803C08A0[];
extern const char lbl_803C08AC[];
extern const char msgTable_803C0954_rodata_803C08B8[];
extern const char msgTable_803C0954_rodata_803C08C4[];
extern const char msgTable_803C0954_rodata_803C08D0[];
extern const char msgTable_803C0954_rodata_803C08DC[];
extern const char msgTable_803C0954_rodata_803C08E8[];
extern const char msgTable_803C0954_rodata_803C08F4[];
extern const char msgTable_803C0954_rodata_803C0900[];
extern const char msgTable_803C0954_rodata_803C090C[];
extern const char msgTable_803C0954_rodata_803C0918[];
extern const char msgTable_803C0954_rodata_803C0924[];
extern const char msgTable_803C0954_rodata_803C0930[];
extern const char msgTable_803C0954_rodata_803C093C[];
extern const char msgTable_803C0954_rodata_803C0948[];
extern const char msgTable_803C0B20_rodata_803C0AD0[];
extern const char msgTable_803C0B20_rodata_803C0AF0[];
extern const char msgTable_803C0B20_rodata_803C0B10[];
extern const char msgTable_803C0BBC_rodata_803C0B58[];
extern const char msgTable_803C0BBC_rodata_803C0B68[];
extern const char msgTable_803C0BBC_rodata_803C0B78[];
extern const char msgTable_803C0BBC_rodata_803C0B88[];
extern const char msgTable_803C0BBC_rodata_803C0B98[];
extern const char msgTable_803C0BBC_rodata_803C0BA8[];
extern const char msgTable_803C0CBC_rodata_803C0BD4[];
extern const char msgTable_803C0CBC_rodata_803C0BE8[];
extern const char msgTable_803C0CBC_rodata_803C0BF8[];
extern const char msgTable_803C0CBC_rodata_803C0C08[];
extern const char msgTable_803C0CBC_rodata_803C0C18[];
extern const char msgTable_803C0CBC_rodata_803C0C2C[];
extern const char msgTable_803C0CBC_rodata_803C0C3C[];
extern const char msgTable_803C0CBC_rodata_803C0C50[];
extern const char msgTable_803C0CBC_rodata_803C0C64[];
extern const char msgTable_803C0CBC_rodata_803C0C78[];
extern const char msgTable_803C0CBC_rodata_803C0C8C[];
extern const char msgTable_803C0CBC_rodata_803C0CA4[];
extern const char lbl_803C0D30[];
extern const char lbl_803C0D3C[];
extern const char msgTable_803C0DD4_rodata_803C0D74[];
extern const char msgTable_803C0DD4_rodata_803C0D80[];
extern const char msgTable_803C0DD4_rodata_803C0D8C[];
extern const char msgTable_803C0DD4_rodata_803C0D98[];
extern const char msgTable_803C0DD4_rodata_803C0DA4[];
extern const char msgTable_803C0DD4_rodata_803C0DB0[];
extern const char msgTable_803C0DD4_rodata_803C0DBC[];
extern const char msgTable_803C0DD4_rodata_803C0DC8[];
extern const char lbl_803C0E00[];
extern const char lbl_803C0E20[];
extern const char lbl_803C0E40[];
extern const char lbl_803C0E5C[];
extern const char lbl_803C0E88[];
extern const char lbl_803C0EE4[];
extern const char lbl_803C0EF8[];
extern const char lbl_803C0F0C[];
extern const char lbl_803C0F20[];
extern const char msgTable_803C0FA8_rodata_803C0F38[];
extern const char msgTable_803C0FA8_rodata_803C0F50[];
extern const char lbl_803C0F68[];
extern const char lbl_803C0F7C[];
extern const char lbl_803C0F94[];
extern const char lbl_803C0FD8[];
extern const char lbl_803C0FF8[];
extern const char lbl_803C1018[];
extern const char lbl_803C1038[];
extern const char lbl_803C1054[];
extern const char lbl_803C10A8[];
extern const char lbl_803C10E4[];
extern const char lbl_803C10FC[];
extern const char msgTable_803C1140_rodata_803C1110[];
extern const char msgTable_803C1140_rodata_803C111C[];
extern const char msgTable_803C1140_rodata_803C1128[];
extern const char msgTable_803C1140_rodata_803C1134[];
extern const char lbl_803C1150[];
extern const char msgTable_803C11BC_rodata_803C1184[];
extern const char lbl_803C11F0[];
extern const char lbl_803C11FC[];
extern const char lbl_803C1208[];
extern const char lbl_803C1214[];
extern const char lbl_803C1220[];
extern const char msgTable_803C1280_rodata_803C122C[];
extern const char lbl_803C1238[];
extern const char lbl_803C1244[];
extern const char lbl_803C1250[];
extern const char lbl_803C125C[];
extern const char lbl_803C1268[];
extern const char lbl_803C1274[];
extern const char lbl_803C137C[];
extern const char lbl_803C1398[];
extern const char lbl_803C13F0[];
extern const char lbl_803C13FC[];
extern const char lbl_803C1408[];
extern const char lbl_803C1414[];
extern const char lbl_803C1424[];
extern const char lbl_803C1434[];
extern const char lbl_803C145C[];
extern const char lbl_803C146C[];
extern const char lbl_803C1478[];
extern const char lbl_803C1484[];
extern const char lbl_803C1494[];
extern const char lbl_803C14A4[];
extern const char lbl_803C14B0[];
extern const char lbl_803C14C0[];
extern const char lbl_803C14D0[];
extern const char lbl_803C14E0[];
extern const char lbl_803C14EC[];
extern const char lbl_803C14FC[];
extern const char lbl_803C1540[];
extern const char lbl_803C154C[];
extern const char lbl_803C1558[];
extern const char lbl_803C1564[];
extern const char lbl_803C1574[];
extern const char lbl_803C1584[];
extern const char msgTable_803C1A30_rodata_803C16C8[];
extern const char msgTable_803C1A30_rodata_803C16E4[];
extern const char msgTable_803C1A30_rodata_803C16FC[];
extern const char msgTable_803C1A30_rodata_803C170C[];
extern const char msgTable_803C1A30_rodata_803C1720[];
extern const char msgTable_803C1A30_rodata_803C173C[];
extern const char msgTable_803C1A30_rodata_803C1754[];
extern const char msgTable_803C1A30_rodata_803C176C[];
extern const char msgTable_803C1A30_rodata_803C1784[];
extern const char msgTable_803C1A30_rodata_803C1794[];
extern const char msgTable_803C1A30_rodata_803C17AC[];
extern const char msgTable_803C1A30_rodata_803C17C8[];
extern const char msgTable_803C1A30_rodata_803C17E4[];
extern const char msgTable_803C1A30_rodata_803C1808[];
extern const char msgTable_803C1A30_rodata_803C1820[];
extern const char msgTable_803C1A30_rodata_803C1838[];
extern const char msgTable_803C1A30_rodata_803C1850[];
extern const char msgTable_803C1A30_rodata_803C1864[];
extern const char msgTable_803C1A30_rodata_803C187C[];
extern const char msgTable_803C1A30_rodata_803C1894[];
extern const char msgTable_803C1A30_rodata_803C18A8[];
extern const char msgTable_803C1A30_rodata_803C18C0[];
extern const char msgTable_803C1A30_rodata_803C18D8[];
extern const char msgTable_803C1A30_rodata_803C18F4[];
extern const char msgTable_803C1A30_rodata_803C1908[];
extern const char msgTable_803C1A30_rodata_803C1920[];
extern const char msgTable_803C1A30_rodata_803C1930[];
extern const char msgTable_803C1A30_rodata_803C1958[];
extern const char msgTable_803C1A30_rodata_803C1974[];
extern const char msgTable_803C1A30_rodata_803C1984[];
extern const char msgTable_803C1A30_rodata_803C1998[];
extern const char msgTable_803C1A30_rodata_803C19B4[];
extern const char msgTable_803C1A30_rodata_803C19CC[];
extern const char msgTable_803C1A30_rodata_803C19F0[];
extern const char msgTable_803C1A30_rodata_803C1A10[];
extern const char lbl_803C1C10[];
extern const char lbl_803C1C20[];
extern const char lbl_803C1C2C[];
extern const char lbl_803C1C38[];
extern const char lbl_803C1C48[];
extern const char lbl_803C1C5C[];
extern const char lbl_803C1C6C[];
extern const char lbl_803C1C84[];
extern const char lbl_803C1C98[];
extern const char lbl_803C1CA4[];
extern const char lbl_803C1CB8[];
extern const char lbl_803C1CD0[];
extern const char lbl_803C1CEC[];
extern const char lbl_803C1D08[];
extern const char lbl_803C1D18[];
extern const char lbl_803C1D28[];
extern const char lbl_803C1D3C[];
extern const char lbl_803C1D48[];
extern const char lbl_803C1D5C[];
extern const char lbl_803C1D6C[];
extern const char lbl_803C1D88[];
extern const char lbl_803C1DA0[];
extern const char lbl_803C1DBC[];
extern const char lbl_803C1DD4[];
extern const char lbl_803C1DE0[];
extern const char lbl_803C1DF4[];
extern const char lbl_803C1E00[];
extern const char lbl_803C1E14[];
extern const char lbl_803C1E24[];
extern const char lbl_803C1E44[];
extern const char lbl_803C1E5C[];
extern const char lbl_803C1E6C[];
extern const char lbl_803C1E80[];
extern const char lbl_803C1E90[];
extern const char lbl_803C1EB0[];
extern const char lbl_803C1EC4[];
extern const char lbl_803C1ED8[];
extern const char msgTable_803C21BC_rodata_803C2144[];
extern const char msgTable_803C21BC_rodata_803C2158[];
extern const char msgTable_803C21BC_rodata_803C2168[];
extern const char msgTable_803C21BC_rodata_803C217C[];
extern const char msgTable_803C21BC_rodata_803C2198[];
extern const char msgTable_803C21BC_rodata_803C21A8[];
extern const char msgTable_803C22D0_rodata_803C222C[];
extern const char msgTable_803C22D0_rodata_803C2244[];
extern const char msgTable_803C22D0_rodata_803C2258[];
extern const char msgTable_803C22D0_rodata_803C226C[];
extern const char msgTable_803C22D0_rodata_803C227C[];
extern const char msgTable_803C22D0_rodata_803C228C[];
extern const char msgTable_803C22D0_rodata_803C22A0[];
extern const char msgTable_803C22D0_rodata_803C22B8[];
extern const char lbl_803C2340[];
extern const char lbl_803C234C[];
extern const char lbl_803C235C[];
extern const char lbl_803C2374[];
extern const char lbl_803C2400[];
extern const char lbl_803C2414[];
extern const char lbl_803C2424[];
extern const char lbl_803C2430[];
extern const char lbl_806DA910[];
extern const char lbl_806DA918[];
extern const char lbl_806DA920[];
extern const char lbl_806DA928[];
extern const char lbl_806DA930[];
extern const char lbl_806DA934[];
extern const char lbl_806DA93C[];
extern const char lbl_806DA944[];
extern const char lbl_806DA954[];
extern const char lbl_806DA95C[];
extern const char lbl_806DA964[];
extern const char lbl_806DA96C[];
extern const char lbl_806DA974[];
extern const char lbl_806DA978[];
extern const char lbl_806DA980[];
extern const char lbl_806DA988[];
extern const char lbl_806DA990[];
extern const char lbl_806DA998[];
extern const char lbl_806DA9A0[];
extern const char lbl_806DA9A8[];
extern const char lbl_806DA9B0[];
extern const char lbl_806DA9B8[];
extern const char lbl_806DA9C0[];
extern const char lbl_806DA9C8[];
extern const char lbl_806DA9D0[];
extern const char lbl_806DA9D8[];
extern const char lbl_806DA9DC[];
extern const char lbl_806DA9E4[];
extern const char lbl_806DA9F4[];
extern const char lbl_806DA9FC[];
extern const char lbl_806DAA04[];
extern const char lbl_806DAA0C[];
extern const char lbl_806DAA14[];
extern const char lbl_806DAA1C[];
extern const char lbl_806DAA24[];
extern const char lbl_806DAA2C[];
extern const char lbl_806DAA34[];
extern const char lbl_806DAA3C[];
extern const char lbl_806DAA44[];
extern const char lbl_806DAA4C[];
extern const char lbl_806DAA54[];
extern const char lbl_806DAA5C[];
extern const char lbl_806DAA64[];
extern const char lbl_806DAA6C[];
extern const char lbl_806DAA70[];
extern const char lbl_806DAA78[];
extern const char lbl_806DAA80[];
extern const char lbl_806DAA84[];
extern const char lbl_806DAA8C[];
extern const char lbl_806DAA90[];
extern const char msgString_803C0508[];
extern const char msgString_803C0764[];
extern const char msgString_803C0820[];
extern const char msgString_803C0868[];
extern const char msgString_803C0A14[];
extern const char msgString_803C0A34[];
extern const char msgString_803C0A58[];
extern const char msgString_803C0A64[];
extern const char msgString_803C0A80[];
extern const char msgString_803C0AAC[];
extern const char msgString_803C0B2C[];
extern const char msgString_803C0CEC[];
extern const char msgString_803C0D08[];
extern const char msgString_803C0D1C[];
extern const char msgString_803C0EBC[];
extern const char msgString_803C10C4[];
extern const char msgString_803C11C8[];
extern const char msgString_803C1340[];
extern const char msgString_803C1354[];
extern const char msgString_803C1368[];
extern const char msgString_803C13C4[];
extern const char msgString_803C15F0[];
extern const char msgString_803C161C[];
extern const char msgString_803C1638[];
}

extern "C" const char lbl_803C0390[] = "ルイージ";

extern "C" const char lbl_803C039C[] = "キノピオ";

extern "C" const char msgTable_803C03EC_rodata_803C03A8[] = "ドンキーコング";

extern "C" const char lbl_803C03B8[] = "ヨッシー";

extern "C" const char lbl_803C03C4[] = "パックマン";

extern "C" const char msgTable_803C03EC_rodata_803C03D0[] = "Ms.パックマン";

extern "C" const char lbl_803C03E0[] = "アカベイ";

extern "C" const char *const msgTable_803C03EC[11] = {
    lbl_806DA910, lbl_803C0390, lbl_806DA918, lbl_806DA920,
    lbl_806DA928, lbl_803C039C, msgTable_803C03EC_rodata_803C03A8, lbl_803C03B8,
    lbl_803C03C4, msgTable_803C03EC_rodata_803C03D0, lbl_803C03E0,
};

extern "C" const char msgTable_803C0430_rodata_803C0418[] = "ドンキー";

extern "C" const char msgTable_803C0430_rodata_803C0424[] = "ミズパック";

extern "C" const char *const msgTable_803C0430[11] = {
    lbl_806DA910, lbl_803C0390, lbl_806DA918, lbl_806DA920,
    lbl_806DA928, lbl_803C039C, msgTable_803C0430_rodata_803C0418, lbl_803C03B8,
    lbl_803C03C4, msgTable_803C0430_rodata_803C0424, lbl_803C03E0,
};

extern "C" const char msgTable_803C04CC_rodata_803C045C[] = " 顔写真つきワイワイレース ";

extern "C" const char lbl_803C0478[] = " 他の参加者を待っています ";

extern "C" const char lbl_803C0494[] = "マリオカードを入れられます";

extern "C" const char lbl_803C04B0[] = "対戦プレイヤーが準備中です";

extern "C" const char *const msgTable_803C04CC[4] = {
    msgTable_803C04CC_rodata_803C045C, lbl_803C0478, lbl_803C0494, lbl_803C04B0,
};

extern "C" const char msgTable_803C04F8_rodata_803C04DC[] = " 顔写真なしガチンコレース ";

extern "C" const char *const msgTable_803C04F8[4] = {
    msgTable_803C04F8_rodata_803C04DC, lbl_803C0478, lbl_803C0494, lbl_803C04B0,
};

extern "C" const char msgString_803C0508[] = "対戦キャンセルボタンを押しながら\nコインをいれると対戦エントリーを\nキャンセルできます。";

extern "C" const char msgTable_803C0604_rodata_803C0560[] = " １人プレイ";

extern "C" const char msgTable_803C0604_rodata_803C056C[] = "６カップ２４コースで";

extern "C" const char msgTable_803C0604_rodata_803C0584[] = "優勝をめざします！";

extern "C" const char msgTable_803C0604_rodata_803C0598[] = "コースを選んでベスト";

extern "C" const char msgTable_803C0604_rodata_803C05B0[] = "タイムをめざします！";

extern "C" const char msgTable_803C0604_rodata_803C05C8[] = " 対戦プレイ";

extern "C" const char msgTable_803C0604_rodata_803C05D4[] = "ゲームのプレイヤーに";

extern "C" const char msgTable_803C0604_rodata_803C05EC[] = "対戦を申し込みます！";

extern "C" const char *const msgTable_803C0604[9] = {
    msgTable_803C0604_rodata_803C0560, msgTable_803C0604_rodata_803C056C, msgTable_803C0604_rodata_803C0584, msgTable_803C0604_rodata_803C0560,
    msgTable_803C0604_rodata_803C0598, msgTable_803C0604_rodata_803C05B0, msgTable_803C0604_rodata_803C05C8, msgTable_803C0604_rodata_803C05D4,
    msgTable_803C0604_rodata_803C05EC,
};

extern "C" const char msgTable_803C0728_rodata_803C0628[] = "　　 ゲーム結果を記録できます。";

extern "C" const char msgTable_803C0728_rodata_803C0648[] = "次のラウンドの挑戦権を保存できます。";

extern "C" const char msgTable_803C0728_rodata_803C0670[] = " 手に入れたアイテムを保存できます。";

extern "C" const char msgTable_803C0728_rodata_803C0694[] = "　　今回のタイムを記録できます。";

extern "C" const char msgTable_803C0728_rodata_803C06B8[] = "　　 レース結果を記録できます。";

extern "C" const char msgTable_803C0728_rodata_803C06D8[] = "作らない場合、今回のレースで獲得した";

extern "C" const char msgTable_803C0728_rodata_803C0700[] = "コインマイレージは全てなくなります。";

extern "C" const char *const msgTable_803C0728[15] = {
    msgTable_803C0728_rodata_803C0628, lbl_806DA930, msgTable_803C0728_rodata_803C0648, lbl_806DA930,
    msgTable_803C0728_rodata_803C0670, lbl_806DA930, msgTable_803C0728_rodata_803C0694, lbl_806DA930,
    msgTable_803C0728_rodata_803C06B8, lbl_806DA930, msgTable_803C0728_rodata_803C06D8, msgTable_803C0728_rodata_803C0700,
    lbl_806DA934, lbl_806DA93C, lbl_806DA944,
};

extern "C" const char msgString_803C0764[] = "他のプレイヤーを待っています";

extern "C" const char lbl_803C0784[] = "アイテムボタンで好きなタイミングに";

extern "C" const char lbl_803C07A8[] = "シャッターをきることもできます。";

extern "C" const char *const msgTable_803C07CC[4] = {
    lbl_806DA954, lbl_806DA95C, lbl_806DA964, lbl_806DA96C,
};

extern "C" const char msgTable_803C0814_rodata_803C07DC[] = "どのラウンドを選んでもチャレンジゲームに挑戦できます";

extern "C" const char *const msgTable_803C0814[3] = {
    lbl_806DA974, msgTable_803C0814_rodata_803C07DC, msgTable_803C0814_rodata_803C07DC,
};

extern "C" const char msgString_803C0820[] = "ブレーキを踏みながらアクセルで決定するとスタッフゴーストが出現します";

extern "C" const char msgString_803C0868[] = "コンディションを選んでください";

extern "C" const char msgTable_803C0954_rodata_803C0888[] = "　昼間　";

extern "C" const char msgTable_803C0954_rodata_803C0894[] = "　夕方　";

extern "C" const char msgTable_803C0954_rodata_803C08A0[] = "　夜間　";

extern "C" const char lbl_803C08AC[] = "－－－－";

extern "C" const char msgTable_803C0954_rodata_803C08B8[] = "　晴天　";

extern "C" const char msgTable_803C0954_rodata_803C08C4[] = "　雨天　";

extern "C" const char msgTable_803C0954_rodata_803C08D0[] = "雨上がり";

extern "C" const char msgTable_803C0954_rodata_803C08DC[] = "　朝方　";

extern "C" const char msgTable_803C0954_rodata_803C08E8[] = "　通常　";

extern "C" const char msgTable_803C0954_rodata_803C08F4[] = "草少なめ";

extern "C" const char msgTable_803C0954_rodata_803C0900[] = " 草多め ";

extern "C" const char msgTable_803C0954_rodata_803C090C[] = " 壁出現 ";

extern "C" const char msgTable_803C0954_rodata_803C0918[] = " 敵出現 ";

extern "C" const char msgTable_803C0954_rodata_803C0924[] = "　雲上　";

extern "C" const char msgTable_803C0954_rodata_803C0930[] = "　月夜　";

extern "C" const char msgTable_803C0954_rodata_803C093C[] = "　海中　";

extern "C" const char msgTable_803C0954_rodata_803C0948[] = "　海底　";

extern "C" const char *const msgTable_803C0954[48] = {
    msgTable_803C0954_rodata_803C0888, lbl_806DA930, msgTable_803C0954_rodata_803C0894, lbl_806DA930,
    msgTable_803C0954_rodata_803C08A0, lbl_806DA930, lbl_803C08AC, lbl_806DA930,
    msgTable_803C0954_rodata_803C08B8, lbl_806DA930, msgTable_803C0954_rodata_803C08C4, lbl_806DA930,
    msgTable_803C0954_rodata_803C08D0, lbl_806DA930, lbl_803C08AC, lbl_806DA930,
    msgTable_803C0954_rodata_803C0888, lbl_806DA930, msgTable_803C0954_rodata_803C08A0, lbl_806DA930,
    msgTable_803C0954_rodata_803C08DC, lbl_806DA930, lbl_803C08AC, lbl_806DA930,
    msgTable_803C0954_rodata_803C08E8, lbl_806DA930, msgTable_803C0954_rodata_803C08F4, lbl_806DA930,
    msgTable_803C0954_rodata_803C0900, lbl_806DA930, lbl_803C08AC, lbl_806DA930,
    msgTable_803C0954_rodata_803C08E8, lbl_806DA930, msgTable_803C0954_rodata_803C090C, lbl_806DA930,
    msgTable_803C0954_rodata_803C0918, lbl_806DA930, lbl_803C08AC, lbl_806DA930,
    msgTable_803C0954_rodata_803C0924, lbl_806DA930, msgTable_803C0954_rodata_803C0930, lbl_806DA930,
    msgTable_803C0954_rodata_803C093C, lbl_806DA930, msgTable_803C0954_rodata_803C0948, lbl_806DA930,
};

extern "C" const char msgString_803C0A14[] = "新しいアイテムパックを作ります";

extern "C" const char msgString_803C0A34[] = "アイテムボックスのアイテムを自由に";

extern "C" const char msgString_803C0A58[] = "選べます。";

extern "C" const char msgString_803C0A64[] = "最近作ったアイテムパック";

extern "C" const char msgString_803C0A80[] = "以前使ったアイテムパックでレースします。";

extern "C" const char msgString_803C0AAC[] = "アイテムボタンを押してください。";

extern "C" const char msgTable_803C0B20_rodata_803C0AD0[] = "決定したアイテムはレース中に";

extern "C" const char msgTable_803C0B20_rodata_803C0AF0[] = "アイテムボックスを通過すると";

extern "C" const char msgTable_803C0B20_rodata_803C0B10[] = "手に入ります。";

extern "C" const char *const msgTable_803C0B20[3] = {
    msgTable_803C0B20_rodata_803C0AD0, msgTable_803C0B20_rodata_803C0AF0, msgTable_803C0B20_rodata_803C0B10,
};

extern "C" const char msgString_803C0B2C[] = "このレースでは以下のアイテムを使用します。";

extern "C" const char msgTable_803C0BBC_rodata_803C0B58[] = "マリオステージ";

extern "C" const char msgTable_803C0BBC_rodata_803C0B68[] = "ＤＫステージ";

extern "C" const char msgTable_803C0BBC_rodata_803C0B78[] = "ワリオステージ";

extern "C" const char msgTable_803C0BBC_rodata_803C0B88[] = "PAC-MANステージ";

extern "C" const char msgTable_803C0BBC_rodata_803C0B98[] = "クッパステージ";

extern "C" const char msgTable_803C0BBC_rodata_803C0BA8[] = "レインボーステージ";

extern "C" const char *const msgTable_803C0BBC[6] = {
    msgTable_803C0BBC_rodata_803C0B58, msgTable_803C0BBC_rodata_803C0B68, msgTable_803C0BBC_rodata_803C0B78, msgTable_803C0BBC_rodata_803C0B88,
    msgTable_803C0BBC_rodata_803C0B98, msgTable_803C0BBC_rodata_803C0BA8,
};

extern "C" const char msgTable_803C0CBC_rodata_803C0BD4[] = "マリオハイウェイ";

extern "C" const char msgTable_803C0CBC_rodata_803C0BE8[] = "マリオビーチ";

extern "C" const char msgTable_803C0CBC_rodata_803C0BF8[] = "ＤＫジャングル";

extern "C" const char msgTable_803C0CBC_rodata_803C0C08[] = "バナナン遺跡";

extern "C" const char msgTable_803C0CBC_rodata_803C0C18[] = "ダイヤモンドシティ";

extern "C" const char msgTable_803C0CBC_rodata_803C0C2C[] = "スノーパニック";

extern "C" const char msgTable_803C0CBC_rodata_803C0C3C[] = "パックマウンテン";

extern "C" const char msgTable_803C0CBC_rodata_803C0C50[] = "パックラビリンス";

extern "C" const char msgTable_803C0CBC_rodata_803C0C64[] = "クッパキャッスル";

extern "C" const char msgTable_803C0CBC_rodata_803C0C78[] = "キャッスルウォール";

extern "C" const char msgTable_803C0CBC_rodata_803C0C8C[] = "レインボーコースター";

extern "C" const char msgTable_803C0CBC_rodata_803C0CA4[] = "レインボーダウンヒル";

extern "C" const char *const msgTable_803C0CBC[12] = {
    msgTable_803C0CBC_rodata_803C0BD4, msgTable_803C0CBC_rodata_803C0BE8, msgTable_803C0CBC_rodata_803C0BF8, msgTable_803C0CBC_rodata_803C0C08,
    msgTable_803C0CBC_rodata_803C0C18, msgTable_803C0CBC_rodata_803C0C2C, msgTable_803C0CBC_rodata_803C0C3C, msgTable_803C0CBC_rodata_803C0C50,
    msgTable_803C0CBC_rodata_803C0C64, msgTable_803C0CBC_rodata_803C0C78, msgTable_803C0CBC_rodata_803C0C8C, msgTable_803C0CBC_rodata_803C0CA4,
};

extern "C" const char msgString_803C0CEC[] = "レースで使用するアイテム";

extern "C" const char msgString_803C0D08[] = "ダッシュキノコ３つ";

extern "C" const char msgString_803C0D1C[] = "で最速を目指せ！";

extern "C" const char lbl_803C0D30[] = "DONKY KONG";

extern "C" const char lbl_803C0D3C[] = "Ms.PAC-MAN";

extern "C" const char *const msgTable_803C0D48[11] = {
    lbl_806DA978, lbl_806DA980, lbl_806DA988, lbl_806DA990,
    lbl_806DA998, lbl_806DA9A0, lbl_803C0D30, lbl_806DA9A8,
    lbl_806DA9B0, lbl_803C0D3C, lbl_806DA9B8,
};

extern "C" const char msgTable_803C0DD4_rodata_803C0D74[] = "ＭＡＲＩＯ";

extern "C" const char msgTable_803C0DD4_rodata_803C0D80[] = "ＬＵＩＧＩ";

extern "C" const char msgTable_803C0DD4_rodata_803C0D8C[] = "ＷＡＲＩＯ";

extern "C" const char msgTable_803C0DD4_rodata_803C0D98[] = "ＰＥＡＣＨ";

extern "C" const char msgTable_803C0DD4_rodata_803C0DA4[] = "ＫＩＮＧ";

extern "C" const char msgTable_803C0DD4_rodata_803C0DB0[] = "ＴＯＡＤ";

extern "C" const char msgTable_803C0DD4_rodata_803C0DBC[] = "ＹＯＳＨＩ";

extern "C" const char msgTable_803C0DD4_rodata_803C0DC8[] = "Ｍｓ．Ｐ";

extern "C" const char *const msgTable_803C0DD4[11] = {
    msgTable_803C0DD4_rodata_803C0D74, msgTable_803C0DD4_rodata_803C0D80, msgTable_803C0DD4_rodata_803C0D8C, msgTable_803C0DD4_rodata_803C0D98,
    msgTable_803C0DD4_rodata_803C0DA4, msgTable_803C0DD4_rodata_803C0DB0, lbl_806DA9C0, msgTable_803C0DD4_rodata_803C0DBC,
    lbl_806DA9C8, msgTable_803C0DD4_rodata_803C0DC8, lbl_806DA9D0,
};

extern "C" const char lbl_803C0E00[] = "Party race with face picture.";

extern "C" const char lbl_803C0E20[] = "Waiting for other challenger.";

extern "C" const char lbl_803C0E40[] = "Mario Card can be inserted";

extern "C" const char lbl_803C0E5C[] = "   Challenger Waiting    ";

extern "C" const char *const msgTable_803C0E78[4] = {
    lbl_803C0E00, lbl_803C0E20, lbl_803C0E40, lbl_803C0E5C,
};

extern "C" const char lbl_803C0E88[] = "Versus race without face picture.";

extern "C" const char *const msgTable_803C0EAC[4] = {
    lbl_803C0E88, lbl_803C0E20, lbl_803C0E40, lbl_803C0E5C,
};

extern "C" const char msgString_803C0EBC[] = "Hold the brake and gas \nto skip versus.";

extern "C" const char lbl_803C0EE4[] = "   Single Player";

extern "C" const char lbl_803C0EF8[] = "   Challenge 6 cups";

extern "C" const char lbl_803C0F0C[] = "      24 races !";

extern "C" const char lbl_803C0F20[] = "  Select a course and ";

extern "C" const char msgTable_803C0FA8_rodata_803C0F38[] = "　 set the best time ";

extern "C" const char msgTable_803C0FA8_rodata_803C0F50[] = " 　  attack record. ";

extern "C" const char lbl_803C0F68[] = "      2-4 Players";

extern "C" const char lbl_803C0F7C[] = "    Challenge player";

extern "C" const char lbl_803C0F94[] = "    for versus game";

extern "C" const char *const msgTable_803C0FA8[12] = {
    lbl_803C0EE4, lbl_803C0EF8, lbl_803C0F0C, lbl_806DA9D8,
    lbl_803C0EE4, lbl_803C0F20, msgTable_803C0FA8_rodata_803C0F38, msgTable_803C0FA8_rodata_803C0F50,
    lbl_803C0F68, lbl_803C0F7C, lbl_803C0F94, lbl_806DA9D8,
};

extern "C" const char lbl_803C0FD8[] = "   Game results can be saved";

extern "C" const char lbl_803C0FF8[] = "  You can challenge next round";

extern "C" const char lbl_803C1018[] = "  You can save your item data";

extern "C" const char lbl_803C1038[] = "  You can save your records";

extern "C" const char lbl_803C1054[] = "  You can save your race results";

extern "C" const char *const msgTable_803C1078[12] = {
    lbl_803C0FD8, lbl_806DA930, lbl_803C0FF8, lbl_806DA930,
    lbl_803C1018, lbl_806DA930, lbl_803C1038, lbl_806DA930,
    lbl_803C1054, lbl_806DA930, lbl_806DA930, lbl_806DA930,
};

extern "C" const char lbl_803C10A8[] = "Acceleration";

extern "C" const char *const msgTable_803C10B8[3] = {
    lbl_803C10A8, lbl_806DA9DC, lbl_806DA9E4,
};

extern "C" const char msgString_803C10C4[] = "        Please wait!        ";

extern "C" const char lbl_803C10E4[] = "Press the item button";

extern "C" const char lbl_803C10FC[] = " to snap a picture.";

extern "C" const char msgTable_803C1140_rodata_803C1110[] = " 　   EASY";

extern "C" const char msgTable_803C1140_rodata_803C111C[] = "   　NORMAL";

extern "C" const char msgTable_803C1140_rodata_803C1128[] = "　   MASTER";

extern "C" const char msgTable_803C1140_rodata_803C1134[] = "  　 MASTER";

extern "C" const char *const msgTable_803C1140[4] = {
    msgTable_803C1140_rodata_803C1110, msgTable_803C1140_rodata_803C111C, msgTable_803C1140_rodata_803C1128, msgTable_803C1140_rodata_803C1134,
};

extern "C" const char lbl_803C1150[] = "     You can race a challenge game in any round. ";

extern "C" const char msgTable_803C11BC_rodata_803C1184[] = "　　 You can race a challenge game in any round.　　";

extern "C" const char *const msgTable_803C11BC[3] = {
    lbl_806DA974, lbl_803C1150, msgTable_803C11BC_rodata_803C1184,
};

extern "C" const char msgString_803C11C8[] = "     S E L E C T     C O N D I T I O N";

extern "C" const char lbl_803C11F0[] = "Daytime ";

extern "C" const char lbl_803C11FC[] = "Evening ";

extern "C" const char lbl_803C1208[] = " Night  ";

extern "C" const char lbl_803C1214[] = "Midnight";

extern "C" const char lbl_803C1220[] = " Clear  ";

extern "C" const char msgTable_803C1280_rodata_803C122C[] = "　Rain　";

extern "C" const char lbl_803C1238[] = " After  ";

extern "C" const char lbl_803C1244[] = "  Rain  ";

extern "C" const char lbl_803C1250[] = "  With  ";

extern "C" const char lbl_803C125C[] = " Traps  ";

extern "C" const char lbl_803C1268[] = " Normal ";

extern "C" const char lbl_803C1274[] = "  Coral ";

extern "C" const char *const msgTable_803C1280[48] = {
    lbl_803C11F0, lbl_806DA974, lbl_803C11FC, lbl_806DA974,
    lbl_803C1208, lbl_806DA974, lbl_803C1214, lbl_806DA974,
    lbl_803C1220, lbl_806DA974, msgTable_803C1280_rodata_803C122C, lbl_806DA974,
    lbl_803C1238, lbl_803C1244, lbl_803C08AC, lbl_806DA974,
    lbl_806DA9F4, lbl_806DA974, lbl_806DA9FC, lbl_806DA974,
    lbl_803C1238, lbl_803C1244, lbl_803C08AC, lbl_806DA974,
    lbl_806DAA04, lbl_806DA974, lbl_803C1250, lbl_803C125C,
    lbl_803C1250, lbl_803C125C, lbl_803C08AC, lbl_806DA974,
    lbl_803C1268, lbl_806DA974, lbl_803C1250, lbl_803C125C,
    lbl_803C1250, lbl_803C125C, lbl_803C08AC, lbl_806DA974,
    lbl_806DAA0C, lbl_806DAA14, lbl_803C1274, lbl_806DA974,
    lbl_806DAA1C, lbl_806DA974, lbl_806DAA24, lbl_806DAA2C,
};

extern "C" const char msgString_803C1340[] = "Create new pack.";

extern "C" const char msgString_803C1354[] = "Latest pack used.";

extern "C" const char msgString_803C1368[] = "Press Item button.";

extern "C" const char lbl_803C137C[] = "Items can be obtained by ";

extern "C" const char lbl_803C1398[] = "running through the item boxes.";

extern "C" const char *const msgTable_803C13B8[3] = {
    lbl_803C137C, lbl_803C1398, lbl_806DA930,
};

extern "C" const char msgString_803C13C4[] = "Following item will be used in this race.";

extern "C" const char lbl_803C13F0[] = "MARIO STAGE";

extern "C" const char lbl_803C13FC[] = "DK STAGE";

extern "C" const char lbl_803C1408[] = "WARIO STAGE";

extern "C" const char lbl_803C1414[] = "PAC-MAN STAGE";

extern "C" const char lbl_803C1424[] = "BOWSER STAGE";

extern "C" const char lbl_803C1434[] = "RAINBOW STAGE";

extern "C" const char *const msgTable_803C1444[6] = {
    lbl_803C13F0, lbl_803C13FC, lbl_803C1408, lbl_803C1414,
    lbl_803C1424, lbl_803C1434,
};

extern "C" const char lbl_803C145C[] = "MARIO HIGHWAY";

extern "C" const char lbl_803C146C[] = "MARIO BEACH";

extern "C" const char lbl_803C1478[] = "DK JUNGLE";

extern "C" const char lbl_803C1484[] = "BANANAN RUINS";

extern "C" const char lbl_803C1494[] = "DIAMOND CITY";

extern "C" const char lbl_803C14A4[] = "SNOW PANIC";

extern "C" const char lbl_803C14B0[] = "PAC MOUNTAIN";

extern "C" const char lbl_803C14C0[] = "PAC LABYRINTH";

extern "C" const char lbl_803C14D0[] = "BOWSER'S CASTLE";

extern "C" const char lbl_803C14E0[] = "CASTLE WALL";

extern "C" const char lbl_803C14EC[] = "RAINBOW COASTER";

extern "C" const char lbl_803C14FC[] = "RAINBOW DOWNHILL";

extern "C" const char *const msgTable_803C1510[12] = {
    lbl_803C145C, lbl_803C146C, lbl_803C1478, lbl_803C1484,
    lbl_803C1494, lbl_803C14A4, lbl_803C14B0, lbl_803C14C0,
    lbl_803C14D0, lbl_803C14E0, lbl_803C14EC, lbl_803C14FC,
};

extern "C" const char lbl_803C1540[] = "Night   ";

extern "C" const char lbl_803C154C[] = "After Rain";

extern "C" const char lbl_803C1558[] = "With Traps";

extern "C" const char lbl_803C1564[] = "With Traps  ";

extern "C" const char lbl_803C1574[] = "Tree of Beans";

extern "C" const char lbl_803C1584[] = "Deep Sea";

extern "C" const char *const msgTable_803C1590[24] = {
    lbl_803C11F0, lbl_803C11FC, lbl_803C1540, lbl_803C1214,
    lbl_806DAA34, lbl_806DAA3C, lbl_803C154C, lbl_806DAA44,
    lbl_803C11F0, lbl_806DAA4C, lbl_806DAA54, lbl_806DAA44,
    lbl_806DAA5C, lbl_803C1558, lbl_803C1558, lbl_806DAA44,
    lbl_806DAA64, lbl_803C1564, lbl_806DAA6C, lbl_806DAA44,
    lbl_803C1574, lbl_806DAA70, lbl_806DAA78, lbl_803C1584,
};

extern "C" const char msgString_803C15F0[] = "Following items will be used in this race";

extern "C" const char msgString_803C161C[] = "Use 3 dash mushrooms to ";

extern "C" const char msgString_803C1638[] = " reach maximum speed.";

extern "C" const int lbl_803C1650[30] = { 0x735, 0x735, 0x736, 0x737, 0x734, 0x73b, 0x73b, 0x73b, 0x734, 0x741, 0x741, 0x735, 0x741, 0x741, 0x735, 0x741, 0x741, 0x735, 0x741, 0x741, 0x735, 0x741, 0x741, 0x0, 0x738, 0x734, 0x73b, 0x73b, 0x0, 0x0 };

extern "C" const char msgTable_803C1A30_rodata_803C16C8[] = "カードが払い出されます。";

extern "C" const char msgTable_803C1A30_rodata_803C16E4[] = "カードをお取り下さい。";

extern "C" const char msgTable_803C1A30_rodata_803C16FC[] = "　　カードを";

extern "C" const char msgTable_803C1A30_rodata_803C170C[] = "入れてください。";

extern "C" const char msgTable_803C1A30_rodata_803C1720[] = "コインを入れてください。";

extern "C" const char msgTable_803C1A30_rodata_803C173C[] = "カードを購入しました。";

extern "C" const char msgTable_803C1A30_rodata_803C1754[] = "基本アイテムゲット！";

extern "C" const char msgTable_803C1A30_rodata_803C176C[] = "このカードは更新時期に";

extern "C" const char msgTable_803C1A30_rodata_803C1784[] = "なりました。";

extern "C" const char msgTable_803C1A30_rodata_803C1794[] = "次回のプレイでカードを";

extern "C" const char msgTable_803C1A30_rodata_803C17AC[] = "更新することができます。";

extern "C" const char msgTable_803C1A30_rodata_803C17C8[] = "このカードは更新時期のため";

extern "C" const char msgTable_803C1A30_rodata_803C17E4[] = "データを記録することができません。";

extern "C" const char msgTable_803C1A30_rodata_803C1808[] = "カードを更新しました。";

extern "C" const char msgTable_803C1A30_rodata_803C1820[] = "ただいまカードを使って";

extern "C" const char msgTable_803C1A30_rodata_803C1838[] = "遊ぶことはできません。";

extern "C" const char msgTable_803C1A30_rodata_803C1850[] = "ただいまカードの";

extern "C" const char msgTable_803C1A30_rodata_803C1864[] = "新規発行はできません。";

extern "C" const char msgTable_803C1A30_rodata_803C187C[] = "カードが排出されます。";

extern "C" const char msgTable_803C1A30_rodata_803C1894[] = "カードを使用せずに";

extern "C" const char msgTable_803C1A30_rodata_803C18A8[] = "ゲームをはじめます。";

extern "C" const char msgTable_803C1A30_rodata_803C18C0[] = "カードの向きを確認して";

extern "C" const char msgTable_803C1A30_rodata_803C18D8[] = "もう一度入れてください。";

extern "C" const char msgTable_803C1A30_rodata_803C18F4[] = "別のマリオカードを";

extern "C" const char msgTable_803C1A30_rodata_803C1908[] = "更新済みのカードが払い";

extern "C" const char msgTable_803C1A30_rodata_803C1920[] = "出されます。";

extern "C" const char msgTable_803C1A30_rodata_803C1930[] = "このラウンドは自分で選んだアイテムで";

extern "C" const char msgTable_803C1A30_rodata_803C1958[] = "　　　　レースを行います！";

extern "C" const char msgTable_803C1A30_rodata_803C1974[] = "ゲームデータを";

extern "C" const char msgTable_803C1A30_rodata_803C1984[] = "セーブしています。";

extern "C" const char msgTable_803C1A30_rodata_803C1998[] = "ゴールドアイテムゲット！";

extern "C" const char msgTable_803C1A30_rodata_803C19B4[] = "ロケテストカードです";

extern "C" const char msgTable_803C1A30_rodata_803C19CC[] = "このカードはロケテストカードのため";

extern "C" const char msgTable_803C1A30_rodata_803C19F0[] = "コインを%d枚入れてください。";

extern "C" const char msgTable_803C1A30_rodata_803C1A10[] = "コインを%d00円入れてください。";

extern "C" const char *const msgTable_803C1A30[120] = {
    lbl_806DA974, msgTable_803C1A30_rodata_803C16C8, lbl_806DA974, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C16E4, lbl_806DA974, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C16FC, msgTable_803C1A30_rodata_803C170C, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C1720, lbl_806DA974, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C173C, msgTable_803C1A30_rodata_803C1754, lbl_806DA974,
    msgTable_803C1A30_rodata_803C176C, msgTable_803C1A30_rodata_803C1784, msgTable_803C1A30_rodata_803C1794, msgTable_803C1A30_rodata_803C17AC,
    lbl_806DA974, msgTable_803C1A30_rodata_803C17C8, msgTable_803C1A30_rodata_803C17E4, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C176C, msgTable_803C1A30_rodata_803C1784, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C1808, lbl_806DA974, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C1820, msgTable_803C1A30_rodata_803C1838, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C1850, msgTable_803C1A30_rodata_803C1864, lbl_806DA974,
    msgTable_803C1A30_rodata_803C187C, msgTable_803C1A30_rodata_803C1894, msgTable_803C1A30_rodata_803C18A8, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C18C0, msgTable_803C1A30_rodata_803C18D8, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C1894, msgTable_803C1A30_rodata_803C18A8, lbl_806DA974,
    msgTable_803C1A30_rodata_803C187C, msgTable_803C1A30_rodata_803C1894, msgTable_803C1A30_rodata_803C18A8, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C18F4, msgTable_803C1A30_rodata_803C170C, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C1894, msgTable_803C1A30_rodata_803C18A8, lbl_806DA974,
    msgTable_803C1A30_rodata_803C187C, msgTable_803C1A30_rodata_803C1894, msgTable_803C1A30_rodata_803C18A8, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C18F4, msgTable_803C1A30_rodata_803C170C, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C1894, msgTable_803C1A30_rodata_803C18A8, lbl_806DA974,
    msgTable_803C1A30_rodata_803C187C, msgTable_803C1A30_rodata_803C1908, msgTable_803C1A30_rodata_803C1920, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C18F4, msgTable_803C1A30_rodata_803C170C, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C1894, msgTable_803C1A30_rodata_803C18A8, lbl_806DA974,
    lbl_806DA930, msgTable_803C1A30_rodata_803C1930, msgTable_803C1A30_rodata_803C1958, lbl_806DA974,
    lbl_806DA930, msgTable_803C1A30_rodata_803C1974, msgTable_803C1A30_rodata_803C1984, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C173C, msgTable_803C1A30_rodata_803C1998, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C19B4, lbl_806DA974, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C19CC, msgTable_803C1A30_rodata_803C17E4, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C19F0, lbl_806DA974, lbl_806DA974,
    lbl_806DA974, msgTable_803C1A30_rodata_803C1A10, lbl_806DA974, lbl_806DA974,
};

extern "C" const char lbl_803C1C10[] = "Card will be";

extern "C" const char lbl_803C1C20[] = "ejected.";

extern "C" const char lbl_803C1C2C[] = "Take card.";

extern "C" const char lbl_803C1C38[] = "Please insert ";

extern "C" const char lbl_803C1C48[] = "Please insert coins";

extern "C" const char lbl_803C1C5C[] = "You made a CARD";

extern "C" const char lbl_803C1C6C[] = "Basic Item Received!";

extern "C" const char lbl_803C1C84[] = "Your card must be";

extern "C" const char lbl_803C1C98[] = "renewed.";

extern "C" const char lbl_803C1CA4[] = "Card can be renewed";

extern "C" const char lbl_803C1CB8[] = "during the next game.";

extern "C" const char lbl_803C1CD0[] = "Your card cannot be saved";

extern "C" const char lbl_803C1CEC[] = "since it is not renewed.";

extern "C" const char lbl_803C1D08[] = "Your card needs";

extern "C" const char lbl_803C1D18[] = "to be renewed.";

extern "C" const char lbl_803C1D28[] = "Your card has been";

extern "C" const char lbl_803C1D3C[] = "updated.";

extern "C" const char lbl_803C1D48[] = "Card readers are ";

extern "C" const char lbl_803C1D5C[] = "not functional.";

extern "C" const char lbl_803C1D6C[] = "New cards are not available";

extern "C" const char lbl_803C1D88[] = "Card will be ejected.";

extern "C" const char lbl_803C1DA0[] = "Card reader not functional.";

extern "C" const char lbl_803C1DBC[] = "Check card position and";

extern "C" const char lbl_803C1DD4[] = "try again.";

extern "C" const char lbl_803C1DE0[] = "Game start with out";

extern "C" const char lbl_803C1DF4[] = "using card.";

extern "C" const char lbl_803C1E00[] = "Try again with a";

extern "C" const char lbl_803C1E14[] = "different card.";

extern "C" const char lbl_803C1E24[] = "Start game with out using card.";

extern "C" const char lbl_803C1E44[] = "GStart game with out ";

extern "C" const char lbl_803C1E5C[] = "Your old card";

extern "C" const char lbl_803C1E6C[] = "shall be ejected.";

extern "C" const char lbl_803C1E80[] = "In this round, ";

extern "C" const char lbl_803C1E90[] = "race with pre - selected items.";

extern "C" const char lbl_803C1EB0[] = "Saving game data";

extern "C" const char lbl_803C1EC4[] = "Gold Item Received!";

extern "C" const char lbl_803C1ED8[] = "Please insert %d coin(s)";

extern "C" const char *const msgTable_803C1EF4[120] = {
    lbl_803C1C10, lbl_803C1C20, lbl_806DA974, lbl_806DA974,
    lbl_803C1C2C, lbl_806DA974, lbl_806DA974, lbl_806DA974,
    lbl_803C1C38, lbl_806DAA84, lbl_806DA974, lbl_806DA974,
    lbl_806DA974, lbl_803C1C48, lbl_806DA974, lbl_806DA974,
    lbl_803C1C5C, lbl_803C1C6C, lbl_806DA974, lbl_806DA974,
    lbl_803C1C84, lbl_803C1C98, lbl_803C1CA4, lbl_803C1CB8,
    lbl_806DA974, lbl_803C1CD0, lbl_803C1CEC, lbl_806DA974,
    lbl_806DA974, lbl_803C1D08, lbl_803C1D18, lbl_806DA974,
    lbl_806DA974, lbl_803C1D28, lbl_803C1D3C, lbl_806DA974,
    lbl_806DA974, lbl_803C1D48, lbl_803C1D5C, lbl_806DA974,
    lbl_806DA974, lbl_803C1D6C, lbl_806DA930, lbl_806DA974,
    lbl_806DA930, lbl_803C1D88, lbl_803C1DA0, lbl_806DA974,
    lbl_806DA974, lbl_803C1DBC, lbl_803C1DD4, lbl_806DA974,
    lbl_806DA974, lbl_803C1DE0, lbl_803C1DF4, lbl_806DA974,
    lbl_806DA930, lbl_803C1D88, lbl_803C1DA0, lbl_806DA974,
    lbl_806DA974, lbl_803C1E00, lbl_803C1E14, lbl_806DA974,
    lbl_806DA974, lbl_803C1DE0, lbl_803C1DF4, lbl_806DA974,
    lbl_806DA930, lbl_803C1D88, lbl_803C1E24, lbl_806DA974,
    lbl_806DA974, lbl_803C1E00, lbl_803C1E14, lbl_806DA974,
    lbl_806DA974, lbl_803C1E44, lbl_803C1DF4, lbl_806DA974,
    lbl_806DA974, lbl_803C1E5C, lbl_803C1E6C, lbl_806DA974,
    lbl_806DA974, lbl_803C1E00, lbl_803C1E14, lbl_806DA974,
    lbl_806DA974, lbl_803C1DE0, lbl_803C1DF4, lbl_806DA974,
    lbl_806DA930, lbl_803C1E80, lbl_803C1E90, lbl_806DA974,
    lbl_806DA930, lbl_803C1EB0, lbl_806DA930, lbl_806DA974,
    lbl_803C1C5C, lbl_803C1EC4, lbl_806DA974, lbl_806DA974,
    lbl_806DA974, lbl_803C1D08, lbl_803C1D18, lbl_806DA974,
    lbl_806DA974, lbl_803C1CD0, lbl_803C1CEC, lbl_806DA974,
    lbl_806DA974, lbl_803C1ED8, lbl_806DA974, lbl_806DA974,
    lbl_806DA974, lbl_803C1ED8, lbl_806DA974, lbl_806DA974,
};

extern "C" const int lbl_803C20D4[14] = { 0x736, 0x737, 0x738, 0x73a, 0x73a, 0x73f, 0x73e, 0x73e, 0x73e, 0x747, 0x73a, 0x738, 0x738, 0x73a };

extern "C" const int lbl_803C210C[14] = { 0x746, 0x73d, 0x73d, 0x73d, 0x73d, 0x73d, 0x73d, 0x73d, 0x73d, 0x73f, 0x73d, 0x73d, 0x73d, 0x73d };

extern "C" const char msgTable_803C21BC_rodata_803C2144[] = "　　カードを入れて";

extern "C" const char msgTable_803C21BC_rodata_803C2158[] = "　　　 ください";

extern "C" const char msgTable_803C21BC_rodata_803C2168[] = "　　次のラウンドの";

extern "C" const char msgTable_803C21BC_rodata_803C217C[] = "挑戦権を手に入れました！";

extern "C" const char msgTable_803C21BC_rodata_803C2198[] = "　　　記録する";

extern "C" const char msgTable_803C21BC_rodata_803C21A8[] = "　　キャンセルする";

extern "C" const char *const msgTable_803C21BC[14][2] = {
    msgTable_803C21BC_rodata_803C2144, msgTable_803C21BC_rodata_803C2158, lbl_806DA974, lbl_806DA974,
    lbl_806DA974, lbl_806DA974, lbl_806DA974, lbl_806DA974,
    msgTable_803C21BC_rodata_803C2168, msgTable_803C21BC_rodata_803C217C, lbl_806DA974, lbl_806DA974,
    msgTable_803C21BC_rodata_803C2198, lbl_806DA974, lbl_806DA974, lbl_806DA974,
    lbl_806DA974, lbl_806DA974, msgTable_803C21BC_rodata_803C21A8, lbl_806DA974,
    lbl_806DAA8C, lbl_806DAA8C, lbl_806DAA8C, lbl_806DAA8C,
    lbl_806DAA8C, lbl_806DAA8C, lbl_806DAA80, lbl_806DAA80,
};

extern "C" const char msgTable_803C22D0_rodata_803C222C[] = "今回のゲームデータは";

extern "C" const char msgTable_803C22D0_rodata_803C2244[] = "　記録されません。";

extern "C" const char msgTable_803C22D0_rodata_803C2258[] = "　コンティニュー";

extern "C" const char msgTable_803C22D0_rodata_803C226C[] = "　　　しない";

extern "C" const char msgTable_803C22D0_rodata_803C227C[] = " 　　記録しない";

extern "C" const char msgTable_803C22D0_rodata_803C228C[] = "　キャンセルしない";

extern "C" const char msgTable_803C22D0_rodata_803C22A0[] = "このカードでゲームを";

extern "C" const char msgTable_803C22D0_rodata_803C22B8[] = "することはできません";

extern "C" const char *const msgTable_803C22D0[14][2] = {
    lbl_806DA930, lbl_806DA930, lbl_806DA930, lbl_806DAA80,
    msgTable_803C22D0_rodata_803C222C, msgTable_803C22D0_rodata_803C2244, msgTable_803C22D0_rodata_803C2258, msgTable_803C22D0_rodata_803C226C,
    lbl_806DA974, lbl_806DA974, lbl_806DA974, lbl_806DA974,
    msgTable_803C22D0_rodata_803C227C, lbl_806DA974, lbl_806DA974, lbl_806DA974,
    lbl_806DA974, lbl_806DA974, msgTable_803C22D0_rodata_803C228C, lbl_806DA974,
    msgTable_803C22D0_rodata_803C22A0, msgTable_803C22D0_rodata_803C22B8, msgTable_803C22D0_rodata_803C222C, msgTable_803C22D0_rodata_803C2244,
    msgTable_803C22D0_rodata_803C22A0, msgTable_803C22D0_rodata_803C22B8, msgTable_803C22D0_rodata_803C2258, msgTable_803C22D0_rodata_803C226C,
};

extern "C" const char lbl_803C2340[] = "   Please ";

extern "C" const char lbl_803C234C[] = " insert card";

extern "C" const char lbl_803C235C[] = " You got the title to ";

extern "C" const char lbl_803C2374[] = "challenge the  next round !";

extern "C" const char *const msgTable_803C2390[14][2] = {
    lbl_803C2340, lbl_803C234C, lbl_806DA974, lbl_806DA974,
    lbl_806DA974, lbl_806DA974, lbl_806DA974, lbl_806DA974,
    lbl_803C235C, lbl_803C2374, lbl_806DA974, lbl_806DA974,
    lbl_806DA974, lbl_806DA974, lbl_806DA974, lbl_806DA974,
    lbl_806DA974, lbl_806DA974, lbl_806DA974, lbl_806DA974,
    lbl_806DAA80, lbl_806DAA80, lbl_806DAA80, lbl_806DAA80,
    lbl_806DAA80, lbl_806DAA80, lbl_806DAA80, lbl_806DAA80,
};

extern "C" const char lbl_803C2400[] = "You can challenge";

extern "C" const char lbl_803C2414[] = " next round !";

extern "C" const char lbl_803C2424[] = " This card ";

extern "C" const char lbl_803C2430[] = " cannot be used.";

extern "C" const char *const msgTable_803C2444[14][2] = {
    lbl_806DA974, lbl_806DA974, lbl_806DA974, lbl_806DA974,
    lbl_806DA930, lbl_806DAA80, lbl_806DAA80, lbl_806DAA80,
    lbl_803C2400, lbl_803C2414, lbl_806DA974, lbl_806DA974,
    lbl_806DA974, lbl_806DA974, lbl_806DA974, lbl_806DA974,
    lbl_806DA974, lbl_806DA974, lbl_806DA974, lbl_806DA974,
    lbl_803C2424, lbl_803C2430, lbl_806DA974, lbl_806DA974,
    lbl_803C2424, lbl_803C2430, lbl_806DAA80, lbl_806DAA80,
};

extern "C" const char *const msgTable_803C24B4[5] = {
    lbl_806DAA90, lbl_806DA974, lbl_806DA974, lbl_806DA974,
    0,
};

extern "C" const char *fn_80202CC0(int msg, int line) {
    int checkedLine = line;
    if (line > 1 || line < 0) {
        checkedLine = 0;
    }
    if (msg <= -1 || msg >= 14) {
        return msgTable_803C24B4[checkedLine];
    }
    if (isJapanese() == 0) {
        return msgTable_803C22D0[msg][checkedLine];
    }
    return msgTable_803C2444[msg][checkedLine];
}

extern "C" const char *fn_80202D70(int msg, int line) {
    int checkedLine = line;
    if (line > 1 || line < 0) {
        checkedLine = 0;
    }
    if (msg <= -1 || msg >= 14) {
        return msgTable_803C24B4[checkedLine];
    }
    if (isJapanese() == 0) {
        return msgTable_803C21BC[msg][checkedLine];
    }
    return msgTable_803C2390[msg][checkedLine];
}

extern "C" int fn_80202E20(int msg) {
    if (msg <= -1 || msg >= 14) {
        return 0x734;
    }
    return lbl_803C210C[msg];
}

extern "C" int fn_80202E4C(int msg) {
    if (msg <= -1 || msg >= 14) {
        return 0x734;
    }
    return lbl_803C20D4[msg];
}

extern "C" const char *fn_80202E78(int msg, int line) {
    int checkedLine = line;
    if (line > 3 || line < 0) {
        checkedLine = 0;
    }
    if (msg <= -1 || msg >= 30) {
        return msgTable_803C24B4[checkedLine];
    }
    if (isJapanese() == 0) {
        return ((const char *const (*)[4])msgTable_803C1A30)[msg][checkedLine];
    }
    return ((const char *const (*)[4])msgTable_803C1EF4)[msg][checkedLine];
}
