/*
 * 0x80157940..0x8015A6E4: list helpers and the scene updates that use them.
 */
#include "game/types/size_t.h"
#pragma cplusplus on

#include "game/types/ListNode.h"

#include "game/types/ListIter.h"

#include "game/types/List.h"

#include "game/types/DataBuf.h"

#include "game/types/DrawObj.h"

#include "game/types/DrawScene.h"

#include "game/types/InputView.h"

#include "game/types/MenuTarget.h"

#include "game/types/MenuTarget.h"

typedef struct OptionMenu {
    char pad0[0x1d];
    unsigned char toggleEnabled;
    char pad1E[2];
    MenuTarget *target;
    char pad24[0x20];
    float blink;
    char pad48[4];
    bool toggle;
    char pad4D[3];
    float fade50;
    float fade54;
    unsigned char sel;
    char pad59[3];
    float blink2;
    char pad60[4];
    int value;
    char pad68[0x1c];
    int scroll;
    int scrollTimer;
} OptionMenu;

/* TOP-END */

extern "C" {
void MemoryManager_TimedFree(void *p);
extern void Alloc();
extern void __throw();
extern void fn_801F7DAC();
void HSD_StateInvalidate(int state);
void fn_8011F994(int i);
void fn_8013D940(int i);
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void RumbleUpdate();
extern void SetRumbleMode();
extern void SetSyncTarget();
int WeatherSystem_PickVariant(int sel);
void clStream_setVolume(int ch, int vol);
extern void fn_8015A6E4();
extern void fn_801678FC();
extern void fn_801698B4();
unsigned char fn_8019083C(int ch);
extern void fn_801932F8();
extern void fn_801FE27C();
extern void fn_801FE348();
extern void fn_801FE390();
extern void fn_801FEF18();
extern unsigned int lbl_806D8390;
extern const float lbl_806D8394;
extern const float lbl_806D8398;
extern const float lbl_806D839C;
extern unsigned int lbl_806D83A0;
extern unsigned int lbl_806D83A4;
extern unsigned int lbl_806D83A8;
extern unsigned int lbl_806D83AC;
extern const float lbl_806D83B0;
extern unsigned int lbl_806D83B4;
extern unsigned int lbl_806D83B8;
extern unsigned int lbl_806D83BC;
extern unsigned int lbl_806D83C0;
void fn_801FE36C(void);
extern struct InputView *g_pInputState;
extern const float lbl_806D83C4;
extern const float lbl_806D83C8;
extern void GetTextureByIdAndLang();
extern void fn_80167744();
extern void fn_80168798();
extern void fn_80168D84();
extern void fn_80169334();
extern void fn_801695E0();
extern void isJapanese();
extern unsigned int lbl_806D83CC;
extern unsigned int lbl_806D83D0;
extern unsigned int lbl_806D83D4;
extern unsigned int lbl_806D83DC;
extern unsigned int lbl_806D83E0;
extern unsigned int lbl_806D83EC;
extern unsigned int lbl_806D83F8;
extern unsigned int lbl_806D83FC;
extern unsigned int lbl_806D8400;
extern unsigned int lbl_806D8404;
extern unsigned int lbl_806D8408;
extern unsigned int lbl_806D840C;
extern unsigned int lbl_806D8410;
extern unsigned int lbl_806D8414;
extern unsigned int lbl_806D8418;
extern unsigned int lbl_806D841C;
extern unsigned int lbl_806D8420;
extern unsigned int lbl_806D8424;
extern unsigned int lbl_806D8428;
extern unsigned int lbl_806D842C;
extern unsigned int lbl_806D8430;
extern unsigned int lbl_806D8434;
extern unsigned int lbl_806D843C;
extern unsigned int lbl_806D8448;
extern unsigned int lbl_80367E24[];
extern unsigned int lbl_80367E38[];
extern void fn_80168404();
extern unsigned int lbl_806D8454;
extern unsigned int lbl_806D8458;
extern unsigned int lbl_806D845C;
extern unsigned int lbl_806D8460;
extern unsigned int lbl_806D8464;
extern unsigned int lbl_806D8470;
extern unsigned int lbl_806D8484;
extern unsigned int lbl_806D8488;
extern unsigned int lbl_806D848C;
extern unsigned int lbl_806D8490;
extern unsigned int lbl_806D8494;
extern unsigned int lbl_806D84A0;
extern unsigned int SceneList_80157EA8_rodata_803678D8[];
extern unsigned int lbl_806D84B0;
extern unsigned int lbl_806D84B4;
extern unsigned int lbl_806D84B8;
extern unsigned int lbl_806D84BC;
extern unsigned int lbl_806D84C0;
extern unsigned int lbl_806D84C4;
extern unsigned int lbl_806D84C8;
extern unsigned int lbl_806D84CC;
extern unsigned int lbl_806D84D0;
extern unsigned int lbl_806D84D4;
extern void Item_GetDescriptorField0();
extern void Item_GetDescriptorField8();
extern void Item_GetDescriptorFieldC();
extern void PlayerData_GetUnlockedItemIdByIndex_U8();
extern void fn_8013BEC8();
extern void fn_80168B90();
extern void fn_8016918C();
extern void fn_8023D938();
extern void fn_8023DAA8();
extern unsigned int lbl_806D84DC;
extern unsigned int lbl_806D84E0;
extern unsigned int lbl_806D84E4;
extern unsigned int lbl_806D84E8;
extern unsigned int lbl_806D84EC;
extern unsigned int lbl_806D84F0;
extern unsigned int lbl_806D84F4;
extern unsigned int lbl_806D84F8;
extern unsigned int lbl_806D84FC;
extern unsigned int lbl_806D8500;
extern unsigned int lbl_806D8504;
extern unsigned int lbl_806D8508;
extern unsigned int lbl_806D850C;
extern unsigned int lbl_806D8510;
extern unsigned int lbl_806D8514;
extern unsigned int lbl_806D8518;
extern unsigned int lbl_806D851C;
extern unsigned int lbl_806D8520;
extern unsigned int lbl_806D8524;
extern unsigned int lbl_806D8528;
extern unsigned int lbl_806D852C;
extern unsigned int lbl_806D8530;
extern unsigned int lbl_806D8534;
extern unsigned int lbl_806D8538;
extern unsigned int lbl_806D853C;
extern unsigned int lbl_806D8540;
extern unsigned int lbl_806D8544;
extern unsigned int lbl_806D8548;
extern unsigned int lbl_806D854C;
extern unsigned int lbl_806D8550;
extern unsigned int lbl_806D8554;
extern unsigned int lbl_806D8558;
extern unsigned int lbl_806D855C;
extern unsigned int lbl_806D8560;
extern unsigned int lbl_806D8564;
extern unsigned int lbl_806D8568;
extern unsigned int lbl_806D856C;
extern unsigned int lbl_806D8570;
void fn_80157940(void);
void fn_801579F0(ListIter *ret, List *l, ListIter *it);
void fn_80157A68(void);
void fn_80157B20(List *l);
void fn_80157B38(void);
void fn_80157BE8(ListIter *ret, List *l, ListIter *it);
void fn_80157C60(void);
void fn_80157D18(List *l);
void fn_80157D30(void);
void fn_80157EA8(List *l);
DataBuf *dtor_80157EC0(DataBuf *self, short flag);
void fn_80157F1C(DrawScene *self);
void fn_80157FB4(void);
void fn_801589BC(OptionMenu *self, int mode);
void fn_80158CE4(void);
void fn_8015915C(void);
void fn_801596D4(void);
void fn_80159BD0(void);

#pragma section R ".extab_user"






#pragma section R ".extabindex_user"






}

