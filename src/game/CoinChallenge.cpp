/*
 * Coin challenge mini game (clCGameYI), .text 0x802143E4..0x802151C8.
 * One TU: Draw, Update, destructor, constructor; it owns the coin course
 * tables, the vtable and the RTTI of clCGameYI / clCGame / clJobRunner.
 * Flags: GC/2.6, -inline deferred (functions below are in reverse address
 * order), -RTTI on, -rostr.
 * Open: the float literals 0x806DAE20..0x806DAE58 belong to this TU too, but
 * the target pool has 1.0f before 0.1f while Update loads 0.1f first, so
 * .sdata2 is only owned up to the "clCGame" RTTI name (splits.txt).
 * Merged 2026-11-09 from CoinChallengeRender.cpp, CoinChallengeUpdate.cpp,
 * anon_80214B3C.cpp and CoinChallengeInit.cpp.
 */
#include "game/types/size_t.h"
#include "game/singleton.h"

void *operator new(size_t size);
void operator delete(void *p) throw();

/* --- owned .data 0x804ECC20..0x804EDA78 (tools/own_data.py) --- */
#pragma force_active on
extern "C" unsigned int CoinChallenge_data_804ECC20[304] = { 0xC407639F, 0x00000000, 0xC587C4E5, 0x00000001, 0xC405AD79, 0x00000000, 0xC58F30B2, 0x00000001, 0xC40722AA, 0x00000000, 0xC5967A0A, 0x00000001, 0xC40A636D, 0x00000000, 0xC59E5989, 0x00000001, 0xC4136BD4, 0x00000000, 0xC5A5E8BE, 0x00000001, 0xC425DC54, 0x00000000, 0xC5AC84F0, 0x00000001, 0xC43D329B, 0x00000000, 0xC5B35510, 0x00000001, 0xC456FA18, 0x00000000, 0xC5B9DADF, 0x00000001, 0xC470D07B, 0x00000000, 0xC5C0B92F, 0x00000001, 0xC484572B, 0x00000000, 0xC5C7B808, 0x00000001, 0xC48F7ED1, 0x00000000, 0xC5CECDDD, 0x00000001, 0xC496B1AA, 0x00000000, 0xC5D657A2, 0x00000001, 0xC49C152F, 0x00000000, 0xC5DD6433, 0x00000001, 0xC4A0DE7F, 0x00000000, 0xC5E4EE48, 0x00000001, 0xC4A60019, 0x00000000, 0xC5EC3DD7, 0x00000001, 0xC4AB6979, 0x00000000, 0xC5F3B94E, 0x00000001, 0xC4B08B4C, 0x00000000, 0xC5FB0B6A, 0x00000001, 0xC4B5C981, 0x00000000, 0xC601361E, 0x00000001, 0xC4BA4698, 0x00000000, 0xC604AA08, 0x00000001, 0xC4BFC79E, 0x00000000, 0xC6083B52, 0x00000001, 0xC4C501BA, 0x00000000, 0xC60BD062, 0x00000001, 0xC4CA4F9E, 0x00000000, 0xC60F68F2, 0x00000001, 0xC4CF7BF8, 0x00000000, 0xC612F87B, 0x00000001, 0xC4D42A14, 0x00000000, 0xC61686A7, 0x00000001, 0xC4D8D4E5, 0x00000000, 0xC61A46CB, 0x00000001, 0xC4DE0B0A, 0x00000000, 0xC61DD129, 0x00000001, 0xC4E449DB, 0x00000000, 0xC6211FAE, 0x00000001, 0xC4EE5BBE, 0x00000000, 0xC6249FA4, 0x00000001, 0xC4FD3D81, 0x00000000, 0xC627CD33, 0x00000001, 0xC5076179, 0x00000000, 0xC62AA5A4, 0x00000001, 0xC510D05E, 0x00000000, 0xC62D6EAE, 0x00000001, 0xC51A63DB, 0x00000000, 0xC6305AC3, 0x00000001, 0xC523C51B, 0x00000000, 0xC6332285, 0x00000001, 0xC52D7EE5, 0x00000000, 0xC63601A4, 0x00000001, 0xC5375CCD, 0x00000000, 0xC638EE52, 0x00000001, 0xC541090A, 0x00000000, 0xC63BD31F, 0x00000001, 0xC54A89C3, 0x00000000, 0xC63EAE7B, 0x00000001, 0xC553C8D1, 0x00000000, 0xC64179C3, 0x00000001, 0xC55D458D, 0x00000000, 0xC644457B, 0x00000001, 0xC567210E, 0x00000000, 0xC6473BAE, 0x00000001, 0xC56F7FF4, 0x00000000, 0xC64AB08F, 0x00000001, 0xC5754A4A, 0x00000000, 0xC64E4DEC, 0x00000001, 0xC57922F6, 0x00000000, 0xC651CC66, 0x00000001, 0xC57A6073, 0x00000000, 0xC65581F6, 0x00000001, 0xC57A04C1, 0x00000000, 0xC659571F, 0x00000001, 0xC5780BC7, 0x00000000, 0xC65D08B8, 0x00000001, 0xC57586EE, 0x00000000, 0xC660E285, 0x00000001, 0xC572883D, 0x00000000, 0xC6649DCD, 0x00000001, 0xC56FD560, 0x00000000, 0xC6684B3D, 0x00000001, 0xC56D1189, 0x00000000, 0xC66BD571, 0x00000001, 0xC56A40EE, 0x00000000, 0xC66F9BD7, 0x00000001, 0xC567669C, 0x00000000, 0xC67355B8, 0x00000001, 0xC5647A35, 0x00000000, 0xC6771148, 0x00000001, 0xC561D191, 0x00000000, 0xC67A8B5C, 0x00000001, 0xC55F2DBA, 0x00000000, 0xC67E13B8, 0x00000001, 0xC55C044E, 0x00000000, 0xC6810ADC, 0x00000001, 0xC5593AB0, 0x00000000, 0xC682D6F1, 0x00000001, 0xC55664A0, 0x00000000, 0xC684AC4D, 0x00000001, 0xC5537046, 0x00000000, 0xC68681D2, 0x00000001, 0xC55018E9, 0x00000000, 0xC68856A4, 0x00000001, 0xC54C59EC, 0x00000000, 0xC68A3EBD, 0x00000001, 0xC5484533, 0x00000000, 0xC68C19F1, 0x00000001, 0xC5428C04, 0x00000000, 0xC68DCC43, 0x00000001, 0xC53B4E14, 0x00000000, 0xC68F67C8, 0x00000001, 0xC5303F37, 0x00000000, 0xC690AC80, 0x00000001, 0xC5235E6F, 0x00000000, 0xC691D51A, 0x00000001, 0xC51747CB, 0x00000000, 0xC692C280, 0x00000001, 0xC50AF796, 0x00000000, 0xC693AC57, 0x00000001, 0xC4FC66C1, 0x00000000, 0xC694A276, 0x00000001, 0xC4E2B1E3, 0x00000000, 0xC6959671, 0x00000001, 0xC4C97E77, 0x00000000, 0xC69686B3, 0x00000001, 0xC4B04852, 0x00000000, 0xC697771A, 0x00000001, 0xC4052291, 0x00000000, 0xC566E30E, 0x00000001, 0xC4050A8F, 0x00000000, 0xC5759C56, 0x00000001, 0xC405FAED, 0x00000000, 0xC5812A87, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000002 };
extern "C" unsigned int CoinChallenge_data_804ED0E0[304] = { 0xC4008048, 0x00000000, 0xC588C9D9, 0x00000001, 0xC4024B70, 0x00000000, 0xC58FFAF2, 0x00000001, 0xC405124B, 0x00000000, 0xC596F8F0, 0x00000001, 0xC408B771, 0x00000000, 0xC59E15AA, 0x00000001, 0xC4154D36, 0x00000000, 0xC5A5995C, 0x00000001, 0xC4256649, 0x00000000, 0xC5AD3E81, 0x00000001, 0xC487E88B, 0x00000000, 0xC5D6D2E9, 0x00000001, 0xC48A0D48, 0x00000000, 0xC5D6B583, 0x00000001, 0xC483451F, 0x00000000, 0xC5D0629C, 0x00000001, 0xC4E5C48B, 0x00000000, 0xC61F6114, 0x00000001, 0xC4E58277, 0x00000000, 0xC6205666, 0x00000001, 0xC4E7ABDF, 0x00000000, 0xC62038EC, 0x00000001, 0xC48B7B12, 0x00000000, 0xC5D8D8F0, 0x00000001, 0xC485B2D9, 0x00000000, 0xC5D17ADF, 0x00000001, 0xC48653CF, 0x00000000, 0xC5D4D6E7, 0x00000001, 0xC484E687, 0x00000000, 0xC5D31CD1, 0x00000001, 0xC48719CB, 0x00000000, 0xC5D30417, 0x00000001, 0xC48886A0, 0x00000000, 0xC5D4A396, 0x00000001, 0xC4894385, 0x00000000, 0xC5D8F08F, 0x00000001, 0xC4E71AB8, 0x00000000, 0xC6214CC3, 0x00000001, 0xC4E9A68F, 0x00000000, 0xC621261F, 0x00000001, 0xC4ECF019, 0x00000000, 0xC622129A, 0x00000001, 0xC48390EE, 0x00000000, 0xC5D1A17B, 0x00000001, 0xC4EA4F64, 0x00000000, 0xC6222AD7, 0x00000001, 0xC4EFB442, 0x00000000, 0xC622DF1F, 0x00000001, 0xC4ED2AB8, 0x00000000, 0xC6230FD7, 0x00000001, 0xC4E3445A, 0x00000000, 0xC61F8A0A, 0x00000001, 0xC4F2A73B, 0x00000000, 0xC623ADF6, 0x00000001, 0xC4EF5733, 0x00000000, 0xC623DF85, 0x00000001, 0xC57860F2, 0x00000000, 0xC65F170A, 0x00000001, 0xC579BD71, 0x00000000, 0xC65F3085, 0x00000001, 0xC5777991, 0x00000000, 0xC661DF00, 0x00000001, 0xC57779D7, 0x00000000, 0xC66000A4, 0x00000001, 0xC578F506, 0x00000000, 0xC66017F6, 0x00000001, 0xC5762429, 0x00000000, 0xC661D000, 0x00000001, 0xC575AF9A, 0x00000000, 0xC663DB1F, 0x00000001, 0xC57470A4, 0x00000000, 0xC663D471, 0x00000001, 0xC557B408, 0x00000000, 0xC67ECE66, 0x00000001, 0xC5562419, 0x00000000, 0xC67EBD7B, 0x00000001, 0xC5554B7D, 0x00000000, 0xC680D094, 0x00000001, 0xC553C56D, 0x00000000, 0xC680CF05, 0x00000001, 0xC5782D9A, 0x00000000, 0xC660EE0A, 0x00000001, 0xC576AA04, 0x00000000, 0xC662C748, 0x00000001, 0xC55840F6, 0x00000000, 0xC67DFEE1, 0x00000001, 0xC556D360, 0x00000000, 0xC67FD029, 0x00000001, 0xC55625DB, 0x00000000, 0xC68054C8, 0x00000001, 0xC554AB1F, 0x00000000, 0xC6813FAE, 0x00000001, 0xC55403AE, 0x00000000, 0xC681AD9A, 0x00000001, 0xC576C9FC, 0x00000000, 0xC660E085, 0x00000001, 0xC57538D9, 0x00000000, 0xC662BF3D, 0x00000001, 0xC5568112, 0x00000000, 0xC67DE866, 0x00000001, 0xC5553D71, 0x00000000, 0xC67FC5D7, 0x00000001, 0xC55491F0, 0x00000000, 0xC6804838, 0x00000001, 0xC5531DC7, 0x00000000, 0xC6813961, 0x00000001, 0xC552770E, 0x00000000, 0xC681A129, 0x00000001, 0xC55008CD, 0x00000000, 0xC641D185, 0x00000001, 0xC551F306, 0x00000000, 0xC6426BAE, 0x00000001, 0xC553052F, 0x00000000, 0xC6423B48, 0x00000001, 0xC55125D7, 0x00000000, 0xC6418B0A, 0x00000001, 0xC5540506, 0x00000000, 0xC6431600, 0x00000001, 0xC5552579, 0x00000000, 0xC642DF00, 0x00000001, 0xC4984E04, 0x00000000, 0xC69D7376, 0x00000001, 0xC49ACAFA, 0x00000000, 0xC69CF805, 0x00000001, 0xC498139E, 0x00000000, 0xC69CFC33, 0x00000001, 0xC49ADF1B, 0x00000000, 0xC69D73AE, 0x00000001, 0xC49B1DAA, 0x00000000, 0xC69DE405, 0x00000001, 0xC49824EE, 0x00000000, 0xC69DEBB3, 0x00000001, 0xC49B0160, 0x00000000, 0xC69E700A, 0x00000001, 0xC49ACED1, 0x00000000, 0xC69EE229, 0x00000001, 0xC498087B, 0x00000000, 0xC69EEB00, 0x00000001, 0xC4982CBC, 0x00000000, 0xC69E6BDC, 0x00000001, 0xC3F83E28, 0x00000000, 0xC5654775, 0x00000001, 0xC3FB65EA, 0x00000000, 0xC5744498, 0x00000001, 0xC3FE5320, 0x00000000, 0xC5819EFA, 0x00000001, 0xC43765E7, 0x00000000, 0xC5B3C1B2, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000002 };
extern "C" unsigned int CoinChallenge_data_804ED5A0[304] = { 0xC3DA1A82, 0x00000000, 0xC5902727, 0x00000001, 0xC3DAD090, 0x00000000, 0xC598CE0E, 0x00000001, 0xC3F6E88A, 0x00000000, 0xC5A033FC, 0x00000001, 0xC408F4FC, 0x00000000, 0xC5A6D9A4, 0x00000001, 0xC41E745A, 0x00000000, 0xC5ACE3BA, 0x00000001, 0xC439B93E, 0x00000000, 0xC5B410F2, 0x00000001, 0xC45601DE, 0x00000000, 0xC5BA37F4, 0x00000001, 0xC474B162, 0x00000000, 0xC5C09A29, 0x00000001, 0xC4873FD7, 0x00000000, 0xC5C7B808, 0x00000001, 0xC492EA77, 0x00000000, 0xC5CF0498, 0x00000001, 0xC49AF839, 0x00000000, 0xC5D657A2, 0x00000001, 0xC49F80D5, 0x00000000, 0xC5DD6433, 0x00000001, 0xC4A36F3B, 0x00000000, 0xC5E4EE48, 0x00000001, 0xC4A4D4DD, 0x00000000, 0xC5EC7491, 0x00000001, 0xC4A5A4F6, 0x00000000, 0xC5F3B94E, 0x00000001, 0xC4A7D21D, 0x00000000, 0xC5FB4225, 0x00000001, 0xC4AA57A6, 0x00000000, 0xC600FCA6, 0x00000001, 0xC4AEA5CB, 0x00000000, 0xC604C910, 0x00000001, 0xC4B426D1, 0x00000000, 0xC6082BCE, 0x00000001, 0xC4BA7148, 0x00000000, 0xC60BBD23, 0x00000001, 0xC4C1FF54, 0x00000000, 0xC60F7D9D, 0x00000001, 0xC4C9B581, 0x00000000, 0xC613082B, 0x00000001, 0xC4D158EE, 0x00000000, 0xC61673D2, 0x00000001, 0xC4DA1204, 0x00000000, 0xC61A391D, 0x00000001, 0xC4E26A98, 0x00000000, 0xC61DC37B, 0x00000001, 0xC4EAC22D, 0x00000000, 0xC6210E3D, 0x00000001, 0xC4F505D3, 0x00000000, 0xC624645C, 0x00000001, 0xC5007548, 0x00000000, 0xC627BB14, 0x00000001, 0xC506F404, 0x00000000, 0xC62AC100, 0x00000001, 0xC50ECA66, 0x00000000, 0xC62DD048, 0x00000001, 0xC5177A6A, 0x00000000, 0xC631398F, 0x00000001, 0xC51FEC00, 0x00000000, 0xC6346AE1, 0x00000001, 0xC52794BC, 0x00000000, 0xC6370900, 0x00000001, 0xC53150E5, 0x00000000, 0xC63A3A00, 0x00000001, 0xC53B8004, 0x00000000, 0xC63D4329, 0x00000001, 0xC542E0E5, 0x00000000, 0xC63F355C, 0x00000001, 0xC54DB73F, 0x00000000, 0xC641DEB8, 0x00000001, 0xC5566C46, 0x00000000, 0xC643D4A4, 0x00000001, 0xC55FCCBC, 0x00000000, 0xC6460A85, 0x00000001, 0xC56B385E, 0x00000000, 0xC648B5A4, 0x00000001, 0xC572E6B0, 0x00000000, 0xC64AEC7B, 0x00000001, 0xC5775DDF, 0x00000000, 0xC64D281F, 0x00000001, 0xC57B533F, 0x00000000, 0xC65001B8, 0x00000001, 0xC57DD933, 0x00000000, 0xC652D7AE, 0x00000001, 0xC5784AEE, 0x00000000, 0xC65E66CD, 0x00000001, 0xC5749F58, 0x00000000, 0xC66237D7, 0x00000001, 0xC570DCA4, 0x00000000, 0xC6658685, 0x00000001, 0xC56CDE04, 0x00000000, 0xC668E9CD, 0x00000001, 0xC56942C5, 0x00000000, 0xC66BF47B, 0x00000001, 0xC564EA62, 0x00000000, 0xC66FBE48, 0x00000001, 0xC560FABC, 0x00000000, 0xC6732C3D, 0x00000001, 0xC55E448F, 0x00000000, 0xC676AED7, 0x00000001, 0xC55BE1DF, 0x00000000, 0xC67A2FF6, 0x00000001, 0xC559E825, 0x00000000, 0xC67DA71F, 0x00000001, 0xC55864A4, 0x00000000, 0xC680C50A, 0x00000001, 0xC55724C9, 0x00000000, 0xC6828BEC, 0x00000001, 0xC555CCC5, 0x00000000, 0xC6840F71, 0x00000001, 0xC5545CE5, 0x00000000, 0xC685C6CD, 0x00000001, 0xC552BD06, 0x00000000, 0xC6877AE1, 0x00000001, 0xC5515954, 0x00000000, 0xC688D757, 0x00000001, 0xC54F8768, 0x00000000, 0xC68A641F, 0x00000001, 0xC54CD0E5, 0x00000000, 0xC68B8E38, 0x00000001, 0xC5307950, 0x00000000, 0xC68FA68F, 0x00000001, 0xC52866F2, 0x00000000, 0xC69050D7, 0x00000001, 0xC51F28FA, 0x00000000, 0xC6911129, 0x00000001, 0xC513D348, 0x00000000, 0xC691EC48, 0x00000001, 0xC5077D9E, 0x00000000, 0xC692C3C8, 0x00000001, 0xC4F7893F, 0x00000000, 0xC69395A9, 0x00000001, 0xC4E39831, 0x00000000, 0xC6945929, 0x00000001, 0xC4CCFC29, 0x00000000, 0xC6954FF6, 0x00000001, 0xC4BBDD79, 0x00000000, 0xC696555C, 0x00000001, 0xC4AE5CAC, 0x00000000, 0xC697891F, 0x00000001, 0xC4A50F23, 0x00000000, 0xC698ED61, 0x00000001, 0xC3DBD8AA, 0x00000000, 0xC588761F, 0x00000001, 0xC3E03C08, 0x00000000, 0xC5818D19, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000002 };
extern "C" int MiniGame_CoinChallenge_Init_data_804EDA60[3][2] = {
    {(int)&CoinChallenge_data_804ECC20, (int)&CoinChallenge_data_804ECC20},
    {(int)&CoinChallenge_data_804ED0E0, (int)&CoinChallenge_data_804ED0E0},
    {(int)&CoinChallenge_data_804ED5A0, (int)&CoinChallenge_data_804ED5A0}
};
#pragma force_active reset

