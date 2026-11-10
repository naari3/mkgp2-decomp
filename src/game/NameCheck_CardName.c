#include "game/types/text_word.h"
/* NameCheck: card-name filter (0x80099994..0x8009B98C), merged from
 * NameCheck_CardName.c + NameCheck_ScanBanned.c.
 *
 * Both functions address their tables through this TU's .rodata section
 * anchor (0x80318270, +0x10000 for offsets past 32K), so the TU owns the whole
 * pool 0x80318270..0x80320960; the tables and strings the code reads are
 * static objects, everything referenced from other TUs keeps its global name.
 * docs/mwcc_internals.md "Vreg numbering" (NameCheck_CardName).
 */
#include "game/NameCheck_ScanBanned_private.h"

extern NameCode *wcscpy(NameCode *, const NameCode *);
extern void DebugPrintf(const char *, ...);
extern unsigned int wcslen(const unsigned short *);
extern unsigned char NameCheck_ScanBannedWords(unsigned short *);



/* --- .rodata 0x80318270..0x8031B7C0 (tools/data2c.py) --- */
#pragma force_active on
/* element type read off the values (all floats), not from code */
const float NameCheck_CardName_rodata_80318270[255] = {
    1.0f, 0.7f, 0.9f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f,
    83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f,
    83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f,
    83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f,
    0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f,
    83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f,
    83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f,
    83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f,
    83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f,
    83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f,
    83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f
};
const char lbl_8031866C[] = "cart_mario.dat";
const char lbl_8031867C[] = "cart_mario_mid.dat";
const char lbl_80318690[] = "cart_mario_low.dat";
const char lbl_803186A4[] = "cart_luigi.dat";
const char lbl_803186B4[] = "cart_luigi_mid.dat";
const char lbl_803186C8[] = "cart_luigi_low.dat";
const char lbl_803186DC[] = "cart_wario.dat";
const char lbl_803186EC[] = "cart_wario_mid.dat";
const char lbl_80318700[] = "cart_wario_low.dat";
const char lbl_80318714[] = "cart_peach.dat";
const char lbl_80318724[] = "cart_peach_mid.dat";
const char lbl_80318738[] = "cart_peach_low.dat";
const char lbl_8031874C[] = "cart_koopa.dat";
const char lbl_8031875C[] = "cart_koopa_mid.dat";
const char lbl_80318770[] = "cart_koopa_low.dat";
const char lbl_80318784[] = "cart_kinopio.dat";
const char lbl_80318798[] = "cart_kinopio_mid.dat";
const char lbl_803187B0[] = "cart_kinopio_low.dat";
const char lbl_803187C8[] = "cart_donkey.dat";
const char lbl_803187D8[] = "cart_donkey_mid.dat";
const char lbl_803187EC[] = "cart_donkey_low.dat";
const char lbl_80318800[] = "cart_yoshi.dat";
const char lbl_80318810[] = "cart_yoshi_mid.dat";
const char lbl_80318824[] = "cart_yoshi_low.dat";
const char lbl_80318838[] = "cart_pacman.dat";
const char lbl_80318848[] = "cart_pacman_mid.dat";
const char lbl_8031885C[] = "cart_pacman_low.dat";
const char lbl_80318870[] = "cart_mspacman.dat";
const char lbl_80318884[] = "cart_mspacman_mid.dat";
const char lbl_8031889C[] = "cart_mspacman_low.dat";
const char lbl_803188B4[] = "cart_monster.dat";
const char lbl_803188C8[] = "cart_monster_mid.dat";
const char lbl_803188E0[] = "cart_monster_low.dat";
const char lbl_803188F8[] = "cart_waluigi.dat";
const char lbl_8031890C[] = "cart_waluigi_mid.dat";
const char lbl_80318924[] = "cart_waluigi_low.dat";
const char lbl_8031893C[] = "cart_mametch.dat";
const char lbl_80318950[] = "cart_mametch_mid.dat";
const char lbl_80318968[] = "cart_mametch_low.dat";
const char lbl_80318980[] = "gold_mario.dat";
const char lbl_80318990[] = "gold_mario_mid.dat";
const char lbl_803189A4[] = "gold_mario_low.dat";
const char lbl_803189B8[] = "gold_luigi.dat";
const char lbl_803189C8[] = "gold_luigi_mid.dat";
const char lbl_803189DC[] = "gold_luigi_low.dat";
const char lbl_803189F0[] = "gold_wario.dat";
const char lbl_80318A00[] = "gold_wario_mid.dat";
const char lbl_80318A14[] = "gold_wario_low.dat";
const char lbl_80318A28[] = "gold_peach.dat";
const char lbl_80318A38[] = "gold_peach_mid.dat";
const char lbl_80318A4C[] = "gold_peach_low.dat";
const char lbl_80318A60[] = "gold_koopa.dat";
const char lbl_80318A70[] = "gold_koopa_mid.dat";
const char lbl_80318A84[] = "gold_koopa_low.dat";
const char lbl_80318A98[] = "gold_kinopio.dat";
const char lbl_80318AAC[] = "gold_kinopio_mid.dat";
const char lbl_80318AC4[] = "gold_kinopio_low.dat";
const char lbl_80318ADC[] = "gold_donkey.dat";
const char lbl_80318AEC[] = "gold_donkey_mid.dat";
const char lbl_80318B00[] = "gold_donkey_low.dat";
const char lbl_80318B14[] = "gold_yoshi.dat";
const char lbl_80318B24[] = "gold_yoshi_mid.dat";
const char lbl_80318B38[] = "gold_yoshi_low.dat";
const char lbl_80318B4C[] = "gold_pacman.dat";
const char lbl_80318B5C[] = "gold_pacman_mid.dat";
const char lbl_80318B70[] = "gold_pacman_low.dat";
const char lbl_80318B84[] = "gold_mspacman.dat";
const char lbl_80318B98[] = "gold_mspacman_mid.dat";
const char lbl_80318BB0[] = "gold_mspacman_low.dat";
const char lbl_80318BC8[] = "gold_monster.dat";
const char lbl_80318BDC[] = "gold_monster_mid.dat";
const char lbl_80318BF4[] = "gold_monster_low.dat";
const char lbl_80318C0C[] = "gold_waluigi.dat";
const char lbl_80318C20[] = "gold_waluigi_mid.dat";
const char lbl_80318C38[] = "gold_waluigi_low.dat";
const char lbl_80318C50[] = "gold_mametch.dat";
const char lbl_80318C64[] = "gold_mametch_mid.dat";
const char lbl_80318C7C[] = "gold_mametch_low.dat";
const char lbl_80318C94[] = "sp_cart_mario.dat";
const char lbl_80318CA8[] = "sp_cart_mario_mid.dat";
const char lbl_80318CC0[] = "sp_cart_mario_low.dat";
const char lbl_80318CD8[] = "sp_cart_luigi.dat";
const char lbl_80318CEC[] = "sp_cart_luigi_mid.dat";
const char lbl_80318D04[] = "sp_cart_luigi_low.dat";
const char lbl_80318D1C[] = "sp_cart_wario.dat";
const char lbl_80318D30[] = "sp_cart_wario_mid.dat";
const char lbl_80318D48[] = "sp_cart_wario_low.dat";
const char lbl_80318D60[] = "sp_cart_peach.dat";
const char lbl_80318D74[] = "sp_cart_peach_mid.dat";
const char lbl_80318D8C[] = "sp_cart_peach_low.dat";
const char lbl_80318DA4[] = "sp_cart_koopa.dat";
const char lbl_80318DB8[] = "sp_cart_koopa_mid.dat";
const char lbl_80318DD0[] = "sp_cart_koopa_low.dat";
const char lbl_80318DE8[] = "sp_cart_kinopio.dat";
const char lbl_80318DFC[] = "sp_cart_kinopio_mid.dat";
const char lbl_80318E14[] = "sp_cart_kinopio_low.dat";
const char lbl_80318E2C[] = "sp_cart_donkey.dat";
const char lbl_80318E40[] = "sp_cart_donkey_mid.dat";
const char lbl_80318E58[] = "sp_cart_donkey_low.dat";
const char lbl_80318E70[] = "sp_cart_yoshi.dat";
const char lbl_80318E84[] = "sp_cart_yoshi_mid.dat";
const char lbl_80318E9C[] = "sp_cart_yoshi_low.dat";
const char lbl_80318EB4[] = "sp_cart_pacman.dat";
const char lbl_80318EC8[] = "sp_cart_pacman_mid.dat";
const char lbl_80318EE0[] = "sp_cart_pacman_low.dat";
const char lbl_80318EF8[] = "sp_cart_mspacman.dat";
const char lbl_80318F10[] = "sp_cart_mspacman_mid.dat";
const char lbl_80318F2C[] = "sp_cart_mspacman_low.dat";
const char lbl_80318F48[] = "sp_cart_monster.dat";
const char lbl_80318F5C[] = "sp_cart_monster_mid.dat";
const char lbl_80318F74[] = "sp_cart_monster_low.dat";
const char lbl_80318F8C[] = "sp_cart_waluigi.dat";
const char lbl_80318FA0[] = "sp_cart_waluigi_mid.dat";
const char lbl_80318FB8[] = "sp_cart_waluigi_low.dat";
const char lbl_80318FD0[] = "sp_cart_mametch.dat";
const char lbl_80318FE4[] = "sp_cart_mametch_mid.dat";
const char lbl_80318FFC[] = "sp_cart_mametch_low.dat";
const char lbl_80319014[] = "mario_handle.dat";
const char lbl_80319028[] = "mario_item_handle.dat";
const char lbl_80319040[] = "mario_tamb_cen.dat";
const char lbl_80319054[] = "mario_item_pa_tamb.dat";
const char lbl_8031906C[] = "mario_item_goo_tamb.dat";
const char lbl_80319084[] = "mario_tamb_l.dat";
const char lbl_80319098[] = "mario_item_pa_tamb_l.dat";
const char lbl_803190B4[] = "mario_item_goo_tamb_l.dat";
const char lbl_803190D0[] = "mario_tamb_r.dat";
const char lbl_803190E4[] = "mario_item_pa_tamb_r.dat";
const char lbl_80319100[] = "mario_item_goo_tamb_r.dat";
const char lbl_8031911C[] = "mario_damage.dat";
const char lbl_80319130[] = "mario_hit_l.dat";
const char lbl_80319140[] = "mario_hit_r.dat";
const char lbl_80319150[] = "mario_item_attack.dat";
const char lbl_80319168[] = "mario_jump.dat";
const char lbl_80319178[] = "mario_item_jump.dat";
const char lbl_8031918C[] = "mario_item_b_attack.dat";
const char lbl_803191A4[] = "mario_turbo_lv1.dat";
const char lbl_803191B8[] = "mario_item_turbo_lv1.dat";
const char lbl_803191D4[] = "mario_brake.dat";
const char lbl_803191E4[] = "mario_item_brake.dat";
const char lbl_803191FC[] = "mario_surprise.dat";
const char lbl_80319210[] = "mario_item_surprise.dat";
const char lbl_80319228[] = "mario_joy.dat";
const char lbl_80319238[] = "mario_absorption.dat";
const char lbl_80319250[] = "mario_bazooka.dat";
const char lbl_80319264[] = "mario_hammer.dat";
const char lbl_80319278[] = "mario_take.dat";
const char lbl_80319288[] = "mario_win.dat";
const char lbl_80319298[] = "mario_loses.dat";
const char lbl_803192A8[] = "mario_hit_thunder.dat";
const char lbl_803192C0[] = "luigi_handle.dat";
const char lbl_803192D4[] = "luigi_item_handle.dat";
const char lbl_803192EC[] = "luigi_tamb_cen.dat";
const char lbl_80319300[] = "luigi_item_pa_tamb.dat";
const char lbl_80319318[] = "luigi_item_goo_tamb.dat";
const char lbl_80319330[] = "luigi_tamb_l.dat";
const char lbl_80319344[] = "luigi_item_pa_tamb_l.dat";
const char lbl_80319360[] = "luigi_item_goo_tamb_l.dat";
const char lbl_8031937C[] = "luigi_tamb_r.dat";
const char lbl_80319390[] = "luigi_item_pa_tamb_r.dat";
const char lbl_803193AC[] = "luigi_item_goo_tamb_r.dat";
const char lbl_803193C8[] = "luigi_damage.dat";
const char lbl_803193DC[] = "luigi_hit_l.dat";
const char lbl_803193EC[] = "luigi_hit_r.dat";
const char lbl_803193FC[] = "luigi_item_attack.dat";
const char lbl_80319414[] = "luigi_jump.dat";
const char lbl_80319424[] = "luigi_item_jump.dat";
const char lbl_80319438[] = "luigi_item_b_attack.dat";
const char lbl_80319450[] = "luigi_turbo_lv1.dat";
const char lbl_80319464[] = "luigi_item_turbo_lv1.dat";
const char lbl_80319480[] = "luigi_brake.dat";
const char lbl_80319490[] = "luigi_item_brake.dat";
const char lbl_803194A8[] = "luigi_surprise.dat";
const char lbl_803194BC[] = "luigi_item_surprise.dat";
const char lbl_803194D4[] = "luigi_joy.dat";
const char lbl_803194E4[] = "luigi_absorption.dat";
const char lbl_803194FC[] = "luigi_bazooka.dat";
const char lbl_80319510[] = "luigi_hammer.dat";
const char lbl_80319524[] = "luigi_take.dat";
const char lbl_80319534[] = "luigi_win.dat";
const char lbl_80319544[] = "luigi_loses.dat";
const char lbl_80319554[] = "luigi_hit_thunder.dat";
const char lbl_8031956C[] = "wario_handle.dat";
const char lbl_80319580[] = "wario_item_handle.dat";
const char lbl_80319598[] = "wario_fart_handle.dat";
const char lbl_803195B0[] = "wario_pick_handle.dat";
const char lbl_803195C8[] = "wario_tamb_cen.dat";
const char lbl_803195DC[] = "wario_item_pa_tamb.dat";
const char lbl_803195F4[] = "wario_item_goo_tamb.dat";
const char lbl_8031960C[] = "wario_fart_tamb_cen.dat";
const char lbl_80319624[] = "wario_pick_tamb_cen.dat";
const char lbl_8031963C[] = "wario_tamb_l.dat";
const char lbl_80319650[] = "wario_item_pa_tamb_l.dat";
const char lbl_8031966C[] = "wario_item_goo_tamb_l.dat";
const char lbl_80319688[] = "wario_fart_tamb_l.dat";
const char lbl_803196A0[] = "wario_pick_tamb_l.dat";
const char lbl_803196B8[] = "wario_tamb_r.dat";
const char lbl_803196CC[] = "wario_item_pa_tamb_r.dat";
const char lbl_803196E8[] = "wario_item_goo_tamb_r.dat";
const char lbl_80319704[] = "wario_fart_tamb_r.dat";
const char lbl_8031971C[] = "wario_pick_tamb_r.dat";
const char lbl_80319734[] = "wario_damage.dat";
const char lbl_80319748[] = "wario_hit_l.dat";
const char lbl_80319758[] = "wario_hit_r.dat";
const char lbl_80319768[] = "wario_item_attack.dat";
const char lbl_80319780[] = "wario_jump.dat";
const char lbl_80319790[] = "wario_item_jump.dat";
const char lbl_803197A4[] = "wario_fart_jump.dat";
const char lbl_803197B8[] = "wario_pick_jump.dat";
const char lbl_803197CC[] = "wario_item_b_attack.dat";
const char lbl_803197E4[] = "wario_turbo_lv1.dat";
const char lbl_803197F8[] = "wario_item_turbo_lv1.dat";
const char lbl_80319814[] = "wario_brake.dat";
const char lbl_80319824[] = "wario_item_brake.dat";
const char lbl_8031983C[] = "wario_surprise.dat";
const char lbl_80319850[] = "wario_item_surprise.dat";
const char lbl_80319868[] = "wario_fart_surprise.dat";
const char lbl_80319880[] = "wario_pick_surprise.dat";
const char lbl_80319898[] = "wario_joy.dat";
const char lbl_803198A8[] = "wario_absorption.dat";
const char lbl_803198C0[] = "wario_bazooka.dat";
const char lbl_803198D4[] = "wario_hammer.dat";
const char lbl_803198E8[] = "wario_take.dat";
const char lbl_803198F8[] = "wario_win.dat";
const char lbl_80319908[] = "wario_loses.dat";
const char lbl_80319918[] = "wario_hit_thunder.dat";
const char lbl_80319930[] = "wario_biyoyonpunch.dat";
const char lbl_80319948[] = "wario_item_eat.dat";
const char lbl_8031995C[] = "wario_fart_attack.dat";
const char lbl_80319974[] = "peach_handle.dat";
const char lbl_80319988[] = "peach_item_handle.dat";
const char lbl_803199A0[] = "peach_tamb_cen.dat";
const char lbl_803199B4[] = "peach_item_pa_tamb.dat";
const char lbl_803199CC[] = "peach_item_goo_tamb.dat";
const char lbl_803199E4[] = "peach_tamb_l.dat";
const char lbl_803199F8[] = "peach_item_pa_tamb_l.dat";
const char lbl_80319A14[] = "peach_item_goo_tamb_l.dat";
const char lbl_80319A30[] = "peach_tamb_r.dat";
const char lbl_80319A44[] = "peach_item_pa_tamb_r.dat";
const char lbl_80319A60[] = "peach_item_goo_tamb_r.dat";
const char lbl_80319A7C[] = "peach_damage.dat";
const char lbl_80319A90[] = "peach_hit_l.dat";
const char lbl_80319AA0[] = "peach_hit_r.dat";
const char lbl_80319AB0[] = "peach_item_attack.dat";
const char lbl_80319AC8[] = "peach_jump.dat";
const char lbl_80319AD8[] = "peach_item_jump.dat";
const char lbl_80319AEC[] = "peach_item_b_attack.dat";
const char lbl_80319B04[] = "peach_turbo_lv1.dat";
const char lbl_80319B18[] = "peach_item_turbo_lv1.dat";
const char lbl_80319B34[] = "peach_brake.dat";
const char lbl_80319B44[] = "peach_item_brake.dat";
const char lbl_80319B5C[] = "peach_surprise.dat";
const char lbl_80319B70[] = "peach_item_surprise.dat";
const char lbl_80319B88[] = "peach_joy.dat";
const char lbl_80319B98[] = "peach_absorption.dat";
const char lbl_80319BB0[] = "peach_bazooka.dat";
const char lbl_80319BC4[] = "peach_hammer.dat";
const char lbl_80319BD8[] = "peach_take.dat";
const char lbl_80319BE8[] = "peach_win.dat";
const char lbl_80319BF8[] = "peach_loses.dat";
const char lbl_80319C08[] = "peach_hit_thunder.dat";
const char lbl_80319C20[] = "peach_item_drink.dat";
const char lbl_80319C38[] = "koopa_handle.dat";
const char lbl_80319C4C[] = "koopa_item_handle.dat";
const char lbl_80319C64[] = "koopa_tamb_cen.dat";
const char lbl_80319C78[] = "koopa_item_pa_tamb.dat";
const char lbl_80319C90[] = "koopa_item_goo_tamb.dat";
const char lbl_80319CA8[] = "koopa_tamb_l.dat";
const char lbl_80319CBC[] = "koopa_item_pa_tamb_l.dat";
const char lbl_80319CD8[] = "koopa_item_goo_tamb_l.dat";
const char lbl_80319CF4[] = "koopa_tamb_r.dat";
const char lbl_80319D08[] = "koopa_item_pa_tamb_r.dat";
const char lbl_80319D24[] = "koopa_item_goo_tamb_r.dat";
const char lbl_80319D40[] = "koopa_damage.dat";
const char lbl_80319D54[] = "koopa_hit_l.dat";
const char lbl_80319D64[] = "koopa_hit_r.dat";
const char lbl_80319D74[] = "koopa_item_attack.dat";
const char lbl_80319D8C[] = "koopa_jump.dat";
const char lbl_80319D9C[] = "koopa_item_jump.dat";
const char lbl_80319DB0[] = "koopa_item_b_attack.dat";
const char lbl_80319DC8[] = "koopa_turbo_lv1.dat";
const char lbl_80319DDC[] = "koopa_item_turbo_lv1.dat";
const char lbl_80319DF8[] = "koopa_brake.dat";
const char lbl_80319E08[] = "koopa_item_brake.dat";
const char lbl_80319E20[] = "koopa_surprise.dat";
const char lbl_80319E34[] = "koopa_item_surprise.dat";
const char lbl_80319E4C[] = "koopa_joy.dat";
const char lbl_80319E5C[] = "koopa_absorption.dat";
const char lbl_80319E74[] = "koopa_bazooka.dat";
const char lbl_80319E88[] = "koopa_hammer.dat";
const char lbl_80319E9C[] = "koopa_take.dat";
const char lbl_80319EAC[] = "koopa_win.dat";
const char lbl_80319EBC[] = "koopa_loses.dat";
const char lbl_80319ECC[] = "koopa_hit_thunder.dat";
const char lbl_80319EE4[] = "koopa_item_eat.dat";
const char lbl_80319EF8[] = "koopa_b_bazooka.dat";
const char lbl_80319F0C[] = "koopa_fire_attack.dat";
const char lbl_80319F24[] = "kinopio_handle.dat";
const char lbl_80319F38[] = "kinopio_item_handle.dat";
const char lbl_80319F50[] = "kinopio_tamb_cen.dat";
const char lbl_80319F68[] = "kinopio_item_pa_tamb.dat";
const char lbl_80319F84[] = "kinopio_item_goo_tamb.dat";
const char lbl_80319FA0[] = "kinopio_tamb_l.dat";
const char lbl_80319FB4[] = "kinopio_item_pa_tamb_l.dat";
const char lbl_80319FD0[] = "kinopio_item_goo_tamb_l.dat";
const char lbl_80319FEC[] = "kinopio_tamb_r.dat";
const char lbl_8031A000[] = "kinopio_item_pa_tamb_r.dat";
const char lbl_8031A01C[] = "kinopio_item_goo_tamb_r.dat";
const char lbl_8031A038[] = "kinopio_damage.dat";
const char lbl_8031A04C[] = "kinopio_hit_l.dat";
const char lbl_8031A060[] = "kinopio_hit_r.dat";
const char lbl_8031A074[] = "kinopio_item_attack.dat";
const char lbl_8031A08C[] = "kinopio_jump.dat";
const char lbl_8031A0A0[] = "kinopio_item_jump.dat";
const char lbl_8031A0B8[] = "kinopio_item_b_attack.dat";
const char lbl_8031A0D4[] = "kinopio_turbo_lv1.dat";
const char lbl_8031A0EC[] = "kinopio_item_turbo_lv1.dat";
const char lbl_8031A108[] = "kinopio_brake.dat";
const char lbl_8031A11C[] = "kinopio_item_brake.dat";
const char lbl_8031A134[] = "kinopio_surprise.dat";
const char lbl_8031A14C[] = "kinopio_item_surprise.dat";
const char lbl_8031A168[] = "kinopio_joy.dat";
const char lbl_8031A178[] = "kinopio_absorption.dat";
const char lbl_8031A190[] = "kinopio_bazooka.dat";
const char lbl_8031A1A4[] = "kinopio_hammer.dat";
const char lbl_8031A1B8[] = "kinopio_take.dat";
const char lbl_8031A1CC[] = "kinopio_win.dat";
const char lbl_8031A1DC[] = "kinopio_loses.dat";
const char lbl_8031A1F0[] = "kinopio_hit_thunder.dat";
const char lbl_8031A208[] = "donkey_handle.dat";
const char lbl_8031A21C[] = "donkey_item_handle.dat";
const char lbl_8031A234[] = "donkey_banana_handle.dat";
const char lbl_8031A250[] = "donkey_tamb_cen.dat";
const char lbl_8031A264[] = "donkey_item_pa_tamb.dat";
const char lbl_8031A27C[] = "donkey_item_goo_tamb.dat";
const char lbl_8031A298[] = "donkey_banana_tamb_cen.dat";
const char lbl_8031A2B4[] = "donkey_tamb_l.dat";
const char lbl_8031A2C8[] = "donkey_item_pa_tamb_l.dat";
const char lbl_8031A2E4[] = "donkey_item_goo_tamb_l.dat";
const char lbl_8031A300[] = "donkey_banana_tamb_l.dat";
const char lbl_8031A31C[] = "donkey_tamb_r.dat";
const char lbl_8031A330[] = "donkey_item_pa_tamb_r.dat";
const char lbl_8031A34C[] = "donkey_item_goo_tamb_r.dat";
const char lbl_8031A368[] = "donkey_banana_tamb_r.dat";
const char lbl_8031A384[] = "donkey_damage.dat";
const char lbl_8031A398[] = "donkey_hit_l.dat";
const char lbl_8031A3AC[] = "donkey_hit_r.dat";
const char lbl_8031A3C0[] = "donkey_item_attack.dat";
const char lbl_8031A3D8[] = "donkey_jump.dat";
const char lbl_8031A3E8[] = "donkey_item_jump.dat";
const char lbl_8031A400[] = "donkey_banana_jump.dat";
const char lbl_8031A418[] = "donkey_item_b_attack.dat";
const char lbl_8031A434[] = "donkey_turbo_lv1.dat";
const char lbl_8031A44C[] = "donkey_item_turbo_lv1.dat";
const char lbl_8031A468[] = "donkey_brake.dat";
const char lbl_8031A47C[] = "donkey_item_brake.dat";
const char lbl_8031A494[] = "donkey_surprise.dat";
const char lbl_8031A4A8[] = "donkey_item_surprise.dat";
const char lbl_8031A4C4[] = "donkey_banana_surprise.dat";
const char lbl_8031A4E0[] = "donkey_joy.dat";
const char lbl_8031A4F0[] = "donkey_absorption.dat";
const char lbl_8031A508[] = "donkey_bazooka.dat";
const char lbl_8031A51C[] = "donkey_hammer.dat";
const char lbl_8031A530[] = "donkey_take.dat";
const char lbl_8031A540[] = "donkey_win.dat";
const char lbl_8031A550[] = "donkey_loses.dat";
const char lbl_8031A564[] = "donkey_hit_thunder.dat";
const char lbl_8031A57C[] = "donkey_slack_attack.dat";
const char lbl_8031A594[] = "donkey_slack_b_attack.dat";
const char lbl_8031A5B0[] = "donkey_item_eat.dat";
const char lbl_8031A5C4[] = "donkey_conga.dat";
const char lbl_8031A5D8[] = "yoshi_handle.dat";
const char lbl_8031A5EC[] = "yoshi_item_handle.dat";
const char lbl_8031A604[] = "yoshi_bero_handle.dat";
const char lbl_8031A61C[] = "yoshi_tamb_cen.dat";
const char lbl_8031A630[] = "yoshi_item_pa_tamb.dat";
const char lbl_8031A648[] = "yoshi_item_goo_tamb.dat";
const char lbl_8031A660[] = "yoshi_bero_tamb_cen.dat";
const char lbl_8031A678[] = "yoshi_tamb_l.dat";
const char lbl_8031A68C[] = "yoshi_item_pa_tamb_l.dat";
const char lbl_8031A6A8[] = "yoshi_item_goo_tamb_l.dat";
const char lbl_8031A6C4[] = "yoshi_bero_tamb_l.dat";
const char lbl_8031A6DC[] = "yoshi_tamb_r.dat";
const char lbl_8031A6F0[] = "yoshi_item_pa_tamb_r.dat";
const char lbl_8031A70C[] = "yoshi_item_goo_tamb_r.dat";
const char lbl_8031A728[] = "yoshi_bero_tamb_r.dat";
const char lbl_8031A740[] = "yoshi_damage.dat";
const char lbl_8031A754[] = "yoshi_hit_l.dat";
const char lbl_8031A764[] = "yoshi_hit_r.dat";
const char lbl_8031A774[] = "yoshi_item_attack.dat";
const char lbl_8031A78C[] = "yoshi_jump.dat";
const char lbl_8031A79C[] = "yoshi_item_jump.dat";
const char lbl_8031A7B0[] = "yoshi_bero_jump.dat";
const char lbl_8031A7C4[] = "yoshi_item_b_attack.dat";
const char lbl_8031A7DC[] = "yoshi_turbo_lv1.dat";
const char lbl_8031A7F0[] = "yoshi_item_turbo_lv1.dat";
const char lbl_8031A80C[] = "yoshi_brake.dat";
const char lbl_8031A81C[] = "yoshi_item_brake.dat";
const char lbl_8031A834[] = "yoshi_surprise.dat";
const char lbl_8031A848[] = "yoshi_item_surprise.dat";
const char lbl_8031A860[] = "yoshi_bero_surprise.dat";
const char lbl_8031A878[] = "yoshi_joy.dat";
const char lbl_8031A888[] = "yoshi_absorption.dat";
const char lbl_8031A8A0[] = "yoshi_bazooka.dat";
const char lbl_8031A8B4[] = "yoshi_hammer.dat";
const char lbl_8031A8C8[] = "yoshi_take.dat";
const char lbl_8031A8D8[] = "yoshi_win.dat";
const char lbl_8031A8E8[] = "yoshi_loses.dat";
const char lbl_8031A8F8[] = "yoshi_hit_thunder.dat";
const char lbl_8031A910[] = "yoshi_bero_attack.dat";
const char lbl_8031A928[] = "pacman_handle.dat";
const char lbl_8031A93C[] = "pacman_item_handle.dat";
const char lbl_8031A954[] = "pacman_tamb_cen.dat";
const char lbl_8031A968[] = "pacman_item_pa_tamb.dat";
const char lbl_8031A980[] = "pacman_item_goo_tamb.dat";
const char lbl_8031A99C[] = "pacman_tamb_l.dat";
const char lbl_8031A9B0[] = "pacman_item_pa_tamb_l.dat";
const char lbl_8031A9CC[] = "pacman_item_goo_tamb_l.dat";
const char lbl_8031A9E8[] = "pacman_tamb_r.dat";
const char lbl_8031A9FC[] = "pacman_item_pa_tamb_r.dat";
const char lbl_8031AA18[] = "pacman_item_goo_tamb_r.dat";
const char lbl_8031AA34[] = "pacman_damage.dat";
const char lbl_8031AA48[] = "pacman_hit_l.dat";
const char lbl_8031AA5C[] = "pacman_hit_r.dat";
const char lbl_8031AA70[] = "pacman_item_attack.dat";
const char lbl_8031AA88[] = "pacman_jump.dat";
const char lbl_8031AA98[] = "pacman_item_jump.dat";
const char lbl_8031AAB0[] = "pacman_item_b_attack.dat";
const char lbl_8031AACC[] = "pacman_turbo_lv1.dat";
const char lbl_8031AAE4[] = "pacman_item_turbo_lv1.dat";
const char lbl_8031AB00[] = "pacman_brake.dat";
const char lbl_8031AB14[] = "pacman_item_brake.dat";
const char lbl_8031AB2C[] = "pacman_surprise.dat";
const char lbl_8031AB40[] = "pacman_item_surprise.dat";
const char lbl_8031AB5C[] = "pacman_joy.dat";
const char lbl_8031AB6C[] = "pacman_absorption.dat";
const char lbl_8031AB84[] = "pacman_bazooka.dat";
const char lbl_8031AB98[] = "pacman_hammer.dat";
const char lbl_8031ABAC[] = "pacman_take.dat";
const char lbl_8031ABBC[] = "pacman_win.dat";
const char lbl_8031ABCC[] = "pacman_loses.dat";
const char lbl_8031ABE0[] = "pacman_hit_thunder.dat";
const char lbl_8031ABF8[] = "mspacman_handle.dat";
const char lbl_8031AC0C[] = "mspacman_item_handle.dat";
const char lbl_8031AC28[] = "mspacman_tamb_cen.dat";
const char lbl_8031AC40[] = "mspacman_item_pa_tamb.dat";
const char lbl_8031AC5C[] = "mspacman_item_goo_tamb.dat";
const char lbl_8031AC78[] = "mspacman_tamb_l.dat";
const char lbl_8031AC8C[] = "mspacman_item_pa_tamb_l.dat";
const char lbl_8031ACA8[] = "mspacman_item_goo_tamb_l.dat";
const char lbl_8031ACC8[] = "mspacman_tamb_r.dat";
const char lbl_8031ACDC[] = "mspacman_item_pa_tamb_r.dat";
const char lbl_8031ACF8[] = "mspacman_item_goo_tamb_r.dat";
const char lbl_8031AD18[] = "mspacman_damage.dat";
const char lbl_8031AD2C[] = "mspacman_hit_l.dat";
const char lbl_8031AD40[] = "mspacman_hit_r.dat";
const char lbl_8031AD54[] = "mspacman_item_attack.dat";
const char lbl_8031AD70[] = "mspacman_jump.dat";
const char lbl_8031AD84[] = "mspacman_item_jump.dat";
const char lbl_8031AD9C[] = "mspacman_item_b_attack.dat";
const char lbl_8031ADB8[] = "mspacman_turbo_lv1.dat";
const char lbl_8031ADD0[] = "mspacman_item_turbo_lv1.dat";
const char lbl_8031ADEC[] = "mspacman_brake.dat";
const char lbl_8031AE00[] = "mspacman_item_brake.dat";
const char lbl_8031AE18[] = "mspacman_surprise.dat";
const char lbl_8031AE30[] = "mspacman_item_surprise.dat";
const char lbl_8031AE4C[] = "mspacman_joy.dat";
const char lbl_8031AE60[] = "mspacman_absorption.dat";
const char lbl_8031AE78[] = "mspacman_bazooka.dat";
const char lbl_8031AE90[] = "mspacman_hammer.dat";
const char lbl_8031AEA4[] = "mspacman_take.dat";
const char lbl_8031AEB8[] = "mspacman_win.dat";
const char lbl_8031AECC[] = "mspacman_loses.dat";
const char lbl_8031AEE0[] = "mspacman_hit_thunder.dat";
const char lbl_8031AEFC[] = "monster_handle.dat";
const char lbl_8031AF10[] = "monster_item_handle.dat";
const char lbl_8031AF28[] = "monster_tamb_cen.dat";
const char lbl_8031AF40[] = "monster_item_pa_tamb.dat";
const char lbl_8031AF5C[] = "monster_item_goo_tamb.dat";
const char lbl_8031AF78[] = "monster_tamb_l.dat";
const char lbl_8031AF8C[] = "monster_item_pa_tamb_l.dat";
const char lbl_8031AFA8[] = "monster_item_goo_tamb_l.dat";
const char lbl_8031AFC4[] = "monster_tamb_r.dat";
const char lbl_8031AFD8[] = "monster_item_pa_tamb_r.dat";
const char lbl_8031AFF4[] = "monster_item_goo_tamb_r.dat";
const char lbl_8031B010[] = "monster_damage.dat";
const char lbl_8031B024[] = "monster_hit_l.dat";
const char lbl_8031B038[] = "monster_hit_r.dat";
const char lbl_8031B04C[] = "monster_item_attack.dat";
const char lbl_8031B064[] = "monster_jump.dat";
const char lbl_8031B078[] = "monster_item_jump.dat";
const char lbl_8031B090[] = "monster_item_b_attack.dat";
const char lbl_8031B0AC[] = "monster_turbo_lv1.dat";
const char lbl_8031B0C4[] = "monster_item_turbo_lv1.dat";
const char lbl_8031B0E0[] = "monster_brake.dat";
const char lbl_8031B0F4[] = "monster_item_brake.dat";
const char lbl_8031B10C[] = "monster_surprise.dat";
const char lbl_8031B124[] = "monster_item_surprise.dat";
const char lbl_8031B140[] = "monster_joy.dat";
const char lbl_8031B150[] = "monster_absorption.dat";
const char lbl_8031B168[] = "monster_bazooka.dat";
const char lbl_8031B17C[] = "monster_hammer.dat";
const char lbl_8031B190[] = "monster_take.dat";
const char lbl_8031B1A4[] = "monster_win.dat";
const char lbl_8031B1B4[] = "monster_loses.dat";
const char lbl_8031B1C8[] = "monster_hit_thunder.dat";
const char lbl_8031B1E0[] = "monster_item_eat.dat";
const char lbl_8031B1F8[] = "waluigi_handle.dat";
const char lbl_8031B20C[] = "waluigi_item_handle.dat";
const char lbl_8031B224[] = "waluigi_tamb_cen.dat";
const char lbl_8031B23C[] = "waluigi_item_pa_tamb.dat";
const char lbl_8031B258[] = "waluigi_item_goo_tamb.dat";
const char lbl_8031B274[] = "waluigi_tamb_l.dat";
const char lbl_8031B288[] = "waluigi_item_pa_tamb_l.dat";
const char lbl_8031B2A4[] = "waluigi_item_goo_tamb_l.dat";
const char lbl_8031B2C0[] = "waluigi_tamb_r.dat";
const char lbl_8031B2D4[] = "waluigi_item_pa_tamb_r.dat";
const char lbl_8031B2F0[] = "waluigi_item_goo_tamb_r.dat";
const char lbl_8031B30C[] = "waluigi_damage.dat";
const char lbl_8031B320[] = "waluigi_hit_l.dat";
const char lbl_8031B334[] = "waluigi_hit_r.dat";
const char lbl_8031B348[] = "waluigi_item_attack.dat";
const char lbl_8031B360[] = "waluigi_jump.dat";
const char lbl_8031B374[] = "waluigi_item_jump.dat";
const char lbl_8031B38C[] = "waluigi_item_b_attack.dat";
const char lbl_8031B3A8[] = "waluigi_turbo_lv1.dat";
const char lbl_8031B3C0[] = "waluigi_item_turbo_lv1.dat";
const char lbl_8031B3DC[] = "waluigi_brake.dat";
const char lbl_8031B3F0[] = "waluigi_item_brake.dat";
const char lbl_8031B408[] = "waluigi_surprise.dat";
const char lbl_8031B420[] = "waluigi_item_surprise.dat";
const char lbl_8031B43C[] = "waluigi_joy.dat";
const char lbl_8031B44C[] = "waluigi_absorption.dat";
const char lbl_8031B464[] = "waluigi_bazooka.dat";
const char lbl_8031B478[] = "waluigi_hammer.dat";
const char lbl_8031B48C[] = "waluigi_take.dat";
const char lbl_8031B4A0[] = "waluigi_win.dat";
const char lbl_8031B4B0[] = "waluigi_loses.dat";
const char lbl_8031B4C4[] = "waluigi_hit_thunder.dat";
const char lbl_8031B4DC[] = "mametch_handle.dat";
const char lbl_8031B4F0[] = "mametch_item_handle.dat";
const char lbl_8031B508[] = "mametch_tamb_cen.dat";
const char lbl_8031B520[] = "mametch_item_pa_tamb.dat";
const char lbl_8031B53C[] = "mametch_item_goo_tamb.dat";
const char lbl_8031B558[] = "mametch_tamb_l.dat";
const char lbl_8031B56C[] = "mametch_item_pa_tamb_l.dat";
const char lbl_8031B588[] = "mametch_item_goo_tamb_l.dat";
const char lbl_8031B5A4[] = "mametch_tamb_r.dat";
const char lbl_8031B5B8[] = "mametch_item_pa_tamb_r.dat";
const char lbl_8031B5D4[] = "mametch_item_goo_tamb_r.dat";
const char lbl_8031B5F0[] = "mametch_damage.dat";
const char lbl_8031B604[] = "mametch_hit_l.dat";
const char lbl_8031B618[] = "mametch_hit_r.dat";
const char lbl_8031B62C[] = "mametch_item_attack.dat";
const char lbl_8031B644[] = "mametch_jump.dat";
const char lbl_8031B658[] = "mametch_item_jump.dat";
const char lbl_8031B670[] = "mametch_item_b_attack.dat";
const char lbl_8031B68C[] = "mametch_turbo_lv1.dat";
const char lbl_8031B6A4[] = "mametch_item_turbo_lv1.dat";
const char lbl_8031B6C0[] = "mametch_brake.dat";
const char lbl_8031B6D4[] = "mametch_item_brake.dat";
const char lbl_8031B6EC[] = "mametch_surprise.dat";
const char lbl_8031B704[] = "mametch_item_surprise.dat";
const char lbl_8031B720[] = "mametch_joy.dat";
const char lbl_8031B730[] = "mametch_absorption.dat";
const char lbl_8031B748[] = "mametch_bazooka.dat";
const char lbl_8031B75C[] = "mametch_hammer.dat";
const char lbl_8031B770[] = "mametch_take.dat";
const char lbl_8031B784[] = "mametch_win.dat";
const char lbl_8031B794[] = "mametch_loses.dat";
const char lbl_8031B7A8[] = "mametch_hit_thunder.dat";
#pragma force_active reset
/* --- .rodata 0x8031B7C0..0x8032061C (moved from RaceData_8009BEF4) --- */
extern char lbl_806D3624[];
extern char lbl_806D362C[];
extern char lbl_806D3634[];
extern char lbl_806D363C[];
extern char lbl_806D3644[];
extern char lbl_806D364C[];
extern char lbl_806D3654[];
extern char lbl_806D365C[];
extern char lbl_806D3664[];
extern char lbl_806D366C[];
extern char lbl_806D3674[];
extern char lbl_806D367C[];
extern char lbl_806D3684[];
extern char lbl_806D368C[];
extern char lbl_806D3694[];
extern char lbl_806D369C[];
extern char lbl_806D36A4[];
extern char lbl_806D36AC[];
extern char lbl_806D36B4[];
extern char lbl_806D36BC[];
extern char lbl_806D36C4[];
extern char lbl_806D36CC[];
extern char lbl_806D36D4[];
extern char lbl_806D36DC[];
extern char lbl_806D36E4[];
extern char lbl_806D36EC[];
extern char lbl_806D36F4[];
extern char lbl_806D36FC[];
extern char lbl_806D3704[];
extern char lbl_806D370C[];
extern char lbl_806D3714[];
extern char lbl_806D371C[];
extern char lbl_806D3724[];
extern char lbl_806D372C[];
extern char lbl_806D3734[];
extern char lbl_806D373C[];
extern char lbl_806D3744[];
extern char lbl_806D374C[];
extern char lbl_806D3754[];
extern char lbl_806D375C[];
extern char lbl_806D3764[];
extern char lbl_806D376C[];
extern char lbl_806D3774[];
extern char lbl_806D377C[];
extern char lbl_806D3784[];
extern char lbl_806D378C[];
extern char lbl_806D3794[];
extern char lbl_806D379C[];
extern char lbl_806D37A4[];
extern char lbl_806D37AC[];
extern char lbl_806D37B4[];
extern char lbl_806D37BC[];
extern char lbl_806D37C4[];
extern char lbl_806D37CC[];
extern char lbl_806D37D4[];
extern char lbl_806D37DC[];
extern char lbl_806D37E4[];
extern char lbl_806D37EC[];
extern char lbl_806D37F4[];
extern char lbl_806D37FC[];
extern char lbl_806D3804[];
extern char lbl_806D380C[];
extern char lbl_806D3814[];
extern char lbl_806D381C[];
extern char lbl_806D3824[];
extern char lbl_806D382C[];
extern char lbl_806D3834[];
extern char lbl_806D383C[];
extern char lbl_806D3844[];
extern char lbl_806D384C[];
extern char lbl_806D3854[];
extern char lbl_806D385C[];
extern char lbl_806D3864[];
extern char lbl_806D386C[];
extern char lbl_806D3874[];
extern char lbl_806D387C[];
extern char lbl_806D3884[];
extern char lbl_806D388C[];
extern char lbl_806D3894[];
extern char lbl_806D389C[];
extern char lbl_806D38A4[];
extern char lbl_806D38AC[];
extern char lbl_806D38B4[];
extern char lbl_806D38BC[];
extern char lbl_806D38C4[];
extern char lbl_806D38CC[];
extern char lbl_806D38D4[];
extern char lbl_806D38DC[];
extern char lbl_806D38E4[];
extern char lbl_806D38EC[];
extern char lbl_806D38F4[];
extern char lbl_806D38FC[];
extern char lbl_806D3904[];
extern char lbl_806D390C[];
extern char lbl_806D3914[];
extern char lbl_806D391C[];
extern char lbl_806D3924[];
extern char lbl_806D392C[];
extern char lbl_806D3934[];
extern char lbl_806D393C[];
extern char lbl_806D3944[];
extern char lbl_806D394C[];
extern char lbl_806D3954[];
extern char lbl_806D395C[];
extern char lbl_806D3964[];
extern char lbl_806D396C[];
extern char lbl_806D3974[];
extern char lbl_806D397C[];
extern char lbl_806D3984[];
extern char lbl_806D398C[];
extern char lbl_806D3994[];
extern char lbl_806D399C[];
extern char lbl_806D39A4[];
extern char lbl_806D39AC[];
extern char lbl_806D39B4[];
extern char lbl_806D39BC[];
extern char lbl_806D39C4[];
extern char lbl_806D39CC[];
extern char lbl_806D39D4[];
extern char lbl_806D39DC[];
extern char lbl_806D39E4[];
extern char lbl_806D39EC[];
extern char lbl_806D39F4[];
extern char lbl_806D39FC[];
extern char lbl_806D3A04[];
extern char lbl_806D3A0C[];
extern char lbl_806D3A14[];
extern char lbl_806D3A1C[];
extern char lbl_806D3A24[];
extern char lbl_806D3A2C[];
extern char lbl_806D3A34[];
extern char lbl_806D3A3C[];
extern char lbl_806D3A44[];
extern char lbl_806D3A4C[];
extern char lbl_806D3A54[];
extern char lbl_806D3A5C[];
extern char lbl_806D3A64[];
extern char lbl_806D3A6C[];
extern char lbl_806D3A74[];
extern char lbl_806D3A7C[];
extern char lbl_806D3A84[];
extern char lbl_806D3A8C[];
extern char lbl_806D3A94[];
extern char lbl_806D3A9C[];
extern char lbl_806D3AA4[];
extern char lbl_806D3AAC[];
extern char lbl_806D3AB4[];
extern char lbl_806D3ABC[];
extern char lbl_806D3AC4[];
extern char lbl_806D3ACC[];
extern char lbl_806D3AD4[];
extern char lbl_806D3ADC[];
extern char lbl_806D3AE4[];
extern char lbl_806D3AEC[];
extern char lbl_806D3AF4[];
extern char lbl_806D3AFC[];
extern char lbl_806D3B04[];
extern char lbl_806D3B0C[];
extern char lbl_806D3B14[];
extern char lbl_806D3B1C[];
extern char lbl_806D3B24[];
extern char lbl_806D3B2C[];
extern char lbl_806D3B34[];
extern char lbl_806D3B3C[];
extern char lbl_806D3B44[];
extern char lbl_806D3B4C[];
extern char lbl_806D3B54[];
extern char lbl_806D3B5C[];
extern char lbl_806D3B64[];
extern char lbl_806D3B6C[];
extern char lbl_806D3B74[];
extern char lbl_806D3B7C[];
extern char lbl_806D3B84[];
extern char lbl_806D3B8C[];
extern char lbl_806D3B94[];
extern char lbl_806D3B9C[];
extern char lbl_806D3BA4[];
extern char lbl_806D3BAC[];
extern char lbl_806D3BB4[];
extern char lbl_806D3BBC[];
extern char lbl_806D3BC4[];
extern char lbl_806D3BCC[];
extern char lbl_806D3BD4[];
extern char lbl_806D3BDC[];
extern char lbl_806D3BE4[];
extern char lbl_806D3BEC[];
extern char lbl_806D3BF4[];
extern char lbl_806D3BFC[];
extern char lbl_806D3C04[];
extern char lbl_806D3C0C[];
extern char lbl_806D3C14[];
extern char lbl_806D3C1C[];
extern char lbl_806D3C24[];
extern char lbl_806D3C2C[];
extern char lbl_806D3C34[];
extern char lbl_806D3C3C[];
extern char lbl_806D3C44[];
extern char lbl_806D3C4C[];
extern char lbl_806D3C54[];
extern char lbl_806D3C5C[];
extern char lbl_806D3C64[];
extern char lbl_806D3C6C[];
extern char lbl_806D3C74[];
extern char lbl_806D3C7C[];
extern char lbl_806D3C84[];
extern char lbl_806D3C8C[];
extern char lbl_806D3C94[];
extern char lbl_806D3C9C[];
extern char lbl_806D3CA4[];
extern char lbl_806D3CAC[];
extern char lbl_806D3CB4[];
extern char lbl_806D3CBC[];
extern char lbl_806D3CC4[];
extern char lbl_806D3CCC[];
extern char lbl_806D3CD4[];
extern char lbl_806D3CDC[];
extern char lbl_806D3CE4[];
extern char lbl_806D3CEC[];
extern char lbl_806D3CF4[];
extern char lbl_806D3CFC[];
extern char lbl_806D3D04[];
extern char lbl_806D3D0C[];
extern char lbl_806D3D14[];
extern char lbl_806D3D1C[];
extern char lbl_806D3D24[];
extern char lbl_806D3D2C[];
extern char lbl_806D3D34[];
extern char lbl_806D3D3C[];
extern char lbl_806D3D44[];
extern char lbl_806D3D4C[];
extern char lbl_806D3D54[];
extern char lbl_806D3D5C[];
extern char lbl_806D3D64[];
extern char lbl_806D3D6C[];
extern char lbl_806D3D74[];
extern char lbl_806D3D7C[];
extern char lbl_806D3D84[];
extern char lbl_806D3D8C[];
extern char lbl_806D3D94[];
extern char lbl_806D3D9C[];
extern char lbl_806D3DA4[];
extern char lbl_806D3DAC[];
extern char lbl_806D3DB4[];
extern char lbl_806D3DBC[];
extern char lbl_806D3DC4[];
extern char lbl_806D3DCC[];
extern char lbl_806D3DD4[];
extern char lbl_806D3DDC[];
extern char lbl_806D3DE4[];
extern char lbl_806D3DEC[];
extern char lbl_806D3DF4[];
extern char lbl_806D3DFC[];
extern char lbl_806D3E04[];
extern char lbl_806D3E0C[];
extern char lbl_806D3E14[];
extern char lbl_806D3E1C[];
extern char lbl_806D3E24[];
extern char lbl_806D3E2C[];
extern char lbl_806D3E34[];
extern char lbl_806D3E3C[];
extern char lbl_806D3E44[];
extern char lbl_806D3E4C[];
extern char lbl_806D3E54[];
extern char lbl_806D3E5C[];
extern char lbl_806D3E64[];
extern char lbl_806D3E6C[];
extern char lbl_806D3E74[];
extern char lbl_806D3E7C[];
extern char lbl_806D3E84[];
extern char lbl_806D3E8C[];
extern char lbl_806D3E94[];
extern char lbl_806D3E9C[];
extern char lbl_806D3EA4[];
extern char lbl_806D3EAC[];
extern char lbl_806D3EB4[];
extern char lbl_806D3EBC[];
extern char lbl_806D3EC4[];
extern char lbl_806D3ECC[];
extern char lbl_806D3ED4[];
extern char lbl_806D3EDC[];
extern char lbl_806D3EE4[];
extern char lbl_806D3EEC[];
extern char lbl_806D3EF4[];
extern char lbl_806D3EFC[];
extern char lbl_806D3F04[];
extern char lbl_806D3F0C[];
extern char lbl_806D3F14[];
extern char lbl_806D3F1C[];
extern char lbl_806D3F24[];
extern char lbl_806D3F2C[];
extern char lbl_806D3F34[];
extern char lbl_806D3F3C[];
extern char lbl_806D3F44[];
extern char lbl_806D3F4C[];
extern char lbl_806D3F54[];
extern char lbl_806D3F5C[];
extern char lbl_806D3F64[];
extern char lbl_806D3F6C[];
extern char lbl_806D3F74[];
extern char lbl_806D3F7C[];
extern char lbl_806D3F84[];
extern char lbl_806D3F8C[];
extern char lbl_806D3F94[];
extern char lbl_806D3F9C[];
extern char lbl_806D3FA4[];
extern char lbl_806D3FAC[];
extern char lbl_806D3FB4[];
extern char lbl_806D3FBC[];
extern char lbl_806D3FC4[];
extern char lbl_806D3FCC[];
extern char lbl_806D3FD4[];
extern char lbl_806D3FDC[];
extern char lbl_806D3FE4[];
extern char lbl_806D3FEC[];
extern char lbl_806D3FF4[];
extern char lbl_806D3FFC[];
extern char lbl_806D4004[];
extern char lbl_806D400C[];
extern char lbl_806D4014[];
extern char lbl_806D401C[];
extern char lbl_806D4024[];
extern char lbl_806D402C[];
extern char lbl_806D4034[];
extern char lbl_806D403C[];
extern char lbl_806D4044[];
extern char lbl_806D404C[];
extern char lbl_806D4054[];
extern char lbl_806D405C[];
extern char lbl_806D4064[];
extern char lbl_806D406C[];
extern char lbl_806D4074[];
extern char lbl_806D407C[];
extern char lbl_806D4084[];
extern char lbl_806D408C[];
extern char lbl_806D4094[];
extern char lbl_806D409C[];
extern char lbl_806D40A4[];
extern char lbl_806D40AC[];
extern char lbl_806D40B4[];
extern char lbl_806D40BC[];
extern char lbl_806D40C4[];
extern char lbl_806D40CC[];
extern char lbl_806D40D4[];
extern char lbl_806D40DC[];
extern char lbl_806D40E4[];
extern char lbl_806D40EC[];
extern char lbl_806D40F4[];
extern char lbl_806D40FC[];
extern char lbl_806D4104[];
extern char lbl_806D410C[];
extern char lbl_806D4114[];
extern char lbl_806D411C[];
extern char lbl_806D4124[];
extern char lbl_806D412C[];
extern char lbl_806D4134[];
extern char lbl_806D413C[];
extern char lbl_806D4144[];
extern char lbl_806D414C[];
extern char lbl_806D4154[];
extern char lbl_806D415C[];
extern char lbl_806D4164[];
extern char lbl_806D416C[];
extern char lbl_806D4174[];
extern char lbl_806D417C[];
extern char lbl_806D4184[];
extern char lbl_806D418C[];
extern char lbl_806D4194[];
extern char lbl_806D419C[];
extern char lbl_806D41A4[];
extern char lbl_806D41AC[];
extern char lbl_806D41B4[];
extern char lbl_806D41BC[];
extern char lbl_806D41C4[];
extern char lbl_806D41CC[];
extern char lbl_806D41D4[];
extern char lbl_806D41DC[];
extern char lbl_806D41E4[];
extern char lbl_806D41EC[];
extern char lbl_806D41F4[];
extern char lbl_806D41FC[];
extern char lbl_806D4204[];
extern char lbl_806D420C[];
extern char lbl_806D4214[];
extern char lbl_806D421C[];
extern char lbl_806D4224[];
extern char lbl_806D422C[];
extern char lbl_806D4234[];
extern char lbl_806D423C[];
extern char lbl_806D4244[];
extern char lbl_806D424C[];
extern char lbl_806D4254[];
extern char lbl_806D425C[];
extern char lbl_806D4264[];
extern char lbl_806D426C[];
extern char lbl_806D4274[];
extern char lbl_806D427C[];
extern char lbl_806D4284[];
extern char lbl_806D428C[];
extern char lbl_806D4294[];
extern char lbl_806D429C[];
extern char lbl_806D42A4[];
extern char lbl_806D42AC[];
extern char lbl_806D42B4[];
extern char lbl_806D42BC[];
extern char lbl_806D42C4[];
extern char lbl_806D42CC[];
extern char lbl_806D42D4[];
extern char lbl_806D42DC[];
extern char lbl_806D42E4[];
extern char lbl_806D42EC[];
extern char lbl_806D42F4[];
extern char lbl_806D42FC[];
extern char lbl_806D4304[];
extern char lbl_806D430C[];
extern char lbl_806D4314[];
extern char lbl_806D431C[];
extern char lbl_806D4324[];
extern char lbl_806D432C[];
extern char lbl_806D4334[];
extern char lbl_806D433C[];
extern char lbl_806D4344[];
extern char lbl_806D434C[];
extern char lbl_806D4354[];
extern char lbl_806D435C[];
extern char lbl_806D4364[];
extern char lbl_806D436C[];
extern char lbl_806D4374[];
extern char lbl_806D437C[];
extern char lbl_806D4384[];
extern char lbl_806D438C[];
extern char lbl_806D4394[];
extern char lbl_806D439C[];
extern char lbl_806D43A4[];
extern char lbl_806D43AC[];
extern char lbl_806D43B4[];
extern char lbl_806D43BC[];
extern char lbl_806D43C4[];
extern char lbl_806D43CC[];
extern char lbl_806D43D4[];
extern char lbl_806D43DC[];
extern char lbl_806D43E4[];
extern char lbl_806D43EC[];
extern char lbl_806D43F4[];
extern char lbl_806D43FC[];
extern char lbl_806D4404[];
extern char lbl_806D440C[];
extern char lbl_806D4414[];
extern char lbl_806D441C[];
extern char lbl_806D4424[];
extern char lbl_806D442C[];
extern char lbl_806D4434[];
extern char lbl_806D443C[];
extern char lbl_806D4444[];
extern char lbl_806D444C[];
extern char lbl_806D4454[];
extern char lbl_806D445C[];
extern char lbl_806D4464[];
extern char lbl_806D446C[];
extern char lbl_806D4474[];
extern char lbl_806D447C[];
extern char lbl_806D4484[];
extern char lbl_806D448C[];
extern char lbl_806D4494[];
extern char lbl_806D449C[];
extern char lbl_806D44A4[];
extern char lbl_806D44AC[];
extern char lbl_806D44B4[];
extern char lbl_806D44BC[];
extern char lbl_806D44C4[];
extern char lbl_806D44CC[];
extern char lbl_806D44D4[];
extern char lbl_806D44DC[];
extern char lbl_806D44E4[];
extern char lbl_806D44EC[];
extern char lbl_806D44F4[];
extern char lbl_806D44FC[];
extern char lbl_806D4504[];
extern char lbl_806D450C[];
extern char lbl_806D4514[];
extern char lbl_806D451C[];
extern char lbl_806D4524[];
extern char lbl_806D452C[];
extern char lbl_806D4534[];
extern char lbl_806D453C[];
extern char lbl_806D4544[];
extern char lbl_806D454C[];
extern char lbl_806D4554[];
extern char lbl_806D455C[];
extern char lbl_806D4564[];
extern char lbl_806D456C[];
extern char lbl_806D4574[];
extern char lbl_806D457C[];
extern char lbl_806D4584[];
extern char lbl_806D458C[];
extern char lbl_806D4594[];
extern char lbl_806D459C[];
extern char lbl_806D45A4[];
extern char lbl_806D45AC[];
extern char lbl_806D45B4[];
extern char lbl_806D45BC[];
extern char lbl_806D45C4[];
extern char lbl_806D45CC[];
extern char lbl_806D45D4[];
extern char lbl_806D45DC[];
extern char lbl_806D45E4[];
extern char lbl_806D45EC[];
extern char lbl_806D45F4[];
extern char lbl_806D45FC[];
extern char lbl_806D4604[];
extern char lbl_806D460C[];
extern char lbl_806D4614[];
extern char lbl_806D461C[];
extern char lbl_806D4624[];
extern char lbl_806D462C[];
extern char lbl_806D4634[];
extern char lbl_806D463C[];
extern char lbl_806D4644[];
extern char lbl_806D464C[];
extern char lbl_806D4654[];
extern char lbl_806D465C[];
extern char lbl_806D4664[];
extern char lbl_806D466C[];
extern char lbl_806D4674[];
extern char lbl_806D467C[];
extern char lbl_806D4684[];
extern char lbl_806D468C[];
extern char lbl_806D4694[];
extern char lbl_806D469C[];
extern char lbl_806D46A4[];
extern char lbl_806D46AC[];
extern char lbl_806D46B4[];
#pragma force_active on
const char lbl_8031B7C0[] = "MARIO    ";
const char lbl_8031B7CC[] = "mario_hyouji.dat";
const char lbl_8031B7E0[] = "mario_bone_a.dat";
const char lbl_8031B7F4[] = "mario_bone_b.dat";
const char lbl_8031B808[] = "lod_mario.dat";
const char lbl_8031B818[] = "mirror_mario.dat";
const char lbl_8031B82C[] = "LUIGI    ";
const char lbl_8031B838[] = "luigi_hyouji.dat";
const char lbl_8031B84C[] = "luigi_bone_a.dat";
const char lbl_8031B860[] = "luigi_bone_b.dat";
const char lbl_8031B874[] = "lod_luigi.dat";
const char lbl_8031B884[] = "mirror_luigi.dat";
const char lbl_8031B898[] = "WARIO    ";
const char lbl_8031B8A4[] = "wario_hyouji.dat";
const char lbl_8031B8B8[] = "wario_bone_a.dat";
const char lbl_8031B8CC[] = "wario_bone_b.dat";
const char lbl_8031B8E0[] = "lod_wario.dat";
const char lbl_8031B8F0[] = "mirror_wario.dat";
const char lbl_8031B904[] = "PEACH    ";
const char lbl_8031B910[] = "peach_hyouji.dat";
const char lbl_8031B924[] = "peach_bone_a.dat";
const char lbl_8031B938[] = "peach_bone_b.dat";
const char lbl_8031B94C[] = "lod_peach.dat";
const char lbl_8031B95C[] = "mirror_peach.dat";
const char lbl_8031B970[] = "KOOPA    ";
const char lbl_8031B97C[] = "koopa_hyouji.dat";
const char lbl_8031B990[] = "koopa_bone_a.dat";
const char lbl_8031B9A4[] = "koopa_bone_b.dat";
const char lbl_8031B9B8[] = "lod_koopa.dat";
const char lbl_8031B9C8[] = "mirror_koopa.dat";
const char lbl_8031B9DC[] = "KINOPIO  ";
const char lbl_8031B9E8[] = "kinopio_hyouji.dat";
const char lbl_8031B9FC[] = "kinopio_bone_a.dat";
const char lbl_8031BA10[] = "kinopio_bone_b.dat";
const char lbl_8031BA24[] = "lod_kinopio.dat";
const char lbl_8031BA34[] = "mirror_kinopio.dat";
const char lbl_8031BA48[] = "DONKEY   ";
const char lbl_8031BA54[] = "donkey_hyouji.dat";
const char lbl_8031BA68[] = "donkey_bone_a.dat";
const char lbl_8031BA7C[] = "donkey_bone_b.dat";
const char lbl_8031BA90[] = "lod_donkey.dat";
const char lbl_8031BAA0[] = "mirror_donkey.dat";
const char lbl_8031BAB4[] = "YOSHI    ";
const char lbl_8031BAC0[] = "yoshi_hyouji.dat";
const char lbl_8031BAD4[] = "yoshi_bone_a.dat";
const char lbl_8031BAE8[] = "yoshi_bone_b.dat";
const char lbl_8031BAFC[] = "lod_yoshi.dat";
const char lbl_8031BB0C[] = "mirror_yoshi.dat";
const char lbl_8031BB20[] = "PACMAN   ";
const char lbl_8031BB2C[] = "pacman_hyouji.dat";
const char lbl_8031BB40[] = "pacman_bone_a.dat";
const char lbl_8031BB54[] = "pacman_bone_b.dat";
const char lbl_8031BB68[] = "lod_pacman.dat";
const char lbl_8031BB78[] = "mirror_pacman.dat";
const char lbl_8031BB8C[] = "MS PACMAN";
const char lbl_8031BB98[] = "mspacman_hyouji.dat";
const char lbl_8031BBAC[] = "mspacman_bone_a.dat";
const char lbl_8031BBC0[] = "mspacman_bone_b.dat";
const char lbl_8031BBD4[] = "lod_mspacman.dat";
const char lbl_8031BBE8[] = "mirror_mspacman.dat";
const char lbl_8031BBFC[] = "MONSTER  ";
const char lbl_8031BC08[] = "monster_hyouji.dat";
const char lbl_8031BC1C[] = "monster_bone_a.dat";
const char lbl_8031BC30[] = "monster_bone_b.dat";
const char lbl_8031BC44[] = "lod_monster.dat";
const char lbl_8031BC54[] = "mirror_monster.dat";
const char lbl_8031BC68[] = "WALUIGI  ";
const char lbl_8031BC74[] = "waluigi_hyouji.dat";
const char lbl_8031BC88[] = "waluigi_bone_a.dat";
const char lbl_8031BC9C[] = "waluigi_bone_b.dat";
const char lbl_8031BCB0[] = "lod_waluigi.dat";
const char lbl_8031BCC0[] = "mirror_waluigi.dat";
const char lbl_8031BCD4[] = "MAMETH   ";
const char lbl_8031BCE0[] = "mametch_hyouji.dat";
const char lbl_8031BCF4[] = "mametch_bone_a.dat";
const char lbl_8031BD08[] = "mametch_bone_b.dat";
const char lbl_8031BD1C[] = "lod_mametch.dat";
const char lbl_8031BD2C[] = "mirror_mametch.dat";
const char lbl_8031BD40[] = "NO CHARA ";
const char lbl_8031BD4C[] = "PCA_challenge.dat";
const char lbl_8031BD60[] = "PC_land_PCA_challenge_joint";
const char lbl_8031BD7C[] = "DNA_waluigi_tv.dat";
const char lbl_8031BD90[] = "DN_stadium_DNA_all_joint";
const char lbl_8031BDAC[] = "DNA_audience_all.dat";
const char lbl_8031BDC4[] = "DNA_dino_f.dat";
const char lbl_8031BDD4[] = "DNA_dino_as.dat";
const char lbl_8031BDE4[] = "DNA_dino_a_walk.dat";
const char lbl_8031BDF8[] = "DNA_spotlight_a.dat";
const char lbl_8031BE0C[] = "DNA_dino_b.dat";
const char lbl_8031BE1C[] = "DNA_airship_as.dat";
const char lbl_8031BE30[] = "MR highway";
const char lbl_8031BE3C[] = "DK jungle";
const char lbl_8031BE48[] = "WC dcity";
const char lbl_8031BE54[] = "KP castle";
const char lbl_8031BE60[] = "DN stadium";
const char lbl_8031BE6C[] = "MR highway Challenge";
const char lbl_8031BE84[] = "DK jungle Challenge";
const char lbl_8031BE98[] = "WC dcity Challenge";
const char lbl_8031BEAC[] = "PC land Challenge";
const char lbl_8031BEC0[] = "KP castle Challenge";
const char lbl_8031BED4[] = "RB road Challenge";
const char lbl_8031BEE8[] = "YI land Challenge";
const char lbl_8031BEFC[] = "DN stadium Challenge";
const char lbl_8031BF14[] = "MR_highway_share_road_joint";
const char lbl_8031BF30[] = "MR_highway_short_road_joint";
const char lbl_8031BF4C[] = "MR_highway_long_road_joint";
const char lbl_8031BF68[] = "MR_highway_short_branch_joint";
const char lbl_8031BF88[] = "MR_highway_long_branch_joint";
const char lbl_8031BFA8[] = "MR_highway_short_occlusion_joint";
const char lbl_8031BFCC[] = "MR_highway_long_occlusion_joint";
const char lbl_8031BFEC[] = "MR_highway_opac_joint";
const char lbl_8031C004[] = "MR_highway_alpha_joint";
const char lbl_8031C01C[] = "MR_highway_short_alpha_joint";
const char lbl_8031C03C[] = "MR_highway_long_alpha_joint";
const char lbl_8031C058[] = "MR_highway_short_normal_joint";
const char lbl_8031C078[] = "MR_highway_long_normal_joint";
const char lbl_8031C098[] = "MR_highway_short_reverse_joint";
const char lbl_8031C0B8[] = "MR_highway_long_reverse_joint";
const char lbl_8031C0D8[] = "DK_jungle_share_road_joint";
const char lbl_8031C0F4[] = "DK_jungle_short_road_joint";
const char lbl_8031C110[] = "DK_jungle_long_road_joint";
const char lbl_8031C12C[] = "DK_jungle_short_branch_joint";
const char lbl_8031C14C[] = "DK_jungle_long_branch_joint";
const char lbl_8031C168[] = "DK_jungle_short_occlusion_joint";
const char lbl_8031C188[] = "DK_jungle_long_occlusion_joint";
const char lbl_8031C1A8[] = "DK_jungle_opac_joint";
const char lbl_8031C1C0[] = "DK_jungle_alpha_joint";
const char lbl_8031C1D8[] = "DK_jungle_short_alpha_joint";
const char lbl_8031C1F4[] = "DK_jungle_long_alpha_joint";
const char lbl_8031C210[] = "DK_jungle_short_normal_joint";
const char lbl_8031C230[] = "DK_jungle_long_normal_joint";
const char lbl_8031C24C[] = "DK_jungle_short_reverse_joint";
const char lbl_8031C26C[] = "DK_jungle_long_reverse_joint";
const char lbl_8031C28C[] = "WC_dcity_share_road_joint";
const char lbl_8031C2A8[] = "WC_dcity_short_road_joint";
const char lbl_8031C2C4[] = "WC_dcity_long_road_joint";
const char lbl_8031C2E0[] = "WC_dcity_short_branch_joint";
const char lbl_8031C2FC[] = "WC_dcity_long_branch_joint";
const char lbl_8031C318[] = "WC_dcity_short_occlusion_joint";
const char lbl_8031C338[] = "WC_dcity_long_occlusion_joint";
const char lbl_8031C358[] = "WC_dcity_opac_joint";
const char lbl_8031C36C[] = "WC_dcity_alpha_joint";
const char lbl_8031C384[] = "WC_dcity_short_alpha_joint";
const char lbl_8031C3A0[] = "WC_dcity_long_alpha_joint";
const char lbl_8031C3BC[] = "WC_dcity_short_normal_joint";
const char lbl_8031C3D8[] = "WC_dcity_long_normal_joint";
const char lbl_8031C3F4[] = "WC_dcity_short_reverse_joint";
const char lbl_8031C414[] = "WC_dcity_long_reverse_joint";
const char lbl_8031C430[] = "PC_land_share_road_joint";
const char lbl_8031C44C[] = "PC_land_short_road_joint";
const char lbl_8031C468[] = "PC_land_long_road_joint";
const char lbl_8031C480[] = "PC_land_short_branch_joint";
const char lbl_8031C49C[] = "PC_land_long_branch_joint";
const char lbl_8031C4B8[] = "PC_land_short_occlusion_joint";
const char lbl_8031C4D8[] = "PC_land_long_occlusion_joint";
const char lbl_8031C4F8[] = "PC_land_opac_joint";
const char lbl_8031C50C[] = "PC_land_alpha_joint";
const char lbl_8031C520[] = "PC_land_short_alpha_joint";
const char lbl_8031C53C[] = "PC_land_long_alpha_joint";
const char lbl_8031C558[] = "PC_land_short_normal_joint";
const char lbl_8031C574[] = "PC_land_long_normal_joint";
const char lbl_8031C590[] = "PC_land_short_reverse_joint";
const char lbl_8031C5AC[] = "PC_land_long_reverse_joint";
const char lbl_8031C5C8[] = "KP_castle_share_road_joint";
const char lbl_8031C5E4[] = "KP_castle_short_road_joint";
const char lbl_8031C600[] = "KP_castle_long_road_joint";
const char lbl_8031C61C[] = "KP_castle_short_branch_joint";
const char lbl_8031C63C[] = "KP_castle_long_branch_joint";
const char lbl_8031C658[] = "KP_castle_short_occlusion_joint";
const char lbl_8031C678[] = "KP_castle_long_occlusion_joint";
const char lbl_8031C698[] = "KP_castle_opac_joint";
const char lbl_8031C6B0[] = "KP_castle_alpha_joint";
const char lbl_8031C6C8[] = "KP_castle_short_alpha_joint";
const char lbl_8031C6E4[] = "KP_castle_long_alpha_joint";
const char lbl_8031C700[] = "KP_castle_nofog_joint";
const char lbl_8031C718[] = "KP_castle_short_normal_joint";
const char lbl_8031C738[] = "KP_castle_long_normal_joint";
const char lbl_8031C754[] = "KP_castle_short_reverse_joint";
const char lbl_8031C774[] = "KP_castle_long_reverse_joint";
const char lbl_8031C794[] = "RB_road_share_road_joint";
const char lbl_8031C7B0[] = "RB_road_short_road_joint";
const char lbl_8031C7CC[] = "RB_road_long_road_joint";
const char lbl_8031C7E4[] = "RB_road_short_branch_joint";
const char lbl_8031C800[] = "RB_road_long_branch_joint";
const char lbl_8031C81C[] = "RB_road_short_occlusion_joint";
const char lbl_8031C83C[] = "RB_road_long_occlusion_joint";
const char lbl_8031C85C[] = "RB_road_opac_joint";
const char lbl_8031C870[] = "RB_road_alpha_joint";
const char lbl_8031C884[] = "RB_road_short_alpha_joint";
const char lbl_8031C8A0[] = "RB_road_long_alpha_joint";
const char lbl_8031C8BC[] = "RB_road_short_normal_joint";
const char lbl_8031C8D8[] = "RB_road_long_normal_joint";
const char lbl_8031C8F4[] = "RB_road_short_reverse_joint";
const char lbl_8031C910[] = "RB_road_long_reverse_joint";
const char lbl_8031C92C[] = "YI_land_share_road_joint";
const char lbl_8031C948[] = "YI_land_short_road_joint";
const char lbl_8031C964[] = "YI_land_long_road_joint";
const char lbl_8031C97C[] = "YI_land_short_branch_joint";
const char lbl_8031C998[] = "YI_land_long_branch_joint";
const char lbl_8031C9B4[] = "YI_land_short_occlusion_joint";
const char lbl_8031C9D4[] = "YI_land_long_occlusion_joint";
const char lbl_8031C9F4[] = "YI_land_opac_joint";
const char lbl_8031CA08[] = "YI_land_alpha_joint";
const char lbl_8031CA1C[] = "YI_land_short_alpha_joint";
const char lbl_8031CA38[] = "YI_land_long_alpha_joint";
const char lbl_8031CA54[] = "YI_land_short_normal_joint";
const char lbl_8031CA70[] = "YI_land_long_normal_joint";
const char lbl_8031CA8C[] = "YI_land_short_reverse_joint";
const char lbl_8031CAA8[] = "YI_land_long_reverse_joint";
const char lbl_8031CAC4[] = "DN_stadium_share_road_joint";
const char lbl_8031CAE0[] = "DN_stadium_short_road_joint";
const char lbl_8031CAFC[] = "DN_stadium_long_road_joint";
const char lbl_8031CB18[] = "DN_stadium_short_branch_joint";
const char lbl_8031CB38[] = "DN_stadium_long_branch_joint";
const char lbl_8031CB58[] = "DN_stadium_short_occlusion_joint";
const char lbl_8031CB7C[] = "DN_stadium_long_occlusion_joint";
const char lbl_8031CB9C[] = "DN_stadium_opac_joint";
const char lbl_8031CBB4[] = "DN_stadium_alpha_joint";
const char lbl_8031CBCC[] = "DN_stadium_short_alpha_joint";
const char lbl_8031CBEC[] = "DN_stadium_long_alpha_joint";
const char lbl_8031CC08[] = "DN_stadium_short_normal_joint";
const char lbl_8031CC28[] = "DN_stadium_long_normal_joint";
const char lbl_8031CC48[] = "DN_stadium_short_reverse_joint";
const char lbl_8031CC68[] = "DN_stadium_long_reverse_joint";
const char lbl_8031CC88[] = "poihana_b.dat";
const char lbl_8031CC98[] = "test_course_poihana_b_joint";
const char lbl_8031CCB4[] = "poihana_r.dat";
const char lbl_8031CCC4[] = "test_course_poihana_r_joint";
const char lbl_8031CCE0[] = "p_flower.dat";
const char lbl_8031CCF0[] = "test_course_p_flower_joint";
const char lbl_8031CD0C[] = "kinopio_byebye.dat";
const char lbl_8031CD20[] = "test_course_kinopio_byebye_joint";
const char lbl_8031CD44[] = "test_course_kinopio_jump_joint";
const char lbl_8031CD64[] = "kinopio_sit.dat";
const char lbl_8031CD74[] = "test_course_kinopio_sit_joint";
const char lbl_8031CD94[] = "test_course_f_ship.dat";
const char lbl_8031CDAC[] = "test_course_f_ship_joint";
const char lbl_8031CDC8[] = "test_course_start_gate.dat";
const char lbl_8031CDE4[] = "test_course_start_gate_joint";
const char lbl_8031CE04[] = "test_course_coconut.dat";
const char lbl_8031CE1C[] = "test_course_coconut_joint";
const char lbl_8031CE38[] = "test : short";
const char lbl_8031CE48[] = "test_course_road.dat";
const char lbl_8031CE60[] = "test : long ";
const char lbl_8031CE70[] = "mr_highway_long_Auto.bin";
const char lbl_8031CE8C[] = "mr_highway_long_Auto_R.bin";
const char lbl_8031CEA8[] = "MR_highway : short";
const char lbl_8031CEBC[] = "MRA_s_day.dat";
const char lbl_8031CECC[] = "MRA_s_eve.dat";
const char lbl_8031CEDC[] = "MRA_s_night.dat";
const char lbl_8031CEEC[] = "mr_highway_short_Auto.bin";
const char lbl_8031CF08[] = "MR_highway_short_A.dat";
const char lbl_8031CF20[] = "MR_highway_short_B.dat";
const char lbl_8031CF38[] = "MR_highway_short_C.dat";
const char lbl_8031CF50[] = "mr_highway_short.bin";
const char lbl_8031CF68[] = "mr_highway_short_Auto_R.bin";
const char lbl_8031CF84[] = "MR_highway_shade_s.dat";
const char lbl_8031CF9C[] = "MR_highway_shade_bs.dat";
const char lbl_8031CFB4[] = "MR_highway_shade_cs.dat";
const char lbl_8031CFCC[] = "MR_highway : long ";
const char lbl_8031CFE0[] = "MRA_l_day.dat";
const char lbl_8031CFF0[] = "MRA_l_eve.dat";
const char lbl_8031D000[] = "MRA_l_night.dat";
const char lbl_8031D010[] = "MR_highway_ground_C.dat";
const char lbl_8031D028[] = "MR_highway_long_A.dat";
const char lbl_8031D040[] = "MR_highway_long_B.dat";
const char lbl_8031D058[] = "MR_highway_long_C.dat";
const char lbl_8031D070[] = "mr_highway_long.bin";
const char lbl_8031D084[] = "MR_highway_shade_l.dat";
const char lbl_8031D09C[] = "MR_highway_shade_bl.dat";
const char lbl_8031D0B4[] = "MR_highway_shade_cl.dat";
const char lbl_8031D0CC[] = "DK_jungle : short";
const char lbl_8031D0E0[] = "DKA_s_day.dat";
const char lbl_8031D0F0[] = "DKA_s_eve.dat";
const char lbl_8031D100[] = "DKA_s_night.dat";
const char lbl_8031D110[] = "DK_jungle_short_C.dat";
const char lbl_8031D128[] = "dk_jungle_short_Auto.bin";
const char lbl_8031D144[] = "DK_jungle_short_A.dat";
const char lbl_8031D15C[] = "DK_jungle_short_B.dat";
const char lbl_8031D174[] = "dk_jungle_short.bin";
const char lbl_8031D188[] = "dk_jungle_short_Auto_R.bin";
const char lbl_8031D1A4[] = "DK_jungle : long ";
const char lbl_8031D1B8[] = "DKA_l_day.dat";
const char lbl_8031D1C8[] = "DKA_l_eve.dat";
const char lbl_8031D1D8[] = "DKA_l_night.dat";
const char lbl_8031D1E8[] = "DK_jungle_long_C.dat";
const char lbl_8031D200[] = "dk_jungle_long_Auto.bin";
const char lbl_8031D218[] = "DK_jungle_long_A.dat";
const char lbl_8031D230[] = "DK_jungle_long_B.dat";
const char lbl_8031D248[] = "dk_jungle_long.bin";
const char lbl_8031D25C[] = "dk_jungle_long_Auto_R.bin";
const char lbl_8031D278[] = "WC_dcity : short";
const char lbl_8031D28C[] = "WA_AS.dat";
const char lbl_8031D298[] = "WA_BS.dat";
const char lbl_8031D2A4[] = "WA_CS.dat";
const char lbl_8031D2B0[] = "wc_dcity_short_Auto.bin";
const char lbl_8031D2C8[] = "WC_dcity_short_A.dat";
const char lbl_8031D2E0[] = "WC_dcity_short_B.dat";
const char lbl_8031D2F8[] = "WC_dcity_short_C.dat";
const char lbl_8031D310[] = "wc_dcity_short.bin";
const char lbl_8031D324[] = "wc_dcity_short_Auto_R.bin";
const char lbl_8031D340[] = "WC_dcity_shade_s.dat";
const char lbl_8031D358[] = "WC_dcity : long ";
const char lbl_8031D36C[] = "wc_dcity_long_Auto.bin";
const char lbl_8031D384[] = "WC_dcity_long_A.dat";
const char lbl_8031D398[] = "WC_dcity_long_B.dat";
const char lbl_8031D3AC[] = "WC_dcity_long_C.dat";
const char lbl_8031D3C0[] = "wc_dcity_long.bin";
const char lbl_8031D3D4[] = "wc_dcity_long_Auto_R.bin";
const char lbl_8031D3F0[] = "WC_dcity_shade_l.dat";
const char lbl_8031D408[] = "PC_land : short";
const char lbl_8031D418[] = "PCL_s_day.dat";
const char lbl_8031D428[] = "pc_land_short_Auto.bin";
const char lbl_8031D440[] = "PC_land_short_a.dat";
const char lbl_8031D454[] = "pc_land_short.bin";
const char lbl_8031D468[] = "pc_land_short_a.bin";
const char lbl_8031D47C[] = "pc_land_short_b.bin";
const char lbl_8031D490[] = "pc_land_short_c.bin";
const char lbl_8031D4A4[] = "pc_land_short_Auto_R.bin";
const char lbl_8031D4C0[] = "PC_land : long ";
const char lbl_8031D4D0[] = "PCL_l_day.dat";
const char lbl_8031D4E0[] = "pc_land_long_Auto.bin";
const char lbl_8031D4F8[] = "PC_land_long_a.dat";
const char lbl_8031D50C[] = "pc_land_long.bin";
const char lbl_8031D520[] = "pc_land_long_a.bin";
const char lbl_8031D534[] = "pc_land_long_b.bin";
const char lbl_8031D548[] = "pc_land_long_c.bin";
const char lbl_8031D55C[] = "pc_land_long_Auto_R.bin";
const char lbl_8031D574[] = "KP_castle : short";
const char lbl_8031D588[] = "KPC_s_day.dat";
const char lbl_8031D598[] = "KP_castle_ground_A.dat";
const char lbl_8031D5B0[] = "kp_castle_short_Auto.bin";
const char lbl_8031D5CC[] = "kp_castle_short.bin";
const char lbl_8031D5E0[] = "kp_castle_short_Auto_R.bin";
const char lbl_8031D5FC[] = "KP_castle : long ";
const char lbl_8031D610[] = "KPC_l_day.dat";
const char lbl_8031D620[] = "KP_castle_ground_B.dat";
const char lbl_8031D638[] = "kp_castle_long_Auto.bin";
const char lbl_8031D650[] = "kp_castle_long.bin";
const char lbl_8031D664[] = "kp_castle_long_Auto_R.bin";
const char lbl_8031D680[] = "RB_road : short";
const char lbl_8031D690[] = "rb_light_A.dat";
const char lbl_8031D6A0[] = "rb_light_B.dat";
const char lbl_8031D6B0[] = "rb_light_C.dat";
const char lbl_8031D6C0[] = "rb_light_D.dat";
const char lbl_8031D6D0[] = "rb_road_short_Auto.bin";
const char lbl_8031D6E8[] = "RB_road_short_a.dat";
const char lbl_8031D6FC[] = "RB_road_short_b.dat";
const char lbl_8031D710[] = "RB_road_short_c.dat";
const char lbl_8031D724[] = "RB_road_short_d.dat";
const char lbl_8031D738[] = "rb_road_short.bin";
const char lbl_8031D74C[] = "rb_road_short_Auto_R.bin";
const char lbl_8031D768[] = "RB_road : long ";
const char lbl_8031D778[] = "rb_road_long_Auto.bin";
const char lbl_8031D790[] = "RB_road_long_a.dat";
const char lbl_8031D7A4[] = "RB_road_long_b.dat";
const char lbl_8031D7B8[] = "RB_road_long_c.dat";
const char lbl_8031D7CC[] = "RB_road_long_d.dat";
const char lbl_8031D7E0[] = "rb_road_long.bin";
const char lbl_8031D7F4[] = "rb_road_long_Auto_R.bin";
const char lbl_8031D80C[] = "RB_road_long_a_r.dat";
const char lbl_8031D824[] = "RB_road_long_b_r.dat";
const char lbl_8031D83C[] = "RB_road_long_c_r.dat";
const char lbl_8031D854[] = "RB_road_long_d_r.dat";
const char lbl_8031D86C[] = "rb_road_long_r.bin";
const char lbl_8031D880[] = "YI_LAND : short";
const char lbl_8031D890[] = "YI_land_short_a.dat";
const char lbl_8031D8A4[] = "yi_land_short_Auto.bin";
const char lbl_8031D8BC[] = "yi_land_short.bin";
const char lbl_8031D8D0[] = "yi_land_short_Auto_R.bin";
const char lbl_8031D8EC[] = "YI_LAND : long ";
const char lbl_8031D8FC[] = "YI_land_long_a.dat";
const char lbl_8031D910[] = "yi_land_long_Auto.bin";
const char lbl_8031D928[] = "yi_land_long.bin";
const char lbl_8031D93C[] = "yi_land_long_Auto_R.bin";
const char lbl_8031D954[] = "DN_stadium : short";
const char lbl_8031D968[] = "dn_stadium_short_a.dat";
const char lbl_8031D980[] = "dn_stadium_short_Auto.bin";
const char lbl_8031D99C[] = "dn_stadium_short.bin";
const char lbl_8031D9B4[] = "dn_stadium_short_Auto_R.bin";
const char lbl_8031D9D0[] = "dn_stadium_shade_as.dat";
const char lbl_8031D9E8[] = "DN_stadium : long ";
const char lbl_8031D9FC[] = "dn_stadium_long_a.dat";
const char lbl_8031DA14[] = "dn_stadium_long_Auto.bin";
const char lbl_8031DA30[] = "dn_stadium_long.bin";
const char lbl_8031DA44[] = "dn_stadium__long.bin";
const char lbl_8031DA5C[] = "dn_stadium_long_Auto_R.bin";
const char lbl_8031DA78[] = "dn_stadium_shade_al.dat";
const char lbl_8031DA90[] = "MR_highway challenge";
const char lbl_8031DAA8[] = "MR_highway_challenge.dat";
const char lbl_8031DAC4[] = "mr_highway_challenge.bin";
const char lbl_8031DAE0[] = "DK_jungle challenge";
const char lbl_8031DAF4[] = "DK_jungle_challenge.dat";
const char lbl_8031DB0C[] = "WC_dcity challenge";
const char lbl_8031DB20[] = "WC_dcity_challenge.dat";
const char lbl_8031DB38[] = "wc_dcity_challenge.bin";
const char lbl_8031DB50[] = "PC_land challenge";
const char lbl_8031DB64[] = "PC_land_challenge.dat";
const char lbl_8031DB7C[] = "pc_land_challenge.bin";
const char lbl_8031DB94[] = "KP_castle challenge";
const char lbl_8031DBA8[] = "KP_castle_challenge.dat";
const char lbl_8031DBC0[] = "kp_castle_challenge.bin";
const char lbl_8031DBD8[] = "RB_road challenge";
const char lbl_8031DBEC[] = "rb_road_challenge.bin";
const char lbl_8031DC04[] = "YI_LAND challenge";
const char lbl_8031DC18[] = "DN_stadium challenge";
const char lbl_8031DC30[] = "dn_stadium_challenge.dat";
const char lbl_8031DC4C[] = "dn_stadium_challenge.bin";
const unsigned int NameCheck_CardName_rodata_8031DC68[3] = { TEXT_WORD(0x82, 0xA0, 0x82, 0xA2), TEXT_WORD(0x82, 0xA6, 0x82, 0xAB), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DC74[3] = { TEXT_WORD(0x82, 0xA0, 0x82, 0xA2), TEXT_WORD(0x82, 0xCC, 0x82, 0xB1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DC80[3] = { TEXT_WORD(0x82, 0xA0, 0x82, 0xAB), TEXT_WORD(0x82, 0xE0, 0x82, 0xA4), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DC8C[3] = { TEXT_WORD(0x82, 0xA0, 0x82, 0xB3), TEXT_WORD(0x82, 0xB1, 0x82, 0xA4), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DC98[3] = { TEXT_WORD(0x82, 0xA0, 0x82, 0xB5), TEXT_WORD(0x82, 0xAB, 0x82, 0xE8), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DCA4[3] = { TEXT_WORD(0x82, 0xA0, 0x82, 0xDF), TEXT_WORD(0x82, 0xB1, 0x82, 0xA4), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DCB0[3] = { TEXT_WORD(0x82, 0xA2, 0x82, 0xBD), TEXT_WORD(0x82, 0xB1, 0x82, 0xA4), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DCBC[3] = { TEXT_WORD(0x82, 0xA2, 0x82, 0xDF), TEXT_WORD(0x82, 0xAD, 0x82, 0xE7), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DCC8[3] = { TEXT_WORD(0x82, 0xA2, 0x82, 0xF1), TEXT_WORD(0x82, 0xA9, 0x82, 0xAD), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DCD4[3] = { TEXT_WORD(0x82, 0xA2, 0x82, 0xF1), TEXT_WORD(0x82, 0xAF, 0x82, 0xA2), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DCE0[3] = { TEXT_WORD(0x82, 0xA2, 0x82, 0xF1), TEXT_WORD(0x82, 0xCC, 0x82, 0xA4), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DCEC[3] = { TEXT_WORD(0x82, 0xA2, 0x82, 0xF1), TEXT_WORD(0x82, 0xCE, 0x82, 0xA2), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DCF8[3] = { TEXT_WORD(0x82, 0xA2, 0x82, 0xF1), TEXT_WORD(0x82, 0xE0, 0x82, 0xA4), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DD04[3] = { TEXT_WORD(0x82, 0xA4, 0x82, 0xB7), TEXT_WORD(0x82, 0xCC, 0x82, 0xEB), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DD10[3] = { TEXT_WORD(0x82, 0xA4, 0x82, 0xDC), TEXT_WORD(0x82, 0xB8, 0x82, 0xDF), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DD1C[3] = { TEXT_WORD(0x82, 0xA6, 0x82, 0xB7), TEXT_WORD(0x82, 0xA6, 0x82, 0xDE), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DD28[3] = { TEXT_WORD(0x82, 0xA6, 0x82, 0xBD), TEXT_WORD(0x82, 0xF1, 0x82, 0xDA), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DD34[3] = { TEXT_WORD(0x82, 0xA8, 0x82, 0xC1), TEXT_WORD(0x82, 0xCF, 0x82, 0xA2), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DD40[3] = { TEXT_WORD(0x82, 0xA8, 0x82, 0xC8), TEXT_WORD(0x82, 0xC9, 0x82, 0xA2), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DD4C[3] = { TEXT_WORD(0x82, 0xA8, 0x82, 0xC8), TEXT_WORD(0x82, 0xC9, 0x81, '['), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DD58[3] = { TEXT_WORD(0x82, 0xA8, 0x82, 0xDC), TEXT_WORD(0x82, 0xED, 0x82, 0xE8), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DD64[3] = { TEXT_WORD(0x82, 0xA8, 0x82, 0xED), TEXT_WORD(0x82, 0xA2, 0x82, 0xE2), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DD70[3] = { TEXT_WORD(0x82, 0xA8, 0x82, 0xF1), TEXT_WORD(0x82, 0xDA, 0x82, 0xA4), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DD7C[3] = { TEXT_WORD(0x82, 0xAA, 0x82, 0xA2), TEXT_WORD(0x82, 0xAB, 0x82, 0xBF), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DD88[3] = { TEXT_WORD(0x82, 0xAA, 0x82, 0xA2), TEXT_WORD(0x82, 0xB6, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DD94[3] = { TEXT_WORD(0x82, 0xAA, 0x82, 0xBF), TEXT_WORD(0x82, 0xE1, 0x82, 0xDF), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DDA0[3] = { TEXT_WORD(0x82, 0xA9, 0x82, 0xED), TEXT_WORD(0x82, 0xDA, 0x82, 0xA4), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DDAC[3] = { TEXT_WORD(0x82, 0xAA, 0x82, 0xF1), TEXT_WORD(0x82, 0xB5, 0x82, 0xE1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DDB8[3] = { TEXT_WORD(0x82, 0xAB, 0x81, '['), TEXT_WORD(0x82, 0xB9, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DDC4[3] = { TEXT_WORD(0x82, 0xAB, 0x82, 0xA9), TEXT_WORD(0x82, 0xB6, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DDD0[3] = { TEXT_WORD(0x82, 0xAB, 0x82, 0xAE), TEXT_WORD(0x82, 0xE9, 0x82, 0xA2), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DDDC[3] = { TEXT_WORD(0x82, 0xAB, 0x82, 0xAF), TEXT_WORD(0x82, 0xA2, 0x82, 0xB6), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DDE8[3] = { TEXT_WORD(0x82, 0xAB, 0x82, 0xB6), TEXT_WORD(0x82, 0xE9, 0x82, 0xB5), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DDF4[3] = { TEXT_WORD(0x82, 0xAB, 0x82, 0xBF), TEXT_WORD(0x82, 0xAA, 0x82, 0xA2), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DE00[3] = { TEXT_WORD(0x82, 0xAB, 0x82, 0xE3), TEXT_WORD(0x82, 0xA4, 0x82, 0xB6), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DE0C[3] = { TEXT_WORD(0x82, 0xAB, 0x82, 0xF1), TEXT_WORD(0x82, 0xBD, 0x82, 0xDC), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DE18[3] = { TEXT_WORD(0x82, 0xAD, 0x81, '['), TEXT_WORD(0x82, 0xE8, 0x81, '['), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DE24[3] = { TEXT_WORD(0x82, 0xAD, 0x82, 0xEB), TEXT_WORD(0x82, 0xF1, 0x82, 0xDA), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DE30[3] = { TEXT_WORD(0x82, 0xB1, 0x82, 0xA4), TEXT_WORD(0x82, 0xDC, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DE3C[3] = { TEXT_WORD(0x82, 0xB1, 0x81, '['), TEXT_WORD(0x82, 0xDC, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DE48[3] = { TEXT_WORD(0x82, 0xB1, 0x82, 0xA9), TEXT_WORD(0x82, 0xA2, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DE54[3] = { TEXT_WORD(0x82, 0xB1, 0x82, 0xC3), TEXT_WORD(0x82, 0xA9, 0x82, 0xA2), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DE60[3] = { TEXT_WORD(0x82, 0xB4, 0x81, '['), TEXT_WORD(0x82, 0xDF, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DE6C[3] = { TEXT_WORD(0x82, 0xB3, 0x82, 0xA2), TEXT_WORD(0x82, 0xCD, 0x82, 0xC4), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DE78[3] = { TEXT_WORD(0x82, 0xB3, 0x82, 0xF1), TEXT_WORD(0x82, 0xB7, 0x82, 0xAF), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DE84[3] = { TEXT_WORD(0x82, 0xB5, 0x82, 0xC8), TEXT_WORD(0x82, 0xB6, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DE90[3] = { TEXT_WORD(0x82, 0xB6, 0x82, 0xD5), TEXT_WORD(0x82, 0xB5, 0x81, '['), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DE9C[3] = { TEXT_WORD(0x82, 0xB5, 0x82, 0xE1), TEXT_WORD(0x82, 0xB9, 0x82, 0xA2), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DEA8[3] = { TEXT_WORD(0x82, 0xB6, 0x82, 0xE5), TEXT_WORD(0x82, 0xA4, 0x82, 0xD3), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DEB4[3] = { TEXT_WORD(0x82, 0xB6, 0x82, 0xE5), TEXT_WORD(0x82, 0xAF, 0x82, 0xC2), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DEC0[3] = { TEXT_WORD(0x82, 0xB6, 0x82, 0xE5), TEXT_WORD(0x82, 0xB1, 0x82, 0xA4), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DECC[3] = { TEXT_WORD(0x82, 0xB5, 0x82, 0xE5), TEXT_WORD(0x82, 0xB6, 0x82, 0xE5), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DED8[3] = { TEXT_WORD(0x82, 0xB7, 0x82, 0xA9), TEXT_WORD(0x82, 0xC6, 0x82, 0xEB), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DEE4[3] = { TEXT_WORD(0x82, 0xB7, 0x82, 0xD8), TEXT_WORD(0x82, 0xE9, 0x82, 0xDC), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DEF0[3] = { TEXT_WORD(0x82, 0xB8, 0x82, 0xE8), TEXT_WORD(0x82, 0xB9, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DEFC[3] = { TEXT_WORD(0x82, 0xB9, 0x82, 0xA2), TEXT_WORD(0x82, 0xA6, 0x82, 0xAB), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DF08[3] = { TEXT_WORD(0x82, 0xB9, 0x82, 0xA2), TEXT_WORD(0x82, 0xB1, 0x82, 0xA4), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DF14[3] = { TEXT_WORD(0x82, 0xB9, 0x82, 0xA2), TEXT_WORD(0x82, 0xCD, 0x82, 0xAD), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DF20[3] = { TEXT_WORD(0x82, 0xB9, 0x82, 0xC1), TEXT_WORD(0x82, 0xAD, 0x82, 0xB7), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DF2C[3] = { TEXT_WORD(0x82, 0xB9, 0x82, 0xF1), TEXT_WORD(0x82, 0xB6, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DF38[3] = { TEXT_WORD(0x82, 0xB9, 0x82, 0xF1), TEXT_WORD(0x82, 0xB8, 0x82, 0xE8), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DF44[3] = { TEXT_WORD(0x82, 0xBB, 0x82, 0xA4), TEXT_WORD(0x82, 0xB6, 0x82, 0xD3), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DF50[3] = { TEXT_WORD(0x82, 0xBD, 0x82, 0xB2), TEXT_WORD(0x82, 0xB3, 0x82, 0xAD), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DF5C[3] = { TEXT_WORD(0x82, 0xBD, 0x82, 0xDC), TEXT_WORD(0x82, 0xAB, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DF68[3] = { TEXT_WORD(0x82, 0xBD, 0x82, 0xE8), TEXT_WORD(0x82, 0xCE, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DF74[3] = { TEXT_WORD(0x82, 0xBE, 0x82, 0xF1), TEXT_WORD(0x82, 0xB1, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DF80[3] = { TEXT_WORD(0x82, 0xBD, 0x82, 0xF1), TEXT_WORD(0x82, 0xDB, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DF8C[3] = { TEXT_WORD(0x82, 0xBF, 0x82, 0xE5), TEXT_WORD(0x82, 0xA4, 0x82, 0xE8), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DF98[3] = { TEXT_WORD(0x82, 0xBF, 0x82, 0xF1), TEXT_WORD(0x82, 0xA9, 0x82, 0xB7), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DFA4[3] = { TEXT_WORD(0x82, 0xBF, 0x82, 0xF1), TEXT_WORD(0x82, 0xBF, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DFB0[3] = { TEXT_WORD(0x82, 0xC5, 0x82, 0xA9), TEXT_WORD(0x82, 0xBF, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DFBC[3] = { TEXT_WORD(0x82, 0xC4, 0x82, 0xF1), TEXT_WORD(0x82, 0xDA, 0x82, 0xA4), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DFC8[3] = { TEXT_WORD(0x82, 0xC7, 0x82, 0xA4), TEXT_WORD(0x82, 0xC4, 0x82, 0xA2), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DFD4[3] = { TEXT_WORD(0x82, 0xC6, 0x82, 0xA4), TEXT_WORD(0x82, 0xC8, 0x82, 0xA2), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DFE0[3] = { TEXT_WORD(0x82, 0xC7, 0x82, 0xAB), TEXT_WORD(0x82, 0xE3, 0x82, 0xBB), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DFEC[3] = { TEXT_WORD(0x82, 0xC7, 0x82, 0xAB), TEXT_WORD(0x82, 0xE3, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031DFF8[3] = { TEXT_WORD(0x82, 0xC7, 0x82, 0xDF), TEXT_WORD(0x82, 0xAD, 0x82, 0xE7), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E004[3] = { TEXT_WORD(0x82, 0xC7, 0x82, 0xE0), TEXT_WORD(0x82, 0xC1, 0x82, 0xBD), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E010[3] = { TEXT_WORD(0x82, 0xC7, 0x82, 0xE0), TEXT_WORD(0x82, 0xC1, 0x82, 0xC4), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E01C[3] = { TEXT_WORD(0x82, 0xC7, 0x82, 0xE0), TEXT_WORD(0x82, 0xC1, 0x82, 0xC6), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E028[3] = { TEXT_WORD(0x82, 0xC6, 0x82, 0xE9), TEXT_WORD(0x82, 0xA6, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E034[3] = { TEXT_WORD(0x82, 0xC8, 0x82, 0xA9), TEXT_WORD(0x82, 0xBE, 0x82, 0xB5), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E040[3] = { TEXT_WORD(0x82, 0xC8, 0x82, 0xF1), TEXT_WORD(0x82, 0xB9, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E04C[3] = { TEXT_WORD(0x82, 0xC9, 0x82, 0xB1), TEXT_WORD(0x82, 0xE6, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E058[3] = { TEXT_WORD(0x82, 0xCA, 0x82, 0xDC), TEXT_WORD(0x82, 0xC1, 0x82, 0xAB), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E064[3] = { TEXT_WORD(0x82, 0xCA, 0x82, 0xEA), TEXT_WORD(0x82, 0xCA, 0x82, 0xEA), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E070[3] = { TEXT_WORD(0x82, 0xCE, 0x82, 0x9F), TEXT_WORD(0x82, 0xAC, 0x82, 0xC8), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E07C[3] = { TEXT_WORD(0x82, 0xCE, 0x81, '['), TEXT_WORD(0x82, 0xB6, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E088[3] = { TEXT_WORD(0x82, 0xCF, 0x82, 0xA2), TEXT_WORD(0x83, 'Y', 0x83, 0x8A), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E094[3] = { TEXT_WORD(0x82, 0xCF, 0x82, 0xA2), TEXT_WORD(0x82, 0xB8, 0x82, 0xE8), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E0A0[3] = { TEXT_WORD(0x82, 0xCE, 0x82, 0xA2), TEXT_WORD(0x82, 0xC7, 0x82, 0xAD), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E0AC[3] = { TEXT_WORD(0x82, 0xCD, 0x82, 0xA2), TEXT_WORD(0x82, 0xDD, 0x82, 0xB7), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E0B8[3] = { TEXT_WORD(0x82, 0xCE, 0x82, 0xBF), TEXT_WORD(0x82, 0xE5, 0x82, 0xA4), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E0C4[3] = { TEXT_WORD(0x82, 0xCF, 0x82, 0xF1), TEXT_WORD(0x82, 0xCF, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E0D0[3] = { TEXT_WORD(0x82, 0xD1, 0x81, '['), TEXT_WORD(0x82, 0xBF, 0x82, 0xAD), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E0DC[3] = { TEXT_WORD(0x82, 0xD0, 0x82, 0xC1), TEXT_WORD(0x82, 0xAB, 0x81, '['), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E0E8[3] = { TEXT_WORD(0x82, 0xD2, 0x82, 0xF1), TEXT_WORD(0x82, 0xB3, 0x82, 0xEB), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E0F4[3] = { TEXT_WORD(0x82, 0xD3, 0x82, 0x9F), TEXT_WORD(0x82, 0xC1, 0x82, 0xAD), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E100[3] = { TEXT_WORD(0x82, 0xD3, 0x82, 0xAE), TEXT_WORD(0x82, 0xB5, 0x82, 0xE1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E10C[3] = { TEXT_WORD(0x82, 0xD4, 0x82, 0xB3), TEXT_WORD(0x82, 0xA2, 0x82, 0xAD), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E118[3] = { TEXT_WORD(0x82, 0xD4, 0x82, 0xBD), TEXT_WORD(0x82, 0xCE, 0x82, 0xB1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E124[3] = { TEXT_WORD(0x82, 0xD3, 0x82, 0xEB), TEXT_WORD(0x82, 0xA4, 0x82, 0xB6), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E130[3] = { TEXT_WORD(0x82, 0xD6, 0x82, 0xE9), TEXT_WORD(0x82, 0xD8, 0x82, 0xB7), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E13C[3] = { TEXT_WORD(0x82, 0xD6, 0x82, 0xEB), TEXT_WORD(0x82, 0xA2, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E148[3] = { TEXT_WORD(0x82, 0xD9, 0x82, 0xA4), TEXT_WORD(0x82, 0xAF, 0x82, 0xA2), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E154[3] = { TEXT_WORD(0x82, 0xD9, 0x81, '['), TEXT_WORD(0x82, 0xAF, 0x81, '['), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E160[3] = { TEXT_WORD(0x82, 0xD9, 0x82, 0xAD), TEXT_WORD(0x82, 0xB9, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E16C[3] = { TEXT_WORD(0x82, 0xDB, 0x82, 0xB1), TEXT_WORD(0x82, 0xBF, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E178[3] = { TEXT_WORD(0x82, 0xDB, 0x82, 0xB1), TEXT_WORD(0x82, 0xD8, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E184[3] = { TEXT_WORD(0x82, 0xDB, 0x82, 0xE8), TEXT_WORD(0x82, 0xB1, 0x82, 0xA4), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E190[3] = { TEXT_WORD(0x82, 0xDC, 0x82, 0xF1), TEXT_WORD(0x82, 0xB6, 0x82, 0xE9), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E19C[3] = { TEXT_WORD(0x82, 0xDD, 0x82, 0xC2), TEXT_WORD(0x82, 0xAD, 0x82, 0xBF), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E1A8[3] = { TEXT_WORD(0x82, 0xDD, 0x82, 0xC2), TEXT_WORD(0x82, 0xB1, 0x82, 0xB5), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E1B4[3] = { TEXT_WORD(0x82, 0xDF, 0x82, 0xC1), TEXT_WORD(0x82, 0xA9, 0x82, 0xBF), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E1C0[3] = { TEXT_WORD(0x82, 0xE0, 0x82, 0xA4), TEXT_WORD(0x82, 0xB6, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E1CC[3] = { TEXT_WORD(0x82, 0xE0, 0x82, 0xF1), TEXT_WORD(0x82, 0xE0, 0x82, 0xA4), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E1D8[3] = { TEXT_WORD(0x82, 0xE2, 0x82, 0xE7), TEXT_WORD(0x82, 0xB9, 0x82, 0xEB), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E1E4[3] = { TEXT_WORD(0x82, 0xE2, 0x82, 0xE8), TEXT_WORD(0x82, 0xB1, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E1F0[3] = { TEXT_WORD(0x82, 0xE2, 0x82, 0xE8), TEXT_WORD(0x82, 0xB3, 0x81, '['), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E1FC[3] = { TEXT_WORD(0x82, 0xE2, 0x82, 0xE8), TEXT_WORD(0x82, 0xBF, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E208[3] = { TEXT_WORD(0x82, 0xE2, 0x82, 0xE8), TEXT_WORD(0x82, 0xDC, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E214[3] = { TEXT_WORD(0x82, 0xE2, 0x82, 0xF1), TEXT_WORD(0x82, 0xAB, 0x81, '['), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E220[3] = { TEXT_WORD(0x82, 0xE6, 0x82, 0xA2), TEXT_WORD(0x82, 0xE6, 0x82, 0xA2), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E22C[3] = { TEXT_WORD(0x82, 0xE6, 0x82, 0xC2), TEXT_WORD(0x82, 0xA0, 0x82, 0xB5), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E238[3] = { TEXT_WORD(0x82, 0xE7, 0x82, 0xC5), TEXT_WORD(0x82, 0xA1, 0x82, 0xF1), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E244[3] = { TEXT_WORD(0x82, 0xE7, 0x82, 0xF1), TEXT_WORD(0x82, 0xB1, 0x82, 0xA4), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E250[3] = { TEXT_WORD(0x82, 0xEB, 0x82, 0xF1), TEXT_WORD(0x82, 0xCF, 0x82, 0xE8), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E25C[3] = { TEXT_WORD(0x82, 0xA0, 0x82, 0xA2), TEXT_WORD(0x82, 0xCA, 0x82, 0xB6), TEXT_WORD(0x82, 0xF1, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E268[3] = { TEXT_WORD(0x82, 0xA0, 0x82, 0xAB), TEXT_WORD(0x82, 0xDF, 0x82, 0xAD), TEXT_WORD(0x82, 0xE7, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E274[3] = { TEXT_WORD(0x82, 0xA0, 0x82, 0xE9), TEXT_WORD(0x82, 0xA9, 0x82, 0xA2), TEXT_WORD(0x82, 0xBE, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E280[3] = { TEXT_WORD(0x82, 0xA2, 0x82, 0xAB), TEXT_WORD(0x82, 0xE6, 0x82, 0xCE), TEXT_WORD(0x82, 0xA2, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E28C[3] = { TEXT_WORD(0x82, 0xA2, 0x82, 0xB9), TEXT_WORD(0x82, 0xB1, 0x82, 0xB6), TEXT_WORD(0x82, 0xAB, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E298[3] = { TEXT_WORD(0x82, 0xA2, 0x82, 0xCA), TEXT_WORD(0x82, 0xB1, 0x82, 0xEB), TEXT_WORD(0x82, 0xB5, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E2A4[3] = { TEXT_WORD(0x82, 0xA2, 0x82, 0xCA), TEXT_WORD(0x82, 0xB2, 0x82, 0xEB), TEXT_WORD(0x82, 0xB5, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E2B0[3] = { TEXT_WORD(0x82, 0xA2, 0x82, 0xCA), TEXT_WORD(0x82, 0xB6, 0x82, 0xC9), TEXT_WORD(0x82, 0xF1, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E2BC[3] = { TEXT_WORD(0x82, 0xA4, 0x82, 0xDC), TEXT_WORD(0x82, 0xCC, 0x82, 0xD9), TEXT_WORD(0x82, 0xCB, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E2C8[3] = { TEXT_WORD(0x82, 0xA6, 0x82, 0xB7), TEXT_WORD(0x82, 0xAB, 0x82, 0xE0), TEXT_WORD(0x81, '[', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E2D4[3] = { TEXT_WORD(0x82, 0xA6, 0x82, 0xD0), TEXT_WORD(0x82, 0xDF, 0x82, 0xDC), TEXT_WORD(0x82, 0xE9, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E2E0[3] = { TEXT_WORD(0x82, 0xA8, 0x82, 0xB5), TEXT_WORD(0x82, 0xE0, 0x82, 0xC7), TEXT_WORD(0x82, 0xE8, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E2EC[3] = { TEXT_WORD(0x82, 0xA8, 0x82, 0xBF), TEXT_WORD(0x82, 0xE1, 0x82, 0xAD), TEXT_WORD(0x82, 0xDD, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E2F8[3] = { TEXT_WORD(0x82, 0xA8, 0x82, 0xC8), TEXT_WORD(0x82, 0xD8, 0x82, 0xC1), TEXT_WORD(0x82, 0xC6, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E304[3] = { TEXT_WORD(0x82, 0xA9, 0x82, 0xB3), TEXT_WORD(0x82, 0xC1, 0x82, 0xA9), TEXT_WORD(0x82, 0xAB, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E310[3] = { TEXT_WORD(0x82, 0xA9, 0x82, 0xBD), TEXT_WORD(0x82, 0xC4, 0x82, 0xA8), TEXT_WORD(0x82, 0xBF, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E31C[3] = { TEXT_WORD(0x82, 0xA9, 0x82, 0xC8), TEXT_WORD(0x82, 0xC2, 0x82, 0xF1), TEXT_WORD(0x82, 0xDA, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E328[3] = { TEXT_WORD(0x82, 0xA9, 0x82, 0xED), TEXT_WORD(0x82, 0xBE, 0x82, 0xDA), TEXT_WORD(0x82, 0xA4, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E334[3] = { TEXT_WORD(0x82, 0xA9, 0x82, 0xED), TEXT_WORD(0x82, 0xDE, 0x82, 0xB1), TEXT_WORD(0x82, 0xA4, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E340[3] = { TEXT_WORD(0x82, 0xAB, 0x82, 0xB6), TEXT_WORD(0x82, 0xE5, 0x82, 0xA4), TEXT_WORD(0x82, 0xA2, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E34C[3] = { TEXT_WORD(0x82, 0xAB, 0x82, 0xC4), TEXT_WORD(0x82, 0xA1, 0x82, 0xAA), TEXT_WORD(0x82, 0xA2, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E358[3] = { TEXT_WORD(0x82, 0xAB, 0x82, 0xE5), TEXT_WORD(0x82, 0xA4, 0x82, 0xB6), TEXT_WORD(0x82, 0xF1, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E364[3] = { TEXT_WORD(0x82, 0xAB, 0x82, 0xF1), TEXT_WORD(0x82, 0xB2, 0x82, 0xEB), TEXT_WORD(0x82, 0xA4, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E370[3] = { TEXT_WORD(0x82, 0xAD, 0x82, 0xDD), TEXT_WORD(0x82, 0xC6, 0x82, 0xE8), TEXT_WORD(0x82, 0xE2, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E37C[3] = { TEXT_WORD(0x82, 0xAD, 0x82, 0xE7), TEXT_WORD(0x82, 0xDD, 0x82, 0xB6), TEXT_WORD(0x82, 0xA0, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E388[3] = { TEXT_WORD(0x82, 0xAD, 0x82, 0xE8), TEXT_WORD(0x82, 0xC6, 0x82, 0xE8), TEXT_WORD(0x82, 0xB7, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E394[3] = { TEXT_WORD(0x82, 0xAF, 0x82, 0xC6), TEXT_WORD(0x82, 0xA4, 0x82, 0xB6), TEXT_WORD(0x82, 0xF1, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E3A0[3] = { TEXT_WORD(0x82, 0xB0, 0x82, 0xF1), TEXT_WORD(0x82, 0xBF, 0x82, 0xB6), TEXT_WORD(0x82, 0xF1, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E3AC[3] = { TEXT_WORD(0x82, 0xB2, 0x82, 0xA4), TEXT_WORD(0x82, 0xD1, 0x82, 0xE5), TEXT_WORD(0x82, 0xA4, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E3B8[3] = { TEXT_WORD(0x82, 0xB2, 0x82, 0xB4), TEXT_WORD(0x82, 0xA2, 0x82, 0xB5), TEXT_WORD(0x82, 0xE5, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E3C4[3] = { TEXT_WORD(0x82, 0xB6, 0x82, 0xB2), TEXT_WORD(0x82, 0xAD, 0x82, 0xCE), TEXT_WORD(0x82, 0xE7, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E3D0[3] = { TEXT_WORD(0x82, 0xB5, 0x82, 0xE5), TEXT_WORD(0x82, 0xAD, 0x82, 0xB1), TEXT_WORD(0x82, 0xA4, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E3DC[3] = { TEXT_WORD(0x82, 0xB6, 0x82, 0xE5), TEXT_WORD(0x82, 0xBF, 0x82, 0xE3), TEXT_WORD(0x82, 0xA4, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E3E8[3] = { TEXT_WORD(0x82, 0xB6, 0x82, 0xF1), TEXT_WORD(0x82, 0xAE, 0x82, 0xED), TEXT_WORD(0x82, 0xA2, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E3F4[3] = { TEXT_WORD(0x82, 0xB9, 0x82, 0xA2), TEXT_WORD(0x82, 0xD1, 0x82, 0xE5), TEXT_WORD(0x82, 0xA4, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E400[3] = { TEXT_WORD(0x82, 0xBC, 0x82, 0xCA), TEXT_WORD(0x82, 0xC1, 0x82, 0xC4), TEXT_WORD(0x82, 0xE9, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E40C[3] = { TEXT_WORD(0x82, 0xBE, 0x82, 0xC1), TEXT_WORD(0x82, 0xBF, 0x82, 0xDC), TEXT_WORD(0x82, 0xF1, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E418[3] = { TEXT_WORD(0x82, 0xBD, 0x82, 0xF1), TEXT_WORD(0x82, 0xBB, 0x82, 0xAB), TEXT_WORD(0x82, 0xF1, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E424[3] = { TEXT_WORD(0x82, 0xBF, 0x82, 0xA6), TEXT_WORD(0x82, 0xA8, 0x82, 0xAD), TEXT_WORD(0x82, 0xEA, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E430[3] = { TEXT_WORD(0x82, 0xBF, 0x82, 0xE1), TEXT_WORD(0x82, 0xF1, 0x82, 0xB1), TEXT_WORD(0x82, 0xEB, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E43C[3] = { TEXT_WORD(0x82, 0xBF, 0x82, 0xE5), TEXT_WORD(0x82, 0xC1, 0x82, 0xCF), TEXT_WORD(0x82, 0xE8, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E448[3] = { TEXT_WORD(0x82, 0xBF, 0x82, 0xE5), TEXT_WORD(0x82, 0xCF, 0x81, '['), TEXT_WORD(0x82, 0xE8, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E454[3] = { TEXT_WORD(0x82, 0xC7, 0x82, 0xA4), TEXT_WORD(0x82, 0xED, 0x82, 0xBF), TEXT_WORD(0x82, 0xAD, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E460[3] = { TEXT_WORD(0x82, 0xC6, 0x82, 0xB3), TEXT_WORD(0x82, 0xC2, 0x82, 0xC9), TEXT_WORD(0x82, 0xF1, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E46C[3] = { TEXT_WORD(0x82, 0xC7, 0x82, 0xB3), TEXT_WORD(0x82, 0xDC, 0x82, 0xED), TEXT_WORD(0x82, 0xE8, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E478[3] = { TEXT_WORD(0x82, 0xC6, 0x82, 0xE9), TEXT_WORD(0x82, 0xB1, 0x82, 0xD3), TEXT_WORD(0x82, 0xA4, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E484[3] = { TEXT_WORD(0x82, 0xC9, 0x82, 0xE5), TEXT_WORD(0x82, 0xA4, 0x82, 0xC7), TEXT_WORD(0x82, 0xA4, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E490[3] = { TEXT_WORD(0x82, 0xCE, 0x82, 0x9F), TEXT_WORD(0x81, '[', 0x82, 0xB6), TEXT_WORD(0x82, 0xF1, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E49C[3] = { TEXT_WORD(0x82, 0xCE, 0x82, 0xA2), TEXT_WORD(0x82, 0xB5, 0x82, 0xE3), TEXT_WORD(0x82, 0xF1, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E4A8[3] = { TEXT_WORD(0x82, 0xCE, 0x82, 0xA9), TEXT_WORD(0x82, 0xBF, 0x82, 0xE5), TEXT_WORD(0x82, 0xF1, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E4B4[3] = { TEXT_WORD(0x82, 0xD3, 0x82, 0xA5), TEXT_WORD(0x82, 0xE7, 0x82, 0xBF), TEXT_WORD(0x82, 0xA8, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E4C0[3] = { TEXT_WORD(0x82, 0xD4, 0x82, 0xE7), TEXT_WORD(0x82, 0xAD, 0x82, 0xDD), TEXT_WORD(0x82, 0xF1, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E4CC[3] = { TEXT_WORD(0x82, 0xD3, 0x82, 0xEB), TEXT_WORD(0x82, 0xA4, 0x82, 0xB5), TEXT_WORD(0x82, 0xE1, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E4D8[3] = { TEXT_WORD(0x82, 0xD9, 0x82, 0xCB), TEXT_WORD(0x82, 0xD0, 0x82, 0xEB), TEXT_WORD(0x82, 0xA2, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E4E4[3] = { TEXT_WORD(0x82, 0xDA, 0x82, 0xD6), TEXT_WORD(0x82, 0xDD, 0x82, 0xA0), TEXT_WORD(0x82, 0xF1, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E4F0[3] = { TEXT_WORD(0x82, 0xDC, 0x82, 0xA9), TEXT_WORD(0x82, 0xC8, 0x82, 0xA2), TEXT_WORD(0x82, 0xD3, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E4FC[3] = { TEXT_WORD(0x82, 0xDC, 0x82, 0xE8), TEXT_WORD(0x82, 0xD3, 0x82, 0x9F), TEXT_WORD(0x82, 0xC8, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E508[3] = { TEXT_WORD(0x82, 0xDC, 0x82, 0xF1), TEXT_WORD(0x82, 0xB5, 0x82, 0xE3), TEXT_WORD(0x82, 0xA4, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E514[3] = { TEXT_WORD(0x82, 0xDD, 0x82, 0xA9), TEXT_WORD(0x82, 0xA2, 0x82, 0xB1), TEXT_WORD(0x82, 0xAD, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E520[3] = { TEXT_WORD(0x82, 0xDF, 0x82, 0xAD), TEXT_WORD(0x82, 0xE7, 0x82, 0xA4), TEXT_WORD(0x82, 0xBF, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E52C[3] = { TEXT_WORD(0x82, 0xDF, 0x82, 0xAD), TEXT_WORD(0x82, 0xE7, 0x82, 0xCD), TEXT_WORD(0x82, 0xF1, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E538[3] = { TEXT_WORD(0x82, 0xE2, 0x82, 0xAD), TEXT_WORD(0x82, 0xBF, 0x82, 0xE3), TEXT_WORD(0x82, 0xA4, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E544[3] = { TEXT_WORD(0x82, 0xE2, 0x82, 0xD4), TEXT_WORD(0x82, 0xC9, 0x82, 0xE7), TEXT_WORD(0x82, 0xDD, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E550[3] = { TEXT_WORD(0x82, 0xE7, 0x82, 0xA2), TEXT_WORD(0x82, 0xD1, 0x82, 0xE5), TEXT_WORD(0x82, 0xA4, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E55C[3] = { TEXT_WORD(0x82, 0xE7, 0x82, 0xD4), TEXT_WORD(0x82, 0xD9, 0x82, 0xC4), TEXT_WORD(0x82, 0xE9, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E568[3] = { TEXT_WORD(0x82, 0xE8, 0x82, 0xF1), TEXT_WORD(0x82, 0xD1, 0x82, 0xE5), TEXT_WORD(0x82, 0xA4, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031E574[3] = { TEXT_WORD(0x83, 0x94, 0x82, 0x9F), TEXT_WORD(0x82, 0xAC, 0x82, 0xC8), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E580[3] = { TEXT_WORD(0x82, 0xDD, 0x82, 0xC2), TEXT_WORD(0x82, 0xAD, 0x82, 0xE7), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E58C[3] = { TEXT_WORD(0x83, 'A', 0x83, 'C'), TEXT_WORD(0x83, 'G', 0x83, 'L'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E598[3] = { TEXT_WORD(0x83, 'A', 0x83, 'C'), TEXT_WORD(0x83, 'm', 0x83, 'R'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E5A4[3] = { TEXT_WORD(0x83, 'A', 0x83, 'L'), TEXT_WORD(0x83, 0x82, 0x83, 'E'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E5B0[3] = { TEXT_WORD(0x83, 'A', 0x83, 'T'), TEXT_WORD(0x83, 'R', 0x83, 'E'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E5BC[3] = { TEXT_WORD(0x83, 'A', 0x83, 'V'), TEXT_WORD(0x83, 'L', 0x83, 0x8A), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E5C8[3] = { TEXT_WORD(0x83, 'A', 0x83, 0x81), TEXT_WORD(0x83, 'R', 0x83, 'E'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E5D4[3] = { TEXT_WORD(0x83, 'C', 0x83, '^'), TEXT_WORD(0x83, 'R', 0x83, 'E'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E5E0[3] = { TEXT_WORD(0x83, 'C', 0x83, 0x81), TEXT_WORD(0x83, 'N', 0x83, 0x89), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E5EC[3] = { TEXT_WORD(0x83, 'C', 0x83, 0x93), TEXT_WORD(0x83, 'J', 0x83, 'N'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E5F8[3] = { TEXT_WORD(0x83, 'C', 0x83, 0x93), TEXT_WORD(0x83, 'P', 0x83, 'C'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E604[3] = { TEXT_WORD(0x83, 'C', 0x83, 0x93), TEXT_WORD(0x83, 'm', 0x83, 'E'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E610[3] = { TEXT_WORD(0x83, 'C', 0x83, 0x93), TEXT_WORD(0x83, 'o', 0x83, 'C'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E61C[3] = { TEXT_WORD(0x83, 'C', 0x83, 0x93), TEXT_WORD(0x83, 0x82, 0x83, 'E'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E628[3] = { TEXT_WORD(0x83, 0x94, 0x83, '@'), TEXT_WORD(0x83, 'M', 0x83, 'i'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E634[3] = { TEXT_WORD(0x83, 'E', 0x83, 'X'), TEXT_WORD(0x83, 'm', 0x83, 0x8D), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E640[3] = { TEXT_WORD(0x83, 'E', 0x83, '}'), TEXT_WORD(0x83, 'Y', 0x83, 0x81), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E64C[3] = { TEXT_WORD(0x83, 'G', 0x83, 'X'), TEXT_WORD(0x83, 'G', 0x83, 0x80), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E658[3] = { TEXT_WORD(0x83, 'G', 0x83, '^'), TEXT_WORD(0x83, 0x93, 0x83, '{'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E664[3] = { TEXT_WORD(0x83, 'I', 0x83, 'b'), TEXT_WORD(0x83, 'p', 0x83, 'C'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E670[3] = { TEXT_WORD(0x83, 'I', 0x83, 'i'), TEXT_WORD(0x83, 'j', 0x83, 'C'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E67C[3] = { TEXT_WORD(0x83, 'I', 0x83, 'i'), TEXT_WORD(0x83, 'j', 0x81, '['), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E688[3] = { TEXT_WORD(0x83, 'I', 0x83, '}'), TEXT_WORD(0x83, 0x8F, 0x83, 0x8A), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E694[3] = { TEXT_WORD(0x83, 'I', 0x83, 0x8F), TEXT_WORD(0x83, 'C', 0x83, 0x84), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E6A0[3] = { TEXT_WORD(0x83, 'I', 0x83, 0x93), TEXT_WORD(0x83, '{', 0x83, 'E'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E6AC[3] = { TEXT_WORD(0x83, 'K', 0x83, 'C'), TEXT_WORD(0x83, 'L', 0x83, '`'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E6B8[3] = { TEXT_WORD(0x83, 'K', 0x83, 'C'), TEXT_WORD(0x83, 'W', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E6C4[3] = { TEXT_WORD(0x83, 'K', 0x83, '`'), TEXT_WORD(0x83, 0x83, 0x83, 0x81), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E6D0[3] = { TEXT_WORD(0x83, 'J', 0x83, 0x8F), TEXT_WORD(0x83, '{', 0x83, 'E'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E6DC[3] = { TEXT_WORD(0x83, 'K', 0x83, 0x93), TEXT_WORD(0x83, 'V', 0x83, 0x83), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E6E8[3] = { TEXT_WORD(0x83, 'L', 0x81, '['), TEXT_WORD(0x83, 'Z', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E6F4[3] = { TEXT_WORD(0x83, 'L', 0x83, 'J'), TEXT_WORD(0x83, 'W', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E700[3] = { TEXT_WORD(0x83, 'L', 0x83, 'O'), TEXT_WORD(0x83, 0x8B, 0x83, 'C'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E70C[3] = { TEXT_WORD(0x83, 'L', 0x83, 'P'), TEXT_WORD(0x83, 'C', 0x83, 'W'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E718[3] = { TEXT_WORD(0x83, 'L', 0x83, 'W'), TEXT_WORD(0x83, 0x8B, 0x83, 'V'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E724[3] = { TEXT_WORD(0x83, 'L', 0x83, '`'), TEXT_WORD(0x83, 'K', 0x83, 'C'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E730[3] = { TEXT_WORD(0x83, 'L', 0x83, 0x85), TEXT_WORD(0x83, 'E', 0x83, 'W'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E73C[3] = { TEXT_WORD(0x83, 'L', 0x83, 0x93), TEXT_WORD(0x83, '^', 0x83, '}'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E748[3] = { TEXT_WORD(0x83, 'N', 0x81, '['), TEXT_WORD(0x83, 0x8A, 0x81, '['), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E754[3] = { TEXT_WORD(0x83, 'N', 0x83, 0x8D), TEXT_WORD(0x83, 0x93, 0x83, '{'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E760[3] = { TEXT_WORD(0x83, 'R', 0x83, 'E'), TEXT_WORD(0x83, '}', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E76C[3] = { TEXT_WORD(0x83, 'R', 0x81, '['), TEXT_WORD(0x83, '}', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E778[3] = { TEXT_WORD(0x83, 'R', 0x83, 'J'), TEXT_WORD(0x83, 'C', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E784[3] = { TEXT_WORD(0x83, 'R', 0x83, 'd'), TEXT_WORD(0x83, 'J', 0x83, 'C'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E790[3] = { TEXT_WORD(0x83, 'U', 0x81, '['), TEXT_WORD(0x83, 0x81, 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E79C[3] = { TEXT_WORD(0x83, 'T', 0x83, 'C'), TEXT_WORD(0x83, 'n', 0x83, 'e'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E7A8[3] = { TEXT_WORD(0x83, 'T', 0x83, 0x93), TEXT_WORD(0x83, 'X', 0x83, 'P'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E7B4[3] = { TEXT_WORD(0x83, 'V', 0x83, 'i'), TEXT_WORD(0x83, 'W', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E7C0[3] = { TEXT_WORD(0x83, 'W', 0x83, 'v'), TEXT_WORD(0x83, 'V', 0x81, '['), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E7CC[3] = { TEXT_WORD(0x83, 'V', 0x83, 0x83), TEXT_WORD(0x83, 'Z', 0x83, 'C'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E7D8[3] = { TEXT_WORD(0x83, 'W', 0x83, 0x87), TEXT_WORD(0x83, 'E', 0x83, 't'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E7E4[3] = { TEXT_WORD(0x83, 'W', 0x83, 0x87), TEXT_WORD(0x83, 'P', 0x83, 'c'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E7F0[3] = { TEXT_WORD(0x83, 'W', 0x83, 0x87), TEXT_WORD(0x83, 'R', 0x83, 'E'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E7FC[3] = { TEXT_WORD(0x83, 'V', 0x83, 0x87), TEXT_WORD(0x83, 'W', 0x83, 0x87), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E808[3] = { TEXT_WORD(0x83, 'X', 0x83, 'J'), TEXT_WORD(0x83, 'g', 0x83, 0x8D), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E814[3] = { TEXT_WORD(0x83, 'X', 0x83, 'y'), TEXT_WORD(0x83, 0x8B, 0x83, '}'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E820[3] = { TEXT_WORD(0x83, 'Y', 0x83, 0x8A), TEXT_WORD(0x83, 'Z', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E82C[3] = { TEXT_WORD(0x83, 'Z', 0x83, 'C'), TEXT_WORD(0x83, 'G', 0x83, 'L'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E838[3] = { TEXT_WORD(0x83, 'Z', 0x83, 'C'), TEXT_WORD(0x83, 'R', 0x83, 'E'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E844[3] = { TEXT_WORD(0x83, 'Z', 0x83, 'C'), TEXT_WORD(0x83, 'n', 0x83, 'N'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E850[3] = { TEXT_WORD(0x83, 'Z', 0x83, 'b'), TEXT_WORD(0x83, 'N', 0x83, 'X'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E85C[3] = { TEXT_WORD(0x83, 'Z', 0x83, 0x93), TEXT_WORD(0x83, 'W', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E868[3] = { TEXT_WORD(0x83, 'Z', 0x83, 0x93), TEXT_WORD(0x83, 'Y', 0x83, 0x8A), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E874[3] = { TEXT_WORD(0x83, '\\', 0x83, 'E'), TEXT_WORD(0x83, 'W', 0x83, 't'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E880[3] = { TEXT_WORD(0x83, '^', 0x83, 'S'), TEXT_WORD(0x83, 'T', 0x83, 'N'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E88C[3] = { TEXT_WORD(0x83, '^', 0x83, '}'), TEXT_WORD(0x83, 'L', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E898[3] = { TEXT_WORD(0x83, '^', 0x83, 0x8A), TEXT_WORD(0x83, 'o', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E8A4[3] = { TEXT_WORD(0x83, '_', 0x83, 0x93), TEXT_WORD(0x83, 'R', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E8B0[3] = { TEXT_WORD(0x83, '^', 0x83, 0x93), TEXT_WORD(0x83, '|', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E8BC[3] = { TEXT_WORD(0x83, '`', 0x83, 0x87), TEXT_WORD(0x83, 'E', 0x83, 0x8A), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E8C8[3] = { TEXT_WORD(0x83, '`', 0x83, 0x93), TEXT_WORD(0x83, 'J', 0x83, 'X'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E8D4[3] = { TEXT_WORD(0x83, '`', 0x83, 0x93), TEXT_WORD(0x83, '`', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E8E0[3] = { TEXT_WORD(0x83, 'f', 0x83, 'J'), TEXT_WORD(0x83, '`', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E8EC[3] = { TEXT_WORD(0x83, 'e', 0x83, 0x93), TEXT_WORD(0x83, '{', 0x83, 'E'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E8F8[3] = { TEXT_WORD(0x83, 'h', 0x83, 'E'), TEXT_WORD(0x83, 'e', 0x83, 'C'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E904[3] = { TEXT_WORD(0x83, 'g', 0x83, 'E'), TEXT_WORD(0x83, 'i', 0x83, 'C'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E910[3] = { TEXT_WORD(0x83, 'h', 0x83, 'L'), TEXT_WORD(0x83, 0x85, 0x83, '\\'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E91C[3] = { TEXT_WORD(0x83, 'h', 0x83, 'L'), TEXT_WORD(0x83, 0x85, 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E928[3] = { TEXT_WORD(0x83, 'h', 0x83, 0x81), TEXT_WORD(0x83, 'N', 0x83, 0x89), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E934[3] = { TEXT_WORD(0x83, 'h', 0x83, 0x82), TEXT_WORD(0x83, 'b', 0x83, '^'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E940[3] = { TEXT_WORD(0x83, 'h', 0x83, 0x82), TEXT_WORD(0x83, 'b', 0x83, 'e'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E94C[3] = { TEXT_WORD(0x83, 'h', 0x83, 0x82), TEXT_WORD(0x83, 'b', 0x83, 'g'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E958[3] = { TEXT_WORD(0x83, 'g', 0x83, 0x8B), TEXT_WORD(0x83, 'G', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E964[3] = { TEXT_WORD(0x83, 'i', 0x83, 'J'), TEXT_WORD(0x83, '_', 0x83, 'V'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E970[3] = { TEXT_WORD(0x83, 'i', 0x83, 0x93), TEXT_WORD(0x83, 'Z', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E97C[3] = { TEXT_WORD(0x83, 'j', 0x83, 'R'), TEXT_WORD(0x83, 0x88, 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E988[3] = { TEXT_WORD(0x83, 'k', 0x83, '}'), TEXT_WORD(0x83, 'b', 0x83, 'L'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E994[3] = { TEXT_WORD(0x83, 'k', 0x83, 0x8C), TEXT_WORD(0x83, 'k', 0x83, 0x8C), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E9A0[3] = { TEXT_WORD(0x83, 'o', 0x83, '@'), TEXT_WORD(0x83, 'M', 0x83, 'i'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E9AC[3] = { TEXT_WORD(0x83, 'o', 0x81, '['), TEXT_WORD(0x83, 'W', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E9B8[3] = { TEXT_WORD(0x83, 'p', 0x83, 'C'), TEXT_WORD(0x83, 'Y', 0x83, 0x8A), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E9C4[3] = { TEXT_WORD(0x83, 'p', 0x83, 'C'), TEXT_WORD(0x82, 0xB8, 0x82, 0xE8), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E9D0[3] = { TEXT_WORD(0x83, 'o', 0x83, 'C'), TEXT_WORD(0x83, 'h', 0x83, 'N'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E9DC[3] = { TEXT_WORD(0x83, 'n', 0x83, 'C'), TEXT_WORD(0x83, '~', 0x83, 'X'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E9E8[3] = { TEXT_WORD(0x83, 'o', 0x83, '`'), TEXT_WORD(0x83, 0x87, 0x83, 'E'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031E9F4[3] = { TEXT_WORD(0x83, 'p', 0x83, 0x93), TEXT_WORD(0x83, 'p', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EA00[3] = { TEXT_WORD(0x83, 'r', 0x81, '['), TEXT_WORD(0x83, '`', 0x83, 'N'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EA0C[3] = { TEXT_WORD(0x83, 'q', 0x83, 'b'), TEXT_WORD(0x83, 'L', 0x81, '['), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EA18[3] = { TEXT_WORD(0x83, 's', 0x83, 0x93), TEXT_WORD(0x83, 'T', 0x83, 0x8D), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EA24[3] = { TEXT_WORD(0x83, 't', 0x83, '@'), TEXT_WORD(0x83, 'b', 0x83, 'N'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EA30[3] = { TEXT_WORD(0x83, 't', 0x83, 'O'), TEXT_WORD(0x83, 'V', 0x83, 0x83), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EA3C[3] = { TEXT_WORD(0x83, 'u', 0x83, 'T'), TEXT_WORD(0x83, 'C', 0x83, 'N'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EA48[3] = { TEXT_WORD(0x83, 'u', 0x83, '^'), TEXT_WORD(0x83, 'o', 0x83, 'R'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EA54[3] = { TEXT_WORD(0x83, 't', 0x83, 0x8D), TEXT_WORD(0x83, 'E', 0x83, 'W'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EA60[3] = { TEXT_WORD(0x83, 'w', 0x83, 0x8B), TEXT_WORD(0x83, 'y', 0x83, 'X'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EA6C[3] = { TEXT_WORD(0x83, 'w', 0x83, 0x8D), TEXT_WORD(0x83, 'C', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EA78[3] = { TEXT_WORD(0x83, 'z', 0x83, 'E'), TEXT_WORD(0x83, 'P', 0x83, 'C'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EA84[3] = { TEXT_WORD(0x83, 'z', 0x81, '['), TEXT_WORD(0x83, 'P', 0x81, '['), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EA90[3] = { TEXT_WORD(0x83, 'z', 0x83, 'N'), TEXT_WORD(0x83, 'Z', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EA9C[3] = { TEXT_WORD(0x83, '|', 0x83, 'R'), TEXT_WORD(0x83, '`', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EAA8[3] = { TEXT_WORD(0x83, '|', 0x83, 'R'), TEXT_WORD(0x83, 'y', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EAB4[3] = { TEXT_WORD(0x83, '|', 0x83, 0x8A), TEXT_WORD(0x83, 'R', 0x83, 'E'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EAC0[3] = { TEXT_WORD(0x83, '}', 0x83, 0x93), TEXT_WORD(0x83, 'W', 0x83, 0x8B), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EACC[3] = { TEXT_WORD(0x83, '~', 0x83, 'c'), TEXT_WORD(0x83, 'N', 0x83, '`'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EAD8[3] = { TEXT_WORD(0x83, '~', 0x83, 'c'), TEXT_WORD(0x83, 'N', 0x83, 0x89), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EAE4[3] = { TEXT_WORD(0x83, '~', 0x83, 'c'), TEXT_WORD(0x83, 'R', 0x83, 'V'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EAF0[3] = { TEXT_WORD(0x83, 0x81, 0x83, 'b'), TEXT_WORD(0x83, 'J', 0x83, '`'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EAFC[3] = { TEXT_WORD(0x83, 0x82, 0x83, 'E'), TEXT_WORD(0x83, 'W', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EB08[3] = { TEXT_WORD(0x83, 0x82, 0x83, 0x93), TEXT_WORD(0x83, 0x82, 0x83, 'E'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EB14[3] = { TEXT_WORD(0x83, 0x84, 0x83, 0x89), TEXT_WORD(0x82, 0xB9, 0x82, 0xEB), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EB20[3] = { TEXT_WORD(0x83, 0x84, 0x83, 0x8A), TEXT_WORD(0x83, 'R', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EB2C[3] = { TEXT_WORD(0x83, 0x84, 0x83, 0x8A), TEXT_WORD(0x83, 'T', 0x81, '['), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EB38[3] = { TEXT_WORD(0x83, 0x84, 0x83, 0x8A), TEXT_WORD(0x83, '`', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EB44[3] = { TEXT_WORD(0x83, 0x84, 0x83, 0x8A), TEXT_WORD(0x83, '}', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EB50[3] = { TEXT_WORD(0x83, 0x84, 0x83, 0x93), TEXT_WORD(0x83, 'L', 0x81, '['), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EB5C[3] = { TEXT_WORD(0x83, 0x88, 0x83, 'C'), TEXT_WORD(0x83, 0x88, 0x83, 'C'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EB68[3] = { TEXT_WORD(0x83, 0x88, 0x83, 'c'), TEXT_WORD(0x83, 'A', 0x83, 'V'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EB74[3] = { TEXT_WORD(0x83, 0x89, 0x83, 'f'), TEXT_WORD(0x83, 'B', 0x83, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EB80[3] = { TEXT_WORD(0x83, 0x89, 0x83, 0x93), TEXT_WORD(0x83, 'R', 0x83, 'E'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EB8C[3] = { TEXT_WORD(0x83, 0x8D, 0x83, 0x93), TEXT_WORD(0x83, 'p', 0x83, 0x8A), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EB98[3] = { TEXT_WORD(0x83, 'A', 0x83, 'C'), TEXT_WORD(0x83, 'k', 0x83, 'W'), TEXT_WORD(0x83, 0x93, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EBA4[3] = { TEXT_WORD(0x83, 'A', 0x83, 'L'), TEXT_WORD(0x83, 0x81, 0x83, 'N'), TEXT_WORD(0x83, 0x89, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EBB0[3] = { TEXT_WORD(0x83, 'A', 0x83, 0x8B), TEXT_WORD(0x83, 'J', 0x83, 'C'), TEXT_WORD(0x83, '_', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EBBC[3] = { TEXT_WORD(0x83, 'C', 0x83, 'L'), TEXT_WORD(0x83, 0x88, 0x83, 'o'), TEXT_WORD(0x83, 'C', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EBC8[3] = { TEXT_WORD(0x83, 'C', 0x83, 'Z'), TEXT_WORD(0x83, 'R', 0x83, 'W'), TEXT_WORD(0x83, 'L', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EBD4[3] = { TEXT_WORD(0x83, 'C', 0x83, 'k'), TEXT_WORD(0x83, 'R', 0x83, 0x8D), TEXT_WORD(0x83, 'V', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EBE0[3] = { TEXT_WORD(0x83, 'C', 0x83, 'k'), TEXT_WORD(0x83, 'S', 0x83, 0x8D), TEXT_WORD(0x83, 'V', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EBEC[3] = { TEXT_WORD(0x83, 'C', 0x83, 'k'), TEXT_WORD(0x83, 'W', 0x83, 'j'), TEXT_WORD(0x83, 0x93, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EBF8[3] = { TEXT_WORD(0x83, 'E', 0x83, '}'), TEXT_WORD(0x83, 'm', 0x83, 'z'), TEXT_WORD(0x83, 'l', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EC04[3] = { TEXT_WORD(0x83, 'G', 0x83, 'X'), TEXT_WORD(0x83, 'L', 0x83, 0x82), TEXT_WORD(0x81, '[', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EC10[3] = { TEXT_WORD(0x83, 'G', 0x83, 'q'), TEXT_WORD(0x83, 0x81, 0x83, '}'), TEXT_WORD(0x83, 0x8B, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EC1C[3] = { TEXT_WORD(0x83, 'I', 0x83, 'V'), TEXT_WORD(0x83, 0x82, 0x83, 'h'), TEXT_WORD(0x83, 0x8A, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EC28[3] = { TEXT_WORD(0x83, 'I', 0x83, '`'), TEXT_WORD(0x83, 0x83, 0x83, 'N'), TEXT_WORD(0x83, '~', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EC34[3] = { TEXT_WORD(0x83, 'I', 0x83, 'i'), TEXT_WORD(0x83, 'y', 0x83, 'b'), TEXT_WORD(0x83, 'g', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EC40[3] = { TEXT_WORD(0x83, 'J', 0x83, 'T'), TEXT_WORD(0x83, 'b', 0x83, 'J'), TEXT_WORD(0x83, 'L', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EC4C[3] = { TEXT_WORD(0x83, 'J', 0x83, '^'), TEXT_WORD(0x83, 'e', 0x83, 'I'), TEXT_WORD(0x83, '`', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EC58[3] = { TEXT_WORD(0x83, 'J', 0x83, 'i'), TEXT_WORD(0x83, 'c', 0x83, 0x93), TEXT_WORD(0x83, '{', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EC64[3] = { TEXT_WORD(0x83, 'J', 0x83, 0x8F), TEXT_WORD(0x83, '_', 0x83, '{'), TEXT_WORD(0x83, 'E', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EC70[3] = { TEXT_WORD(0x83, 'J', 0x83, 0x8F), TEXT_WORD(0x83, 0x80, 0x83, 'R'), TEXT_WORD(0x83, 'E', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EC7C[3] = { TEXT_WORD(0x83, 'L', 0x83, 'W'), TEXT_WORD(0x83, 0x87, 0x83, 'E'), TEXT_WORD(0x83, 'C', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EC88[3] = { TEXT_WORD(0x83, 'L', 0x83, 'e'), TEXT_WORD(0x83, 'B', 0x83, 'K'), TEXT_WORD(0x83, 'C', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EC94[3] = { TEXT_WORD(0x83, 'L', 0x83, 0x87), TEXT_WORD(0x83, 'E', 0x83, 'W'), TEXT_WORD(0x83, 0x93, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ECA0[3] = { TEXT_WORD(0x83, 'L', 0x83, 0x93), TEXT_WORD(0x83, 'S', 0x83, 0x8D), TEXT_WORD(0x83, 'E', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ECAC[3] = { TEXT_WORD(0x83, 'N', 0x83, '~'), TEXT_WORD(0x83, 'g', 0x83, 0x8A), TEXT_WORD(0x83, 0x84, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ECB8[3] = { TEXT_WORD(0x83, 'N', 0x83, 0x89), TEXT_WORD(0x83, '~', 0x83, 'W'), TEXT_WORD(0x83, 'A', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ECC4[3] = { TEXT_WORD(0x83, 'N', 0x83, 0x8A), TEXT_WORD(0x83, 'g', 0x83, 0x8A), TEXT_WORD(0x83, 'X', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ECD0[3] = { TEXT_WORD(0x83, 'P', 0x83, 'g'), TEXT_WORD(0x83, 'E', 0x83, 'W'), TEXT_WORD(0x83, 0x93, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ECDC[3] = { TEXT_WORD(0x83, 'Q', 0x83, 0x93), TEXT_WORD(0x83, '`', 0x83, 'W'), TEXT_WORD(0x83, 0x93, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ECE8[3] = { TEXT_WORD(0x83, 'S', 0x83, 'E'), TEXT_WORD(0x83, 'r', 0x83, 0x87), TEXT_WORD(0x83, 'E', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ECF4[3] = { TEXT_WORD(0x83, 'S', 0x83, 'U'), TEXT_WORD(0x83, 'C', 0x83, 'V'), TEXT_WORD(0x83, 0x87, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ED00[3] = { TEXT_WORD(0x83, 'W', 0x83, 'S'), TEXT_WORD(0x83, 'N', 0x83, 'o'), TEXT_WORD(0x83, 0x89, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ED0C[3] = { TEXT_WORD(0x83, 'V', 0x83, 0x87), TEXT_WORD(0x83, 'N', 0x83, 'R'), TEXT_WORD(0x83, 'E', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ED18[3] = { TEXT_WORD(0x83, 'W', 0x83, 0x87), TEXT_WORD(0x83, '`', 0x83, 0x85), TEXT_WORD(0x83, 'E', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ED24[3] = { TEXT_WORD(0x83, 'W', 0x83, 0x93), TEXT_WORD(0x83, 'O', 0x83, 0x8F), TEXT_WORD(0x83, 'C', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ED30[3] = { TEXT_WORD(0x83, 'Z', 0x83, 'C'), TEXT_WORD(0x83, 'r', 0x83, 0x87), TEXT_WORD(0x83, 'E', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ED3C[3] = { TEXT_WORD(0x83, ']', 0x83, 'k'), TEXT_WORD(0x83, 'b', 0x83, 'e'), TEXT_WORD(0x83, 0x8B, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ED48[3] = { TEXT_WORD(0x83, '_', 0x83, 'b'), TEXT_WORD(0x83, '`', 0x83, '}'), TEXT_WORD(0x83, 0x93, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ED54[3] = { TEXT_WORD(0x83, '^', 0x83, 0x93), TEXT_WORD(0x83, '\\', 0x83, 'L'), TEXT_WORD(0x83, 0x93, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ED60[3] = { TEXT_WORD(0x83, '`', 0x83, 'G'), TEXT_WORD(0x83, 'I', 0x83, 'N'), TEXT_WORD(0x83, 0x8C, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ED6C[3] = { TEXT_WORD(0x83, '`', 0x83, 0x83), TEXT_WORD(0x83, 0x93, 0x83, 'R'), TEXT_WORD(0x83, 0x8D, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ED78[3] = { TEXT_WORD(0x83, '`', 0x83, 0x87), TEXT_WORD(0x83, 'b', 0x83, 'p'), TEXT_WORD(0x83, 0x8A, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ED84[3] = { TEXT_WORD(0x83, '`', 0x83, 0x87), TEXT_WORD(0x83, 'p', 0x81, '['), TEXT_WORD(0x83, 0x8A, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ED90[3] = { TEXT_WORD(0x83, 'h', 0x83, 'E'), TEXT_WORD(0x83, 0x8F, 0x83, '`'), TEXT_WORD(0x83, 'N', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031ED9C[3] = { TEXT_WORD(0x83, 'g', 0x83, 'T'), TEXT_WORD(0x83, 'c', 0x83, 'j'), TEXT_WORD(0x83, 0x93, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EDA8[3] = { TEXT_WORD(0x83, 'h', 0x83, 'T'), TEXT_WORD(0x83, '}', 0x83, 0x8F), TEXT_WORD(0x83, 0x8A, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EDB4[3] = { TEXT_WORD(0x83, 'g', 0x83, 0x8B), TEXT_WORD(0x83, 'R', 0x83, 't'), TEXT_WORD(0x83, 'E', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EDC0[3] = { TEXT_WORD(0x83, 'j', 0x83, 0x87), TEXT_WORD(0x83, 'E', 0x83, 'h'), TEXT_WORD(0x83, 'E', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EDCC[3] = { TEXT_WORD(0x83, 'o', 0x83, '@'), TEXT_WORD(0x81, '[', 0x83, 'W'), TEXT_WORD(0x83, 0x93, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EDD8[3] = { TEXT_WORD(0x83, 'o', 0x83, 'C'), TEXT_WORD(0x83, 'V', 0x83, 0x85), TEXT_WORD(0x83, 0x93, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EDE4[3] = { TEXT_WORD(0x83, 'o', 0x83, 'J'), TEXT_WORD(0x83, '`', 0x83, 0x87), TEXT_WORD(0x83, 0x93, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EDF0[3] = { TEXT_WORD(0x83, 't', 0x83, 'F'), TEXT_WORD(0x83, 0x89, 0x83, '`'), TEXT_WORD(0x83, 'I', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EDFC[3] = { TEXT_WORD(0x83, 'u', 0x83, 0x89), TEXT_WORD(0x83, 'N', 0x83, '~'), TEXT_WORD(0x83, 0x93, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EE08[3] = { TEXT_WORD(0x83, 't', 0x83, 0x8D), TEXT_WORD(0x83, 'E', 0x83, 'V'), TEXT_WORD(0x83, 0x83, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EE14[3] = { TEXT_WORD(0x83, 'z', 0x83, 'l'), TEXT_WORD(0x83, 'q', 0x83, 0x8D), TEXT_WORD(0x83, 'C', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EE20[3] = { TEXT_WORD(0x83, '{', 0x83, 'w'), TEXT_WORD(0x83, '~', 0x83, 'A'), TEXT_WORD(0x83, 0x93, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EE2C[3] = { TEXT_WORD(0x83, '}', 0x83, 'J'), TEXT_WORD(0x83, 'i', 0x83, 'C'), TEXT_WORD(0x83, 't', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EE38[3] = { TEXT_WORD(0x83, '}', 0x83, 0x8A), TEXT_WORD(0x83, 't', 0x83, '@'), TEXT_WORD(0x83, 'i', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EE44[3] = { TEXT_WORD(0x83, '}', 0x83, 0x93), TEXT_WORD(0x83, 'V', 0x83, 0x85), TEXT_WORD(0x83, 'E', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EE50[3] = { TEXT_WORD(0x83, '~', 0x83, 'J'), TEXT_WORD(0x83, 'C', 0x83, 'R'), TEXT_WORD(0x83, 'N', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EE5C[3] = { TEXT_WORD(0x83, 0x81, 0x83, 'N'), TEXT_WORD(0x83, 0x89, 0x83, 'E'), TEXT_WORD(0x83, '`', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EE68[3] = { TEXT_WORD(0x83, 0x81, 0x83, 'N'), TEXT_WORD(0x83, 0x89, 0x83, 'n'), TEXT_WORD(0x83, 0x93, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EE74[3] = { TEXT_WORD(0x83, 0x84, 0x83, 'N'), TEXT_WORD(0x83, '`', 0x83, 0x85), TEXT_WORD(0x83, 'E', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EE80[3] = { TEXT_WORD(0x83, 0x84, 0x83, 'u'), TEXT_WORD(0x83, 'j', 0x83, 0x89), TEXT_WORD(0x83, '~', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EE8C[3] = { TEXT_WORD(0x83, 0x89, 0x83, 'C'), TEXT_WORD(0x83, 'r', 0x83, 0x87), TEXT_WORD(0x83, 'E', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EE98[3] = { TEXT_WORD(0x83, 0x89, 0x83, 'u'), TEXT_WORD(0x83, 'z', 0x83, 'e'), TEXT_WORD(0x83, 0x8B, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EEA4[3] = { TEXT_WORD(0x83, 0x8A, 0x83, 0x93), TEXT_WORD(0x83, 'r', 0x83, 0x87), TEXT_WORD(0x83, 'E', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031EEB0[3] = { TEXT_WORD(0x82, '`', 0x82, 'm'), TEXT_WORD(0x82, '`', 0x82, 'k'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EEBC[3] = { TEXT_WORD(0x82, '`', 0x82, 'm'), TEXT_WORD(0x82, 't', 0x82, 'r'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EEC8[3] = { TEXT_WORD(0x82, '`', 0x82, 'q'), TEXT_WORD(0x82, 'r', 0x82, 'd'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EED4[3] = { TEXT_WORD(0x82, 'a', 0x82, 't'), TEXT_WORD(0x82, 'r', 0x82, 't'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EEE0[3] = { TEXT_WORD(0x82, 'b', 0x82, 'k'), TEXT_WORD(0x82, 'h', 0x82, 's'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EEEC[3] = { TEXT_WORD(0x82, 'b', 0x82, 'n'), TEXT_WORD(0x82, 'b', 0x82, 'j'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EEF8[3] = { TEXT_WORD(0x82, 'b', 0x82, 'n'), TEXT_WORD(0x82, 'n', 0x82, 'm'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EF04[3] = { TEXT_WORD(0x82, 'b', 0x82, 't'), TEXT_WORD(0x82, 'm', 0x82, 's'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EF10[3] = { TEXT_WORD(0x82, 'c', 0x82, '`'), TEXT_WORD(0x82, 'l', 0x82, 'm'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EF1C[3] = { TEXT_WORD(0x82, 'c', 0x82, 'h'), TEXT_WORD(0x82, 'b', 0x82, 'j'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EF28[3] = { TEXT_WORD(0x82, 'c', 0x82, 'x'), TEXT_WORD(0x82, 'j', 0x82, 'd'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EF34[3] = { TEXT_WORD(0x82, 'e', 0x81, 0x96), TEXT_WORD(0x81, 0x96, 0x82, 'j'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EF40[3] = { TEXT_WORD(0x82, 'e', 0x81, '~'), TEXT_WORD(0x81, '~', 0x82, 'j'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EF4C[3] = { TEXT_WORD(0x82, 'e', 0x82, 't'), TEXT_WORD(0x82, 'b', 0x82, 'j'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EF58[3] = { TEXT_WORD(0x82, 'f', 0x82, 'n'), TEXT_WORD(0x82, 'n', 0x82, 'j'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EF64[3] = { TEXT_WORD(0x82, 'f', 0x82, 'q'), TEXT_WORD(0x82, 'n', 0x82, 'd'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EF70[3] = { TEXT_WORD(0x82, 'g', 0x82, 'd'), TEXT_WORD(0x82, 'k', 0x82, 'k'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EF7C[3] = { TEXT_WORD(0x82, 'i', 0x82, 'h'), TEXT_WORD(0x82, 'y', 0x82, 'y'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EF88[3] = { TEXT_WORD(0x82, 'j', 0x82, '`'), TEXT_WORD(0x82, 'a', 0x82, 'n'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EF94[3] = { TEXT_WORD(0x82, 'j', 0x82, 'h'), TEXT_WORD(0x82, 'j', 0x82, 'd'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EFA0[3] = { TEXT_WORD(0x82, 'j', 0x82, 'k'), TEXT_WORD(0x82, 'h', 0x82, 's'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EFAC[3] = { TEXT_WORD(0x82, 'j', 0x82, 't'), TEXT_WORD(0x82, 'm', 0x82, 's'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EFB8[3] = { TEXT_WORD(0x82, 'n', 0x82, 'r'), TEXT_WORD(0x82, 'g', 0x82, 'h'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EFC4[3] = { TEXT_WORD(0x82, 'o', 0x82, 'h'), TEXT_WORD(0x82, 'r', 0x82, 'r'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EFD0[3] = { TEXT_WORD(0x82, 'o', 0x82, 'n'), TEXT_WORD(0x82, 'q', 0x82, 'm'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EFDC[3] = { TEXT_WORD(0x82, 'p', 0x82, 't'), TEXT_WORD(0x82, 'h', 0x82, 'l'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EFE8[3] = { TEXT_WORD(0x82, 'q', 0x82, '`'), TEXT_WORD(0x82, 'o', 0x82, 'd'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031EFF4[3] = { TEXT_WORD(0x82, 'r', 0x82, 'g'), TEXT_WORD(0x81, 0x96, 0x82, 's'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F000[3] = { TEXT_WORD(0x82, 'r', 0x82, 'g'), TEXT_WORD(0x81, '~', 0x82, 's'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F00C[3] = { TEXT_WORD(0x82, 'r', 0x82, 'g'), TEXT_WORD(0x82, 'h', 0x82, 's'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F018[3] = { TEXT_WORD(0x82, 'r', 0x82, 'k'), TEXT_WORD(0x82, 't', 0x82, 's'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F024[3] = { TEXT_WORD(0x82, 's', 0x82, 'h'), TEXT_WORD(0x82, 's', 0x82, 'r'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F030[3] = { TEXT_WORD(0x82, 's', 0x82, 'v'), TEXT_WORD(0x82, '`', 0x82, 's'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F03C[3] = { TEXT_WORD(0x82, 'x', 0x82, 'n'), TEXT_WORD(0x82, 's', 0x82, 't'), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F048[3] = { TEXT_WORD(0x82, 'a', 0x82, '`'), TEXT_WORD(0x82, 'm', 0x82, 'c'), TEXT_WORD(0x82, '`', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F054[3] = { TEXT_WORD(0x82, 'a', 0x82, 'h'), TEXT_WORD(0x82, 'j', 0x82, 'j'), TEXT_WORD(0x82, 'n', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F060[3] = { TEXT_WORD(0x82, 'a', 0x82, 'h'), TEXT_WORD(0x82, 's', 0x82, 'b'), TEXT_WORD(0x82, 'g', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F06C[3] = { TEXT_WORD(0x82, 'a', 0x82, 'n'), TEXT_WORD(0x82, 'm', 0x82, 'd'), TEXT_WORD(0x82, 'q', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F078[3] = { TEXT_WORD(0x82, 'b', 0x82, 'g'), TEXT_WORD(0x82, 'h', 0x82, 'm'), TEXT_WORD(0x82, 'j', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F084[3] = { TEXT_WORD(0x82, 'c', 0x82, '`'), TEXT_WORD(0x82, 'q', 0x82, 'j'), TEXT_WORD(0x82, 'x', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F090[3] = { TEXT_WORD(0x82, 'c', 0x82, 'h'), TEXT_WORD(0x82, 'k', 0x82, 'c'), TEXT_WORD(0x82, 'n', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F09C[3] = { TEXT_WORD(0x82, 'c', 0x82, 'n'), TEXT_WORD(0x82, 'i', 0x82, 'h'), TEXT_WORD(0x82, 'm', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F0A8[3] = { TEXT_WORD(0x82, 'c', 0x82, 'n'), TEXT_WORD(0x82, 'j', 0x82, 'n'), TEXT_WORD(0x82, 't', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F0B4[3] = { TEXT_WORD(0x82, 'd', 0x82, '`'), TEXT_WORD(0x82, 's', 0x82, 'l'), TEXT_WORD(0x82, 'd', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F0C0[3] = { TEXT_WORD(0x82, 'e', 0x82, 'd'), TEXT_WORD(0x82, 'k', 0x82, 'b'), TEXT_WORD(0x82, 'g', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F0CC[3] = { TEXT_WORD(0x82, 'e', 0x82, 't'), TEXT_WORD(0x82, 'f', 0x82, 'k'), TEXT_WORD(0x82, 'x', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F0D8[3] = { TEXT_WORD(0x82, 'e', 0x82, 't'), TEXT_WORD(0x82, 'j', 0x82, 'd'), TEXT_WORD(0x82, 'm', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F0E4[3] = { TEXT_WORD(0x82, 'g', 0x82, 'h'), TEXT_WORD(0x82, 'm', 0x82, 'h'), TEXT_WORD(0x82, 'm', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F0F0[3] = { TEXT_WORD(0x82, 'h', 0x82, 'y'), TEXT_WORD(0x82, '`', 0x82, 'q'), TEXT_WORD(0x82, 'h', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F0FC[3] = { TEXT_WORD(0x82, 'i', 0x82, 'n'), TEXT_WORD(0x82, 'j', 0x82, 'n'), TEXT_WORD(0x82, 't', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F108[3] = { TEXT_WORD(0x82, 'j', 0x82, '`'), TEXT_WORD(0x82, 'a', 0x82, 'n'), TEXT_WORD(0x82, 't', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F114[3] = { TEXT_WORD(0x82, 'j', 0x82, 'd'), TEXT_WORD(0x82, 's', 0x82, 'n'), TEXT_WORD(0x82, 't', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F120[3] = { TEXT_WORD(0x82, 'j', 0x82, 'h'), TEXT_WORD(0x82, 'j', 0x82, 'd'), TEXT_WORD(0x82, 'h', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F12C[3] = { TEXT_WORD(0x82, 'l', 0x82, '`'), TEXT_WORD(0x82, 'm', 0x82, 'j'), TEXT_WORD(0x82, 'n', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F138[3] = { TEXT_WORD(0x82, 'l', 0x82, 'x'), TEXT_WORD(0x82, '`', 0x82, 'r'), TEXT_WORD(0x82, 'r', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F144[3] = { TEXT_WORD(0x82, 'm', 0x82, 'h'), TEXT_WORD(0x82, 'f', 0x82, 'f'), TEXT_WORD(0x82, '`', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F150[3] = { TEXT_WORD(0x82, 'm', 0x82, 'h'), TEXT_WORD(0x82, 'm', 0x82, 'o'), TEXT_WORD(0x82, 't', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F15C[3] = { TEXT_WORD(0x82, 'n', 0x82, 'j'), TEXT_WORD(0x82, '`', 0x82, 'l'), TEXT_WORD(0x82, 'd', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F168[3] = { TEXT_WORD(0x82, 'n', 0x82, 'l'), TEXT_WORD(0x82, 'd', 0x82, 'j'), TEXT_WORD(0x82, 'n', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F174[3] = { TEXT_WORD(0x82, 'n', 0x82, 'm'), TEXT_WORD(0x82, 'a', 0x82, 'n'), TEXT_WORD(0x82, 't', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F180[3] = { TEXT_WORD(0x82, 'o', 0x82, 'd'), TEXT_WORD(0x82, 'm', 0x82, 'h'), TEXT_WORD(0x82, 'r', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F18C[3] = { TEXT_WORD(0x82, 'o', 0x82, 'q'), TEXT_WORD(0x82, 'h', 0x82, 'b'), TEXT_WORD(0x82, 'j', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F198[3] = { TEXT_WORD(0x82, 'o', 0x82, 't'), TEXT_WORD(0x82, 'r', 0x82, 'r'), TEXT_WORD(0x82, 'x', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F1A4[3] = { TEXT_WORD(0x82, 'p', 0x82, 't'), TEXT_WORD(0x82, 'd', 0x82, 'd'), TEXT_WORD(0x82, 'q', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F1B0[3] = { TEXT_WORD(0x82, 'r', 0x82, 'd'), TEXT_WORD(0x82, 'l', 0x82, 'd'), TEXT_WORD(0x82, 'm', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F1BC[3] = { TEXT_WORD(0x82, 's', 0x82, 'h'), TEXT_WORD(0x82, 'c', 0x82, 'c'), TEXT_WORD(0x82, 'x', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F1C8[3] = { TEXT_WORD(0x82, 's', 0x82, 'h'), TEXT_WORD(0x82, 'm', 0x82, 'a'), TEXT_WORD(0x82, '`', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F1D4[3] = { TEXT_WORD(0x82, 's', 0x82, 'h'), TEXT_WORD(0x82, 's', 0x82, 's'), TEXT_WORD(0x82, 'x', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F1E0[3] = { TEXT_WORD(0x82, 's', 0x82, 't'), TEXT_WORD(0x82, 'm', 0x82, 'a'), TEXT_WORD(0x82, 'n', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F1EC[3] = { TEXT_WORD(0x82, 'v', 0x82, 'g'), TEXT_WORD(0x82, 'n', 0x82, 'q'), TEXT_WORD(0x82, 'd', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F1F8[3] = { TEXT_WORD(0x82, 'x', 0x82, 'n'), TEXT_WORD(0x82, 's', 0x82, 'r'), TEXT_WORD(0x82, 't', 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F204[3] = { TEXT_WORD(0x82, 0x81, 0x82, 0x8E), TEXT_WORD(0x82, 0x81, 0x82, 0x8C), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F210[3] = { TEXT_WORD(0x82, 0x81, 0x82, 0x8E), TEXT_WORD(0x82, 0x95, 0x82, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F21C[3] = { TEXT_WORD(0x82, 0x81, 0x82, 0x92), TEXT_WORD(0x82, 0x93, 0x82, 0x85), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F228[3] = { TEXT_WORD(0x82, 0x82, 0x82, 0x95), TEXT_WORD(0x82, 0x93, 0x82, 0x95), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F234[3] = { TEXT_WORD(0x82, 0x83, 0x82, 0x8C), TEXT_WORD(0x82, 0x89, 0x82, 0x94), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F240[3] = { TEXT_WORD(0x82, 0x83, 0x82, 0x8F), TEXT_WORD(0x82, 0x83, 0x82, 0x8B), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F24C[3] = { TEXT_WORD(0x82, 0x83, 0x82, 0x8F), TEXT_WORD(0x82, 0x8F, 0x82, 0x8E), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F258[3] = { TEXT_WORD(0x82, 0x83, 0x82, 0x95), TEXT_WORD(0x82, 0x8E, 0x82, 0x94), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F264[3] = { TEXT_WORD(0x82, 0x84, 0x82, 0x81), TEXT_WORD(0x82, 0x8D, 0x82, 0x8E), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F270[3] = { TEXT_WORD(0x82, 0x84, 0x82, 0x89), TEXT_WORD(0x82, 0x83, 0x82, 0x8B), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F27C[3] = { TEXT_WORD(0x82, 0x84, 0x82, 0x99), TEXT_WORD(0x82, 0x8B, 0x82, 0x85), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F288[3] = { TEXT_WORD(0x82, 0x86, 0x81, 0x96), TEXT_WORD(0x81, 0x96, 0x82, 0x8B), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F294[3] = { TEXT_WORD(0x82, 0x86, 0x81, '~'), TEXT_WORD(0x81, '~', 0x82, 0x8B), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F2A0[3] = { TEXT_WORD(0x82, 0x86, 0x82, 0x95), TEXT_WORD(0x82, 0x83, 0x82, 0x8B), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F2AC[3] = { TEXT_WORD(0x82, 0x87, 0x82, 0x8F), TEXT_WORD(0x82, 0x8F, 0x82, 0x8B), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F2B8[3] = { TEXT_WORD(0x82, 0x87, 0x82, 0x92), TEXT_WORD(0x82, 0x8F, 0x82, 0x85), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F2C4[3] = { TEXT_WORD(0x82, 0x88, 0x82, 0x85), TEXT_WORD(0x82, 0x8C, 0x82, 0x8C), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F2D0[3] = { TEXT_WORD(0x82, 0x8A, 0x82, 0x89), TEXT_WORD(0x82, 0x9A, 0x82, 0x9A), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F2DC[3] = { TEXT_WORD(0x82, 0x8B, 0x82, 0x81), TEXT_WORD(0x82, 0x82, 0x82, 0x8F), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F2E8[3] = { TEXT_WORD(0x82, 0x8B, 0x82, 0x89), TEXT_WORD(0x82, 0x8B, 0x82, 0x85), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F2F4[3] = { TEXT_WORD(0x82, 0x8B, 0x82, 0x8C), TEXT_WORD(0x82, 0x89, 0x82, 0x94), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F300[3] = { TEXT_WORD(0x82, 0x8B, 0x82, 0x95), TEXT_WORD(0x82, 0x8E, 0x82, 0x94), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F30C[3] = { TEXT_WORD(0x82, 0x8F, 0x82, 0x93), TEXT_WORD(0x82, 0x88, 0x82, 0x89), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F318[3] = { TEXT_WORD(0x82, 0x90, 0x82, 0x89), TEXT_WORD(0x82, 0x93, 0x82, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F324[3] = { TEXT_WORD(0x82, 0x90, 0x82, 0x8F), TEXT_WORD(0x82, 0x92, 0x82, 0x8E), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F330[3] = { TEXT_WORD(0x82, 0x91, 0x82, 0x95), TEXT_WORD(0x82, 0x89, 0x82, 0x8D), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F33C[3] = { TEXT_WORD(0x82, 0x92, 0x82, 0x81), TEXT_WORD(0x82, 0x90, 0x82, 0x85), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F348[3] = { TEXT_WORD(0x82, 0x93, 0x82, 0x88), TEXT_WORD(0x81, 0x96, 0x82, 0x94), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F354[3] = { TEXT_WORD(0x82, 0x93, 0x82, 0x88), TEXT_WORD(0x81, '~', 0x82, 0x94), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F360[3] = { TEXT_WORD(0x82, 0x93, 0x82, 0x88), TEXT_WORD(0x82, 0x89, 0x82, 0x94), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F36C[3] = { TEXT_WORD(0x82, 0x93, 0x82, 0x8C), TEXT_WORD(0x82, 0x95, 0x82, 0x94), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F378[3] = { TEXT_WORD(0x82, 0x94, 0x82, 0x89), TEXT_WORD(0x82, 0x94, 0x82, 0x93), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F384[3] = { TEXT_WORD(0x82, 0x94, 0x82, 0x97), TEXT_WORD(0x82, 0x81, 0x82, 0x94), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F390[3] = { TEXT_WORD(0x82, 0x99, 0x82, 0x8F), TEXT_WORD(0x82, 0x94, 0x82, 0x95), 0x00000000 };
const unsigned int NameCheck_CardName_rodata_8031F39C[3] = { TEXT_WORD(0x82, 0x82, 0x82, 0x81), TEXT_WORD(0x82, 0x8E, 0x82, 0x84), TEXT_WORD(0x82, 0x81, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F3A8[3] = { TEXT_WORD(0x82, 0x82, 0x82, 0x89), TEXT_WORD(0x82, 0x8B, 0x82, 0x8B), TEXT_WORD(0x82, 0x8F, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F3B4[3] = { TEXT_WORD(0x82, 0x82, 0x82, 0x89), TEXT_WORD(0x82, 0x94, 0x82, 0x83), TEXT_WORD(0x82, 0x88, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F3C0[3] = { TEXT_WORD(0x82, 0x82, 0x82, 0x8F), TEXT_WORD(0x82, 0x8E, 0x82, 0x85), TEXT_WORD(0x82, 0x92, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F3CC[3] = { TEXT_WORD(0x82, 0x83, 0x82, 0x88), TEXT_WORD(0x82, 0x89, 0x82, 0x8E), TEXT_WORD(0x82, 0x8B, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F3D8[3] = { TEXT_WORD(0x82, 0x84, 0x82, 0x81), TEXT_WORD(0x82, 0x92, 0x82, 0x8B), TEXT_WORD(0x82, 0x99, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F3E4[3] = { TEXT_WORD(0x82, 0x84, 0x82, 0x89), TEXT_WORD(0x82, 0x8C, 0x82, 0x84), TEXT_WORD(0x82, 0x8F, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F3F0[3] = { TEXT_WORD(0x82, 0x84, 0x82, 0x8F), TEXT_WORD(0x82, 0x8A, 0x82, 0x89), TEXT_WORD(0x82, 0x8E, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F3FC[3] = { TEXT_WORD(0x82, 0x84, 0x82, 0x8F), TEXT_WORD(0x82, 0x8B, 0x82, 0x8F), TEXT_WORD(0x82, 0x95, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F408[3] = { TEXT_WORD(0x82, 0x85, 0x82, 0x81), TEXT_WORD(0x82, 0x94, 0x82, 0x8D), TEXT_WORD(0x82, 0x85, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F414[3] = { TEXT_WORD(0x82, 0x86, 0x82, 0x85), TEXT_WORD(0x82, 0x8C, 0x82, 0x83), TEXT_WORD(0x82, 0x88, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F420[3] = { TEXT_WORD(0x82, 0x86, 0x82, 0x95), TEXT_WORD(0x82, 0x87, 0x82, 0x8C), TEXT_WORD(0x82, 0x99, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F42C[3] = { TEXT_WORD(0x82, 0x86, 0x82, 0x95), TEXT_WORD(0x82, 0x8B, 0x82, 0x85), TEXT_WORD(0x82, 0x8E, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F438[3] = { TEXT_WORD(0x82, 0x88, 0x82, 0x89), TEXT_WORD(0x82, 0x8E, 0x82, 0x89), TEXT_WORD(0x82, 0x8E, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F444[3] = { TEXT_WORD(0x82, 0x89, 0x82, 0x9A), TEXT_WORD(0x82, 0x81, 0x82, 0x92), TEXT_WORD(0x82, 0x89, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F450[3] = { TEXT_WORD(0x82, 0x8A, 0x82, 0x8F), TEXT_WORD(0x82, 0x8B, 0x82, 0x8F), TEXT_WORD(0x82, 0x95, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F45C[3] = { TEXT_WORD(0x82, 0x8B, 0x82, 0x81), TEXT_WORD(0x82, 0x82, 0x82, 0x8F), TEXT_WORD(0x82, 0x95, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F468[3] = { TEXT_WORD(0x82, 0x8B, 0x82, 0x85), TEXT_WORD(0x82, 0x94, 0x82, 0x8F), TEXT_WORD(0x82, 0x95, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F474[3] = { TEXT_WORD(0x82, 0x8B, 0x82, 0x89), TEXT_WORD(0x82, 0x8B, 0x82, 0x85), TEXT_WORD(0x82, 0x89, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F480[3] = { TEXT_WORD(0x82, 0x8D, 0x82, 0x81), TEXT_WORD(0x82, 0x8E, 0x82, 0x8B), TEXT_WORD(0x82, 0x8F, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F48C[3] = { TEXT_WORD(0x82, 0x8D, 0x82, 0x99), TEXT_WORD(0x82, 0x81, 0x82, 0x93), TEXT_WORD(0x82, 0x93, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F498[3] = { TEXT_WORD(0x82, 0x8E, 0x82, 0x89), TEXT_WORD(0x82, 0x87, 0x82, 0x87), TEXT_WORD(0x82, 0x81, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F4A4[3] = { TEXT_WORD(0x82, 0x8E, 0x82, 0x89), TEXT_WORD(0x82, 0x8E, 0x82, 0x90), TEXT_WORD(0x82, 0x95, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F4B0[3] = { TEXT_WORD(0x82, 0x8F, 0x82, 0x8B), TEXT_WORD(0x82, 0x81, 0x82, 0x8D), TEXT_WORD(0x82, 0x85, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F4BC[3] = { TEXT_WORD(0x82, 0x8F, 0x82, 0x8D), TEXT_WORD(0x82, 0x85, 0x82, 0x8B), TEXT_WORD(0x82, 0x8F, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F4C8[3] = { TEXT_WORD(0x82, 0x8F, 0x82, 0x8E), TEXT_WORD(0x82, 0x82, 0x82, 0x8F), TEXT_WORD(0x82, 0x95, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F4D4[3] = { TEXT_WORD(0x82, 0x90, 0x82, 0x85), TEXT_WORD(0x82, 0x8E, 0x82, 0x89), TEXT_WORD(0x82, 0x93, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F4E0[3] = { TEXT_WORD(0x82, 0x90, 0x82, 0x92), TEXT_WORD(0x82, 0x89, 0x82, 0x83), TEXT_WORD(0x82, 0x8B, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F4EC[3] = { TEXT_WORD(0x82, 0x90, 0x82, 0x95), TEXT_WORD(0x82, 0x93, 0x82, 0x93), TEXT_WORD(0x82, 0x99, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F4F8[3] = { TEXT_WORD(0x82, 0x91, 0x82, 0x95), TEXT_WORD(0x82, 0x85, 0x82, 0x85), TEXT_WORD(0x82, 0x92, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F504[3] = { TEXT_WORD(0x82, 0x93, 0x82, 0x85), TEXT_WORD(0x82, 0x8D, 0x82, 0x85), TEXT_WORD(0x82, 0x8E, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F510[3] = { TEXT_WORD(0x82, 0x94, 0x82, 0x89), TEXT_WORD(0x82, 0x84, 0x82, 0x84), TEXT_WORD(0x82, 0x99, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F51C[3] = { TEXT_WORD(0x82, 0x94, 0x82, 0x89), TEXT_WORD(0x82, 0x8E, 0x82, 0x82), TEXT_WORD(0x82, 0x81, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F528[3] = { TEXT_WORD(0x82, 0x94, 0x82, 0x89), TEXT_WORD(0x82, 0x94, 0x82, 0x94), TEXT_WORD(0x82, 0x99, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F534[3] = { TEXT_WORD(0x82, 0x94, 0x82, 0x95), TEXT_WORD(0x82, 0x8E, 0x82, 0x82), TEXT_WORD(0x82, 0x8F, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F540[3] = { TEXT_WORD(0x82, 0x97, 0x82, 0x88), TEXT_WORD(0x82, 0x8F, 0x82, 0x92), TEXT_WORD(0x82, 0x85, 0, 0) };
const unsigned int NameCheck_CardName_rodata_8031F54C[3] = { TEXT_WORD(0x82, 0x99, 0x82, 0x8F), TEXT_WORD(0x82, 0x94, 0x82, 0x93), TEXT_WORD(0x82, 0x95, 0, 0) };
/* banned-word table: anchor + 0x72E8, read by NameCheck_ScanBannedWords */
static const char *const sBannedWords[1067] = {
    (const char *)lbl_806D3624,
    (const char *)lbl_806D362C,
    (const char *)lbl_806D3634,
    (const char *)lbl_806D363C,
    (const char *)lbl_806D3644,
    (const char *)lbl_806D364C,
    (const char *)lbl_806D3654,
    (const char *)lbl_806D365C,
    (const char *)lbl_806D3664,
    (const char *)lbl_806D366C,
    (const char *)lbl_806D3674,
    (const char *)lbl_806D367C,
    (const char *)lbl_806D3684,
    (const char *)lbl_806D368C,
    (const char *)lbl_806D3694,
    (const char *)lbl_806D369C,
    (const char *)lbl_806D36A4,
    (const char *)lbl_806D36AC,
    (const char *)lbl_806D36B4,
    (const char *)lbl_806D36BC,
    (const char *)lbl_806D36C4,
    (const char *)lbl_806D36CC,
    (const char *)lbl_806D36D4,
    (const char *)lbl_806D36DC,
    (const char *)lbl_806D36E4,
    (const char *)lbl_806D36EC,
    (const char *)lbl_806D36F4,
    (const char *)lbl_806D36FC,
    (const char *)lbl_806D3704,
    (const char *)lbl_806D370C,
    (const char *)lbl_806D3714,
    (const char *)lbl_806D371C,
    (const char *)lbl_806D3724,
    (const char *)lbl_806D372C,
    (const char *)lbl_806D3734,
    (const char *)lbl_806D373C,
    (const char *)lbl_806D3744,
    (const char *)lbl_806D374C,
    (const char *)lbl_806D3754,
    (const char *)lbl_806D375C,
    (const char *)lbl_806D3764,
    (const char *)lbl_806D376C,
    (const char *)lbl_806D3774,
    (const char *)lbl_806D377C,
    (const char *)lbl_806D3784,
    (const char *)lbl_806D378C,
    (const char *)lbl_806D3794,
    (const char *)lbl_806D379C,
    (const char *)lbl_806D37A4,
    (const char *)lbl_806D37AC,
    (const char *)lbl_806D37B4,
    (const char *)lbl_806D37BC,
    (const char *)lbl_806D37C4,
    (const char *)lbl_806D37CC,
    (const char *)lbl_806D37D4,
    (const char *)lbl_806D37DC,
    (const char *)lbl_806D37E4,
    (const char *)lbl_806D37EC,
    (const char *)lbl_806D37F4,
    (const char *)lbl_806D37FC,
    (const char *)lbl_806D3804,
    (const char *)lbl_806D380C,
    (const char *)lbl_806D3814,
    (const char *)lbl_806D381C,
    (const char *)lbl_806D3824,
    (const char *)lbl_806D382C,
    (const char *)lbl_806D3834,
    (const char *)lbl_806D383C,
    (const char *)lbl_806D3844,
    (const char *)lbl_806D384C,
    (const char *)lbl_806D3854,
    (const char *)lbl_806D385C,
    (const char *)lbl_806D3864,
    (const char *)lbl_806D386C,
    (const char *)lbl_806D3874,
    (const char *)lbl_806D387C,
    (const char *)lbl_806D3884,
    (const char *)lbl_806D388C,
    (const char *)lbl_806D3894,
    (const char *)lbl_806D389C,
    (const char *)lbl_806D38A4,
    (const char *)lbl_806D38AC,
    (const char *)lbl_806D38B4,
    (const char *)lbl_806D38BC,
    (const char *)lbl_806D38C4,
    (const char *)lbl_806D38CC,
    (const char *)lbl_806D38D4,
    (const char *)lbl_806D38DC,
    (const char *)lbl_806D38E4,
    (const char *)lbl_806D38EC,
    (const char *)lbl_806D38F4,
    (const char *)lbl_806D38FC,
    (const char *)lbl_806D3904,
    (const char *)lbl_806D390C,
    (const char *)lbl_806D3914,
    (const char *)lbl_806D391C,
    (const char *)lbl_806D3924,
    (const char *)lbl_806D392C,
    (const char *)lbl_806D3934,
    (const char *)lbl_806D393C,
    (const char *)lbl_806D3944,
    (const char *)lbl_806D394C,
    (const char *)lbl_806D3954,
    (const char *)lbl_806D395C,
    (const char *)lbl_806D3964,
    (const char *)lbl_806D396C,
    (const char *)lbl_806D3974,
    (const char *)lbl_806D397C,
    (const char *)lbl_806D3984,
    (const char *)lbl_806D398C,
    (const char *)lbl_806D3994,
    (const char *)lbl_806D399C,
    (const char *)lbl_806D39A4,
    (const char *)lbl_806D39AC,
    (const char *)lbl_806D39B4,
    (const char *)lbl_806D39BC,
    (const char *)lbl_806D39C4,
    (const char *)lbl_806D39CC,
    (const char *)lbl_806D39D4,
    (const char *)lbl_806D39DC,
    (const char *)lbl_806D39E4,
    (const char *)lbl_806D39EC,
    (const char *)lbl_806D39F4,
    (const char *)lbl_806D39FC,
    (const char *)lbl_806D3A04,
    (const char *)lbl_806D3A0C,
    (const char *)lbl_806D3A14,
    (const char *)lbl_806D3A1C,
    (const char *)lbl_806D3A24,
    (const char *)lbl_806D3A2C,
    (const char *)lbl_806D3A34,
    (const char *)lbl_806D3A3C,
    (const char *)lbl_806D3A44,
    (const char *)lbl_806D3A4C,
    (const char *)lbl_806D3A54,
    (const char *)lbl_806D3A5C,
    (const char *)lbl_806D3A64,
    (const char *)lbl_806D3A6C,
    (const char *)lbl_806D3A74,
    (const char *)lbl_806D3A7C,
    (const char *)lbl_806D3A84,
    (const char *)lbl_806D3A8C,
    (const char *)lbl_806D3A94,
    (const char *)lbl_806D3A9C,
    (const char *)lbl_806D3AA4,
    (const char *)lbl_806D3AAC,
    (const char *)lbl_806D3AB4,
    (const char *)lbl_806D3ABC,
    (const char *)lbl_806D3AC4,
    (const char *)lbl_806D3ACC,
    (const char *)lbl_806D3AD4,
    (const char *)lbl_806D3ADC,
    (const char *)lbl_806D3AE4,
    (const char *)lbl_806D3AEC,
    (const char *)lbl_806D3AF4,
    (const char *)lbl_806D3AFC,
    (const char *)lbl_806D3B04,
    (const char *)lbl_806D3B0C,
    (const char *)lbl_806D3B14,
    (const char *)lbl_806D3B1C,
    (const char *)lbl_806D3B24,
    (const char *)lbl_806D3B2C,
    (const char *)lbl_806D3B34,
    (const char *)lbl_806D3B3C,
    (const char *)lbl_806D3B44,
    (const char *)lbl_806D3B4C,
    (const char *)lbl_806D3B54,
    (const char *)lbl_806D3B5C,
    (const char *)lbl_806D3B64,
    (const char *)lbl_806D3B6C,
    (const char *)lbl_806D3B74,
    (const char *)lbl_806D3B7C,
    (const char *)lbl_806D3B84,
    (const char *)lbl_806D3B8C,
    (const char *)lbl_806D3B94,
    (const char *)lbl_806D3B9C,
    (const char *)lbl_806D3BA4,
    (const char *)lbl_806D3BAC,
    (const char *)lbl_806D3BB4,
    (const char *)lbl_806D3BBC,
    (const char *)lbl_806D3BC4,
    (const char *)lbl_806D3BCC,
    (const char *)lbl_806D3BD4,
    (const char *)lbl_806D3BDC,
    (const char *)lbl_806D3BE4,
    (const char *)lbl_806D3BEC,
    (const char *)lbl_806D3BF4,
    (const char *)lbl_806D3BFC,
    (const char *)lbl_806D3C04,
    (const char *)lbl_806D3C0C,
    (const char *)lbl_806D3C14,
    (const char *)lbl_806D3C1C,
    (const char *)lbl_806D3C24,
    (const char *)lbl_806D3C2C,
    (const char *)lbl_806D3C34,
    (const char *)lbl_806D3C3C,
    (const char *)lbl_806D3C44,
    (const char *)lbl_806D3C4C,
    (const char *)lbl_806D3C54,
    (const char *)lbl_806D3C5C,
    (const char *)lbl_806D3C64,
    (const char *)lbl_806D3C6C,
    (const char *)lbl_806D3C74,
    (const char *)lbl_806D3C7C,
    (const char *)lbl_806D3C84,
    (const char *)NameCheck_CardName_rodata_8031DC68,
    (const char *)NameCheck_CardName_rodata_8031DC74,
    (const char *)NameCheck_CardName_rodata_8031DC80,
    (const char *)NameCheck_CardName_rodata_8031DC8C,
    (const char *)NameCheck_CardName_rodata_8031DC98,
    (const char *)NameCheck_CardName_rodata_8031DCA4,
    (const char *)NameCheck_CardName_rodata_8031DCB0,
    (const char *)NameCheck_CardName_rodata_8031DCBC,
    (const char *)NameCheck_CardName_rodata_8031DCC8,
    (const char *)NameCheck_CardName_rodata_8031DCD4,
    (const char *)NameCheck_CardName_rodata_8031DCE0,
    (const char *)NameCheck_CardName_rodata_8031DCEC,
    (const char *)NameCheck_CardName_rodata_8031DCF8,
    (const char *)NameCheck_CardName_rodata_8031DD04,
    (const char *)NameCheck_CardName_rodata_8031DD10,
    (const char *)NameCheck_CardName_rodata_8031DD1C,
    (const char *)NameCheck_CardName_rodata_8031DD28,
    (const char *)NameCheck_CardName_rodata_8031DD34,
    (const char *)NameCheck_CardName_rodata_8031DD40,
    (const char *)NameCheck_CardName_rodata_8031DD4C,
    (const char *)NameCheck_CardName_rodata_8031DD58,
    (const char *)NameCheck_CardName_rodata_8031DD64,
    (const char *)NameCheck_CardName_rodata_8031DD70,
    (const char *)NameCheck_CardName_rodata_8031DD7C,
    (const char *)NameCheck_CardName_rodata_8031DD88,
    (const char *)NameCheck_CardName_rodata_8031DD94,
    (const char *)NameCheck_CardName_rodata_8031DDA0,
    (const char *)NameCheck_CardName_rodata_8031DDAC,
    (const char *)NameCheck_CardName_rodata_8031DDB8,
    (const char *)NameCheck_CardName_rodata_8031DDC4,
    (const char *)NameCheck_CardName_rodata_8031DDD0,
    (const char *)NameCheck_CardName_rodata_8031DDDC,
    (const char *)NameCheck_CardName_rodata_8031DDE8,
    (const char *)NameCheck_CardName_rodata_8031DDF4,
    (const char *)NameCheck_CardName_rodata_8031DE00,
    (const char *)NameCheck_CardName_rodata_8031DE0C,
    (const char *)NameCheck_CardName_rodata_8031DE18,
    (const char *)NameCheck_CardName_rodata_8031DE24,
    (const char *)NameCheck_CardName_rodata_8031DE30,
    (const char *)NameCheck_CardName_rodata_8031DE3C,
    (const char *)NameCheck_CardName_rodata_8031DE48,
    (const char *)NameCheck_CardName_rodata_8031DE54,
    (const char *)NameCheck_CardName_rodata_8031DE60,
    (const char *)NameCheck_CardName_rodata_8031DE6C,
    (const char *)NameCheck_CardName_rodata_8031DE78,
    (const char *)NameCheck_CardName_rodata_8031DE84,
    (const char *)NameCheck_CardName_rodata_8031DE90,
    (const char *)NameCheck_CardName_rodata_8031DE9C,
    (const char *)NameCheck_CardName_rodata_8031DEA8,
    (const char *)NameCheck_CardName_rodata_8031DEB4,
    (const char *)NameCheck_CardName_rodata_8031DEC0,
    (const char *)NameCheck_CardName_rodata_8031DECC,
    (const char *)NameCheck_CardName_rodata_8031DED8,
    (const char *)NameCheck_CardName_rodata_8031DEE4,
    (const char *)NameCheck_CardName_rodata_8031DEF0,
    (const char *)NameCheck_CardName_rodata_8031DEFC,
    (const char *)NameCheck_CardName_rodata_8031DF08,
    (const char *)NameCheck_CardName_rodata_8031DF14,
    (const char *)NameCheck_CardName_rodata_8031DF20,
    (const char *)NameCheck_CardName_rodata_8031DF2C,
    (const char *)NameCheck_CardName_rodata_8031DF38,
    (const char *)NameCheck_CardName_rodata_8031DF44,
    (const char *)NameCheck_CardName_rodata_8031DF50,
    (const char *)NameCheck_CardName_rodata_8031DF5C,
    (const char *)NameCheck_CardName_rodata_8031DF68,
    (const char *)NameCheck_CardName_rodata_8031DF74,
    (const char *)NameCheck_CardName_rodata_8031DF80,
    (const char *)NameCheck_CardName_rodata_8031DF8C,
    (const char *)NameCheck_CardName_rodata_8031DF98,
    (const char *)NameCheck_CardName_rodata_8031DFA4,
    (const char *)NameCheck_CardName_rodata_8031DFB0,
    (const char *)NameCheck_CardName_rodata_8031DFBC,
    (const char *)NameCheck_CardName_rodata_8031DFC8,
    (const char *)NameCheck_CardName_rodata_8031DFD4,
    (const char *)NameCheck_CardName_rodata_8031DFE0,
    (const char *)NameCheck_CardName_rodata_8031DFEC,
    (const char *)NameCheck_CardName_rodata_8031DFF8,
    (const char *)NameCheck_CardName_rodata_8031E004,
    (const char *)NameCheck_CardName_rodata_8031E010,
    (const char *)NameCheck_CardName_rodata_8031E01C,
    (const char *)NameCheck_CardName_rodata_8031E028,
    (const char *)NameCheck_CardName_rodata_8031E034,
    (const char *)NameCheck_CardName_rodata_8031E040,
    (const char *)NameCheck_CardName_rodata_8031E04C,
    (const char *)NameCheck_CardName_rodata_8031E058,
    (const char *)NameCheck_CardName_rodata_8031E064,
    (const char *)NameCheck_CardName_rodata_8031E070,
    (const char *)NameCheck_CardName_rodata_8031E07C,
    (const char *)NameCheck_CardName_rodata_8031E088,
    (const char *)NameCheck_CardName_rodata_8031E094,
    (const char *)NameCheck_CardName_rodata_8031E0A0,
    (const char *)NameCheck_CardName_rodata_8031E0AC,
    (const char *)NameCheck_CardName_rodata_8031E0B8,
    (const char *)NameCheck_CardName_rodata_8031E0C4,
    (const char *)NameCheck_CardName_rodata_8031E0D0,
    (const char *)NameCheck_CardName_rodata_8031E0DC,
    (const char *)NameCheck_CardName_rodata_8031E0E8,
    (const char *)NameCheck_CardName_rodata_8031E0F4,
    (const char *)NameCheck_CardName_rodata_8031E100,
    (const char *)NameCheck_CardName_rodata_8031E10C,
    (const char *)NameCheck_CardName_rodata_8031E118,
    (const char *)NameCheck_CardName_rodata_8031E124,
    (const char *)NameCheck_CardName_rodata_8031E130,
    (const char *)NameCheck_CardName_rodata_8031E13C,
    (const char *)NameCheck_CardName_rodata_8031E148,
    (const char *)NameCheck_CardName_rodata_8031E154,
    (const char *)NameCheck_CardName_rodata_8031E160,
    (const char *)NameCheck_CardName_rodata_8031E16C,
    (const char *)NameCheck_CardName_rodata_8031E178,
    (const char *)NameCheck_CardName_rodata_8031E184,
    (const char *)NameCheck_CardName_rodata_8031E190,
    (const char *)NameCheck_CardName_rodata_8031E19C,
    (const char *)NameCheck_CardName_rodata_8031E1A8,
    (const char *)NameCheck_CardName_rodata_8031E1B4,
    (const char *)NameCheck_CardName_rodata_8031E1C0,
    (const char *)NameCheck_CardName_rodata_8031E1CC,
    (const char *)NameCheck_CardName_rodata_8031E1D8,
    (const char *)NameCheck_CardName_rodata_8031E1E4,
    (const char *)NameCheck_CardName_rodata_8031E1F0,
    (const char *)NameCheck_CardName_rodata_8031E1FC,
    (const char *)NameCheck_CardName_rodata_8031E208,
    (const char *)NameCheck_CardName_rodata_8031E214,
    (const char *)NameCheck_CardName_rodata_8031E220,
    (const char *)NameCheck_CardName_rodata_8031E22C,
    (const char *)NameCheck_CardName_rodata_8031E238,
    (const char *)NameCheck_CardName_rodata_8031E244,
    (const char *)NameCheck_CardName_rodata_8031E250,
    (const char *)NameCheck_CardName_rodata_8031E25C,
    (const char *)NameCheck_CardName_rodata_8031E268,
    (const char *)NameCheck_CardName_rodata_8031E274,
    (const char *)NameCheck_CardName_rodata_8031E280,
    (const char *)NameCheck_CardName_rodata_8031E28C,
    (const char *)NameCheck_CardName_rodata_8031E298,
    (const char *)NameCheck_CardName_rodata_8031E2A4,
    (const char *)NameCheck_CardName_rodata_8031E2B0,
    (const char *)NameCheck_CardName_rodata_8031E2BC,
    (const char *)NameCheck_CardName_rodata_8031E2C8,
    (const char *)NameCheck_CardName_rodata_8031E2D4,
    (const char *)NameCheck_CardName_rodata_8031E2E0,
    (const char *)NameCheck_CardName_rodata_8031E2EC,
    (const char *)NameCheck_CardName_rodata_8031E2F8,
    (const char *)NameCheck_CardName_rodata_8031E304,
    (const char *)NameCheck_CardName_rodata_8031E310,
    (const char *)NameCheck_CardName_rodata_8031E31C,
    (const char *)NameCheck_CardName_rodata_8031E328,
    (const char *)NameCheck_CardName_rodata_8031E334,
    (const char *)NameCheck_CardName_rodata_8031E340,
    (const char *)NameCheck_CardName_rodata_8031E34C,
    (const char *)NameCheck_CardName_rodata_8031E358,
    (const char *)NameCheck_CardName_rodata_8031E364,
    (const char *)NameCheck_CardName_rodata_8031E370,
    (const char *)NameCheck_CardName_rodata_8031E37C,
    (const char *)NameCheck_CardName_rodata_8031E388,
    (const char *)NameCheck_CardName_rodata_8031E394,
    (const char *)NameCheck_CardName_rodata_8031E3A0,
    (const char *)NameCheck_CardName_rodata_8031E3AC,
    (const char *)NameCheck_CardName_rodata_8031E3B8,
    (const char *)NameCheck_CardName_rodata_8031E3C4,
    (const char *)NameCheck_CardName_rodata_8031E3D0,
    (const char *)NameCheck_CardName_rodata_8031E3DC,
    (const char *)NameCheck_CardName_rodata_8031E3E8,
    (const char *)NameCheck_CardName_rodata_8031E3F4,
    (const char *)NameCheck_CardName_rodata_8031E400,
    (const char *)NameCheck_CardName_rodata_8031E40C,
    (const char *)NameCheck_CardName_rodata_8031E418,
    (const char *)NameCheck_CardName_rodata_8031E424,
    (const char *)NameCheck_CardName_rodata_8031E430,
    (const char *)NameCheck_CardName_rodata_8031E43C,
    (const char *)NameCheck_CardName_rodata_8031E448,
    (const char *)NameCheck_CardName_rodata_8031E454,
    (const char *)NameCheck_CardName_rodata_8031E460,
    (const char *)NameCheck_CardName_rodata_8031E46C,
    (const char *)NameCheck_CardName_rodata_8031E478,
    (const char *)NameCheck_CardName_rodata_8031E484,
    (const char *)NameCheck_CardName_rodata_8031E490,
    (const char *)NameCheck_CardName_rodata_8031E49C,
    (const char *)NameCheck_CardName_rodata_8031E4A8,
    (const char *)NameCheck_CardName_rodata_8031E4B4,
    (const char *)NameCheck_CardName_rodata_8031E4C0,
    (const char *)NameCheck_CardName_rodata_8031E4CC,
    (const char *)NameCheck_CardName_rodata_8031E4D8,
    (const char *)NameCheck_CardName_rodata_8031E4E4,
    (const char *)NameCheck_CardName_rodata_8031E4F0,
    (const char *)NameCheck_CardName_rodata_8031E4FC,
    (const char *)NameCheck_CardName_rodata_8031E508,
    (const char *)NameCheck_CardName_rodata_8031E514,
    (const char *)NameCheck_CardName_rodata_8031E520,
    (const char *)NameCheck_CardName_rodata_8031E52C,
    (const char *)NameCheck_CardName_rodata_8031E538,
    (const char *)NameCheck_CardName_rodata_8031E544,
    (const char *)NameCheck_CardName_rodata_8031E550,
    (const char *)NameCheck_CardName_rodata_8031E55C,
    (const char *)NameCheck_CardName_rodata_8031E568,
    (const char *)NameCheck_CardName_rodata_8031E574,
    (const char *)NameCheck_CardName_rodata_8031E580,
    (const char *)lbl_806D3C8C,
    (const char *)lbl_806D3C94,
    (const char *)lbl_806D3C9C,
    (const char *)lbl_806D3CA4,
    (const char *)lbl_806D3CAC,
    (const char *)lbl_806D3CB4,
    (const char *)lbl_806D3CBC,
    (const char *)lbl_806D3CC4,
    (const char *)lbl_806D3CCC,
    (const char *)lbl_806D3CD4,
    (const char *)lbl_806D3CDC,
    (const char *)lbl_806D3CE4,
    (const char *)lbl_806D3CEC,
    (const char *)lbl_806D3CF4,
    (const char *)lbl_806D3CFC,
    (const char *)lbl_806D3D04,
    (const char *)lbl_806D3D0C,
    (const char *)lbl_806D3D14,
    (const char *)lbl_806D3D1C,
    (const char *)lbl_806D3D24,
    (const char *)lbl_806D3D2C,
    (const char *)lbl_806D3D34,
    (const char *)lbl_806D3D3C,
    (const char *)lbl_806D3D44,
    (const char *)lbl_806D3D4C,
    (const char *)lbl_806D3D54,
    (const char *)lbl_806D3D5C,
    (const char *)lbl_806D3D64,
    (const char *)lbl_806D3D6C,
    (const char *)lbl_806D3D74,
    (const char *)lbl_806D3D7C,
    (const char *)lbl_806D3D84,
    (const char *)lbl_806D3D8C,
    (const char *)lbl_806D3D94,
    (const char *)lbl_806D3D9C,
    (const char *)lbl_806D3DA4,
    (const char *)lbl_806D3DAC,
    (const char *)lbl_806D3DB4,
    (const char *)lbl_806D3DBC,
    (const char *)lbl_806D3DC4,
    (const char *)lbl_806D3DCC,
    (const char *)lbl_806D3DD4,
    (const char *)lbl_806D3DDC,
    (const char *)lbl_806D3DE4,
    (const char *)lbl_806D3DEC,
    (const char *)lbl_806D3DF4,
    (const char *)lbl_806D3DFC,
    (const char *)lbl_806D3E04,
    (const char *)lbl_806D3E0C,
    (const char *)lbl_806D3E14,
    (const char *)lbl_806D3E1C,
    (const char *)lbl_806D3E24,
    (const char *)lbl_806D3E2C,
    (const char *)lbl_806D3E34,
    (const char *)lbl_806D3E3C,
    (const char *)lbl_806D3E44,
    (const char *)lbl_806D3E4C,
    (const char *)lbl_806D3E54,
    (const char *)lbl_806D3E5C,
    (const char *)lbl_806D3E64,
    (const char *)lbl_806D3E6C,
    (const char *)lbl_806D3E74,
    (const char *)lbl_806D3E7C,
    (const char *)lbl_806D3E84,
    (const char *)lbl_806D3E8C,
    (const char *)lbl_806D3E94,
    (const char *)lbl_806D3E9C,
    (const char *)lbl_806D3EA4,
    (const char *)lbl_806D3EAC,
    (const char *)lbl_806D3EB4,
    (const char *)lbl_806D3EBC,
    (const char *)lbl_806D3EC4,
    (const char *)lbl_806D3ECC,
    (const char *)lbl_806D3ED4,
    (const char *)lbl_806D3EDC,
    (const char *)lbl_806D3EE4,
    (const char *)lbl_806D3EEC,
    (const char *)lbl_806D3EF4,
    (const char *)lbl_806D3EFC,
    (const char *)lbl_806D3F04,
    (const char *)lbl_806D3F0C,
    (const char *)lbl_806D3F14,
    (const char *)lbl_806D3F1C,
    (const char *)lbl_806D3F24,
    (const char *)lbl_806D3F2C,
    (const char *)lbl_806D3F34,
    (const char *)lbl_806D3F3C,
    (const char *)lbl_806D3F44,
    (const char *)lbl_806D3F4C,
    (const char *)lbl_806D3F54,
    (const char *)lbl_806D3F5C,
    (const char *)lbl_806D3F64,
    (const char *)lbl_806D3F6C,
    (const char *)lbl_806D3F74,
    (const char *)lbl_806D3F7C,
    (const char *)lbl_806D3F84,
    (const char *)lbl_806D3F8C,
    (const char *)lbl_806D3F94,
    (const char *)lbl_806D3F9C,
    (const char *)lbl_806D3FA4,
    (const char *)lbl_806D3FAC,
    (const char *)lbl_806D3FB4,
    (const char *)lbl_806D3FBC,
    (const char *)lbl_806D3FC4,
    (const char *)lbl_806D3FCC,
    (const char *)lbl_806D3FD4,
    (const char *)lbl_806D3FDC,
    (const char *)lbl_806D3FE4,
    (const char *)lbl_806D3FEC,
    (const char *)lbl_806D3FF4,
    (const char *)lbl_806D3FFC,
    (const char *)lbl_806D4004,
    (const char *)lbl_806D400C,
    (const char *)lbl_806D4014,
    (const char *)lbl_806D401C,
    (const char *)lbl_806D4024,
    (const char *)lbl_806D402C,
    (const char *)lbl_806D4034,
    (const char *)lbl_806D403C,
    (const char *)lbl_806D4044,
    (const char *)lbl_806D404C,
    (const char *)lbl_806D4054,
    (const char *)lbl_806D405C,
    (const char *)lbl_806D4064,
    (const char *)lbl_806D406C,
    (const char *)lbl_806D4074,
    (const char *)lbl_806D407C,
    (const char *)lbl_806D4084,
    (const char *)lbl_806D408C,
    (const char *)lbl_806D4094,
    (const char *)lbl_806D409C,
    (const char *)lbl_806D40A4,
    (const char *)lbl_806D40AC,
    (const char *)lbl_806D40B4,
    (const char *)lbl_806D40BC,
    (const char *)lbl_806D40C4,
    (const char *)lbl_806D40CC,
    (const char *)lbl_806D40D4,
    (const char *)lbl_806D40DC,
    (const char *)lbl_806D40E4,
    (const char *)lbl_806D40EC,
    (const char *)lbl_806D40F4,
    (const char *)lbl_806D40FC,
    (const char *)lbl_806D4104,
    (const char *)lbl_806D410C,
    (const char *)lbl_806D4114,
    (const char *)lbl_806D411C,
    (const char *)lbl_806D4124,
    (const char *)lbl_806D412C,
    (const char *)lbl_806D4134,
    (const char *)lbl_806D413C,
    (const char *)lbl_806D4144,
    (const char *)lbl_806D414C,
    (const char *)lbl_806D4154,
    (const char *)lbl_806D415C,
    (const char *)lbl_806D4164,
    (const char *)lbl_806D416C,
    (const char *)lbl_806D4174,
    (const char *)lbl_806D417C,
    (const char *)lbl_806D4184,
    (const char *)lbl_806D418C,
    (const char *)lbl_806D4194,
    (const char *)lbl_806D419C,
    (const char *)lbl_806D41A4,
    (const char *)lbl_806D41AC,
    (const char *)lbl_806D41B4,
    (const char *)lbl_806D41BC,
    (const char *)lbl_806D41C4,
    (const char *)lbl_806D41CC,
    (const char *)lbl_806D41D4,
    (const char *)lbl_806D41DC,
    (const char *)lbl_806D41E4,
    (const char *)lbl_806D41EC,
    (const char *)lbl_806D41F4,
    (const char *)lbl_806D41FC,
    (const char *)lbl_806D4204,
    (const char *)lbl_806D420C,
    (const char *)lbl_806D4214,
    (const char *)lbl_806D421C,
    (const char *)lbl_806D4224,
    (const char *)lbl_806D422C,
    (const char *)lbl_806D4234,
    (const char *)lbl_806D423C,
    (const char *)lbl_806D4244,
    (const char *)lbl_806D424C,
    (const char *)lbl_806D4254,
    (const char *)lbl_806D425C,
    (const char *)lbl_806D4264,
    (const char *)lbl_806D426C,
    (const char *)lbl_806D4274,
    (const char *)lbl_806D427C,
    (const char *)lbl_806D4284,
    (const char *)lbl_806D428C,
    (const char *)lbl_806D4294,
    (const char *)lbl_806D429C,
    (const char *)lbl_806D42A4,
    (const char *)lbl_806D42AC,
    (const char *)lbl_806D42B4,
    (const char *)lbl_806D42BC,
    (const char *)lbl_806D42C4,
    (const char *)lbl_806D42CC,
    (const char *)lbl_806D42D4,
    (const char *)lbl_806D42DC,
    (const char *)lbl_806D42E4,
    (const char *)lbl_806D42EC,
    (const char *)NameCheck_CardName_rodata_8031E58C,
    (const char *)NameCheck_CardName_rodata_8031E598,
    (const char *)NameCheck_CardName_rodata_8031E5A4,
    (const char *)NameCheck_CardName_rodata_8031E5B0,
    (const char *)NameCheck_CardName_rodata_8031E5BC,
    (const char *)NameCheck_CardName_rodata_8031E5C8,
    (const char *)NameCheck_CardName_rodata_8031E5D4,
    (const char *)NameCheck_CardName_rodata_8031E5E0,
    (const char *)NameCheck_CardName_rodata_8031E5EC,
    (const char *)NameCheck_CardName_rodata_8031E5F8,
    (const char *)NameCheck_CardName_rodata_8031E604,
    (const char *)NameCheck_CardName_rodata_8031E610,
    (const char *)NameCheck_CardName_rodata_8031E61C,
    (const char *)NameCheck_CardName_rodata_8031E628,
    (const char *)NameCheck_CardName_rodata_8031E634,
    (const char *)NameCheck_CardName_rodata_8031E640,
    (const char *)NameCheck_CardName_rodata_8031E64C,
    (const char *)NameCheck_CardName_rodata_8031E658,
    (const char *)NameCheck_CardName_rodata_8031E664,
    (const char *)NameCheck_CardName_rodata_8031E670,
    (const char *)NameCheck_CardName_rodata_8031E67C,
    (const char *)NameCheck_CardName_rodata_8031E67C,
    (const char *)NameCheck_CardName_rodata_8031E688,
    (const char *)NameCheck_CardName_rodata_8031E694,
    (const char *)NameCheck_CardName_rodata_8031E6A0,
    (const char *)NameCheck_CardName_rodata_8031E6AC,
    (const char *)NameCheck_CardName_rodata_8031E6B8,
    (const char *)NameCheck_CardName_rodata_8031E6C4,
    (const char *)NameCheck_CardName_rodata_8031E6D0,
    (const char *)NameCheck_CardName_rodata_8031E6DC,
    (const char *)NameCheck_CardName_rodata_8031E6E8,
    (const char *)NameCheck_CardName_rodata_8031E6F4,
    (const char *)NameCheck_CardName_rodata_8031E700,
    (const char *)NameCheck_CardName_rodata_8031E70C,
    (const char *)NameCheck_CardName_rodata_8031E718,
    (const char *)NameCheck_CardName_rodata_8031E718,
    (const char *)NameCheck_CardName_rodata_8031E724,
    (const char *)NameCheck_CardName_rodata_8031E724,
    (const char *)NameCheck_CardName_rodata_8031E730,
    (const char *)NameCheck_CardName_rodata_8031E73C,
    (const char *)NameCheck_CardName_rodata_8031E748,
    (const char *)NameCheck_CardName_rodata_8031E754,
    (const char *)NameCheck_CardName_rodata_8031E760,
    (const char *)NameCheck_CardName_rodata_8031E76C,
    (const char *)NameCheck_CardName_rodata_8031E778,
    (const char *)NameCheck_CardName_rodata_8031E784,
    (const char *)NameCheck_CardName_rodata_8031E790,
    (const char *)NameCheck_CardName_rodata_8031E79C,
    (const char *)NameCheck_CardName_rodata_8031E7A8,
    (const char *)NameCheck_CardName_rodata_8031E7B4,
    (const char *)NameCheck_CardName_rodata_8031E7C0,
    (const char *)NameCheck_CardName_rodata_8031E7CC,
    (const char *)NameCheck_CardName_rodata_8031E7D8,
    (const char *)NameCheck_CardName_rodata_8031E7E4,
    (const char *)NameCheck_CardName_rodata_8031E7F0,
    (const char *)NameCheck_CardName_rodata_8031E7FC,
    (const char *)NameCheck_CardName_rodata_8031E808,
    (const char *)NameCheck_CardName_rodata_8031E814,
    (const char *)NameCheck_CardName_rodata_8031E820,
    (const char *)NameCheck_CardName_rodata_8031E82C,
    (const char *)NameCheck_CardName_rodata_8031E838,
    (const char *)NameCheck_CardName_rodata_8031E844,
    (const char *)NameCheck_CardName_rodata_8031E850,
    (const char *)NameCheck_CardName_rodata_8031E85C,
    (const char *)NameCheck_CardName_rodata_8031E868,
    (const char *)NameCheck_CardName_rodata_8031E874,
    (const char *)NameCheck_CardName_rodata_8031E880,
    (const char *)NameCheck_CardName_rodata_8031E88C,
    (const char *)NameCheck_CardName_rodata_8031E898,
    (const char *)NameCheck_CardName_rodata_8031E8A4,
    (const char *)NameCheck_CardName_rodata_8031E8B0,
    (const char *)NameCheck_CardName_rodata_8031E8BC,
    (const char *)NameCheck_CardName_rodata_8031E8C8,
    (const char *)NameCheck_CardName_rodata_8031E8D4,
    (const char *)NameCheck_CardName_rodata_8031E8E0,
    (const char *)NameCheck_CardName_rodata_8031E8EC,
    (const char *)NameCheck_CardName_rodata_8031E8F8,
    (const char *)NameCheck_CardName_rodata_8031E904,
    (const char *)NameCheck_CardName_rodata_8031E910,
    (const char *)NameCheck_CardName_rodata_8031E91C,
    (const char *)NameCheck_CardName_rodata_8031E928,
    (const char *)NameCheck_CardName_rodata_8031E934,
    (const char *)NameCheck_CardName_rodata_8031E940,
    (const char *)NameCheck_CardName_rodata_8031E94C,
    (const char *)NameCheck_CardName_rodata_8031E958,
    (const char *)NameCheck_CardName_rodata_8031E964,
    (const char *)NameCheck_CardName_rodata_8031E970,
    (const char *)NameCheck_CardName_rodata_8031E97C,
    (const char *)NameCheck_CardName_rodata_8031E988,
    (const char *)NameCheck_CardName_rodata_8031E994,
    (const char *)NameCheck_CardName_rodata_8031E9A0,
    (const char *)NameCheck_CardName_rodata_8031E9AC,
    (const char *)NameCheck_CardName_rodata_8031E9B8,
    (const char *)NameCheck_CardName_rodata_8031E9C4,
    (const char *)NameCheck_CardName_rodata_8031E9D0,
    (const char *)NameCheck_CardName_rodata_8031E9DC,
    (const char *)NameCheck_CardName_rodata_8031E9E8,
    (const char *)NameCheck_CardName_rodata_8031E9F4,
    (const char *)NameCheck_CardName_rodata_8031EA00,
    (const char *)NameCheck_CardName_rodata_8031EA0C,
    (const char *)NameCheck_CardName_rodata_8031EA18,
    (const char *)NameCheck_CardName_rodata_8031EA24,
    (const char *)NameCheck_CardName_rodata_8031EA30,
    (const char *)NameCheck_CardName_rodata_8031EA3C,
    (const char *)NameCheck_CardName_rodata_8031EA48,
    (const char *)NameCheck_CardName_rodata_8031EA54,
    (const char *)NameCheck_CardName_rodata_8031EA60,
    (const char *)NameCheck_CardName_rodata_8031EA6C,
    (const char *)NameCheck_CardName_rodata_8031EA78,
    (const char *)NameCheck_CardName_rodata_8031EA84,
    (const char *)NameCheck_CardName_rodata_8031EA90,
    (const char *)NameCheck_CardName_rodata_8031EA9C,
    (const char *)NameCheck_CardName_rodata_8031EAA8,
    (const char *)NameCheck_CardName_rodata_8031EAB4,
    (const char *)NameCheck_CardName_rodata_8031EAC0,
    (const char *)NameCheck_CardName_rodata_8031EACC,
    (const char *)NameCheck_CardName_rodata_8031EAD8,
    (const char *)NameCheck_CardName_rodata_8031EAE4,
    (const char *)NameCheck_CardName_rodata_8031EAF0,
    (const char *)NameCheck_CardName_rodata_8031EAFC,
    (const char *)NameCheck_CardName_rodata_8031EB08,
    (const char *)NameCheck_CardName_rodata_8031EB14,
    (const char *)NameCheck_CardName_rodata_8031EB20,
    (const char *)NameCheck_CardName_rodata_8031EB2C,
    (const char *)NameCheck_CardName_rodata_8031EB38,
    (const char *)NameCheck_CardName_rodata_8031EB44,
    (const char *)NameCheck_CardName_rodata_8031EB50,
    (const char *)NameCheck_CardName_rodata_8031EB5C,
    (const char *)NameCheck_CardName_rodata_8031EB68,
    (const char *)NameCheck_CardName_rodata_8031EB74,
    (const char *)NameCheck_CardName_rodata_8031EB80,
    (const char *)NameCheck_CardName_rodata_8031EB8C,
    (const char *)NameCheck_CardName_rodata_8031EB98,
    (const char *)NameCheck_CardName_rodata_8031EBA4,
    (const char *)NameCheck_CardName_rodata_8031EBB0,
    (const char *)NameCheck_CardName_rodata_8031EBBC,
    (const char *)NameCheck_CardName_rodata_8031EBC8,
    (const char *)NameCheck_CardName_rodata_8031EBD4,
    (const char *)NameCheck_CardName_rodata_8031EBE0,
    (const char *)NameCheck_CardName_rodata_8031EBEC,
    (const char *)NameCheck_CardName_rodata_8031EBF8,
    (const char *)NameCheck_CardName_rodata_8031EC04,
    (const char *)NameCheck_CardName_rodata_8031EC10,
    (const char *)NameCheck_CardName_rodata_8031EC1C,
    (const char *)NameCheck_CardName_rodata_8031EC28,
    (const char *)NameCheck_CardName_rodata_8031EC34,
    (const char *)NameCheck_CardName_rodata_8031EC40,
    (const char *)NameCheck_CardName_rodata_8031EC4C,
    (const char *)NameCheck_CardName_rodata_8031EC58,
    (const char *)NameCheck_CardName_rodata_8031EC64,
    (const char *)NameCheck_CardName_rodata_8031EC70,
    (const char *)NameCheck_CardName_rodata_8031EC7C,
    (const char *)NameCheck_CardName_rodata_8031EC88,
    (const char *)NameCheck_CardName_rodata_8031EC94,
    (const char *)NameCheck_CardName_rodata_8031ECA0,
    (const char *)NameCheck_CardName_rodata_8031ECAC,
    (const char *)NameCheck_CardName_rodata_8031ECB8,
    (const char *)NameCheck_CardName_rodata_8031ECC4,
    (const char *)NameCheck_CardName_rodata_8031ECD0,
    (const char *)NameCheck_CardName_rodata_8031ECDC,
    (const char *)NameCheck_CardName_rodata_8031ECE8,
    (const char *)NameCheck_CardName_rodata_8031ECF4,
    (const char *)NameCheck_CardName_rodata_8031ED00,
    (const char *)NameCheck_CardName_rodata_8031ED0C,
    (const char *)NameCheck_CardName_rodata_8031ED18,
    (const char *)NameCheck_CardName_rodata_8031ED24,
    (const char *)NameCheck_CardName_rodata_8031ED30,
    (const char *)NameCheck_CardName_rodata_8031ED3C,
    (const char *)NameCheck_CardName_rodata_8031ED48,
    (const char *)NameCheck_CardName_rodata_8031ED54,
    (const char *)NameCheck_CardName_rodata_8031ED60,
    (const char *)NameCheck_CardName_rodata_8031ED6C,
    (const char *)NameCheck_CardName_rodata_8031ED78,
    (const char *)NameCheck_CardName_rodata_8031ED84,
    (const char *)NameCheck_CardName_rodata_8031ED90,
    (const char *)NameCheck_CardName_rodata_8031ED9C,
    (const char *)NameCheck_CardName_rodata_8031EDA8,
    (const char *)NameCheck_CardName_rodata_8031EDB4,
    (const char *)NameCheck_CardName_rodata_8031EDC0,
    (const char *)NameCheck_CardName_rodata_8031EDCC,
    (const char *)NameCheck_CardName_rodata_8031EDD8,
    (const char *)NameCheck_CardName_rodata_8031EDE4,
    (const char *)NameCheck_CardName_rodata_8031EDF0,
    (const char *)NameCheck_CardName_rodata_8031EDFC,
    (const char *)NameCheck_CardName_rodata_8031EE08,
    (const char *)NameCheck_CardName_rodata_8031EE14,
    (const char *)NameCheck_CardName_rodata_8031EE20,
    (const char *)NameCheck_CardName_rodata_8031EE2C,
    (const char *)NameCheck_CardName_rodata_8031EE38,
    (const char *)NameCheck_CardName_rodata_8031EE44,
    (const char *)NameCheck_CardName_rodata_8031EE50,
    (const char *)NameCheck_CardName_rodata_8031EE5C,
    (const char *)NameCheck_CardName_rodata_8031EE68,
    (const char *)NameCheck_CardName_rodata_8031EE74,
    (const char *)NameCheck_CardName_rodata_8031EE80,
    (const char *)NameCheck_CardName_rodata_8031EE8C,
    (const char *)NameCheck_CardName_rodata_8031EE98,
    (const char *)NameCheck_CardName_rodata_8031EEA4,
    (const char *)lbl_806D42F4,
    (const char *)lbl_806D42FC,
    (const char *)lbl_806D4304,
    (const char *)lbl_806D430C,
    (const char *)lbl_806D4314,
    (const char *)lbl_806D431C,
    (const char *)lbl_806D4324,
    (const char *)lbl_806D432C,
    (const char *)lbl_806D4334,
    (const char *)lbl_806D433C,
    (const char *)lbl_806D4344,
    (const char *)lbl_806D434C,
    (const char *)lbl_806D4354,
    (const char *)lbl_806D435C,
    (const char *)lbl_806D4364,
    (const char *)lbl_806D436C,
    (const char *)lbl_806D4374,
    (const char *)lbl_806D437C,
    (const char *)lbl_806D4384,
    (const char *)lbl_806D438C,
    (const char *)lbl_806D4394,
    (const char *)lbl_806D439C,
    (const char *)lbl_806D43A4,
    (const char *)lbl_806D43AC,
    (const char *)lbl_806D43B4,
    (const char *)lbl_806D43BC,
    (const char *)lbl_806D43C4,
    (const char *)lbl_806D43CC,
    (const char *)lbl_806D43D4,
    (const char *)lbl_806D43DC,
    (const char *)lbl_806D43E4,
    (const char *)lbl_806D43EC,
    (const char *)lbl_806D43F4,
    (const char *)lbl_806D43FC,
    (const char *)lbl_806D4404,
    (const char *)lbl_806D440C,
    (const char *)lbl_806D4414,
    (const char *)lbl_806D441C,
    (const char *)lbl_806D4424,
    (const char *)lbl_806D442C,
    (const char *)lbl_806D4434,
    (const char *)lbl_806D443C,
    (const char *)lbl_806D4444,
    (const char *)lbl_806D444C,
    (const char *)lbl_806D4454,
    (const char *)lbl_806D445C,
    (const char *)lbl_806D4464,
    (const char *)lbl_806D446C,
    (const char *)lbl_806D4474,
    (const char *)lbl_806D447C,
    (const char *)lbl_806D4484,
    (const char *)lbl_806D448C,
    (const char *)lbl_806D4494,
    (const char *)lbl_806D449C,
    (const char *)lbl_806D44A4,
    (const char *)lbl_806D44AC,
    (const char *)lbl_806D44B4,
    (const char *)lbl_806D44BC,
    (const char *)lbl_806D44C4,
    (const char *)lbl_806D44CC,
    (const char *)lbl_806D44D4,
    (const char *)NameCheck_CardName_rodata_8031EEB0,
    (const char *)NameCheck_CardName_rodata_8031EEBC,
    (const char *)NameCheck_CardName_rodata_8031EEC8,
    (const char *)NameCheck_CardName_rodata_8031EED4,
    (const char *)NameCheck_CardName_rodata_8031EEE0,
    (const char *)NameCheck_CardName_rodata_8031EEEC,
    (const char *)NameCheck_CardName_rodata_8031EEF8,
    (const char *)NameCheck_CardName_rodata_8031EF04,
    (const char *)NameCheck_CardName_rodata_8031EF10,
    (const char *)NameCheck_CardName_rodata_8031EF1C,
    (const char *)NameCheck_CardName_rodata_8031EF28,
    (const char *)NameCheck_CardName_rodata_8031EF34,
    (const char *)NameCheck_CardName_rodata_8031EF40,
    (const char *)NameCheck_CardName_rodata_8031EF4C,
    (const char *)NameCheck_CardName_rodata_8031EF58,
    (const char *)NameCheck_CardName_rodata_8031EF64,
    (const char *)NameCheck_CardName_rodata_8031EF70,
    (const char *)NameCheck_CardName_rodata_8031EF7C,
    (const char *)NameCheck_CardName_rodata_8031EF88,
    (const char *)NameCheck_CardName_rodata_8031EF94,
    (const char *)NameCheck_CardName_rodata_8031EFA0,
    (const char *)NameCheck_CardName_rodata_8031EFAC,
    (const char *)NameCheck_CardName_rodata_8031EFB8,
    (const char *)NameCheck_CardName_rodata_8031EFC4,
    (const char *)NameCheck_CardName_rodata_8031EFD0,
    (const char *)NameCheck_CardName_rodata_8031EFDC,
    (const char *)NameCheck_CardName_rodata_8031EFE8,
    (const char *)NameCheck_CardName_rodata_8031EFF4,
    (const char *)NameCheck_CardName_rodata_8031F000,
    (const char *)NameCheck_CardName_rodata_8031F00C,
    (const char *)NameCheck_CardName_rodata_8031F018,
    (const char *)NameCheck_CardName_rodata_8031F024,
    (const char *)NameCheck_CardName_rodata_8031F030,
    (const char *)NameCheck_CardName_rodata_8031F03C,
    (const char *)NameCheck_CardName_rodata_8031F048,
    (const char *)NameCheck_CardName_rodata_8031F054,
    (const char *)NameCheck_CardName_rodata_8031F060,
    (const char *)NameCheck_CardName_rodata_8031F06C,
    (const char *)NameCheck_CardName_rodata_8031F078,
    (const char *)NameCheck_CardName_rodata_8031F084,
    (const char *)NameCheck_CardName_rodata_8031F090,
    (const char *)NameCheck_CardName_rodata_8031F09C,
    (const char *)NameCheck_CardName_rodata_8031F0A8,
    (const char *)NameCheck_CardName_rodata_8031F0B4,
    (const char *)NameCheck_CardName_rodata_8031F0C0,
    (const char *)NameCheck_CardName_rodata_8031F0CC,
    (const char *)NameCheck_CardName_rodata_8031F0D8,
    (const char *)NameCheck_CardName_rodata_8031F0E4,
    (const char *)NameCheck_CardName_rodata_8031F0F0,
    (const char *)NameCheck_CardName_rodata_8031F0FC,
    (const char *)NameCheck_CardName_rodata_8031F108,
    (const char *)NameCheck_CardName_rodata_8031F114,
    (const char *)NameCheck_CardName_rodata_8031F120,
    (const char *)NameCheck_CardName_rodata_8031F12C,
    (const char *)NameCheck_CardName_rodata_8031F138,
    (const char *)NameCheck_CardName_rodata_8031F144,
    (const char *)NameCheck_CardName_rodata_8031F150,
    (const char *)NameCheck_CardName_rodata_8031F15C,
    (const char *)NameCheck_CardName_rodata_8031F168,
    (const char *)NameCheck_CardName_rodata_8031F174,
    (const char *)NameCheck_CardName_rodata_8031F180,
    (const char *)NameCheck_CardName_rodata_8031F18C,
    (const char *)NameCheck_CardName_rodata_8031F198,
    (const char *)NameCheck_CardName_rodata_8031F1A4,
    (const char *)NameCheck_CardName_rodata_8031F1B0,
    (const char *)NameCheck_CardName_rodata_8031F1BC,
    (const char *)NameCheck_CardName_rodata_8031F1C8,
    (const char *)NameCheck_CardName_rodata_8031F1D4,
    (const char *)NameCheck_CardName_rodata_8031F1E0,
    (const char *)NameCheck_CardName_rodata_8031F1EC,
    (const char *)NameCheck_CardName_rodata_8031F1F8,
    (const char *)lbl_806D42F4,
    (const char *)lbl_806D44DC,
    (const char *)lbl_806D44E4,
    (const char *)lbl_806D44EC,
    (const char *)lbl_806D44F4,
    (const char *)lbl_806D44FC,
    (const char *)lbl_806D4504,
    (const char *)lbl_806D450C,
    (const char *)lbl_806D4514,
    (const char *)lbl_806D451C,
    (const char *)lbl_806D4524,
    (const char *)lbl_806D452C,
    (const char *)lbl_806D4534,
    (const char *)lbl_806D453C,
    (const char *)lbl_806D4544,
    (const char *)lbl_806D454C,
    (const char *)lbl_806D4554,
    (const char *)lbl_806D455C,
    (const char *)lbl_806D4564,
    (const char *)lbl_806D456C,
    (const char *)lbl_806D4574,
    (const char *)lbl_806D457C,
    (const char *)lbl_806D4584,
    (const char *)lbl_806D458C,
    (const char *)lbl_806D4594,
    (const char *)lbl_806D459C,
    (const char *)lbl_806D45A4,
    (const char *)lbl_806D45AC,
    (const char *)lbl_806D45B4,
    (const char *)lbl_806D45BC,
    (const char *)lbl_806D45C4,
    (const char *)lbl_806D45CC,
    (const char *)lbl_806D45D4,
    (const char *)lbl_806D45DC,
    (const char *)lbl_806D45E4,
    (const char *)lbl_806D45EC,
    (const char *)lbl_806D45F4,
    (const char *)lbl_806D45FC,
    (const char *)lbl_806D4604,
    (const char *)lbl_806D460C,
    (const char *)lbl_806D4614,
    (const char *)lbl_806D461C,
    (const char *)lbl_806D4624,
    (const char *)lbl_806D462C,
    (const char *)lbl_806D4634,
    (const char *)lbl_806D463C,
    (const char *)lbl_806D4644,
    (const char *)lbl_806D464C,
    (const char *)lbl_806D4654,
    (const char *)lbl_806D465C,
    (const char *)lbl_806D4664,
    (const char *)lbl_806D466C,
    (const char *)lbl_806D4674,
    (const char *)lbl_806D467C,
    (const char *)lbl_806D4684,
    (const char *)lbl_806D468C,
    (const char *)lbl_806D4694,
    (const char *)lbl_806D469C,
    (const char *)lbl_806D46A4,
    (const char *)lbl_806D46AC,
    (const char *)lbl_806D46B4,
    (const char *)NameCheck_CardName_rodata_8031F204,
    (const char *)NameCheck_CardName_rodata_8031F210,
    (const char *)NameCheck_CardName_rodata_8031F21C,
    (const char *)NameCheck_CardName_rodata_8031F228,
    (const char *)NameCheck_CardName_rodata_8031F234,
    (const char *)NameCheck_CardName_rodata_8031F240,
    (const char *)NameCheck_CardName_rodata_8031F24C,
    (const char *)NameCheck_CardName_rodata_8031F258,
    (const char *)NameCheck_CardName_rodata_8031F264,
    (const char *)NameCheck_CardName_rodata_8031F270,
    (const char *)NameCheck_CardName_rodata_8031F27C,
    (const char *)NameCheck_CardName_rodata_8031F288,
    (const char *)NameCheck_CardName_rodata_8031F294,
    (const char *)NameCheck_CardName_rodata_8031F2A0,
    (const char *)NameCheck_CardName_rodata_8031F2AC,
    (const char *)NameCheck_CardName_rodata_8031F2B8,
    (const char *)NameCheck_CardName_rodata_8031F2C4,
    (const char *)NameCheck_CardName_rodata_8031F2D0,
    (const char *)NameCheck_CardName_rodata_8031F2DC,
    (const char *)NameCheck_CardName_rodata_8031F2E8,
    (const char *)NameCheck_CardName_rodata_8031F2F4,
    (const char *)NameCheck_CardName_rodata_8031F300,
    (const char *)NameCheck_CardName_rodata_8031F30C,
    (const char *)NameCheck_CardName_rodata_8031F318,
    (const char *)NameCheck_CardName_rodata_8031F324,
    (const char *)NameCheck_CardName_rodata_8031F330,
    (const char *)NameCheck_CardName_rodata_8031F33C,
    (const char *)NameCheck_CardName_rodata_8031F348,
    (const char *)NameCheck_CardName_rodata_8031F354,
    (const char *)NameCheck_CardName_rodata_8031F360,
    (const char *)NameCheck_CardName_rodata_8031F36C,
    (const char *)NameCheck_CardName_rodata_8031F378,
    (const char *)NameCheck_CardName_rodata_8031F384,
    (const char *)NameCheck_CardName_rodata_8031F390,
    (const char *)NameCheck_CardName_rodata_8031F39C,
    (const char *)NameCheck_CardName_rodata_8031F3A8,
    (const char *)NameCheck_CardName_rodata_8031F3B4,
    (const char *)NameCheck_CardName_rodata_8031F3C0,
    (const char *)NameCheck_CardName_rodata_8031F3CC,
    (const char *)NameCheck_CardName_rodata_8031F3D8,
    (const char *)NameCheck_CardName_rodata_8031F3E4,
    (const char *)NameCheck_CardName_rodata_8031F3F0,
    (const char *)NameCheck_CardName_rodata_8031F3FC,
    (const char *)NameCheck_CardName_rodata_8031F408,
    (const char *)NameCheck_CardName_rodata_8031F414,
    (const char *)NameCheck_CardName_rodata_8031F420,
    (const char *)NameCheck_CardName_rodata_8031F42C,
    (const char *)NameCheck_CardName_rodata_8031F438,
    (const char *)NameCheck_CardName_rodata_8031F444,
    (const char *)NameCheck_CardName_rodata_8031F450,
    (const char *)NameCheck_CardName_rodata_8031F45C,
    (const char *)NameCheck_CardName_rodata_8031F468,
    (const char *)NameCheck_CardName_rodata_8031F474,
    (const char *)NameCheck_CardName_rodata_8031F480,
    (const char *)NameCheck_CardName_rodata_8031F48C,
    (const char *)NameCheck_CardName_rodata_8031F498,
    (const char *)NameCheck_CardName_rodata_8031F4A4,
    (const char *)NameCheck_CardName_rodata_8031F4B0,
    (const char *)NameCheck_CardName_rodata_8031F4BC,
    (const char *)NameCheck_CardName_rodata_8031F4C8,
    (const char *)NameCheck_CardName_rodata_8031F4D4,
    (const char *)NameCheck_CardName_rodata_8031F4E0,
    (const char *)NameCheck_CardName_rodata_8031F4EC,
    (const char *)NameCheck_CardName_rodata_8031F4F8,
    (const char *)NameCheck_CardName_rodata_8031F504,
    (const char *)NameCheck_CardName_rodata_8031F510,
    (const char *)NameCheck_CardName_rodata_8031F51C,
    (const char *)NameCheck_CardName_rodata_8031F528,
    (const char *)NameCheck_CardName_rodata_8031F534,
    (const char *)NameCheck_CardName_rodata_8031F540,
    (const char *)NameCheck_CardName_rodata_8031F54C
};
const unsigned int SetCourseParams_rodata_80320604[6] = { TEXT_WORD('M', 'I', 'D', 'N'), TEXT_WORD('I', 'G', 'H', 'T'), 0x00000000, TEXT_WORD('F', 'R', 'E', 'E'), TEXT_WORD(' ', 'R', 'U', 'N'), 0x00000000 };
#pragma force_active reset
/* --- .rodata 0x8032061C..0x80320960: card-name conversion tables and messages --- */
#pragma force_active on
static const NameCode sLower[26] = { 0x8281, 0x8282, 0x8283, 0x8284, 0x8285, 0x8286, 0x8287, 0x8288, 0x8289, 0x828A, 0x828B, 0x828C, 0x828D, 0x828E, 0x828F, 0x8290, 0x8291, 0x8292, 0x8293, 0x8294, 0x8295, 0x8296, 0x8297, 0x8298, 0x8299, 0x829A };
static const NameCode sUpper[26] = { 0x8260, 0x8261, 0x8262, 0x8263, 0x8264, 0x8265, 0x8266, 0x8267, 0x8268, 0x8269, 0x826A, 0x826B, 0x826C, 0x826D, 0x826E, 0x826F, 0x8270, 0x8271, 0x8272, 0x8273, 0x8274, 0x8275, 0x8276, 0x8277, 0x8278, 0x8279 };
static const NameCode sKatakana[82] = { 0x8340, 0x8341, 0x8342, 0x8343, 0x8344, 0x8345, 0x8346, 0x8347, 0x8348, 0x8349, 0x834A, 0x834B, 0x834C, 0x834D, 0x834E, 0x834F, 0x8350, 0x8351, 0x8352, 0x8353, 0x8354, 0x8355, 0x8356, 0x8357, 0x8358, 0x8359, 0x835A, 0x835B, 0x835C, 0x835D, 0x835E, 0x835F, 0x8360, 0x8361, 0x8362, 0x8363, 0x8364, 0x8365, 0x8366, 0x8367, 0x8368, 0x8369, 0x836A, 0x836B, 0x836C, 0x836D, 0x836E, 0x836F, 0x8370, 0x8371, 0x8372, 0x8373, 0x8374, 0x8375, 0x8376, 0x8377, 0x8378, 0x8379, 0x837A, 0x837B, 0x837C, 0x837D, 0x837E, 0x8380, 0x8381, 0x8382, 0x8383, 0x8384, 0x8385, 0x8386, 0x8387, 0x8388, 0x8389, 0x838A, 0x838B, 0x838C, 0x838D, 0x838E, 0x838F, 0x8392, 0x8393, 0x0000 };
static const NameCode sHiragana[82] = { 0x829F, 0x82A0, 0x82A1, 0x82A2, 0x82A3, 0x82A4, 0x82A5, 0x82A6, 0x82A7, 0x82A8, 0x82A9, 0x82AA, 0x82AB, 0x82AC, 0x82AD, 0x82AE, 0x82AF, 0x82B0, 0x82B1, 0x82B2, 0x82B3, 0x82B4, 0x82B5, 0x82B6, 0x82B7, 0x82B8, 0x82B9, 0x82BA, 0x82BB, 0x82BC, 0x82BD, 0x82BE, 0x82BF, 0x82C0, 0x82C1, 0x82C2, 0x82C3, 0x82C4, 0x82C5, 0x82C6, 0x82C7, 0x82C8, 0x82C9, 0x82CA, 0x82CB, 0x82CC, 0x82CD, 0x82CE, 0x82CF, 0x82D0, 0x82D1, 0x82D2, 0x82D3, 0x82D4, 0x82D5, 0x82D6, 0x82D7, 0x82D8, 0x82D9, 0x82DA, 0x82DB, 0x82DC, 0x82DD, 0x82DE, 0x82DF, 0x82E0, 0x82E1, 0x82E2, 0x82E3, 0x82E4, 0x82E5, 0x82E6, 0x82E7, 0x82E8, 0x82E9, 0x82EA, 0x82EB, 0x82EC, 0x82ED, 0x82F0, 0x82F1, 0x0000 };
static const NameCode sSymbols[26] = { 0x8149, 0x8148, 0x8195, 0x8197, 0x8169, 0x816A, 0x8183, 0x8184, 0x814F, 0x817B, 0x817C, 0x817E, 0x8180, 0x8181, 0x815E, 0x815F, 0x8151, 0x8144, 0x8145, 0x8147, 0x8146, 0x8196, 0x819E, 0x815B, 0x8140, 0x0000 };
static const NameCode sDigits[10] = { 0x824F, 0x8250, 0x8251, 0x8252, 0x8253, 0x8254, 0x8255, 0x8256, 0x8257, 0x8258 };
static const NameCharacterSets sCharacterSets[10] = {
    { sHiragana, 81, sKatakana, 81 },
    { sHiragana, 81, 0, 0 },
    { sKatakana, 81, 0, 0 },
    { sUpper, 26, sLower, 26 },
    { sUpper, 26, 0, 0 },
    { sLower, 26, 0, 0 },
    { sDigits, 10, 0, 0 },
    { sHiragana, 81, sSymbols, 24 },
    { sUpper, 26, sSymbols, 24 },
    { sLower, 26, sSymbols, 24 },
};
const char lbl_803208B4[] = "teSingleton<clGame>";
static const char sMsgTooLong[] = "checkCardName over name string %d\n";
static const char sMsgFirst[] = "nameCheck %2d 1st : %s\n";
static const char sMsgSecond[] = "nameCheck %2d 2nd : %s\n";
static const char sMsgHead[] = "checkHaed\n";
static const char sMsgBack[] = "checkBack\n";
static const char sMsgPair[] = "check[%d] - top:%s end:%s\n";
static const char sMsgCounter[] = "Counter is%d\n";
#pragma force_active reset

unsigned char NameCheck_CardName(const unsigned short *name)
{
    unsigned short buf[6];
    unsigned short *cursor;
    int leading;
    int i;
    int j;
    if (wcslen(name) > 5) {
        DebugPrintf(sMsgTooLong, wcslen(name));
        return 0;
    }
    wcscpy(buf, name);
    buf[5] = 0;
    cursor = buf;
    for (leading = 0; leading < 5; leading++) {
        if (buf[leading] != 0x8140) break;
    }
    if (leading > 0) {
        for (i = leading; i < 6; i++) buf[i - leading] = buf[i];
    }
    for (i = 4; i >= 0; i--) {
        if (buf[i] != 0x8140 && buf[i] != 0) break;
        buf[i] = 0;
    }
    if (NameCheck_ScanBannedWords(buf) == 1) return 1;
    /* full-width katakana -> hiragana */
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 81; j++) {
            if (cursor[i] == sKatakana[j]) {
                cursor[i] = sHiragana[j];
                break;
            }
        }
    }
    if (NameCheck_ScanBannedWords(buf) == 1) return 1;
    /* full-width lower case -> upper case */
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 26; j++) {
            if (*cursor == sLower[j]) {
                *cursor = sUpper[j];
                break;
            }
        }
        cursor++;
    }
    return NameCheck_ScanBannedWords(buf) == 1;
}


extern int strcmp(const void *, const void *);
extern int strncmp(const void *, const void *, unsigned int);
extern void *strstr(const void *, const void *);
extern void *strcpy(void *, const void *);
extern void *strcat(void *, const void *);
extern void *memset(void *, int, unsigned int);
extern void DebugPrintf(const char *, ...);
extern const NameDelimiterPair NameCheck_ScanBannedWords_data_8040E450[12];
extern const char *NameCheck_ScanBannedWords_data_8040E4B0[5];
extern const NameCode lbl_806D4740[4];
extern const char lbl_806D4750[4], lbl_806D4754[4], lbl_806D4758[8];
extern const char lbl_806D4760[8], lbl_806D4768[8], lbl_806D4770[8];
extern const char lbl_806D4778[8], lbl_806D4780[8], lbl_806D4788[8];

static inline NameBool contains(unsigned int c, const NameCode *set, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        if (c == *set) return 1;
        set++;
    }
    return 0;
}

static inline NameCode *find_code(NameCode *s, const void *t) { return (NameCode *)strstr(s, t); }
static inline NameBool contains_at(const NameCode *p, const NameCode *set, int count)
{
    NameBool found;
    int i;
    const NameCode *q;
    q = set;
    found = 0;
    for (i = 0; i < count; i++) {
        if (*p == *q) { found = 1; break; }
        q++;
    }
    return found;
}

static inline NameBool at_boundary(const NameCode *p, const NameCode *set, int count)
{
    NameBool found = 0;
    int i;
    if (p) {
        for (i = 0; i < count; i++) {
            if (*p == *set) { found = 1; break; }
            set++;
        }
    }
    return found;
}

#pragma inline_max_size(10000)
static inline int extract_one(const NameCode *buf, NameCode *out, int position,
                             const NameCode *set, int count)
{
    int cursor;
    int length = 0;
    for (cursor = position; cursor < 5; cursor++) {
        if (contains(buf[cursor], set, count) == 1) out[length++] = buf[cursor];
        else if (length > 0) break;
    }
    return cursor;
}
static inline int extract_two(const NameCode *buf, NameCode *out, int position,
                             const NameCode *a, int na, const NameCode *b, int nb)
{
    int cursor;
    int length = 0;
    for (cursor = position; cursor < 5; cursor++) {
        if (contains(buf[cursor], a, na) == 1) out[length++] = buf[cursor];
        else if (contains(buf[cursor], b, nb) == 1) out[length++] = buf[cursor];
        else if (length > 0) break;
    }
    return cursor;
}

/* A scan may consume several characters while it walks the table. */
#define COLLECT_RUN(SET, COUNT) \
    for (k = position; k < 5; k++) { \
        found = 0; \
        for (j = 0; j < (COUNT); j++) { \
            if (buf[position] == (SET)[j]) { \
                parts[part][length++] = buf[position++]; \
                found = 1; \
            } \
        } \
        if (!found) { parts[part][length] = 0; break; } \
    }

#define SPLIT_PARTS(WITH_SYMBOLS) \
    for (word = 0; word < 5; word++) memset(parts[word], 0, 10); \
    position = 0; \
    for (part = 0; part < 5; part++) { \
        length = 0; \
        COLLECT_RUN(upper, 26); \
        if (length > 0) continue; \
        COLLECT_RUN(lower, 26); \
        if (length > 0) continue; \
        COLLECT_RUN(katakana, 81); \
        if (length > 0) continue; \
        COLLECT_RUN(hiragana, 81); \
        if (length > 0) continue; \
        COLLECT_RUN(digits, 10); \
        if (length > 0) continue; \
        if (WITH_SYMBOLS) { COLLECT_RUN(symbols, 25); } \
    }

#define CHECK_WORD(WORD) \
    for (word = 0; word < 1067; word++) { \
        if (strcmp(sBannedWords[word], (WORD)) == 0) return 1; \
    }

#define PRINT_PARTS() \
    DebugPrintf(lbl_806D4768, parts[0]); \
    DebugPrintf(lbl_806D4770, parts[1]); \
    DebugPrintf(lbl_806D4778, parts[2]); \
    DebugPrintf(lbl_806D4780, parts[3]); \
    DebugPrintf(lbl_806D4788, parts[4])

#define CHECK_WORD_V(W, WORD) \
    for (W = 0; W < 1067; W++) { \
        if (strcmp(sBannedWords[W], (WORD)) == 0) return 1; \
    }

#define CHECK_PARTS(WITH_SYMBOLS) { NameBool found; int position, length, part; \
    SPLIT_PARTS(WITH_SYMBOLS); \
    PRINT_PARTS(); \
    for (k = 0; k < 5; k++) { \
        memset(first, 0, 12); \
        strcpy(first, parts[k]); \
        DebugPrintf(lbl_806D4750, first); \
        CHECK_WORD(first); \
        for (j = k + 1; j < 5; j++) { \
            strcat(first, parts[j]); \
            DebugPrintf(lbl_806D4750, first); \
            CHECK_WORD(first); \
        } \
    } \
}

#pragma use_lmw_stmw on
#pragma exceptions on
NameBool NameCheck_ScanBannedWords(NameCode *name)
{
    NameCode buf[6];
    NameCode first[6], second[6];
    NameCode parts[5][5];
    NameCode single[2];
#define upper sUpper
#define lower sLower
#define katakana sHiragana /* this function's names were swapped: 0x80320728 holds hiragana */
#define hiragana sKatakana
#define digits sDigits
#define symbols sSymbols
    NameCode *open;
    const NameCode *boundary_set;
    NameCode *close, *p, *next;
    int j;
    NameBool found, invalid;
    int word, i, k, part, position, length, count;
    unsigned int group;
    int boundary_count;
    wcscpy(buf, name);
    buf[5] = 0;
    CHECK_WORD(buf);
    for (group = 0; group < 10; group++) {
        for (k = 0; k < 6; k++) { second[k] = 0; first[k] = 0; }
        if (!sCharacterSets[group].second) {
            position = extract_one(buf, first, 0, sCharacterSets[group].first, sCharacterSets[group].first_count);
            extract_one(buf, second, position, sCharacterSets[group].first, sCharacterSets[group].first_count);
        } else {
            position = extract_two(buf, first, 0, sCharacterSets[group].first, sCharacterSets[group].first_count,
                                   sCharacterSets[group].second, sCharacterSets[group].second_count);
            extract_two(buf, first, position, sCharacterSets[group].first, sCharacterSets[group].first_count,
                        sCharacterSets[group].second, sCharacterSets[group].second_count);
        }
        DebugPrintf(sMsgFirst, group, first);
        DebugPrintf(sMsgSecond, group, second);
        {
            int word;
            for (word = 0; word < 1067; word++) {
                if (strcmp(sBannedWords[word], first) == 0) return 1;
                if (strcmp(sBannedWords[word], second) == 0) return 1;
            }
        }
    }
    for (group = 0; group < 12; group++) {
        boundary_set = katakana;
        boundary_count = 81;
        if ((int)group >= 11) { boundary_set = lower; boundary_count = 26; }
        else if ((int)group >= 10) { boundary_set = upper; boundary_count = 26; }
        else if ((int)group >= 5) { boundary_set = hiragana; boundary_count = 81; }
        next = (NameCode *)strstr(buf, NameCheck_ScanBannedWords_data_8040E450[group].open);
        open = next;
        if (next) {
            while (next) {
                next = (NameCode *)strstr(open + 1, NameCheck_ScanBannedWords_data_8040E450[group].open);
                if (next) open = next;
            }
            DebugPrintf(sMsgHead);
            if (open != buf && contains_at(open - 1, boundary_set, boundary_count) == 1) break;
            DebugPrintf(sMsgBack);
            close = find_code(open, NameCheck_ScanBannedWords_data_8040E450[group].close);
            if (close) {
                /* The original guard tests byte-address + 1, then reads a code unit. */
                if ((char *)close + 1 && contains_at(close + 1, boundary_set, boundary_count) == 1) break;
                DebugPrintf(sMsgPair, group, open, close);
                invalid = 0;
                for (p = open + 1; *p != *close; p++) {
                    NameBool found;
                    single[0] = *p; single[1] = 0;
                    DebugPrintf(lbl_806D4750, single);
                    found = 0;
                    for (j = 0; j < 25; j++) {
                        if (*p == symbols[j]) { found = 1; break; }
                    }
                    if (!found) { invalid = 1; break; }
                }
                if (invalid == 1) break;
                {
                    NameCode *p; int j;
                    for (p = open + 1; *p != *close; p++) {
                        for (j = 0; (unsigned int)j < 5; j++) {
                            if (strncmp(p, NameCheck_ScanBannedWords_data_8040E4B0[j], 2) == 0) return 1;
                        }
                    }
                }
                break;
            }
        }
    }
    open = (NameCode *)strstr(buf, lbl_806D4754);
    if (open) {
        NameCode *p; int count; NameBool prefix_found; const NameCode *q; NameBool found; int j; const NameCode *set; int bcount;
        count = 0; prefix_found = 0;
        for (p = buf; *p != *open; p++) {
            for (j = 0; j < 3; j++) {
                if (*p == lbl_806D4740[j]) { count++; break; }
            }
            prefix_found = 0;
            for (j = 0; j < 25; j++) {
                if (*p == symbols[j]) { prefix_found = 1; break; }
            }
            if (!prefix_found) count = 0;
        }
        if (count >= 2) {
            for (j = 0; j < 26; j++) {
                if (*open == upper[j]) { prefix_found = 1; break; }
                if (prefix_found == 1) break;
            }
            set = upper; bcount = 26;
            if (prefix_found == 1) { set = lower; bcount = 26; }
            found = 0;
            if (open + 1) {
                q = set;
                for (i = 0; i < bcount; i++) {
                    if (open[1] == *q) { found = 1; break; }
                    q++;
                }
            }
            if (!found) return 1;
        }
    }
    open = (NameCode *)strstr(buf, lbl_806D4758);
    DebugPrintf(lbl_806D4760, open);
    if (open) {
        NameCode *p; int count; NameBool prefix_found; const NameCode *q; NameBool found; int j; const NameCode *set; int bcount;
        count = 0; prefix_found = 0;
        for (p = buf; *p != *open; p++) {
            for (j = 0; j < 3; j++) {
                if (*p == lbl_806D4740[j]) { count++; break; }
            }
            prefix_found = 0;
            for (j = 0; j < 25; j++) {
                if (*p == symbols[j]) { prefix_found = 1; break; }
            }
            if (!prefix_found) count = 0;
        }
        DebugPrintf(sMsgCounter, count);
        if (count >= 1) {
            for (j = 0; j < 26; j++) {
                if (*open == upper[j]) { prefix_found = 1; break; }
                if (prefix_found == 1) break;
            }
            set = upper; bcount = 26;
            if (prefix_found == 1) { set = lower; bcount = 26; }
            found = 0;
            if (open + 2) {
                q = set;
                for (i = 0; i < bcount; i++) {
                    if (open[2] == *q) { found = 1; break; }
                    q++;
                }
            }
            if (!found) return 1;
        }
    }
    CHECK_PARTS(1);
    found = 0;
    for (k = 0; k < 5; k++) {
        for (j = 0; j < 81; j++) {
            if (buf[k] == katakana[j]) { found = 1; break; }
        }
        if (found) break;
    }
    for (k = 0; k < 5; k++) {
        for (j = 0; j < 81; j++) {
            if (buf[k] == hiragana[j]) { found = 1; break; }
        }
        if (found) break;
    }
    if (!found) {
        count = 0;
        for (k = 0; k < 5; k++) {
            for (j = 0; j < 26; j++) if (buf[k] == upper[j]) { count++; break; }
        }
        if (count >= 2) found = 1;
    }
    if (!found) {
        count = 0;
        for (k = 0; k < 5; k++) {
            for (j = 0; j < 26; j++) if (buf[k] == lower[j]) { count++; break; }
        }
        if (count >= 2) found = 1;
    }
    if (!found) {
        count = 0;
        for (k = 0; k < 5; k++) {
            for (j = 0; j < 10; j++) if (buf[k] == digits[j]) { count++; break; }
        }
        if (count >= 2) found = 1;
    }
    if (found) {
        for (k = 0; k < 5;) {
            for (j = 0; j < 25; j++) {
                if (buf[k] == symbols[j]) {
                    for (j = k; j < 5; j++) buf[j] = buf[j + 1];
                    break;
                }
            }
            if ((unsigned int)j >= 25) k++;
        }
        CHECK_WORD_V(k, buf);
    }
    CHECK_PARTS(0);
    return 0;
}
#pragma exceptions reset
#pragma use_lmw_stmw reset
