/* RaceScene_GetPerspFovyForCup (0x8009B9D0): per-cup perspective fovy table
 * lookup. The original TU owned the race/course data .data block
 * (0x80401118..0x8040DE94); the function touches five of its per-cup tables,
 * so the compiler addresses them off the pooled section base. The data below
 * is emitted from the target in order (pointers kept as relocations). */

extern int g_cupId;
extern int g_longRoundFlag;
extern int g_courseVariantIdx;
extern const float lbl_806D4790;
extern const float lbl_806D4794;

extern char lbl_8031866C[];
extern char lbl_8031867C[];
extern char lbl_80318690[];
extern char lbl_803186A4[];
extern char lbl_803186B4[];
extern char lbl_803186C8[];
extern char lbl_803186DC[];
extern char lbl_803186EC[];
extern char lbl_80318700[];
extern char lbl_80318714[];
extern char lbl_80318724[];
extern char lbl_80318738[];
extern char lbl_8031874C[];
extern char lbl_8031875C[];
extern char lbl_80318770[];
extern char lbl_80318784[];
extern char lbl_80318798[];
extern char lbl_803187B0[];
extern char lbl_803187C8[];
extern char lbl_803187D8[];
extern char lbl_803187EC[];
extern char lbl_80318800[];
extern char lbl_80318810[];
extern char lbl_80318824[];
extern char lbl_80318838[];
extern char lbl_80318848[];
extern char lbl_8031885C[];
extern char lbl_80318870[];
extern char lbl_80318884[];
extern char lbl_8031889C[];
extern char lbl_803188B4[];
extern char lbl_803188C8[];
extern char lbl_803188E0[];
extern char lbl_803188F8[];
extern char lbl_8031890C[];
extern char lbl_80318924[];
extern char lbl_8031893C[];
extern char lbl_80318950[];
extern char lbl_80318968[];
extern char lbl_80318980[];
extern char lbl_80318990[];
extern char lbl_803189A4[];
extern char lbl_803189B8[];
extern char lbl_803189C8[];
extern char lbl_803189DC[];
extern char lbl_803189F0[];
extern char lbl_80318A00[];
extern char lbl_80318A14[];
extern char lbl_80318A28[];
extern char lbl_80318A38[];
extern char lbl_80318A4C[];
extern char lbl_80318A60[];
extern char lbl_80318A70[];
extern char lbl_80318A84[];
extern char lbl_80318A98[];
extern char lbl_80318AAC[];
extern char lbl_80318AC4[];
extern char lbl_80318ADC[];
extern char lbl_80318AEC[];
extern char lbl_80318B00[];
extern char lbl_80318B14[];
extern char lbl_80318B24[];
extern char lbl_80318B38[];
extern char lbl_80318B4C[];
extern char lbl_80318B5C[];
extern char lbl_80318B70[];
extern char lbl_80318B84[];
extern char lbl_80318B98[];
extern char lbl_80318BB0[];
extern char lbl_80318BC8[];
extern char lbl_80318BDC[];
extern char lbl_80318BF4[];
extern char lbl_80318C0C[];
extern char lbl_80318C20[];
extern char lbl_80318C38[];
extern char lbl_80318C50[];
extern char lbl_80318C64[];
extern char lbl_80318C7C[];
extern char lbl_80318C94[];
extern char lbl_80318CA8[];
extern char lbl_80318CC0[];
extern char lbl_80318CD8[];
extern char lbl_80318CEC[];
extern char lbl_80318D04[];
extern char lbl_80318D1C[];
extern char lbl_80318D30[];
extern char lbl_80318D48[];
extern char lbl_80318D60[];
extern char lbl_80318D74[];
extern char lbl_80318D8C[];
extern char lbl_80318DA4[];
extern char lbl_80318DB8[];
extern char lbl_80318DD0[];
extern char lbl_80318DE8[];
extern char lbl_80318DFC[];
extern char lbl_80318E14[];
extern char lbl_80318E2C[];
extern char lbl_80318E40[];
extern char lbl_80318E58[];
extern char lbl_80318E70[];
extern char lbl_80318E84[];
extern char lbl_80318E9C[];
extern char lbl_80318EB4[];
extern char lbl_80318EC8[];
extern char lbl_80318EE0[];
extern char lbl_80318EF8[];
extern char lbl_80318F10[];
extern char lbl_80318F2C[];
extern char lbl_80318F48[];
extern char lbl_80318F5C[];
extern char lbl_80318F74[];
extern char lbl_80318F8C[];
extern char lbl_80318FA0[];
extern char lbl_80318FB8[];
extern char lbl_80318FD0[];
extern char lbl_80318FE4[];
extern char lbl_80318FFC[];
extern char lbl_80319014[];
extern char lbl_80319028[];
extern char lbl_80319040[];
extern char lbl_80319054[];
extern char lbl_8031906C[];
extern char lbl_80319084[];
extern char lbl_80319098[];
extern char lbl_803190B4[];
extern char lbl_803190D0[];
extern char lbl_803190E4[];
extern char lbl_80319100[];
extern char lbl_8031911C[];
extern char lbl_80319130[];
extern char lbl_80319140[];
extern char lbl_80319150[];
extern char lbl_80319168[];
extern char lbl_80319178[];
extern char lbl_8031918C[];
extern char lbl_803191A4[];
extern char lbl_803191B8[];
extern char lbl_803191D4[];
extern char lbl_803191E4[];
extern char lbl_803191FC[];
extern char lbl_80319210[];
extern char lbl_80319228[];
extern char lbl_80319238[];
extern char lbl_80319250[];
extern char lbl_80319264[];
extern char lbl_80319278[];
extern char lbl_80319288[];
extern char lbl_80319298[];
extern char lbl_803192A8[];
extern char lbl_803192C0[];
extern char lbl_803192D4[];
extern char lbl_803192EC[];
extern char lbl_80319300[];
extern char lbl_80319318[];
extern char lbl_80319330[];
extern char lbl_80319344[];
extern char lbl_80319360[];
extern char lbl_8031937C[];
extern char lbl_80319390[];
extern char lbl_803193AC[];
extern char lbl_803193C8[];
extern char lbl_803193DC[];
extern char lbl_803193EC[];
extern char lbl_803193FC[];
extern char lbl_80319414[];
extern char lbl_80319424[];
extern char lbl_80319438[];
extern char lbl_80319450[];
extern char lbl_80319464[];
extern char lbl_80319480[];
extern char lbl_80319490[];
extern char lbl_803194A8[];
extern char lbl_803194BC[];
extern char lbl_803194D4[];
extern char lbl_803194E4[];
extern char lbl_803194FC[];
extern char lbl_80319510[];
extern char lbl_80319524[];
extern char lbl_80319534[];
extern char lbl_80319544[];
extern char lbl_80319554[];
extern char lbl_8031956C[];
extern char lbl_80319580[];
extern char lbl_80319598[];
extern char lbl_803195B0[];
extern char lbl_803195C8[];
extern char lbl_803195DC[];
extern char lbl_803195F4[];
extern char lbl_8031960C[];
extern char lbl_80319624[];
extern char lbl_8031963C[];
extern char lbl_80319650[];
extern char lbl_8031966C[];
extern char lbl_80319688[];
extern char lbl_803196A0[];
extern char lbl_803196B8[];
extern char lbl_803196CC[];
extern char lbl_803196E8[];
extern char lbl_80319704[];
extern char lbl_8031971C[];
extern char lbl_80319734[];
extern char lbl_80319748[];
extern char lbl_80319758[];
extern char lbl_80319768[];
extern char lbl_80319780[];
extern char lbl_80319790[];
extern char lbl_803197A4[];
extern char lbl_803197B8[];
extern char lbl_803197CC[];
extern char lbl_803197E4[];
extern char lbl_803197F8[];
extern char lbl_80319814[];
extern char lbl_80319824[];
extern char lbl_8031983C[];
extern char lbl_80319850[];
extern char lbl_80319868[];
extern char lbl_80319880[];
extern char lbl_80319898[];
extern char lbl_803198A8[];
extern char lbl_803198C0[];
extern char lbl_803198D4[];
extern char lbl_803198E8[];
extern char lbl_803198F8[];
extern char lbl_80319908[];
extern char lbl_80319918[];
extern char lbl_80319930[];
extern char lbl_80319948[];
extern char lbl_8031995C[];
extern char lbl_80319974[];
extern char lbl_80319988[];
extern char lbl_803199A0[];
extern char lbl_803199B4[];
extern char lbl_803199CC[];
extern char lbl_803199E4[];
extern char lbl_803199F8[];
extern char lbl_80319A14[];
extern char lbl_80319A30[];
extern char lbl_80319A44[];
extern char lbl_80319A60[];
extern char lbl_80319A7C[];
extern char lbl_80319A90[];
extern char lbl_80319AA0[];
extern char lbl_80319AB0[];
extern char lbl_80319AC8[];
extern char lbl_80319AD8[];
extern char lbl_80319AEC[];
extern char lbl_80319B04[];
extern char lbl_80319B18[];
extern char lbl_80319B34[];
extern char lbl_80319B44[];
extern char lbl_80319B5C[];
extern char lbl_80319B70[];
extern char lbl_80319B88[];
extern char lbl_80319B98[];
extern char lbl_80319BB0[];
extern char lbl_80319BC4[];
extern char lbl_80319BD8[];
extern char lbl_80319BE8[];
extern char lbl_80319BF8[];
extern char lbl_80319C08[];
extern char lbl_80319C20[];
extern char lbl_80319C38[];
extern char lbl_80319C4C[];
extern char lbl_80319C64[];
extern char lbl_80319C78[];
extern char lbl_80319C90[];
extern char lbl_80319CA8[];
extern char lbl_80319CBC[];
extern char lbl_80319CD8[];
extern char lbl_80319CF4[];
extern char lbl_80319D08[];
extern char lbl_80319D24[];
extern char lbl_80319D40[];
extern char lbl_80319D54[];
extern char lbl_80319D64[];
extern char lbl_80319D74[];
extern char lbl_80319D8C[];
extern char lbl_80319D9C[];
extern char lbl_80319DB0[];
extern char lbl_80319DC8[];
extern char lbl_80319DDC[];
extern char lbl_80319DF8[];
extern char lbl_80319E08[];
extern char lbl_80319E20[];
extern char lbl_80319E34[];
extern char lbl_80319E4C[];
extern char lbl_80319E5C[];
extern char lbl_80319E74[];
extern char lbl_80319E88[];
extern char lbl_80319E9C[];
extern char lbl_80319EAC[];
extern char lbl_80319EBC[];
extern char lbl_80319ECC[];
extern char lbl_80319EE4[];
extern char lbl_80319EF8[];
extern char lbl_80319F0C[];
extern char lbl_80319F24[];
extern char lbl_80319F38[];
extern char lbl_80319F50[];
extern char lbl_80319F68[];
extern char lbl_80319F84[];
extern char lbl_80319FA0[];
extern char lbl_80319FB4[];
extern char lbl_80319FD0[];
extern char lbl_80319FEC[];
extern char lbl_8031A000[];
extern char lbl_8031A01C[];
extern char lbl_8031A038[];
extern char lbl_8031A04C[];
extern char lbl_8031A060[];
extern char lbl_8031A074[];
extern char lbl_8031A08C[];
extern char lbl_8031A0A0[];
extern char lbl_8031A0B8[];
extern char lbl_8031A0D4[];
extern char lbl_8031A0EC[];
extern char lbl_8031A108[];
extern char lbl_8031A11C[];
extern char lbl_8031A134[];
extern char lbl_8031A14C[];
extern char lbl_8031A168[];
extern char lbl_8031A178[];
extern char lbl_8031A190[];
extern char lbl_8031A1A4[];
extern char lbl_8031A1B8[];
extern char lbl_8031A1CC[];
extern char lbl_8031A1DC[];
extern char lbl_8031A1F0[];
extern char lbl_8031A208[];
extern char lbl_8031A21C[];
extern char lbl_8031A234[];
extern char lbl_8031A250[];
extern char lbl_8031A264[];
extern char lbl_8031A27C[];
extern char lbl_8031A298[];
extern char lbl_8031A2B4[];
extern char lbl_8031A2C8[];
extern char lbl_8031A2E4[];
extern char lbl_8031A300[];
extern char lbl_8031A31C[];
extern char lbl_8031A330[];
extern char lbl_8031A34C[];
extern char lbl_8031A368[];
extern char lbl_8031A384[];
extern char lbl_8031A398[];
extern char lbl_8031A3AC[];
extern char lbl_8031A3C0[];
extern char lbl_8031A3D8[];
extern char lbl_8031A3E8[];
extern char lbl_8031A400[];
extern char lbl_8031A418[];
extern char lbl_8031A434[];
extern char lbl_8031A44C[];
extern char lbl_8031A468[];
extern char lbl_8031A47C[];
extern char lbl_8031A494[];
extern char lbl_8031A4A8[];
extern char lbl_8031A4C4[];
extern char lbl_8031A4E0[];
extern char lbl_8031A4F0[];
extern char lbl_8031A508[];
extern char lbl_8031A51C[];
extern char lbl_8031A530[];
extern char lbl_8031A540[];
extern char lbl_8031A550[];
extern char lbl_8031A564[];
extern char lbl_8031A57C[];
extern char lbl_8031A594[];
extern char lbl_8031A5B0[];
extern char lbl_8031A5C4[];
extern char lbl_8031A5D8[];
extern char lbl_8031A5EC[];
extern char lbl_8031A604[];
extern char lbl_8031A61C[];
extern char lbl_8031A630[];
extern char lbl_8031A648[];
extern char lbl_8031A660[];
extern char lbl_8031A678[];
extern char lbl_8031A68C[];
extern char lbl_8031A6A8[];
extern char lbl_8031A6C4[];
extern char lbl_8031A6DC[];
extern char lbl_8031A6F0[];
extern char lbl_8031A70C[];
extern char lbl_8031A728[];
extern char lbl_8031A740[];
extern char lbl_8031A754[];
extern char lbl_8031A764[];
extern char lbl_8031A774[];
extern char lbl_8031A78C[];
extern char lbl_8031A79C[];
extern char lbl_8031A7B0[];
extern char lbl_8031A7C4[];
extern char lbl_8031A7DC[];
extern char lbl_8031A7F0[];
extern char lbl_8031A80C[];
extern char lbl_8031A81C[];
extern char lbl_8031A834[];
extern char lbl_8031A848[];
extern char lbl_8031A860[];
extern char lbl_8031A878[];
extern char lbl_8031A888[];
extern char lbl_8031A8A0[];
extern char lbl_8031A8B4[];
extern char lbl_8031A8C8[];
extern char lbl_8031A8D8[];
extern char lbl_8031A8E8[];
extern char lbl_8031A8F8[];
extern char lbl_8031A910[];
extern char lbl_8031A928[];
extern char lbl_8031A93C[];
extern char lbl_8031A954[];
extern char lbl_8031A968[];
extern char lbl_8031A980[];
extern char lbl_8031A99C[];
extern char lbl_8031A9B0[];
extern char lbl_8031A9CC[];
extern char lbl_8031A9E8[];
extern char lbl_8031A9FC[];
extern char lbl_8031AA18[];
extern char lbl_8031AA34[];
extern char lbl_8031AA48[];
extern char lbl_8031AA5C[];
extern char lbl_8031AA70[];
extern char lbl_8031AA88[];
extern char lbl_8031AA98[];
extern char lbl_8031AAB0[];
extern char lbl_8031AACC[];
extern char lbl_8031AAE4[];
extern char lbl_8031AB00[];
extern char lbl_8031AB14[];
extern char lbl_8031AB2C[];
extern char lbl_8031AB40[];
extern char lbl_8031AB5C[];
extern char lbl_8031AB6C[];
extern char lbl_8031AB84[];
extern char lbl_8031AB98[];
extern char lbl_8031ABAC[];
extern char lbl_8031ABBC[];
extern char lbl_8031ABCC[];
extern char lbl_8031ABE0[];
extern char lbl_8031ABF8[];
extern char lbl_8031AC0C[];
extern char lbl_8031AC28[];
extern char lbl_8031AC40[];
extern char lbl_8031AC5C[];
extern char lbl_8031AC78[];
extern char lbl_8031AC8C[];
extern char lbl_8031ACA8[];
extern char lbl_8031ACC8[];
extern char lbl_8031ACDC[];
extern char lbl_8031ACF8[];
extern char lbl_8031AD18[];
extern char lbl_8031AD2C[];
extern char lbl_8031AD40[];
extern char lbl_8031AD54[];
extern char lbl_8031AD70[];
extern char lbl_8031AD84[];
extern char lbl_8031AD9C[];
extern char lbl_8031ADB8[];
extern char lbl_8031ADD0[];
extern char lbl_8031ADEC[];
extern char lbl_8031AE00[];
extern char lbl_8031AE18[];
extern char lbl_8031AE30[];
extern char lbl_8031AE4C[];
extern char lbl_8031AE60[];
extern char lbl_8031AE78[];
extern char lbl_8031AE90[];
extern char lbl_8031AEA4[];
extern char lbl_8031AEB8[];
extern char lbl_8031AECC[];
extern char lbl_8031AEE0[];
extern char lbl_8031AEFC[];
extern char lbl_8031AF10[];
extern char lbl_8031AF28[];
extern char lbl_8031AF40[];
extern char lbl_8031AF5C[];
extern char lbl_8031AF78[];
extern char lbl_8031AF8C[];
extern char lbl_8031AFA8[];
extern char lbl_8031AFC4[];
extern char lbl_8031AFD8[];
extern char lbl_8031AFF4[];
extern char lbl_8031B010[];
extern char lbl_8031B024[];
extern char lbl_8031B038[];
extern char lbl_8031B04C[];
extern char lbl_8031B064[];
extern char lbl_8031B078[];
extern char lbl_8031B090[];
extern char lbl_8031B0AC[];
extern char lbl_8031B0C4[];
extern char lbl_8031B0E0[];
extern char lbl_8031B0F4[];
extern char lbl_8031B10C[];
extern char lbl_8031B124[];
extern char lbl_8031B140[];
extern char lbl_8031B150[];
extern char lbl_8031B168[];
extern char lbl_8031B17C[];
extern char lbl_8031B190[];
extern char lbl_8031B1A4[];
extern char lbl_8031B1B4[];
extern char lbl_8031B1C8[];
extern char lbl_8031B1E0[];
extern char lbl_8031B1F8[];
extern char lbl_8031B20C[];
extern char lbl_8031B224[];
extern char lbl_8031B23C[];
extern char lbl_8031B258[];
extern char lbl_8031B274[];
extern char lbl_8031B288[];
extern char lbl_8031B2A4[];
extern char lbl_8031B2C0[];
extern char lbl_8031B2D4[];
extern char lbl_8031B2F0[];
extern char lbl_8031B30C[];
extern char lbl_8031B320[];
extern char lbl_8031B334[];
extern char lbl_8031B348[];
extern char lbl_8031B360[];
extern char lbl_8031B374[];
extern char lbl_8031B38C[];
extern char lbl_8031B3A8[];
extern char lbl_8031B3C0[];
extern char lbl_8031B3DC[];
extern char lbl_8031B3F0[];
extern char lbl_8031B408[];
extern char lbl_8031B420[];
extern char lbl_8031B43C[];
extern char lbl_8031B44C[];
extern char lbl_8031B464[];
extern char lbl_8031B478[];
extern char lbl_8031B48C[];
extern char lbl_8031B4A0[];
extern char lbl_8031B4B0[];
extern char lbl_8031B4C4[];
extern char lbl_8031B4DC[];
extern char lbl_8031B4F0[];
extern char lbl_8031B508[];
extern char lbl_8031B520[];
extern char lbl_8031B53C[];
extern char lbl_8031B558[];
extern char lbl_8031B56C[];
extern char lbl_8031B588[];
extern char lbl_8031B5A4[];
extern char lbl_8031B5B8[];
extern char lbl_8031B5D4[];
extern char lbl_8031B5F0[];
extern char lbl_8031B604[];
extern char lbl_8031B618[];
extern char lbl_8031B62C[];
extern char lbl_8031B644[];
extern char lbl_8031B658[];
extern char lbl_8031B670[];
extern char lbl_8031B68C[];
extern char lbl_8031B6A4[];
extern char lbl_8031B6C0[];
extern char lbl_8031B6D4[];
extern char lbl_8031B6EC[];
extern char lbl_8031B704[];
extern char lbl_8031B720[];
extern char lbl_8031B730[];
extern char lbl_8031B748[];
extern char lbl_8031B75C[];
extern char lbl_8031B770[];
extern char lbl_8031B784[];
extern char lbl_8031B794[];
extern char lbl_8031B7A8[];
extern char lbl_8031B7C0[];
extern char lbl_8031B7CC[];
extern char lbl_8031B7E0[];
extern char lbl_8031B7F4[];
extern char lbl_8031B808[];
extern char lbl_8031B818[];
extern char lbl_8031B82C[];
extern char lbl_8031B838[];
extern char lbl_8031B84C[];
extern char lbl_8031B860[];
extern char lbl_8031B874[];
extern char lbl_8031B884[];
extern char lbl_8031B898[];
extern char lbl_8031B8A4[];
extern char lbl_8031B8B8[];
extern char lbl_8031B8CC[];
extern char lbl_8031B8E0[];
extern char lbl_8031B8F0[];
extern char lbl_8031B904[];
extern char lbl_8031B910[];
extern char lbl_8031B924[];
extern char lbl_8031B938[];
extern char lbl_8031B94C[];
extern char lbl_8031B95C[];
extern char lbl_8031B970[];
extern char lbl_8031B97C[];
extern char lbl_8031B990[];
extern char lbl_8031B9A4[];
extern char lbl_8031B9B8[];
extern char lbl_8031B9C8[];
extern char lbl_8031B9DC[];
extern char lbl_8031B9E8[];
extern char lbl_8031B9FC[];
extern char lbl_8031BA10[];
extern char lbl_8031BA24[];
extern char lbl_8031BA34[];
extern char lbl_8031BA48[];
extern char lbl_8031BA54[];
extern char lbl_8031BA68[];
extern char lbl_8031BA7C[];
extern char lbl_8031BA90[];
extern char lbl_8031BAA0[];
extern char lbl_8031BAB4[];
extern char lbl_8031BAC0[];
extern char lbl_8031BAD4[];
extern char lbl_8031BAE8[];
extern char lbl_8031BAFC[];
extern char lbl_8031BB0C[];
extern char lbl_8031BB20[];
extern char lbl_8031BB2C[];
extern char lbl_8031BB40[];
extern char lbl_8031BB54[];
extern char lbl_8031BB68[];
extern char lbl_8031BB78[];
extern char lbl_8031BB8C[];
extern char lbl_8031BB98[];
extern char lbl_8031BBAC[];
extern char lbl_8031BBC0[];
extern char lbl_8031BBD4[];
extern char lbl_8031BBE8[];
extern char lbl_8031BBFC[];
extern char lbl_8031BC08[];
extern char lbl_8031BC1C[];
extern char lbl_8031BC30[];
extern char lbl_8031BC44[];
extern char lbl_8031BC54[];
extern char lbl_8031BC68[];
extern char lbl_8031BC74[];
extern char lbl_8031BC88[];
extern char lbl_8031BC9C[];
extern char lbl_8031BCB0[];
extern char lbl_8031BCC0[];
extern char lbl_8031BCD4[];
extern char lbl_8031BCE0[];
extern char lbl_8031BCF4[];
extern char lbl_8031BD08[];
extern char lbl_8031BD1C[];
extern char lbl_8031BD2C[];
extern char lbl_8031BD40[];
extern char lbl_8031BD4C[];
extern char lbl_8031BD60[];
extern char lbl_8031BD7C[];
extern char lbl_8031BD90[];
extern char lbl_8031BDAC[];
extern char lbl_8031BDC4[];
extern char lbl_8031BDD4[];
extern char lbl_8031BDE4[];
extern char lbl_8031BDF8[];
extern char lbl_8031BE0C[];
extern char lbl_8031BE1C[];
extern char lbl_8031BE30[];
extern char lbl_8031BE3C[];
extern char lbl_8031BE48[];
extern char lbl_8031BE54[];
extern char lbl_8031BE60[];
extern char lbl_8031BE6C[];
extern char lbl_8031BE84[];
extern char lbl_8031BE98[];
extern char lbl_8031BEAC[];
extern char lbl_8031BEC0[];
extern char lbl_8031BED4[];
extern char lbl_8031BEE8[];
extern char lbl_8031BEFC[];
extern char lbl_8031BF14[];
extern char lbl_8031BF30[];
extern char lbl_8031BF4C[];
extern char lbl_8031BF68[];
extern char lbl_8031BF88[];
extern char lbl_8031BFA8[];
extern char lbl_8031BFCC[];
extern char lbl_8031BFEC[];
extern char lbl_8031C004[];
extern char lbl_8031C01C[];
extern char lbl_8031C03C[];
extern char lbl_8031C058[];
extern char lbl_8031C078[];
extern char lbl_8031C098[];
extern char lbl_8031C0B8[];
extern char lbl_8031C0D8[];
extern char lbl_8031C0F4[];
extern char lbl_8031C110[];
extern char lbl_8031C12C[];
extern char lbl_8031C14C[];
extern char lbl_8031C168[];
extern char lbl_8031C188[];
extern char lbl_8031C1A8[];
extern char lbl_8031C1C0[];
extern char lbl_8031C1D8[];
extern char lbl_8031C1F4[];
extern char lbl_8031C210[];
extern char lbl_8031C230[];
extern char lbl_8031C24C[];
extern char lbl_8031C26C[];
extern char lbl_8031C28C[];
extern char lbl_8031C2A8[];
extern char lbl_8031C2C4[];
extern char lbl_8031C2E0[];
extern char lbl_8031C2FC[];
extern char lbl_8031C318[];
extern char lbl_8031C338[];
extern char lbl_8031C358[];
extern char lbl_8031C36C[];
extern char lbl_8031C384[];
extern char lbl_8031C3A0[];
extern char lbl_8031C3BC[];
extern char lbl_8031C3D8[];
extern char lbl_8031C3F4[];
extern char lbl_8031C414[];
extern char lbl_8031C430[];
extern char lbl_8031C44C[];
extern char lbl_8031C468[];
extern char lbl_8031C480[];
extern char lbl_8031C49C[];
extern char lbl_8031C4B8[];
extern char lbl_8031C4D8[];
extern char lbl_8031C4F8[];
extern char lbl_8031C50C[];
extern char lbl_8031C520[];
extern char lbl_8031C53C[];
extern char lbl_8031C558[];
extern char lbl_8031C574[];
extern char lbl_8031C590[];
extern char lbl_8031C5AC[];
extern char lbl_8031C5C8[];
extern char lbl_8031C5E4[];
extern char lbl_8031C600[];
extern char lbl_8031C61C[];
extern char lbl_8031C63C[];
extern char lbl_8031C658[];
extern char lbl_8031C678[];
extern char lbl_8031C698[];
extern char lbl_8031C6B0[];
extern char lbl_8031C6C8[];
extern char lbl_8031C6E4[];
extern char lbl_8031C700[];
extern char lbl_8031C718[];
extern char lbl_8031C738[];
extern char lbl_8031C754[];
extern char lbl_8031C774[];
extern char lbl_8031C794[];
extern char lbl_8031C7B0[];
extern char lbl_8031C7CC[];
extern char lbl_8031C7E4[];
extern char lbl_8031C800[];
extern char lbl_8031C81C[];
extern char lbl_8031C83C[];
extern char lbl_8031C85C[];
extern char lbl_8031C870[];
extern char lbl_8031C884[];
extern char lbl_8031C8A0[];
extern char lbl_8031C8BC[];
extern char lbl_8031C8D8[];
extern char lbl_8031C8F4[];
extern char lbl_8031C910[];
extern char lbl_8031C92C[];
extern char lbl_8031C948[];
extern char lbl_8031C964[];
extern char lbl_8031C97C[];
extern char lbl_8031C998[];
extern char lbl_8031C9B4[];
extern char lbl_8031C9D4[];
extern char lbl_8031C9F4[];
extern char lbl_8031CA08[];
extern char lbl_8031CA1C[];
extern char lbl_8031CA38[];
extern char lbl_8031CA54[];
extern char lbl_8031CA70[];
extern char lbl_8031CA8C[];
extern char lbl_8031CAA8[];
extern char lbl_8031CAC4[];
extern char lbl_8031CAE0[];
extern char lbl_8031CAFC[];
extern char lbl_8031CB18[];
extern char lbl_8031CB38[];
extern char lbl_8031CB58[];
extern char lbl_8031CB7C[];
extern char lbl_8031CB9C[];
extern char lbl_8031CBB4[];
extern char lbl_8031CBCC[];
extern char lbl_8031CBEC[];
extern char lbl_8031CC08[];
extern char lbl_8031CC28[];
extern char lbl_8031CC48[];
extern char lbl_8031CC68[];
extern char lbl_8031CC88[];
extern char lbl_8031CC98[];
extern char lbl_8031CCB4[];
extern char lbl_8031CCC4[];
extern char lbl_8031CCE0[];
extern char lbl_8031CCF0[];
extern char lbl_8031CD0C[];
extern char lbl_8031CD20[];
extern char lbl_8031CD44[];
extern char lbl_8031CD64[];
extern char lbl_8031CD74[];
extern char lbl_8031CD94[];
extern char lbl_8031CDAC[];
extern char lbl_8031CDC8[];
extern char lbl_8031CDE4[];
extern char lbl_8031CE04[];
extern char lbl_8031CE1C[];
extern char lbl_8031CE38[];
extern char lbl_8031CE48[];
extern char lbl_8031CE60[];
extern char lbl_8031CE70[];
extern char lbl_8031CE8C[];
extern char lbl_8031CEA8[];
extern char lbl_8031CEBC[];
extern char lbl_8031CECC[];
extern char lbl_8031CEDC[];
extern char lbl_8031CEEC[];
extern char lbl_8031CF08[];
extern char lbl_8031CF20[];
extern char lbl_8031CF38[];
extern char lbl_8031CF50[];
extern char lbl_8031CF68[];
extern char lbl_8031CF84[];
extern char lbl_8031CF9C[];
extern char lbl_8031CFB4[];
extern char lbl_8031CFCC[];
extern char lbl_8031CFE0[];
extern char lbl_8031CFF0[];
extern char lbl_8031D000[];
extern char lbl_8031D010[];
extern char lbl_8031D028[];
extern char lbl_8031D040[];
extern char lbl_8031D058[];
extern char lbl_8031D070[];
extern char lbl_8031D084[];
extern char lbl_8031D09C[];
extern char lbl_8031D0B4[];
extern char lbl_8031D0CC[];
extern char lbl_8031D0E0[];
extern char lbl_8031D0F0[];
extern char lbl_8031D100[];
extern char lbl_8031D110[];
extern char lbl_8031D128[];
extern char lbl_8031D144[];
extern char lbl_8031D15C[];
extern char lbl_8031D174[];
extern char lbl_8031D188[];
extern char lbl_8031D1A4[];
extern char lbl_8031D1B8[];
extern char lbl_8031D1C8[];
extern char lbl_8031D1D8[];
extern char lbl_8031D1E8[];
extern char lbl_8031D200[];
extern char lbl_8031D218[];
extern char lbl_8031D230[];
extern char lbl_8031D248[];
extern char lbl_8031D25C[];
extern char lbl_8031D278[];
extern char lbl_8031D28C[];
extern char lbl_8031D298[];
extern char lbl_8031D2A4[];
extern char lbl_8031D2B0[];
extern char lbl_8031D2C8[];
extern char lbl_8031D2E0[];
extern char lbl_8031D2F8[];
extern char lbl_8031D310[];
extern char lbl_8031D324[];
extern char lbl_8031D340[];
extern char lbl_8031D358[];
extern char lbl_8031D36C[];
extern char lbl_8031D384[];
extern char lbl_8031D398[];
extern char lbl_8031D3AC[];
extern char lbl_8031D3C0[];
extern char lbl_8031D3D4[];
extern char lbl_8031D3F0[];
extern char lbl_8031D408[];
extern char lbl_8031D418[];
extern char lbl_8031D428[];
extern char lbl_8031D440[];
extern char lbl_8031D454[];
extern char lbl_8031D468[];
extern char lbl_8031D47C[];
extern char lbl_8031D490[];
extern char lbl_8031D4A4[];
extern char lbl_8031D4C0[];
extern char lbl_8031D4D0[];
extern char lbl_8031D4E0[];
extern char lbl_8031D4F8[];
extern char lbl_8031D50C[];
extern char lbl_8031D520[];
extern char lbl_8031D534[];
extern char lbl_8031D548[];
extern char lbl_8031D55C[];
extern char lbl_8031D574[];
extern char lbl_8031D588[];
extern char lbl_8031D598[];
extern char lbl_8031D5B0[];
extern char lbl_8031D5CC[];
extern char lbl_8031D5E0[];
extern char lbl_8031D5FC[];
extern char lbl_8031D610[];
extern char lbl_8031D620[];
extern char lbl_8031D638[];
extern char lbl_8031D650[];
extern char lbl_8031D664[];
extern char lbl_8031D680[];
extern char lbl_8031D690[];
extern char lbl_8031D6A0[];
extern char lbl_8031D6B0[];
extern char lbl_8031D6C0[];
extern char lbl_8031D6D0[];
extern char lbl_8031D6E8[];
extern char lbl_8031D6FC[];
extern char lbl_8031D710[];
extern char lbl_8031D724[];
extern char lbl_8031D738[];
extern char lbl_8031D74C[];
extern char lbl_8031D768[];
extern char lbl_8031D778[];
extern char lbl_8031D790[];
extern char lbl_8031D7A4[];
extern char lbl_8031D7B8[];
extern char lbl_8031D7CC[];
extern char lbl_8031D7E0[];
extern char lbl_8031D7F4[];
extern char lbl_8031D80C[];
extern char lbl_8031D824[];
extern char lbl_8031D83C[];
extern char lbl_8031D854[];
extern char lbl_8031D86C[];
extern char lbl_8031D880[];
extern char lbl_8031D890[];
extern char lbl_8031D8A4[];
extern char lbl_8031D8BC[];
extern char lbl_8031D8D0[];
extern char lbl_8031D8EC[];
extern char lbl_8031D8FC[];
extern char lbl_8031D910[];
extern char lbl_8031D928[];
extern char lbl_8031D93C[];
extern char lbl_8031D954[];
extern char lbl_8031D968[];
extern char lbl_8031D980[];
extern char lbl_8031D99C[];
extern char lbl_8031D9B4[];
extern char lbl_8031D9D0[];
extern char lbl_8031D9E8[];
extern char lbl_8031D9FC[];
extern char lbl_8031DA14[];
extern char lbl_8031DA30[];
extern char lbl_8031DA44[];
extern char lbl_8031DA5C[];
extern char lbl_8031DA78[];
extern char lbl_8031DA90[];
extern char lbl_8031DAA8[];
extern char lbl_8031DAC4[];
extern char lbl_8031DAE0[];
extern char lbl_8031DAF4[];
extern char lbl_8031DB0C[];
extern char lbl_8031DB20[];
extern char lbl_8031DB38[];
extern char lbl_8031DB50[];
extern char lbl_8031DB64[];
extern char lbl_8031DB7C[];
extern char lbl_8031DB94[];
extern char lbl_8031DBA8[];
extern char lbl_8031DBC0[];
extern char lbl_8031DBD8[];
extern char lbl_8031DBEC[];
extern char lbl_8031DC04[];
extern char lbl_8031DC18[];
extern char lbl_8031DC30[];
extern char lbl_8031DC4C[];
extern char lbl_806D3600[];
extern char lbl_806D3608[];
extern char lbl_806D3610[];
extern char lbl_806D3618[];
extern char lbl_806D3620[];
extern void *Block2[];
extern void *RaceScene_GetPerspFovyForCup_data_804012EC[];
extern void *RaceScene_GetPerspFovyForCup_data_804013B0[];
extern void *RaceScene_GetPerspFovyForCup_data_80401474[];
extern void *RaceScene_GetPerspFovyForCup_data_80401538[];
extern void *RaceScene_GetPerspFovyForCup_data_804015FC[];
extern void *RaceScene_GetPerspFovyForCup_data_804016C0[];
extern void *RaceScene_GetPerspFovyForCup_data_80401784[];
extern void *RaceScene_GetPerspFovyForCup_data_80401848[];
extern void *RaceScene_GetPerspFovyForCup_data_8040190C[];
extern void *RaceScene_GetPerspFovyForCup_data_804019D0[];
extern void *RaceScene_GetPerspFovyForCup_data_80401A94[];
extern void *RaceScene_GetPerspFovyForCup_data_80401B58[];
extern void *RaceScene_GetPerspFovyForCup_data_80401C1C[];
extern void *RaceScene_GetPerspFovyForCup_data_80401F74[];
extern void *RaceScene_GetPerspFovyForCup_data_804020B4[];
extern void *RaceScene_GetPerspFovyForCup_data_804021F4[];
extern void *RaceScene_GetPerspFovyForCup_data_80402334[];
extern void *RaceScene_GetPerspFovyForCup_data_80402434[];
extern void *RaceScene_GetPerspFovyForCup_data_804025A4[];
extern void *RaceScene_GetPerspFovyForCup_data_80402724[];
extern void *RaceScene_GetPerspFovyForCup_data_80402A44[];
extern void *RaceScene_GetPerspFovyForCup_data_80402D64[];
extern void *RaceScene_GetPerspFovyForCup_data_80402E64[];
extern void *RaceScene_GetPerspFovyForCup_data_80402FD4[];
extern void *RaceScene_GetPerspFovyForCup_data_80403154[];
extern void *RaceScene_GetPerspFovyForCup_data_80403324[];
extern void *RaceScene_GetPerspFovyForCup_data_80403654[];
extern void *RaceScene_GetPerspFovyForCup_data_804039B4[];
extern void *RaceScene_GetPerspFovyForCup_data_80403BA4[];
extern void *RaceScene_GetPerspFovyForCup_data_80403D94[];
extern void *RaceScene_GetPerspFovyForCup_data_80403ED4[];
extern void *RaceScene_GetPerspFovyForCup_data_804040A4[];
extern void *RaceScene_GetPerspFovyForCup_data_804041E4[];
extern void *RaceScene_GetPerspFovyForCup_data_80404394[];
extern void *RaceScene_GetPerspFovyForCup_data_804044F4[];
extern void *RaceScene_GetPerspFovyForCup_data_80404654[];
extern void *RaceScene_GetPerspFovyForCup_data_80404994[];
extern void *RaceScene_GetPerspFovyForCup_data_80404CB4[];
extern void *RaceScene_GetPerspFovyForCup_data_80404DB4[];
extern void *RaceScene_GetPerspFovyForCup_data_80404F34[];
extern void *RaceScene_GetPerspFovyForCup_data_804050B4[];
extern void *RaceScene_GetPerspFovyForCup_data_80405284[];
extern void *RaceScene_GetPerspFovyForCup_data_804055B4[];
extern void *RaceScene_GetPerspFovyForCup_data_80405914[];
extern void *RaceScene_GetPerspFovyForCup_data_80405B04[];
extern void *RaceScene_GetPerspFovyForCup_data_80405CF4[];
extern void *RaceScene_GetPerspFovyForCup_data_80405E94[];
extern void *RaceScene_GetPerspFovyForCup_data_80406034[];
extern void *RaceScene_GetPerspFovyForCup_data_804061D4[];
extern void *RaceScene_GetPerspFovyForCup_data_80406374[];
extern void *RaceScene_GetPerspFovyForCup_data_80406514[];
extern void *RaceScene_GetPerspFovyForCup_data_804066B4[];
extern void *RaceScene_GetPerspFovyForCup_data_80406854[];
extern void *RaceScene_GetPerspFovyForCup_data_804069F4[];
extern void *RaceScene_GetPerspFovyForCup_data_80406B94[];
extern void *RaceScene_GetPerspFovyForCup_data_80406D34[];
extern void *RaceScene_GetPerspFovyForCup_data_80406ED4[];
extern void *RaceScene_GetPerspFovyForCup_data_80407074[];
extern void *RaceScene_GetPerspFovyForCup_data_80407214[];
extern void *RaceScene_GetPerspFovyForCup_data_804073B4[];
extern void *RaceScene_GetPerspFovyForCup_data_80407554[];
extern void *RaceScene_GetPerspFovyForCup_data_804076F4[];
extern void *RaceScene_GetPerspFovyForCup_data_80407894[];
extern void *RaceScene_GetPerspFovyForCup_data_80407A34[];
extern void *RaceScene_GetPerspFovyForCup_data_80407BD4[];
extern void *RaceScene_GetPerspFovyForCup_data_80407D74[];
extern void *RaceScene_GetPerspFovyForCup_data_80407F14[];
extern void *RaceScene_GetPerspFovyForCup_data_804080B4[];
extern void *RaceScene_GetPerspFovyForCup_data_80408254[];
extern void *RaceScene_GetPerspFovyForCup_data_804083F4[];
extern void *RaceScene_GetPerspFovyForCup_data_80408594[];
extern void *RaceScene_GetPerspFovyForCup_data_80408734[];
extern void *RaceScene_GetPerspFovyForCup_data_804088D4[];
extern void *RaceScene_GetPerspFovyForCup_data_80408A74[];
extern void *RaceScene_GetPerspFovyForCup_data_80408C14[];
extern void *RaceScene_GetPerspFovyForCup_data_80408DB4[];
extern void *RaceScene_GetPerspFovyForCup_data_80408F54[];
extern void *RaceScene_GetPerspFovyForCup_data_804090F4[];
extern void *RaceScene_GetPerspFovyForCup_data_804091A4[];
extern void *RaceScene_GetPerspFovyForCup_data_80409254[];
extern void *RaceScene_GetPerspFovyForCup_data_80409304[];
extern void *RaceScene_GetPerspFovyForCup_data_804093B4[];
extern void *RaceScene_GetPerspFovyForCup_data_80409464[];
extern void *RaceScene_GetPerspFovyForCup_data_80409514[];
extern void *RaceScene_GetPerspFovyForCup_data_804095C4[];
extern void *RaceScene_GetPerspFovyForCup_data_80409674[];
extern void *RaceScene_GetPerspFovyForCup_data_80409724[];
extern void *RaceScene_GetPerspFovyForCup_data_804097D4[];
extern void *RaceScene_GetPerspFovyForCup_data_80409884[];
extern void *RaceScene_GetPerspFovyForCup_data_80409934[];
extern void *RaceScene_GetPerspFovyForCup_data_804099E4[];
extern void *RaceScene_GetPerspFovyForCup_data_80409A94[];
extern void *RaceScene_GetPerspFovyForCup_data_80409B44[];
extern void *RaceScene_GetPerspFovyForCup_data_80409BF4[];
extern void *RaceScene_GetPerspFovyForCup_data_80409CA4[];
extern void *RaceScene_GetPerspFovyForCup_data_80409D54[];
extern void *RaceScene_GetPerspFovyForCup_data_80409E04[];
extern void *RaceScene_GetPerspFovyForCup_data_80409EB4[];
extern void *RaceScene_GetPerspFovyForCup_data_80409F64[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A014[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A0C4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A174[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A224[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A2D4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A384[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A434[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A4E4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A594[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A644[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A6F4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A70C[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A724[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A784[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A7E4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A7FC[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A814[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A874[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A8D4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A8EC[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A904[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A964[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A9C4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A9DC[];
extern void *RaceScene_GetPerspFovyForCup_data_8040A9F4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AA0C[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AA24[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AA84[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AAE4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AB44[];
extern void *RaceScene_GetPerspFovyForCup_data_8040ABA4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040ABBC[];
extern void *RaceScene_GetPerspFovyForCup_data_8040ABD4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AC34[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AC94[];
extern void *RaceScene_GetPerspFovyForCup_data_8040ACAC[];
extern void *RaceScene_GetPerspFovyForCup_data_8040ACC4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AD24[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AD84[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AD9C[];
extern void *RaceScene_GetPerspFovyForCup_data_8040ADB4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AE14[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AE74[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AE90[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AEAC[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AEC4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AEDC[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AF3C[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AF9C[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AFB8[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AFD4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040AFF0[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B00C[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B024[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B030[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B048[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B054[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B06C[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B078[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B0B0[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B0C8[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B0D4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B0EC[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B104[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B110[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B11C[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B35C[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B374[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B3D4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B3EC[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B44C[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B494[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B4DC[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B524[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B56C[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B5B4[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B5FC[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B644[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B68C[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B71C[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B764[];
extern void *RaceScene_GetPerspFovyForCup_data_8040B7AC[];

void *RaceScene_GetPerspFovyForCup_data_80401118[117] = {
    lbl_8031866C, lbl_8031867C, lbl_80318690, lbl_803186A4,
    lbl_803186B4, lbl_803186C8, lbl_803186DC, lbl_803186EC,
    lbl_80318700, lbl_80318714, lbl_80318724, lbl_80318738,
    lbl_8031874C, lbl_8031875C, lbl_80318770, lbl_80318784,
    lbl_80318798, lbl_803187B0, lbl_803187C8, lbl_803187D8,
    lbl_803187EC, lbl_80318800, lbl_80318810, lbl_80318824,
    lbl_80318838, lbl_80318848, lbl_8031885C, lbl_80318870,
    lbl_80318884, lbl_8031889C, lbl_803188B4, lbl_803188C8,
    lbl_803188E0, lbl_803188F8, lbl_8031890C, lbl_80318924,
    lbl_8031893C, lbl_80318950, lbl_80318968, lbl_80318980,
    lbl_80318990, lbl_803189A4, lbl_803189B8, lbl_803189C8,
    lbl_803189DC, lbl_803189F0, lbl_80318A00, lbl_80318A14,
    lbl_80318A28, lbl_80318A38, lbl_80318A4C, lbl_80318A60,
    lbl_80318A70, lbl_80318A84, lbl_80318A98, lbl_80318AAC,
    lbl_80318AC4, lbl_80318ADC, lbl_80318AEC, lbl_80318B00,
    lbl_80318B14, lbl_80318B24, lbl_80318B38, lbl_80318B4C,
    lbl_80318B5C, lbl_80318B70, lbl_80318B84, lbl_80318B98,
    lbl_80318BB0, lbl_80318BC8, lbl_80318BDC, lbl_80318BF4,
    lbl_80318C0C, lbl_80318C20, lbl_80318C38, lbl_80318C50,
    lbl_80318C64, lbl_80318C7C, lbl_80318C94, lbl_80318CA8,
    lbl_80318CC0, lbl_80318CD8, lbl_80318CEC, lbl_80318D04,
    lbl_80318D1C, lbl_80318D30, lbl_80318D48, lbl_80318D60,
    lbl_80318D74, lbl_80318D8C, lbl_80318DA4, lbl_80318DB8,
    lbl_80318DD0, lbl_80318DE8, lbl_80318DFC, lbl_80318E14,
    lbl_80318E2C, lbl_80318E40, lbl_80318E58, lbl_80318E70,
    lbl_80318E84, lbl_80318E9C, lbl_80318EB4, lbl_80318EC8,
    lbl_80318EE0, lbl_80318EF8, lbl_80318F10, lbl_80318F2C,
    lbl_80318F48, lbl_80318F5C, lbl_80318F74, lbl_80318F8C,
    lbl_80318FA0, lbl_80318FB8, lbl_80318FD0, lbl_80318FE4,
    lbl_80318FFC,
};
void *RaceScene_GetPerspFovyForCup_data_804012EC[49] = {
    lbl_80319014, lbl_80319028, lbl_80319028, (void *)0x00000000,
    (void *)0x00000000, lbl_80319040, lbl_80319054, lbl_8031906C,
    (void *)0x00000000, (void *)0x00000000, lbl_80319084, lbl_80319098,
    lbl_803190B4, (void *)0x00000000, (void *)0x00000000, lbl_803190D0,
    lbl_803190E4, lbl_80319100, (void *)0x00000000, (void *)0x00000000,
    lbl_8031911C, lbl_80319130, lbl_80319140, lbl_80319150,
    lbl_80319168, lbl_80319178, (void *)0x00000000, (void *)0x00000000,
    lbl_8031918C, lbl_803191A4, lbl_803191B8, lbl_803191D4,
    lbl_803191E4, lbl_803191FC, lbl_80319210, (void *)0x00000000,
    (void *)0x00000000, lbl_80319228, lbl_80319238, lbl_80319250,
    lbl_80319264, lbl_80319278, lbl_80319288, lbl_80319298,
    lbl_803192A8, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_804013B0[49] = {
    lbl_803192C0, lbl_803192D4, lbl_803192D4, (void *)0x00000000,
    (void *)0x00000000, lbl_803192EC, lbl_80319300, lbl_80319318,
    (void *)0x00000000, (void *)0x00000000, lbl_80319330, lbl_80319344,
    lbl_80319360, (void *)0x00000000, (void *)0x00000000, lbl_8031937C,
    lbl_80319390, lbl_803193AC, (void *)0x00000000, (void *)0x00000000,
    lbl_803193C8, lbl_803193DC, lbl_803193EC, lbl_803193FC,
    lbl_80319414, lbl_80319424, (void *)0x00000000, (void *)0x00000000,
    lbl_80319438, lbl_80319450, lbl_80319464, lbl_80319480,
    lbl_80319490, lbl_803194A8, lbl_803194BC, (void *)0x00000000,
    (void *)0x00000000, lbl_803194D4, lbl_803194E4, lbl_803194FC,
    lbl_80319510, lbl_80319524, lbl_80319534, lbl_80319544,
    lbl_80319554, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_80401474[49] = {
    lbl_8031956C, lbl_80319580, lbl_80319580, lbl_80319598,
    lbl_803195B0, lbl_803195C8, lbl_803195DC, lbl_803195F4,
    lbl_8031960C, lbl_80319624, lbl_8031963C, lbl_80319650,
    lbl_8031966C, lbl_80319688, lbl_803196A0, lbl_803196B8,
    lbl_803196CC, lbl_803196E8, lbl_80319704, lbl_8031971C,
    lbl_80319734, lbl_80319748, lbl_80319758, lbl_80319768,
    lbl_80319780, lbl_80319790, lbl_803197A4, lbl_803197B8,
    lbl_803197CC, lbl_803197E4, lbl_803197F8, lbl_80319814,
    lbl_80319824, lbl_8031983C, lbl_80319850, lbl_80319868,
    lbl_80319880, lbl_80319898, lbl_803198A8, lbl_803198C0,
    lbl_803198D4, lbl_803198E8, lbl_803198F8, lbl_80319908,
    lbl_80319918, lbl_80319930, lbl_80319948, lbl_8031995C,
    (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_80401538[49] = {
    lbl_80319974, lbl_80319988, lbl_80319988, (void *)0x00000000,
    (void *)0x00000000, lbl_803199A0, lbl_803199B4, lbl_803199CC,
    (void *)0x00000000, (void *)0x00000000, lbl_803199E4, lbl_803199F8,
    lbl_80319A14, (void *)0x00000000, (void *)0x00000000, lbl_80319A30,
    lbl_80319A44, lbl_80319A60, (void *)0x00000000, (void *)0x00000000,
    lbl_80319A7C, lbl_80319A90, lbl_80319AA0, lbl_80319AB0,
    lbl_80319AC8, lbl_80319AD8, (void *)0x00000000, (void *)0x00000000,
    lbl_80319AEC, lbl_80319B04, lbl_80319B18, lbl_80319B34,
    lbl_80319B44, lbl_80319B5C, lbl_80319B70, (void *)0x00000000,
    (void *)0x00000000, lbl_80319B88, lbl_80319B98, lbl_80319BB0,
    lbl_80319BC4, lbl_80319BD8, lbl_80319BE8, lbl_80319BF8,
    lbl_80319C08, lbl_80319C20, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_804015FC[49] = {
    lbl_80319C38, lbl_80319C4C, lbl_80319C4C, (void *)0x00000000,
    (void *)0x00000000, lbl_80319C64, lbl_80319C78, lbl_80319C90,
    (void *)0x00000000, (void *)0x00000000, lbl_80319CA8, lbl_80319CBC,
    lbl_80319CD8, (void *)0x00000000, (void *)0x00000000, lbl_80319CF4,
    lbl_80319D08, lbl_80319D24, (void *)0x00000000, (void *)0x00000000,
    lbl_80319D40, lbl_80319D54, lbl_80319D64, lbl_80319D74,
    lbl_80319D8C, lbl_80319D9C, (void *)0x00000000, (void *)0x00000000,
    lbl_80319DB0, lbl_80319DC8, lbl_80319DDC, lbl_80319DF8,
    lbl_80319E08, lbl_80319E20, lbl_80319E34, (void *)0x00000000,
    (void *)0x00000000, lbl_80319E4C, lbl_80319E5C, lbl_80319E74,
    lbl_80319E88, lbl_80319E9C, lbl_80319EAC, lbl_80319EBC,
    lbl_80319ECC, lbl_80319EE4, lbl_80319EF8, lbl_80319F0C,
    (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_804016C0[49] = {
    lbl_80319F24, lbl_80319F38, lbl_80319F38, (void *)0x00000000,
    (void *)0x00000000, lbl_80319F50, lbl_80319F68, lbl_80319F84,
    (void *)0x00000000, (void *)0x00000000, lbl_80319FA0, lbl_80319FB4,
    lbl_80319FD0, (void *)0x00000000, (void *)0x00000000, lbl_80319FEC,
    lbl_8031A000, lbl_8031A01C, (void *)0x00000000, (void *)0x00000000,
    lbl_8031A038, lbl_8031A04C, lbl_8031A060, lbl_8031A074,
    lbl_8031A08C, lbl_8031A0A0, (void *)0x00000000, (void *)0x00000000,
    lbl_8031A0B8, lbl_8031A0D4, lbl_8031A0EC, lbl_8031A108,
    lbl_8031A11C, lbl_8031A134, lbl_8031A14C, (void *)0x00000000,
    (void *)0x00000000, lbl_8031A168, lbl_8031A178, lbl_8031A190,
    lbl_8031A1A4, lbl_8031A1B8, lbl_8031A1CC, lbl_8031A1DC,
    lbl_8031A1F0, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_80401784[49] = {
    lbl_8031A208, lbl_8031A21C, lbl_8031A21C, lbl_8031A234,
    (void *)0x00000000, lbl_8031A250, lbl_8031A264, lbl_8031A27C,
    lbl_8031A298, (void *)0x00000000, lbl_8031A2B4, lbl_8031A2C8,
    lbl_8031A2E4, lbl_8031A300, (void *)0x00000000, lbl_8031A31C,
    lbl_8031A330, lbl_8031A34C, lbl_8031A368, (void *)0x00000000,
    lbl_8031A384, lbl_8031A398, lbl_8031A3AC, lbl_8031A3C0,
    lbl_8031A3D8, lbl_8031A3E8, lbl_8031A400, (void *)0x00000000,
    lbl_8031A418, lbl_8031A434, lbl_8031A44C, lbl_8031A468,
    lbl_8031A47C, lbl_8031A494, lbl_8031A4A8, lbl_8031A4C4,
    (void *)0x00000000, lbl_8031A4E0, lbl_8031A4F0, lbl_8031A508,
    lbl_8031A51C, lbl_8031A530, lbl_8031A540, lbl_8031A550,
    lbl_8031A564, lbl_8031A57C, lbl_8031A594, lbl_8031A5B0,
    lbl_8031A5C4,
};
void *RaceScene_GetPerspFovyForCup_data_80401848[49] = {
    lbl_8031A5D8, lbl_8031A5EC, lbl_8031A5EC, lbl_8031A604,
    (void *)0x00000000, lbl_8031A61C, lbl_8031A630, lbl_8031A648,
    lbl_8031A660, (void *)0x00000000, lbl_8031A678, lbl_8031A68C,
    lbl_8031A6A8, lbl_8031A6C4, (void *)0x00000000, lbl_8031A6DC,
    lbl_8031A6F0, lbl_8031A70C, lbl_8031A728, (void *)0x00000000,
    lbl_8031A740, lbl_8031A754, lbl_8031A764, lbl_8031A774,
    lbl_8031A78C, lbl_8031A79C, lbl_8031A7B0, (void *)0x00000000,
    lbl_8031A7C4, lbl_8031A7DC, lbl_8031A7F0, lbl_8031A80C,
    lbl_8031A81C, lbl_8031A834, lbl_8031A848, lbl_8031A860,
    (void *)0x00000000, lbl_8031A878, lbl_8031A888, lbl_8031A8A0,
    lbl_8031A8B4, lbl_8031A8C8, lbl_8031A8D8, lbl_8031A8E8,
    lbl_8031A8F8, lbl_8031A910, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_8040190C[49] = {
    lbl_8031A928, lbl_8031A93C, lbl_8031A93C, (void *)0x00000000,
    (void *)0x00000000, lbl_8031A954, lbl_8031A968, lbl_8031A980,
    (void *)0x00000000, (void *)0x00000000, lbl_8031A99C, lbl_8031A9B0,
    lbl_8031A9CC, (void *)0x00000000, (void *)0x00000000, lbl_8031A9E8,
    lbl_8031A9FC, lbl_8031AA18, (void *)0x00000000, (void *)0x00000000,
    lbl_8031AA34, lbl_8031AA48, lbl_8031AA5C, lbl_8031AA70,
    lbl_8031AA88, lbl_8031AA98, (void *)0x00000000, (void *)0x00000000,
    lbl_8031AAB0, lbl_8031AACC, lbl_8031AAE4, lbl_8031AB00,
    lbl_8031AB14, lbl_8031AB2C, lbl_8031AB40, (void *)0x00000000,
    (void *)0x00000000, lbl_8031AB5C, lbl_8031AB6C, lbl_8031AB84,
    lbl_8031AB98, lbl_8031ABAC, lbl_8031ABBC, lbl_8031ABCC,
    lbl_8031ABE0, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_804019D0[49] = {
    lbl_8031ABF8, lbl_8031AC0C, lbl_8031AC0C, (void *)0x00000000,
    (void *)0x00000000, lbl_8031AC28, lbl_8031AC40, lbl_8031AC5C,
    (void *)0x00000000, (void *)0x00000000, lbl_8031AC78, lbl_8031AC8C,
    lbl_8031ACA8, (void *)0x00000000, (void *)0x00000000, lbl_8031ACC8,
    lbl_8031ACDC, lbl_8031ACF8, (void *)0x00000000, (void *)0x00000000,
    lbl_8031AD18, lbl_8031AD2C, lbl_8031AD40, lbl_8031AD54,
    lbl_8031AD70, lbl_8031AD84, (void *)0x00000000, (void *)0x00000000,
    lbl_8031AD9C, lbl_8031ADB8, lbl_8031ADD0, lbl_8031ADEC,
    lbl_8031AE00, lbl_8031AE18, lbl_8031AE30, (void *)0x00000000,
    (void *)0x00000000, lbl_8031AE4C, lbl_8031AE60, lbl_8031AE78,
    lbl_8031AE90, lbl_8031AEA4, lbl_8031AEB8, lbl_8031AECC,
    lbl_8031AEE0, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_80401A94[49] = {
    lbl_8031AEFC, lbl_8031AF10, lbl_8031AF10, (void *)0x00000000,
    (void *)0x00000000, lbl_8031AF28, lbl_8031AF40, lbl_8031AF5C,
    (void *)0x00000000, (void *)0x00000000, lbl_8031AF78, lbl_8031AF8C,
    lbl_8031AFA8, (void *)0x00000000, (void *)0x00000000, lbl_8031AFC4,
    lbl_8031AFD8, lbl_8031AFF4, (void *)0x00000000, (void *)0x00000000,
    lbl_8031B010, lbl_8031B024, lbl_8031B038, lbl_8031B04C,
    lbl_8031B064, lbl_8031B078, (void *)0x00000000, (void *)0x00000000,
    lbl_8031B090, lbl_8031B0AC, lbl_8031B0C4, lbl_8031B0E0,
    lbl_8031B0F4, lbl_8031B10C, lbl_8031B124, (void *)0x00000000,
    (void *)0x00000000, lbl_8031B140, lbl_8031B150, lbl_8031B168,
    lbl_8031B17C, lbl_8031B190, lbl_8031B1A4, lbl_8031B1B4,
    lbl_8031B1C8, lbl_8031B1E0, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_80401B58[49] = {
    lbl_8031B1F8, lbl_8031B20C, lbl_8031B20C, (void *)0x00000000,
    (void *)0x00000000, lbl_8031B224, lbl_8031B23C, lbl_8031B258,
    (void *)0x00000000, (void *)0x00000000, lbl_8031B274, lbl_8031B288,
    lbl_8031B2A4, (void *)0x00000000, (void *)0x00000000, lbl_8031B2C0,
    lbl_8031B2D4, lbl_8031B2F0, (void *)0x00000000, (void *)0x00000000,
    lbl_8031B30C, lbl_8031B320, lbl_8031B334, lbl_8031B348,
    lbl_8031B360, lbl_8031B374, (void *)0x00000000, (void *)0x00000000,
    lbl_8031B38C, lbl_8031B3A8, lbl_8031B3C0, lbl_8031B3DC,
    lbl_8031B3F0, lbl_8031B408, lbl_8031B420, (void *)0x00000000,
    (void *)0x00000000, lbl_8031B43C, lbl_8031B44C, lbl_8031B464,
    lbl_8031B478, lbl_8031B48C, lbl_8031B4A0, lbl_8031B4B0,
    lbl_8031B4C4, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_80401C1C[49] = {
    lbl_8031B4DC, lbl_8031B4F0, lbl_8031B4F0, (void *)0x00000000,
    (void *)0x00000000, lbl_8031B508, lbl_8031B520, lbl_8031B53C,
    (void *)0x00000000, (void *)0x00000000, lbl_8031B558, lbl_8031B56C,
    lbl_8031B588, (void *)0x00000000, (void *)0x00000000, lbl_8031B5A4,
    lbl_8031B5B8, lbl_8031B5D4, (void *)0x00000000, (void *)0x00000000,
    lbl_8031B5F0, lbl_8031B604, lbl_8031B618, lbl_8031B62C,
    lbl_8031B644, lbl_8031B658, (void *)0x00000000, (void *)0x00000000,
    lbl_8031B670, lbl_8031B68C, lbl_8031B6A4, lbl_8031B6C0,
    lbl_8031B6D4, lbl_8031B6EC, lbl_8031B704, (void *)0x00000000,
    (void *)0x00000000, lbl_8031B720, lbl_8031B730, lbl_8031B748,
    lbl_8031B75C, lbl_8031B770, lbl_8031B784, lbl_8031B794,
    lbl_8031B7A8, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000,
};
/* The layout readers know as CharacterData (include/game/types/CharacterData.h). */
typedef struct CharacterDataRow {
    void *name;
    void *driver_model;
    void *kart_model;
    void *p0C[4];
    float anim1C;
    unsigned char flag20;
    unsigned char pad21[3];
    float anim24;
    unsigned int x28;
} CharacterDataRow;
CharacterDataRow g_characterDataTable[15] = {
    { lbl_8031B7C0, lbl_8031B7CC, lbl_8031B7E0, lbl_8031B7F4, lbl_8031B808, lbl_8031B818, RaceScene_GetPerspFovyForCup_data_804012EC, 30.0f, 0, { 0, 0, 0 }, 50.0f, 0 },
    { lbl_8031B82C, lbl_8031B838, lbl_8031B84C, lbl_8031B860, lbl_8031B874, lbl_8031B884, RaceScene_GetPerspFovyForCup_data_804013B0, 30.0f, 0, { 0, 0, 0 }, 50.0f, 0 },
    { lbl_8031B898, lbl_8031B8A4, lbl_8031B8B8, lbl_8031B8CC, lbl_8031B8E0, lbl_8031B8F0, RaceScene_GetPerspFovyForCup_data_80401474, 40.0f, 0, { 0, 0, 0 }, 50.0f, 0 },
    { lbl_8031B904, lbl_8031B910, lbl_8031B924, lbl_8031B938, lbl_8031B94C, lbl_8031B95C, RaceScene_GetPerspFovyForCup_data_80401538, 60.0f, 1, { 0, 0, 0 }, 50.0f, 0 },
    { lbl_8031B970, lbl_8031B97C, lbl_8031B990, lbl_8031B9A4, lbl_8031B9B8, lbl_8031B9C8, RaceScene_GetPerspFovyForCup_data_804015FC, 30.0f, 0, { 0, 0, 0 }, 60.0f, 0 },
    { lbl_8031B9DC, lbl_8031B9E8, lbl_8031B9FC, lbl_8031BA10, lbl_8031BA24, lbl_8031BA34, RaceScene_GetPerspFovyForCup_data_804016C0, 60.0f, 0, { 0, 0, 0 }, 30.0f, 0 },
    { lbl_8031BA48, lbl_8031BA54, lbl_8031BA68, lbl_8031BA7C, lbl_8031BA90, lbl_8031BAA0, RaceScene_GetPerspFovyForCup_data_80401784, 40.0f, 0, { 0, 0, 0 }, 40.0f, 0 },
    { lbl_8031BAB4, lbl_8031BAC0, lbl_8031BAD4, lbl_8031BAE8, lbl_8031BAFC, lbl_8031BB0C, RaceScene_GetPerspFovyForCup_data_80401848, 60.0f, 0, { 0, 0, 0 }, 50.0f, 0 },
    { lbl_8031BB20, lbl_8031BB2C, lbl_8031BB40, lbl_8031BB54, lbl_8031BB68, lbl_8031BB78, RaceScene_GetPerspFovyForCup_data_8040190C, 60.0f, 0, { 0, 0, 0 }, 50.0f, 0 },
    { lbl_8031BB8C, lbl_8031BB98, lbl_8031BBAC, lbl_8031BBC0, lbl_8031BBD4, lbl_8031BBE8, RaceScene_GetPerspFovyForCup_data_804019D0, 40.0f, 0, { 0, 0, 0 }, 40.0f, 0 },
    { lbl_8031BBFC, lbl_8031BC08, lbl_8031BC1C, lbl_8031BC30, lbl_8031BC44, lbl_8031BC54, RaceScene_GetPerspFovyForCup_data_80401A94, 60.0f, 0, { 0, 0, 0 }, 40.0f, 0 },
    { lbl_8031BC68, lbl_8031BC74, lbl_8031BC88, lbl_8031BC9C, lbl_8031BCB0, lbl_8031BCC0, RaceScene_GetPerspFovyForCup_data_80401B58, 60.0f, 0, { 0, 0, 0 }, 60.0f, 0 },
    { lbl_8031BCD4, lbl_8031BCE0, lbl_8031BCF4, lbl_8031BD08, lbl_8031BD1C, lbl_8031BD2C, RaceScene_GetPerspFovyForCup_data_80401C1C, 60.0f, 0, { 0, 0, 0 }, 60.0f, 0 },
    { lbl_8031BD40, 0, 0, 0, 0, 0, 0, 30.0f, 0, { 0, 0, 0 }, 30.0f, 0 },
    { lbl_8031BD40, 0, 0, 0, 0, 0, 0, 30.0f, 0, { 0, 0, 0 }, 30.0f, 0 }
};
void *RaceScene_GetPerspFovyForCup_data_80401F74[80] = {
    (void *)0xC253982B, (void *)0x00000000, (void *)0xC2E54C64, (void *)0x00000001,
    (void *)0xC1CCAA60, (void *)0x00000000, (void *)0xC2E409E2, (void *)0x00000001,
    (void *)0xBF06C94B, (void *)0x00000000, (void *)0xC2E48B85, (void *)0x00000001,
    (void *)0x41D063B8, (void *)0x00000000, (void *)0xC2E4CBAC, (void *)0x00000001,
    (void *)0x425E6507, (void *)0x00000000, (void *)0xC2E849AD, (void *)0x00000001,
    (void *)0xC2210CEA, (void *)0x00000000, (void *)0xC31EE00D, (void *)0x00000001,
    (void *)0xC14F27A6, (void *)0x00000000, (void *)0xC31E3ECC, (void *)0x00000001,
    (void *)0x4141C083, (void *)0x00000000, (void *)0xC31E7F9E, (void *)0x00000001,
    (void *)0x421ABD1F, (void *)0x00000000, (void *)0xC31E9FB1, (void *)0x00000001,
    (void *)0x42887825, (void *)0x00000000, (void *)0xC3205EB2, (void *)0x00000001,
    (void *)0x44C31D1F, (void *)0x00000000, (void *)0x3EF9EE03, (void *)0x00000001,
    (void *)0x44C6BB33, (void *)0x00000000, (void *)0x4105AC10, (void *)0x00000001,
    (void *)0x44CAA72B, (void *)0x00000000, (void *)0x418308D9, (void *)0x00000001,
    (void *)0x44CE63F0, (void *)0x00000000, (void *)0x41C12DE0, (void *)0x00000001,
    (void *)0x44D1C548, (void *)0x00000000, (void *)0x4200D346, (void *)0x00000001,
    (void *)0x44C35810, (void *)0x00000000, (void *)0x42401793, (void *)0x00000001,
    (void *)0x44C78C9C, (void *)0x00000000, (void *)0x426BBDC5, (void *)0x00000001,
    (void *)0x44CBB493, (void *)0x00000000, (void *)0x428984A1, (void *)0x00000001,
    (void *)0x44CF3CD5, (void *)0x00000000, (void *)0x429FD32B, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804020B4[80] = {
    (void *)0xC253982B, (void *)0x00000000, (void *)0xC2E54C64, (void *)0x00000001,
    (void *)0xC1CCAA60, (void *)0x00000000, (void *)0xC2E409E2, (void *)0x00000001,
    (void *)0xBF06C94B, (void *)0x00000000, (void *)0xC2E48B85, (void *)0x00000001,
    (void *)0x41D063B8, (void *)0x00000000, (void *)0xC2E4CBAC, (void *)0x00000001,
    (void *)0x425E6507, (void *)0x00000000, (void *)0xC2E849AD, (void *)0x00000001,
    (void *)0xC2210CEA, (void *)0x00000000, (void *)0xC31EE00D, (void *)0x00000001,
    (void *)0xC14F27A6, (void *)0x00000000, (void *)0xC31E3ECC, (void *)0x00000001,
    (void *)0x4141C083, (void *)0x00000000, (void *)0xC31E7F9E, (void *)0x00000001,
    (void *)0x421ABD1F, (void *)0x00000000, (void *)0xC31E9FB1, (void *)0x00000001,
    (void *)0x42887825, (void *)0x00000000, (void *)0xC3205EB2, (void *)0x00000001,
    (void *)0x44C3660C, (void *)0x00000000, (void *)0xC40A8E86, (void *)0x00000001,
    (void *)0x44C5D625, (void *)0x00000000, (void *)0xC4050E6F, (void *)0x00000001,
    (void *)0x44C8547B, (void *)0x00000000, (void *)0xC3FDF0EF, (void *)0x00000001,
    (void *)0x44CAF9CB, (void *)0x00000000, (void *)0xC3F15A2D, (void *)0x00000001,
    (void *)0x44C33B4C, (void *)0x00000000, (void *)0xC3F713C7, (void *)0x00000001,
    (void *)0x44C062A0, (void *)0x00000000, (void *)0xC400D246, (void *)0x00000001,
    (void *)0x44C5D7BE, (void *)0x00000000, (void *)0xC3EB8CF4, (void *)0x00000001,
    (void *)0x44CD1F23, (void *)0x00000000, (void *)0xC3E56189, (void *)0x00000001,
    (void *)0x44C8BB44, (void *)0x00000000, (void *)0xC3DF17AE, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804021F4[80] = {
    (void *)0xC2AC4BF5, (void *)0x00000000, (void *)0xC4A3CF2B, (void *)0x00000001,
    (void *)0xC25AB2D7, (void *)0x00000000, (void *)0xC4A3BB02, (void *)0x00000001,
    (void *)0xC1A2185F, (void *)0x00000000, (void *)0xC4A3C31B, (void *)0x00000001,
    (void *)0x4185ABEE, (void *)0x00000000, (void *)0xC4A3A5DB, (void *)0x00000001,
    (void *)0x424582A2, (void *)0x00000000, (void *)0xC4A3BC7B, (void *)0x00000001,
    (void *)0xC2868CC8, (void *)0x00000000, (void *)0xC4AB6AA8, (void *)0x00000001,
    (void *)0xC20B0BFE, (void *)0x00000000, (void *)0xC4AB567F, (void *)0x00000001,
    (void *)0xC01B65DC, (void *)0x00000000, (void *)0xC4AB7FD7, (void *)0x00000001,
    (void *)0x41F3137A, (void *)0x00000000, (void *)0xC4AB83DF, (void *)0x00000001,
    (void *)0x428457F9, (void *)0x00000000, (void *)0xC4AB7937, (void *)0x00000001,
    (void *)0x445F6FA4, (void *)0x00000000, (void *)0x4454FF0E, (void *)0x00000001,
    (void *)0x44562417, (void *)0x00000000, (void *)0x4454E51F, (void *)0x00000001,
    (void *)0x444CFBB1, (void *)0x00000000, (void *)0x44553A6D, (void *)0x00000001,
    (void *)0x44438363, (void *)0x00000000, (void *)0x4454D79E, (void *)0x00000001,
    (void *)0x44643FF5, (void *)0x00000000, (void *)0x44466201, (void *)0x00000001,
    (void *)0x445B2D05, (void *)0x00000000, (void *)0x4446AC80, (void *)0x00000001,
    (void *)0x44521CAF, (void *)0x00000000, (void *)0x4446BB28, (void *)0x00000001,
    (void *)0x4448B064, (void *)0x00000000, (void *)0x44468E89, (void *)0x00000001,
    (void *)0x443F7261, (void *)0x00000000, (void *)0x444651D1, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80402334[64] = {
    (void *)0xC4C8B3C7, (void *)0x00000000, (void *)0xC49CBB4C, (void *)0x00000001,
    (void *)0xC4C5DF12, (void *)0x00000000, (void *)0xC49FFB75, (void *)0x00000001,
    (void *)0xC4C31410, (void *)0x00000000, (void *)0xC4A3E3F8, (void *)0x00000001,
    (void *)0xC4C00A04, (void *)0x00000000, (void *)0xC4A84558, (void *)0x00000001,
    (void *)0xC4C9B148, (void *)0x00000000, (void *)0xC4A77948, (void *)0x00000001,
    (void *)0xC4C6A979, (void *)0x00000000, (void *)0xC4AB0571, (void *)0x00000001,
    (void *)0xC4C39723, (void *)0x00000000, (void *)0xC4AE2F2B, (void *)0x00000001,
    (void *)0xC4C02906, (void *)0x00000000, (void *)0xC4B186D9, (void *)0x00000001,
    (void *)0xC3FD57A8, (void *)0x00000000, (void *)0xC393C687, (void *)0x00000001,
    (void *)0xC3F67017, (void *)0x00000000, (void *)0xC3A4761E, (void *)0x00000001,
    (void *)0xC3EEF53F, (void *)0x00000000, (void *)0xC3B24536, (void *)0x00000001,
    (void *)0xC3E80DAC, (void *)0x00000000, (void *)0xC3C13AE8, (void *)0x00000001,
    (void *)0xC3E5C079, (void *)0x00000000, (void *)0xC3929FF0, (void *)0x00000001,
    (void *)0xC3DED8E9, (void *)0x00000000, (void *)0xC3A228F2, (void *)0x00000001,
    (void *)0xC3D9AB36, (void *)0x00000000, (void *)0xC3B36BD0, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80402434[92] = {
    (void *)0xC495BE1D, (void *)0x00000000, (void *)0xC3D8DB3D, (void *)0x00000001,
    (void *)0xC491092F, (void *)0x00000000, (void *)0xC3D98DBC, (void *)0x00000001,
    (void *)0xC48C279E, (void *)0x00000000, (void *)0xC3D8DB3D, (void *)0x00000001,
    (void *)0xC4879F54, (void *)0x00000000, (void *)0xC3D98DBC, (void *)0x00000001,
    (void *)0xC493A68F, (void *)0x00000000, (void *)0xC3EFDDE7, (void *)0x00000001,
    (void *)0xC48E986A, (void *)0x00000000, (void *)0xC3F09066, (void *)0x00000001,
    (void *)0xC489B6E1, (void *)0x00000000, (void *)0xC3F09066, (void *)0x00000001,
    (void *)0x44FA8FF8, (void *)0x00000000, (void *)0x44888AC1, (void *)0x00000001,
    (void *)0x44F0DA35, (void *)0x00000000, (void *)0x4496B106, (void *)0x00000001,
    (void *)0x44FC09BA, (void *)0x00000000, (void *)0x44969E2D, (void *)0x00000001,
    (void *)0x44F891E3, (void *)0x00000000, (void *)0x44902E56, (void *)0x00000001,
    (void *)0x44F35F7D, (void *)0x00000000, (void *)0x44906C83, (void *)0x00000001,
    (void *)0x44F5F862, (void *)0x00000000, (void *)0x4496CC31, (void *)0x00000001,
    (void *)0x44F5E106, (void *)0x00000000, (void *)0x4488A39E, (void *)0x00000001,
    (void *)0x44F12C19, (void *)0x00000000, (void *)0x4488D042, (void *)0x00000001,
    (void *)0x4434DBC8, (void *)0x00000000, (void *)0xC3ED1B54, (void *)0x00000001,
    (void *)0x44364E0B, (void *)0x00000000, (void *)0xC3AA8439, (void *)0x00000001,
    (void *)0x4435755B, (void *)0x00000000, (void *)0xC3D64E74, (void *)0x00000001,
    (void *)0x4435DEAA, (void *)0x00000000, (void *)0xC3BFDB12, (void *)0x00000001,
    (void *)0x44233F3F, (void *)0x00000000, (void *)0xC3C976E9, (void *)0x00000001,
    (void *)0x44229046, (void *)0x00000000, (void *)0xC3E0C16C, (void *)0x00000001,
    (void *)0x44247034, (void *)0x00000000, (void *)0xC3B31D8E, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804025A4[96] = {
    (void *)0x451828C9, (void *)0x00000000, (void *)0x44B1930A, (void *)0x00000001,
    (void *)0x4519ABB2, (void *)0x00000000, (void *)0x44A7F831, (void *)0x00000001,
    (void *)0x4517ED37, (void *)0x00000000, (void *)0x44D6EA25, (void *)0x00000001,
    (void *)0x4517E396, (void *)0x00000000, (void *)0x44C3D235, (void *)0x00000001,
    (void *)0x45197825, (void *)0x00000000, (void *)0x44DED9FC, (void *)0x00000001,
    (void *)0x451809F4, (void *)0x00000000, (void *)0x44E8239E, (void *)0x00000001,
    (void *)0x451942A4, (void *)0x00000000, (void *)0x44CD44CD, (void *)0x00000001,
    (void *)0x45192E56, (void *)0x00000000, (void *)0x44BA4B5C, (void *)0x00000001,
    (void *)0xC495BE1D, (void *)0x00000000, (void *)0xC3D8DB3D, (void *)0x00000001,
    (void *)0xC491092F, (void *)0x00000000, (void *)0xC3D98DBC, (void *)0x00000001,
    (void *)0xC48C279E, (void *)0x00000000, (void *)0xC3D8DB3D, (void *)0x00000001,
    (void *)0xC4879F54, (void *)0x00000000, (void *)0xC3D98DBC, (void *)0x00000001,
    (void *)0xC493A68F, (void *)0x00000000, (void *)0xC3EFDDE7, (void *)0x00000001,
    (void *)0xC48E986A, (void *)0x00000000, (void *)0xC3F09066, (void *)0x00000001,
    (void *)0xC489B6E1, (void *)0x00000000, (void *)0xC3F09066, (void *)0x00000001,
    (void *)0x45180C46, (void *)0x00000000, (void *)0xC51AC235, (void *)0x00000001,
    (void *)0x451A66BC, (void *)0x00000000, (void *)0xC51AD887, (void *)0x00000001,
    (void *)0x451CD781, (void *)0x00000000, (void *)0xC51AC235, (void *)0x00000001,
    (void *)0x4517A873, (void *)0x00000000, (void *)0xC51481F0, (void *)0x00000001,
    (void *)0x451A95DF, (void *)0x00000000, (void *)0xC51476E9, (void *)0x00000001,
    (void *)0x451D1CEE, (void *)0x00000000, (void *)0xC51470C5, (void *)0x00000001,
    (void *)0x451B8AE9, (void *)0x00000000, (void *)0xC517CD64, (void *)0x00000001,
    (void *)0x45193073, (void *)0x00000000, (void *)0xC517B712, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80402724[200] = {
    (void *)0x45729F0A, (void *)0x00000000, (void *)0xC405DB3A, (void *)0x00000001,
    (void *)0x4576362D, (void *)0x00000000, (void *)0xC40550E0, (void *)0x00000001,
    (void *)0x457A4748, (void *)0x00000000, (void *)0xC4061433, (void *)0x00000001,
    (void *)0x457E2554, (void *)0x00000000, (void *)0xC405C027, (void *)0x00000001,
    (void *)0x4574F87F, (void *)0x00000000, (void *)0xC3E7D47B, (void *)0x00000001,
    (void *)0x45787F4C, (void *)0x00000000, (void *)0xC3E9C5E3, (void *)0x00000001,
    (void *)0xC574E9CF, (void *)0x00000000, (void *)0x458997A2, (void *)0x00000001,
    (void *)0xC5725B06, (void *)0x00000000, (void *)0x45898F39, (void *)0x00000001,
    (void *)0xC56FB6AC, (void *)0x00000000, (void *)0x4589977F, (void *)0x00000001,
    (void *)0xC569AC77, (void *)0x00000000, (void *)0x458AEEC3, (void *)0x00000001,
    (void *)0xC56E449C, (void *)0x00000000, (void *)0x458AF983, (void *)0x00000001,
    (void *)0xC5778CB0, (void *)0x00000000, (void *)0x458999F4, (void *)0x00000001,
    (void *)0xC56BF3AE, (void *)0x00000000, (void *)0x458AF237, (void *)0x00000001,
    (void *)0xC578CA25, (void *)0x00000000, (void *)0x458AE164, (void *)0x00000001,
    (void *)0xC5761A4E, (void *)0x00000000, (void *)0x458AE164, (void *)0x00000001,
    (void *)0xC5738252, (void *)0x00000000, (void *)0x458AE7F4, (void *)0x00000001,
    (void *)0xC570D0C9, (void *)0x00000000, (void *)0x458AF40C, (void *)0x00000001,
    (void *)0x45985314, (void *)0x00000000, (void *)0xC516621D, (void *)0x00000001,
    (void *)0xC5932A00, (void *)0x00000000, (void *)0xC4FA03DF, (void *)0x00000001,
    (void *)0xC5932C60, (void *)0x00000000, (void *)0xC500DC00, (void *)0x00000001,
    (void *)0xC59330D5, (void *)0x00000000, (void *)0xC5045C29, (void *)0x00000001,
    (void *)0x459D0E83, (void *)0x00000000, (void *)0xC5166979, (void *)0x00000001,
    (void *)0x4599E573, (void *)0x00000000, (void *)0xC5167D3B, (void *)0x00000001,
    (void *)0x459B774A, (void *)0x00000000, (void *)0xC5166979, (void *)0x00000001,
    (void *)0x4598CC50, (void *)0x00000000, (void *)0xC511B5D7, (void *)0x00000001,
    (void *)0x459A6677, (void *)0x00000000, (void *)0xC51192FE, (void *)0x00000001,
    (void *)0xC590F93B, (void *)0x00000000, (void *)0xC4EF94FE, (void *)0x00000001,
    (void *)0xC59336E1, (void *)0x00000000, (void *)0xC4F34831, (void *)0x00000001,
    (void *)0xC5933042, (void *)0x00000000, (void *)0xC4ECE33B, (void *)0x00000001,
    (void *)0xC5A23EE1, (void *)0x00000000, (void *)0xC40114CB, (void *)0x00000001,
    (void *)0xC5A249F6, (void *)0x00000000, (void *)0xC3EBC4D0, (void *)0x00000001,
    (void *)0xC5A245DF, (void *)0x00000000, (void *)0xC3D0F14E, (void *)0x00000001,
    (void *)0xC5A24C1F, (void *)0x00000000, (void *)0xC3B82AFB, (void *)0x00000001,
    (void *)0xC5A247E5, (void *)0x00000000, (void *)0xC3A0059F, (void *)0x00000001,
    (void *)0xC5A23D44, (void *)0x00000000, (void *)0xC388E748, (void *)0x00000001,
    (void *)0xC5A45EF2, (void *)0x00000000, (void *)0xC3945FDC, (void *)0x00000001,
    (void *)0x457BF56D, (void *)0x00000000, (void *)0xC3E9C5E3, (void *)0x00000001,
    (void *)0x45800654, (void *)0x00000000, (void *)0xC3E9C5E3, (void *)0x00000001,
    (void *)0x459C1546, (void *)0x00000000, (void *)0xC51192FE, (void *)0x00000001,
    (void *)0x459DA2EC, (void *)0x00000000, (void *)0xC51171DB, (void *)0x00000001,
    (void *)0xC5910AA2, (void *)0x00000000, (void *)0xC4F73179, (void *)0x00000001,
    (void *)0xC5910AA2, (void *)0x00000000, (void *)0xC4FDFD2F, (void *)0x00000001,
    (void *)0xC5910AA2, (void *)0x00000000, (void *)0xC502CCD5, (void *)0x00000001,
    (void *)0xC5A46A29, (void *)0x00000000, (void *)0xC3AE4EBF, (void *)0x00000001,
    (void *)0xC5A4755E, (void *)0x00000000, (void *)0xC3C56FE9, (void *)0x00000001,
    (void *)0xC5A46A29, (void *)0x00000000, (void *)0xC3DF5ECF, (void *)0x00000001,
    (void *)0xC5A46A29, (void *)0x00000000, (void *)0xC3F89A41, (void *)0x00000001,
    (void *)0xC56D30D5, (void *)0x00000000, (void *)0x4589977F, (void *)0x00000001,
    (void *)0xC56AAB02, (void *)0x00000000, (void *)0x45898E44, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80402A44[200] = {
    (void *)0x459E39F0, (void *)0x00000000, (void *)0xC5165D27, (void *)0x00000001,
    (void *)0x4598F7DB, (void *)0x00000000, (void *)0xC512439E, (void *)0x00000001,
    (void *)0x459A9510, (void *)0x00000000, (void *)0xC51223E3, (void *)0x00000001,
    (void *)0xC57A32A4, (void *)0x00000000, (void *)0xC3E14F35, (void *)0x00000001,
    (void *)0xC57A325E, (void *)0x00000000, (void *)0xC3CD2E84, (void *)0x00000001,
    (void *)0xC57A2AC5, (void *)0x00000000, (void *)0xC3B4C44A, (void *)0x00000001,
    (void *)0xC57A36B0, (void *)0x00000000, (void *)0xC39A574C, (void *)0x00000001,
    (void *)0xC57A25CB, (void *)0x00000000, (void *)0xC3837E53, (void *)0x00000001,
    (void *)0xC57E22D5, (void *)0x00000000, (void *)0xC3D963DA, (void *)0x00000001,
    (void *)0xC57E15FC, (void *)0x00000000, (void *)0xC3C0F05C, (void *)0x00000001,
    (void *)0xC5AE7C8B, (void *)0x00000000, (void *)0x452E84A0, (void *)0x00000001,
    (void *)0xC5AA087F, (void *)0x00000000, (void *)0x45258CF2, (void *)0x00000001,
    (void *)0xC5ABA36D, (void *)0x00000000, (void *)0x45268B60, (void *)0x00000001,
    (void *)0xC5AA0625, (void *)0x00000000, (void *)0x4529DA56, (void *)0x00000001,
    (void *)0xC5ACE858, (void *)0x00000000, (void *)0x45277BC7, (void *)0x00000001,
    (void *)0xC5AB784E, (void *)0x00000000, (void *)0x452B2337, (void *)0x00000001,
    (void *)0xC5ACF6D5, (void *)0x00000000, (void *)0x452C95DF, (void *)0x00000001,
    (void *)0xC5A8B0A2, (void *)0x00000000, (void *)0x452866D5, (void *)0x00000001,
    (void *)0xC5AEBD5C, (void *)0x00000000, (void *)0x4528937D, (void *)0x00000001,
    (void *)0xC5B07075, (void *)0x00000000, (void *)0x45298C1D, (void *)0x00000001,
    (void *)0x459C3AF0, (void *)0x00000000, (void *)0xC511F0C1, (void *)0x00000001,
    (void *)0x459DADAA, (void *)0x00000000, (void *)0xC511F0C1, (void *)0x00000001,
    (void *)0xC57DF9CF, (void *)0x00000000, (void *)0xC3A927C2, (void *)0x00000001,
    (void *)0xC57DF9CF, (void *)0x00000000, (void *)0xC38DD924, (void *)0x00000001,
    (void *)0xC57DF9CF, (void *)0x00000000, (void *)0xC36DE412, (void *)0x00000001,
    (void *)0x4572FAB8, (void *)0x00000000, (void *)0xC40F7751, (void *)0x00000001,
    (void *)0x45757FD7, (void *)0x00000000, (void *)0xC40F852A, (void *)0x00000001,
    (void *)0x4578E6E5, (void *)0x00000000, (void *)0xC40FFC66, (void *)0x00000001,
    (void *)0x457F50E5, (void *)0x00000000, (void *)0xC40F6932, (void *)0x00000001,
    (void *)0x457C1CA4, (void *)0x00000000, (void *)0xC40F327D, (void *)0x00000001,
    (void *)0x4574611B, (void *)0x00000000, (void *)0xC3F7DCA5, (void *)0x00000001,
    (void *)0x4577981D, (void *)0x00000000, (void *)0xC3F7BC92, (void *)0x00000001,
    (void *)0x457A97D7, (void *)0x00000000, (void *)0xC3F517EC, (void *)0x00000001,
    (void *)0xC583DD9A, (void *)0x00000000, (void *)0x44A3D000, (void *)0x00000001,
    (void *)0xC5840BFC, (void *)0x00000000, (void *)0x44A9B408, (void *)0x00000001,
    (void *)0xC58467CD, (void *)0x00000000, (void *)0x44AF60D5, (void *)0x00000001,
    (void *)0xC584B9E9, (void *)0x00000000, (void *)0x44B59927, (void *)0x00000001,
    (void *)0xC585319C, (void *)0x00000000, (void *)0x44BBE52F, (void *)0x00000001,
    (void *)0xC5858B81, (void *)0x00000000, (void *)0x44C0BC08, (void *)0x00000001,
    (void *)0xC585C1BC, (void *)0x00000000, (void *)0x44A4A66F, (void *)0x00000001,
    (void *)0x457DB7BE, (void *)0x00000000, (void *)0xC3F70429, (void *)0x00000001,
    (void *)0xC5862802, (void *)0x00000000, (void *)0x44AB3DDB, (void *)0x00000001,
    (void *)0xC58674B6, (void *)0x00000000, (void *)0x44B0D5A2, (void *)0x00000001,
    (void *)0xC586CE35, (void *)0x00000000, (void *)0x44B6D3A6, (void *)0x00000001,
    (void *)0xC58727B4, (void *)0x00000000, (void *)0x44BD37F8, (void *)0x00000001,
    (void *)0x45985314, (void *)0x00000000, (void *)0xC516621D, (void *)0x00000001,
    (void *)0x459CEF3D, (void *)0x00000000, (void *)0xC51654A0, (void *)0x00000001,
    (void *)0x4599B9E1, (void *)0x00000000, (void *)0xC51660D1, (void *)0x00000001,
    (void *)0x459B6F3B, (void *)0x00000000, (void *)0xC51654A0, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80402D64[64] = {
    (void *)0xC27F1B23, (void *)0x00000000, (void *)0xC5360D12, (void *)0x00000001,
    (void *)0xC1D0FAE7, (void *)0x00000000, (void *)0xC5362360, (void *)0x00000001,
    (void *)0x414ED29E, (void *)0x00000000, (void *)0xC5360D12, (void *)0x00000001,
    (void *)0x4244BDEE, (void *)0x00000000, (void *)0xC5362360, (void *)0x00000001,
    (void *)0xC23C2969, (void *)0x00000000, (void *)0xC538ED64, (void *)0x00000001,
    (void *)0xC0D326C0, (void *)0x00000000, (void *)0xC53903B6, (void *)0x00000001,
    (void *)0x4201CC42, (void *)0x00000000, (void *)0xC53903B6, (void *)0x00000001,
    (void *)0x4498BC5A, (void *)0x00000000, (void *)0xC4444F64, (void *)0x00000001,
    (void *)0x449E5439, (void *)0x00000000, (void *)0xC4405A51, (void *)0x00000001,
    (void *)0x44A3B775, (void *)0x00000000, (void *)0xC43BF387, (void *)0x00000001,
    (void *)0x449D4677, (void *)0x00000000, (void *)0xC42E995A, (void *)0x00000001,
    (void *)0x44A2C000, (void *)0x00000000, (void *)0xC42858E7, (void *)0x00000001,
    (void *)0x44A78D48, (void *)0x00000000, (void *)0xC421EB38, (void *)0x00000001,
    (void *)0x44A918E5, (void *)0x00000000, (void *)0xC43778C5, (void *)0x00000001,
    (void *)0x44981AFA, (void *)0x00000000, (void *)0xC434D7E4, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80402E64[92] = {
    (void *)0x44D705B2, (void *)0x00000000, (void *)0xC40D050B, (void *)0x00000001,
    (void *)0x44DD9354, (void *)0x00000000, (void *)0xC40538CA, (void *)0x00000001,
    (void *)0x44E34883, (void *)0x00000000, (void *)0xC3FB3D56, (void *)0x00000001,
    (void *)0x44DA9A04, (void *)0x00000000, (void *)0xC3DB6A16, (void *)0x00000001,
    (void *)0x44E0138D, (void *)0x00000000, (void *)0xC3CDA17C, (void *)0x00000001,
    (void *)0x44CE8F64, (void *)0x00000000, (void *)0xC4011030, (void *)0x00000001,
    (void *)0x44E8FBDF, (void *)0x00000000, (void *)0xC3ED28EC, (void *)0x00000001,
    (void *)0x44D45D50, (void *)0x00000000, (void *)0xC3EDE168, (void *)0x00000001,
    (void *)0x45451683, (void *)0x00000000, (void *)0xC559FFA6, (void *)0x00000001,
    (void *)0x4545110A, (void *)0x00000000, (void *)0xC55D2AB0, (void *)0x00000001,
    (void *)0x45454E04, (void *)0x00000000, (void *)0xC560B99A, (void *)0x00000001,
    (void *)0x454ADBA2, (void *)0x00000000, (void *)0xC55E56C9, (void *)0x00000001,
    (void *)0x454B5225, (void *)0x00000000, (void *)0xC561BBCF, (void *)0x00000001,
    (void *)0x45458A19, (void *)0x00000000, (void *)0xC5643242, (void *)0x00000001,
    (void *)0x454A1D1B, (void *)0x00000000, (void *)0xC55AE004, (void *)0x00000001,
    (void *)0xC27F1B23, (void *)0x00000000, (void *)0xC5360D12, (void *)0x00000001,
    (void *)0xC1D0FAE7, (void *)0x00000000, (void *)0xC5362360, (void *)0x00000001,
    (void *)0x414ED29E, (void *)0x00000000, (void *)0xC5360D12, (void *)0x00000001,
    (void *)0x4244BDEE, (void *)0x00000000, (void *)0xC5362360, (void *)0x00000001,
    (void *)0xC23C2969, (void *)0x00000000, (void *)0xC538ED64, (void *)0x00000001,
    (void *)0xC0D326C0, (void *)0x00000000, (void *)0xC53903B6, (void *)0x00000001,
    (void *)0x4201CC42, (void *)0x00000000, (void *)0xC53903B6, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80402FD4[96] = {
    (void *)0xC3C920D5, (void *)0x00000000, (void *)0xC561E906, (void *)0x00000001,
    (void *)0xC46D2912, (void *)0x00000000, (void *)0xC1A0A979, (void *)0x00000001,
    (void *)0xC5290560, (void *)0x00000000, (void *)0xC469630C, (void *)0x00000001,
    (void *)0xC50CCF54, (void *)0x00000000, (void *)0xC5D181F2, (void *)0x00000001,
    (void *)0xC51066FA, (void *)0x00000000, (void *)0xC5D777CF, (void *)0x00000001,
    (void *)0xC3B63EFA, (void *)0x00000000, (void *)0xC560CBC3, (void *)0x00000001,
    (void *)0xC3A42622, (void *)0x00000000, (void *)0xC5603EB0, (void *)0x00000001,
    (void *)0xC46BD8B4, (void *)0x00000000, (void *)0x42390D5D, (void *)0x00000001,
    (void *)0xC525B148, (void *)0x00000000, (void *)0xC452A5DE, (void *)0x00000001,
    (void *)0xC5111175, (void *)0x00000000, (void *)0xC5D49FAE, (void *)0x00000001,
    (void *)0xC393B2E5, (void *)0x00000000, (void *)0xC55F75E7, (void *)0x00000001,
    (void *)0xC46C1C66, (void *)0x00000000, (void *)0x429DE7BC, (void *)0x00000001,
    (void *)0xC52456C5, (void *)0x00000000, (void *)0xC448ECF6, (void *)0x00000001,
    (void *)0xC50CEA39, (void *)0x00000000, (void *)0xC5D4E142, (void *)0x00000001,
    (void *)0xC380EA4E, (void *)0x00000000, (void *)0xC55E5A8F, (void *)0x00000001,
    (void *)0xC46C6EEE, (void *)0x00000000, (void *)0x42E0C40B, (void *)0x00000001,
    (void *)0xC522E48F, (void *)0x00000000, (void *)0xC43DABF3, (void *)0x00000001,
    (void *)0xC50A95E7, (void *)0x00000000, (void *)0xC5D36F2B, (void *)0x00000001,
    (void *)0xC50EDAB4, (void *)0x00000000, (void *)0xC5D2FD6D, (void *)0x00000001,
    (void *)0xC46C5DCE, (void *)0x00000000, (void *)0x417A1C39, (void *)0x00000001,
    (void *)0xC52784DD, (void *)0x00000000, (void *)0xC45E4F85, (void *)0x00000001,
    (void *)0xC512CEFE, (void *)0x00000000, (void *)0xC5D60156, (void *)0x00000001,
    (void *)0xC50ED8E5, (void *)0x00000000, (void *)0xC5D606BA, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80403154[116] = {
    (void *)0xC52DD0D1, (void *)0x00000000, (void *)0xC523DFBA, (void *)0x00000001,
    (void *)0x461AE732, (void *)0x00000000, (void *)0xC5D7DB21, (void *)0x00000001,
    (void *)0x45FB95D3, (void *)0x00000000, (void *)0xC4882A7F, (void *)0x00000001,
    (void *)0x46020DB0, (void *)0x00000000, (void *)0xC592F8EC, (void *)0x00000001,
    (void *)0x45FB939C, (void *)0x00000000, (void *)0xC48F0F3B, (void *)0x00000001,
    (void *)0xC52F444A, (void *)0x00000000, (void *)0xC521890A, (void *)0x00000001,
    (void *)0x460148B8, (void *)0x00000000, (void *)0xC5931EB6, (void *)0x00000001,
    (void *)0x45FBA33D, (void *)0x00000000, (void *)0xC4821821, (void *)0x00000001,
    (void *)0x45FB9AB6, (void *)0x00000000, (void *)0xC495467F, (void *)0x00000001,
    (void *)0x461A2FE1, (void *)0x00000000, (void *)0xC5D7E11F, (void *)0x00000001,
    (void *)0xC52C8B54, (void *)0x00000000, (void *)0xC526581D, (void *)0x00000001,
    (void *)0xC52AF873, (void *)0x00000000, (void *)0xC5291D1B, (void *)0x00000001,
    (void *)0xC5296083, (void *)0x00000000, (void *)0xC52B6EE5, (void *)0x00000001,
    (void *)0x46197243, (void *)0x00000000, (void *)0xC5D7F15A, (void *)0x00000001,
    (void *)0x4618BEDC, (void *)0x00000000, (void *)0xC5D7F34C, (void *)0x00000001,
    (void *)0x46182658, (void *)0x00000000, (void *)0xC5D7DB25, (void *)0x00000001,
    (void *)0xC557CF91, (void *)0x00000000, (void *)0xC28F366A, (void *)0x00000001,
    (void *)0xC557AB12, (void *)0x00000000, (void *)0xC169762B, (void *)0x00000001,
    (void *)0xC557AB12, (void *)0x00000000, (void *)0x42574E6B, (void *)0x00000001,
    (void *)0xC557AB12, (void *)0x00000000, (void *)0x42EFED84, (void *)0x00000001,
    (void *)0xC553F65A, (void *)0x00000000, (void *)0xC230F4EC, (void *)0x00000001,
    (void *)0xC553F65A, (void *)0x00000000, (void *)0x419CF0C3, (void *)0x00000001,
    (void *)0xC553F65A, (void *)0x00000000, (void *)0x42AB8280, (void *)0x00000001,
    (void *)0x45FBA33D, (void *)0x00000000, (void *)0xC477055B, (void *)0x00000001,
    (void *)0x4602D54B, (void *)0x00000000, (void *)0xC592B664, (void *)0x00000001,
    (void *)0x4603A7FD, (void *)0x00000000, (void *)0xC5928A0A, (void *)0x00000001,
    (void *)0x460490DB, (void *)0x00000000, (void *)0xC5923156, (void *)0x00000001,
    (void *)0x461B8FC4, (void *)0x00000000, (void *)0xC5D7DB21, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80403324[204] = {
    (void *)0xC5669C98, (void *)0x00000000, (void *)0xC66E4AB8, (void *)0x00000001,
    (void *)0xC56D4779, (void *)0x00000000, (void *)0xC66E9F7B, (void *)0x00000001,
    (void *)0xC43E481A, (void *)0x00000000, (void *)0xC5B93421, (void *)0x00000001,
    (void *)0xC4555ECC, (void *)0x00000000, (void *)0xC5B7EE6A, (void *)0x00000001,
    (void *)0xC56393EC, (void *)0x00000000, (void *)0xC66E2129, (void *)0x00000001,
    (void *)0xC569E3DF, (void *)0x00000000, (void *)0xC66E7652, (void *)0x00000001,
    (void *)0xC4334E8C, (void *)0x00000000, (void *)0xC5B9D0DF, (void *)0x00000001,
    (void *)0xC449E87E, (void *)0x00000000, (void *)0xC5B889A8, (void *)0x00000001,
    (void *)0xC52E46EE, (void *)0x00000000, (void *)0xC638A971, (void *)0x00000001,
    (void *)0xC5353D1F, (void *)0x00000000, (void *)0xC6373166, (void *)0x00000001,
    (void *)0xC4BB5DCB, (void *)0x00000000, (void *)0xC611B5C2, (void *)0x00000001,
    (void *)0xC4C88A04, (void *)0x00000000, (void *)0xC6115DA4, (void *)0x00000001,
    (void *)0xC530676D, (void *)0x00000000, (void *)0xC6383871, (void *)0x00000001,
    (void *)0xC532AAFA, (void *)0x00000000, (void *)0xC637BE52, (void *)0x00000001,
    (void *)0xC4C19FB6, (void *)0x00000000, (void *)0xC6119153, (void *)0x00000001,
    (void *)0xC4CFE958, (void *)0x00000000, (void *)0xC611279F, (void *)0x00000001,
    (void *)0xC455F583, (void *)0x00000000, (void *)0xC5B65EF8, (void *)0x00000001,
    (void *)0xC44B07F5, (void *)0x00000000, (void *)0xC5B700FE, (void *)0x00000001,
    (void *)0xC43F1ACC, (void *)0x00000000, (void *)0xC5B7BFA2, (void *)0x00000001,
    (void *)0xC43377D9, (void *)0x00000000, (void *)0xC5B85017, (void *)0x00000001,
    (void *)0xC4BF549C, (void *)0x00000000, (void *)0xC612320A, (void *)0x00000001,
    (void *)0xC4C5E45A, (void *)0x00000000, (void *)0xC6120C5B, (void *)0x00000001,
    (void *)0xC4CC993F, (void *)0x00000000, (void *)0xC611DF00, (void *)0x00000001,
    (void *)0xC4D37B64, (void *)0x00000000, (void *)0xC611BD28, (void *)0x00000001,
    (void *)0xC508F112, (void *)0x00000000, (void *)0xC693CED7, (void *)0x00000001,
    (void *)0xC5064B58, (void *)0x00000000, (void *)0xC6932E33, (void *)0x00000001,
    (void *)0xC50BC214, (void *)0x00000000, (void *)0xC694648F, (void *)0x00000001,
    (void *)0xC50798F2, (void *)0x00000000, (void *)0xC69384B8, (void *)0x00000001,
    (void *)0xC565A73B, (void *)0x00000000, (void *)0xC66D8DCD, (void *)0x00000001,
    (void *)0xC56C686F, (void *)0x00000000, (void *)0xC66DF033, (void *)0x00000001,
    (void *)0xC50C6021, (void *)0x00000000, (void *)0xC693D138, (void *)0x00000001,
    (void *)0xC50AC2A0, (void *)0x00000000, (void *)0xC6938294, (void *)0x00000001,
    (void *)0xC507BA8B, (void *)0x00000000, (void *)0xC692EBCD, (void *)0x00000001,
    (void *)0xC4839948, (void *)0x00000000, (void *)0xC410C329, (void *)0x00000001,
    (void *)0xC47BCD50, (void *)0x00000000, (void *)0xC4099FB5, (void *)0x00000001,
    (void *)0xC465FE11, (void *)0x00000000, (void *)0xC3F6A176, (void *)0x00000001,
    (void *)0xC568C26A, (void *)0x00000000, (void *)0xC66DB971, (void *)0x00000001,
    (void *)0xC56F9A4A, (void *)0x00000000, (void *)0xC66E0DC3, (void *)0x00000001,
    (void *)0xC50DE8E9, (void *)0x00000000, (void *)0xC6941785, (void *)0x00000001,
    (void *)0xC5095123, (void *)0x00000000, (void *)0xC6933CF6, (void *)0x00000001,
    (void *)0xC50A53B2, (void *)0x00000000, (void *)0xC6941BE1, (void *)0x00000001,
    (void *)0xC470AD13, (void *)0x00000000, (void *)0xC4031883, (void *)0x00000001,
    (void *)0xC45929A2, (void *)0x00000000, (void *)0xC3FF2357, (void *)0x00000001,
    (void *)0xC4640BE4, (void *)0x00000000, (void *)0xC407B336, (void *)0x00000001,
    (void *)0xC46FF5AC, (void *)0x00000000, (void *)0xC40F5FCD, (void *)0x00000001,
    (void *)0xC47B1C08, (void *)0x00000000, (void *)0xC4167034, (void *)0x00000001,
    (void *)0xC535D614, (void *)0x00000000, (void *)0xC637F49A, (void *)0x00000001,
    (void *)0xC5335046, (void *)0x00000000, (void *)0xC6387FD7, (void *)0x00000001,
    (void *)0xC530E771, (void *)0x00000000, (void *)0xC638FF7B, (void *)0x00000001,
    (void *)0xC52EB391, (void *)0x00000000, (void *)0xC6396EB8, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80403654[216] = {
    (void *)0x435E4EED, (void *)0x00000000, (void *)0xC611BCE8, (void *)0x00000001,
    (void *)0xC2991805, (void *)0x00000000, (void *)0xC5BB0EAA, (void *)0x00000001,
    (void *)0xC32B705C, (void *)0x00000000, (void *)0xC5BCB40E, (void *)0x00000001,
    (void *)0x438BFFF6, (void *)0x00000000, (void *)0xC611BD48, (void *)0x00000001,
    (void *)0xC21B3591, (void *)0x00000000, (void *)0xC5BA63E1, (void *)0x00000001,
    (void *)0xC2F4EDAC, (void *)0x00000000, (void *)0xC5BBE331, (void *)0x00000001,
    (void *)0xC408C0A9, (void *)0x00000000, (void *)0xC644943D, (void *)0x00000001,
    (void *)0xC414F618, (void *)0x00000000, (void *)0xC644473D, (void *)0x00000001,
    (void *)0xC42A3DD1, (void *)0x00000000, (void *)0xC6446DF6, (void *)0x00000001,
    (void *)0x43967783, (void *)0x00000000, (void *)0xC6112E61, (void *)0x00000001,
    (void *)0x4341B042, (void *)0x00000000, (void *)0xC611341F, (void *)0x00000001,
    (void *)0xC4363356, (void *)0x00000000, (void *)0xC64435D7, (void *)0x00000001,
    (void *)0xC420D348, (void *)0x00000000, (void *)0xC644075C, (void *)0x00000001,
    (void *)0xC42C5F36, (void *)0x00000000, (void *)0xC643C529, (void *)0x00000001,
    (void *)0x43792F14, (void *)0x00000000, (void *)0xC6112E73, (void *)0x00000001,
    (void *)0x430FCE63, (void *)0x00000000, (void *)0xC6113172, (void *)0x00000001,
    (void *)0xC35918A7, (void *)0x00000000, (void *)0xC5BBE531, (void *)0x00000001,
    (void *)0xC32B45C3, (void *)0x00000000, (void *)0xC5BB1BEE, (void *)0x00000001,
    (void *)0xC2F6CD36, (void *)0x00000000, (void *)0xC5BA58A2, (void *)0x00000001,
    (void *)0xC2A31864, (void *)0x00000000, (void *)0xC5B999E3, (void *)0x00000001,
    (void *)0x4321D9E2, (void *)0x00000000, (void *)0xC611BC38, (void *)0x00000001,
    (void *)0xC5331A56, (void *)0x00000000, (void *)0xC60ED1BE, (void *)0x00000001,
    (void *)0xC41E2115, (void *)0x00000000, (void *)0xC644B0EC, (void *)0x00000001,
    (void *)0xC4114C5D, (void *)0x00000000, (void *)0xC644FCD7, (void *)0x00000001,
    (void *)0xC5513568, (void *)0x00000000, (void *)0xC66925CD, (void *)0x00000001,
    (void *)0xC53319EC, (void *)0x00000000, (void *)0xC60D43CC, (void *)0x00000001,
    (void *)0xC5314C08, (void *)0x00000000, (void *)0xC60E141D, (void *)0x00000001,
    (void *)0xC54F0137, (void *)0x00000000, (void *)0xC6689114, (void *)0x00000001,
    (void *)0xC5535191, (void *)0x00000000, (void *)0xC669CC5C, (void *)0x00000001,
    (void *)0xC5350764, (void *)0x00000000, (void *)0xC60E20A3, (void *)0x00000001,
    (void *)0xC5369BBE, (void *)0x00000000, (void *)0xC60D8361, (void *)0x00000001,
    (void *)0xC54D1550, (void *)0x00000000, (void *)0xC667E485, (void *)0x00000001,
    (void *)0xC54BC550, (void *)0x00000000, (void *)0xC668B79A, (void *)0x00000001,
    (void *)0xC54F5025, (void *)0x00000000, (void *)0xC669F2E1, (void *)0x00000001,
    (void *)0xC5CDCB71, (void *)0x00000000, (void *)0xC63A25F6, (void *)0x00000001,
    (void *)0xC5CBF93F, (void *)0x00000000, (void *)0xC63A3C85, (void *)0x00000001,
    (void *)0xC5C8A808, (void *)0x00000000, (void *)0xC63A5F8F, (void *)0x00000001,
    (void *)0x42102420, (void *)0x00000000, (void *)0xC38E9ED9, (void *)0x00000001,
    (void *)0x4302655A, (void *)0x00000000, (void *)0xC3AA47C8, (void *)0x00000001,
    (void *)0x432F0759, (void *)0x00000000, (void *)0xC3BA1B12, (void *)0x00000001,
    (void *)0xC54A1FA6, (void *)0x00000000, (void *)0xC6681248, (void *)0x00000001,
    (void *)0xC54D68C9, (void *)0x00000000, (void *)0xC669505C, (void *)0x00000001,
    (void *)0xC5C97081, (void *)0x00000000, (void *)0xC63AE648, (void *)0x00000001,
    (void *)0xC5CA54DB, (void *)0x00000000, (void *)0xC63A46D7, (void *)0x00000001,
    (void *)0xC5388435, (void *)0x00000000, (void *)0xC60CE5E0, (void *)0x00000001,
    (void *)0x42A00767, (void *)0x00000000, (void *)0xC39CC80A, (void *)0x00000001,
    (void *)0xC52F1E8B, (void *)0x00000000, (void *)0xC60ED997, (void *)0x00000001,
    (void *)0x41B61F6B, (void *)0x00000000, (void *)0xC3A7BD81, (void *)0x00000001,
    (void *)0x42963207, (void *)0x00000000, (void *)0xC3B6AC85, (void *)0x00000001,
    (void *)0x42F42042, (void *)0x00000000, (void *)0xC3C3E351, (void *)0x00000001,
    (void *)0xC5CB1E58, (void *)0x00000000, (void *)0xC63ADD3D, (void *)0x00000001,
    (void *)0xC5CCF808, (void *)0x00000000, (void *)0xC63AD6AE, (void *)0x00000001,
    (void *)0xC534BDD3, (void *)0x00000000, (void *)0xC60CB891, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804039B4[124] = {
    (void *)0x44014B76, (void *)0x00000000, (void *)0xC5C52B1D, (void *)0x00000001,
    (void *)0x4408185F, (void *)0x00000000, (void *)0xC5C530C1, (void *)0x00000001,
    (void *)0x440FC672, (void *)0x00000000, (void *)0xC5C5302D, (void *)0x00000001,
    (void *)0x4416CE6B, (void *)0x00000000, (void *)0xC5C53BD3, (void *)0x00000001,
    (void *)0x441FAE77, (void *)0x00000000, (void *)0xC5C538EE, (void *)0x00000001,
    (void *)0x4427D2DB, (void *)0x00000000, (void *)0xC5C54402, (void *)0x00000001,
    (void *)0x458CDFC1, (void *)0x00000000, (void *)0xC5C83B2B, (void *)0x00000001,
    (void *)0x458DC99E, (void *)0x00000000, (void *)0xC5C8502D, (void *)0x00000001,
    (void *)0x458EDD27, (void *)0x00000000, (void *)0xC5C840EC, (void *)0x00000001,
    (void *)0x458FEE9A, (void *)0x00000000, (void *)0xC5C8549A, (void *)0x00000001,
    (void *)0x45911804, (void *)0x00000000, (void *)0xC5C85037, (void *)0x00000001,
    (void *)0x4592021B, (void *)0x00000000, (void *)0xC5C8470E, (void *)0x00000001,
    (void *)0x4404A55B, (void *)0x00000000, (void *)0xC5C804C9, (void *)0x00000001,
    (void *)0x440CED64, (void *)0x00000000, (void *)0xC5C80ADB, (void *)0x00000001,
    (void *)0x4414203B, (void *)0x00000000, (void *)0xC5C80E29, (void *)0x00000001,
    (void *)0x441BB39C, (void *)0x00000000, (void *)0xC5C802AE, (void *)0x00000001,
    (void *)0x4424A5D0, (void *)0x00000000, (void *)0xC5C7F66D, (void *)0x00000001,
    (void *)0x442DDA53, (void *)0x00000000, (void *)0xC5C7FF4A, (void *)0x00000001,
    (void *)0x44E99442, (void *)0x00000000, (void *)0xC46BBCAF, (void *)0x00000001,
    (void *)0x44EB437D, (void *)0x00000000, (void *)0xC46278C1, (void *)0x00000001,
    (void *)0x44ED00C5, (void *)0x00000000, (void *)0xC45888A9, (void *)0x00000001,
    (void *)0x44EE6148, (void *)0x00000000, (void *)0xC4505249, (void *)0x00000001,
    (void *)0x44EF77CF, (void *)0x00000000, (void *)0xC4487392, (void *)0x00000001,
    (void *)0x44F13452, (void *)0x00000000, (void *)0xC4413780, (void *)0x00000001,
    (void *)0x44E18408, (void *)0x00000000, (void *)0xC468128F, (void *)0x00000001,
    (void *)0x44E2EA66, (void *)0x00000000, (void *)0xC460D99A, (void *)0x00000001,
    (void *)0x44E4AD48, (void *)0x00000000, (void *)0xC4589B85, (void *)0x00000001,
    (void *)0x44E5B171, (void *)0x00000000, (void *)0xC450BF56, (void *)0x00000001,
    (void *)0x44E7727F, (void *)0x00000000, (void *)0xC447CAC9, (void *)0x00000001,
    (void *)0x44E914EE, (void *)0x00000000, (void *)0xC43F227D, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80403BA4[124] = {
    (void *)0x44014B76, (void *)0x00000000, (void *)0xC5C52B1D, (void *)0x00000001,
    (void *)0x4408185F, (void *)0x00000000, (void *)0xC5C530C1, (void *)0x00000001,
    (void *)0x440FC672, (void *)0x00000000, (void *)0xC5C5302D, (void *)0x00000001,
    (void *)0x4416CE6B, (void *)0x00000000, (void *)0xC5C53BD3, (void *)0x00000001,
    (void *)0x441FAE77, (void *)0x00000000, (void *)0xC5C538EE, (void *)0x00000001,
    (void *)0x4427D2DB, (void *)0x00000000, (void *)0xC5C54402, (void *)0x00000001,
    (void *)0x4518367F, (void *)0x00000000, (void *)0xC5B0A521, (void *)0x00000001,
    (void *)0x451A0A3D, (void *)0x00000000, (void *)0xC5B0BA23, (void *)0x00000001,
    (void *)0x451C3150, (void *)0x00000000, (void *)0xC5B0AAE1, (void *)0x00000001,
    (void *)0x451E5435, (void *)0x00000000, (void *)0xC5B0BE8D, (void *)0x00000001,
    (void *)0x4520A70A, (void *)0x00000000, (void *)0xC5B0BA2B, (void *)0x00000001,
    (void *)0x45227B37, (void *)0x00000000, (void *)0xC5B0B104, (void *)0x00000001,
    (void *)0x4404A55B, (void *)0x00000000, (void *)0xC5C804C9, (void *)0x00000001,
    (void *)0x440CED64, (void *)0x00000000, (void *)0xC5C80ADB, (void *)0x00000001,
    (void *)0x4414203B, (void *)0x00000000, (void *)0xC5C80E29, (void *)0x00000001,
    (void *)0x441BB39C, (void *)0x00000000, (void *)0xC5C802AE, (void *)0x00000001,
    (void *)0x4424A5D0, (void *)0x00000000, (void *)0xC5C7F66D, (void *)0x00000001,
    (void *)0x442DDA53, (void *)0x00000000, (void *)0xC5C7FF4A, (void *)0x00000001,
    (void *)0x453EF256, (void *)0x00000000, (void *)0xC4436309, (void *)0x00000001,
    (void *)0x453FC9F0, (void *)0x00000000, (void *)0xC43A1F1C, (void *)0x00000001,
    (void *)0x4540A893, (void *)0x00000000, (void *)0xC4302F04, (void *)0x00000001,
    (void *)0x454158D5, (void *)0x00000000, (void *)0xC427F8A2, (void *)0x00000001,
    (void *)0x4541E419, (void *)0x00000000, (void *)0xC42019ED, (void *)0x00000001,
    (void *)0x4542C25A, (void *)0x00000000, (void *)0xC418DDDB, (void *)0x00000001,
    (void *)0x453AEA35, (void *)0x00000000, (void *)0xC43FB8EA, (void *)0x00000001,
    (void *)0x453B9D64, (void *)0x00000000, (void *)0xC4387FF5, (void *)0x00000001,
    (void *)0x453C7ED5, (void *)0x00000000, (void *)0xC43041DE, (void *)0x00000001,
    (void *)0x453D00E9, (void *)0x00000000, (void *)0xC42865AF, (void *)0x00000001,
    (void *)0x453DE175, (void *)0x00000000, (void *)0xC41F7124, (void *)0x00000001,
    (void *)0x453EB2A8, (void *)0x00000000, (void *)0xC416C8D7, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80403D94[80] = {
    (void *)0xC281157E, (void *)0x00000000, (void *)0x44C629D3, (void *)0x00000001,
    (void *)0xC214E7FD, (void *)0x00000000, (void *)0x44C63DFC, (void *)0x00000001,
    (void *)0xC142B7F4, (void *)0x00000000, (void *)0x44C635E3, (void *)0x00000001,
    (void *)0x41667C1C, (void *)0x00000000, (void *)0x44C631DB, (void *)0x00000001,
    (void *)0x422FD220, (void *)0x00000000, (void *)0x44C5F9FC, (void *)0x00000001,
    (void *)0xC24F9FBC, (void *)0x00000000, (void *)0x44C0A298, (void *)0x00000001,
    (void *)0xC1C4B978, (void *)0x00000000, (void *)0x44C0B6C1, (void *)0x00000001,
    (void *)0x3EEEA50D, (void *)0x00000000, (void *)0x44C0AEA8, (void *)0x00000001,
    (void *)0x41D85490, (void *)0x00000000, (void *)0x44C0AAA0, (void *)0x00000001,
    (void *)0x42625D69, (void *)0x00000000, (void *)0x44C072C1, (void *)0x00000001,
    (void *)0x44C4E093, (void *)0x00000000, (void *)0xC4B81021, (void *)0x00000001,
    (void *)0x44C8452F, (void *)0x00000000, (void *)0xC4B85083, (void *)0x00000001,
    (void *)0x44CBDAF2, (void *)0x00000000, (void *)0xC4B88BD7, (void *)0x00000001,
    (void *)0x44CF97AE, (void *)0x00000000, (void *)0xC4B8CF64, (void *)0x00000001,
    (void *)0x44D34F44, (void *)0x00000000, (void *)0xC4B9265E, (void *)0x00000001,
    (void *)0x44C63AE1, (void *)0x00000000, (void *)0xC4B377D7, (void *)0x00000001,
    (void *)0x44CA52B8, (void *)0x00000000, (void *)0xC4B3ACFE, (void *)0x00000001,
    (void *)0x44CDEB02, (void *)0x00000000, (void *)0xC4B3E839, (void *)0x00000001,
    (void *)0x44D21FAE, (void *)0x00000000, (void *)0xC4B3F8E5, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80403ED4[116] = {
    (void *)0xC281157E, (void *)0x00000000, (void *)0x44C629D3, (void *)0x00000001,
    (void *)0xC214E7FD, (void *)0x00000000, (void *)0x44C63DFC, (void *)0x00000001,
    (void *)0xC142B7F4, (void *)0x00000000, (void *)0x44C635E3, (void *)0x00000001,
    (void *)0x41667C1C, (void *)0x00000000, (void *)0x44C631DB, (void *)0x00000001,
    (void *)0x422FD220, (void *)0x00000000, (void *)0x44C5F9FC, (void *)0x00000001,
    (void *)0xC24F9FBC, (void *)0x00000000, (void *)0x44C0A298, (void *)0x00000001,
    (void *)0xC1C4B978, (void *)0x00000000, (void *)0x44C0B6C1, (void *)0x00000001,
    (void *)0x3EEEA50D, (void *)0x00000000, (void *)0x44C0AEA8, (void *)0x00000001,
    (void *)0x41D85490, (void *)0x00000000, (void *)0x44C0AAA0, (void *)0x00000001,
    (void *)0x42625D69, (void *)0x00000000, (void *)0x44C072C1, (void *)0x00000001,
    (void *)0x45266FCB, (void *)0x00000000, (void *)0xC4F8D829, (void *)0x00000001,
    (void *)0x45285A31, (void *)0x00000000, (void *)0xC4F8B75C, (void *)0x00000001,
    (void *)0x452A502D, (void *)0x00000000, (void *)0xC4F87625, (void *)0x00000001,
    (void *)0x452C579E, (void *)0x00000000, (void *)0xC4F83D27, (void *)0x00000001,
    (void *)0x452DFA9C, (void *)0x00000000, (void *)0xC4F84CEE, (void *)0x00000001,
    (void *)0x4526FABC, (void *)0x00000000, (void *)0xC4F2B052, (void *)0x00000001,
    (void *)0x4529305E, (void *)0x00000000, (void *)0xC4F2D23D, (void *)0x00000001,
    (void *)0x452B5208, (void *)0x00000000, (void *)0xC4F2A991, (void *)0x00000001,
    (void *)0x452D6846, (void *)0x00000000, (void *)0xC4F271BA, (void *)0x00000001,
    (void *)0x4253B9D6, (void *)0x00000000, (void *)0xC54289FC, (void *)0x00000001,
    (void *)0x419C55EA, (void *)0x00000000, (void *)0xC5429077, (void *)0x00000001,
    (void *)0xC168FE1E, (void *)0x00000000, (void *)0xC5428F5C, (void *)0x00000001,
    (void *)0xC247A88A, (void *)0x00000000, (void *)0xC54293D7, (void *)0x00000001,
    (void *)0x42784F57, (void *)0x00000000, (void *)0xC545B7F0, (void *)0x00000001,
    (void *)0x420F8FF7, (void *)0x00000000, (void *)0xC545A550, (void *)0x00000001,
    (void *)0x405B4784, (void *)0x00000000, (void *)0xC545A1A6, (void *)0x00000001,
    (void *)0xC1DF9513, (void *)0x00000000, (void *)0xC545ACCD, (void *)0x00000001,
    (void *)0xC26A650A, (void *)0x00000000, (void *)0xC545A7C3, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804040A4[80] = {
    (void *)0xC2AC4BF5, (void *)0x00000000, (void *)0xC4A3CF2B, (void *)0x00000001,
    (void *)0xC25AB2D7, (void *)0x00000000, (void *)0xC4A3BB02, (void *)0x00000001,
    (void *)0xC1A2185F, (void *)0x00000000, (void *)0xC4A3C31B, (void *)0x00000001,
    (void *)0x4185ABEE, (void *)0x00000000, (void *)0xC4A3A5DB, (void *)0x00000001,
    (void *)0x424582A2, (void *)0x00000000, (void *)0xC4A3BC7B, (void *)0x00000001,
    (void *)0xC2868CC8, (void *)0x00000000, (void *)0xC4AB6AA8, (void *)0x00000001,
    (void *)0xC20B0BFE, (void *)0x00000000, (void *)0xC4AB567F, (void *)0x00000001,
    (void *)0xC01B65DC, (void *)0x00000000, (void *)0xC4AB7FD7, (void *)0x00000001,
    (void *)0x41F3137A, (void *)0x00000000, (void *)0xC4AB83DF, (void *)0x00000001,
    (void *)0x428457F9, (void *)0x00000000, (void *)0xC4AB7937, (void *)0x00000001,
    (void *)0x445F6FA4, (void *)0x00000000, (void *)0x4454FF0E, (void *)0x00000001,
    (void *)0x44562417, (void *)0x00000000, (void *)0x4454E51F, (void *)0x00000001,
    (void *)0x444CFBB1, (void *)0x00000000, (void *)0x44553A6D, (void *)0x00000001,
    (void *)0x44438363, (void *)0x00000000, (void *)0x4454D79E, (void *)0x00000001,
    (void *)0x44643FF5, (void *)0x00000000, (void *)0x44466201, (void *)0x00000001,
    (void *)0x445B2D05, (void *)0x00000000, (void *)0x4446AC80, (void *)0x00000001,
    (void *)0x44521CAF, (void *)0x00000000, (void *)0x4446BB28, (void *)0x00000001,
    (void *)0x4448B064, (void *)0x00000000, (void *)0x44468E89, (void *)0x00000001,
    (void *)0x443F7261, (void *)0x00000000, (void *)0x444651D1, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804041E4[108] = {
    (void *)0xC29C21FA, (void *)0x00000000, (void *)0x44940D2F, (void *)0x00000001,
    (void *)0xC21C664F, (void *)0x00000000, (void *)0x44940CBC, (void *)0x00000001,
    (void *)0xBFBE862F, (void *)0x00000000, (void *)0x4493EA25, (void *)0x00000001,
    (void *)0x41EF7F9C, (void *)0x00000000, (void *)0x44942323, (void *)0x00000001,
    (void *)0x42850A43, (void *)0x00000000, (void *)0x4493D0D5, (void *)0x00000001,
    (void *)0xC2701ACF, (void *)0x00000000, (void *)0x449A98D5, (void *)0x00000001,
    (void *)0xC1BD138A, (void *)0x00000000, (void *)0x449A55AA, (void *)0x00000001,
    (void *)0x416A0B39, (void *)0x00000000, (void *)0x449A1A87, (void *)0x00000001,
    (void *)0x4254DCF5, (void *)0x00000000, (void *)0x449A3117, (void *)0x00000001,
    (void *)0xC493C1D3, (void *)0x00000000, (void *)0xC41B0E1E, (void *)0x00000001,
    (void *)0xC495C07B, (void *)0x00000000, (void *)0xC41209BF, (void *)0x00000001,
    (void *)0xC4921819, (void *)0x00000000, (void *)0xC424091D, (void *)0x00000001,
    (void *)0xC4966E66, (void *)0x00000000, (void *)0xC42BE0FC, (void *)0x00000001,
    (void *)0xC4981EC1, (void *)0x00000000, (void *)0xC4244F2E, (void *)0x00000001,
    (void *)0xC499DFF8, (void *)0x00000000, (void *)0xC41AD880, (void *)0x00000001,
    (void *)0xC49BCC93, (void *)0x00000000, (void *)0xC4129768, (void *)0x00000001,
    (void *)0xC555DA7F, (void *)0x00000000, (void *)0xC52D5E35, (void *)0x00000001,
    (void *)0xC55A1EFA, (void *)0x00000000, (void *)0xC52D8A04, (void *)0x00000001,
    (void *)0xC55AF7F0, (void *)0x00000000, (void *)0xC52B465E, (void *)0x00000001,
    (void *)0xC55BEFB2, (void *)0x00000000, (void *)0xC528DCD1, (void *)0x00000001,
    (void *)0xC55D10DD, (void *)0x00000000, (void *)0xC52691FC, (void *)0x00000001,
    (void *)0xC556AD75, (void *)0x00000000, (void *)0xC52B4DF4, (void *)0x00000001,
    (void *)0xC557AA93, (void *)0x00000000, (void *)0xC528EDBA, (void *)0x00000001,
    (void *)0xC5589F8D, (void *)0x00000000, (void *)0xC526472F, (void *)0x00000001,
    (void *)0xC559B898, (void *)0x00000000, (void *)0xC523EE39, (void *)0x00000001,
    (void *)0xC55E050E, (void *)0x00000000, (void *)0xC5243214, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80404394[88] = {
    (void *)0x432B0FCC, (void *)0x00000000, (void *)0x44FC4EE1, (void *)0x00000001,
    (void *)0x432B83FE, (void *)0x00000000, (void *)0x4507E09C, (void *)0x00000001,
    (void *)0x432B542C, (void *)0x00000000, (void *)0x45016771, (void *)0x00000001,
    (void *)0x432AD76D, (void *)0x00000000, (void *)0x4504BE56, (void *)0x00000001,
    (void *)0x43715D0E, (void *)0x00000000, (void *)0x4503247F, (void *)0x00000001,
    (void *)0x4372E50B, (void *)0x00000000, (void *)0x44FFEDE3, (void *)0x00000001,
    (void *)0x4372EE01, (void *)0x00000000, (void *)0x450644F6, (void *)0x00000001,
    (void *)0x4355BD56, (void *)0x00000000, (void *)0x43ABAD12, (void *)0x00000001,
    (void *)0x43563189, (void *)0x00000000, (void *)0x43F97660, (void *)0x00000001,
    (void *)0x435601B7, (void *)0x00000000, (void *)0x43C5ACF7, (void *)0x00000001,
    (void *)0x435584FE, (void *)0x00000000, (void *)0x43E0641F, (void *)0x00000001,
    (void *)0x438E0556, (void *)0x00000000, (void *)0x43D39577, (void *)0x00000001,
    (void *)0x438EC955, (void *)0x00000000, (void *)0x43BA2900, (void *)0x00000001,
    (void *)0x438ECDD0, (void *)0x00000000, (void *)0x43EC991D, (void *)0x00000001,
    (void *)0x44901506, (void *)0x00000000, (void *)0xC4DA7BE7, (void *)0x00000001,
    (void *)0x4490238D, (void *)0x00000000, (void *)0xC4C7099A, (void *)0x00000001,
    (void *)0x44901D91, (void *)0x00000000, (void *)0xC4D3FBF0, (void *)0x00000001,
    (void *)0x44900DFC, (void *)0x00000000, (void *)0xC4CD4E25, (void *)0x00000001,
    (void *)0x4498DEB0, (void *)0x00000000, (void *)0xC4D081D3, (void *)0x00000001,
    (void *)0x44990FAE, (void *)0x00000000, (void *)0xC4D6DCEE, (void *)0x00000001,
    (void *)0x449910CD, (void *)0x00000000, (void *)0xC4CA40E5, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804044F4[88] = {
    (void *)0xC4866E04, (void *)0x00000000, (void *)0x44EAC3A6, (void *)0x00000001,
    (void *)0xC48F19EC, (void *)0x00000000, (void *)0x44FDEB7D, (void *)0x00000001,
    (void *)0xC48C8191, (void *)0x00000000, (void *)0x44ED7B5C, (void *)0x00000001,
    (void *)0xC492F7BE, (void *)0x00000000, (void *)0x44F0F5DB, (void *)0x00000001,
    (void *)0xC48375FC, (void *)0x00000000, (void *)0x44F393CF, (void *)0x00000001,
    (void *)0xC47D3A8F, (void *)0x00000000, (void *)0x44EEF796, (void *)0x00000001,
    (void *)0xC4891579, (void *)0x00000000, (void *)0x44F8AAD1, (void *)0x00000001,
    (void *)0x451844CD, (void *)0x00000000, (void *)0xC39D44BC, (void *)0x00000001,
    (void *)0x45180917, (void *)0x00000000, (void *)0xC2E251AA, (void *)0x00000001,
    (void *)0x451A2348, (void *)0x00000000, (void *)0xC322D831, (void *)0x00000001,
    (void *)0x45180400, (void *)0x00000000, (void *)0xC35305A8, (void *)0x00000001,
    (void *)0x451A4E19, (void *)0x00000000, (void *)0xC3842E11, (void *)0x00000001,
    (void *)0x451A3B7D, (void *)0x00000000, (void *)0xC3B5DA82, (void *)0x00000001,
    (void *)0x451A3C08, (void *)0x00000000, (void *)0xC289AAAA, (void *)0x00000001,
    (void *)0x4435B8CA, (void *)0x00000000, (void *)0xC5459473, (void *)0x00000001,
    (void *)0x446A9D25, (void *)0x00000000, (void *)0xC5458856, (void *)0x00000001,
    (void *)0x4446E0F9, (void *)0x00000000, (void *)0xC54598D9, (void *)0x00000001,
    (void *)0x44595AED, (void *)0x00000000, (void *)0xC5458662, (void *)0x00000001,
    (void *)0x4451DA65, (void *)0x00000000, (void *)0xC540570A, (void *)0x00000001,
    (void *)0x443DA08B, (void *)0x00000000, (void *)0xC5404035, (void *)0x00000001,
    (void *)0x446355B5, (void *)0x00000000, (void *)0xC5403AAC, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80404654[208] = {
    (void *)0xC59472C1, (void *)0x00000000, (void *)0xC40568E7, (void *)0x00000001,
    (void *)0xC594729E, (void *)0x00000000, (void *)0xC3F52073, (void *)0x00000001,
    (void *)0xC594581B, (void *)0x00000000, (void *)0xC3DBB3CD, (void *)0x00000001,
    (void *)0xC59474C7, (void *)0x00000000, (void *)0xC3B91D7A, (void *)0x00000001,
    (void *)0xC5945A23, (void *)0x00000000, (void *)0xC39F913E, (void *)0x00000001,
    (void *)0xC5944F7D, (void *)0x00000000, (void *)0xC3892659, (void *)0x00000001,
    (void *)0xC596D61B, (void *)0x00000000, (void *)0xC395525B, (void *)0x00000001,
    (void *)0xC574E9CF, (void *)0x00000000, (void *)0x458997A2, (void *)0x00000001,
    (void *)0xC5725B06, (void *)0x00000000, (void *)0x45898F39, (void *)0x00000001,
    (void *)0xC56FB6AC, (void *)0x00000000, (void *)0x4589977F, (void *)0x00000001,
    (void *)0xC569AC77, (void *)0x00000000, (void *)0x458AEEC3, (void *)0x00000001,
    (void *)0xC56E449C, (void *)0x00000000, (void *)0x458AF983, (void *)0x00000001,
    (void *)0xC5778CB0, (void *)0x00000000, (void *)0x458999F4, (void *)0x00000001,
    (void *)0xC56BF3AE, (void *)0x00000000, (void *)0x458AF237, (void *)0x00000001,
    (void *)0xC578CA25, (void *)0x00000000, (void *)0x458AE164, (void *)0x00000001,
    (void *)0xC5761A4E, (void *)0x00000000, (void *)0x458AE164, (void *)0x00000001,
    (void *)0xC5738252, (void *)0x00000000, (void *)0x458AE7F4, (void *)0x00000001,
    (void *)0xC570D0C9, (void *)0x00000000, (void *)0x458AF40C, (void *)0x00000001,
    (void *)0xC596E152, (void *)0x00000000, (void *)0xC3AF413E, (void *)0x00000001,
    (void *)0xC596E152, (void *)0x00000000, (void *)0xC3C87CB6, (void *)0x00000001,
    (void *)0xC596E152, (void *)0x00000000, (void *)0xC3E5ECBC, (void *)0x00000001,
    (void *)0xC596E152, (void *)0x00000000, (void *)0xC3FFDB9F, (void *)0x00000001,
    (void *)0xC56D30D5, (void *)0x00000000, (void *)0x4589977F, (void *)0x00000001,
    (void *)0xC56AAB02, (void *)0x00000000, (void *)0x45898E44, (void *)0x00000001,
    (void *)0xC555BB9E, (void *)0x00000000, (void *)0x45AA76EE, (void *)0x00000001,
    (void *)0xC555A846, (void *)0x00000000, (void *)0x45A91E0E, (void *)0x00000001,
    (void *)0xC55598D9, (void *)0x00000000, (void *)0x45A7C789, (void *)0x00000001,
    (void *)0xC555AB79, (void *)0x00000000, (void *)0x45A65F56, (void *)0x00000001,
    (void *)0xC555AE19, (void *)0x00000000, (void *)0x45A4DBFE, (void *)0x00000001,
    (void *)0xC555C323, (void *)0x00000000, (void *)0x45A3A47F, (void *)0x00000001,
    (void *)0x459E208F, (void *)0x00000000, (void *)0x44DA45BA, (void *)0x00000001,
    (void *)0x459B455C, (void *)0x00000000, (void *)0x44E21927, (void *)0x00000001,
    (void *)0x45993D6F, (void *)0x00000000, (void *)0x44E23083, (void *)0x00000001,
    (void *)0x459FC91F, (void *)0x00000000, (void *)0x44DA3764, (void *)0x00000001,
    (void *)0x459C4710, (void *)0x00000000, (void *)0x44DA27AE, (void *)0x00000001,
    (void *)0x459A60D1, (void *)0x00000000, (void *)0x44DA2462, (void *)0x00000001,
    (void *)0x45987133, (void *)0x00000000, (void *)0x44DA30DD, (void *)0x00000001,
    (void *)0x455AB8A0, (void *)0x00000000, (void *)0xC5244179, (void *)0x00000001,
    (void *)0x45597856, (void *)0x00000000, (void *)0xC51F6750, (void *)0x00000001,
    (void *)0x45556883, (void *)0x00000000, (void *)0xC51FB621, (void *)0x00000001,
    (void *)0x45515B54, (void *)0x00000000, (void *)0xC5200F96, (void *)0x00000001,
    (void *)0x4557420C, (void *)0x00000000, (void *)0xC525061D, (void *)0x00000001,
    (void *)0x45535781, (void *)0x00000000, (void *)0xC5261791, (void *)0x00000001,
    (void *)0x454FF087, (void *)0x00000000, (void *)0xC526C64A, (void *)0x00000001,
    (void *)0xC55245E7, (void *)0x00000000, (void *)0x45A43198, (void *)0x00000001,
    (void *)0xC5526AD1, (void *)0x00000000, (void *)0x45A5C78B, (void *)0x00000001,
    (void *)0xC5527D44, (void *)0x00000000, (void *)0x45A74B0A, (void *)0x00000001,
    (void *)0xC5527D44, (void *)0x00000000, (void *)0x45A8D7C7, (void *)0x00000001,
    (void *)0xC5528FBA, (void *)0x00000000, (void *)0x45AA1AAE, (void *)0x00000001,
    (void *)0x459D3548, (void *)0x00000000, (void *)0x44E21927, (void *)0x00000001,
    (void *)0x459F3437, (void *)0x00000000, (void *)0x44E25548, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80404994[200] = {
    (void *)0x4598C673, (void *)0x00000000, (void *)0x44E7685A, (void *)0x00000001,
    (void *)0x459A65E3, (void *)0x00000000, (void *)0x44E74DF4, (void *)0x00000001,
    (void *)0x459C1A02, (void *)0x00000000, (void *)0x44E78D68, (void *)0x00000001,
    (void *)0x459DBB81, (void *)0x00000000, (void *)0x44E77F0A, (void *)0x00000001,
    (void *)0x459F7162, (void *)0x00000000, (void *)0x44E74ED1, (void *)0x00000001,
    (void *)0x459993CB, (void *)0x00000000, (void *)0x44F099A2, (void *)0x00000001,
    (void *)0x4555A50A, (void *)0x00000000, (void *)0xC513CDA2, (void *)0x00000001,
    (void *)0x45586610, (void *)0x00000000, (void *)0xC513ED96, (void *)0x00000001,
    (void *)0x455B3656, (void *)0x00000000, (void *)0xC513E0EE, (void *)0x00000001,
    (void *)0xC59505D1, (void *)0x00000000, (void *)0x457DE95C, (void *)0x00000001,
    (void *)0xC5947AAC, (void *)0x00000000, (void *)0x4578288F, (void *)0x00000001,
    (void *)0xC593AE66, (void *)0x00000000, (void *)0x457AB581, (void *)0x00000001,
    (void *)0xC592EE35, (void *)0x00000000, (void *)0x457D1D3F, (void *)0x00000001,
    (void *)0xC59232B8, (void *)0x00000000, (void *)0x457F6ED5, (void *)0x00000001,
    (void *)0xC59179F6, (void *)0x00000000, (void *)0x4580ECDF, (void *)0x00000001,
    (void *)0xC5929E3D, (void *)0x00000000, (void *)0x4582CC68, (void *)0x00000001,
    (void *)0x45529A10, (void *)0x00000000, (void *)0xC513E733, (void *)0x00000001,
    (void *)0xC5935E9A, (void *)0x00000000, (void *)0x4581C208, (void *)0x00000001,
    (void *)0xC5944B64, (void *)0x00000000, (void *)0x45805EE3, (void *)0x00000001,
    (void *)0xC595D4FE, (void *)0x00000000, (void *)0x457B2306, (void *)0x00000001,
    (void *)0xC596D08B, (void *)0x00000000, (void *)0x457897DF, (void *)0x00000001,
    (void *)0x459B5912, (void *)0x00000000, (void *)0x44F04E14, (void *)0x00000001,
    (void *)0x459D0B79, (void *)0x00000000, (void *)0x44F04E14, (void *)0x00000001,
    (void *)0x459EBDE1, (void *)0x00000000, (void *)0x44F04E14, (void *)0x00000001,
    (void *)0xC5970E27, (void *)0x00000000, (void *)0x43EBC66A, (void *)0x00000001,
    (void *)0xC59542BE, (void *)0x00000000, (void *)0x43DF8364, (void *)0x00000001,
    (void *)0xC59534EC, (void *)0x00000000, (void *)0x43C2F1E2, (void *)0x00000001,
    (void *)0x4559B635, (void *)0x00000000, (void *)0xC516E019, (void *)0x00000001,
    (void *)0x4556F2AC, (void *)0x00000000, (void *)0xC516D1EC, (void *)0x00000001,
    (void *)0x454FD2FA, (void *)0x00000000, (void *)0xC513F933, (void *)0x00000001,
    (void *)0xC5952B06, (void *)0x00000000, (void *)0x43AB8B8C, (void *)0x00000001,
    (void *)0xC59538A8, (void *)0x00000000, (void *)0x43943635, (void *)0x00000001,
    (void *)0xC5953554, (void *)0x00000000, (void *)0x437A0CFB, (void *)0x00000001,
    (void *)0xC595BAEE, (void *)0x00000000, (void *)0x44C4787B, (void *)0x00000001,
    (void *)0xC5963C81, (void *)0x00000000, (void *)0x44CAF3CF, (void *)0x00000001,
    (void *)0xC596CAE3, (void *)0x00000000, (void *)0x44D10BF0, (void *)0x00000001,
    (void *)0xC5974CAE, (void *)0x00000000, (void *)0x44D6F591, (void *)0x00000001,
    (void *)0xC597E3C9, (void *)0x00000000, (void *)0x44DDB287, (void *)0x00000001,
    (void *)0xC5992DBC, (void *)0x00000000, (void *)0x44D84A2D, (void *)0x00000001,
    (void *)0xC599CD5E, (void *)0x00000000, (void *)0x44DF075C, (void *)0x00000001,
    (void *)0x45540D3B, (void *)0x00000000, (void *)0xC516B85A, (void *)0x00000001,
    (void *)0xC597A16F, (void *)0x00000000, (void *)0x44C51D48, (void *)0x00000001,
    (void *)0x455127CB, (void *)0x00000000, (void *)0xC516B85A, (void *)0x00000001,
    (void *)0xC5970010, (void *)0x00000000, (void *)0x43883C7B, (void *)0x00000001,
    (void *)0xC5970E29, (void *)0x00000000, (void *)0x43A00515, (void *)0x00000001,
    (void *)0xC5970E29, (void *)0x00000000, (void *)0x43B8AF32, (void *)0x00000001,
    (void *)0xC5970010, (void *)0x00000000, (void *)0x43D31C50, (void *)0x00000001,
    (void *)0xC598ADE9, (void *)0x00000000, (void *)0x44D1B2B8, (void *)0x00000001,
    (void *)0xC5982E10, (void *)0x00000000, (void *)0x44CB1B4C, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80404CB4[64] = {
    (void *)0x43787653, (void *)0x00000000, (void *)0xC5582CFA, (void *)0x00000001,
    (void *)0x43856890, (void *)0x00000000, (void *)0xC55A8DF8, (void *)0x00000001,
    (void *)0x438FC40B, (void *)0x00000000, (void *)0xC55CF0A4, (void *)0x00000001,
    (void *)0x439B9F80, (void *)0x00000000, (void *)0xC55F6117, (void *)0x00000001,
    (void *)0x434C67CF, (void *)0x00000000, (void *)0xC55AB0A0, (void *)0x00000001,
    (void *)0x4360954D, (void *)0x00000000, (void *)0xC55D308F, (void *)0x00000001,
    (void *)0x43783113, (void *)0x00000000, (void *)0xC560250A, (void *)0x00000001,
    (void *)0xC32EEEBF, (void *)0x00000000, (void *)0x4492E47B, (void *)0x00000001,
    (void *)0xC2F801BE, (void *)0x00000000, (void *)0x44942BF8, (void *)0x00000001,
    (void *)0xC290B556, (void *)0x00000000, (void *)0x44955A5E, (void *)0x00000001,
    (void *)0xC31FC53F, (void *)0x00000000, (void *)0x449D4F2B, (void *)0x00000001,
    (void *)0xC2E4F340, (void *)0x00000000, (void *)0x449DF2C9, (void *)0x00000001,
    (void *)0xC26A2111, (void *)0x00000000, (void *)0x449F0CCD, (void *)0x00000001,
    (void *)0xC1B2101E, (void *)0x00000000, (void *)0x44970073, (void *)0x00000001,
    (void *)0xC352BDD3, (void *)0x00000000, (void *)0x449C8A7F, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80404DB4[96] = {
    (void *)0x43787653, (void *)0x00000000, (void *)0xC5582CFA, (void *)0x00000001,
    (void *)0x43856890, (void *)0x00000000, (void *)0xC55A8DF8, (void *)0x00000001,
    (void *)0x438FC40B, (void *)0x00000000, (void *)0xC55CF0A4, (void *)0x00000001,
    (void *)0x439B9F80, (void *)0x00000000, (void *)0xC55F6117, (void *)0x00000001,
    (void *)0x434C67CF, (void *)0x00000000, (void *)0xC55AB0A0, (void *)0x00000001,
    (void *)0x4360954D, (void *)0x00000000, (void *)0xC55D308F, (void *)0x00000001,
    (void *)0x43783113, (void *)0x00000000, (void *)0xC560250A, (void *)0x00000001,
    (void *)0x44D705B2, (void *)0x00000000, (void *)0xC40D050B, (void *)0x00000001,
    (void *)0x44DD9354, (void *)0x00000000, (void *)0xC40538CA, (void *)0x00000001,
    (void *)0x44E34883, (void *)0x00000000, (void *)0xC3FB3D56, (void *)0x00000001,
    (void *)0x44DA9A04, (void *)0x00000000, (void *)0xC3DB6A16, (void *)0x00000001,
    (void *)0x44E0138D, (void *)0x00000000, (void *)0xC3CDA17C, (void *)0x00000001,
    (void *)0x44CE8F64, (void *)0x00000000, (void *)0xC4011030, (void *)0x00000001,
    (void *)0x44E8FBDF, (void *)0x00000000, (void *)0xC3ED28EC, (void *)0x00000001,
    (void *)0x44D45D50, (void *)0x00000000, (void *)0xC3EDE168, (void *)0x00000001,
    (void *)0xC32EEEBF, (void *)0x00000000, (void *)0x4492E47B, (void *)0x00000001,
    (void *)0xC2F801BE, (void *)0x00000000, (void *)0x44942BF8, (void *)0x00000001,
    (void *)0xC290B556, (void *)0x00000000, (void *)0x44955A5E, (void *)0x00000001,
    (void *)0xC31FC53F, (void *)0x00000000, (void *)0x449D4F2B, (void *)0x00000001,
    (void *)0xC2E4F340, (void *)0x00000000, (void *)0x449DF2C9, (void *)0x00000001,
    (void *)0xC26A2111, (void *)0x00000000, (void *)0x449F0CCD, (void *)0x00000001,
    (void *)0xC1B2101E, (void *)0x00000000, (void *)0x44970073, (void *)0x00000001,
    (void *)0xC352BDD3, (void *)0x00000000, (void *)0x449C8A7F, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80404F34[96] = {
    (void *)0xC3C920D5, (void *)0x00000000, (void *)0xC561E906, (void *)0x00000001,
    (void *)0xC46D2912, (void *)0x00000000, (void *)0xC1A0A979, (void *)0x00000001,
    (void *)0xC5290560, (void *)0x00000000, (void *)0xC469630C, (void *)0x00000001,
    (void *)0xC50CCF54, (void *)0x00000000, (void *)0xC5D181F2, (void *)0x00000001,
    (void *)0xC51066FA, (void *)0x00000000, (void *)0xC5D777CF, (void *)0x00000001,
    (void *)0xC3B63EFA, (void *)0x00000000, (void *)0xC560CBC3, (void *)0x00000001,
    (void *)0xC3A42622, (void *)0x00000000, (void *)0xC5603EB0, (void *)0x00000001,
    (void *)0xC46BD8B4, (void *)0x00000000, (void *)0x42390D5D, (void *)0x00000001,
    (void *)0xC525B148, (void *)0x00000000, (void *)0xC452A5DE, (void *)0x00000001,
    (void *)0xC5111175, (void *)0x00000000, (void *)0xC5D49FAE, (void *)0x00000001,
    (void *)0xC393B2E5, (void *)0x00000000, (void *)0xC55F75E7, (void *)0x00000001,
    (void *)0xC46C1C66, (void *)0x00000000, (void *)0x429DE7BC, (void *)0x00000001,
    (void *)0xC52456C5, (void *)0x00000000, (void *)0xC448ECF6, (void *)0x00000001,
    (void *)0xC50CEA39, (void *)0x00000000, (void *)0xC5D4E142, (void *)0x00000001,
    (void *)0xC380EA4E, (void *)0x00000000, (void *)0xC55E5A8F, (void *)0x00000001,
    (void *)0xC46C6EEE, (void *)0x00000000, (void *)0x42E0C40B, (void *)0x00000001,
    (void *)0xC522E48F, (void *)0x00000000, (void *)0xC43DABF3, (void *)0x00000001,
    (void *)0xC50A95E7, (void *)0x00000000, (void *)0xC5D36F2B, (void *)0x00000001,
    (void *)0xC50EDAB4, (void *)0x00000000, (void *)0xC5D2FD6D, (void *)0x00000001,
    (void *)0xC46C5DCE, (void *)0x00000000, (void *)0x417A1C39, (void *)0x00000001,
    (void *)0xC52784DD, (void *)0x00000000, (void *)0xC45E4F85, (void *)0x00000001,
    (void *)0xC512CEFE, (void *)0x00000000, (void *)0xC5D60156, (void *)0x00000001,
    (void *)0xC50ED8E5, (void *)0x00000000, (void *)0xC5D606BA, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804050B4[116] = {
    (void *)0xC52DD0D1, (void *)0x00000000, (void *)0xC523DFBA, (void *)0x00000001,
    (void *)0x461AE732, (void *)0x00000000, (void *)0xC5D7DB21, (void *)0x00000001,
    (void *)0x45FB95D3, (void *)0x00000000, (void *)0xC4882A7F, (void *)0x00000001,
    (void *)0x46020DB0, (void *)0x00000000, (void *)0xC592F8EC, (void *)0x00000001,
    (void *)0x45FB939C, (void *)0x00000000, (void *)0xC48F0F3B, (void *)0x00000001,
    (void *)0xC52F444A, (void *)0x00000000, (void *)0xC521890A, (void *)0x00000001,
    (void *)0x460148B8, (void *)0x00000000, (void *)0xC5931EB6, (void *)0x00000001,
    (void *)0x45FBA33D, (void *)0x00000000, (void *)0xC4821821, (void *)0x00000001,
    (void *)0x45FB9AB6, (void *)0x00000000, (void *)0xC495467F, (void *)0x00000001,
    (void *)0x461A2FE1, (void *)0x00000000, (void *)0xC5D7E11F, (void *)0x00000001,
    (void *)0xC52C8B54, (void *)0x00000000, (void *)0xC526581D, (void *)0x00000001,
    (void *)0xC52AF873, (void *)0x00000000, (void *)0xC5291D1B, (void *)0x00000001,
    (void *)0xC5296083, (void *)0x00000000, (void *)0xC52B6EE5, (void *)0x00000001,
    (void *)0x46197243, (void *)0x00000000, (void *)0xC5D7F15A, (void *)0x00000001,
    (void *)0x4618BEDC, (void *)0x00000000, (void *)0xC5D7F34C, (void *)0x00000001,
    (void *)0x46182658, (void *)0x00000000, (void *)0xC5D7DB25, (void *)0x00000001,
    (void *)0xC557CF91, (void *)0x00000000, (void *)0xC28F366A, (void *)0x00000001,
    (void *)0xC557AB12, (void *)0x00000000, (void *)0xC169762B, (void *)0x00000001,
    (void *)0xC557AB12, (void *)0x00000000, (void *)0x42574E6B, (void *)0x00000001,
    (void *)0xC557AB12, (void *)0x00000000, (void *)0x42EFED84, (void *)0x00000001,
    (void *)0xC553F65A, (void *)0x00000000, (void *)0xC230F4EC, (void *)0x00000001,
    (void *)0xC553F65A, (void *)0x00000000, (void *)0x419CF0C3, (void *)0x00000001,
    (void *)0xC553F65A, (void *)0x00000000, (void *)0x42AB8280, (void *)0x00000001,
    (void *)0x45FBA33D, (void *)0x00000000, (void *)0xC477055B, (void *)0x00000001,
    (void *)0x4602D54B, (void *)0x00000000, (void *)0xC592B664, (void *)0x00000001,
    (void *)0x4603A7FD, (void *)0x00000000, (void *)0xC5928A0A, (void *)0x00000001,
    (void *)0x460490DB, (void *)0x00000000, (void *)0xC5923156, (void *)0x00000001,
    (void *)0x461B8FC4, (void *)0x00000000, (void *)0xC5D7DB21, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80405284[204] = {
    (void *)0xC5669C98, (void *)0x00000000, (void *)0xC66E4AB8, (void *)0x00000001,
    (void *)0xC56D4779, (void *)0x00000000, (void *)0xC66E9F7B, (void *)0x00000001,
    (void *)0xC43E481A, (void *)0x00000000, (void *)0xC5B93421, (void *)0x00000001,
    (void *)0xC4555ECC, (void *)0x00000000, (void *)0xC5B7EE6A, (void *)0x00000001,
    (void *)0xC56393EC, (void *)0x00000000, (void *)0xC66E2129, (void *)0x00000001,
    (void *)0xC569E3DF, (void *)0x00000000, (void *)0xC66E7652, (void *)0x00000001,
    (void *)0xC4334E8C, (void *)0x00000000, (void *)0xC5B9D0DF, (void *)0x00000001,
    (void *)0xC449E87E, (void *)0x00000000, (void *)0xC5B889A8, (void *)0x00000001,
    (void *)0xC52E46EE, (void *)0x00000000, (void *)0xC638A971, (void *)0x00000001,
    (void *)0xC5353D1F, (void *)0x00000000, (void *)0xC6373166, (void *)0x00000001,
    (void *)0xC4BB5DCB, (void *)0x00000000, (void *)0xC611B5C2, (void *)0x00000001,
    (void *)0xC4C88A04, (void *)0x00000000, (void *)0xC6115DA4, (void *)0x00000001,
    (void *)0xC530676D, (void *)0x00000000, (void *)0xC6383871, (void *)0x00000001,
    (void *)0xC532AAFA, (void *)0x00000000, (void *)0xC637BE52, (void *)0x00000001,
    (void *)0xC4C19FB6, (void *)0x00000000, (void *)0xC6119153, (void *)0x00000001,
    (void *)0xC4CFE958, (void *)0x00000000, (void *)0xC611279F, (void *)0x00000001,
    (void *)0xC455F583, (void *)0x00000000, (void *)0xC5B65EF8, (void *)0x00000001,
    (void *)0xC44B07F5, (void *)0x00000000, (void *)0xC5B700FE, (void *)0x00000001,
    (void *)0xC43F1ACC, (void *)0x00000000, (void *)0xC5B7BFA2, (void *)0x00000001,
    (void *)0xC43377D9, (void *)0x00000000, (void *)0xC5B85017, (void *)0x00000001,
    (void *)0xC4BF549C, (void *)0x00000000, (void *)0xC612320A, (void *)0x00000001,
    (void *)0xC4C5E45A, (void *)0x00000000, (void *)0xC6120C5B, (void *)0x00000001,
    (void *)0xC4CC993F, (void *)0x00000000, (void *)0xC611DF00, (void *)0x00000001,
    (void *)0xC4D37B64, (void *)0x00000000, (void *)0xC611BD28, (void *)0x00000001,
    (void *)0xC508F112, (void *)0x00000000, (void *)0xC693CED7, (void *)0x00000001,
    (void *)0xC5064B58, (void *)0x00000000, (void *)0xC6932E33, (void *)0x00000001,
    (void *)0xC50BC214, (void *)0x00000000, (void *)0xC694648F, (void *)0x00000001,
    (void *)0xC50798F2, (void *)0x00000000, (void *)0xC69384B8, (void *)0x00000001,
    (void *)0xC565A73B, (void *)0x00000000, (void *)0xC66D8DCD, (void *)0x00000001,
    (void *)0xC56C686F, (void *)0x00000000, (void *)0xC66DF033, (void *)0x00000001,
    (void *)0xC50C6021, (void *)0x00000000, (void *)0xC693D138, (void *)0x00000001,
    (void *)0xC50AC2A0, (void *)0x00000000, (void *)0xC6938294, (void *)0x00000001,
    (void *)0xC507BA8B, (void *)0x00000000, (void *)0xC692EBCD, (void *)0x00000001,
    (void *)0xC4839948, (void *)0x00000000, (void *)0xC410C329, (void *)0x00000001,
    (void *)0xC47BCD50, (void *)0x00000000, (void *)0xC4099FB5, (void *)0x00000001,
    (void *)0xC465FE11, (void *)0x00000000, (void *)0xC3F6A176, (void *)0x00000001,
    (void *)0xC568C26A, (void *)0x00000000, (void *)0xC66DB971, (void *)0x00000001,
    (void *)0xC56F9A4A, (void *)0x00000000, (void *)0xC66E0DC3, (void *)0x00000001,
    (void *)0xC50DE8E9, (void *)0x00000000, (void *)0xC6941785, (void *)0x00000001,
    (void *)0xC5095123, (void *)0x00000000, (void *)0xC6933CF6, (void *)0x00000001,
    (void *)0xC50A53B2, (void *)0x00000000, (void *)0xC6941BE1, (void *)0x00000001,
    (void *)0xC470AD13, (void *)0x00000000, (void *)0xC4031883, (void *)0x00000001,
    (void *)0xC45929A2, (void *)0x00000000, (void *)0xC3FF2357, (void *)0x00000001,
    (void *)0xC4640BE4, (void *)0x00000000, (void *)0xC407B336, (void *)0x00000001,
    (void *)0xC46FF5AC, (void *)0x00000000, (void *)0xC40F5FCD, (void *)0x00000001,
    (void *)0xC47B1C08, (void *)0x00000000, (void *)0xC4167034, (void *)0x00000001,
    (void *)0xC535D614, (void *)0x00000000, (void *)0xC637F49A, (void *)0x00000001,
    (void *)0xC5335046, (void *)0x00000000, (void *)0xC6387FD7, (void *)0x00000001,
    (void *)0xC530E771, (void *)0x00000000, (void *)0xC638FF7B, (void *)0x00000001,
    (void *)0xC52EB391, (void *)0x00000000, (void *)0xC6396EB8, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804055B4[216] = {
    (void *)0x435E4EED, (void *)0x00000000, (void *)0xC611BCE8, (void *)0x00000001,
    (void *)0xC2991805, (void *)0x00000000, (void *)0xC5BB0EAA, (void *)0x00000001,
    (void *)0xC32B705C, (void *)0x00000000, (void *)0xC5BCB40E, (void *)0x00000001,
    (void *)0x438BFFF6, (void *)0x00000000, (void *)0xC611BD48, (void *)0x00000001,
    (void *)0xC21B3591, (void *)0x00000000, (void *)0xC5BA63E1, (void *)0x00000001,
    (void *)0xC2F4EDAC, (void *)0x00000000, (void *)0xC5BBE331, (void *)0x00000001,
    (void *)0xC408C0A9, (void *)0x00000000, (void *)0xC644943D, (void *)0x00000001,
    (void *)0xC414F618, (void *)0x00000000, (void *)0xC644473D, (void *)0x00000001,
    (void *)0xC42A3DD1, (void *)0x00000000, (void *)0xC6446DF6, (void *)0x00000001,
    (void *)0x43967783, (void *)0x00000000, (void *)0xC6112E61, (void *)0x00000001,
    (void *)0x4341B042, (void *)0x00000000, (void *)0xC611341F, (void *)0x00000001,
    (void *)0xC4363356, (void *)0x00000000, (void *)0xC64435D7, (void *)0x00000001,
    (void *)0xC420D348, (void *)0x00000000, (void *)0xC644075C, (void *)0x00000001,
    (void *)0xC42C5F36, (void *)0x00000000, (void *)0xC643C529, (void *)0x00000001,
    (void *)0x43792F14, (void *)0x00000000, (void *)0xC6112E73, (void *)0x00000001,
    (void *)0x430FCE63, (void *)0x00000000, (void *)0xC6113172, (void *)0x00000001,
    (void *)0xC35918A7, (void *)0x00000000, (void *)0xC5BBE531, (void *)0x00000001,
    (void *)0xC32B45C3, (void *)0x00000000, (void *)0xC5BB1BEE, (void *)0x00000001,
    (void *)0xC2F6CD36, (void *)0x00000000, (void *)0xC5BA58A2, (void *)0x00000001,
    (void *)0xC2A31864, (void *)0x00000000, (void *)0xC5B999E3, (void *)0x00000001,
    (void *)0x4321D9E2, (void *)0x00000000, (void *)0xC611BC38, (void *)0x00000001,
    (void *)0xC5331A56, (void *)0x00000000, (void *)0xC60ED1BE, (void *)0x00000001,
    (void *)0xC41E2115, (void *)0x00000000, (void *)0xC644B0EC, (void *)0x00000001,
    (void *)0xC4114C5D, (void *)0x00000000, (void *)0xC644FCD7, (void *)0x00000001,
    (void *)0xC5513568, (void *)0x00000000, (void *)0xC66925CD, (void *)0x00000001,
    (void *)0xC53319EC, (void *)0x00000000, (void *)0xC60D43CC, (void *)0x00000001,
    (void *)0xC5314C08, (void *)0x00000000, (void *)0xC60E141D, (void *)0x00000001,
    (void *)0xC54F0137, (void *)0x00000000, (void *)0xC6689114, (void *)0x00000001,
    (void *)0xC5535191, (void *)0x00000000, (void *)0xC669CC5C, (void *)0x00000001,
    (void *)0xC5350764, (void *)0x00000000, (void *)0xC60E20A3, (void *)0x00000001,
    (void *)0xC5369BBE, (void *)0x00000000, (void *)0xC60D8361, (void *)0x00000001,
    (void *)0xC54D1550, (void *)0x00000000, (void *)0xC667E485, (void *)0x00000001,
    (void *)0xC54BC550, (void *)0x00000000, (void *)0xC668B79A, (void *)0x00000001,
    (void *)0xC54F5025, (void *)0x00000000, (void *)0xC669F2E1, (void *)0x00000001,
    (void *)0xC5CDCB71, (void *)0x00000000, (void *)0xC63A25F6, (void *)0x00000001,
    (void *)0xC5CBF93F, (void *)0x00000000, (void *)0xC63A3C85, (void *)0x00000001,
    (void *)0xC5C8A808, (void *)0x00000000, (void *)0xC63A5F8F, (void *)0x00000001,
    (void *)0x42102420, (void *)0x00000000, (void *)0xC38E9ED9, (void *)0x00000001,
    (void *)0x4302655A, (void *)0x00000000, (void *)0xC3AA47C8, (void *)0x00000001,
    (void *)0x432F0759, (void *)0x00000000, (void *)0xC3BA1B12, (void *)0x00000001,
    (void *)0xC54A1FA6, (void *)0x00000000, (void *)0xC6681248, (void *)0x00000001,
    (void *)0xC54D68C9, (void *)0x00000000, (void *)0xC669505C, (void *)0x00000001,
    (void *)0xC5C97081, (void *)0x00000000, (void *)0xC63AE648, (void *)0x00000001,
    (void *)0xC5CA54DB, (void *)0x00000000, (void *)0xC63A46D7, (void *)0x00000001,
    (void *)0xC5388435, (void *)0x00000000, (void *)0xC60CE5E0, (void *)0x00000001,
    (void *)0x42A00767, (void *)0x00000000, (void *)0xC39CC80A, (void *)0x00000001,
    (void *)0xC52F1E8B, (void *)0x00000000, (void *)0xC60ED997, (void *)0x00000001,
    (void *)0x41B61F6B, (void *)0x00000000, (void *)0xC3A7BD81, (void *)0x00000001,
    (void *)0x42963207, (void *)0x00000000, (void *)0xC3B6AC85, (void *)0x00000001,
    (void *)0x42F42042, (void *)0x00000000, (void *)0xC3C3E351, (void *)0x00000001,
    (void *)0xC5CB1E58, (void *)0x00000000, (void *)0xC63ADD3D, (void *)0x00000001,
    (void *)0xC5CCF808, (void *)0x00000000, (void *)0xC63AD6AE, (void *)0x00000001,
    (void *)0xC534BDD3, (void *)0x00000000, (void *)0xC60CB891, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80405914[124] = {
    (void *)0x44014B76, (void *)0x00000000, (void *)0xC5C52B1D, (void *)0x00000001,
    (void *)0x4408185F, (void *)0x00000000, (void *)0xC5C530C1, (void *)0x00000001,
    (void *)0x440FC672, (void *)0x00000000, (void *)0xC5C5302D, (void *)0x00000001,
    (void *)0x4416CE6B, (void *)0x00000000, (void *)0xC5C53BD3, (void *)0x00000001,
    (void *)0x441FAE77, (void *)0x00000000, (void *)0xC5C538EE, (void *)0x00000001,
    (void *)0x4427D2DB, (void *)0x00000000, (void *)0xC5C54402, (void *)0x00000001,
    (void *)0x458CDFC1, (void *)0x00000000, (void *)0xC5C83B2B, (void *)0x00000001,
    (void *)0x458DC99E, (void *)0x00000000, (void *)0xC5C8502D, (void *)0x00000001,
    (void *)0x458EDD27, (void *)0x00000000, (void *)0xC5C840EC, (void *)0x00000001,
    (void *)0x458FEE9A, (void *)0x00000000, (void *)0xC5C8549A, (void *)0x00000001,
    (void *)0x45911804, (void *)0x00000000, (void *)0xC5C85037, (void *)0x00000001,
    (void *)0x4592021B, (void *)0x00000000, (void *)0xC5C8470E, (void *)0x00000001,
    (void *)0x4404A55B, (void *)0x00000000, (void *)0xC5C804C9, (void *)0x00000001,
    (void *)0x440CED64, (void *)0x00000000, (void *)0xC5C80ADB, (void *)0x00000001,
    (void *)0x4414203B, (void *)0x00000000, (void *)0xC5C80E29, (void *)0x00000001,
    (void *)0x441BB39C, (void *)0x00000000, (void *)0xC5C802AE, (void *)0x00000001,
    (void *)0x4424A5D0, (void *)0x00000000, (void *)0xC5C7F66D, (void *)0x00000001,
    (void *)0x442DDA53, (void *)0x00000000, (void *)0xC5C7FF4A, (void *)0x00000001,
    (void *)0x44E99442, (void *)0x00000000, (void *)0xC46BBCAF, (void *)0x00000001,
    (void *)0x44EB437D, (void *)0x00000000, (void *)0xC46278C1, (void *)0x00000001,
    (void *)0x44ED00C5, (void *)0x00000000, (void *)0xC45888A9, (void *)0x00000001,
    (void *)0x44EE6148, (void *)0x00000000, (void *)0xC4505249, (void *)0x00000001,
    (void *)0x44EF77CF, (void *)0x00000000, (void *)0xC4487392, (void *)0x00000001,
    (void *)0x44F13452, (void *)0x00000000, (void *)0xC4413780, (void *)0x00000001,
    (void *)0x44E18408, (void *)0x00000000, (void *)0xC468128F, (void *)0x00000001,
    (void *)0x44E2EA66, (void *)0x00000000, (void *)0xC460D99A, (void *)0x00000001,
    (void *)0x44E4AD48, (void *)0x00000000, (void *)0xC4589B85, (void *)0x00000001,
    (void *)0x44E5B171, (void *)0x00000000, (void *)0xC450BF56, (void *)0x00000001,
    (void *)0x44E7727F, (void *)0x00000000, (void *)0xC447CAC9, (void *)0x00000001,
    (void *)0x44E914EE, (void *)0x00000000, (void *)0xC43F227D, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80405B04[124] = {
    (void *)0x44014B76, (void *)0x00000000, (void *)0xC5C52B1D, (void *)0x00000001,
    (void *)0x4408185F, (void *)0x00000000, (void *)0xC5C530C1, (void *)0x00000001,
    (void *)0x440FC672, (void *)0x00000000, (void *)0xC5C5302D, (void *)0x00000001,
    (void *)0x4416CE6B, (void *)0x00000000, (void *)0xC5C53BD3, (void *)0x00000001,
    (void *)0x441FAE77, (void *)0x00000000, (void *)0xC5C538EE, (void *)0x00000001,
    (void *)0x4427D2DB, (void *)0x00000000, (void *)0xC5C54402, (void *)0x00000001,
    (void *)0x4518367F, (void *)0x00000000, (void *)0xC5B0A521, (void *)0x00000001,
    (void *)0x451A0A3D, (void *)0x00000000, (void *)0xC5B0BA23, (void *)0x00000001,
    (void *)0x451C3150, (void *)0x00000000, (void *)0xC5B0AAE1, (void *)0x00000001,
    (void *)0x451E5435, (void *)0x00000000, (void *)0xC5B0BE8D, (void *)0x00000001,
    (void *)0x4520A70A, (void *)0x00000000, (void *)0xC5B0BA2B, (void *)0x00000001,
    (void *)0x45227B37, (void *)0x00000000, (void *)0xC5B0B104, (void *)0x00000001,
    (void *)0x4404A55B, (void *)0x00000000, (void *)0xC5C804C9, (void *)0x00000001,
    (void *)0x440CED64, (void *)0x00000000, (void *)0xC5C80ADB, (void *)0x00000001,
    (void *)0x4414203B, (void *)0x00000000, (void *)0xC5C80E29, (void *)0x00000001,
    (void *)0x441BB39C, (void *)0x00000000, (void *)0xC5C802AE, (void *)0x00000001,
    (void *)0x4424A5D0, (void *)0x00000000, (void *)0xC5C7F66D, (void *)0x00000001,
    (void *)0x442DDA53, (void *)0x00000000, (void *)0xC5C7FF4A, (void *)0x00000001,
    (void *)0x453EF256, (void *)0x00000000, (void *)0xC4436309, (void *)0x00000001,
    (void *)0x453FC9F0, (void *)0x00000000, (void *)0xC43A1F1C, (void *)0x00000001,
    (void *)0x4540A893, (void *)0x00000000, (void *)0xC4302F04, (void *)0x00000001,
    (void *)0x454158D5, (void *)0x00000000, (void *)0xC427F8A2, (void *)0x00000001,
    (void *)0x4541E419, (void *)0x00000000, (void *)0xC42019ED, (void *)0x00000001,
    (void *)0x4542C25A, (void *)0x00000000, (void *)0xC418DDDB, (void *)0x00000001,
    (void *)0x453AEA35, (void *)0x00000000, (void *)0xC43FB8EA, (void *)0x00000001,
    (void *)0x453B9D64, (void *)0x00000000, (void *)0xC4387FF5, (void *)0x00000001,
    (void *)0x453C7ED5, (void *)0x00000000, (void *)0xC43041DE, (void *)0x00000001,
    (void *)0x453D00E9, (void *)0x00000000, (void *)0xC42865AF, (void *)0x00000001,
    (void *)0x453DE175, (void *)0x00000000, (void *)0xC41F7124, (void *)0x00000001,
    (void *)0x453EB2A8, (void *)0x00000000, (void *)0xC416C8D7, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80405CF4[104] = {
    (void *)0x44028C90, (void *)0x00000000, (void *)0xC5048683, (void *)0x00000001,
    (void *)0x43E75A54, (void *)0x00000000, (void *)0xC502D842, (void *)0x00000001,
    (void *)0x43CFE22D, (void *)0x00000000, (void *)0xC50159C3, (void *)0x00000001,
    (void *)0x43B6D3DA, (void *)0x00000000, (void *)0xC4FDA581, (void *)0x00000001,
    (void *)0x439DFC6A, (void *)0x00000000, (void *)0xC4F93560, (void *)0x00000001,
    (void *)0x4239CD1E, (void *)0x00000000, (void *)0x44C08AB8, (void *)0x00000001,
    (void *)0x42327712, (void *)0x00000000, (void *)0x44C79614, (void *)0x00000001,
    (void *)0x4232042B, (void *)0x00000000, (void *)0x44CEE89C, (void *)0x00000001,
    (void *)0x42308C10, (void *)0x00000000, (void *)0x44D57591, (void *)0x00000001,
    (void *)0x4387B405, (void *)0x00000000, (void *)0xC4F487AE, (void *)0x00000001,
    (void *)0x41678A87, (void *)0x00000000, (void *)0x44C074EE, (void *)0x00000001,
    (void *)0x4160462A, (void *)0x00000000, (void *)0x44C7A029, (void *)0x00000001,
    (void *)0x4174DAC4, (void *)0x00000000, (void *)0x44CF18FE, (void *)0x00000001,
    (void *)0x4167DD4F, (void *)0x00000000, (void *)0x44D5A277, (void *)0x00000001,
    (void *)0x436E6100, (void *)0x00000000, (void *)0xC4EEF9DB, (void *)0x00000001,
    (void *)0x44CA12FA, (void *)0x00000000, (void *)0xC4A5423D, (void *)0x00000001,
    (void *)0x44C97189, (void *)0x00000000, (void *)0xC49D974C, (void *)0x00000001,
    (void *)0x44C99062, (void *)0x00000000, (void *)0xC49541EC, (void *)0x00000001,
    (void *)0x44C960CD, (void *)0x00000000, (void *)0xC48C062D, (void *)0x00000001,
    (void *)0x44C9612F, (void *)0x00000000, (void *)0xC484DAA0, (void *)0x00000001,
    (void *)0x44C5F0D5, (void *)0x00000000, (void *)0xC4A61010, (void *)0x00000001,
    (void *)0x44C59B6D, (void *)0x00000000, (void *)0xC49E013F, (void *)0x00000001,
    (void *)0x44C5EF96, (void *)0x00000000, (void *)0xC4952E4E, (void *)0x00000001,
    (void *)0x44C5FE5E, (void *)0x00000000, (void *)0xC48C8CFE, (void *)0x00000001,
    (void *)0x44C5C408, (void *)0x00000000, (void *)0xC484F537, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80405E94[104] = {
    (void *)0x449A7344, (void *)0x00000000, (void *)0xC2502C10, (void *)0x00000001,
    (void *)0x4497362D, (void *)0x00000000, (void *)0x4105F264, (void *)0x00000001,
    (void *)0x44945971, (void *)0x00000000, (void *)0x428EFBA3, (void *)0x00000001,
    (void *)0x449379C3, (void *)0x00000000, (void *)0x430256DC, (void *)0x00000001,
    (void *)0x44958893, (void *)0x00000000, (void *)0xC277685B, (void *)0x00000001,
    (void *)0x42E43C9F, (void *)0x00000000, (void *)0xC56FBD8D, (void *)0x00000001,
    (void *)0x434E7EE0, (void *)0x00000000, (void *)0x4502FBF0, (void *)0x00000001,
    (void *)0x43CD3176, (void *)0x00000000, (void *)0x4509FDD3, (void *)0x00000001,
    (void *)0x448E6DC3, (void *)0x00000000, (void *)0x42F8E618, (void *)0x00000001,
    (void *)0x4492BCF6, (void *)0x00000000, (void *)0xC0FEFAF0, (void *)0x00000001,
    (void *)0x4316AC30, (void *)0x00000000, (void *)0xC572D035, (void *)0x00000001,
    (void *)0x42A91825, (void *)0x00000000, (void *)0xC56B58AC, (void *)0x00000001,
    (void *)0x4396636E, (void *)0x00000000, (void *)0x45072CD9, (void *)0x00000001,
    (void *)0x4401DB28, (void *)0x00000000, (void *)0x450B6ECD, (void *)0x00000001,
    (void *)0x448FB7E7, (void *)0x00000000, (void *)0x425B4361, (void *)0x00000001,
    (void *)0x450233A6, (void *)0x00000000, (void *)0xC57BF19E, (void *)0x00000001,
    (void *)0x450D1F81, (void *)0x00000000, (void *)0xC578CFAA, (void *)0x00000001,
    (void *)0x4348E20C, (void *)0x00000000, (void *)0xC575E371, (void *)0x00000001,
    (void *)0x45282477, (void *)0x00000000, (void *)0xC4F2366F, (void *)0x00000001,
    (void *)0x4527FF64, (void *)0x00000000, (void *)0xC4EA509C, (void *)0x00000001,
    (void *)0x44F914D5, (void *)0x00000000, (void *)0xC57CED89, (void *)0x00000001,
    (void *)0x45083B7D, (void *)0x00000000, (void *)0xC57A8C98, (void *)0x00000001,
    (void *)0x451151FC, (void *)0x00000000, (void *)0xC57741D7, (void *)0x00000001,
    (void *)0x45264E00, (void *)0x00000000, (void *)0xC4F29800, (void *)0x00000001,
    (void *)0x45261E31, (void *)0x00000000, (void *)0xC4EA6B33, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80406034[104] = {
    (void *)0x444EF59D, (void *)0x00000000, (void *)0x42523E8C, (void *)0x00000001,
    (void *)0x433811BE, (void *)0x00000000, (void *)0x44D2A4DD, (void *)0x00000001,
    (void *)0x43D38368, (void *)0x00000000, (void *)0x44DB0B75, (void *)0x00000001,
    (void *)0x444DCEF3, (void *)0x00000000, (void *)0xC36D46D6, (void *)0x00000001,
    (void *)0x444F76AE, (void *)0x00000000, (void *)0xC208C32A, (void *)0x00000001,
    (void *)0x4127BC21, (void *)0x00000000, (void *)0x446EE434, (void *)0x00000001,
    (void *)0x4134949A, (void *)0x00000000, (void *)0x447B6CEE, (void *)0x00000001,
    (void *)0x41249820, (void *)0x00000000, (void *)0x4484176D, (void *)0x00000001,
    (void *)0x411C05A5, (void *)0x00000000, (void *)0x4489A785, (void *)0x00000001,
    (void *)0x445E5807, (void *)0x00000000, (void *)0xC2B5B62E, (void *)0x00000001,
    (void *)0xC16A5D64, (void *)0x00000000, (void *)0x446F1415, (void *)0x00000001,
    (void *)0xC18353AE, (void *)0x00000000, (void *)0x447BBD81, (void *)0x00000001,
    (void *)0xC18A0270, (void *)0x00000000, (void *)0x44840D17, (void *)0x00000001,
    (void *)0xC18DB3B1, (void *)0x00000000, (void *)0x4489949C, (void *)0x00000001,
    (void *)0x445F2D5B, (void *)0x00000000, (void *)0xC1D373B1, (void *)0x00000001,
    (void *)0x42E0CC64, (void *)0x00000000, (void *)0x44CC607B, (void *)0x00000001,
    (void *)0x43A9D25E, (void *)0x00000000, (void *)0x44DA408B, (void *)0x00000001,
    (void *)0x4411C981, (void *)0x00000000, (void *)0x44D68DF4, (void *)0x00000001,
    (void *)0x444E4ACE, (void *)0x00000000, (void *)0xC2B416F7, (void *)0x00000001,
    (void *)0x445ED4AA, (void *)0x00000000, (void *)0xC322F77A, (void *)0x00000001,
    (void *)0x445FF1EC, (void *)0x00000000, (void *)0x4241532B, (void *)0x00000001,
    (void *)0x43845461, (void *)0x00000000, (void *)0x44D85DB2, (void *)0x00000001,
    (void *)0x43FE8DFA, (void *)0x00000000, (void *)0x44D9C266, (void *)0x00000001,
    (void *)0x444E0874, (void *)0x00000000, (void *)0xC31E180A, (void *)0x00000001,
    (void *)0x445FA2F5, (void *)0x00000000, (void *)0xC3718E6A, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804061D4[104] = {
    (void *)0xC50613B6, (void *)0x00000000, (void *)0xC4758BF6, (void *)0x00000001,
    (void *)0x44303AEB, (void *)0x00000000, (void *)0x43F0A38C, (void *)0x00000001,
    (void *)0x44233568, (void *)0x00000000, (void *)0x43E0FF7D, (void *)0x00000001,
    (void *)0xC50C121D, (void *)0x00000000, (void *)0xC5046902, (void *)0x00000001,
    (void *)0xC5050971, (void *)0x00000000, (void *)0xC480FA25, (void *)0x00000001,
    (void *)0xC58E719E, (void *)0x00000000, (void *)0xC51E21AE, (void *)0x00000001,
    (void *)0xC591C535, (void *)0x00000000, (void *)0xC5129B06, (void *)0x00000001,
    (void *)0xC5918917, (void *)0x00000000, (void *)0xC508FD50, (void *)0x00000001,
    (void *)0xC5909554, (void *)0x00000000, (void *)0xC5043154, (void *)0x00000001,
    (void *)0xC50B4CE9, (void *)0x00000000, (void *)0xC507B93F, (void *)0x00000001,
    (void *)0xC5902702, (void *)0x00000000, (void *)0xC51AA9E7, (void *)0x00000001,
    (void *)0xC5913CBE, (void *)0x00000000, (void *)0xC51717DB, (void *)0x00000001,
    (void *)0xC591DA7D, (void *)0x00000000, (void *)0xC50D6D91, (void *)0x00000001,
    (void *)0xC58F2F89, (void *)0x00000000, (void *)0xC50060B4, (void *)0x00000001,
    (void *)0xC500C1CB, (void *)0x00000000, (void *)0xC47B3BD7, (void *)0x00000001,
    (void *)0xC5035D71, (void *)0x00000000, (void *)0xC4785AD7, (void *)0x00000001,
    (void *)0x442B49F7, (void *)0x00000000, (void *)0x43D985F4, (void *)0x00000001,
    (void *)0x441D0FFE, (void *)0x00000000, (void *)0x43CCB1FF, (void *)0x00000001,
    (void *)0xC5064F9E, (void *)0x00000000, (void *)0xC5059873, (void *)0x00000001,
    (void *)0xC50F3C19, (void *)0x00000000, (void *)0xC508DDF8, (void *)0x00000001,
    (void *)0xC501D4A4, (void *)0x00000000, (void *)0xC46F02D7, (void *)0x00000001,
    (void *)0x442813C8, (void *)0x00000000, (void *)0x43F6EBCD, (void *)0x00000001,
    (void *)0x442382DB, (void *)0x00000000, (void *)0x43C4815F, (void *)0x00000001,
    (void *)0xC5079014, (void *)0x00000000, (void *)0xC5026DD7, (void *)0x00000001,
    (void *)0xC51051CB, (void *)0x00000000, (void *)0xC505AAB8, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80406374[104] = {
    (void *)0x447DB48B, (void *)0x00000000, (void *)0x45055487, (void *)0x00000001,
    (void *)0x447BC906, (void *)0x00000000, (void *)0x450131B2, (void *)0x00000001,
    (void *)0x44832214, (void *)0x00000000, (void *)0x43D7B080, (void *)0x00000001,
    (void *)0x44CA307B, (void *)0x00000000, (void *)0xC4AE1E4E, (void *)0x00000001,
    (void *)0xC3A8EEB8, (void *)0x00000000, (void *)0xC5014A21, (void *)0x00000001,
    (void *)0x44899AA8, (void *)0x00000000, (void *)0x45053025, (void *)0x00000001,
    (void *)0x4488E256, (void *)0x00000000, (void *)0x45013DA2, (void *)0x00000001,
    (void *)0x448E1D81, (void *)0x00000000, (void *)0x43D5C100, (void *)0x00000001,
    (void *)0x44CE9981, (void *)0x00000000, (void *)0xC4B2C506, (void *)0x00000001,
    (void *)0xC3940AA0, (void *)0x00000000, (void *)0xC4FAA062, (void *)0x00000001,
    (void *)0x4493B78D, (void *)0x00000000, (void *)0x45054BA6, (void *)0x00000001,
    (void *)0x44932548, (void *)0x00000000, (void *)0x4501D8FE, (void *)0x00000001,
    (void *)0x4497A266, (void *)0x00000000, (void *)0x43D57F5F, (void *)0x00000001,
    (void *)0x44CEC5CB, (void *)0x00000000, (void *)0xC4A8C117, (void *)0x00000001,
    (void *)0xC37F9958, (void *)0x00000000, (void *)0xC4F22C31, (void *)0x00000001,
    (void *)0xC48083C7, (void *)0x00000000, (void *)0x44F0E4E5, (void *)0x00000001,
    (void *)0xC48B1A7F, (void *)0x00000000, (void *)0x44D7F4E5, (void *)0x00000001,
    (void *)0x44A069DB, (void *)0x00000000, (void *)0x43D618EF, (void *)0x00000001,
    (void *)0x44D49842, (void *)0x00000000, (void *)0xC4ABA46A, (void *)0x00000001,
    (void *)0xC34A81CB, (void *)0x00000000, (void *)0xC4EE1F2B, (void *)0x00000001,
    (void *)0xC46C1F4C, (void *)0x00000000, (void *)0x44FA63A6, (void *)0x00000001,
    (void *)0xC4878179, (void *)0x00000000, (void *)0x44E5BE4E, (void *)0x00000001,
    (void *)0x44A850FE, (void *)0x00000000, (void *)0x43D58E11, (void *)0x00000001,
    (void *)0x44C7650E, (void *)0x00000000, (void *)0xC4090F57, (void *)0x00000001,
    (void *)0x44CE2800, (void *)0x00000000, (void *)0xC419DCE0, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80406514[104] = {
    (void *)0x45279D23, (void *)0x00000000, (void *)0x4525A487, (void *)0x00000001,
    (void *)0x4528F242, (void *)0x00000000, (void *)0x451A21B2, (void *)0x00000001,
    (void *)0x4526610A, (void *)0x00000000, (void *)0xC4B613DF, (void *)0x00000001,
    (void *)0x443060F6, (void *)0x00000000, (void *)0xC4ECDE4E, (void *)0x00000001,
    (void *)0x45280229, (void *)0x00000000, (void *)0x4432577B, (void *)0x00000001,
    (void *)0x451CFD54, (void *)0x00000000, (void *)0x45363025, (void *)0x00000001,
    (void *)0x4524E12B, (void *)0x00000000, (void *)0x452DEDA2, (void *)0x00000001,
    (void *)0x45281EC1, (void *)0x00000000, (void *)0xC49E0FBE, (void *)0x00000001,
    (void *)0x443E7302, (void *)0x00000000, (void *)0xC4F34506, (void *)0x00000001,
    (void *)0xC3940AA0, (void *)0x00000000, (void *)0xC4FAA062, (void *)0x00000001,
    (void *)0x45038BC7, (void *)0x00000000, (void *)0x4537BBA6, (void *)0x00000001,
    (void *)0x450FD2A4, (void *)0x00000000, (void *)0x453898FE, (void *)0x00000001,
    (void *)0x45287133, (void *)0x00000000, (void *)0xC487A029, (void *)0x00000001,
    (void *)0x4522A2E5, (void *)0x00000000, (void *)0xC576708B, (void *)0x00000001,
    (void *)0x4527C66A, (void *)0x00000000, (void *)0x444D679E, (void *)0x00000001,
    (void *)0xC48083C7, (void *)0x00000000, (void *)0x44F0E4E5, (void *)0x00000001,
    (void *)0x43A89604, (void *)0x00000000, (void *)0x450A3A73, (void *)0x00000001,
    (void *)0x452704EE, (void *)0x00000000, (void *)0xC461F388, (void *)0x00000001,
    (void *)0x45268C21, (void *)0x00000000, (void *)0xC5724235, (void *)0x00000001,
    (void *)0xC34A81CB, (void *)0x00000000, (void *)0xC4EE1F2B, (void *)0x00000001,
    (void *)0x43D14168, (void *)0x00000000, (void *)0x450EC1D3, (void *)0x00000001,
    (void *)0xC4878179, (void *)0x00000000, (void *)0x44E5BE4E, (void *)0x00000001,
    (void *)0x4525887F, (void *)0x00000000, (void *)0xC43A38F7, (void *)0x00000001,
    (void *)0x45216287, (void *)0x00000000, (void *)0xC53D23D7, (void *)0x00000001,
    (void *)0x45235400, (void *)0x00000000, (void *)0xC5429737, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804066B4[104] = {
    (void *)0xC574993F, (void *)0x00000000, (void *)0x4525CF8D, (void *)0x00000001,
    (void *)0xC5751025, (void *)0x00000000, (void *)0x45202639, (void *)0x00000001,
    (void *)0xC5BD73C5, (void *)0x00000000, (void *)0xC4A64C73, (void *)0x00000001,
    (void *)0xC5BCDFBE, (void *)0x00000000, (void *)0xC49F6558, (void *)0x00000001,
    (void *)0xC54A690A, (void *)0x00000000, (void *)0xC4F9ADD3, (void *)0x00000001,
    (void *)0xC572105E, (void *)0x00000000, (void *)0x4525F0DD, (void *)0x00000001,
    (void *)0xC5722127, (void *)0x00000000, (void *)0x451FE3BA, (void *)0x00000001,
    (void *)0xC5B9DAC1, (void *)0x00000000, (void *)0xC4A8987B, (void *)0x00000001,
    (void *)0xC5B9C33B, (void *)0x00000000, (void *)0xC4A2F127, (void *)0x00000001,
    (void *)0xC545C117, (void *)0x00000000, (void *)0xC4EBE604, (void *)0x00000001,
    (void *)0xC56A867F, (void *)0x00000000, (void *)0x45BAC6F0, (void *)0x00000001,
    (void *)0xC56CAC7F, (void *)0x00000000, (void *)0x45B70864, (void *)0x00000001,
    (void *)0xC5B699F8, (void *)0x00000000, (void *)0xC4AA160C, (void *)0x00000001,
    (void *)0xC5B6C081, (void *)0x00000000, (void *)0xC4A40862, (void *)0x00000001,
    (void *)0xC543986A, (void *)0x00000000, (void *)0xC4D73EC1, (void *)0x00000001,
    (void *)0xC5774E0C, (void *)0x00000000, (void *)0x45015CBC, (void *)0x00000001,
    (void *)0xC5771F6D, (void *)0x00000000, (void *)0x44F4EAE1, (void *)0x00000001,
    (void *)0xC574D95C, (void *)0x00000000, (void *)0x44B56189, (void *)0x00000001,
    (void *)0xC574F062, (void *)0x00000000, (void *)0x44AAB2D1, (void *)0x00000001,
    (void *)0xC544762D, (void *)0x00000000, (void *)0xC4C455D3, (void *)0x00000001,
    (void *)0xC5748B33, (void *)0x00000000, (void *)0x45016225, (void *)0x00000001,
    (void *)0xC574946A, (void *)0x00000000, (void *)0x44F54BD7, (void *)0x00000001,
    (void *)0xC571C466, (void *)0x00000000, (void *)0x44B5864E, (void *)0x00000001,
    (void *)0xC571D8B0, (void *)0x00000000, (void *)0x44AAA24E, (void *)0x00000001,
    (void *)0xC5495BA2, (void *)0x00000000, (void *)0xC4B15DAA, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80406854[104] = {
    (void *)0xC5B827D3, (void *)0x00000000, (void *)0xC166FEE5, (void *)0x00000001,
    (void *)0xC545E354, (void *)0x00000000, (void *)0x440549C1, (void *)0x00000001,
    (void *)0xC5AE3864, (void *)0x00000000, (void *)0x448A8614, (void *)0x00000001,
    (void *)0xC5AF617D, (void *)0x00000000, (void *)0x449B6010, (void *)0x00000001,
    (void *)0xC5A6E044, (void *)0x00000000, (void *)0x4531F55C, (void *)0x00000001,
    (void *)0xC5B76A48, (void *)0x00000000, (void *)0xC2F574F1, (void *)0x00000001,
    (void *)0xC5B5A01D, (void *)0x00000000, (void *)0x434775F7, (void *)0x00000001,
    (void *)0xC544E64A, (void *)0x00000000, (void *)0x443883E1, (void *)0x00000001,
    (void *)0xC5B0D18F, (void *)0x00000000, (void *)0x449F210E, (void *)0x00000001,
    (void *)0xC5A9E0C1, (void *)0x00000000, (void *)0x4529FEC9, (void *)0x00000001,
    (void *)0xC5B5B9D5, (void *)0x00000000, (void *)0xC3558903, (void *)0x00000001,
    (void *)0xC5B73B04, (void *)0x00000000, (void *)0x42EDF382, (void *)0x00000001,
    (void *)0xC543E1CF, (void *)0x00000000, (void *)0x441CD5B9, (void *)0x00000001,
    (void *)0xC5AF7DFC, (void *)0x00000000, (void *)0x4492CA35, (void *)0x00000001,
    (void *)0xC5AB1860, (void *)0x00000000, (void *)0x45207493, (void *)0x00000001,
    (void *)0xC5473AC1, (void *)0x00000000, (void *)0xC446F7AC, (void *)0x00000001,
    (void *)0xC5480A77, (void *)0x00000000, (void *)0xC42F63F6, (void *)0x00000001,
    (void *)0xC5496EC1, (void *)0x00000000, (void *)0xC41147DE, (void *)0x00000001,
    (void *)0xC5B11FB0, (void *)0x00000000, (void *)0x44914473, (void *)0x00000001,
    (void *)0xC5A9668D, (void *)0x00000000, (void *)0x4516D698, (void *)0x00000001,
    (void *)0xC54A5302, (void *)0x00000000, (void *)0xC4484F9C, (void *)0x00000001,
    (void *)0xC54A56B0, (void *)0x00000000, (void *)0xC42FC415, (void *)0x00000001,
    (void *)0xC54BAC4A, (void *)0x00000000, (void *)0xC41686B5, (void *)0x00000001,
    (void *)0xC5AF025A, (void *)0x00000000, (void *)0x44860646, (void *)0x00000001,
    (void *)0xC5A6BF0C, (void *)0x00000000, (void *)0x450EAFDF, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804069F4[104] = {
    (void *)0xC3252B5E, (void *)0x00000000, (void *)0xC5960814, (void *)0x00000001,
    (void *)0xC2D828CE, (void *)0x00000000, (void *)0xC5936E27, (void *)0x00000001,
    (void *)0xC2A5A27A, (void *)0x00000000, (void *)0xC590D310, (void *)0x00000001,
    (void *)0x43C270BE, (void *)0x00000000, (void *)0xC555F2F2, (void *)0x00000001,
    (void *)0x43AE6646, (void *)0x00000000, (void *)0xC5577D50, (void *)0x00000001,
    (void *)0xC30ED219, (void *)0x00000000, (void *)0xC596B400, (void *)0x00000001,
    (void *)0xC2A2A578, (void *)0x00000000, (void *)0xC593F417, (void *)0x00000001,
    (void *)0xC25AD510, (void *)0x00000000, (void *)0xC59118C1, (void *)0x00000001,
    (void *)0x43CC176D, (void *)0x00000000, (void *)0xC55895E7, (void *)0x00000001,
    (void *)0x43B88F2E, (void *)0x00000000, (void *)0xC559DE73, (void *)0x00000001,
    (void *)0x43D8485C, (void *)0x00000000, (void *)0xC5543775, (void *)0x00000001,
    (void *)0x43E3BC05, (void *)0x00000000, (void *)0xC556C7BE, (void *)0x00000001,
    (void *)0x43888319, (void *)0x00000000, (void *)0x44C5BF5C, (void *)0x00000001,
    (void *)0x440C25BE, (void *)0x00000000, (void *)0x44A8CAF2, (void *)0x00000001,
    (void *)0x43FB801D, (void *)0x00000000, (void *)0x44B1A656, (void *)0x00000001,
    (void *)0x43DB77C8, (void *)0x00000000, (void *)0x44B9AC52, (void *)0x00000001,
    (void *)0x43B7D13B, (void *)0x00000000, (void *)0x44C07F33, (void *)0x00000001,
    (void *)0x445D8861, (void *)0x00000000, (void *)0xC267E04C, (void *)0x00000001,
    (void *)0x4467482B, (void *)0x00000000, (void *)0xC3509DB2, (void *)0x00000001,
    (void *)0x44B76CDD, (void *)0x00000000, (void *)0xC494EA25, (void *)0x00000001,
    (void *)0x44B9C323, (void *)0x00000000, (void *)0xC49C908B, (void *)0x00000001,
    (void *)0x4461BB63, (void *)0x00000000, (void *)0xC3071C15, (void *)0x00000001,
    (void *)0x446D4EF0, (void *)0x00000000, (void *)0xC38303FE, (void *)0x00000001,
    (void *)0x44B2A07B, (void *)0x00000000, (void *)0xC4960F85, (void *)0x00000001,
    (void *)0x44B4CB23, (void *)0x00000000, (void *)0xC49DDC39, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80406B94[104] = {
    (void *)0xC3252B5E, (void *)0x00000000, (void *)0xC5960814, (void *)0x00000001,
    (void *)0xC2D828CE, (void *)0x00000000, (void *)0xC5936E27, (void *)0x00000001,
    (void *)0xC2A5A27A, (void *)0x00000000, (void *)0xC590D310, (void *)0x00000001,
    (void *)0x443A47F6, (void *)0x00000000, (void *)0xC54CB4EE, (void *)0x00000001,
    (void *)0x44218EA0, (void *)0x00000000, (void *)0xC54FB7B2, (void *)0x00000001,
    (void *)0xC30ED219, (void *)0x00000000, (void *)0xC596B400, (void *)0x00000001,
    (void *)0xC2A2A578, (void *)0x00000000, (void *)0xC593F417, (void *)0x00000001,
    (void *)0xC25AD510, (void *)0x00000000, (void *)0xC59118C1, (void *)0x00000001,
    (void *)0x43E97F91, (void *)0x00000000, (void *)0xC5553985, (void *)0x00000001,
    (void *)0x43BCC2A0, (void *)0x00000000, (void *)0xC5583042, (void *)0x00000001,
    (void *)0x44537C54, (void *)0x00000000, (void *)0xC549EC8F, (void *)0x00000001,
    (void *)0x440AA72B, (void *)0x00000000, (void *)0xC5527964, (void *)0x00000001,
    (void *)0x43888319, (void *)0x00000000, (void *)0x44C5BF5C, (void *)0x00000001,
    (void *)0x440C25BE, (void *)0x00000000, (void *)0x44A8CAF2, (void *)0x00000001,
    (void *)0x43FB801D, (void *)0x00000000, (void *)0x44B1A656, (void *)0x00000001,
    (void *)0x43DB77C8, (void *)0x00000000, (void *)0x44B9AC52, (void *)0x00000001,
    (void *)0x43B7D13B, (void *)0x00000000, (void *)0x44C07F33, (void *)0x00000001,
    (void *)0x44DDDC19, (void *)0x00000000, (void *)0xC3BA14F7, (void *)0x00000001,
    (void *)0x44EF9AA0, (void *)0x00000000, (void *)0xC40DCC40, (void *)0x00000001,
    (void *)0x45045D5C, (void *)0x00000000, (void *)0xC4551A1E, (void *)0x00000001,
    (void *)0x4532AAE1, (void *)0x00000000, (void *)0xC5145DE3, (void *)0x00000001,
    (void *)0x44E62312, (void *)0x00000000, (void *)0xC3EBD564, (void *)0x00000001,
    (void *)0x44F7B91F, (void *)0x00000000, (void *)0xC425D3A3, (void *)0x00000001,
    (void *)0x4500AB9E, (void *)0x00000000, (void *)0xC43B9422, (void *)0x00000001,
    (void *)0x4531344E, (void *)0x00000000, (void *)0xC516EDEC, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80406D34[104] = {
    (void *)0xC464E735, (void *)0x00000000, (void *)0xC59BFFF8, (void *)0x00000001,
    (void *)0xC5018BD7, (void *)0x00000000, (void *)0x423EA9DA, (void *)0x00000001,
    (void *)0xC5832750, (void *)0x00000000, (void *)0xC42616AB, (void *)0x00000001,
    (void *)0xC54935A6, (void *)0x00000000, (void *)0xC5C09F85, (void *)0x00000001,
    (void *)0xC3DF94CA, (void *)0x00000000, (void *)0xC593CA98, (void *)0x00000001,
    (void *)0xC44FAD56, (void *)0x00000000, (void *)0xC59A28DF, (void *)0x00000001,
    (void *)0xC43AB1B5, (void *)0x00000000, (void *)0xC598A01B, (void *)0x00000001,
    (void *)0xC4D04F44, (void *)0x00000000, (void *)0x42340120, (void *)0x00000001,
    (void *)0xC585B650, (void *)0x00000000, (void *)0xC3F68D2C, (void *)0x00000001,
    (void *)0xC54E3C2D, (void *)0x00000000, (void *)0xC5BF0A33, (void *)0x00000001,
    (void *)0xC3229D29, (void *)0x00000000, (void *)0xC2E8A880, (void *)0x00000001,
    (void *)0xC422A7F9, (void *)0x00000000, (void *)0xC597237B, (void *)0x00000001,
    (void *)0xC4B74323, (void *)0x00000000, (void *)0x423F649C, (void *)0x00000001,
    (void *)0xC585E466, (void *)0x00000000, (void *)0xC3C8AB09, (void *)0x00000001,
    (void *)0xC55503CB, (void *)0x00000000, (void *)0xC5BE939E, (void *)0x00000001,
    (void *)0xC3112A93, (void *)0x00000000, (void *)0xC2B0C791, (void *)0x00000001,
    (void *)0xC40B0457, (void *)0x00000000, (void *)0xC59580E5, (void *)0x00000001,
    (void *)0xC49F68DD, (void *)0x00000000, (void *)0x424DBE96, (void *)0x00000001,
    (void *)0xC58579A2, (void *)0x00000000, (void *)0xC393CDFE, (void *)0x00000001,
    (void *)0xC552AF79, (void *)0x00000000, (void *)0xC5BD2187, (void *)0x00000001,
    (void *)0xC54B4106, (void *)0x00000000, (void *)0xC5C21B00, (void *)0x00000001,
    (void *)0xC4EA3723, (void *)0x00000000, (void *)0x423FC546, (void *)0x00000001,
    (void *)0xC584BA6A, (void *)0x00000000, (void *)0xC4132DB9, (void *)0x00000001,
    (void *)0xC54FF9BA, (void *)0x00000000, (void *)0xC5C06BDB, (void *)0x00000001,
    (void *)0xC3B59910, (void *)0x00000000, (void *)0xC5921E6D, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80406ED4[104] = {
    (void *)0xC583698F, (void *)0x00000000, (void *)0xC426CF3A, (void *)0x00000001,
    (void *)0xC56F46D1, (void *)0x00000000, (void *)0xC5A13E8F, (void *)0x00000001,
    (void *)0x46125E63, (void *)0x00000000, (void *)0xC5C3E668, (void *)0x00000001,
    (void *)0x45F39733, (void *)0x00000000, (void *)0xC56C702D, (void *)0x00000001,
    (void *)0x4607B61E, (void *)0x00000000, (void *)0xC4BBCBCF, (void *)0x00000001,
    (void *)0xC584C600, (void *)0x00000000, (void *)0xC4122799, (void *)0x00000001,
    (void *)0xC57210E9, (void *)0x00000000, (void *)0xC59F96D5, (void *)0x00000001,
    (void *)0x4613C061, (void *)0x00000000, (void *)0xC5C52F79, (void *)0x00000001,
    (void *)0x45F425DF, (void *)0x00000000, (void *)0xC568706F, (void *)0x00000001,
    (void *)0x4608666F, (void *)0x00000000, (void *)0xC4BC1B1B, (void *)0x00000001,
    (void *)0xC585BAAA, (void *)0x00000000, (void *)0xC3EE03E7, (void *)0x00000001,
    (void *)0xC56FA5CB, (void *)0x00000000, (void *)0xC59F8C64, (void *)0x00000001,
    (void *)0xC571986F, (void *)0x00000000, (void *)0xC5A15D8F, (void *)0x00000001,
    (void *)0x45F54B64, (void *)0x00000000, (void *)0xC56C331B, (void *)0x00000001,
    (void *)0x46079B92, (void *)0x00000000, (void *)0xC4B774EE, (void *)0x00000001,
    (void *)0xC585AA75, (void *)0x00000000, (void *)0xC3BAD495, (void *)0x00000001,
    (void *)0x45E58D12, (void *)0x00000000, (void *)0xC4E4FDFC, (void *)0x00000001,
    (void *)0x45E59F87, (void *)0x00000000, (void *)0xC4EC8A0C, (void *)0x00000001,
    (void *)0x460F3E82, (void *)0x00000000, (void *)0xC5C16702, (void *)0x00000001,
    (void *)0x460848BD, (void *)0x00000000, (void *)0xC4B7ED1F, (void *)0x00000001,
    (void *)0xC584ED5C, (void *)0x00000000, (void *)0xC381B396, (void *)0x00000001,
    (void *)0x45E6F112, (void *)0x00000000, (void *)0xC4E4B20C, (void *)0x00000001,
    (void *)0x45E704CD, (void *)0x00000000, (void *)0xC4EC94C5, (void *)0x00000001,
    (void *)0x4610C42A, (void *)0x00000000, (void *)0xC5C2E91B, (void *)0x00000001,
    (void *)0x45F28EBA, (void *)0x00000000, (void *)0xC5691D1B, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80407074[104] = {
    (void *)0xC56481BE, (void *)0x00000000, (void *)0xC647BF48, (void *)0x00000001,
    (void *)0xC4DF81BA, (void *)0x00000000, (void *)0xC6205285, (void *)0x00000001,
    (void *)0xC50743F8, (void *)0x00000000, (void *)0xC62AC41F, (void *)0x00000001,
    (void *)0xC49AE558, (void *)0x00000000, (void *)0xC5DF9DE1, (void *)0x00000001,
    (void *)0xC499E0C5, (void *)0x00000000, (void *)0xC5DE00A2, (void *)0x00000001,
    (void *)0xC56925F8, (void *)0x00000000, (void *)0xC649C3CD, (void *)0x00000001,
    (void *)0xC4DDE4A4, (void *)0x00000000, (void *)0xC61FC4D7, (void *)0x00000001,
    (void *)0xC5057B33, (void *)0x00000000, (void *)0xC62A47CD, (void *)0x00000001,
    (void *)0xC49BD53F, (void *)0x00000000, (void *)0xC5E0FDFE, (void *)0x00000001,
    (void *)0xC49CD410, (void *)0x00000000, (void *)0xC5E297D5, (void *)0x00000001,
    (void *)0xC5612056, (void *)0x00000000, (void *)0xC646999A, (void *)0x00000001,
    (void *)0xC54EFED1, (void *)0x00000000, (void *)0xC6869FF1, (void *)0x00000001,
    (void *)0xC54E5F12, (void *)0x00000000, (void *)0xC687051A, (void *)0x00000001,
    (void *)0xC54DB579, (void *)0x00000000, (void *)0xC687698F, (void *)0x00000001,
    (void *)0xC48D727F, (void *)0x00000000, (void *)0xC69E65D2, (void *)0x00000001,
    (void *)0xC5510AA4, (void *)0x00000000, (void *)0xC68586F6, (void *)0x00000001,
    (void *)0xC5503B44, (void *)0x00000000, (void *)0xC685F0A9, (void *)0x00000001,
    (void *)0xC54F9487, (void *)0x00000000, (void *)0xC68651E6, (void *)0x00000001,
    (void *)0xC48D9137, (void *)0x00000000, (void *)0xC69F3EB8, (void *)0x00000001,
    (void *)0xC48D43AE, (void *)0x00000000, (void *)0xC69EDF43, (void *)0x00000001,
    (void *)0xC48D6CDD, (void *)0x00000000, (void *)0xC69DFDA9, (void *)0x00000001,
    (void *)0xC48D3591, (void *)0x00000000, (void *)0xC69FB82E, (void *)0x00000001,
    (void *)0xC566151B, (void *)0x00000000, (void *)0xC6487900, (void *)0x00000001,
    (void *)0xC5679BF0, (void *)0x00000000, (void *)0xC64927EC, (void *)0x00000001,
    (void *)0xC562B419, (void *)0x00000000, (void *)0xC6472FE1, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80407214[104] = {
    (void *)0xC5740B3B, (void *)0x00000000, (void *)0xC661570A, (void *)0x00000001,
    (void *)0xC56F58EE, (void *)0x00000000, (void *)0xC66252B8, (void *)0x00000001,
    (void *)0x4325DC71, (void *)0x00000000, (void *)0xC61B6E0F, (void *)0x00000001,
    (void *)0x4322CBCD, (void *)0x00000000, (void *)0xC61C41AE, (void *)0x00000001,
    (void *)0x431CCE6A, (void *)0x00000000, (void *)0xC61CEBB8, (void *)0x00000001,
    (void *)0xC571979A, (void *)0x00000000, (void *)0xC661DE33, (void *)0x00000001,
    (void *)0xC56C5979, (void *)0x00000000, (void *)0xC662C052, (void *)0x00000001,
    (void *)0x432A31E5, (void *)0x00000000, (void *)0xC618F257, (void *)0x00000001,
    (void *)0x4329DF76, (void *)0x00000000, (void *)0xC619D705, (void *)0x00000001,
    (void *)0x4328748F, (void *)0x00000000, (void *)0xC61A9734, (void *)0x00000001,
    (void *)0xC5B3E20A, (void *)0x00000000, (void *)0xC629D429, (void *)0x00000001,
    (void *)0xC5B68421, (void *)0x00000000, (void *)0xC62AEA8F, (void *)0x00000001,
    (void *)0xC5BCF53B, (void *)0x00000000, (void *)0xC64A0314, (void *)0x00000001,
    (void *)0xC5B7C28D, (void *)0x00000000, (void *)0xC62B6C71, (void *)0x00000001,
    (void *)0xC5B55D42, (void *)0x00000000, (void *)0xC62A33E1, (void *)0x00000001,
    (void *)0xC50ACBAA, (void *)0x00000000, (void *)0xC5C1583B, (void *)0x00000001,
    (void *)0xC5089FC3, (void *)0x00000000, (void *)0xC5C2C2F8, (void *)0x00000001,
    (void *)0xC50633AA, (void *)0x00000000, (void *)0xC5C427B8, (void *)0x00000001,
    (void *)0xC502CB9E, (void *)0x00000000, (void *)0xC5C67FAA, (void *)0x00000001,
    (void *)0xC5046266, (void *)0x00000000, (void *)0xC5C57968, (void *)0x00000001,
    (void *)0xC5BBA1E5, (void *)0x00000000, (void *)0xC64AC75C, (void *)0x00000001,
    (void *)0xC5BA01D1, (void *)0x00000000, (void *)0xC64B9A85, (void *)0x00000001,
    (void *)0xC5B83900, (void *)0x00000000, (void *)0xC64C799A, (void *)0x00000001,
    (void *)0xC5C06B7B, (void *)0x00000000, (void *)0xC647CC33, (void *)0x00000001,
    (void *)0xC5BEE462, (void *)0x00000000, (void *)0xC648F99A, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804073B4[104] = {
    (void *)0x458F7ACF, (void *)0x00000000, (void *)0xC5CB1252, (void *)0x00000001,
    (void *)0x459026C9, (void *)0x00000000, (void *)0xC5CD0B14, (void *)0x00000001,
    (void *)0x458F5EFA, (void *)0x00000000, (void *)0xC5CCF2C9, (void *)0x00000001,
    (void *)0x458FB296, (void *)0x00000000, (void *)0xC5CEA564, (void *)0x00000001,
    (void *)0x44465A82, (void *)0x00000000, (void *)0xC5E27D1B, (void *)0x00000001,
    (void *)0x458F17FC, (void *)0x00000000, (void *)0xC5CE996A, (void *)0x00000001,
    (void *)0x4591A842, (void *)0x00000000, (void *)0xC510A404, (void *)0x00000001,
    (void *)0x4591A0F0, (void *)0x00000000, (void *)0xC513A71F, (void *)0x00000001,
    (void *)0x45903E00, (void *)0x00000000, (void *)0xC5CB1B44, (void *)0x00000001,
    (void *)0x444F4B0E, (void *)0x00000000, (void *)0xC5E480D1, (void *)0x00000001,
    (void *)0x43FF59C7, (void *)0x00000000, (void *)0xC4F660EE, (void *)0x00000001,
    (void *)0x4590EE62, (void *)0x00000000, (void *)0xC510E4E1, (void *)0x00000001,
    (void *)0x4590F0F2, (void *)0x00000000, (void *)0xC5134596, (void *)0x00000001,
    (void *)0x4590E45C, (void *)0x00000000, (void *)0xC5160EB4, (void *)0x00000001,
    (void *)0x445D657F, (void *)0x00000000, (void *)0xC5E6676F, (void *)0x00000001,
    (void *)0x4405BD52, (void *)0x00000000, (void *)0xC4F646A0, (void *)0x00000001,
    (void *)0x43FF4838, (void *)0x00000000, (void *)0xC4EC478D, (void *)0x00000001,
    (void *)0x43FFF2D1, (void *)0x00000000, (void *)0xC4F1C246, (void *)0x00000001,
    (void *)0x4405BF3A, (void *)0x00000000, (void *)0xC4FBBC00, (void *)0x00000001,
    (void *)0x446D7408, (void *)0x00000000, (void *)0xC5E86539, (void *)0x00000001,
    (void *)0x43FF0C5D, (void *)0x00000000, (void *)0xC4FBD150, (void *)0x00000001,
    (void *)0x4405C13B, (void *)0x00000000, (void *)0xC4EC4042, (void *)0x00000001,
    (void *)0x4405BCEF, (void *)0x00000000, (void *)0xC4F1BFF8, (void *)0x00000001,
    (void *)0x4591A883, (void *)0x00000000, (void *)0xC51633CB, (void *)0x00000001,
    (void *)0x447E4083, (void *)0x00000000, (void *)0xC5E9FC33, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80407554[104] = {
    (void *)0x443EE3C7, (void *)0x00000000, (void *)0xC5E03C8B, (void *)0x00000001,
    (void *)0x4438B30E, (void *)0x00000000, (void *)0xC5DE7508, (void *)0x00000001,
    (void *)0x44453316, (void *)0x00000000, (void *)0xC5E1EDEE, (void *)0x00000001,
    (void *)0x444CC75F, (void *)0x00000000, (void *)0xC5E35C8D, (void *)0x00000001,
    (void *)0x44552C02, (void *)0x00000000, (void *)0xC5E49ED3, (void *)0x00000001,
    (void *)0x445D7211, (void *)0x00000000, (void *)0xC5E60D71, (void *)0x00000001,
    (void *)0x451E0EE5, (void *)0x00000000, (void *)0xC5D8E78F, (void *)0x00000001,
    (void *)0x451DA5F0, (void *)0x00000000, (void *)0xC5DAE08B, (void *)0x00000001,
    (void *)0x458EA729, (void *)0x00000000, (void *)0xC4F9211F, (void *)0x00000001,
    (void *)0x451A86AC, (void *)0x00000000, (void *)0xC5DACFC7, (void *)0x00000001,
    (void *)0x458E1BD7, (void *)0x00000000, (void *)0xC501FA29, (void *)0x00000001,
    (void *)0x451ADE56, (void *)0x00000000, (void *)0xC5D8E29C, (void *)0x00000001,
    (void *)0x458EA8AC, (void *)0x00000000, (void *)0xC4E0D493, (void *)0x00000001,
    (void *)0x43CDE439, (void *)0x00000000, (void *)0xC40C84CE, (void *)0x00000001,
    (void *)0x43F2C210, (void *)0x00000000, (void *)0xC3F84E9B, (void *)0x00000001,
    (void *)0x45335B9A, (void *)0x00000000, (void *)0xC59527C3, (void *)0x00000001,
    (void *)0x453512A0, (void *)0x00000000, (void *)0xC5906139, (void *)0x00000001,
    (void *)0x4539BE29, (void *)0x00000000, (void *)0xC587144C, (void *)0x00000001,
    (void *)0x45375E7B, (void *)0x00000000, (void *)0xC58B80D7, (void *)0x00000001,
    (void *)0x453B8E46, (void *)0x00000000, (void *)0xC582DCD9, (void *)0x00000001,
    (void *)0x45409B64, (void *)0x00000000, (void *)0xC574CB91, (void *)0x00000001,
    (void *)0x454382BC, (void *)0x00000000, (void *)0xC56CBD50, (void *)0x00000001,
    (void *)0x453DAD7D, (void *)0x00000000, (void *)0xC57D8C4A, (void *)0x00000001,
    (void *)0x43B2E436, (void *)0x00000000, (void *)0xC41E9817, (void *)0x00000001,
    (void *)0x458EDA48, (void *)0x00000000, (void *)0xC4EEAC10, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804076F4[104] = {
    (void *)0x44028C90, (void *)0x00000000, (void *)0xC5048683, (void *)0x00000001,
    (void *)0x43E75A54, (void *)0x00000000, (void *)0xC502D842, (void *)0x00000001,
    (void *)0x43CFE22D, (void *)0x00000000, (void *)0xC50159C3, (void *)0x00000001,
    (void *)0x43B6D3DA, (void *)0x00000000, (void *)0xC4FDA581, (void *)0x00000001,
    (void *)0x439DFC6A, (void *)0x00000000, (void *)0xC4F93560, (void *)0x00000001,
    (void *)0x4239CD1E, (void *)0x00000000, (void *)0x44C08AB8, (void *)0x00000001,
    (void *)0x42327712, (void *)0x00000000, (void *)0x44C79614, (void *)0x00000001,
    (void *)0x4232042B, (void *)0x00000000, (void *)0x44CEE89C, (void *)0x00000001,
    (void *)0x42308C10, (void *)0x00000000, (void *)0x44D57591, (void *)0x00000001,
    (void *)0x4387B405, (void *)0x00000000, (void *)0xC4F487AE, (void *)0x00000001,
    (void *)0x41678A87, (void *)0x00000000, (void *)0x44C074EE, (void *)0x00000001,
    (void *)0x4160462A, (void *)0x00000000, (void *)0x44C7A029, (void *)0x00000001,
    (void *)0x4174DAC4, (void *)0x00000000, (void *)0x44CF18FE, (void *)0x00000001,
    (void *)0x4167DD4F, (void *)0x00000000, (void *)0x44D5A277, (void *)0x00000001,
    (void *)0x436E6100, (void *)0x00000000, (void *)0xC4EEF9DB, (void *)0x00000001,
    (void *)0x44CA12FA, (void *)0x00000000, (void *)0xC4A5423D, (void *)0x00000001,
    (void *)0x44C97189, (void *)0x00000000, (void *)0xC49D974C, (void *)0x00000001,
    (void *)0x44C99062, (void *)0x00000000, (void *)0xC49541EC, (void *)0x00000001,
    (void *)0x44C960CD, (void *)0x00000000, (void *)0xC48C062D, (void *)0x00000001,
    (void *)0x44C9612F, (void *)0x00000000, (void *)0xC484DAA0, (void *)0x00000001,
    (void *)0x44C5F0D5, (void *)0x00000000, (void *)0xC4A61010, (void *)0x00000001,
    (void *)0x44C59B6D, (void *)0x00000000, (void *)0xC49E013F, (void *)0x00000001,
    (void *)0x44C5EF96, (void *)0x00000000, (void *)0xC4952E4E, (void *)0x00000001,
    (void *)0x44C5FE5E, (void *)0x00000000, (void *)0xC48C8CFE, (void *)0x00000001,
    (void *)0x44C5C408, (void *)0x00000000, (void *)0xC484F537, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80407894[104] = {
    (void *)0x449A7344, (void *)0x00000000, (void *)0xC2502C10, (void *)0x00000001,
    (void *)0x4497362D, (void *)0x00000000, (void *)0x4105F264, (void *)0x00000001,
    (void *)0x44945971, (void *)0x00000000, (void *)0x428EFBA3, (void *)0x00000001,
    (void *)0x449379C3, (void *)0x00000000, (void *)0x430256DC, (void *)0x00000001,
    (void *)0x44958893, (void *)0x00000000, (void *)0xC277685B, (void *)0x00000001,
    (void *)0x42E43C9F, (void *)0x00000000, (void *)0xC56FBD8D, (void *)0x00000001,
    (void *)0x434E7EE0, (void *)0x00000000, (void *)0x4502FBF0, (void *)0x00000001,
    (void *)0x43CD3176, (void *)0x00000000, (void *)0x4509FDD3, (void *)0x00000001,
    (void *)0x448E6DC3, (void *)0x00000000, (void *)0x42F8E618, (void *)0x00000001,
    (void *)0x4492BCF6, (void *)0x00000000, (void *)0xC0FEFAF0, (void *)0x00000001,
    (void *)0x4316AC30, (void *)0x00000000, (void *)0xC572D035, (void *)0x00000001,
    (void *)0x42A91825, (void *)0x00000000, (void *)0xC56B58AC, (void *)0x00000001,
    (void *)0x4396636E, (void *)0x00000000, (void *)0x45072CD9, (void *)0x00000001,
    (void *)0x4401DB28, (void *)0x00000000, (void *)0x450B6ECD, (void *)0x00000001,
    (void *)0x448FB7E7, (void *)0x00000000, (void *)0x425B4361, (void *)0x00000001,
    (void *)0x450233A6, (void *)0x00000000, (void *)0xC57BF19E, (void *)0x00000001,
    (void *)0x450D1F81, (void *)0x00000000, (void *)0xC578CFAA, (void *)0x00000001,
    (void *)0x4348E20C, (void *)0x00000000, (void *)0xC575E371, (void *)0x00000001,
    (void *)0x45282477, (void *)0x00000000, (void *)0xC4F2366F, (void *)0x00000001,
    (void *)0x4527FF64, (void *)0x00000000, (void *)0xC4EA509C, (void *)0x00000001,
    (void *)0x44F914D5, (void *)0x00000000, (void *)0xC57CED89, (void *)0x00000001,
    (void *)0x45083B7D, (void *)0x00000000, (void *)0xC57A8C98, (void *)0x00000001,
    (void *)0x451151FC, (void *)0x00000000, (void *)0xC57741D7, (void *)0x00000001,
    (void *)0x45264E00, (void *)0x00000000, (void *)0xC4F29800, (void *)0x00000001,
    (void *)0x45261E31, (void *)0x00000000, (void *)0xC4EA6B33, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80407A34[104] = {
    (void *)0x444EF59D, (void *)0x00000000, (void *)0x42523E8C, (void *)0x00000001,
    (void *)0x433811BE, (void *)0x00000000, (void *)0x44D2A4DD, (void *)0x00000001,
    (void *)0x43D38368, (void *)0x00000000, (void *)0x44DB0B75, (void *)0x00000001,
    (void *)0x444DCEF3, (void *)0x00000000, (void *)0xC36D46D6, (void *)0x00000001,
    (void *)0x444F76AE, (void *)0x00000000, (void *)0xC208C32A, (void *)0x00000001,
    (void *)0x4127BC21, (void *)0x00000000, (void *)0x446EE434, (void *)0x00000001,
    (void *)0x4134949A, (void *)0x00000000, (void *)0x447B6CEE, (void *)0x00000001,
    (void *)0x41249820, (void *)0x00000000, (void *)0x4484176D, (void *)0x00000001,
    (void *)0x411C05A5, (void *)0x00000000, (void *)0x4489A785, (void *)0x00000001,
    (void *)0x445E5807, (void *)0x00000000, (void *)0xC2B5B62E, (void *)0x00000001,
    (void *)0xC16A5D64, (void *)0x00000000, (void *)0x446F1415, (void *)0x00000001,
    (void *)0xC18353AE, (void *)0x00000000, (void *)0x447BBD81, (void *)0x00000001,
    (void *)0xC18A0270, (void *)0x00000000, (void *)0x44840D17, (void *)0x00000001,
    (void *)0xC18DB3B1, (void *)0x00000000, (void *)0x4489949C, (void *)0x00000001,
    (void *)0x445F2D5B, (void *)0x00000000, (void *)0xC1D373B1, (void *)0x00000001,
    (void *)0x42E0CC64, (void *)0x00000000, (void *)0x44CC607B, (void *)0x00000001,
    (void *)0x43A9D25E, (void *)0x00000000, (void *)0x44DA408B, (void *)0x00000001,
    (void *)0x4411C981, (void *)0x00000000, (void *)0x44D68DF4, (void *)0x00000001,
    (void *)0x444E4ACE, (void *)0x00000000, (void *)0xC2B416F7, (void *)0x00000001,
    (void *)0x445ED4AA, (void *)0x00000000, (void *)0xC322F77A, (void *)0x00000001,
    (void *)0x445FF1EC, (void *)0x00000000, (void *)0x4241532B, (void *)0x00000001,
    (void *)0x43845461, (void *)0x00000000, (void *)0x44D85DB2, (void *)0x00000001,
    (void *)0x43FE8DFA, (void *)0x00000000, (void *)0x44D9C266, (void *)0x00000001,
    (void *)0x444E0874, (void *)0x00000000, (void *)0xC31E180A, (void *)0x00000001,
    (void *)0x445FA2F5, (void *)0x00000000, (void *)0xC3718E6A, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80407BD4[104] = {
    (void *)0xC50613B6, (void *)0x00000000, (void *)0xC4758BF6, (void *)0x00000001,
    (void *)0x44303AEB, (void *)0x00000000, (void *)0x43F0A38C, (void *)0x00000001,
    (void *)0x44233568, (void *)0x00000000, (void *)0x43E0FF7D, (void *)0x00000001,
    (void *)0xC50C121D, (void *)0x00000000, (void *)0xC5046902, (void *)0x00000001,
    (void *)0xC5050971, (void *)0x00000000, (void *)0xC480FA25, (void *)0x00000001,
    (void *)0xC58E719E, (void *)0x00000000, (void *)0xC51E21AE, (void *)0x00000001,
    (void *)0xC591C535, (void *)0x00000000, (void *)0xC5129B06, (void *)0x00000001,
    (void *)0xC5918917, (void *)0x00000000, (void *)0xC508FD50, (void *)0x00000001,
    (void *)0xC5909554, (void *)0x00000000, (void *)0xC5043154, (void *)0x00000001,
    (void *)0xC50B4CE9, (void *)0x00000000, (void *)0xC507B93F, (void *)0x00000001,
    (void *)0xC5902702, (void *)0x00000000, (void *)0xC51AA9E7, (void *)0x00000001,
    (void *)0xC5913CBE, (void *)0x00000000, (void *)0xC51717DB, (void *)0x00000001,
    (void *)0xC591DA7D, (void *)0x00000000, (void *)0xC50D6D91, (void *)0x00000001,
    (void *)0xC58F2F89, (void *)0x00000000, (void *)0xC50060B4, (void *)0x00000001,
    (void *)0xC500C1CB, (void *)0x00000000, (void *)0xC47B3BD7, (void *)0x00000001,
    (void *)0xC5035D71, (void *)0x00000000, (void *)0xC4785AD7, (void *)0x00000001,
    (void *)0x442B49F7, (void *)0x00000000, (void *)0x43D985F4, (void *)0x00000001,
    (void *)0x441D0FFE, (void *)0x00000000, (void *)0x43CCB1FF, (void *)0x00000001,
    (void *)0xC5064F9E, (void *)0x00000000, (void *)0xC5059873, (void *)0x00000001,
    (void *)0xC50F3C19, (void *)0x00000000, (void *)0xC508DDF8, (void *)0x00000001,
    (void *)0xC501D4A4, (void *)0x00000000, (void *)0xC46F02D7, (void *)0x00000001,
    (void *)0x442813C8, (void *)0x00000000, (void *)0x43F6EBCD, (void *)0x00000001,
    (void *)0x442382DB, (void *)0x00000000, (void *)0x43C4815F, (void *)0x00000001,
    (void *)0xC5079014, (void *)0x00000000, (void *)0xC5026DD7, (void *)0x00000001,
    (void *)0xC51051CB, (void *)0x00000000, (void *)0xC505AAB8, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80407D74[104] = {
    (void *)0x447DB48B, (void *)0x00000000, (void *)0x45055487, (void *)0x00000001,
    (void *)0x447BC906, (void *)0x00000000, (void *)0x450131B2, (void *)0x00000001,
    (void *)0x44832214, (void *)0x00000000, (void *)0x43D7B080, (void *)0x00000001,
    (void *)0x44CA307B, (void *)0x00000000, (void *)0xC4AE1E4E, (void *)0x00000001,
    (void *)0xC3A8EEB8, (void *)0x00000000, (void *)0xC5014A21, (void *)0x00000001,
    (void *)0x44899AA8, (void *)0x00000000, (void *)0x45053025, (void *)0x00000001,
    (void *)0x4488E256, (void *)0x00000000, (void *)0x45013DA2, (void *)0x00000001,
    (void *)0x448E1D81, (void *)0x00000000, (void *)0x43D5C100, (void *)0x00000001,
    (void *)0x44CE9981, (void *)0x00000000, (void *)0xC4B2C506, (void *)0x00000001,
    (void *)0xC3940AA0, (void *)0x00000000, (void *)0xC4FAA062, (void *)0x00000001,
    (void *)0x4493B78D, (void *)0x00000000, (void *)0x45054BA6, (void *)0x00000001,
    (void *)0x44932548, (void *)0x00000000, (void *)0x4501D8FE, (void *)0x00000001,
    (void *)0x4497A266, (void *)0x00000000, (void *)0x43D57F5F, (void *)0x00000001,
    (void *)0x44CEC5CB, (void *)0x00000000, (void *)0xC4A8C117, (void *)0x00000001,
    (void *)0xC37F9958, (void *)0x00000000, (void *)0xC4F22C31, (void *)0x00000001,
    (void *)0xC48083C7, (void *)0x00000000, (void *)0x44F0E4E5, (void *)0x00000001,
    (void *)0xC48B1A7F, (void *)0x00000000, (void *)0x44D7F4E5, (void *)0x00000001,
    (void *)0x44A069DB, (void *)0x00000000, (void *)0x43D618EF, (void *)0x00000001,
    (void *)0x44D49842, (void *)0x00000000, (void *)0xC4ABA46A, (void *)0x00000001,
    (void *)0xC34A81CB, (void *)0x00000000, (void *)0xC4EE1F2B, (void *)0x00000001,
    (void *)0xC46C1F4C, (void *)0x00000000, (void *)0x44FA63A6, (void *)0x00000001,
    (void *)0xC4878179, (void *)0x00000000, (void *)0x44E5BE4E, (void *)0x00000001,
    (void *)0x44A850FE, (void *)0x00000000, (void *)0x43D58E11, (void *)0x00000001,
    (void *)0x44C7650E, (void *)0x00000000, (void *)0xC4090F57, (void *)0x00000001,
    (void *)0x44CE2800, (void *)0x00000000, (void *)0xC419DCE0, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80407F14[104] = {
    (void *)0x45279D23, (void *)0x00000000, (void *)0x4525A487, (void *)0x00000001,
    (void *)0x4528F242, (void *)0x00000000, (void *)0x451A21B2, (void *)0x00000001,
    (void *)0x4526610A, (void *)0x00000000, (void *)0xC4B613DF, (void *)0x00000001,
    (void *)0x443060F6, (void *)0x00000000, (void *)0xC4ECDE4E, (void *)0x00000001,
    (void *)0x45280229, (void *)0x00000000, (void *)0x4432577B, (void *)0x00000001,
    (void *)0x451CFD54, (void *)0x00000000, (void *)0x45363025, (void *)0x00000001,
    (void *)0x4524E12B, (void *)0x00000000, (void *)0x452DEDA2, (void *)0x00000001,
    (void *)0x45281EC1, (void *)0x00000000, (void *)0xC49E0FBE, (void *)0x00000001,
    (void *)0x443E7302, (void *)0x00000000, (void *)0xC4F34506, (void *)0x00000001,
    (void *)0xC3940AA0, (void *)0x00000000, (void *)0xC4FAA062, (void *)0x00000001,
    (void *)0x45038BC7, (void *)0x00000000, (void *)0x4537BBA6, (void *)0x00000001,
    (void *)0x450FD2A4, (void *)0x00000000, (void *)0x453898FE, (void *)0x00000001,
    (void *)0x45287133, (void *)0x00000000, (void *)0xC487A029, (void *)0x00000001,
    (void *)0x4522A2E5, (void *)0x00000000, (void *)0xC576708B, (void *)0x00000001,
    (void *)0x4527C66A, (void *)0x00000000, (void *)0x444D679E, (void *)0x00000001,
    (void *)0xC48083C7, (void *)0x00000000, (void *)0x44F0E4E5, (void *)0x00000001,
    (void *)0x43A89604, (void *)0x00000000, (void *)0x450A3A73, (void *)0x00000001,
    (void *)0x452704EE, (void *)0x00000000, (void *)0xC461F388, (void *)0x00000001,
    (void *)0x45268C21, (void *)0x00000000, (void *)0xC5724235, (void *)0x00000001,
    (void *)0xC34A81CB, (void *)0x00000000, (void *)0xC4EE1F2B, (void *)0x00000001,
    (void *)0x43D14168, (void *)0x00000000, (void *)0x450EC1D3, (void *)0x00000001,
    (void *)0xC4878179, (void *)0x00000000, (void *)0x44E5BE4E, (void *)0x00000001,
    (void *)0x4525887F, (void *)0x00000000, (void *)0xC43A38F7, (void *)0x00000001,
    (void *)0x45216287, (void *)0x00000000, (void *)0xC53D23D7, (void *)0x00000001,
    (void *)0x45235400, (void *)0x00000000, (void *)0xC5429737, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804080B4[104] = {
    (void *)0xC574993F, (void *)0x00000000, (void *)0x4525CF8D, (void *)0x00000001,
    (void *)0xC5751025, (void *)0x00000000, (void *)0x45202639, (void *)0x00000001,
    (void *)0xC5BD73C5, (void *)0x00000000, (void *)0xC4A64C73, (void *)0x00000001,
    (void *)0xC5BCDFBE, (void *)0x00000000, (void *)0xC49F6558, (void *)0x00000001,
    (void *)0xC54A690A, (void *)0x00000000, (void *)0xC4F9ADD3, (void *)0x00000001,
    (void *)0xC572105E, (void *)0x00000000, (void *)0x4525F0DD, (void *)0x00000001,
    (void *)0xC5722127, (void *)0x00000000, (void *)0x451FE3BA, (void *)0x00000001,
    (void *)0xC5B9DAC1, (void *)0x00000000, (void *)0xC4A8987B, (void *)0x00000001,
    (void *)0xC5B9C33B, (void *)0x00000000, (void *)0xC4A2F127, (void *)0x00000001,
    (void *)0xC545C117, (void *)0x00000000, (void *)0xC4EBE604, (void *)0x00000001,
    (void *)0xC56A867F, (void *)0x00000000, (void *)0x45BAC6F0, (void *)0x00000001,
    (void *)0xC56CAC7F, (void *)0x00000000, (void *)0x45B70864, (void *)0x00000001,
    (void *)0xC5B699F8, (void *)0x00000000, (void *)0xC4AA160C, (void *)0x00000001,
    (void *)0xC5B6C081, (void *)0x00000000, (void *)0xC4A40862, (void *)0x00000001,
    (void *)0xC543986A, (void *)0x00000000, (void *)0xC4D73EC1, (void *)0x00000001,
    (void *)0xC5774E0C, (void *)0x00000000, (void *)0x45015CBC, (void *)0x00000001,
    (void *)0xC5771F6D, (void *)0x00000000, (void *)0x44F4EAE1, (void *)0x00000001,
    (void *)0xC574D95C, (void *)0x00000000, (void *)0x44B56189, (void *)0x00000001,
    (void *)0xC574F062, (void *)0x00000000, (void *)0x44AAB2D1, (void *)0x00000001,
    (void *)0xC544762D, (void *)0x00000000, (void *)0xC4C455D3, (void *)0x00000001,
    (void *)0xC5748B33, (void *)0x00000000, (void *)0x45016225, (void *)0x00000001,
    (void *)0xC574946A, (void *)0x00000000, (void *)0x44F54BD7, (void *)0x00000001,
    (void *)0xC571C466, (void *)0x00000000, (void *)0x44B5864E, (void *)0x00000001,
    (void *)0xC571D8B0, (void *)0x00000000, (void *)0x44AAA24E, (void *)0x00000001,
    (void *)0xC5495BA2, (void *)0x00000000, (void *)0xC4B15DAA, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80408254[104] = {
    (void *)0xC5B827D3, (void *)0x00000000, (void *)0xC166FEE5, (void *)0x00000001,
    (void *)0xC545E354, (void *)0x00000000, (void *)0x440549C1, (void *)0x00000001,
    (void *)0xC5AE3864, (void *)0x00000000, (void *)0x448A8614, (void *)0x00000001,
    (void *)0xC5AF617D, (void *)0x00000000, (void *)0x449B6010, (void *)0x00000001,
    (void *)0xC5A6E044, (void *)0x00000000, (void *)0x4531F55C, (void *)0x00000001,
    (void *)0xC5B76A48, (void *)0x00000000, (void *)0xC2F574F1, (void *)0x00000001,
    (void *)0xC5B5A01D, (void *)0x00000000, (void *)0x434775F7, (void *)0x00000001,
    (void *)0xC544E64A, (void *)0x00000000, (void *)0x443883E1, (void *)0x00000001,
    (void *)0xC5B0D18F, (void *)0x00000000, (void *)0x449F210E, (void *)0x00000001,
    (void *)0xC5A9E0C1, (void *)0x00000000, (void *)0x4529FEC9, (void *)0x00000001,
    (void *)0xC5B5B9D5, (void *)0x00000000, (void *)0xC3558903, (void *)0x00000001,
    (void *)0xC5B73B04, (void *)0x00000000, (void *)0x42EDF382, (void *)0x00000001,
    (void *)0xC543E1CF, (void *)0x00000000, (void *)0x441CD5B9, (void *)0x00000001,
    (void *)0xC5AF7DFC, (void *)0x00000000, (void *)0x4492CA35, (void *)0x00000001,
    (void *)0xC5AB1860, (void *)0x00000000, (void *)0x45207493, (void *)0x00000001,
    (void *)0xC5473AC1, (void *)0x00000000, (void *)0xC446F7AC, (void *)0x00000001,
    (void *)0xC5480A77, (void *)0x00000000, (void *)0xC42F63F6, (void *)0x00000001,
    (void *)0xC5496EC1, (void *)0x00000000, (void *)0xC41147DE, (void *)0x00000001,
    (void *)0xC5B11FB0, (void *)0x00000000, (void *)0x44914473, (void *)0x00000001,
    (void *)0xC5A9668D, (void *)0x00000000, (void *)0x4516D698, (void *)0x00000001,
    (void *)0xC54A5302, (void *)0x00000000, (void *)0xC4484F9C, (void *)0x00000001,
    (void *)0xC54A56B0, (void *)0x00000000, (void *)0xC42FC415, (void *)0x00000001,
    (void *)0xC54BAC4A, (void *)0x00000000, (void *)0xC41686B5, (void *)0x00000001,
    (void *)0xC5AF025A, (void *)0x00000000, (void *)0x44860646, (void *)0x00000001,
    (void *)0xC5A6BF0C, (void *)0x00000000, (void *)0x450EAFDF, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804083F4[104] = {
    (void *)0xC3252B5E, (void *)0x00000000, (void *)0xC5960814, (void *)0x00000001,
    (void *)0xC2D828CE, (void *)0x00000000, (void *)0xC5936E27, (void *)0x00000001,
    (void *)0xC2A5A27A, (void *)0x00000000, (void *)0xC590D310, (void *)0x00000001,
    (void *)0x43C270BE, (void *)0x00000000, (void *)0xC555F2F2, (void *)0x00000001,
    (void *)0x43AE6646, (void *)0x00000000, (void *)0xC5577D50, (void *)0x00000001,
    (void *)0xC30ED219, (void *)0x00000000, (void *)0xC596B400, (void *)0x00000001,
    (void *)0xC2A2A578, (void *)0x00000000, (void *)0xC593F417, (void *)0x00000001,
    (void *)0xC25AD510, (void *)0x00000000, (void *)0xC59118C1, (void *)0x00000001,
    (void *)0x43CC176D, (void *)0x00000000, (void *)0xC55895E7, (void *)0x00000001,
    (void *)0x43B88F2E, (void *)0x00000000, (void *)0xC559DE73, (void *)0x00000001,
    (void *)0x43D8485C, (void *)0x00000000, (void *)0xC5543775, (void *)0x00000001,
    (void *)0x43E3BC05, (void *)0x00000000, (void *)0xC556C7BE, (void *)0x00000001,
    (void *)0x43888319, (void *)0x00000000, (void *)0x44C5BF5C, (void *)0x00000001,
    (void *)0x440C25BE, (void *)0x00000000, (void *)0x44A8CAF2, (void *)0x00000001,
    (void *)0x43FB801D, (void *)0x00000000, (void *)0x44B1A656, (void *)0x00000001,
    (void *)0x43DB77C8, (void *)0x00000000, (void *)0x44B9AC52, (void *)0x00000001,
    (void *)0x43B7D13B, (void *)0x00000000, (void *)0x44C07F33, (void *)0x00000001,
    (void *)0x445D8861, (void *)0x00000000, (void *)0xC267E04C, (void *)0x00000001,
    (void *)0x4467482B, (void *)0x00000000, (void *)0xC3509DB2, (void *)0x00000001,
    (void *)0x44B76CDD, (void *)0x00000000, (void *)0xC494EA25, (void *)0x00000001,
    (void *)0x44B9C323, (void *)0x00000000, (void *)0xC49C908B, (void *)0x00000001,
    (void *)0x4461BB63, (void *)0x00000000, (void *)0xC3071C15, (void *)0x00000001,
    (void *)0x446D4EF0, (void *)0x00000000, (void *)0xC38303FE, (void *)0x00000001,
    (void *)0x44B2A07B, (void *)0x00000000, (void *)0xC4960F85, (void *)0x00000001,
    (void *)0x44B4CB23, (void *)0x00000000, (void *)0xC49DDC39, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80408594[104] = {
    (void *)0xC3252B5E, (void *)0x00000000, (void *)0xC5960814, (void *)0x00000001,
    (void *)0xC2D828CE, (void *)0x00000000, (void *)0xC5936E27, (void *)0x00000001,
    (void *)0xC2A5A27A, (void *)0x00000000, (void *)0xC590D310, (void *)0x00000001,
    (void *)0x443A47F6, (void *)0x00000000, (void *)0xC54CB4EE, (void *)0x00000001,
    (void *)0x44218EA0, (void *)0x00000000, (void *)0xC54FB7B2, (void *)0x00000001,
    (void *)0xC30ED219, (void *)0x00000000, (void *)0xC596B400, (void *)0x00000001,
    (void *)0xC2A2A578, (void *)0x00000000, (void *)0xC593F417, (void *)0x00000001,
    (void *)0xC25AD510, (void *)0x00000000, (void *)0xC59118C1, (void *)0x00000001,
    (void *)0x43E97F91, (void *)0x00000000, (void *)0xC5553985, (void *)0x00000001,
    (void *)0x43BCC2A0, (void *)0x00000000, (void *)0xC5583042, (void *)0x00000001,
    (void *)0x44537C54, (void *)0x00000000, (void *)0xC549EC8F, (void *)0x00000001,
    (void *)0x440AA72B, (void *)0x00000000, (void *)0xC5527964, (void *)0x00000001,
    (void *)0x43888319, (void *)0x00000000, (void *)0x44C5BF5C, (void *)0x00000001,
    (void *)0x440C25BE, (void *)0x00000000, (void *)0x44A8CAF2, (void *)0x00000001,
    (void *)0x43FB801D, (void *)0x00000000, (void *)0x44B1A656, (void *)0x00000001,
    (void *)0x43DB77C8, (void *)0x00000000, (void *)0x44B9AC52, (void *)0x00000001,
    (void *)0x43B7D13B, (void *)0x00000000, (void *)0x44C07F33, (void *)0x00000001,
    (void *)0x44DDDC19, (void *)0x00000000, (void *)0xC3BA14F7, (void *)0x00000001,
    (void *)0x44EF9AA0, (void *)0x00000000, (void *)0xC40DCC40, (void *)0x00000001,
    (void *)0x45045D5C, (void *)0x00000000, (void *)0xC4551A1E, (void *)0x00000001,
    (void *)0x4532AAE1, (void *)0x00000000, (void *)0xC5145DE3, (void *)0x00000001,
    (void *)0x44E62312, (void *)0x00000000, (void *)0xC3EBD564, (void *)0x00000001,
    (void *)0x44F7B91F, (void *)0x00000000, (void *)0xC425D3A3, (void *)0x00000001,
    (void *)0x4500AB9E, (void *)0x00000000, (void *)0xC43B9422, (void *)0x00000001,
    (void *)0x4531344E, (void *)0x00000000, (void *)0xC516EDEC, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80408734[104] = {
    (void *)0xC464E735, (void *)0x00000000, (void *)0xC59BFFF8, (void *)0x00000001,
    (void *)0xC5018BD7, (void *)0x00000000, (void *)0x423EA9DA, (void *)0x00000001,
    (void *)0xC5832750, (void *)0x00000000, (void *)0xC42616AB, (void *)0x00000001,
    (void *)0xC54935A6, (void *)0x00000000, (void *)0xC5C09F85, (void *)0x00000001,
    (void *)0xC3DF94CA, (void *)0x00000000, (void *)0xC593CA98, (void *)0x00000001,
    (void *)0xC44FAD56, (void *)0x00000000, (void *)0xC59A28DF, (void *)0x00000001,
    (void *)0xC43AB1B5, (void *)0x00000000, (void *)0xC598A01B, (void *)0x00000001,
    (void *)0xC4D04F44, (void *)0x00000000, (void *)0x42340120, (void *)0x00000001,
    (void *)0xC585B650, (void *)0x00000000, (void *)0xC3F68D2C, (void *)0x00000001,
    (void *)0xC54E3C2D, (void *)0x00000000, (void *)0xC5BF0A33, (void *)0x00000001,
    (void *)0xC3229D29, (void *)0x00000000, (void *)0xC2E8A880, (void *)0x00000001,
    (void *)0xC422A7F9, (void *)0x00000000, (void *)0xC597237B, (void *)0x00000001,
    (void *)0xC4B74323, (void *)0x00000000, (void *)0x423F649C, (void *)0x00000001,
    (void *)0xC585E466, (void *)0x00000000, (void *)0xC3C8AB09, (void *)0x00000001,
    (void *)0xC55503CB, (void *)0x00000000, (void *)0xC5BE939E, (void *)0x00000001,
    (void *)0xC3112A93, (void *)0x00000000, (void *)0xC2B0C791, (void *)0x00000001,
    (void *)0xC40B0457, (void *)0x00000000, (void *)0xC59580E5, (void *)0x00000001,
    (void *)0xC49F68DD, (void *)0x00000000, (void *)0x424DBE96, (void *)0x00000001,
    (void *)0xC58579A2, (void *)0x00000000, (void *)0xC393CDFE, (void *)0x00000001,
    (void *)0xC552AF79, (void *)0x00000000, (void *)0xC5BD2187, (void *)0x00000001,
    (void *)0xC54B4106, (void *)0x00000000, (void *)0xC5C21B00, (void *)0x00000001,
    (void *)0xC4EA3723, (void *)0x00000000, (void *)0x423FC546, (void *)0x00000001,
    (void *)0xC584BA6A, (void *)0x00000000, (void *)0xC4132DB9, (void *)0x00000001,
    (void *)0xC54FF9BA, (void *)0x00000000, (void *)0xC5C06BDB, (void *)0x00000001,
    (void *)0xC3B59910, (void *)0x00000000, (void *)0xC5921E6D, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804088D4[104] = {
    (void *)0xC583698F, (void *)0x00000000, (void *)0xC426CF3A, (void *)0x00000001,
    (void *)0xC56F46D1, (void *)0x00000000, (void *)0xC5A13E8F, (void *)0x00000001,
    (void *)0x46125E63, (void *)0x00000000, (void *)0xC5C3E668, (void *)0x00000001,
    (void *)0x45F39733, (void *)0x00000000, (void *)0xC56C702D, (void *)0x00000001,
    (void *)0x4607B61E, (void *)0x00000000, (void *)0xC4BBCBCF, (void *)0x00000001,
    (void *)0xC584C600, (void *)0x00000000, (void *)0xC4122799, (void *)0x00000001,
    (void *)0xC57210E9, (void *)0x00000000, (void *)0xC59F96D5, (void *)0x00000001,
    (void *)0x4613C061, (void *)0x00000000, (void *)0xC5C52F79, (void *)0x00000001,
    (void *)0x45F425DF, (void *)0x00000000, (void *)0xC568706F, (void *)0x00000001,
    (void *)0x4608666F, (void *)0x00000000, (void *)0xC4BC1B1B, (void *)0x00000001,
    (void *)0xC585BAAA, (void *)0x00000000, (void *)0xC3EE03E7, (void *)0x00000001,
    (void *)0xC56FA5CB, (void *)0x00000000, (void *)0xC59F8C64, (void *)0x00000001,
    (void *)0xC571986F, (void *)0x00000000, (void *)0xC5A15D8F, (void *)0x00000001,
    (void *)0x45F54B64, (void *)0x00000000, (void *)0xC56C331B, (void *)0x00000001,
    (void *)0x46079B92, (void *)0x00000000, (void *)0xC4B774EE, (void *)0x00000001,
    (void *)0xC585AA75, (void *)0x00000000, (void *)0xC3BAD495, (void *)0x00000001,
    (void *)0x45E58D12, (void *)0x00000000, (void *)0xC4E4FDFC, (void *)0x00000001,
    (void *)0x45E59F87, (void *)0x00000000, (void *)0xC4EC8A0C, (void *)0x00000001,
    (void *)0x460F3E82, (void *)0x00000000, (void *)0xC5C16702, (void *)0x00000001,
    (void *)0x460848BD, (void *)0x00000000, (void *)0xC4B7ED1F, (void *)0x00000001,
    (void *)0xC584ED5C, (void *)0x00000000, (void *)0xC381B396, (void *)0x00000001,
    (void *)0x45E6F112, (void *)0x00000000, (void *)0xC4E4B20C, (void *)0x00000001,
    (void *)0x45E704CD, (void *)0x00000000, (void *)0xC4EC94C5, (void *)0x00000001,
    (void *)0x4610C42A, (void *)0x00000000, (void *)0xC5C2E91B, (void *)0x00000001,
    (void *)0x45F28EBA, (void *)0x00000000, (void *)0xC5691D1B, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80408A74[104] = {
    (void *)0xC56481BE, (void *)0x00000000, (void *)0xC647BF48, (void *)0x00000001,
    (void *)0xC4DF81BA, (void *)0x00000000, (void *)0xC6205285, (void *)0x00000001,
    (void *)0xC50743F8, (void *)0x00000000, (void *)0xC62AC41F, (void *)0x00000001,
    (void *)0xC49AE558, (void *)0x00000000, (void *)0xC5DF9DE1, (void *)0x00000001,
    (void *)0xC499E0C5, (void *)0x00000000, (void *)0xC5DE00A2, (void *)0x00000001,
    (void *)0xC56925F8, (void *)0x00000000, (void *)0xC649C3CD, (void *)0x00000001,
    (void *)0xC4DDE4A4, (void *)0x00000000, (void *)0xC61FC4D7, (void *)0x00000001,
    (void *)0xC5057B33, (void *)0x00000000, (void *)0xC62A47CD, (void *)0x00000001,
    (void *)0xC49BD53F, (void *)0x00000000, (void *)0xC5E0FDFE, (void *)0x00000001,
    (void *)0xC49CD410, (void *)0x00000000, (void *)0xC5E297D5, (void *)0x00000001,
    (void *)0xC5612056, (void *)0x00000000, (void *)0xC646999A, (void *)0x00000001,
    (void *)0xC54EFED1, (void *)0x00000000, (void *)0xC6869FF1, (void *)0x00000001,
    (void *)0xC54E5F12, (void *)0x00000000, (void *)0xC687051A, (void *)0x00000001,
    (void *)0xC54DB579, (void *)0x00000000, (void *)0xC687698F, (void *)0x00000001,
    (void *)0xC48D727F, (void *)0x00000000, (void *)0xC69E65D2, (void *)0x00000001,
    (void *)0xC5510AA4, (void *)0x00000000, (void *)0xC68586F6, (void *)0x00000001,
    (void *)0xC5503B44, (void *)0x00000000, (void *)0xC685F0A9, (void *)0x00000001,
    (void *)0xC54F9487, (void *)0x00000000, (void *)0xC68651E6, (void *)0x00000001,
    (void *)0xC48D9137, (void *)0x00000000, (void *)0xC69F3EB8, (void *)0x00000001,
    (void *)0xC48D43AE, (void *)0x00000000, (void *)0xC69EDF43, (void *)0x00000001,
    (void *)0xC48D6CDD, (void *)0x00000000, (void *)0xC69DFDA9, (void *)0x00000001,
    (void *)0xC48D3591, (void *)0x00000000, (void *)0xC69FB82E, (void *)0x00000001,
    (void *)0xC566151B, (void *)0x00000000, (void *)0xC6487900, (void *)0x00000001,
    (void *)0xC5679BF0, (void *)0x00000000, (void *)0xC64927EC, (void *)0x00000001,
    (void *)0xC562B419, (void *)0x00000000, (void *)0xC6472FE1, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80408C14[104] = {
    (void *)0xC5740B3B, (void *)0x00000000, (void *)0xC661570A, (void *)0x00000001,
    (void *)0xC56F58EE, (void *)0x00000000, (void *)0xC66252B8, (void *)0x00000001,
    (void *)0x4325DC71, (void *)0x00000000, (void *)0xC61B6E0F, (void *)0x00000001,
    (void *)0x4322CBCD, (void *)0x00000000, (void *)0xC61C41AE, (void *)0x00000001,
    (void *)0x431CCE6A, (void *)0x00000000, (void *)0xC61CEBB8, (void *)0x00000001,
    (void *)0xC571979A, (void *)0x00000000, (void *)0xC661DE33, (void *)0x00000001,
    (void *)0xC56C5979, (void *)0x00000000, (void *)0xC662C052, (void *)0x00000001,
    (void *)0x432A31E5, (void *)0x00000000, (void *)0xC618F257, (void *)0x00000001,
    (void *)0x4329DF76, (void *)0x00000000, (void *)0xC619D705, (void *)0x00000001,
    (void *)0x4328748F, (void *)0x00000000, (void *)0xC61A9734, (void *)0x00000001,
    (void *)0xC5B3E20A, (void *)0x00000000, (void *)0xC629D429, (void *)0x00000001,
    (void *)0xC5B68421, (void *)0x00000000, (void *)0xC62AEA8F, (void *)0x00000001,
    (void *)0xC5BCF53B, (void *)0x00000000, (void *)0xC64A0314, (void *)0x00000001,
    (void *)0xC5B7C28D, (void *)0x00000000, (void *)0xC62B6C71, (void *)0x00000001,
    (void *)0xC5B55D42, (void *)0x00000000, (void *)0xC62A33E1, (void *)0x00000001,
    (void *)0xC50ACBAA, (void *)0x00000000, (void *)0xC5C1583B, (void *)0x00000001,
    (void *)0xC5089FC3, (void *)0x00000000, (void *)0xC5C2C2F8, (void *)0x00000001,
    (void *)0xC50633AA, (void *)0x00000000, (void *)0xC5C427B8, (void *)0x00000001,
    (void *)0xC502CB9E, (void *)0x00000000, (void *)0xC5C67FAA, (void *)0x00000001,
    (void *)0xC5046266, (void *)0x00000000, (void *)0xC5C57968, (void *)0x00000001,
    (void *)0xC5BBA1E5, (void *)0x00000000, (void *)0xC64AC75C, (void *)0x00000001,
    (void *)0xC5BA01D1, (void *)0x00000000, (void *)0xC64B9A85, (void *)0x00000001,
    (void *)0xC5B83900, (void *)0x00000000, (void *)0xC64C799A, (void *)0x00000001,
    (void *)0xC5C06B7B, (void *)0x00000000, (void *)0xC647CC33, (void *)0x00000001,
    (void *)0xC5BEE462, (void *)0x00000000, (void *)0xC648F99A, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80408DB4[104] = {
    (void *)0x458F7ACF, (void *)0x00000000, (void *)0xC5CB1252, (void *)0x00000001,
    (void *)0x459026C9, (void *)0x00000000, (void *)0xC5CD0B14, (void *)0x00000001,
    (void *)0x458F5EFA, (void *)0x00000000, (void *)0xC5CCF2C9, (void *)0x00000001,
    (void *)0x458FB296, (void *)0x00000000, (void *)0xC5CEA564, (void *)0x00000001,
    (void *)0x44465A82, (void *)0x00000000, (void *)0xC5E27D1B, (void *)0x00000001,
    (void *)0x458F17FC, (void *)0x00000000, (void *)0xC5CE996A, (void *)0x00000001,
    (void *)0x4591A842, (void *)0x00000000, (void *)0xC510A404, (void *)0x00000001,
    (void *)0x4591A0F0, (void *)0x00000000, (void *)0xC513A71F, (void *)0x00000001,
    (void *)0x45903E00, (void *)0x00000000, (void *)0xC5CB1B44, (void *)0x00000001,
    (void *)0x444F4B0E, (void *)0x00000000, (void *)0xC5E480D1, (void *)0x00000001,
    (void *)0x43FF59C7, (void *)0x00000000, (void *)0xC4F660EE, (void *)0x00000001,
    (void *)0x4590EE62, (void *)0x00000000, (void *)0xC510E4E1, (void *)0x00000001,
    (void *)0x4590F0F2, (void *)0x00000000, (void *)0xC5134596, (void *)0x00000001,
    (void *)0x4590E45C, (void *)0x00000000, (void *)0xC5160EB4, (void *)0x00000001,
    (void *)0x445D657F, (void *)0x00000000, (void *)0xC5E6676F, (void *)0x00000001,
    (void *)0x4405BD52, (void *)0x00000000, (void *)0xC4F646A0, (void *)0x00000001,
    (void *)0x43FF4838, (void *)0x00000000, (void *)0xC4EC478D, (void *)0x00000001,
    (void *)0x43FFF2D1, (void *)0x00000000, (void *)0xC4F1C246, (void *)0x00000001,
    (void *)0x4405BF3A, (void *)0x00000000, (void *)0xC4FBBC00, (void *)0x00000001,
    (void *)0x446D7408, (void *)0x00000000, (void *)0xC5E86539, (void *)0x00000001,
    (void *)0x43FF0C5D, (void *)0x00000000, (void *)0xC4FBD150, (void *)0x00000001,
    (void *)0x4405C13B, (void *)0x00000000, (void *)0xC4EC4042, (void *)0x00000001,
    (void *)0x4405BCEF, (void *)0x00000000, (void *)0xC4F1BFF8, (void *)0x00000001,
    (void *)0x4591A883, (void *)0x00000000, (void *)0xC51633CB, (void *)0x00000001,
    (void *)0x447E4083, (void *)0x00000000, (void *)0xC5E9FC33, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80408F54[104] = {
    (void *)0x443EE3C7, (void *)0x00000000, (void *)0xC5E03C8B, (void *)0x00000001,
    (void *)0x4438B30E, (void *)0x00000000, (void *)0xC5DE7508, (void *)0x00000001,
    (void *)0x44453316, (void *)0x00000000, (void *)0xC5E1EDEE, (void *)0x00000001,
    (void *)0x444CC75F, (void *)0x00000000, (void *)0xC5E35C8D, (void *)0x00000001,
    (void *)0x44552C02, (void *)0x00000000, (void *)0xC5E49ED3, (void *)0x00000001,
    (void *)0x445D7211, (void *)0x00000000, (void *)0xC5E60D71, (void *)0x00000001,
    (void *)0x451E0EE5, (void *)0x00000000, (void *)0xC5D8E78F, (void *)0x00000001,
    (void *)0x451DA5F0, (void *)0x00000000, (void *)0xC5DAE08B, (void *)0x00000001,
    (void *)0x458EA729, (void *)0x00000000, (void *)0xC4F9211F, (void *)0x00000001,
    (void *)0x451A86AC, (void *)0x00000000, (void *)0xC5DACFC7, (void *)0x00000001,
    (void *)0x458E1BD7, (void *)0x00000000, (void *)0xC501FA29, (void *)0x00000001,
    (void *)0x451ADE56, (void *)0x00000000, (void *)0xC5D8E29C, (void *)0x00000001,
    (void *)0x458EA8AC, (void *)0x00000000, (void *)0xC4E0D493, (void *)0x00000001,
    (void *)0x43CDE439, (void *)0x00000000, (void *)0xC40C84CE, (void *)0x00000001,
    (void *)0x43F2C210, (void *)0x00000000, (void *)0xC3F84E9B, (void *)0x00000001,
    (void *)0x45335B9A, (void *)0x00000000, (void *)0xC59527C3, (void *)0x00000001,
    (void *)0x453512A0, (void *)0x00000000, (void *)0xC5906139, (void *)0x00000001,
    (void *)0x4539BE29, (void *)0x00000000, (void *)0xC587144C, (void *)0x00000001,
    (void *)0x45375E7B, (void *)0x00000000, (void *)0xC58B80D7, (void *)0x00000001,
    (void *)0x453B8E46, (void *)0x00000000, (void *)0xC582DCD9, (void *)0x00000001,
    (void *)0x45409B64, (void *)0x00000000, (void *)0xC574CB91, (void *)0x00000001,
    (void *)0x454382BC, (void *)0x00000000, (void *)0xC56CBD50, (void *)0x00000001,
    (void *)0x453DAD7D, (void *)0x00000000, (void *)0xC57D8C4A, (void *)0x00000001,
    (void *)0x43B2E436, (void *)0x00000000, (void *)0xC41E9817, (void *)0x00000001,
    (void *)0x458EDA48, (void *)0x00000000, (void *)0xC4EEAC10, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804090F4[44] = {
    (void *)0x43CFE22D, (void *)0x00000000, (void *)0xC50159C3, (void *)0x00000001,
    (void *)0x43B6D3DA, (void *)0x00000000, (void *)0xC4FDA581, (void *)0x00000001,
    (void *)0x439DFC6A, (void *)0x00000000, (void *)0xC4F93560, (void *)0x00000001,
    (void *)0x43B159E2, (void *)0x00000000, (void *)0x45086200, (void *)0x00000001,
    (void *)0x43E82296, (void *)0x00000000, (void *)0x450A444E, (void *)0x00000001,
    (void *)0x44104CAF, (void *)0x00000000, (void *)0x450AA6C9, (void *)0x00000001,
    (void *)0x4445DC58, (void *)0x00000000, (void *)0x4506C273, (void *)0x00000001,
    (void *)0x4387B405, (void *)0x00000000, (void *)0xC4F487AE, (void *)0x00000001,
    (void *)0x442DA842, (void *)0x00000000, (void *)0x4509EB3F, (void *)0x00000001,
    (void *)0x436E6100, (void *)0x00000000, (void *)0xC4EEF9DB, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804091A4[44] = {
    (void *)0x449A7344, (void *)0x00000000, (void *)0xC2502C10, (void *)0x00000001,
    (void *)0x4497362D, (void *)0x00000000, (void *)0x4105F264, (void *)0x00000001,
    (void *)0x44945971, (void *)0x00000000, (void *)0x428EFBA3, (void *)0x00000001,
    (void *)0x434E7EE0, (void *)0x00000000, (void *)0x4502FBF0, (void *)0x00000001,
    (void *)0x43CD3176, (void *)0x00000000, (void *)0x4509FDD3, (void *)0x00000001,
    (void *)0x4396636E, (void *)0x00000000, (void *)0x45072CD9, (void *)0x00000001,
    (void *)0x4401DB28, (void *)0x00000000, (void *)0x450B6ECD, (void *)0x00000001,
    (void *)0x450233A6, (void *)0x00000000, (void *)0xC57BF19E, (void *)0x00000001,
    (void *)0x450D1F81, (void *)0x00000000, (void *)0xC578CFAA, (void *)0x00000001,
    (void *)0x45083B7D, (void *)0x00000000, (void *)0xC57A8C98, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80409254[44] = {
    (void *)0x444EF59D, (void *)0x00000000, (void *)0x42523E8C, (void *)0x00000001,
    (void *)0x444F76AE, (void *)0x00000000, (void *)0xC208C32A, (void *)0x00000001,
    (void *)0x4292D312, (void *)0x00000000, (void *)0xC4BCDBAE, (void *)0x00000001,
    (void *)0x42946E1F, (void *)0x00000000, (void *)0xC4B69754, (void *)0x00000001,
    (void *)0x43A91168, (void *)0x00000000, (void *)0x44D88E66, (void *)0x00000001,
    (void *)0x4411088D, (void *)0x00000000, (void *)0x44D68DF4, (void *)0x00000001,
    (void *)0x444E4ACE, (void *)0x00000000, (void *)0xC2B416F7, (void *)0x00000001,
    (void *)0x4383936B, (void *)0x00000000, (void *)0x44D5BA5E, (void *)0x00000001,
    (void *)0x43FB8A2A, (void *)0x00000000, (void *)0x44D931B2, (void *)0x00000001,
    (void *)0x444E0874, (void *)0x00000000, (void *)0xC31E180A, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80409304[44] = {
    (void *)0x44233568, (void *)0x00000000, (void *)0x43E0FF7D, (void *)0x00000001,
    (void *)0xC591C535, (void *)0x00000000, (void *)0xC5129B06, (void *)0x00000001,
    (void *)0xC5918917, (void *)0x00000000, (void *)0xC508FD50, (void *)0x00000001,
    (void *)0xC5909554, (void *)0x00000000, (void *)0xC5043154, (void *)0x00000001,
    (void *)0xC5913CBE, (void *)0x00000000, (void *)0xC51717DB, (void *)0x00000001,
    (void *)0xC591DA7D, (void *)0x00000000, (void *)0xC50D6D91, (void *)0x00000001,
    (void *)0xC5035D71, (void *)0x00000000, (void *)0xC4785AD7, (void *)0x00000001,
    (void *)0x442B49F7, (void *)0x00000000, (void *)0x43D985F4, (void *)0x00000001,
    (void *)0x441D0FFE, (void *)0x00000000, (void *)0x43CCB1FF, (void *)0x00000001,
    (void *)0x442382DB, (void *)0x00000000, (void *)0x43C4815F, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804093B4[44] = {
    (void *)0x44C6307B, (void *)0x00000000, (void *)0xC4B19E4E, (void *)0x00000001,
    (void *)0x4488E256, (void *)0x00000000, (void *)0x45013DA2, (void *)0x00000001,
    (void *)0x44CE3981, (void *)0x00000000, (void *)0xC4AA6506, (void *)0x00000001,
    (void *)0x44932548, (void *)0x00000000, (void *)0x4501D8FE, (void *)0x00000001,
    (void *)0xC37F9958, (void *)0x00000000, (void *)0xC4F22C31, (void *)0x00000001,
    (void *)0xC48083C7, (void *)0x00000000, (void *)0x44F0E4E5, (void *)0x00000001,
    (void *)0xC34A81CB, (void *)0x00000000, (void *)0xC4EE1F2B, (void *)0x00000001,
    (void *)0xC4878179, (void *)0x00000000, (void *)0x44E5BE4E, (void *)0x00000001,
    (void *)0x44C7650E, (void *)0x00000000, (void *)0xC4090F57, (void *)0x00000001,
    (void *)0x44CE2800, (void *)0x00000000, (void *)0xC419DCE0, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80409464[44] = {
    (void *)0x4526610A, (void *)0x00000000, (void *)0xC4B613DF, (void *)0x00000001,
    (void *)0xC3940AA0, (void *)0x00000000, (void *)0xC4FAA062, (void *)0x00000001,
    (void *)0x45287133, (void *)0x00000000, (void *)0xC487A029, (void *)0x00000001,
    (void *)0x43FF70E5, (void *)0x00000000, (void *)0x4513B273, (void *)0x00000001,
    (void *)0x43A89604, (void *)0x00000000, (void *)0x450A3A73, (void *)0x00000001,
    (void *)0xC34A81CB, (void *)0x00000000, (void *)0xC4EE1F2B, (void *)0x00000001,
    (void *)0x43D14168, (void *)0x00000000, (void *)0x450EC1D3, (void *)0x00000001,
    (void *)0x4525887F, (void *)0x00000000, (void *)0xC43A38F7, (void *)0x00000001,
    (void *)0x45216287, (void *)0x00000000, (void *)0xC53D23D7, (void *)0x00000001,
    (void *)0x45235400, (void *)0x00000000, (void *)0xC5429737, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80409514[44] = {
    (void *)0xC574993F, (void *)0x00000000, (void *)0x4525CF8D, (void *)0x00000001,
    (void *)0xC5748B2F, (void *)0x00000000, (void *)0x45205B68, (void *)0x00000001,
    (void *)0xC5BCDFBE, (void *)0x00000000, (void *)0xC49F6558, (void *)0x00000001,
    (void *)0xC5B9C33B, (void *)0x00000000, (void *)0xC4A2F127, (void *)0x00000001,
    (void *)0xC56A867F, (void *)0x00000000, (void *)0x45BAC6F0, (void *)0x00000001,
    (void *)0xC56CAC7F, (void *)0x00000000, (void *)0x45B70864, (void *)0x00000001,
    (void *)0xC5762985, (void *)0x00000000, (void *)0x45015CBC, (void *)0x00000001,
    (void *)0xC575FAE5, (void *)0x00000000, (void *)0x44F4EAE1, (void *)0x00000001,
    (void *)0xC57412A0, (void *)0x00000000, (void *)0x44B56189, (void *)0x00000001,
    (void *)0xC57429A6, (void *)0x00000000, (void *)0x44AAB2D1, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804095C4[44] = {
    (void *)0xC5B827D3, (void *)0x00000000, (void *)0xC166FEE5, (void *)0x00000001,
    (void *)0xC545E354, (void *)0x00000000, (void *)0x440549C1, (void *)0x00000001,
    (void *)0xC5AE3864, (void *)0x00000000, (void *)0x448A8614, (void *)0x00000001,
    (void *)0xC5AF617D, (void *)0x00000000, (void *)0x449B6010, (void *)0x00000001,
    (void *)0xC5A6E044, (void *)0x00000000, (void *)0x4531F55C, (void *)0x00000001,
    (void *)0xC5B76A48, (void *)0x00000000, (void *)0xC2F574F1, (void *)0x00000001,
    (void *)0xC5A9E0C1, (void *)0x00000000, (void *)0x4529FEC9, (void *)0x00000001,
    (void *)0xC5B73B04, (void *)0x00000000, (void *)0x42EDF382, (void *)0x00000001,
    (void *)0xC543E1CF, (void *)0x00000000, (void *)0x441CD5B9, (void *)0x00000001,
    (void *)0xC5AF7DFC, (void *)0x00000000, (void *)0x4492CA35, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80409674[44] = {
    (void *)0xC3252B5E, (void *)0x00000000, (void *)0xC5960814, (void *)0x00000001,
    (void *)0xC2D828CE, (void *)0x00000000, (void *)0xC5936E27, (void *)0x00000001,
    (void *)0xC2A5A27A, (void *)0x00000000, (void *)0xC590D310, (void *)0x00000001,
    (void *)0x43AE6646, (void *)0x00000000, (void *)0xC5577D50, (void *)0x00000001,
    (void *)0x43B88F2E, (void *)0x00000000, (void *)0xC559DE73, (void *)0x00000001,
    (void *)0x43888319, (void *)0x00000000, (void *)0x44C5BF5C, (void *)0x00000001,
    (void *)0x440C25BE, (void *)0x00000000, (void *)0x44A8CAF2, (void *)0x00000001,
    (void *)0x43FB801D, (void *)0x00000000, (void *)0x44B1A656, (void *)0x00000001,
    (void *)0x43DB77C8, (void *)0x00000000, (void *)0x44B9AC52, (void *)0x00000001,
    (void *)0x43B7D13B, (void *)0x00000000, (void *)0x44C07F33, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80409724[44] = {
    (void *)0x443A47F6, (void *)0x00000000, (void *)0xC54CB4EE, (void *)0x00000001,
    (void *)0x44218EA0, (void *)0x00000000, (void *)0xC54FB7B2, (void *)0x00000001,
    (void *)0x44537C54, (void *)0x00000000, (void *)0xC549EC8F, (void *)0x00000001,
    (void *)0x43888319, (void *)0x00000000, (void *)0x44C5BF5C, (void *)0x00000001,
    (void *)0x43FB801D, (void *)0x00000000, (void *)0x44B1A656, (void *)0x00000001,
    (void *)0x43DB77C8, (void *)0x00000000, (void *)0x44B9AC52, (void *)0x00000001,
    (void *)0x43B7D13B, (void *)0x00000000, (void *)0x44C07F33, (void *)0x00000001,
    (void *)0x44F4A22D, (void *)0x00000000, (void *)0xC41ABB23, (void *)0x00000001,
    (void *)0x44E62312, (void *)0x00000000, (void *)0xC3EBD564, (void *)0x00000001,
    (void *)0x4500AB9E, (void *)0x00000000, (void *)0xC43B9422, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804097D4[44] = {
    (void *)0xC464E735, (void *)0x00000000, (void *)0xC59BFFF8, (void *)0x00000001,
    (void *)0xC54935A6, (void *)0x00000000, (void *)0xC5C09F85, (void *)0x00000001,
    (void *)0xC43AB1B5, (void *)0x00000000, (void *)0xC598A01B, (void *)0x00000001,
    (void *)0xC4D04F44, (void *)0x00000000, (void *)0x42340120, (void *)0x00000001,
    (void *)0xC54E3C2D, (void *)0x00000000, (void *)0xC5BF0A33, (void *)0x00000001,
    (void *)0xC4B74323, (void *)0x00000000, (void *)0x423F649C, (void *)0x00000001,
    (void *)0xC40B0457, (void *)0x00000000, (void *)0xC59580E5, (void *)0x00000001,
    (void *)0xC552AF79, (void *)0x00000000, (void *)0xC5BD2187, (void *)0x00000001,
    (void *)0xC4EA3723, (void *)0x00000000, (void *)0x423FC546, (void *)0x00000001,
    (void *)0xC3B59910, (void *)0x00000000, (void *)0xC5921E6D, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80409884[44] = {
    (void *)0xC56F46D1, (void *)0x00000000, (void *)0xC5A13E8F, (void *)0x00000001,
    (void *)0x46125E63, (void *)0x00000000, (void *)0xC5C3E668, (void *)0x00000001,
    (void *)0x4607B61E, (void *)0x00000000, (void *)0xC4BBCBCF, (void *)0x00000001,
    (void *)0x45F34D1F, (void *)0x00000000, (void *)0xC568706F, (void *)0x00000001,
    (void *)0x4608666F, (void *)0x00000000, (void *)0xC4BC1B1B, (void *)0x00000001,
    (void *)0xC571986F, (void *)0x00000000, (void *)0xC5A15D8F, (void *)0x00000001,
    (void *)0x45F472A4, (void *)0x00000000, (void *)0xC56C331B, (void *)0x00000001,
    (void *)0x46079B92, (void *)0x00000000, (void *)0xC4B774EE, (void *)0x00000001,
    (void *)0x460848BD, (void *)0x00000000, (void *)0xC4B7ED1F, (void *)0x00000001,
    (void *)0x4610C42A, (void *)0x00000000, (void *)0xC5C2E91B, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80409934[44] = {
    (void *)0xC5675E93, (void *)0x00000000, (void *)0xC64985A4, (void *)0x00000001,
    (void *)0xC49E50B4, (void *)0x00000000, (void *)0xC5E32FE9, (void *)0x00000001,
    (void *)0xC49C0DDB, (void *)0x00000000, (void *)0xC5E00760, (void *)0x00000001,
    (void *)0xC499A3BE, (void *)0x00000000, (void *)0xC5DCB352, (void *)0x00000001,
    (void *)0xC56447CF, (void *)0x00000000, (void *)0xC649F9C3, (void *)0x00000001,
    (void *)0xC55575F4, (void *)0x00000000, (void *)0xC6849038, (void *)0x00000001,
    (void *)0xC551E242, (void *)0x00000000, (void *)0xC6847CE6, (void *)0x00000001,
    (void *)0xC4942312, (void *)0x00000000, (void *)0xC699ECD7, (void *)0x00000001,
    (void *)0xC4A71D50, (void *)0x00000000, (void *)0xC697EA8F, (void *)0x00000001,
    (void *)0xC4C2ED1F, (void *)0x00000000, (void *)0xC696AA3D, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_804099E4[44] = {
    (void *)0x433631FF, (void *)0x00000000, (void *)0xC617CD08, (void *)0x00000001,
    (void *)0x4335512D, (void *)0x00000000, (void *)0xC619A814, (void *)0x00000001,
    (void *)0x435C2AF5, (void *)0x00000000, (void *)0xC617D672, (void *)0x00000001,
    (void *)0x435F59C1, (void *)0x00000000, (void *)0xC619A8B5, (void *)0x00000001,
    (void *)0xC5C3BA91, (void *)0x00000000, (void *)0xC644AAE1, (void *)0x00000001,
    (void *)0xC5C1744A, (void *)0x00000000, (void *)0xC64625B8, (void *)0x00000001,
    (void *)0xC5BEF568, (void *)0x00000000, (void *)0xC647A452, (void *)0x00000001,
    (void *)0xC5B70510, (void *)0x00000000, (void *)0xC64B5100, (void *)0x00000001,
    (void *)0xC5BCA74A, (void *)0x00000000, (void *)0xC648F1C3, (void *)0x00000001,
    (void *)0xC5BA08AE, (void *)0x00000000, (void *)0xC64A3014, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80409A94[44] = {
    (void *)0x458E0D79, (void *)0x00000000, (void *)0xC5D0336A, (void *)0x00000001,
    (void *)0x458DC0C3, (void *)0x00000000, (void *)0xC5D2D417, (void *)0x00000001,
    (void *)0x443B0924, (void *)0x00000000, (void *)0xC5E02C48, (void *)0x00000001,
    (void *)0x458F8C5A, (void *)0x00000000, (void *)0xC5D04ED5, (void *)0x00000001,
    (void *)0x458F5BBA, (void *)0x00000000, (void *)0xC5D316CB, (void *)0x00000001,
    (void *)0x444F7F96, (void *)0x00000000, (void *)0xC5E43221, (void *)0x00000001,
    (void *)0x441834DA, (void *)0x00000000, (void *)0xC4B39979, (void *)0x00000001,
    (void *)0x4418673A, (void *)0x00000000, (void *)0xC4C4493F, (void *)0x00000001,
    (void *)0x4417E75B, (void *)0x00000000, (void *)0xC4D27968, (void *)0x00000001,
    (void *)0x4470C8B8, (void *)0x00000000, (void *)0xC5E7E26D, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80409B44[44] = {
    (void *)0x452E95A6, (void *)0x00000000, (void *)0xC594B98F, (void *)0x00000001,
    (void *)0x451F8EB0, (void *)0x00000000, (void *)0xC5AF1C19, (void *)0x00000001,
    (void *)0x4530DD5C, (void *)0x00000000, (void *)0xC5951462, (void *)0x00000001,
    (void *)0x452252A8, (void *)0x00000000, (void *)0xC5AF6BD5, (void *)0x00000001,
    (void *)0x454302C9, (void *)0x00000000, (void *)0xC56BF86F, (void *)0x00000001,
    (void *)0x4540440C, (void *)0x00000000, (void *)0xC56A3BE3, (void *)0x00000001,
    (void *)0x437E63C3, (void *)0x00000000, (void *)0xC449E936, (void *)0x00000001,
    (void *)0x458D6560, (void *)0x00000000, (void *)0xC4DEF0FE, (void *)0x00000001,
    (void *)0x439A5574, (void *)0x00000000, (void *)0xC44CC2A0, (void *)0x00000001,
    (void *)0x458EB375, (void *)0x00000000, (void *)0xC4DEF51F, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80409BF4[44] = {
    (void *)0x43CFE22D, (void *)0x00000000, (void *)0xC50159C3, (void *)0x00000001,
    (void *)0x43B6D3DA, (void *)0x00000000, (void *)0xC4FDA581, (void *)0x00000001,
    (void *)0x439DFC6A, (void *)0x00000000, (void *)0xC4F93560, (void *)0x00000001,
    (void *)0x43B159E2, (void *)0x00000000, (void *)0x45086200, (void *)0x00000001,
    (void *)0x43E82296, (void *)0x00000000, (void *)0x450A444E, (void *)0x00000001,
    (void *)0x44104CAF, (void *)0x00000000, (void *)0x450AA6C9, (void *)0x00000001,
    (void *)0x4445DC58, (void *)0x00000000, (void *)0x4506C273, (void *)0x00000001,
    (void *)0x4387B405, (void *)0x00000000, (void *)0xC4F487AE, (void *)0x00000001,
    (void *)0x442DA842, (void *)0x00000000, (void *)0x4509EB3F, (void *)0x00000001,
    (void *)0x436E6100, (void *)0x00000000, (void *)0xC4EEF9DB, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80409CA4[44] = {
    (void *)0x449A7344, (void *)0x00000000, (void *)0xC2502C10, (void *)0x00000001,
    (void *)0x4497362D, (void *)0x00000000, (void *)0x4105F264, (void *)0x00000001,
    (void *)0x44945971, (void *)0x00000000, (void *)0x428EFBA3, (void *)0x00000001,
    (void *)0x434E7EE0, (void *)0x00000000, (void *)0x4502FBF0, (void *)0x00000001,
    (void *)0x43CD3176, (void *)0x00000000, (void *)0x4509FDD3, (void *)0x00000001,
    (void *)0x4396636E, (void *)0x00000000, (void *)0x45072CD9, (void *)0x00000001,
    (void *)0x4401DB28, (void *)0x00000000, (void *)0x450B6ECD, (void *)0x00000001,
    (void *)0x450233A6, (void *)0x00000000, (void *)0xC57BF19E, (void *)0x00000001,
    (void *)0x450D1F81, (void *)0x00000000, (void *)0xC578CFAA, (void *)0x00000001,
    (void *)0x45083B7D, (void *)0x00000000, (void *)0xC57A8C98, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80409D54[44] = {
    (void *)0x444EF59D, (void *)0x00000000, (void *)0x42523E8C, (void *)0x00000001,
    (void *)0x444F76AE, (void *)0x00000000, (void *)0xC208C32A, (void *)0x00000001,
    (void *)0x4292D312, (void *)0x00000000, (void *)0xC4BCDBAE, (void *)0x00000001,
    (void *)0x42946E1F, (void *)0x00000000, (void *)0xC4B69754, (void *)0x00000001,
    (void *)0x43A91168, (void *)0x00000000, (void *)0x44D88E66, (void *)0x00000001,
    (void *)0x4411088D, (void *)0x00000000, (void *)0x44D68DF4, (void *)0x00000001,
    (void *)0x444E4ACE, (void *)0x00000000, (void *)0xC2B416F7, (void *)0x00000001,
    (void *)0x4383936B, (void *)0x00000000, (void *)0x44D5BA5E, (void *)0x00000001,
    (void *)0x43FB8A2A, (void *)0x00000000, (void *)0x44D931B2, (void *)0x00000001,
    (void *)0x444E0874, (void *)0x00000000, (void *)0xC31E180A, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80409E04[44] = {
    (void *)0x44233568, (void *)0x00000000, (void *)0x43E0FF7D, (void *)0x00000001,
    (void *)0xC591C535, (void *)0x00000000, (void *)0xC5129B06, (void *)0x00000001,
    (void *)0xC5918917, (void *)0x00000000, (void *)0xC508FD50, (void *)0x00000001,
    (void *)0xC5909554, (void *)0x00000000, (void *)0xC5043154, (void *)0x00000001,
    (void *)0xC5913CBE, (void *)0x00000000, (void *)0xC51717DB, (void *)0x00000001,
    (void *)0xC591DA7D, (void *)0x00000000, (void *)0xC50D6D91, (void *)0x00000001,
    (void *)0xC5035D71, (void *)0x00000000, (void *)0xC4785AD7, (void *)0x00000001,
    (void *)0x442B49F7, (void *)0x00000000, (void *)0x43D985F4, (void *)0x00000001,
    (void *)0x441D0FFE, (void *)0x00000000, (void *)0x43CCB1FF, (void *)0x00000001,
    (void *)0x442382DB, (void *)0x00000000, (void *)0x43C4815F, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80409EB4[44] = {
    (void *)0x44C6307B, (void *)0x00000000, (void *)0xC4B19E4E, (void *)0x00000001,
    (void *)0x4488E256, (void *)0x00000000, (void *)0x45013DA2, (void *)0x00000001,
    (void *)0x44CE3981, (void *)0x00000000, (void *)0xC4AA6506, (void *)0x00000001,
    (void *)0x44932548, (void *)0x00000000, (void *)0x4501D8FE, (void *)0x00000001,
    (void *)0xC37F9958, (void *)0x00000000, (void *)0xC4F22C31, (void *)0x00000001,
    (void *)0xC48083C7, (void *)0x00000000, (void *)0x44F0E4E5, (void *)0x00000001,
    (void *)0xC34A81CB, (void *)0x00000000, (void *)0xC4EE1F2B, (void *)0x00000001,
    (void *)0xC4878179, (void *)0x00000000, (void *)0x44E5BE4E, (void *)0x00000001,
    (void *)0x44C7650E, (void *)0x00000000, (void *)0xC4090F57, (void *)0x00000001,
    (void *)0x44CE2800, (void *)0x00000000, (void *)0xC419DCE0, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_80409F64[44] = {
    (void *)0x4526610A, (void *)0x00000000, (void *)0xC4B613DF, (void *)0x00000001,
    (void *)0xC3940AA0, (void *)0x00000000, (void *)0xC4FAA062, (void *)0x00000001,
    (void *)0x45287133, (void *)0x00000000, (void *)0xC487A029, (void *)0x00000001,
    (void *)0x43FF70E5, (void *)0x00000000, (void *)0x4513B273, (void *)0x00000001,
    (void *)0x43A89604, (void *)0x00000000, (void *)0x450A3A73, (void *)0x00000001,
    (void *)0xC34A81CB, (void *)0x00000000, (void *)0xC4EE1F2B, (void *)0x00000001,
    (void *)0x43D14168, (void *)0x00000000, (void *)0x450EC1D3, (void *)0x00000001,
    (void *)0x4525887F, (void *)0x00000000, (void *)0xC43A38F7, (void *)0x00000001,
    (void *)0x45216287, (void *)0x00000000, (void *)0xC53D23D7, (void *)0x00000001,
    (void *)0x45235400, (void *)0x00000000, (void *)0xC5429737, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_8040A014[44] = {
    (void *)0xC574993F, (void *)0x00000000, (void *)0x4525CF8D, (void *)0x00000001,
    (void *)0xC5748B2F, (void *)0x00000000, (void *)0x45205B68, (void *)0x00000001,
    (void *)0xC5BCDFBE, (void *)0x00000000, (void *)0xC49F6558, (void *)0x00000001,
    (void *)0xC5B9C33B, (void *)0x00000000, (void *)0xC4A2F127, (void *)0x00000001,
    (void *)0xC56A867F, (void *)0x00000000, (void *)0x45BAC6F0, (void *)0x00000001,
    (void *)0xC56CAC7F, (void *)0x00000000, (void *)0x45B70864, (void *)0x00000001,
    (void *)0xC5762985, (void *)0x00000000, (void *)0x45015CBC, (void *)0x00000001,
    (void *)0xC575FAE5, (void *)0x00000000, (void *)0x44F4EAE1, (void *)0x00000001,
    (void *)0xC57412A0, (void *)0x00000000, (void *)0x44B56189, (void *)0x00000001,
    (void *)0xC57429A6, (void *)0x00000000, (void *)0x44AAB2D1, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_8040A0C4[44] = {
    (void *)0xC5B827D3, (void *)0x00000000, (void *)0xC166FEE5, (void *)0x00000001,
    (void *)0xC545E354, (void *)0x00000000, (void *)0x440549C1, (void *)0x00000001,
    (void *)0xC5AE3864, (void *)0x00000000, (void *)0x448A8614, (void *)0x00000001,
    (void *)0xC5AF617D, (void *)0x00000000, (void *)0x449B6010, (void *)0x00000001,
    (void *)0xC5A6E044, (void *)0x00000000, (void *)0x4531F55C, (void *)0x00000001,
    (void *)0xC5B76A48, (void *)0x00000000, (void *)0xC2F574F1, (void *)0x00000001,
    (void *)0xC5A9E0C1, (void *)0x00000000, (void *)0x4529FEC9, (void *)0x00000001,
    (void *)0xC5B73B04, (void *)0x00000000, (void *)0x42EDF382, (void *)0x00000001,
    (void *)0xC543E1CF, (void *)0x00000000, (void *)0x441CD5B9, (void *)0x00000001,
    (void *)0xC5AF7DFC, (void *)0x00000000, (void *)0x4492CA35, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_8040A174[44] = {
    (void *)0xC3252B5E, (void *)0x00000000, (void *)0xC5960814, (void *)0x00000001,
    (void *)0xC2D828CE, (void *)0x00000000, (void *)0xC5936E27, (void *)0x00000001,
    (void *)0xC2A5A27A, (void *)0x00000000, (void *)0xC590D310, (void *)0x00000001,
    (void *)0x43AE6646, (void *)0x00000000, (void *)0xC5577D50, (void *)0x00000001,
    (void *)0x43B88F2E, (void *)0x00000000, (void *)0xC559DE73, (void *)0x00000001,
    (void *)0x43888319, (void *)0x00000000, (void *)0x44C5BF5C, (void *)0x00000001,
    (void *)0x440C25BE, (void *)0x00000000, (void *)0x44A8CAF2, (void *)0x00000001,
    (void *)0x43FB801D, (void *)0x00000000, (void *)0x44B1A656, (void *)0x00000001,
    (void *)0x43DB77C8, (void *)0x00000000, (void *)0x44B9AC52, (void *)0x00000001,
    (void *)0x43B7D13B, (void *)0x00000000, (void *)0x44C07F33, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_8040A224[44] = {
    (void *)0x443A47F6, (void *)0x00000000, (void *)0xC54CB4EE, (void *)0x00000001,
    (void *)0x44218EA0, (void *)0x00000000, (void *)0xC54FB7B2, (void *)0x00000001,
    (void *)0x44537C54, (void *)0x00000000, (void *)0xC549EC8F, (void *)0x00000001,
    (void *)0x43888319, (void *)0x00000000, (void *)0x44C5BF5C, (void *)0x00000001,
    (void *)0x43FB801D, (void *)0x00000000, (void *)0x44B1A656, (void *)0x00000001,
    (void *)0x43DB77C8, (void *)0x00000000, (void *)0x44B9AC52, (void *)0x00000001,
    (void *)0x43B7D13B, (void *)0x00000000, (void *)0x44C07F33, (void *)0x00000001,
    (void *)0x44F4A22D, (void *)0x00000000, (void *)0xC41ABB23, (void *)0x00000001,
    (void *)0x44E62312, (void *)0x00000000, (void *)0xC3EBD564, (void *)0x00000001,
    (void *)0x4500AB9E, (void *)0x00000000, (void *)0xC43B9422, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_8040A2D4[44] = {
    (void *)0xC464E735, (void *)0x00000000, (void *)0xC59BFFF8, (void *)0x00000001,
    (void *)0xC54935A6, (void *)0x00000000, (void *)0xC5C09F85, (void *)0x00000001,
    (void *)0xC43AB1B5, (void *)0x00000000, (void *)0xC598A01B, (void *)0x00000001,
    (void *)0xC4D04F44, (void *)0x00000000, (void *)0x42340120, (void *)0x00000001,
    (void *)0xC54E3C2D, (void *)0x00000000, (void *)0xC5BF0A33, (void *)0x00000001,
    (void *)0xC4B74323, (void *)0x00000000, (void *)0x423F649C, (void *)0x00000001,
    (void *)0xC40B0457, (void *)0x00000000, (void *)0xC59580E5, (void *)0x00000001,
    (void *)0xC552AF79, (void *)0x00000000, (void *)0xC5BD2187, (void *)0x00000001,
    (void *)0xC4EA3723, (void *)0x00000000, (void *)0x423FC546, (void *)0x00000001,
    (void *)0xC3B59910, (void *)0x00000000, (void *)0xC5921E6D, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_8040A384[44] = {
    (void *)0xC56F46D1, (void *)0x00000000, (void *)0xC5A13E8F, (void *)0x00000001,
    (void *)0x46125E63, (void *)0x00000000, (void *)0xC5C3E668, (void *)0x00000001,
    (void *)0x4607B61E, (void *)0x00000000, (void *)0xC4BBCBCF, (void *)0x00000001,
    (void *)0x45F34D1F, (void *)0x00000000, (void *)0xC568706F, (void *)0x00000001,
    (void *)0x4608666F, (void *)0x00000000, (void *)0xC4BC1B1B, (void *)0x00000001,
    (void *)0xC571986F, (void *)0x00000000, (void *)0xC5A15D8F, (void *)0x00000001,
    (void *)0x45F472A4, (void *)0x00000000, (void *)0xC56C331B, (void *)0x00000001,
    (void *)0x46079B92, (void *)0x00000000, (void *)0xC4B774EE, (void *)0x00000001,
    (void *)0x460848BD, (void *)0x00000000, (void *)0xC4B7ED1F, (void *)0x00000001,
    (void *)0x4610C42A, (void *)0x00000000, (void *)0xC5C2E91B, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_8040A434[44] = {
    (void *)0xC5675E93, (void *)0x00000000, (void *)0xC64985A4, (void *)0x00000001,
    (void *)0xC49E50B4, (void *)0x00000000, (void *)0xC5E32FE9, (void *)0x00000001,
    (void *)0xC49C0DDB, (void *)0x00000000, (void *)0xC5E00760, (void *)0x00000001,
    (void *)0xC499A3BE, (void *)0x00000000, (void *)0xC5DCB352, (void *)0x00000001,
    (void *)0xC56447CF, (void *)0x00000000, (void *)0xC649F9C3, (void *)0x00000001,
    (void *)0xC55575F4, (void *)0x00000000, (void *)0xC6849038, (void *)0x00000001,
    (void *)0xC551E242, (void *)0x00000000, (void *)0xC6847CE6, (void *)0x00000001,
    (void *)0xC4942312, (void *)0x00000000, (void *)0xC699ECD7, (void *)0x00000001,
    (void *)0xC4A71D50, (void *)0x00000000, (void *)0xC697EA8F, (void *)0x00000001,
    (void *)0xC4C2ED1F, (void *)0x00000000, (void *)0xC696AA3D, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_8040A4E4[44] = {
    (void *)0x433631FF, (void *)0x00000000, (void *)0xC617CD08, (void *)0x00000001,
    (void *)0x4335512D, (void *)0x00000000, (void *)0xC619A814, (void *)0x00000001,
    (void *)0x435C2AF5, (void *)0x00000000, (void *)0xC617D672, (void *)0x00000001,
    (void *)0x435F59C1, (void *)0x00000000, (void *)0xC619A8B5, (void *)0x00000001,
    (void *)0xC5C3BA91, (void *)0x00000000, (void *)0xC644AAE1, (void *)0x00000001,
    (void *)0xC5C1744A, (void *)0x00000000, (void *)0xC64625B8, (void *)0x00000001,
    (void *)0xC5BEF568, (void *)0x00000000, (void *)0xC647A452, (void *)0x00000001,
    (void *)0xC5B70510, (void *)0x00000000, (void *)0xC64B5100, (void *)0x00000001,
    (void *)0xC5BCA74A, (void *)0x00000000, (void *)0xC648F1C3, (void *)0x00000001,
    (void *)0xC5BA08AE, (void *)0x00000000, (void *)0xC64A3014, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_8040A594[44] = {
    (void *)0x458E0D79, (void *)0x00000000, (void *)0xC5D0336A, (void *)0x00000001,
    (void *)0x458DC0C3, (void *)0x00000000, (void *)0xC5D2D417, (void *)0x00000001,
    (void *)0x443B0924, (void *)0x00000000, (void *)0xC5E02C48, (void *)0x00000001,
    (void *)0x458F8C5A, (void *)0x00000000, (void *)0xC5D04ED5, (void *)0x00000001,
    (void *)0x458F5BBA, (void *)0x00000000, (void *)0xC5D316CB, (void *)0x00000001,
    (void *)0x444F7F96, (void *)0x00000000, (void *)0xC5E43221, (void *)0x00000001,
    (void *)0x441834DA, (void *)0x00000000, (void *)0xC4B39979, (void *)0x00000001,
    (void *)0x4418673A, (void *)0x00000000, (void *)0xC4C4493F, (void *)0x00000001,
    (void *)0x4417E75B, (void *)0x00000000, (void *)0xC4D27968, (void *)0x00000001,
    (void *)0x4470C8B8, (void *)0x00000000, (void *)0xC5E7E26D, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_8040A644[44] = {
    (void *)0x452E95A6, (void *)0x00000000, (void *)0xC594B98F, (void *)0x00000001,
    (void *)0x451F8EB0, (void *)0x00000000, (void *)0xC5AF1C19, (void *)0x00000001,
    (void *)0x4530DD5C, (void *)0x00000000, (void *)0xC5951462, (void *)0x00000001,
    (void *)0x452252A8, (void *)0x00000000, (void *)0xC5AF6BD5, (void *)0x00000001,
    (void *)0x454302C9, (void *)0x00000000, (void *)0xC56BF86F, (void *)0x00000001,
    (void *)0x4540440C, (void *)0x00000000, (void *)0xC56A3BE3, (void *)0x00000001,
    (void *)0x437E63C3, (void *)0x00000000, (void *)0xC449E936, (void *)0x00000001,
    (void *)0x458D6560, (void *)0x00000000, (void *)0xC4DEF0FE, (void *)0x00000001,
    (void *)0x439A5574, (void *)0x00000000, (void *)0xC44CC2A0, (void *)0x00000001,
    (void *)0x458EB375, (void *)0x00000000, (void *)0xC4DEF51F, (void *)0x00000001,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000002,
};
void *RaceScene_GetPerspFovyForCup_data_8040A6F4[6] = {
    (void *)0xC3285D11, (void *)0xC3285D11, (void *)0x44290A62, (void *)0x42B5FA8B,
    (void *)0xC192E0DF, (void *)0x4429099E,
};
void *RaceScene_GetPerspFovyForCup_data_8040A70C[6] = {
    (void *)0xC3285CFB, (void *)0xC199CDD3, (void *)0x4418CA30, (void *)0x42B5FAF5,
    (void *)0xC19903BF, (void *)0x4418C9A4,
};
void *RaceScene_GetPerspFovyForCup_data_8040A724[24] = {
    (void *)0x41F00000, (void *)0x00000000, (void *)0x449B0000, (void *)0xC1F00000,
    (void *)0x00000000, (void *)0x44A14000, (void *)0x41F00000, (void *)0x00000000,
    (void *)0x44A78000, (void *)0xC1F00000, (void *)0x00000000, (void *)0x44ADC000,
    (void *)0x41F00000, (void *)0x00000000, (void *)0x44B40000, (void *)0xC1F00000,
    (void *)0x00000000, (void *)0x44BA4000, (void *)0x41F00000, (void *)0x00000000,
    (void *)0x44C08000, (void *)0xC1F00000, (void *)0x00000000, (void *)0x44C6C000,
};
void *RaceScene_GetPerspFovyForCup_data_8040A784[24] = {
    (void *)0x41F00000, (void *)0x00000000, (void *)0xC2200000, (void *)0xC1F00000,
    (void *)0x00000000, (void *)0xC2B40000, (void *)0x41F00000, (void *)0x00000000,
    (void *)0xC30C0000, (void *)0xC1F00000, (void *)0x00000000, (void *)0xC33E0000,
    (void *)0x41F00000, (void *)0x00000000, (void *)0xC3700000, (void *)0xC1F00000,
    (void *)0x00000000, (void *)0xC3910000, (void *)0x41F00000, (void *)0x00000000,
    (void *)0xC3AA0000, (void *)0xC1F00000, (void *)0x00000000, (void *)0xC3C30000,
};
void *RaceScene_GetPerspFovyForCup_data_8040A7E4[6] = {
    (void *)0xC37A0000, (void *)0x00000000, (void *)0x43960000, (void *)0x437A0000,
    (void *)0x00000000, (void *)0x43960000,
};
void *RaceScene_GetPerspFovyForCup_data_8040A7FC[6] = {
    (void *)0xC37A0000, (void *)0x00000000, (void *)0x43660000, (void *)0x437A0000,
    (void *)0x00000000, (void *)0x43660000,
};
void *RaceScene_GetPerspFovyForCup_data_8040A814[24] = {
    (void *)0x41D80000, (void *)0x00000000, (void *)0x44188000, (void *)0xC2040000,
    (void *)0x00000000, (void *)0x44250000, (void *)0x41D80000, (void *)0x00000000,
    (void *)0x44318000, (void *)0xC2040000, (void *)0x00000000, (void *)0x443E0000,
    (void *)0x41D80000, (void *)0x00000000, (void *)0x444A8000, (void *)0xC2040000,
    (void *)0x00000000, (void *)0x44570000, (void *)0x41D80000, (void *)0x00000000,
    (void *)0x44638000, (void *)0xC2040000, (void *)0x00000000, (void *)0x44700000,
};
void *RaceScene_GetPerspFovyForCup_data_8040A874[24] = {
    (void *)0xC2040000, (void *)0x00000000, (void *)0xC1F00000, (void *)0x41D80000,
    (void *)0x00000000, (void *)0xC2A00000, (void *)0xC2040000, (void *)0x00000000,
    (void *)0xC3020000, (void *)0x41D80000, (void *)0x00000000, (void *)0xC3340000,
    (void *)0xC2040000, (void *)0x00000000, (void *)0xC3660000, (void *)0x41D80000,
    (void *)0x00000000, (void *)0xC38C0000, (void *)0xC2040000, (void *)0x00000000,
    (void *)0xC3A50000, (void *)0x41D80000, (void *)0x00000000, (void *)0xC3BE0000,
};
void *RaceScene_GetPerspFovyForCup_data_8040A8D4[6] = {
    (void *)0xC3160000, (void *)0x00000000, (void *)0xC3E10000, (void *)0x43160000,
    (void *)0x00000000, (void *)0xC3E10000,
};
void *RaceScene_GetPerspFovyForCup_data_8040A8EC[6] = {
    (void *)0xC3160000, (void *)0x00000000, (void *)0xC3FA0000, (void *)0x43160000,
    (void *)0x00000000, (void *)0xC3FA0000,
};
void *RaceScene_GetPerspFovyForCup_data_8040A904[24] = {
    (void *)0x41F00000, (void *)0x00000000, (void *)0xC38C0000, (void *)0xC1F00000,
    (void *)0x00000000, (void *)0xC3660000, (void *)0x41F00000, (void *)0x00000000,
    (void *)0xC3340000, (void *)0xC1F00000, (void *)0x00000000, (void *)0xC3020000,
    (void *)0x41F00000, (void *)0x00000000, (void *)0xC2A00000, (void *)0xC1F00000,
    (void *)0x00000000, (void *)0xC1F00000, (void *)0x41F00000, (void *)0x00000000,
    (void *)0x42A00000, (void *)0xC1F00000, (void *)0x00000000, (void *)0x43020000,
};
void *RaceScene_GetPerspFovyForCup_data_8040A964[24] = {
    (void *)0x41F00000, (void *)0x00000000, (void *)0xC4278000, (void *)0xC1F00000,
    (void *)0x00000000, (void *)0xC4340000, (void *)0x41F00000, (void *)0x00000000,
    (void *)0xC4408000, (void *)0xC1F00000, (void *)0x00000000, (void *)0xC44D0000,
    (void *)0x41F00000, (void *)0x00000000, (void *)0xC4598000, (void *)0xC1F00000,
    (void *)0x00000000, (void *)0xC4660000, (void *)0x41F00000, (void *)0x00000000,
    (void *)0x4485C000, (void *)0xC1F00000, (void *)0x00000000, (void *)0x448C0000,
};
void *RaceScene_GetPerspFovyForCup_data_8040A9C4[6] = {
    (void *)0xC3960000, (void *)0x00000000, (void *)0xC4B04000, (void *)0x43960000,
    (void *)0x00000000, (void *)0xC4B04000,
};
void *RaceScene_GetPerspFovyForCup_data_8040A9DC[6] = {
    (void *)0xC5814000, (void *)0x00000000, (void *)0xC56F4000, (void *)0xC55F2000,
    (void *)0x00000000, (void *)0xC5739800,
};
void *RaceScene_GetPerspFovyForCup_data_8040A9F4[6] = {
    (void *)0xC3960000, (void *)0x00000000, (void *)0xC4B72000, (void *)0x43960000,
    (void *)0x00000000, (void *)0xC4B72000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AA0C[6] = {
    (void *)0xC580719A, (void *)0x00000000, (void *)0xC567A19A, (void *)0xC55E2800,
    (void *)0x00000000, (void *)0xC56EF800,
};
void *RaceScene_GetPerspFovyForCup_data_8040AA24[24] = {
    (void *)0x41F00000, (void *)0x00000000, (void *)0xC47F0000, (void *)0xC1F00000,
    (void *)0x00000000, (void *)0xC4728000, (void *)0x41F00000, (void *)0x00000000,
    (void *)0xC4660000, (void *)0xC1F00000, (void *)0x00000000, (void *)0xC4598000,
    (void *)0x41F00000, (void *)0x00000000, (void *)0xC44D0000, (void *)0xC1F00000,
    (void *)0x00000000, (void *)0xC4408000, (void *)0xC1F00000, (void *)0x00000000,
    (void *)0xC4408000, (void *)0xC1F00000, (void *)0x00000000, (void *)0xC4408000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AA84[24] = {
    (void *)0xC5730000, (void *)0x00000000, (void *)0xC582B000, (void *)0xC56F4000,
    (void *)0x00000000, (void *)0xC5844000, (void *)0xC5730000, (void *)0x00000000,
    (void *)0xC585D000, (void *)0xC56F4000, (void *)0x00000000, (void *)0xC5876000,
    (void *)0xC5730000, (void *)0x00000000, (void *)0xC588F000, (void *)0xC56F4000,
    (void *)0x00000000, (void *)0xC58A8000, (void *)0xC56F4000, (void *)0x00000000,
    (void *)0xC58A8000, (void *)0x461C4000, (void *)0x00000000, (void *)0x44548000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AAE4[24] = {
    (void *)0xC1F00000, (void *)0x00000000, (void *)0xC4E82000, (void *)0x41F00000,
    (void *)0x00000000, (void *)0xC4EE6000, (void *)0xC1F00000, (void *)0x00000000,
    (void *)0xC4F4A000, (void *)0x41F00000, (void *)0x00000000, (void *)0xC4FAE000,
    (void *)0xC1F00000, (void *)0x00000000, (void *)0xC5009000, (void *)0x41F00000,
    (void *)0x00000000, (void *)0xC503B000, (void *)0x41F00000, (void *)0x00000000,
    (void *)0xC503B000, (void *)0x41F00000, (void *)0x00000000, (void *)0xC503B000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AB44[24] = {
    (void *)0xC5636800, (void *)0x00000000, (void *)0xC5542000, (void *)0xC5658E66,
    (void *)0x00000000, (void *)0xC54FBE66, (void *)0xC560DCCD, (void *)0x00000000,
    (void *)0xC54E699A, (void *)0xC56304CD, (void *)0x00000000, (void *)0xC54A0800,
    (void *)0xC55E519A, (void *)0x00000000, (void *)0xC548B4CD, (void *)0xC560799A,
    (void *)0x00000000, (void *)0xC5445333, (void *)0xC560799A, (void *)0x00000000,
    (void *)0xC5445333, (void *)0x461C4000, (void *)0x00000000, (void *)0x44548000,
};
void *RaceScene_GetPerspFovyForCup_data_8040ABA4[6] = {
    (void *)0xC4A46000, (void *)0x00000000, (void *)0x4466E000, (void *)0xC470C000,
    (void *)0x00000000, (void *)0x4466E000,
};
void *RaceScene_GetPerspFovyForCup_data_8040ABBC[6] = {
    (void *)0xC4A46000, (void *)0x00000000, (void *)0x44568000, (void *)0xC470C000,
    (void *)0x00000000, (void *)0x44568000,
};
void *RaceScene_GetPerspFovyForCup_data_8040ABD4[24] = {
    (void *)0xC489C000, (void *)0x00000000, (void *)0x4484C000, (void *)0xC4934000,
    (void *)0x00000000, (void *)0x448B0000, (void *)0xC489C000, (void *)0x00000000,
    (void *)0x44914000, (void *)0xC4934000, (void *)0x00000000, (void *)0x44978000,
    (void *)0xC489C000, (void *)0x00000000, (void *)0x449DC000, (void *)0xC4934000,
    (void *)0x00000000, (void *)0x44A40000, (void *)0xC489C000, (void *)0x00000000,
    (void *)0x44708000, (void *)0xC4934000, (void *)0x00000000, (void *)0x447D0000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AC34[24] = {
    (void *)0xC4934000, (void *)0x00000000, (void *)0x44340000, (void *)0xC489C000,
    (void *)0x00000000, (void *)0x44278000, (void *)0xC4934000, (void *)0x00000000,
    (void *)0x441B0000, (void *)0xC489C000, (void *)0x00000000, (void *)0x440E8000,
    (void *)0xC4934000, (void *)0x00000000, (void *)0x44020000, (void *)0xC489C000,
    (void *)0x00000000, (void *)0x43EB0000, (void *)0xC4934000, (void *)0x00000000,
    (void *)0x444D0000, (void *)0xC489C000, (void *)0x00000000, (void *)0x44408000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AC94[6] = {
    (void *)0x4596F000, (void *)0x00000000, (void *)0x44849000, (void *)0x45A3FC00,
    (void *)0x00000000, (void *)0x44849000,
};
void *RaceScene_GetPerspFovyForCup_data_8040ACAC[6] = {
    (void *)0x4596F000, (void *)0x00000000, (void *)0x4469E000, (void *)0x45A3FC00,
    (void *)0x00000000, (void *)0x4469E000,
};
void *RaceScene_GetPerspFovyForCup_data_8040ACC4[24] = {
    (void *)0x459D2400, (void *)0x00000000, (void *)0x44A68000, (void *)0x459ABC00,
    (void *)0x00000000, (void *)0x44ACC000, (void *)0x459D2400, (void *)0x00000000,
    (void *)0x44B30000, (void *)0x459ABC00, (void *)0x00000000, (void *)0x44B94000,
    (void *)0x459D2400, (void *)0x00000000, (void *)0x44BF8000, (void *)0x459ABC00,
    (void *)0x00000000, (void *)0x44C5C000, (void *)0x459D2400, (void *)0x00000000,
    (void *)0x44CC0000, (void *)0x459ABC00, (void *)0x00000000, (void *)0x44D24000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AD24[24] = {
    (void *)0x459AB000, (void *)0x00000000, (void *)0x44230000, (void *)0x459D1800,
    (void *)0x00000000, (void *)0x4417C000, (void *)0x459AB000, (void *)0x00000000,
    (void *)0x440B4000, (void *)0x459D1800, (void *)0x00000000, (void *)0x43FD8000,
    (void *)0x459AB000, (void *)0x00000000, (void *)0x43E20000, (void *)0x459D1800,
    (void *)0x00000000, (void *)0x43C90000, (void *)0x459AB000, (void *)0x00000000,
    (void *)0x43B00000, (void *)0x459E0800, (void *)0x00000000, (void *)0x43970000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AD84[6] = {
    (void *)0xC4312000, (void *)0x00000000, (void *)0xC524B000, (void *)0xC38B4000,
    (void *)0x00000000, (void *)0xC524B000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AD9C[6] = {
    (void *)0xC4312000, (void *)0x00000000, (void *)0xC5375000, (void *)0xC38B4000,
    (void *)0x00000000, (void *)0xC5375000,
};
void *RaceScene_GetPerspFovyForCup_data_8040ADB4[24] = {
    (void *)0xC3E7C000, (void *)0x00000000, (void *)0xC5157000, (void *)0xC402E000,
    (void *)0x00000000, (void *)0xC5125000, (void *)0xC3E7C000, (void *)0x00000000,
    (void *)0xC50F3000, (void *)0xC402E000, (void *)0x00000000, (void *)0xC50C1000,
    (void *)0xC3E7C000, (void *)0x00000000, (void *)0xC508F000, (void *)0xC402E000,
    (void *)0x00000000, (void *)0xC505D000, (void *)0xC3E7C000, (void *)0x00000000,
    (void *)0xC502B000, (void *)0xC402E000, (void *)0x00000000, (void *)0xC4FF2000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AE14[24] = {
    (void *)0xC402E000, (void *)0x00000000, (void *)0xC5469000, (void *)0xC3E7C000,
    (void *)0x00000000, (void *)0xC549B000, (void *)0xC402E000, (void *)0x00000000,
    (void *)0xC54CD000, (void *)0xC3E7C000, (void *)0x00000000, (void *)0xC54FF000,
    (void *)0xC402E000, (void *)0x00000000, (void *)0xC5531000, (void *)0xC3E7C000,
    (void *)0x00000000, (void *)0xC5563000, (void *)0xC402E000, (void *)0x00000000,
    (void *)0xC5595000, (void *)0xC3E7C000, (void *)0x00000000, (void *)0xC55C7000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AE74[7] = {
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AE90[7] = {
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AEAC[6] = {
    (void *)0x43E60000, (void *)0x00000000, (void *)0xC58CA000, (void *)0x44520000,
    (void *)0x00000000, (void *)0xC58CA000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AEC4[6] = {
    (void *)0x43E60000, (void *)0x00000000, (void *)0xC58FC000, (void *)0x44520000,
    (void *)0x00000000, (void *)0xC58FC000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AEDC[24] = {
    (void *)0x441D8000, (void *)0x00000000, (void *)0xC57BE000, (void *)0x440E8000,
    (void *)0x00000000, (void *)0xC578C000, (void *)0x441D8000, (void *)0x00000000,
    (void *)0xC575A000, (void *)0x440E8000, (void *)0x00000000, (void *)0xC5728000,
    (void *)0x441D8000, (void *)0x00000000, (void *)0xC56F6000, (void *)0x440E8000,
    (void *)0x00000000, (void *)0xC56C4000, (void *)0x441D8000, (void *)0x00000000,
    (void *)0xC5692000, (void *)0x440E8000, (void *)0x00000000, (void *)0xC56C4000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AF3C[24] = {
    (void *)0x440E8000, (void *)0x00000000, (void *)0xC59E7000, (void *)0x441D8000,
    (void *)0x00000000, (void *)0xC5A00000, (void *)0x440E8000, (void *)0x00000000,
    (void *)0xC5A19000, (void *)0x441D8000, (void *)0x00000000, (void *)0xC5A32000,
    (void *)0x440E8000, (void *)0x00000000, (void *)0xC5A4B000, (void *)0x441D8000,
    (void *)0x00000000, (void *)0xC5A64000, (void *)0x440E8000, (void *)0x00000000,
    (void *)0xC5A7D000, (void *)0x441D8000, (void *)0x00000000, (void *)0xC5A96000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AF9C[7] = {
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AFB8[7] = {
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AFD4[7] = {
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_8040AFF0[7] = {
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_8040B00C[6] = {
    (void *)0xC341B5CC, (void *)0x00000000, (void *)0x43EF8C0F, (void *)0x430BDD3E,
    (void *)0x00000000, (void *)0x43F23AF3,
};
void *RaceScene_GetPerspFovyForCup_data_8040B024[3] = {
    (void *)0x44F9C774, (void *)0xC3430000, (void *)0x43E1930E,
};
void *RaceScene_GetPerspFovyForCup_data_8040B030[6] = {
    (void *)0xC37A0000, (void *)0x00000000, (void *)0x432A0000, (void *)0x437A0000,
    (void *)0x00000000, (void *)0x432A0000,
};
void *RaceScene_GetPerspFovyForCup_data_8040B048[3] = {
    (void *)0x41F00000, (void *)0x00000000, (void *)0x439B0000,
};
void *RaceScene_GetPerspFovyForCup_data_8040B054[6] = {
    (void *)0xC37A0000, (void *)0x00000000, (void *)0xC32A0000, (void *)0x437A0000,
    (void *)0x00000000, (void *)0xC32A0000,
};
void *RaceScene_GetPerspFovyForCup_data_8040B06C[3] = {
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_8040B078[14] = {
    (void *)0x00000000, (void *)0xBF800000, (void *)0xBF800000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031BD4C, lbl_8031BD60, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000,
};
void *RaceScene_GetPerspFovyForCup_data_8040B0B0[6] = {
    (void *)0xC341B5CC, (void *)0x00000000, (void *)0x43EF8C0F, (void *)0x430BDD3E,
    (void *)0x00000000, (void *)0x43F23AF3,
};
void *RaceScene_GetPerspFovyForCup_data_8040B0C8[3] = {
    (void *)0x00000000, (void *)0x00000000, (void *)0x43B90000,
};
void *RaceScene_GetPerspFovyForCup_data_8040B0D4[6] = {
    (void *)0xC3C80000, (void *)0x00000000, (void *)0xC5CB2000, (void *)0xC4480000,
    (void *)0x00000000, (void *)0xC4BB8000,
};
void *RaceScene_GetPerspFovyForCup_data_8040B0EC[6] = {
    (void *)0xC3C80000, (void *)0x00000000, (void *)0xC4BB8000, (void *)0xC4480000,
    (void *)0x00000000, (void *)0xC5CB2000,
};
void *RaceScene_GetPerspFovyForCup_data_8040B104[3] = {
    (void *)0x44160000, (void *)0x00000000, (void *)0xC4960000,
};
void *RaceScene_GetPerspFovyForCup_data_8040B110[3] = {
    (void *)0x44160000, (void *)0x00000000, (void *)0xC5D48000,
};
void *RaceScene_GetPerspFovyForCup_data_8040B11C[63] = {
    (void *)0x00000000, (void *)0xBF800000, (void *)0xBF800000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031BD7C, lbl_8031BD90, (void *)0x00000000,
    (void *)0xBF800000, (void *)0xBF800000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031BDAC, lbl_8031BD90, (void *)0x00000000, (void *)0xBF800000,
    (void *)0xBF800000, (void *)0x00000000, (void *)0x00000000, lbl_8031BDC4,
    lbl_8031BD90, (void *)0x00000000, (void *)0xBF800000, (void *)0xBF800000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031BDD4, lbl_8031BD90,
    (void *)0x00000000, (void *)0xBF800000, (void *)0xBF800000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031BDE4, lbl_8031BD90, (void *)0x00000000,
    (void *)0xBF800000, (void *)0xBF800000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031BDF8, lbl_8031BD90, (void *)0x00000000, (void *)0xBF800000,
    (void *)0xBF800000, (void *)0x00000000, (void *)0x00000000, lbl_8031BE0C,
    lbl_8031BD90, (void *)0x00000000, (void *)0xBF800000, (void *)0xBF800000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031BE1C, lbl_8031BD90,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
};
void *GetCoinSpawnTable_data_8040B218[64] = {
    RaceScene_GetPerspFovyForCup_data_80405CF4, RaceScene_GetPerspFovyForCup_data_804090F4, RaceScene_GetPerspFovyForCup_data_804076F4, RaceScene_GetPerspFovyForCup_data_80409BF4,
    RaceScene_GetPerspFovyForCup_data_80405E94, RaceScene_GetPerspFovyForCup_data_804091A4, RaceScene_GetPerspFovyForCup_data_80407894, RaceScene_GetPerspFovyForCup_data_80409CA4,
    RaceScene_GetPerspFovyForCup_data_80406034, RaceScene_GetPerspFovyForCup_data_80409254, RaceScene_GetPerspFovyForCup_data_80407A34, RaceScene_GetPerspFovyForCup_data_80409D54,
    RaceScene_GetPerspFovyForCup_data_804061D4, RaceScene_GetPerspFovyForCup_data_80409304, RaceScene_GetPerspFovyForCup_data_80407BD4, RaceScene_GetPerspFovyForCup_data_80409E04,
    RaceScene_GetPerspFovyForCup_data_804069F4, RaceScene_GetPerspFovyForCup_data_80409674, RaceScene_GetPerspFovyForCup_data_804083F4, RaceScene_GetPerspFovyForCup_data_8040A174,
    RaceScene_GetPerspFovyForCup_data_80406B94, RaceScene_GetPerspFovyForCup_data_80409724, RaceScene_GetPerspFovyForCup_data_80408594, RaceScene_GetPerspFovyForCup_data_8040A224,
    RaceScene_GetPerspFovyForCup_data_80406D34, RaceScene_GetPerspFovyForCup_data_804097D4, RaceScene_GetPerspFovyForCup_data_80408734, RaceScene_GetPerspFovyForCup_data_8040A2D4,
    RaceScene_GetPerspFovyForCup_data_80406ED4, RaceScene_GetPerspFovyForCup_data_80409884, RaceScene_GetPerspFovyForCup_data_804088D4, RaceScene_GetPerspFovyForCup_data_8040A384,
    RaceScene_GetPerspFovyForCup_data_80406374, RaceScene_GetPerspFovyForCup_data_804093B4, RaceScene_GetPerspFovyForCup_data_80407D74, RaceScene_GetPerspFovyForCup_data_80409EB4,
    RaceScene_GetPerspFovyForCup_data_80406514, RaceScene_GetPerspFovyForCup_data_80409464, RaceScene_GetPerspFovyForCup_data_80407F14, RaceScene_GetPerspFovyForCup_data_80409F64,
    RaceScene_GetPerspFovyForCup_data_804066B4, RaceScene_GetPerspFovyForCup_data_80409514, RaceScene_GetPerspFovyForCup_data_804080B4, RaceScene_GetPerspFovyForCup_data_8040A014,
    RaceScene_GetPerspFovyForCup_data_80406854, RaceScene_GetPerspFovyForCup_data_804095C4, RaceScene_GetPerspFovyForCup_data_80408254, RaceScene_GetPerspFovyForCup_data_8040A0C4,
    RaceScene_GetPerspFovyForCup_data_80407074, RaceScene_GetPerspFovyForCup_data_80409934, RaceScene_GetPerspFovyForCup_data_80408A74, RaceScene_GetPerspFovyForCup_data_8040A434,
    RaceScene_GetPerspFovyForCup_data_80407214, RaceScene_GetPerspFovyForCup_data_804099E4, RaceScene_GetPerspFovyForCup_data_80408C14, RaceScene_GetPerspFovyForCup_data_8040A4E4,
    RaceScene_GetPerspFovyForCup_data_804073B4, RaceScene_GetPerspFovyForCup_data_80409A94, RaceScene_GetPerspFovyForCup_data_80408DB4, RaceScene_GetPerspFovyForCup_data_8040A594,
    RaceScene_GetPerspFovyForCup_data_80407554, RaceScene_GetPerspFovyForCup_data_80409B44, RaceScene_GetPerspFovyForCup_data_80408F54, RaceScene_GetPerspFovyForCup_data_8040A644,
};
void *DebugOverlay_GetCupLabel_data_8040B318[17] = {
    lbl_806D3600, lbl_8031BE30, lbl_8031BE3C, lbl_8031BE48,
    lbl_806D3608, lbl_8031BE54, lbl_806D3610, lbl_806D3618,
    lbl_8031BE60, lbl_8031BE6C, lbl_8031BE84, lbl_8031BE98,
    lbl_8031BEAC, lbl_8031BEC0, lbl_8031BED4, lbl_8031BEE8,
    lbl_8031BEFC,
};
void *RaceScene_GetPerspFovyForCup_data_8040B35C[6] = {
    (void *)0xC30E0000, (void *)0x00000000, (void *)0x44628000, (void *)0x42A00000,
    (void *)0x00000000, (void *)0x44628000,
};
void *RaceScene_GetPerspFovyForCup_data_8040B374[24] = {
    (void *)0x41F00000, (void *)0x00000000, (void *)0x44848000, (void *)0xC1F00000,
    (void *)0x00000000, (void *)0x448AC000, (void *)0x41F00000, (void *)0x00000000,
    (void *)0x44910000, (void *)0xC1F00000, (void *)0x00000000, (void *)0x44974000,
    (void *)0x41F00000, (void *)0x00000000, (void *)0x449D8000, (void *)0xC1F00000,
    (void *)0x00000000, (void *)0x44A3C000, (void *)0x41F00000, (void *)0x00000000,
    (void *)0x44AA0000, (void *)0xC1F00000, (void *)0x00000000, (void *)0x44B04000,
};
void *RaceScene_GetPerspFovyForCup_data_8040B3D4[6] = {
    (void *)0xC30E0000, (void *)0x00000000, (void *)0x44628000, (void *)0x42A00000,
    (void *)0x00000000, (void *)0x44628000,
};
void *RaceScene_GetPerspFovyForCup_data_8040B3EC[24] = {
    (void *)0x41F00000, (void *)0x00000000, (void *)0x44848000, (void *)0xC1F00000,
    (void *)0x00000000, (void *)0x448AC000, (void *)0x41F00000, (void *)0x00000000,
    (void *)0x44910000, (void *)0xC1F00000, (void *)0x00000000, (void *)0x44974000,
    (void *)0x41F00000, (void *)0x00000000, (void *)0x449D8000, (void *)0xC1F00000,
    (void *)0x00000000, (void *)0x44A3C000, (void *)0x41F00000, (void *)0x00000000,
    (void *)0x44AA0000, (void *)0xC1F00000, (void *)0x00000000, (void *)0x44B04000,
};
void *RaceScene_GetPerspFovyForCup_data_8040B44C[18] = {
    lbl_8031BF14, lbl_8031BF30, lbl_8031BF4C, lbl_8031BF68,
    lbl_8031BF88, lbl_8031BFA8, lbl_8031BFCC, lbl_8031BF68,
    lbl_8031BF88, lbl_8031BFEC, lbl_8031C004, lbl_8031C01C,
    lbl_8031C03C, (void *)0x00000000, lbl_8031C058, lbl_8031C078,
    lbl_8031C098, lbl_8031C0B8,
};
void *RaceScene_GetPerspFovyForCup_data_8040B494[18] = {
    lbl_8031BF14, lbl_8031BF30, lbl_8031BF4C, lbl_8031BF68,
    lbl_8031BF88, lbl_8031BFA8, lbl_8031BFCC, lbl_8031BF68,
    lbl_8031BF88, lbl_8031BFEC, lbl_8031C004, lbl_8031C01C,
    lbl_8031C03C, (void *)0x00000000, lbl_8031C058, lbl_8031C078,
    lbl_8031C098, lbl_8031C0B8,
};
void *RaceScene_GetPerspFovyForCup_data_8040B4DC[18] = {
    lbl_8031C0D8, lbl_8031C0F4, lbl_8031C110, lbl_8031C12C,
    lbl_8031C14C, lbl_8031C168, lbl_8031C188, lbl_8031C12C,
    lbl_8031C14C, lbl_8031C1A8, lbl_8031C1C0, lbl_8031C1D8,
    lbl_8031C1F4, (void *)0x00000000, lbl_8031C210, lbl_8031C230,
    lbl_8031C24C, lbl_8031C26C,
};
void *RaceScene_GetPerspFovyForCup_data_8040B524[18] = {
    lbl_8031C28C, lbl_8031C2A8, lbl_8031C2C4, lbl_8031C2E0,
    lbl_8031C2FC, lbl_8031C318, lbl_8031C338, lbl_8031C2E0,
    lbl_8031C2FC, lbl_8031C358, lbl_8031C36C, lbl_8031C384,
    lbl_8031C3A0, (void *)0x00000000, lbl_8031C3BC, lbl_8031C3D8,
    lbl_8031C3F4, lbl_8031C414,
};
void *RaceScene_GetPerspFovyForCup_data_8040B56C[18] = {
    lbl_8031C430, lbl_8031C44C, lbl_8031C468, lbl_8031C480,
    lbl_8031C49C, lbl_8031C4B8, lbl_8031C4D8, lbl_8031C480,
    lbl_8031C49C, lbl_8031C4F8, lbl_8031C50C, lbl_8031C520,
    lbl_8031C53C, (void *)0x00000000, lbl_8031C558, lbl_8031C574,
    lbl_8031C590, lbl_8031C5AC,
};
void *RaceScene_GetPerspFovyForCup_data_8040B5B4[18] = {
    lbl_8031C5C8, lbl_8031C5E4, lbl_8031C600, lbl_8031C61C,
    lbl_8031C63C, lbl_8031C658, lbl_8031C678, lbl_8031C61C,
    lbl_8031C63C, lbl_8031C698, lbl_8031C6B0, lbl_8031C6C8,
    lbl_8031C6E4, lbl_8031C700, lbl_8031C718, lbl_8031C738,
    lbl_8031C754, lbl_8031C774,
};
void *RaceScene_GetPerspFovyForCup_data_8040B5FC[18] = {
    lbl_8031C794, lbl_8031C7B0, lbl_8031C7CC, lbl_8031C7E4,
    lbl_8031C800, lbl_8031C81C, lbl_8031C83C, lbl_8031C7E4,
    lbl_8031C800, lbl_8031C85C, lbl_8031C870, lbl_8031C884,
    lbl_8031C8A0, (void *)0x00000000, lbl_8031C8BC, lbl_8031C8D8,
    lbl_8031C8F4, lbl_8031C910,
};
void *RaceScene_GetPerspFovyForCup_data_8040B644[18] = {
    lbl_8031C92C, lbl_8031C948, lbl_8031C964, lbl_8031C97C,
    lbl_8031C998, lbl_8031C9B4, lbl_8031C9D4, lbl_8031C97C,
    lbl_8031C998, lbl_8031C9F4, lbl_8031CA08, lbl_8031CA1C,
    lbl_8031CA38, (void *)0x00000000, lbl_8031CA54, lbl_8031CA70,
    lbl_8031CA8C, lbl_8031CAA8,
};
void *RaceScene_GetPerspFovyForCup_data_8040B68C[18] = {
    lbl_8031CAC4, lbl_8031CAE0, lbl_8031CAFC, lbl_8031CB18,
    lbl_8031CB38, lbl_8031CB58, lbl_8031CB7C, lbl_8031CB18,
    lbl_8031CB38, lbl_8031CB9C, lbl_8031CBB4, lbl_8031CBCC,
    lbl_8031CBEC, (void *)0x00000000, lbl_8031CC08, lbl_8031CC28,
    lbl_8031CC48, lbl_8031CC68,
};
void *Block2[18] = {
    lbl_8031BF14, lbl_8031BF30, lbl_8031BF4C, lbl_8031BF68,
    lbl_8031BF88, lbl_8031BFA8, lbl_8031BFCC, lbl_8031BF68,
    lbl_8031BF88, lbl_8031BFEC, lbl_8031C004, lbl_8031C01C,
    lbl_8031C03C, (void *)0x00000000, lbl_8031C058, lbl_8031C078,
    lbl_8031C098, lbl_8031C0B8,
};
void *RaceScene_GetPerspFovyForCup_data_8040B71C[18] = {
    lbl_8031C0D8, lbl_8031C0F4, lbl_8031C110, lbl_8031C12C,
    lbl_8031C14C, lbl_8031C168, lbl_8031C188, lbl_8031C12C,
    lbl_8031C14C, lbl_8031C1A8, lbl_8031C1C0, lbl_8031C1D8,
    lbl_8031C1F4, (void *)0x00000000, lbl_8031C210, lbl_8031C230,
    lbl_8031C24C, lbl_8031C26C,
};
void *RaceScene_GetPerspFovyForCup_data_8040B764[18] = {
    lbl_8031C430, lbl_8031C44C, lbl_8031C468, lbl_8031C480,
    lbl_8031C49C, lbl_8031C4B8, lbl_8031C4D8, lbl_8031C480,
    lbl_8031C49C, lbl_8031C4F8, lbl_8031C50C, lbl_8031C520,
    lbl_8031C53C, (void *)0x00000000, lbl_8031C558, lbl_8031C574,
    lbl_8031C590, lbl_8031C5AC,
};
void *RaceScene_GetPerspFovyForCup_data_8040B7AC[88] = {
    lbl_8031C5C8, lbl_8031C5E4, lbl_8031C600, lbl_8031C61C,
    lbl_8031C63C, lbl_8031C658, lbl_8031C678, lbl_8031C61C,
    lbl_8031C63C, lbl_8031C698, lbl_8031C6B0, lbl_8031C6C8,
    lbl_8031C6E4, lbl_8031C700, lbl_8031C718, lbl_8031C738,
    lbl_8031C754, lbl_8031C774, (void *)0x00000000, (void *)0xBF800000,
    (void *)0xBF800000, (void *)0x00000000, (void *)0x00000000, lbl_8031CC88,
    lbl_8031CC98, (void *)0x00000000, (void *)0xBF800000, (void *)0xBF800000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031CCB4, lbl_8031CCC4,
    (void *)0x00000000, (void *)0x42C80000, (void *)0xC4160000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031CCE0, lbl_8031CCF0, (void *)0x00000000,
    (void *)0x42C80000, (void *)0xC3C80000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031CD0C, lbl_8031CD20, (void *)0x00000000, (void *)0x42C80000,
    (void *)0xC3C80000, (void *)0x00000000, (void *)0x00000000, lbl_8031A08C,
    lbl_8031CD44, (void *)0x00000000, (void *)0x42C80000, (void *)0xC3C80000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031CD64, lbl_8031CD74,
    (void *)0x00000000, (void *)0xBF800000, (void *)0xBF800000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031CD94, lbl_8031CDAC, (void *)0x00000000,
    (void *)0x43480000, (void *)0xC4960000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031CDC8, lbl_8031CDE4, (void *)0x01000000, (void *)0x42C80000,
    (void *)0xC4960000, (void *)0x00000000, (void *)0x00000000, lbl_8031CE04,
    lbl_8031CE1C, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
};
void *SetCourseParams_data_8040B90C[2346] = {
    lbl_8031CE38, RaceScene_GetPerspFovyForCup_data_8040B44C, RaceScene_GetPerspFovyForCup_data_8040B44C, RaceScene_GetPerspFovyForCup_data_8040B44C,
    RaceScene_GetPerspFovyForCup_data_8040B44C, lbl_8031CE48, lbl_8031CE48, lbl_8031CE48,
    lbl_8031CE48, RaceScene_GetPerspFovyForCup_data_8040B35C, RaceScene_GetPerspFovyForCup_data_8040B374, (void *)0x43340000,
    (void *)0x00000000, lbl_8031CE48, lbl_8031CE48, lbl_8031CE48,
    lbl_8031CE48, lbl_8031CE48, lbl_8031CE48, lbl_8031CE48,
    lbl_8031CE48, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_806D3620, lbl_806D3620, lbl_806D3620,
    lbl_806D3620, RaceScene_GetPerspFovyForCup_data_8040B3D4, RaceScene_GetPerspFovyForCup_data_8040B3EC, (void *)0x00000000,
    (void *)0x00000000, lbl_8031CE48, lbl_8031CE48, lbl_8031CE48,
    lbl_8031CE48, lbl_8031CE48, lbl_8031CE48, lbl_8031CE48,
    lbl_8031CE48, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_806D3620, lbl_806D3620, lbl_806D3620,
    lbl_806D3620, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031CE60, RaceScene_GetPerspFovyForCup_data_8040B44C, RaceScene_GetPerspFovyForCup_data_8040B44C,
    RaceScene_GetPerspFovyForCup_data_8040B44C, RaceScene_GetPerspFovyForCup_data_8040B44C, lbl_8031CE48, lbl_8031CE48,
    lbl_8031CE48, lbl_8031CE48, RaceScene_GetPerspFovyForCup_data_8040B35C, RaceScene_GetPerspFovyForCup_data_8040B374,
    (void *)0x43340000, lbl_8031CE70, lbl_8031CE48, lbl_8031CE48,
    lbl_8031CE48, lbl_8031CE48, lbl_8031CE48, lbl_8031CE48,
    lbl_8031CE48, lbl_8031CE48, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_806D3620, lbl_806D3620,
    lbl_806D3620, lbl_806D3620, RaceScene_GetPerspFovyForCup_data_8040B3D4, RaceScene_GetPerspFovyForCup_data_8040B3EC,
    (void *)0x00000000, lbl_8031CE8C, lbl_8031CE48, lbl_8031CE48,
    lbl_8031CE48, lbl_8031CE48, lbl_8031CE48, lbl_8031CE48,
    lbl_8031CE48, lbl_8031CE48, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_806D3620, lbl_806D3620,
    lbl_806D3620, lbl_806D3620, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031CEA8, RaceScene_GetPerspFovyForCup_data_8040B494,
    RaceScene_GetPerspFovyForCup_data_8040B494, RaceScene_GetPerspFovyForCup_data_8040B494, RaceScene_GetPerspFovyForCup_data_8040B494, lbl_8031CEBC,
    lbl_8031CECC, lbl_8031CEDC, lbl_8031CEBC, RaceScene_GetPerspFovyForCup_data_8040A6F4,
    RaceScene_GetPerspFovyForCup_data_8040A724, (void *)0x43340000, lbl_8031CEEC, lbl_8031CF08,
    lbl_8031CF20, lbl_8031CF38, lbl_8031CF38, lbl_8031CF08,
    lbl_8031CF20, lbl_8031CF38, lbl_8031CF38, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_80401F74,
    RaceScene_GetPerspFovyForCup_data_80401F74, RaceScene_GetPerspFovyForCup_data_80401F74, RaceScene_GetPerspFovyForCup_data_80401F74, RaceScene_GetPerspFovyForCup_data_80405CF4,
    RaceScene_GetPerspFovyForCup_data_80405CF4, RaceScene_GetPerspFovyForCup_data_80405CF4, RaceScene_GetPerspFovyForCup_data_80405CF4, lbl_8031CF50,
    lbl_8031CF50, lbl_8031CF50, lbl_8031CF50, RaceScene_GetPerspFovyForCup_data_8040A70C,
    RaceScene_GetPerspFovyForCup_data_8040A784, (void *)0x00000000, lbl_8031CF68, lbl_8031CF08,
    lbl_8031CF20, lbl_8031CF38, lbl_8031CF38, lbl_8031CF08,
    lbl_8031CF20, lbl_8031CF38, lbl_8031CF38, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_80403D94,
    RaceScene_GetPerspFovyForCup_data_80403D94, RaceScene_GetPerspFovyForCup_data_80403D94, RaceScene_GetPerspFovyForCup_data_80403D94, RaceScene_GetPerspFovyForCup_data_804076F4,
    RaceScene_GetPerspFovyForCup_data_804076F4, RaceScene_GetPerspFovyForCup_data_804076F4, RaceScene_GetPerspFovyForCup_data_804076F4, lbl_8031CF50,
    lbl_8031CF50, lbl_8031CF50, lbl_8031CF50, lbl_8031CF84,
    lbl_8031CF9C, lbl_8031CFB4, lbl_8031CF84, lbl_8031CFCC,
    RaceScene_GetPerspFovyForCup_data_8040B494, RaceScene_GetPerspFovyForCup_data_8040B494, RaceScene_GetPerspFovyForCup_data_8040B494, RaceScene_GetPerspFovyForCup_data_8040B494,
    lbl_8031CFE0, lbl_8031CFF0, lbl_8031D000, lbl_8031D010,
    RaceScene_GetPerspFovyForCup_data_8040A6F4, RaceScene_GetPerspFovyForCup_data_8040A724, (void *)0x43340000, lbl_8031CE70,
    lbl_8031D028, lbl_8031D040, lbl_8031D058, lbl_8031D058,
    lbl_8031D028, lbl_8031D040, lbl_8031D058, lbl_8031D058,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    RaceScene_GetPerspFovyForCup_data_804020B4, RaceScene_GetPerspFovyForCup_data_804020B4, RaceScene_GetPerspFovyForCup_data_804020B4, RaceScene_GetPerspFovyForCup_data_804020B4,
    RaceScene_GetPerspFovyForCup_data_80405E94, RaceScene_GetPerspFovyForCup_data_80405E94, RaceScene_GetPerspFovyForCup_data_80405E94, RaceScene_GetPerspFovyForCup_data_80405E94,
    lbl_8031D070, lbl_8031D070, lbl_8031D070, lbl_8031D070,
    RaceScene_GetPerspFovyForCup_data_8040A70C, RaceScene_GetPerspFovyForCup_data_8040A784, (void *)0x00000000, lbl_8031CE8C,
    lbl_8031D028, lbl_8031D040, lbl_8031D058, lbl_8031D058,
    lbl_8031D028, lbl_8031D040, lbl_8031D058, lbl_8031D058,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    RaceScene_GetPerspFovyForCup_data_80403ED4, RaceScene_GetPerspFovyForCup_data_80403ED4, RaceScene_GetPerspFovyForCup_data_80403ED4, RaceScene_GetPerspFovyForCup_data_80403ED4,
    RaceScene_GetPerspFovyForCup_data_80407894, RaceScene_GetPerspFovyForCup_data_80407894, RaceScene_GetPerspFovyForCup_data_80407894, RaceScene_GetPerspFovyForCup_data_80407894,
    lbl_8031D070, lbl_8031D070, lbl_8031D070, lbl_8031D070,
    lbl_8031D084, lbl_8031D09C, lbl_8031D0B4, lbl_8031D084,
    lbl_8031D0CC, RaceScene_GetPerspFovyForCup_data_8040B4DC, RaceScene_GetPerspFovyForCup_data_8040B4DC, RaceScene_GetPerspFovyForCup_data_8040B4DC,
    RaceScene_GetPerspFovyForCup_data_8040B4DC, lbl_8031D0E0, lbl_8031D0F0, lbl_8031D100,
    lbl_8031D110, RaceScene_GetPerspFovyForCup_data_8040A7E4, RaceScene_GetPerspFovyForCup_data_8040A814, (void *)0x43340000,
    lbl_8031D128, lbl_8031D144, lbl_8031D15C, lbl_8031D110,
    lbl_8031D110, lbl_8031D144, lbl_8031D15C, lbl_8031D110,
    lbl_8031D110, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_804021F4, RaceScene_GetPerspFovyForCup_data_804021F4, RaceScene_GetPerspFovyForCup_data_804021F4,
    RaceScene_GetPerspFovyForCup_data_804021F4, RaceScene_GetPerspFovyForCup_data_80406034, RaceScene_GetPerspFovyForCup_data_80406034, RaceScene_GetPerspFovyForCup_data_80406034,
    RaceScene_GetPerspFovyForCup_data_80406034, lbl_8031D174, lbl_8031D174, lbl_8031D174,
    lbl_8031D174, RaceScene_GetPerspFovyForCup_data_8040A7FC, RaceScene_GetPerspFovyForCup_data_8040A874, (void *)0x00000000,
    lbl_8031D188, lbl_8031D144, lbl_8031D15C, lbl_8031D110,
    lbl_8031D110, lbl_8031D144, lbl_8031D15C, lbl_8031D110,
    lbl_8031D110, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_804040A4, RaceScene_GetPerspFovyForCup_data_804040A4, RaceScene_GetPerspFovyForCup_data_804040A4,
    RaceScene_GetPerspFovyForCup_data_804040A4, RaceScene_GetPerspFovyForCup_data_80407A34, RaceScene_GetPerspFovyForCup_data_80407A34, RaceScene_GetPerspFovyForCup_data_80407A34,
    RaceScene_GetPerspFovyForCup_data_80407A34, lbl_8031D174, lbl_8031D174, lbl_8031D174,
    lbl_8031D174, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031D1A4, RaceScene_GetPerspFovyForCup_data_8040B4DC, RaceScene_GetPerspFovyForCup_data_8040B4DC,
    RaceScene_GetPerspFovyForCup_data_8040B4DC, RaceScene_GetPerspFovyForCup_data_8040B4DC, lbl_8031D1B8, lbl_8031D1C8,
    lbl_8031D1D8, lbl_8031D1E8, RaceScene_GetPerspFovyForCup_data_8040A7E4, RaceScene_GetPerspFovyForCup_data_8040A814,
    (void *)0x43340000, lbl_8031D200, lbl_8031D218, lbl_8031D230,
    lbl_8031D1E8, lbl_8031D1E8, lbl_8031D218, lbl_8031D230,
    lbl_8031D1E8, lbl_8031D1E8, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_80402334, RaceScene_GetPerspFovyForCup_data_80402334,
    RaceScene_GetPerspFovyForCup_data_80402334, RaceScene_GetPerspFovyForCup_data_80402334, RaceScene_GetPerspFovyForCup_data_804061D4, RaceScene_GetPerspFovyForCup_data_804061D4,
    RaceScene_GetPerspFovyForCup_data_804061D4, RaceScene_GetPerspFovyForCup_data_804061D4, lbl_8031D248, lbl_8031D248,
    lbl_8031D248, lbl_8031D248, RaceScene_GetPerspFovyForCup_data_8040A7FC, RaceScene_GetPerspFovyForCup_data_8040A874,
    (void *)0x00000000, lbl_8031D25C, lbl_8031D218, lbl_8031D230,
    lbl_8031D1E8, lbl_8031D1E8, lbl_8031D218, lbl_8031D230,
    lbl_8031D1E8, lbl_8031D1E8, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_804041E4, RaceScene_GetPerspFovyForCup_data_804041E4,
    RaceScene_GetPerspFovyForCup_data_804041E4, RaceScene_GetPerspFovyForCup_data_804041E4, RaceScene_GetPerspFovyForCup_data_80407BD4, RaceScene_GetPerspFovyForCup_data_80407BD4,
    RaceScene_GetPerspFovyForCup_data_80407BD4, RaceScene_GetPerspFovyForCup_data_80407BD4, lbl_8031D248, lbl_8031D248,
    lbl_8031D248, lbl_8031D248, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031D278, RaceScene_GetPerspFovyForCup_data_8040B524,
    RaceScene_GetPerspFovyForCup_data_8040B524, RaceScene_GetPerspFovyForCup_data_8040B524, RaceScene_GetPerspFovyForCup_data_8040B524, lbl_8031D28C,
    lbl_8031D298, lbl_8031D298, lbl_8031D2A4, RaceScene_GetPerspFovyForCup_data_8040A8D4,
    RaceScene_GetPerspFovyForCup_data_8040A904, (void *)0x43340000, lbl_8031D2B0, lbl_8031D2C8,
    lbl_8031D2E0, lbl_8031D2F8, lbl_8031D2F8, lbl_8031D2C8,
    lbl_8031D2E0, lbl_8031D2F8, lbl_8031D2F8, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_80402D64,
    RaceScene_GetPerspFovyForCup_data_80402D64, RaceScene_GetPerspFovyForCup_data_80402D64, RaceScene_GetPerspFovyForCup_data_80402D64, RaceScene_GetPerspFovyForCup_data_804069F4,
    RaceScene_GetPerspFovyForCup_data_804069F4, RaceScene_GetPerspFovyForCup_data_804069F4, RaceScene_GetPerspFovyForCup_data_804069F4, lbl_8031D310,
    lbl_8031D310, lbl_8031D310, lbl_8031D310, RaceScene_GetPerspFovyForCup_data_8040A8EC,
    RaceScene_GetPerspFovyForCup_data_8040A964, (void *)0x00000000, lbl_8031D324, lbl_8031D2C8,
    lbl_8031D2E0, lbl_8031D2F8, lbl_8031D2F8, lbl_8031D2C8,
    lbl_8031D2E0, lbl_8031D2F8, lbl_8031D2F8, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_80404CB4,
    RaceScene_GetPerspFovyForCup_data_80404CB4, RaceScene_GetPerspFovyForCup_data_80404CB4, RaceScene_GetPerspFovyForCup_data_80404CB4, RaceScene_GetPerspFovyForCup_data_804083F4,
    RaceScene_GetPerspFovyForCup_data_804083F4, RaceScene_GetPerspFovyForCup_data_804083F4, RaceScene_GetPerspFovyForCup_data_804083F4, lbl_8031D310,
    lbl_8031D310, lbl_8031D310, lbl_8031D310, lbl_8031D340,
    (void *)0x00000000, (void *)0x00000000, lbl_8031D340, lbl_8031D358,
    RaceScene_GetPerspFovyForCup_data_8040B524, RaceScene_GetPerspFovyForCup_data_8040B524, RaceScene_GetPerspFovyForCup_data_8040B524, RaceScene_GetPerspFovyForCup_data_8040B524,
    lbl_8031D28C, lbl_8031D298, lbl_8031D298, lbl_8031D2A4,
    RaceScene_GetPerspFovyForCup_data_8040A8D4, RaceScene_GetPerspFovyForCup_data_8040A904, (void *)0x43340000, lbl_8031D36C,
    lbl_8031D384, lbl_8031D398, lbl_8031D3AC, lbl_8031D3AC,
    lbl_8031D384, lbl_8031D398, lbl_8031D3AC, lbl_8031D3AC,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    RaceScene_GetPerspFovyForCup_data_80402E64, RaceScene_GetPerspFovyForCup_data_80402E64, RaceScene_GetPerspFovyForCup_data_80402E64, RaceScene_GetPerspFovyForCup_data_80402E64,
    RaceScene_GetPerspFovyForCup_data_80406B94, RaceScene_GetPerspFovyForCup_data_80406B94, RaceScene_GetPerspFovyForCup_data_80406B94, RaceScene_GetPerspFovyForCup_data_80406B94,
    lbl_8031D3C0, lbl_8031D3C0, lbl_8031D3C0, lbl_8031D3C0,
    RaceScene_GetPerspFovyForCup_data_8040A8EC, RaceScene_GetPerspFovyForCup_data_8040A964, (void *)0x00000000, lbl_8031D3D4,
    lbl_8031D384, lbl_8031D398, lbl_8031D3AC, lbl_8031D3AC,
    lbl_8031D384, lbl_8031D398, lbl_8031D3AC, lbl_8031D3AC,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    RaceScene_GetPerspFovyForCup_data_80404DB4, RaceScene_GetPerspFovyForCup_data_80404DB4, RaceScene_GetPerspFovyForCup_data_80404DB4, RaceScene_GetPerspFovyForCup_data_80404DB4,
    RaceScene_GetPerspFovyForCup_data_80408594, RaceScene_GetPerspFovyForCup_data_80408594, RaceScene_GetPerspFovyForCup_data_80408594, RaceScene_GetPerspFovyForCup_data_80408594,
    lbl_8031D3C0, lbl_8031D3C0, lbl_8031D3C0, lbl_8031D3C0,
    lbl_8031D3F0, (void *)0x00000000, (void *)0x00000000, lbl_8031D3F0,
    lbl_8031D408, RaceScene_GetPerspFovyForCup_data_8040B56C, RaceScene_GetPerspFovyForCup_data_8040B56C, RaceScene_GetPerspFovyForCup_data_8040B56C,
    RaceScene_GetPerspFovyForCup_data_8040B56C, lbl_8031D418, lbl_8031D418, lbl_8031D418,
    lbl_8031D418, RaceScene_GetPerspFovyForCup_data_8040A9C4, RaceScene_GetPerspFovyForCup_data_8040AA24, (void *)0x43340000,
    lbl_8031D428, lbl_8031D440, lbl_8031D440, lbl_8031D440,
    lbl_8031D440, lbl_8031D440, lbl_8031D440, lbl_8031D440,
    lbl_8031D440, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_80402FD4, RaceScene_GetPerspFovyForCup_data_80402FD4, RaceScene_GetPerspFovyForCup_data_80402FD4,
    RaceScene_GetPerspFovyForCup_data_80402FD4, RaceScene_GetPerspFovyForCup_data_80406D34, RaceScene_GetPerspFovyForCup_data_80406D34, RaceScene_GetPerspFovyForCup_data_80406D34,
    RaceScene_GetPerspFovyForCup_data_80406D34, lbl_8031D454, lbl_8031D468, lbl_8031D47C,
    lbl_8031D490, RaceScene_GetPerspFovyForCup_data_8040A9F4, RaceScene_GetPerspFovyForCup_data_8040AAE4, (void *)0x00000000,
    lbl_8031D4A4, lbl_8031D440, lbl_8031D440, lbl_8031D440,
    lbl_8031D440, lbl_8031D440, lbl_8031D440, lbl_8031D440,
    lbl_8031D440, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_80404F34, RaceScene_GetPerspFovyForCup_data_80404F34, RaceScene_GetPerspFovyForCup_data_80404F34,
    RaceScene_GetPerspFovyForCup_data_80404F34, RaceScene_GetPerspFovyForCup_data_80408734, RaceScene_GetPerspFovyForCup_data_80408734, RaceScene_GetPerspFovyForCup_data_80408734,
    RaceScene_GetPerspFovyForCup_data_80408734, lbl_8031D454, lbl_8031D468, lbl_8031D47C,
    lbl_8031D490, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031D4C0, RaceScene_GetPerspFovyForCup_data_8040B56C, RaceScene_GetPerspFovyForCup_data_8040B56C,
    RaceScene_GetPerspFovyForCup_data_8040B56C, RaceScene_GetPerspFovyForCup_data_8040B56C, lbl_8031D4D0, lbl_8031D4D0,
    lbl_8031D4D0, lbl_8031D4D0, RaceScene_GetPerspFovyForCup_data_8040A9DC, RaceScene_GetPerspFovyForCup_data_8040AA84,
    (void *)0x00000000, lbl_8031D4E0, lbl_8031D4F8, lbl_8031D4F8,
    lbl_8031D4F8, lbl_8031D4F8, lbl_8031D4F8, lbl_8031D4F8,
    lbl_8031D4F8, lbl_8031D4F8, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_80403154, RaceScene_GetPerspFovyForCup_data_80403154,
    RaceScene_GetPerspFovyForCup_data_80403154, RaceScene_GetPerspFovyForCup_data_80403154, RaceScene_GetPerspFovyForCup_data_80406ED4, RaceScene_GetPerspFovyForCup_data_80406ED4,
    RaceScene_GetPerspFovyForCup_data_80406ED4, RaceScene_GetPerspFovyForCup_data_80406ED4, lbl_8031D50C, lbl_8031D520,
    lbl_8031D534, lbl_8031D548, RaceScene_GetPerspFovyForCup_data_8040AA0C, RaceScene_GetPerspFovyForCup_data_8040AB44,
    (void *)0x434C0000, lbl_8031D55C, lbl_8031D4F8, lbl_8031D4F8,
    lbl_8031D4F8, lbl_8031D4F8, lbl_8031D4F8, lbl_8031D4F8,
    lbl_8031D4F8, lbl_8031D4F8, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_804050B4, RaceScene_GetPerspFovyForCup_data_804050B4,
    RaceScene_GetPerspFovyForCup_data_804050B4, RaceScene_GetPerspFovyForCup_data_804050B4, RaceScene_GetPerspFovyForCup_data_804088D4, RaceScene_GetPerspFovyForCup_data_804088D4,
    RaceScene_GetPerspFovyForCup_data_804088D4, RaceScene_GetPerspFovyForCup_data_804088D4, lbl_8031D50C, lbl_8031D520,
    lbl_8031D534, lbl_8031D548, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031D574, RaceScene_GetPerspFovyForCup_data_8040B5B4,
    RaceScene_GetPerspFovyForCup_data_8040B5B4, RaceScene_GetPerspFovyForCup_data_8040B5B4, RaceScene_GetPerspFovyForCup_data_8040B5B4, lbl_8031D588,
    lbl_8031D588, lbl_8031D588, lbl_8031D598, RaceScene_GetPerspFovyForCup_data_8040ABA4,
    RaceScene_GetPerspFovyForCup_data_8040ABD4, (void *)0x43340000, lbl_8031D5B0, lbl_8031D598,
    lbl_8031D598, lbl_8031D598, lbl_8031D598, lbl_8031D598,
    lbl_8031D598, lbl_8031D598, lbl_8031D598, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_80402434,
    RaceScene_GetPerspFovyForCup_data_80402434, RaceScene_GetPerspFovyForCup_data_80402434, RaceScene_GetPerspFovyForCup_data_80402434, RaceScene_GetPerspFovyForCup_data_80406374,
    RaceScene_GetPerspFovyForCup_data_80406374, RaceScene_GetPerspFovyForCup_data_80406374, RaceScene_GetPerspFovyForCup_data_80406374, lbl_8031D5CC,
    lbl_8031D5CC, lbl_8031D5CC, lbl_8031D5CC, RaceScene_GetPerspFovyForCup_data_8040ABBC,
    RaceScene_GetPerspFovyForCup_data_8040AC34, (void *)0x00000000, lbl_8031D5E0, lbl_8031D598,
    lbl_8031D598, lbl_8031D598, lbl_8031D598, lbl_8031D598,
    lbl_8031D598, lbl_8031D598, lbl_8031D598, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_80404394,
    RaceScene_GetPerspFovyForCup_data_80404394, RaceScene_GetPerspFovyForCup_data_80404394, RaceScene_GetPerspFovyForCup_data_80404394, RaceScene_GetPerspFovyForCup_data_80407D74,
    RaceScene_GetPerspFovyForCup_data_80407D74, RaceScene_GetPerspFovyForCup_data_80407D74, RaceScene_GetPerspFovyForCup_data_80407D74, lbl_8031D5CC,
    lbl_8031D5CC, lbl_8031D5CC, lbl_8031D5CC, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, lbl_8031D5FC,
    RaceScene_GetPerspFovyForCup_data_8040B5B4, RaceScene_GetPerspFovyForCup_data_8040B5B4, RaceScene_GetPerspFovyForCup_data_8040B5B4, RaceScene_GetPerspFovyForCup_data_8040B5B4,
    lbl_8031D610, lbl_8031D610, lbl_8031D610, lbl_8031D620,
    RaceScene_GetPerspFovyForCup_data_8040ABA4, RaceScene_GetPerspFovyForCup_data_8040ABD4, (void *)0x43340000, lbl_8031D638,
    lbl_8031D620, lbl_8031D620, lbl_8031D620, lbl_8031D620,
    lbl_8031D620, lbl_8031D620, lbl_8031D620, lbl_8031D620,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    RaceScene_GetPerspFovyForCup_data_804025A4, RaceScene_GetPerspFovyForCup_data_804025A4, RaceScene_GetPerspFovyForCup_data_804025A4, RaceScene_GetPerspFovyForCup_data_804025A4,
    RaceScene_GetPerspFovyForCup_data_80406514, RaceScene_GetPerspFovyForCup_data_80406514, RaceScene_GetPerspFovyForCup_data_80406514, RaceScene_GetPerspFovyForCup_data_80406514,
    lbl_8031D650, lbl_8031D650, lbl_8031D650, lbl_8031D650,
    RaceScene_GetPerspFovyForCup_data_8040ABBC, RaceScene_GetPerspFovyForCup_data_8040AC34, (void *)0x00000000, lbl_8031D664,
    lbl_8031D620, lbl_8031D620, lbl_8031D620, lbl_8031D620,
    lbl_8031D620, lbl_8031D620, lbl_8031D620, lbl_8031D620,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    RaceScene_GetPerspFovyForCup_data_804044F4, RaceScene_GetPerspFovyForCup_data_804044F4, RaceScene_GetPerspFovyForCup_data_804044F4, RaceScene_GetPerspFovyForCup_data_804044F4,
    RaceScene_GetPerspFovyForCup_data_80407F14, RaceScene_GetPerspFovyForCup_data_80407F14, RaceScene_GetPerspFovyForCup_data_80407F14, RaceScene_GetPerspFovyForCup_data_80407F14,
    lbl_8031D650, lbl_8031D650, lbl_8031D650, lbl_8031D650,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031D680, RaceScene_GetPerspFovyForCup_data_8040B5FC, RaceScene_GetPerspFovyForCup_data_8040B5FC, RaceScene_GetPerspFovyForCup_data_8040B5FC,
    RaceScene_GetPerspFovyForCup_data_8040B5FC, lbl_8031D690, lbl_8031D6A0, lbl_8031D6B0,
    lbl_8031D6C0, RaceScene_GetPerspFovyForCup_data_8040AC94, RaceScene_GetPerspFovyForCup_data_8040ACC4, (void *)0x43340000,
    lbl_8031D6D0, lbl_8031D6E8, lbl_8031D6FC, lbl_8031D710,
    lbl_8031D724, lbl_8031D6E8, lbl_8031D6FC, lbl_8031D710,
    lbl_8031D724, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_80402724, RaceScene_GetPerspFovyForCup_data_80402724, RaceScene_GetPerspFovyForCup_data_80402724,
    RaceScene_GetPerspFovyForCup_data_80402724, RaceScene_GetPerspFovyForCup_data_804066B4, RaceScene_GetPerspFovyForCup_data_804066B4, RaceScene_GetPerspFovyForCup_data_804066B4,
    RaceScene_GetPerspFovyForCup_data_804066B4, lbl_8031D738, lbl_8031D738, lbl_8031D738,
    lbl_8031D738, RaceScene_GetPerspFovyForCup_data_8040ACAC, RaceScene_GetPerspFovyForCup_data_8040AD24, (void *)0x00000000,
    lbl_8031D74C, lbl_8031D6E8, lbl_8031D6FC, lbl_8031D710,
    lbl_8031D724, lbl_8031D6E8, lbl_8031D6FC, lbl_8031D710,
    lbl_8031D724, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_80404654, RaceScene_GetPerspFovyForCup_data_80404654, RaceScene_GetPerspFovyForCup_data_80404654,
    RaceScene_GetPerspFovyForCup_data_80404654, RaceScene_GetPerspFovyForCup_data_804080B4, RaceScene_GetPerspFovyForCup_data_804080B4, RaceScene_GetPerspFovyForCup_data_804080B4,
    RaceScene_GetPerspFovyForCup_data_804080B4, lbl_8031D738, lbl_8031D738, lbl_8031D738,
    lbl_8031D738, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031D768, RaceScene_GetPerspFovyForCup_data_8040B5FC, RaceScene_GetPerspFovyForCup_data_8040B5FC,
    RaceScene_GetPerspFovyForCup_data_8040B5FC, RaceScene_GetPerspFovyForCup_data_8040B5FC, lbl_8031D690, lbl_8031D6A0,
    lbl_8031D6B0, lbl_8031D6C0, RaceScene_GetPerspFovyForCup_data_8040AC94, RaceScene_GetPerspFovyForCup_data_8040ACC4,
    (void *)0x43340000, lbl_8031D778, lbl_8031D790, lbl_8031D7A4,
    lbl_8031D7B8, lbl_8031D7CC, lbl_8031D790, lbl_8031D7A4,
    lbl_8031D7B8, lbl_8031D7CC, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_80402A44, RaceScene_GetPerspFovyForCup_data_80402A44,
    RaceScene_GetPerspFovyForCup_data_80402A44, RaceScene_GetPerspFovyForCup_data_80402A44, RaceScene_GetPerspFovyForCup_data_80406854, RaceScene_GetPerspFovyForCup_data_80406854,
    RaceScene_GetPerspFovyForCup_data_80406854, RaceScene_GetPerspFovyForCup_data_80406854, lbl_8031D7E0, lbl_8031D7E0,
    lbl_8031D7E0, lbl_8031D7E0, RaceScene_GetPerspFovyForCup_data_8040ACAC, RaceScene_GetPerspFovyForCup_data_8040AD24,
    (void *)0x00000000, lbl_8031D7F4, lbl_8031D80C, lbl_8031D824,
    lbl_8031D83C, lbl_8031D854, lbl_8031D80C, lbl_8031D824,
    lbl_8031D83C, lbl_8031D854, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, RaceScene_GetPerspFovyForCup_data_80404994, RaceScene_GetPerspFovyForCup_data_80404994,
    RaceScene_GetPerspFovyForCup_data_80404994, RaceScene_GetPerspFovyForCup_data_80404994, RaceScene_GetPerspFovyForCup_data_80408254, RaceScene_GetPerspFovyForCup_data_80408254,
    RaceScene_GetPerspFovyForCup_data_80408254, RaceScene_GetPerspFovyForCup_data_80408254, lbl_8031D86C, lbl_8031D86C,
    lbl_8031D86C, lbl_8031D86C, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031D880, RaceScene_GetPerspFovyForCup_data_8040B644,
    RaceScene_GetPerspFovyForCup_data_8040B644, RaceScene_GetPerspFovyForCup_data_8040B644, RaceScene_GetPerspFovyForCup_data_8040B644, lbl_8031D890,
    lbl_8031D890, lbl_8031D890, lbl_8031D890, RaceScene_GetPerspFovyForCup_data_8040AD84,
    RaceScene_GetPerspFovyForCup_data_8040ADB4, (void *)0x43340000, lbl_8031D8A4, lbl_8031D890,
    lbl_8031D890, lbl_8031D890, lbl_8031D890, lbl_8031D890,
    lbl_8031D890, lbl_8031D890, lbl_8031D890, RaceScene_GetPerspFovyForCup_data_8040AE74,
    RaceScene_GetPerspFovyForCup_data_8040AE74, RaceScene_GetPerspFovyForCup_data_8040AE74, RaceScene_GetPerspFovyForCup_data_8040AE74, RaceScene_GetPerspFovyForCup_data_80403324,
    RaceScene_GetPerspFovyForCup_data_80403324, RaceScene_GetPerspFovyForCup_data_80403324, RaceScene_GetPerspFovyForCup_data_80403324, RaceScene_GetPerspFovyForCup_data_80407074,
    RaceScene_GetPerspFovyForCup_data_80407074, RaceScene_GetPerspFovyForCup_data_80407074, RaceScene_GetPerspFovyForCup_data_80407074, lbl_8031D8BC,
    lbl_8031D8BC, lbl_8031D8BC, lbl_8031D8BC, RaceScene_GetPerspFovyForCup_data_8040AD9C,
    RaceScene_GetPerspFovyForCup_data_8040AE14, (void *)0x00000000, lbl_8031D8D0, lbl_8031D890,
    lbl_8031D890, lbl_8031D890, lbl_8031D890, lbl_8031D890,
    lbl_8031D890, lbl_8031D890, lbl_8031D890, RaceScene_GetPerspFovyForCup_data_8040AE74,
    RaceScene_GetPerspFovyForCup_data_8040AE74, RaceScene_GetPerspFovyForCup_data_8040AE74, RaceScene_GetPerspFovyForCup_data_8040AE74, RaceScene_GetPerspFovyForCup_data_80405284,
    RaceScene_GetPerspFovyForCup_data_80405284, RaceScene_GetPerspFovyForCup_data_80405284, RaceScene_GetPerspFovyForCup_data_80405284, RaceScene_GetPerspFovyForCup_data_80408A74,
    RaceScene_GetPerspFovyForCup_data_80408A74, RaceScene_GetPerspFovyForCup_data_80408A74, RaceScene_GetPerspFovyForCup_data_80408A74, lbl_8031D8BC,
    lbl_8031D8BC, lbl_8031D8BC, lbl_8031D8BC, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, lbl_8031D8EC,
    RaceScene_GetPerspFovyForCup_data_8040B644, RaceScene_GetPerspFovyForCup_data_8040B644, RaceScene_GetPerspFovyForCup_data_8040B644, RaceScene_GetPerspFovyForCup_data_8040B644,
    lbl_8031D8FC, lbl_8031D8FC, lbl_8031D8FC, lbl_8031D8FC,
    RaceScene_GetPerspFovyForCup_data_8040AD84, RaceScene_GetPerspFovyForCup_data_8040ADB4, (void *)0x43340000, lbl_8031D910,
    lbl_8031D8FC, lbl_8031D8FC, lbl_8031D8FC, lbl_8031D8FC,
    lbl_8031D8FC, lbl_8031D8FC, lbl_8031D8FC, lbl_8031D8FC,
    RaceScene_GetPerspFovyForCup_data_8040AE90, RaceScene_GetPerspFovyForCup_data_8040AE90, RaceScene_GetPerspFovyForCup_data_8040AE90, RaceScene_GetPerspFovyForCup_data_8040AE90,
    RaceScene_GetPerspFovyForCup_data_80403654, RaceScene_GetPerspFovyForCup_data_80403654, RaceScene_GetPerspFovyForCup_data_80403654, RaceScene_GetPerspFovyForCup_data_80403654,
    RaceScene_GetPerspFovyForCup_data_80407214, RaceScene_GetPerspFovyForCup_data_80407214, RaceScene_GetPerspFovyForCup_data_80407214, RaceScene_GetPerspFovyForCup_data_80407214,
    lbl_8031D928, lbl_8031D928, lbl_8031D928, lbl_8031D928,
    RaceScene_GetPerspFovyForCup_data_8040AD9C, RaceScene_GetPerspFovyForCup_data_8040AE14, (void *)0x00000000, lbl_8031D93C,
    lbl_8031D8FC, lbl_8031D8FC, lbl_8031D8FC, lbl_8031D8FC,
    lbl_8031D8FC, lbl_8031D8FC, lbl_8031D8FC, lbl_8031D8FC,
    RaceScene_GetPerspFovyForCup_data_8040AE90, RaceScene_GetPerspFovyForCup_data_8040AE90, RaceScene_GetPerspFovyForCup_data_8040AE90, RaceScene_GetPerspFovyForCup_data_8040AE90,
    RaceScene_GetPerspFovyForCup_data_804055B4, RaceScene_GetPerspFovyForCup_data_804055B4, RaceScene_GetPerspFovyForCup_data_804055B4, RaceScene_GetPerspFovyForCup_data_804055B4,
    RaceScene_GetPerspFovyForCup_data_80408C14, RaceScene_GetPerspFovyForCup_data_80408C14, RaceScene_GetPerspFovyForCup_data_80408C14, RaceScene_GetPerspFovyForCup_data_80408C14,
    lbl_8031D928, lbl_8031D928, lbl_8031D928, lbl_8031D928,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031D954, RaceScene_GetPerspFovyForCup_data_8040B68C, RaceScene_GetPerspFovyForCup_data_8040B68C, RaceScene_GetPerspFovyForCup_data_8040B68C,
    RaceScene_GetPerspFovyForCup_data_8040B68C, lbl_8031D968, lbl_8031D968, lbl_8031D968,
    lbl_8031D968, RaceScene_GetPerspFovyForCup_data_8040AEAC, RaceScene_GetPerspFovyForCup_data_8040AEDC, (void *)0x43340000,
    lbl_8031D980, lbl_8031D968, lbl_8031D968, lbl_8031D968,
    lbl_8031D968, lbl_8031D968, lbl_8031D968, lbl_8031D968,
    lbl_8031D968, RaceScene_GetPerspFovyForCup_data_8040AF9C, RaceScene_GetPerspFovyForCup_data_8040AF9C, RaceScene_GetPerspFovyForCup_data_8040AF9C,
    RaceScene_GetPerspFovyForCup_data_8040AF9C, RaceScene_GetPerspFovyForCup_data_804039B4, RaceScene_GetPerspFovyForCup_data_804039B4, RaceScene_GetPerspFovyForCup_data_804039B4,
    RaceScene_GetPerspFovyForCup_data_804039B4, RaceScene_GetPerspFovyForCup_data_804073B4, RaceScene_GetPerspFovyForCup_data_804073B4, RaceScene_GetPerspFovyForCup_data_804073B4,
    RaceScene_GetPerspFovyForCup_data_804073B4, lbl_8031D99C, lbl_8031D99C, lbl_8031D99C,
    lbl_8031D99C, RaceScene_GetPerspFovyForCup_data_8040AEC4, RaceScene_GetPerspFovyForCup_data_8040AF3C, (void *)0x00000000,
    lbl_8031D9B4, lbl_8031D968, lbl_8031D968, lbl_8031D968,
    lbl_8031D968, lbl_8031D968, lbl_8031D968, lbl_8031D968,
    lbl_8031D968, RaceScene_GetPerspFovyForCup_data_8040AFD4, RaceScene_GetPerspFovyForCup_data_8040AFD4, RaceScene_GetPerspFovyForCup_data_8040AFD4,
    RaceScene_GetPerspFovyForCup_data_8040AFD4, RaceScene_GetPerspFovyForCup_data_80405914, RaceScene_GetPerspFovyForCup_data_80405914, RaceScene_GetPerspFovyForCup_data_80405914,
    RaceScene_GetPerspFovyForCup_data_80405914, RaceScene_GetPerspFovyForCup_data_80408DB4, RaceScene_GetPerspFovyForCup_data_80408DB4, RaceScene_GetPerspFovyForCup_data_80408DB4,
    RaceScene_GetPerspFovyForCup_data_80408DB4, lbl_8031D99C, lbl_8031D99C, lbl_8031D99C,
    lbl_8031D99C, lbl_8031D9D0, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031D9E8, RaceScene_GetPerspFovyForCup_data_8040B68C, RaceScene_GetPerspFovyForCup_data_8040B68C,
    RaceScene_GetPerspFovyForCup_data_8040B68C, RaceScene_GetPerspFovyForCup_data_8040B68C, lbl_8031D9FC, lbl_8031D9FC,
    lbl_8031D9FC, lbl_8031D9FC, RaceScene_GetPerspFovyForCup_data_8040AEAC, RaceScene_GetPerspFovyForCup_data_8040AEDC,
    (void *)0x43340000, lbl_8031DA14, lbl_8031D9FC, lbl_8031D9FC,
    lbl_8031D9FC, lbl_8031D9FC, lbl_8031D9FC, lbl_8031D9FC,
    lbl_8031D9FC, lbl_8031D9FC, RaceScene_GetPerspFovyForCup_data_8040AFB8, RaceScene_GetPerspFovyForCup_data_8040AFB8,
    RaceScene_GetPerspFovyForCup_data_8040AFB8, RaceScene_GetPerspFovyForCup_data_8040AFB8, RaceScene_GetPerspFovyForCup_data_80403BA4, RaceScene_GetPerspFovyForCup_data_80403BA4,
    RaceScene_GetPerspFovyForCup_data_80403BA4, RaceScene_GetPerspFovyForCup_data_80403BA4, RaceScene_GetPerspFovyForCup_data_80407554, RaceScene_GetPerspFovyForCup_data_80407554,
    RaceScene_GetPerspFovyForCup_data_80407554, RaceScene_GetPerspFovyForCup_data_80407554, lbl_8031DA30, lbl_8031DA30,
    lbl_8031DA30, lbl_8031DA44, RaceScene_GetPerspFovyForCup_data_8040AEC4, RaceScene_GetPerspFovyForCup_data_8040AF3C,
    (void *)0x00000000, lbl_8031DA5C, lbl_8031D9FC, lbl_8031D9FC,
    lbl_8031D9FC, lbl_8031D9FC, lbl_8031D9FC, lbl_8031D9FC,
    lbl_8031D9FC, lbl_8031D9FC, RaceScene_GetPerspFovyForCup_data_8040AFF0, RaceScene_GetPerspFovyForCup_data_8040AFF0,
    RaceScene_GetPerspFovyForCup_data_8040AFF0, RaceScene_GetPerspFovyForCup_data_8040AFF0, RaceScene_GetPerspFovyForCup_data_80405B04, RaceScene_GetPerspFovyForCup_data_80405B04,
    RaceScene_GetPerspFovyForCup_data_80405B04, RaceScene_GetPerspFovyForCup_data_80405B04, RaceScene_GetPerspFovyForCup_data_80408F54, RaceScene_GetPerspFovyForCup_data_80408F54,
    RaceScene_GetPerspFovyForCup_data_80408F54, RaceScene_GetPerspFovyForCup_data_80408F54, lbl_8031DA30, lbl_8031DA30,
    lbl_8031DA30, lbl_8031DA44, lbl_8031DA78, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031DA90, Block2,
    Block2, Block2, Block2, lbl_8031CEBC,
    lbl_8031CEBC, lbl_8031CEBC, lbl_8031CEBC, RaceScene_GetPerspFovyForCup_data_8040B00C,
    RaceScene_GetPerspFovyForCup_data_8040B024, (void *)0x43A50000, (void *)0x00000000, lbl_8031DAA8,
    lbl_8031DAA8, lbl_8031DAA8, lbl_8031DAA8, lbl_8031DAA8,
    lbl_8031DAA8, lbl_8031DAA8, lbl_8031DAA8, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, lbl_8031DAC4,
    lbl_8031DAC4, lbl_8031DAC4, lbl_8031DAC4, RaceScene_GetPerspFovyForCup_data_8040B00C,
    RaceScene_GetPerspFovyForCup_data_8040B024, (void *)0x43A50000, (void *)0x00000000, lbl_8031DAA8,
    lbl_8031DAA8, lbl_8031DAA8, lbl_8031DAA8, lbl_8031DAA8,
    lbl_8031DAA8, lbl_8031DAA8, lbl_8031DAA8, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, lbl_8031DAC4,
    lbl_8031DAC4, lbl_8031DAC4, lbl_8031DAC4, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, lbl_8031DA90,
    Block2, Block2, Block2, Block2,
    lbl_8031DAA8, lbl_8031DAA8, lbl_8031DAA8, lbl_8031DAA8,
    RaceScene_GetPerspFovyForCup_data_8040B00C, RaceScene_GetPerspFovyForCup_data_8040B024, (void *)0x43A50000, (void *)0x00000000,
    lbl_8031DAA8, lbl_8031DAA8, lbl_8031DAA8, lbl_8031DAA8,
    lbl_8031DAA8, lbl_8031DAA8, lbl_8031DAA8, lbl_8031DAA8,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031DAC4, lbl_8031DAC4, lbl_8031DAC4, lbl_8031DAC4,
    RaceScene_GetPerspFovyForCup_data_8040B00C, RaceScene_GetPerspFovyForCup_data_8040B024, (void *)0x43A50000, (void *)0x00000000,
    lbl_8031DAA8, lbl_8031DAA8, lbl_8031DAA8, lbl_8031DAA8,
    lbl_8031DAA8, lbl_8031DAA8, lbl_8031DAA8, lbl_8031DAA8,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031DAC4, lbl_8031DAC4, lbl_8031DAC4, lbl_8031DAC4,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031DAE0, RaceScene_GetPerspFovyForCup_data_8040B71C, RaceScene_GetPerspFovyForCup_data_8040B71C, RaceScene_GetPerspFovyForCup_data_8040B71C,
    RaceScene_GetPerspFovyForCup_data_8040B71C, lbl_8031D0E0, lbl_8031D0E0, lbl_8031D0E0,
    lbl_8031D0E0, RaceScene_GetPerspFovyForCup_data_8040B030, RaceScene_GetPerspFovyForCup_data_8040B048, (void *)0x43340000,
    (void *)0x00000000, lbl_8031DAF4, lbl_8031DAF4, lbl_8031DAF4,
    lbl_8031DAF4, lbl_8031DAF4, lbl_8031DAF4, lbl_8031DAF4,
    lbl_8031DAF4, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031D174, lbl_8031D174, lbl_8031D174,
    lbl_8031D174, RaceScene_GetPerspFovyForCup_data_8040B030, RaceScene_GetPerspFovyForCup_data_8040B048, (void *)0x43340000,
    (void *)0x00000000, lbl_8031DAF4, lbl_8031DAF4, lbl_8031DAF4,
    lbl_8031DAF4, lbl_8031DAF4, lbl_8031DAF4, lbl_8031DAF4,
    lbl_8031DAF4, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031D174, lbl_8031D174, lbl_8031D174,
    lbl_8031D174, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031DAE0, RaceScene_GetPerspFovyForCup_data_8040B71C, RaceScene_GetPerspFovyForCup_data_8040B71C,
    RaceScene_GetPerspFovyForCup_data_8040B71C, RaceScene_GetPerspFovyForCup_data_8040B71C, lbl_8031DAF4, lbl_8031DAF4,
    lbl_8031DAF4, lbl_8031DAF4, RaceScene_GetPerspFovyForCup_data_8040B030, RaceScene_GetPerspFovyForCup_data_8040B048,
    (void *)0x43340000, (void *)0x00000000, lbl_8031DAF4, lbl_8031DAF4,
    lbl_8031DAF4, lbl_8031DAF4, lbl_8031DAF4, lbl_8031DAF4,
    lbl_8031DAF4, lbl_8031DAF4, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031D174, lbl_8031D174,
    lbl_8031D174, lbl_8031D174, RaceScene_GetPerspFovyForCup_data_8040B030, RaceScene_GetPerspFovyForCup_data_8040B048,
    (void *)0x43340000, (void *)0x00000000, lbl_8031DAF4, lbl_8031DAF4,
    lbl_8031DAF4, lbl_8031DAF4, lbl_8031DAF4, lbl_8031DAF4,
    lbl_8031DAF4, lbl_8031DAF4, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031D174, lbl_8031D174,
    lbl_8031D174, lbl_8031D174, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031DB0C, RaceScene_GetPerspFovyForCup_data_8040B524,
    RaceScene_GetPerspFovyForCup_data_8040B524, RaceScene_GetPerspFovyForCup_data_8040B524, RaceScene_GetPerspFovyForCup_data_8040B524, lbl_8031D28C,
    lbl_8031D28C, lbl_8031D28C, lbl_8031D28C, RaceScene_GetPerspFovyForCup_data_8040A8D4,
    RaceScene_GetPerspFovyForCup_data_8040A904, (void *)0x43340000, (void *)0x00000000, lbl_8031DB20,
    lbl_8031DB20, lbl_8031DB20, lbl_8031DB20, lbl_8031DB20,
    lbl_8031DB20, lbl_8031DB20, lbl_8031DB20, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, lbl_8031D310,
    lbl_8031D310, lbl_8031D310, lbl_8031D310, RaceScene_GetPerspFovyForCup_data_8040A8D4,
    RaceScene_GetPerspFovyForCup_data_8040A904, (void *)0x43340000, (void *)0x00000000, lbl_8031DB20,
    lbl_8031DB20, lbl_8031DB20, lbl_8031DB20, lbl_8031DB20,
    lbl_8031DB20, lbl_8031DB20, lbl_8031DB20, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, lbl_8031D310,
    lbl_8031D310, lbl_8031D310, lbl_8031D310, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, lbl_8031DB0C,
    RaceScene_GetPerspFovyForCup_data_8040B524, RaceScene_GetPerspFovyForCup_data_8040B524, RaceScene_GetPerspFovyForCup_data_8040B524, RaceScene_GetPerspFovyForCup_data_8040B524,
    lbl_8031D28C, lbl_8031D28C, lbl_8031D28C, lbl_8031D28C,
    RaceScene_GetPerspFovyForCup_data_8040A8D4, RaceScene_GetPerspFovyForCup_data_8040A904, (void *)0x43340000, (void *)0x00000000,
    lbl_8031DB20, lbl_8031DB20, lbl_8031DB20, lbl_8031DB20,
    lbl_8031DB20, lbl_8031DB20, lbl_8031DB20, lbl_8031DB20,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031DB38, lbl_8031DB38, lbl_8031DB38, lbl_8031DB38,
    RaceScene_GetPerspFovyForCup_data_8040A8D4, RaceScene_GetPerspFovyForCup_data_8040A904, (void *)0x43340000, (void *)0x00000000,
    lbl_8031DB20, lbl_8031DB20, lbl_8031DB20, lbl_8031DB20,
    lbl_8031DB20, lbl_8031DB20, lbl_8031DB20, lbl_8031DB20,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031DB38, lbl_8031DB38, lbl_8031DB38, lbl_8031DB38,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031DB50, RaceScene_GetPerspFovyForCup_data_8040B764, RaceScene_GetPerspFovyForCup_data_8040B764, RaceScene_GetPerspFovyForCup_data_8040B764,
    RaceScene_GetPerspFovyForCup_data_8040B764, lbl_8031D418, lbl_8031D418, lbl_8031D418,
    lbl_8031D418, RaceScene_GetPerspFovyForCup_data_8040B054, RaceScene_GetPerspFovyForCup_data_8040B06C, (void *)0x43340000,
    (void *)0x00000000, lbl_8031DB64, lbl_8031DB64, lbl_8031DB64,
    lbl_8031DB64, lbl_8031DB64, lbl_8031DB64, lbl_8031DB64,
    lbl_8031DB64, RaceScene_GetPerspFovyForCup_data_8040B078, RaceScene_GetPerspFovyForCup_data_8040B078, RaceScene_GetPerspFovyForCup_data_8040B078,
    RaceScene_GetPerspFovyForCup_data_8040B078, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031DB7C, lbl_8031DB7C, lbl_8031DB7C,
    lbl_8031DB7C, RaceScene_GetPerspFovyForCup_data_8040B054, RaceScene_GetPerspFovyForCup_data_8040B06C, (void *)0x43340000,
    (void *)0x00000000, lbl_8031DB64, lbl_8031DB64, lbl_8031DB64,
    lbl_8031DB64, lbl_8031DB64, lbl_8031DB64, lbl_8031DB64,
    lbl_8031DB64, RaceScene_GetPerspFovyForCup_data_8040B078, RaceScene_GetPerspFovyForCup_data_8040B078, RaceScene_GetPerspFovyForCup_data_8040B078,
    RaceScene_GetPerspFovyForCup_data_8040B078, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031DB7C, lbl_8031DB7C, lbl_8031DB7C,
    lbl_8031DB7C, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031DB50, RaceScene_GetPerspFovyForCup_data_8040B764, RaceScene_GetPerspFovyForCup_data_8040B764,
    RaceScene_GetPerspFovyForCup_data_8040B764, RaceScene_GetPerspFovyForCup_data_8040B764, lbl_8031D4D0, lbl_8031D4D0,
    lbl_8031D4D0, lbl_8031D4D0, RaceScene_GetPerspFovyForCup_data_8040B054, RaceScene_GetPerspFovyForCup_data_8040B06C,
    (void *)0x43340000, (void *)0x00000000, lbl_8031DB64, lbl_8031DB64,
    lbl_8031DB64, lbl_8031DB64, lbl_8031DB64, lbl_8031DB64,
    lbl_8031DB64, lbl_8031DB64, RaceScene_GetPerspFovyForCup_data_8040B078, RaceScene_GetPerspFovyForCup_data_8040B078,
    RaceScene_GetPerspFovyForCup_data_8040B078, RaceScene_GetPerspFovyForCup_data_8040B078, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031DB7C, lbl_8031DB7C,
    lbl_8031DB7C, lbl_8031DB7C, RaceScene_GetPerspFovyForCup_data_8040B054, RaceScene_GetPerspFovyForCup_data_8040B06C,
    (void *)0x43340000, (void *)0x00000000, lbl_8031DB64, lbl_8031DB64,
    lbl_8031DB64, lbl_8031DB64, lbl_8031DB64, lbl_8031DB64,
    lbl_8031DB64, lbl_8031DB64, RaceScene_GetPerspFovyForCup_data_8040B078, RaceScene_GetPerspFovyForCup_data_8040B078,
    RaceScene_GetPerspFovyForCup_data_8040B078, RaceScene_GetPerspFovyForCup_data_8040B078, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031DB7C, lbl_8031DB7C,
    lbl_8031DB7C, lbl_8031DB7C, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031DB94, RaceScene_GetPerspFovyForCup_data_8040B7AC,
    RaceScene_GetPerspFovyForCup_data_8040B7AC, RaceScene_GetPerspFovyForCup_data_8040B7AC, RaceScene_GetPerspFovyForCup_data_8040B7AC, lbl_8031DBA8,
    lbl_8031DBA8, lbl_8031DBA8, lbl_8031DBA8, RaceScene_GetPerspFovyForCup_data_8040B0B0,
    RaceScene_GetPerspFovyForCup_data_8040B0C8, (void *)0x43340000, (void *)0x00000000, lbl_8031DBA8,
    lbl_8031DBA8, lbl_8031DBA8, lbl_8031DBA8, lbl_8031DBA8,
    lbl_8031DBA8, lbl_8031DBA8, lbl_8031DBA8, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, lbl_8031DBC0,
    lbl_8031DBC0, lbl_8031DBC0, lbl_8031DBC0, RaceScene_GetPerspFovyForCup_data_8040B0B0,
    RaceScene_GetPerspFovyForCup_data_8040B0C8, (void *)0x43340000, (void *)0x00000000, lbl_8031DBA8,
    lbl_8031DBA8, lbl_8031DBA8, lbl_8031DBA8, lbl_8031DBA8,
    lbl_8031DBA8, lbl_8031DBA8, lbl_8031DBA8, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, lbl_8031DBC0,
    lbl_8031DBC0, lbl_8031DBC0, lbl_8031DBC0, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, lbl_8031DB94,
    RaceScene_GetPerspFovyForCup_data_8040B7AC, RaceScene_GetPerspFovyForCup_data_8040B7AC, RaceScene_GetPerspFovyForCup_data_8040B7AC, RaceScene_GetPerspFovyForCup_data_8040B7AC,
    lbl_8031DBA8, lbl_8031DBA8, lbl_8031DBA8, lbl_8031DBA8,
    RaceScene_GetPerspFovyForCup_data_8040B0B0, RaceScene_GetPerspFovyForCup_data_8040B0C8, (void *)0x43340000, (void *)0x00000000,
    lbl_8031DBA8, lbl_8031DBA8, lbl_8031DBA8, lbl_8031DBA8,
    lbl_8031DBA8, lbl_8031DBA8, lbl_8031DBA8, lbl_8031DBA8,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031DBC0, lbl_8031DBC0, lbl_8031DBC0, lbl_8031DBC0,
    RaceScene_GetPerspFovyForCup_data_8040B0B0, RaceScene_GetPerspFovyForCup_data_8040B0C8, (void *)0x43340000, (void *)0x00000000,
    lbl_8031DBA8, lbl_8031DBA8, lbl_8031DBA8, lbl_8031DBA8,
    lbl_8031DBA8, lbl_8031DBA8, lbl_8031DBA8, lbl_8031DBA8,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031DBC0, lbl_8031DBC0, lbl_8031DBC0, lbl_8031DBC0,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031DBD8, RaceScene_GetPerspFovyForCup_data_8040B5FC, RaceScene_GetPerspFovyForCup_data_8040B5FC, RaceScene_GetPerspFovyForCup_data_8040B5FC,
    RaceScene_GetPerspFovyForCup_data_8040B5FC, lbl_8031D6B0, lbl_8031D6B0, lbl_8031D6B0,
    lbl_8031D6B0, RaceScene_GetPerspFovyForCup_data_8040AC94, RaceScene_GetPerspFovyForCup_data_8040ACC4, (void *)0x43340000,
    (void *)0x00000000, lbl_8031D710, lbl_8031D710, lbl_8031D710,
    lbl_8031D710, lbl_8031D710, lbl_8031D710, lbl_8031D710,
    lbl_8031D710, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031D738, lbl_8031D738, lbl_8031D738,
    lbl_8031D738, RaceScene_GetPerspFovyForCup_data_8040AC94, RaceScene_GetPerspFovyForCup_data_8040ACC4, (void *)0x43340000,
    (void *)0x00000000, lbl_8031D710, lbl_8031D710, lbl_8031D710,
    lbl_8031D710, lbl_8031D710, lbl_8031D710, lbl_8031D710,
    lbl_8031D710, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031D738, lbl_8031D738, lbl_8031D738,
    lbl_8031D738, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031DBD8, RaceScene_GetPerspFovyForCup_data_8040B5FC, RaceScene_GetPerspFovyForCup_data_8040B5FC,
    RaceScene_GetPerspFovyForCup_data_8040B5FC, RaceScene_GetPerspFovyForCup_data_8040B5FC, lbl_8031D7B8, lbl_8031D7B8,
    lbl_8031D7B8, lbl_8031D7B8, RaceScene_GetPerspFovyForCup_data_8040AC94, RaceScene_GetPerspFovyForCup_data_8040ACC4,
    (void *)0x43340000, (void *)0x00000000, lbl_8031D7B8, lbl_8031D7B8,
    lbl_8031D7B8, lbl_8031D7B8, lbl_8031D7B8, lbl_8031D7B8,
    lbl_8031D7B8, lbl_8031D7B8, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031DBEC, lbl_8031DBEC,
    lbl_8031DBEC, lbl_8031DBEC, RaceScene_GetPerspFovyForCup_data_8040AC94, RaceScene_GetPerspFovyForCup_data_8040ACC4,
    (void *)0x43340000, (void *)0x00000000, lbl_8031D7B8, lbl_8031D7B8,
    lbl_8031D7B8, lbl_8031D7B8, lbl_8031D7B8, lbl_8031D7B8,
    lbl_8031D7B8, lbl_8031D7B8, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031DBEC, lbl_8031DBEC,
    lbl_8031DBEC, lbl_8031DBEC, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031DC04, RaceScene_GetPerspFovyForCup_data_8040B644,
    RaceScene_GetPerspFovyForCup_data_8040B644, RaceScene_GetPerspFovyForCup_data_8040B644, RaceScene_GetPerspFovyForCup_data_8040B644, lbl_8031D890,
    lbl_8031D890, lbl_8031D890, lbl_8031D890, RaceScene_GetPerspFovyForCup_data_8040AD84,
    RaceScene_GetPerspFovyForCup_data_8040ADB4, (void *)0x43340000, (void *)0x00000000, lbl_8031D890,
    lbl_8031D890, lbl_8031D890, lbl_8031D890, lbl_8031D890,
    lbl_8031D890, lbl_8031D890, lbl_8031D890, RaceScene_GetPerspFovyForCup_data_8040AE74,
    RaceScene_GetPerspFovyForCup_data_8040AE74, RaceScene_GetPerspFovyForCup_data_8040AE74, RaceScene_GetPerspFovyForCup_data_8040AE74, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, lbl_8031D8BC,
    lbl_8031D8BC, lbl_8031D8BC, lbl_8031D8BC, RaceScene_GetPerspFovyForCup_data_8040AD84,
    RaceScene_GetPerspFovyForCup_data_8040ADB4, (void *)0x43340000, (void *)0x00000000, lbl_8031D890,
    lbl_8031D890, lbl_8031D890, lbl_8031D890, lbl_8031D890,
    lbl_8031D890, lbl_8031D890, lbl_8031D890, RaceScene_GetPerspFovyForCup_data_8040AE74,
    RaceScene_GetPerspFovyForCup_data_8040AE74, RaceScene_GetPerspFovyForCup_data_8040AE74, RaceScene_GetPerspFovyForCup_data_8040AE74, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, lbl_8031D8BC,
    lbl_8031D8BC, lbl_8031D8BC, lbl_8031D8BC, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, lbl_8031DC04,
    RaceScene_GetPerspFovyForCup_data_8040B644, RaceScene_GetPerspFovyForCup_data_8040B644, RaceScene_GetPerspFovyForCup_data_8040B644, RaceScene_GetPerspFovyForCup_data_8040B644,
    lbl_8031D890, lbl_8031D890, lbl_8031D890, lbl_8031D890,
    RaceScene_GetPerspFovyForCup_data_8040AD84, RaceScene_GetPerspFovyForCup_data_8040ADB4, (void *)0x43340000, (void *)0x00000000,
    lbl_8031D890, lbl_8031D890, lbl_8031D890, lbl_8031D890,
    lbl_8031D890, lbl_8031D890, lbl_8031D890, lbl_8031D890,
    RaceScene_GetPerspFovyForCup_data_8040AE74, RaceScene_GetPerspFovyForCup_data_8040AE74, RaceScene_GetPerspFovyForCup_data_8040AE74, RaceScene_GetPerspFovyForCup_data_8040AE74,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031D8BC, lbl_8031D8BC, lbl_8031D8BC, lbl_8031D8BC,
    RaceScene_GetPerspFovyForCup_data_8040AD84, RaceScene_GetPerspFovyForCup_data_8040ADB4, (void *)0x43340000, (void *)0x00000000,
    lbl_8031D890, lbl_8031D890, lbl_8031D890, lbl_8031D890,
    lbl_8031D890, lbl_8031D890, lbl_8031D890, lbl_8031D890,
    RaceScene_GetPerspFovyForCup_data_8040AE74, RaceScene_GetPerspFovyForCup_data_8040AE74, RaceScene_GetPerspFovyForCup_data_8040AE74, RaceScene_GetPerspFovyForCup_data_8040AE74,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031D8BC, lbl_8031D8BC, lbl_8031D8BC, lbl_8031D8BC,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    lbl_8031DC18, RaceScene_GetPerspFovyForCup_data_8040B68C, RaceScene_GetPerspFovyForCup_data_8040B68C, RaceScene_GetPerspFovyForCup_data_8040B68C,
    RaceScene_GetPerspFovyForCup_data_8040B68C, lbl_8031D968, lbl_8031D968, lbl_8031D968,
    lbl_8031D968, RaceScene_GetPerspFovyForCup_data_8040B0D4, RaceScene_GetPerspFovyForCup_data_8040B104, (void *)0x43340000,
    (void *)0x00000000, lbl_8031DC30, lbl_8031DC30, lbl_8031DC30,
    lbl_8031DC30, lbl_8031DC30, lbl_8031DC30, lbl_8031DC30,
    lbl_8031DC30, RaceScene_GetPerspFovyForCup_data_8040B11C, RaceScene_GetPerspFovyForCup_data_8040B11C, RaceScene_GetPerspFovyForCup_data_8040B11C,
    RaceScene_GetPerspFovyForCup_data_8040B11C, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031DC4C, lbl_8031DC4C, lbl_8031DC4C,
    lbl_8031DC4C, RaceScene_GetPerspFovyForCup_data_8040B0EC, RaceScene_GetPerspFovyForCup_data_8040B110, (void *)0x00000000,
    (void *)0x00000000, lbl_8031DC30, lbl_8031DC30, lbl_8031DC30,
    lbl_8031DC30, lbl_8031DC30, lbl_8031DC30, lbl_8031DC30,
    lbl_8031DC30, RaceScene_GetPerspFovyForCup_data_8040B11C, RaceScene_GetPerspFovyForCup_data_8040B11C, RaceScene_GetPerspFovyForCup_data_8040B11C,
    RaceScene_GetPerspFovyForCup_data_8040B11C, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031DC4C, lbl_8031DC4C, lbl_8031DC4C,
    lbl_8031DC4C, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, lbl_8031DC18, RaceScene_GetPerspFovyForCup_data_8040B68C, RaceScene_GetPerspFovyForCup_data_8040B68C,
    RaceScene_GetPerspFovyForCup_data_8040B68C, RaceScene_GetPerspFovyForCup_data_8040B68C, lbl_8031D968, lbl_8031D968,
    lbl_8031D968, lbl_8031D968, RaceScene_GetPerspFovyForCup_data_8040B0D4, RaceScene_GetPerspFovyForCup_data_8040B104,
    (void *)0x43340000, (void *)0x00000000, lbl_8031DC30, lbl_8031DC30,
    lbl_8031DC30, lbl_8031DC30, lbl_8031DC30, lbl_8031DC30,
    lbl_8031DC30, lbl_8031DC30, RaceScene_GetPerspFovyForCup_data_8040B11C, RaceScene_GetPerspFovyForCup_data_8040B11C,
    RaceScene_GetPerspFovyForCup_data_8040B11C, RaceScene_GetPerspFovyForCup_data_8040B11C, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031DC4C, lbl_8031DC4C,
    lbl_8031DC4C, lbl_8031DC4C, RaceScene_GetPerspFovyForCup_data_8040B0EC, RaceScene_GetPerspFovyForCup_data_8040B110,
    (void *)0x00000000, (void *)0x00000000, lbl_8031DC30, lbl_8031DC30,
    lbl_8031DC30, lbl_8031DC30, lbl_8031DC30, lbl_8031DC30,
    lbl_8031DC30, lbl_8031DC30, RaceScene_GetPerspFovyForCup_data_8040B11C, RaceScene_GetPerspFovyForCup_data_8040B11C,
    RaceScene_GetPerspFovyForCup_data_8040B11C, RaceScene_GetPerspFovyForCup_data_8040B11C, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000, lbl_8031DC4C, lbl_8031DC4C,
    lbl_8031DC4C, lbl_8031DC4C, (void *)0x00000000, (void *)0x00000000,
    (void *)0x00000000, (void *)0x00000000,
};
float lbl_8040DDB4[2][4] = {
    {65535.0f, 3000.0f, 65535.0f, 65535.0f},
    {65535.0f, 3000.0f, 65535.0f, 65535.0f},
};
float lbl_8040DDD4[2][4] = {
    {5000.0f, 5000.0f, 5000.0f, 5000.0f},
    {5000.0f, 5000.0f, 5000.0f, 5000.0f},
};
float lbl_8040DDF4[2][4] = {
    {65535.0f, 65535.0f, 65535.0f, 65535.0f},
    {65535.0f, 65535.0f, 65535.0f, 65535.0f},
};
float lbl_8040DE14[2][4] = {
    {65535.0f, 65535.0f, 65535.0f, 65535.0f},
    {65535.0f, 65535.0f, 65535.0f, 65535.0f},
};
float lbl_8040DE34[2][4] = {
    {65535.0f, 65535.0f, 65535.0f, 65535.0f},
    {65535.0f, 65535.0f, 65535.0f, 65535.0f},
};
float lbl_8040DE54[2][4] = {
    {65535.0f, 65535.0f, 65535.0f, 65535.0f},
    {65535.0f, 65535.0f, 65535.0f, 65535.0f},
};
float lbl_8040DE74[2][4] = {
    {65535.0f, 65535.0f, 65535.0f, 65535.0f},
    {65535.0f, 65535.0f, 65535.0f, 65535.0f},
};

float RaceScene_GetPerspFovyForCup(void)
{
    if (g_cupId < 0) {
        return lbl_806D4790;
    }
    if (g_longRoundFlag < 0) {
        return lbl_806D4790;
    }
    if (g_courseVariantIdx < 0) {
        return lbl_806D4790;
    }
    switch (g_cupId) {
    case 2:
        return lbl_8040DDB4[g_longRoundFlag][g_courseVariantIdx];
    case 3:
        return lbl_8040DDD4[g_longRoundFlag][g_courseVariantIdx];
    case 4:
        return lbl_8040DDF4[g_longRoundFlag][g_courseVariantIdx];
    case 5:
        return lbl_8040DE14[g_longRoundFlag][g_courseVariantIdx];
    case 6:
        return lbl_8040DE34[g_longRoundFlag][g_courseVariantIdx];
    }
    return lbl_806D4794;
}