#include "game/types/Vec3.h"
struct SpriteHandle;

struct HsdClassInfo {
    char pad[0x30];
    void (*release)(struct HsdObj *o);
    void (*destroy)(struct HsdObj *o);
};
struct HsdObj {
    HsdClassInfo *info;
    unsigned short ref;
};

struct InputPlayer {
    virtual void slot08();
    virtual void slot0c();
    virtual float steering();
    virtual void slot14();
    virtual float accelerator();
    virtual float brake();
};
#include "game/types/KartDriver.h"
#include "game/types/VObj.h"
struct Scene3D {
    virtual ~Scene3D();
    virtual unsigned char Ready();
    virtual void Render();
};
struct CarObject {
    virtual void Update();
    virtual ~CarObject();
    unsigned char pad[0xF9]; unsigned char fd, fe; unsigned char tail[0x19];
};
struct Camera {
    Camera(int, int, float, float, void *);
    virtual ~Camera();
    unsigned char opaque[0x28];
};
struct WeatherSystem { unsigned char opaque[0x1B4]; WeatherSystem(unsigned char); ~WeatherSystem(); };
struct LakituStart { unsigned char opaque[0x58]; LakituStart(const char *, int, float, float, float); ~LakituStart(); };
struct CourseEnvironment { unsigned char opaque[0x37C]; CourseEnvironment(); ~CourseEnvironment(); };
struct ChallengeGoalCamera { unsigned char opaque[8]; ChallengeGoalCamera(); ~ChallengeGoalCamera(); };
struct HUD { unsigned char opaque[0x80]; HUD(int); ~HUD(); };