static inline InputView *input_state(void)
{
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
}



struct LNode { LNode *prev; LNode *next; };
struct LList { int size; LNode head; };
struct LPos { LNode *n; LPos(LNode *p) : n(p) {} LPos(const LPos &p) : n(p.n) {} };
struct LBuf {
    int pad0;
    void *data;
    char rest[0x94 - 8];
    LBuf(const LBuf &o); /* fn_801F7DAC */
};
struct LValue {
    int a;
    LBuf b;
    LValue(const LValue &v) : a(v.a), b(v.b) {}
};
struct LValueNode { LNode link; LValue value; };
struct LGuard {
    LNode **allocator;
    LValueNode *node;
    LGuard(LNode **a, LValueNode *n) : allocator(a), node(n) {}
    ~LGuard() { if (node) MemoryManager_TimedFree(node); } /* weak copy = dtor_80157EC0 */
    LValueNode *Release() { LValueNode *p = node; node = 0; return p; }
};
inline void *operator new(size_t, void *p) { return p; }
inline void operator delete(void *, void *) {}

static inline LPos LInsert(LList *l, LNode *at, LValueNode *node)
{
    at->prev->next = &node->link;
    node->link.prev = at->prev;
    at->prev = &node->link;
    node->link.next = at;
    ++l->size;
    return LPos(&node->link);
}

extern "C" LPos fn_80157DE0(LList *l, const LPos &pos, const LValue &value)
{
    LGuard guard(&l->head.prev, (LValueNode *)((void *(*)(unsigned long))Alloc)(sizeof(LValueNode)));
    new (&guard.node->value) LValue(value);
    return LInsert(l, pos.n, guard.Release());
}