extern "C" {
extern VObj *lbl_806D10AC;
extern VObj *lbl_806D10D0;
extern VObj *lbl_806D109C;
extern const unsigned int lbl_806DC1B0;
extern const unsigned int lbl_806DC190;
extern const unsigned int lbl_806DC1B8;
extern unsigned char g_raceEnded, g_lakituStartAnimDone, lbl_806D1290;
extern unsigned char lbl_806D1548[8];
extern float g_raceTimeRemaining;
extern WeatherSystem *g_weatherSystem;
extern void *g_raceCamera;
extern int g_characterId, g_roundIndex, g_ccClass, lbl_806D12BC, lbl_806CF128;

/* Draw */
void clDrawMan_Buckets_Reset(void*);
void clDrawMan_SetMaxClipZ(void*, float);
void TransparentDraw_SortAndDispatch();
void CObj_DebugVizPathFlush(void*);
void fn_8016B0C4();
void KartItem_RenderPipelinedWithEffects(void*, int);
void Object_RenderJObjIfWithinRange(void*);
void CourseEnvironment_RenderObjects_Timed(void*);
void fn_80139810();
void clItemBoxManager_Draw(void*);
void Subsystem36c_DispatchPass2_Timed(void*);
void ItemObjectManager_Render();
void DrawEffect_TickAndCull();
void clDrawMan_EndFrame_NoOp(void*);
void clDrawMan_Buckets_Dispatch(void*);
void Subsystem36c_DispatchPass4_Timed(void*);
void TransitionEffect_RenderPass(void*, int);
void fn_80253448(void*, unsigned int);
void fn_8011F994(int);
void fn_802535D4(void*);
void HSD_StateInvalidate(int);

/* Update */
void *GetRaceContextPtr();
void ItemObjectManager_PerFrameUpdate(void *);
void *GetInputManager();
InputPlayer *InputMgr_GetPlayer(void *, int);
unsigned char IsRaceStarted();
unsigned char NokoNokoChallenge_HandleBrakeInput(void *, int);
void CarObject_ApplyInput(void *, float, float, float, unsigned char);
void CarObject_FrameUpdate(void *, int);
void KartItem_UpdateShadowBillboardAndViewport(void *, void *, int);
void KartMovement_SetSpeedScale(void *, float);
KartDriver *CarObject_GetRenderObj(void *);
void *KartDriver_GetKartRootMtx(void *);
void ChallengeGoalCamera_Update(void *, void *, void *);
void Fog_UpdateFromCourseScene3D();
void LakituStart_UpdateCountdown(void *);
void CourseEnvironment_UpdateAndCullZones_Timed(void *);
void fn_8013A534();
int Clamp_Int(int, int, int);
void SpriteLayer_SetResource(void *, int);
unsigned char IsCardValid();
int CObj_LoadProjMatrix(void *, Vec3 *);
int CObj_ApplyScissor(void *, Vec3 *);
void ItemObjectManager_Update();
#ifdef __MWERKS__
void VfxSlotMgr_Update(Vec3, Vec3);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void VfxSlotMgr_Update(Vec3 *, Vec3 *);
static inline void VfxSlotMgr_Update_ByValue(Vec3 a0, Vec3 a1) { VfxSlotMgr_Update(&a0, &a1); }
#define VfxSlotMgr_Update VfxSlotMgr_Update_ByValue
#endif
void fn_80253FD8(void *, float);
float CarObject_CalcSpeedRatio(void *);
void fn_80253EBC(void *, float);
float KartItem_GetCurrentSpeedWithBonus(void *);
void fn_80253EC0(void *, float);
void HUD_FrameUpdate(void *);
void fn_8011F804(void *, float, float);
void SpriteHandle_RecomputeCull(void *);
void TransitionEffect_Tick(void *);
void SetCoinCount(int);
int NokoNokoChallenge_CalcResultText(void *, int, int);
void fn_80253C74(void *, int, int, int);
void KartMovement_ResetOnGoal(void *);
void KartMovement_ResetOnTimeout(void *);
void NokoNokoChallenge_SaveResult(void *, int, unsigned int);
int Object_SetByte10_Return1(void *, int);
unsigned char fn_80253C40(void *);
int NokoNokoChallenge_TransitionToResult(void *);
void fn_8016B32C(void *);

/* destructor */
void *SetActiveCamera(int a, void *cam);
void SetPlayerCarObject(void *car);
void SpriteHandle_Destroy(SpriteHandle *h);
void fn_8013A6F8(void);
void ItemObjectManager_Reset(void);
void VfxSlotMgr_Shutdown(void);
void ClRomTable_PurgeAll(void);
void RankingTable_Init(void *ctx);
void SceneDrawList_Reset(void);
void fn_80121210(void);
void SetResourceLoadingFlag(unsigned char on);
void clRom_PurgeAll(void);

/* constructor */
void* DrawManager_GetOrCreate();
void DMAChannelManager_Init(); void* TransitionEffect_GetOrCreate();
void SoundChannels_ClearAll(); void ItemObjectManager_Init();
void CourseObjectManager_Init(); void SetReverseRoundFlag(unsigned char);
void* GetCourseDataPtr(); HsdObj* HSD_LObjLoadDesc(void*);
void ProcessSystemTick(int);
void* SoundDriver_GetOrCreate(void*);
int GetStartPosition(int,float*,float*,float*); float GetCourseStartYaw();
int GetDisplayBufferIndex();
struct CICar;
void CarObject_Init(CICar*,int,int,int,int,unsigned char,int,int,unsigned char,float,float,float);
const char** GetKartModelNameEntry(int,int);
struct CIScene;
void Scene3D_Init(CIScene*,const char*);
void Scene3D_GetCameraPos(Scene3D*,float*,float*);
int Scene3D_SetupProjection(Scene3D*,float,float);
void HUD_RegisterOverlay(HUD*,int,int); void SetCourseScene3D(Scene3D*);
int MiniGame_GetTimerValue(); void PreloadEffectResources(int);
const float* MiniGame_GetCourseData(); int* NokoNokoChallenge_GetCoinDivisor();
void CoinSystem_Init(int,int);
void CourseObjects_Activate();
}

/* Construction views: the kart and the scene are built in place by their
 * init functions, without a vtable store of their own. */
struct CICar {
    unsigned char opaque[0x118];
    CICar(const float* x,const float* z) {
        int character=g_characterId;
        float yaw=GetCourseStartYaw();
        int display=GetDisplayBufferIndex();
        CarObject_Init(this,display,character,0,0,1,6,0,0,*x,*z,yaw);
    }
};
struct CIScene {
    unsigned char opaque[0x3084];
    CIScene() { Scene3D_Init(this,*GetKartModelNameEntry(g_characterId,-1)); }
};

/* Coin counter sprites: [4] tens digit, [5] ones digit. */
struct CoinIcons {
    SpriteHandle *icons[9];
    unsigned char exiting;
    float slide;
    CoinIcons(int goal);
    ~CoinIcons() {
        for (int i = 0; i < 9; i++) {
            SpriteHandle_Destroy(icons[i]);
        }
        fn_80121210();
    }
};

#include "game/types/clJobRunner.h"
struct clCGame : clJobRunner {
    float phase;
    clCGame() { phase = 0.0f; }
    virtual ~clCGame();
};
struct clCGameYI : clCGame {
    /* 0x08 */ CarObject *car;
    /* 0x0C */ LakituStart *lakitu;
    /* 0x10 */ CourseEnvironment *env;
    /* 0x14 */ Scene3D *scene;
    /* 0x18 */ ChallengeGoalCamera *goalCam;
    /* 0x1C */ Camera *camera;
    /* 0x20 */ HsdObj *lights;
    /* 0x24 */ int x24;
    /* 0x28 */ HUD *hud;
    /* 0x2C */ CoinIcons *icons;
    /* 0x30 */ unsigned char active, won;
    /* 0x34 */ int endDelay, resultFrames, targetCoins, awards, divisor;
    clCGameYI();
    virtual void Draw();
    virtual int Update();
    virtual ~clCGameYI();
};

/* Also read by ScoreDisplay_Init (anon_802151C8.cpp). */
extern "C" extern const float CoinChallenge_rodata_803C3DD8[18];
extern const float CoinChallenge_rodata_803C3DD8[18] = {
    320.0f, 71.25f, 250.0f, 69.25f, 320.0f, 33.25f, 285.0f, 71.25f, 315.0f, 69.25f,
    345.0f, 69.25f, 365.0f, 76.25f, 380.0f, 83.25f, 398.0f, 83.25f
};

static inline void* PresentOrNull(void* p) {
    if (!p) p = 0;
    return p;
}

/* -inline deferred: functions are emitted in reverse source order. */
clCGameYI::clCGameYI() {
    DrawManager_GetOrCreate(); SetResourceLoadingFlag(0); DMAChannelManager_Init();
    TransitionEffect_GetOrCreate(); SoundChannels_ClearAll(); ItemObjectManager_Init();
    CourseObjectManager_Init(); SetReverseRoundFlag(0);
    env=new CourseEnvironment;
    lights=HSD_LObjLoadDesc(GetCourseDataPtr());
    camera=new Camera(256,256,1000.0f,0.1f,lights);
    SetActiveCamera(0,camera); g_raceCamera=camera; ProcessSystemTick(0);
    RankingTable_Init(GetRaceContextPtr()); lbl_806D12BC=0; SoundDriver_GetOrCreate(0);
    float x,z; GetStartPosition(0,&x,0,&z);
    car=(CarObject*)new CICar(&x,&z); car->fd=0; car->fe=0;
    {KartDriver*r=CarObject_GetRenderObj(car); r->visible_238=1;}
    {KartDriver*r=CarObject_GetRenderObj(car); r->forceDraw=1;}
    SetPlayerCarObject(car);
    lakitu=new LakituStart("jyugemu_start.dat",0,0.0f,0.0f,0.0f);
    scene=(Scene3D*)new CIScene; goalCam=new ChallengeGoalCamera; ProcessSystemTick(0);
    float projectionX,projectionZ;
    Scene3D_GetCameraPos(scene,&projectionX,&projectionZ);
    projectionX+=10.0f; Scene3D_SetupProjection(scene,projectionX,projectionZ);
    hud=new HUD(0);
    HUD_RegisterOverlay(hud,6,0); HUD_RegisterOverlay(hud,17,0);
    HUD_RegisterOverlay(hud,18,0); HUD_RegisterOverlay(hud,14,0);
    g_lakituStartAnimDone=0; SetCourseScene3D(scene); g_raceEnded=0;
    lbl_806CF128=1; active=0; won=0; endDelay=0; resultFrames=0;
    g_raceTimeRemaining=(float)MiniGame_GetTimerValue();
    PreloadEffectResources(9); PreloadEffectResources(10);
    targetCoins=(int)*MiniGame_GetCourseData(); icons=new CoinIcons(targetCoins);
    CoinIcons* display=icons;
    SpriteLayer_SetResource(display->icons[5],0x14BA);
    SpriteLayer_SetResource(display->icons[4],0x1ECD);
    awards=0; divisor=*NokoNokoChallenge_GetCoinDivisor();
    int highRound=(g_roundIndex>=4) ? 1 : 0;
    CoinSystem_Init(MiniGame_CoinChallenge_Init_data_804EDA60[g_ccClass][highRound],1);
    CourseObjects_Activate();
    if(!g_weatherSystem) g_weatherSystem=new WeatherSystem(1);
    SetResourceLoadingFlag(1);
}

static inline int RefDec(HsdObj *o) {
    int ret = o->ref == (unsigned short)-1;
    if (ret) {
        return ret;
    }
    return o->ref-- == 0;
}

static inline void ObjUnref(HsdObj *o) {
    if (o == 0) {
        return;
    }
    if (RefDec(o)) {
        if (o != 0) {
            o->info->release(o);
            o->info->destroy(o);
        }
    }
}

clCGameYI::~clCGameYI() {
    if (g_weatherSystem != 0) {
        delete g_weatherSystem;
        g_weatherSystem = 0;
    }
    SetActiveCamera(0, 0);
    delete scene;
    delete lakitu;
    delete goalCam;
    SetPlayerCarObject(0);
    delete car;
    g_raceCamera = 0;
    if (camera != 0) {
        delete camera;
    }
    if (lights != 0) {
        ObjUnref(lights);
    }
    delete env;
    delete icons;
    delete hud;
    fn_8013A6F8();
    ItemObjectManager_Reset();
    VfxSlotMgr_Shutdown();
    ClRomTable_PurgeAll();
    RankingTable_Init(GetRaceContextPtr());
    delete lbl_806D10D0;
    lbl_806D10D0 = 0;
    SceneDrawList_Reset();
    delete lbl_806D109C;
    lbl_806D109C = 0;
    SetResourceLoadingFlag(0);
    clRom_PurgeAll();
    delete lbl_806D10AC;
    lbl_806D10AC = 0;
}

static inline void *getTransition() {
    return SINGLETON_INSTANCE(lbl_806D109C);
}

static inline void SetCoinIcons(CoinIcons *sprites, int shown) {
    if (shown > 99) shown = 99;
    int tens = shown / 10;
    SpriteLayer_SetResource(sprites->icons[5], shown % 10 + 0x14ba);
    short tensResource = 0x1ecd;
    if (tens > 0) tensResource = tens + 0x14ba;
    SpriteLayer_SetResource(sprites->icons[4], tensResource);
}

static inline void UpdateCoinIcons(CoinIcons *sprites) {
    SpriteHandle **cursor;
    int i;
    if (sprites->exiting != 0) {
        if (sprites->slide >= 1.0f) goto sprites_done;
        float accelerator = 640.0f;
        const float *positions = CoinChallenge_rodata_803C3DD8;
        cursor = sprites->icons;
        sprites->slide += 0.1f;
        for (int j = 0; j < 9; ++j, positions += 2, ++cursor)
            fn_8011F804(*cursor, accelerator * sprites->slide + positions[0], positions[1]);
    }
    {
        for (i = 0; i < 9; ++i, sprites = (CoinIcons *)((char *)sprites + 4))
            SpriteHandle_RecomputeCull(sprites->icons[0]);
    }
sprites_done:
    return;
}

int clCGameYI::Update() {
    int before;
    int after;
    InputPlayer *input;
    float accelerator, brake;
    Vec3 projection, scissor;
    if (active == 0) active = 1;
    ItemObjectManager_PerFrameUpdate(GetRaceContextPtr());
    if (g_raceEnded != 1) {
        input = InputMgr_GetPlayer(GetInputManager(), 0);
        if (lbl_806D1290 == 0) accelerator = input->accelerator();
        else accelerator = 0.8f;
        brake = input->brake();
        int holding = 0;
        if (accelerator < 0.1f && brake < 0.1f && IsRaceStarted()) holding = 1;
        if (NokoNokoChallenge_HandleBrakeInput(this, holding) == 1) accelerator = 1.0f;
        CarObject_ApplyInput(car, input->steering(), accelerator, brake, IsRaceStarted());
        CarObject_FrameUpdate(car, 0);
        KartItem_UpdateShadowBillboardAndViewport(car, scene, 0);
    } else {
        CarObject_ApplyInput(car, 0.0f, 0.0f, 0.0f, 1);
        KartMovement_SetSpeedScale(car, 0.2f);
        CarObject_FrameUpdate(car, 0);
        if (endDelay > 0) KartItem_UpdateShadowBillboardAndViewport(car, scene, 0);
        else ChallengeGoalCamera_Update(goalCam, scene, KartDriver_GetKartRootMtx(CarObject_GetRenderObj(car)));
    }
    Fog_UpdateFromCourseScene3D();
    LakituStart_UpdateCountdown(lakitu);
    CourseEnvironment_UpdateAndCullZones_Timed(env);
    before = CarObject_GetRenderObj(car)->coins;
    fn_8013A534();
    if (g_raceEnded != 1) {
        after = CarObject_GetRenderObj(car)->coins;
        SetCoinIcons(icons, Clamp_Int(after, 0, targetCoins));
        if (after != before && IsCardValid() == 1) {
            if (divisor - 1 == after % divisor) lbl_806D1548[0] = 1;
            if (before / divisor != after / divisor) ++awards;
        }
        if (after >= targetCoins) {
            won = 1;
            endDelay = 30;
            g_raceEnded = 1;
        }
    }
    CObj_LoadProjMatrix(scene, &projection);
    CObj_ApplyScissor(scene, &scissor);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(projection, scissor);
    if (IsRaceStarted() == 1 && g_raceEnded != 1) {
        float zero;
        float remaining;
        remaining = g_raceTimeRemaining;
        zero = 0.0f;
        if (remaining >= zero) {
            g_raceTimeRemaining = remaining - 0.016666668f;
            if (g_raceTimeRemaining < zero) {
                g_raceTimeRemaining = zero;
                g_raceEnded = 1;
            }
        }
    }
    fn_80253FD8(hud, g_raceTimeRemaining);
    fn_80253EBC(hud, 100.0f * CarObject_CalcSpeedRatio(car));
    fn_80253EC0(hud, KartItem_GetCurrentSpeedWithBonus(car));
    HUD_FrameUpdate(hud);
    UpdateCoinIcons(icons);
    TransitionEffect_Tick(getTransition());
    if (g_raceEnded == 1) {
        if (endDelay > 0) --endDelay;
        else {
            if (resultFrames == 0) {
                SetCoinCount(awards);
                if (won != 0) {
                    KartDriver *render = CarObject_GetRenderObj(car);
                    fn_80253C74(hud, 1, NokoNokoChallenge_CalcResultText(this, 1, 0), render->coins);
                    KartMovement_ResetOnGoal(CarObject_GetRenderObj(car));
                } else {
                    KartDriver *render = CarObject_GetRenderObj(car);
                    fn_80253C74(hud, 0, NokoNokoChallenge_CalcResultText(this, 0, 0), render->coins);
                    KartMovement_ResetOnTimeout(CarObject_GetRenderObj(car));
                }
                NokoNokoChallenge_SaveResult(this, awards, won);
                icons->exiting = 1;
                Object_SetByte10_Return1(scene, 1);
                g_lakituStartAnimDone = 0;
            } else if (fn_80253C40(hud)) return NokoNokoChallenge_TransitionToResult(this);
            ++resultFrames;
        }
    }
    if (g_weatherSystem) fn_8016B32C(g_weatherSystem);
    return -2;
}

void clCGameYI::Draw() {
    if (active) {
        if (scene->Ready() == 1) {
            clDrawMan_Buckets_Reset(PresentOrNull(lbl_806D10AC));
            clDrawMan_SetMaxClipZ(PresentOrNull(lbl_806D10AC), 2000.0f);
            TransparentDraw_SortAndDispatch();
            CObj_DebugVizPathFlush(scene);
            fn_8016B0C4();
            KartItem_RenderPipelinedWithEffects(car, 0);
            Object_RenderJObjIfWithinRange(lakitu);
            CourseEnvironment_RenderObjects_Timed(env);
            fn_80139810();
            clItemBoxManager_Draw(PresentOrNull(lbl_806D10D0));
            Subsystem36c_DispatchPass2_Timed(env);
            ItemObjectManager_Render();
            DrawEffect_TickAndCull();
            clDrawMan_EndFrame_NoOp(PresentOrNull(lbl_806D10AC));
            clDrawMan_Buckets_Dispatch(PresentOrNull(lbl_806D10AC));
            Subsystem36c_DispatchPass4_Timed(env);
            TransitionEffect_RenderPass(PresentOrNull(lbl_806D109C), 2);
            TransitionEffect_RenderPass(PresentOrNull(lbl_806D109C), 4);
            TransitionEffect_RenderPass(PresentOrNull(lbl_806D109C), 6);
            fn_80253448(hud, lbl_806DC1B0 | lbl_806DC190);
            fn_8011F994(1);
            scene->Render();
        }
        fn_80253448(hud, lbl_806DC1B8);
        fn_802535D4(hud);
        TransitionEffect_RenderPass(PresentOrNull(lbl_806D109C), 1);
        HSD_StateInvalidate(0x7f);
    }
}
