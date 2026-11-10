
/* sdata symbols referenced from asm */
/* .rodata 0x802EE028..0x802EE320 belongs to this file (pool_audit): Draw
 * addresses its menu strings from the section start (lbl_802EE028 + 0x220..).
 * Objects used by name from .data/.sdata keep their lbl_ names. */
extern const char lbl_806D2A54[], lbl_806D2AAC[], lbl_806D2AB4[], lbl_806D2ABC[], lbl_806D2AC4[], lbl_806D2ACC[], lbl_806D2AD4[], lbl_806D2ADC[], lbl_806D2AE4[], lbl_806D2AEC[], lbl_806D2AF4[], lbl_806D2AFC[], lbl_806D2B04[], lbl_806D2B08[], lbl_806D2B10[], lbl_806D2B18[], lbl_806D2B20[], lbl_806D2B28[], lbl_806D2B30[];
#pragma force_active on
const char lbl_802EE028[] = "50cc URA";
const char lbl_802EE034[] = "100cc URA";
const char lbl_802EE040[] = "150cc URA";
const char lbl_802EE04C[] = "take RANDOM";
const char lbl_802EE058[] = "take GOLD";
const char lbl_802EE064[] = "LOCATION TEST";
const char lbl_802EE074[] = "DONKEY KONG";
const char lbl_802EE080[] = "Ms.PAC-MAN";
const char lbl_802EE08C[] = "Take Standard";
const char lbl_802EE09C[] = "Take All";
const char lbl_802EE0A8[] = "CMD RESET";
const char lbl_802EE0B4[] = "GET CARD";
const char lbl_802EE0C0[] = "READ CARD ONLY";
const char lbl_802EE0D0[] = "READ CARD AND DATA";
const char lbl_802EE0E4[] = "WRITE DATA";
const char lbl_802EE0F0[] = "CLEANING";
const char lbl_802EE0FC[] = "cp::Eject";
const char lbl_802EE108[] = "cp::Insert";
const char lbl_802EE114[] = "cp::Read";
const char lbl_802EE120[] = "cp::Write";
const char lbl_802EE12C[] = "cp::Print";
const char *const lbl_802EE138[18] = {
    lbl_802EE0A8, lbl_806D2AAC, lbl_806D2AB4, lbl_806D2ABC, lbl_802EE0B4, lbl_806D2AC4, lbl_802EE0C0, lbl_802EE0D0, lbl_802EE0E4, lbl_806D2ACC, lbl_806D2AD4, lbl_806D2ADC, lbl_802EE0F0, lbl_802EE0FC, lbl_802EE108, lbl_802EE114, lbl_802EE120, lbl_802EE12C
};
const char lbl_802EE180[] = "MARIO KART";
const char lbl_802EE18C[] = "YAMASITA";
const char lbl_802EE198[] = "YAMAZAKI";
const char lbl_802EE1A4[] = "1234567890";
const char lbl_802EE1B0[] = "ABCDEFGHIJ";
const char lbl_802EE1BC[] = "BLUE BACK";
const char lbl_802EE1C8[] = "ALPHA BLEND";
const char lbl_802EE1D4[] = "flying disc";
const char *const lbl_802EE1E0[20] = {
    lbl_802EE180, lbl_806D2AE4, lbl_802EE18C, lbl_806D2AEC, lbl_806D2AF4, lbl_802EE198, lbl_806D2A54, lbl_806D2AFC, lbl_806D2B04, lbl_806D2B08, lbl_806D2B10, lbl_802EE1A4, lbl_802EE1B0, lbl_802EE1BC, lbl_802EE1C8, lbl_806D2B18, lbl_802EE1D4, lbl_806D2B20, lbl_806D2B28, lbl_806D2B30
};
const char lbl_802EE230[] = "clMiyoshi";
const char lbl_802EE23C[] = "clJobRunner";
static const char sMiyTitle[] = "CARD CREATE";
static const char sMiyChr[] = "CHR           %s";
static const char sMiy50[] = "50CC CLEAR    %s";
static const char sMiy100[] = "100CC CLEAR   %s";
static const char sMiy150[] = "150CC CLEAR   %s";
static const char sMiyUsed[] = "USED          %s";
static const char sMiyGold[] = "GOLD          %s";
static const char sMiyLoc[] = "LOCATION TEST %s";
static const char sMiyWins[] = "WINS          %d";
static const char sMiyMilage[] = "MILAGE        %d";
static const char sMiyItem[] = "NORMAL ITEM   %s";
#pragma force_active reset
/* .data 0x803F9E18..0x803F9F2C is this file's too: Draw indexes the name
 * tables from one data base (addi rX, base, 0x24 / 0x0 / 0xC / 0x18 / 0x58). */
extern const char lbl_806D2A28[], lbl_806D2A2C[], lbl_806D2A34[], lbl_806D2A3C[], lbl_806D2A54[], lbl_806D2A5C[], lbl_806D2A64[], lbl_806D2A6C[], lbl_806D2A74[], lbl_806D2A7C[], lbl_806D2A84[], lbl_806D2A8C[], lbl_806D2A94[], lbl_806D2A9C[], lbl_806D2AA4[], lbl_806D2B38[], lbl_806D2B40[], lbl_806D2B48[], lbl_806D2B50[];
extern const char clMiyoshiCardCreate_data_806CEEE0[], clMiyoshiCardCreate_data_806CEEE8[];
asm void clMiyoshiCardCreate_Tick(void);
extern void card_eject_init(), card_eject_state_machine(), card_send_cleaning_cmd_init(),
    card_cleaning_state_machine(), card_send_read_cmd_init_dup_unused(), card_read_state_machine(),
    Sci2Card_WriteTrackData_StartFlow(), Sci2Card_WriteTrackData_PollState();
extern void __dt__11MiyoshiModeFv();
extern void clMiyoshiCardCreate_Draw(void *);
static const char *sMiyCC0[3] = { lbl_806D2A28, lbl_806D2A2C, lbl_802EE028 };
static const char *sMiyCC1[3] = { lbl_806D2A28, lbl_806D2A34, lbl_802EE034 };
static const char *sMiyCC2[3] = { lbl_806D2A28, lbl_806D2A3C, lbl_802EE040 };
static const char *sMiyChara[13] = {
    lbl_806D2A54, lbl_806D2A5C, lbl_806D2A64, lbl_806D2A6C, lbl_806D2A74, lbl_806D2A7C, lbl_802EE074, lbl_806D2A84, lbl_806D2A8C, lbl_802EE080, lbl_806D2A94, lbl_806D2A9C, lbl_806D2AA4
};
int clMiyoshiCardCreate_Tick_data_803F9E70[16] = { 0, 4, 9, 14, 19, 24, 29, 34, 39, 44, 49, 59, 69, 79, 89, 99 };
struct MiyoshiCardCmd { void (*init)(); void (*poll)(); const char *name; };
struct MiyoshiCardCmd lbl_803F9EB0[4] = {
    { card_eject_init, card_eject_state_machine, lbl_806D2B38 },
    { card_send_cleaning_cmd_init, card_cleaning_state_machine, lbl_806D2B40 },
    { card_send_read_cmd_init_dup_unused, card_read_state_machine, lbl_806D2B48 },
    { Sci2Card_WriteTrackData_StartFlow, Sci2Card_WriteTrackData_PollState, lbl_806D2B50 },
};
const void *clMiyoshiCardCreate_data_803F9EE0[3] = { clMiyoshiCardCreate_data_806CEEE0, 0, 0 };
const void *__vt__11MiyoshiMode[5] = { clMiyoshiCardCreate_data_806CEEE8, 0, (void *)clMiyoshiCardCreate_Tick,
    (void *)clMiyoshiCardCreate_Draw, (void *)__dt__11MiyoshiModeFv };
static void *jumptable_803F9F00[11] = {
    (char *)clMiyoshiCardCreate_Tick + 0xBC, (char *)clMiyoshiCardCreate_Tick + 0xD8, (char *)clMiyoshiCardCreate_Tick + 0xF4, (char *)clMiyoshiCardCreate_Tick + 0x110, (char *)clMiyoshiCardCreate_Tick + 0x12C, (char *)clMiyoshiCardCreate_Tick + 0x148, (char *)clMiyoshiCardCreate_Tick + 0x164, (char *)clMiyoshiCardCreate_Tick + 0x180, (char *)clMiyoshiCardCreate_Tick + 0x19C, (char *)clMiyoshiCardCreate_Tick + 0x1B8, (char *)clMiyoshiCardCreate_Tick + 0x1D4
};
/* Only observed lifetime/layout: 4B mode, 44B state, 216B display context. */
#pragma cplusplus on
void *operator new(unsigned long);
void operator delete(void *);
struct MiyoshiState;
struct MiyoshiDisplay;
extern "C" {
extern MiyoshiState *clMiyoshiCardCreate_bss_806D10D8;
extern MiyoshiDisplay *lbl_806D1880;
void MemoryManager_TimedFree(void *);
void *fn_801DB68C(void *, short);
}
struct MiyoshiState {
    int status, selection, counter, character, cc0, cc1, cc2;
    unsigned char flag0, flag1, flag2, reserved1f;
    int kart, points;
    unsigned char flag3;
    MiyoshiState() {
        character = 0; cc0 = 0; cc1 = 0; cc2 = 0;
        flag0 = 0; flag1 = 0; flag2 = 0;
        kart = 0; points = 0; selection = 0; flag3 = 0;
        status = 0; counter = 0;
    }
};
struct MiyoshiBase {
    MiyoshiBase();
    virtual void key();
    virtual ~MiyoshiBase();
};
struct MiyoshiMode : MiyoshiBase {
    virtual void key();
    MiyoshiMode() { clMiyoshiCardCreate_bss_806D10D8 = new MiyoshiState; }
    ~MiyoshiMode();
};
#if 1
/* Draw complete draft: 3 approaches exhausted; 84.63% best, no gain claimed. */
extern "C" {
void DrawText(void *, int, int, int, float, const char *, ...);
void DisplayContext_Flush(void *);
extern const char *const clMiyoshiCardCreate_Draw_data_806CEEC0[2];
extern const char *const clMiyoshiCardCreate_Draw_data_806CEEC8[2];
extern const char *const clMiyoshiCardCreate_Draw_data_806CEED0[2];
extern const char *const clMiyoshiCardCreate_Draw_data_806CEED8[2];
extern const float lbl_806D2B58;
extern const char lbl_806D2B5C[8];
extern const char lbl_806D2B64[4];
}
struct MiyoshiDisplay {
    char observedStorage[216];
    MiyoshiDisplay();
};
struct MiyoshiTables {
    const char *cc0[3], *cc1[3], *cc2[3], *characters[13], *karts[17];
};
static inline MiyoshiDisplay *Miyoshi_GetContext() {
    if (lbl_806D1880 == 0) lbl_806D1880 = new MiyoshiDisplay;
    return lbl_806D1880;
}
extern "C" void clMiyoshiCardCreate_Draw(void *) {
    MiyoshiState *state;
    MiyoshiDisplay *context;
    context = Miyoshi_GetContext();
    context = lbl_806D1880;
    state = clMiyoshiCardCreate_bss_806D10D8;
    DrawText(context,14,24,7,lbl_806D2B58,sMiyTitle);
    DrawText(context,28,72,7,lbl_806D2B58,sMiyChr,sMiyChara[state->character]);
    DrawText(context,28,96,7,lbl_806D2B58,sMiy50,sMiyCC0[state->cc0]);
    DrawText(context,28,120,7,lbl_806D2B58,sMiy100,sMiyCC1[state->cc1]);
    DrawText(context,28,144,7,lbl_806D2B58,sMiy150,sMiyCC2[state->cc2]);
    DrawText(context,28,168,7,lbl_806D2B58,sMiyUsed,clMiyoshiCardCreate_Draw_data_806CEEC0[state->flag0!=0]);
    DrawText(context,28,192,7,lbl_806D2B58,sMiyGold,clMiyoshiCardCreate_Draw_data_806CEEC8[state->flag1!=0]);
    DrawText(context,28,216,7,lbl_806D2B58,sMiyLoc,clMiyoshiCardCreate_Draw_data_806CEED0[state->flag2!=0]);
    DrawText(context,28,240,7,lbl_806D2B58,sMiyWins,clMiyoshiCardCreate_Tick_data_803F9E70[state->kart]);
    int points;
    if (state->points<=0) points=0; else points=state->points*100-1;
    DrawText(context,28,264,7,lbl_806D2B58,sMiyMilage,points);
    DrawText(context,28,288,7,lbl_806D2B58,sMiyItem,clMiyoshiCardCreate_Draw_data_806CEED8[state->flag3!=0]);
    DrawText(context,28,312,7,lbl_806D2B58,lbl_806D2B5C);
    int y;
    if(state->selection==10) y=312; else y=(state->selection+3)*24;
    state->counter &= 31;
    if (state->counter<24) DrawText(context,14,y,7,lbl_806D2B58,lbl_806D2B64);
    DisplayContext_Flush(Miyoshi_GetContext());
}
#pragma cplusplus off

#endif




#pragma cplusplus on
#if 0
/* Tick complete draft: 97.87%; generated jump-table data is outside this TU. */
/* Virtual slot +0x20 is InputObj_IsPressed (r3 self, r4 mask, normalized byte). */
struct MiyoshiInput {
    virtual void destroy(short);
    virtual void update();
    virtual float steering();
    virtual float defaultFloat();
    virtual float accelerator();
    virtual float brake();
    virtual unsigned char isPressed(unsigned int);
};
extern "C" {
void *GetInputManager();
MiyoshiInput *InputMgr_GetPlayer(void *, unsigned int);
int WrapInRange(int, int, int);
void PlayerData_Construct(void *,int,int,int,int,unsigned char,unsigned char,unsigned char,int,int,unsigned char);
unsigned char card_save_trigger(unsigned char);
unsigned char card_rw_state_machine();
unsigned char CardSave_Tick();
void card_rw_kick_state_machine();
extern unsigned int g_playerData[];
}
extern "C" int clMiyoshiCardCreate_Tick(void *) {
    MiyoshiInput *input=InputMgr_GetPlayer(GetInputManager(),0);
    unsigned char confirm=input->isPressed(1);
    unsigned char next=input->isPressed(128);
    MiyoshiState *state=clMiyoshiCardCreate_bss_806D10D8;
    if(state->status==0) {
        if(next==1) state->selection=WrapInRange(state->selection+1,0,10);
        else if(confirm==1) {
            switch(state->selection) {
            case 0: state->character=WrapInRange(state->character+1,0,12); break;
            case 1: state->cc0=WrapInRange(state->cc0+1,0,2); break;
            case 2: state->cc1=WrapInRange(state->cc1+1,0,2); break;
            case 3: state->cc2=WrapInRange(state->cc2+1,0,2); break;
            case 4: state->flag0=state->flag0!=1; break;
            case 5: state->flag1=state->flag1!=1; break;
            case 6: state->flag2=state->flag2!=1; break;
            case 7: state->kart=WrapInRange(state->kart+1,0,16); break;
            case 8: state->points=WrapInRange(state->points+1,0,40); break;
            case 9: state->flag3=state->flag3!=1; break;
            case 10:
                int points;
                if(state->points<=0) points=0; else points=state->points*100-1;
                PlayerData_Construct(g_playerData,state->character,state->cc0,state->cc1,state->cc2,
                    state->flag0,state->flag1,state->flag2,clMiyoshiCardCreate_Tick_data_803F9E70[state->kart],points,state->flag3);
                card_save_trigger(0); state->status=1; break;
            }
        }
    } else if(state->status==1) {
        if(CardSave_Tick()==1) { state->status=2; card_rw_kick_state_machine(); }
    } else if(state->status==2) {
        if(card_rw_state_machine()==1) state->status=3;
    }
    ++state->counter;
    int result;
    if(state->status==3) result=-4; else result=-2;
    return result;
}
#endif
#pragma cplusplus off
/* === extracted from auto_clMiyoshiCardCreate_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CardSave_Tick();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void PlayerData_Construct();
extern void WrapInRange();
extern void card_rw_kick_state_machine();
extern void card_rw_state_machine();
extern void card_save_trigger();

/* --- extern decls: sda21-referenced data --- */

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int g_playerData[];

/* --- function index (1 fns, .text 0x80061394..0x80061668) ---
 * [  0] 0x80061394 size:0x2D4   global clMiyoshiCardCreate_Tick
 */

/* --- forward decls --- */
asm void clMiyoshiCardCreate_Tick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clMiyoshiCardCreate_Tick[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clMiyoshiCardCreate_Tick = {
    (void *)&clMiyoshiCardCreate_Tick, 0x000002D4, (void *)extab_clMiyoshiCardCreate_Tick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clMiyoshiCardCreate_Tick(void) { /* 0x80061394 size:0x2D4 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    mr r31, r3
    li r4, 0x1
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    mr r30, r3
    mr r3, r31
    lwz r12, 0x0(r31)
    li r4, 0x80
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    lwz r31, clMiyoshiCardCreate_bss_806D10D8(r13)
    lwz r0, 0x0(r31)
    cmpwi r0, 0x0
    bne clMiyoshiCardCreate_Tick_L_800615E4
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne clMiyoshiCardCreate_Tick_L_80061420
    lwz r3, 0x4(r31)
    li r4, 0x0
    li r5, 0xa
    addi r3, r3, 0x1
    bl WrapInRange
    stw r3, 0x4(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    clMiyoshiCardCreate_Tick_L_80061420:
    clrlwi r0, r30, 24
    cmplwi r0, 0x1
    bne clMiyoshiCardCreate_Tick_L_8006162C
    lwz r0, 0x4(r31)
    cmplwi r0, 0xa
    bgt clMiyoshiCardCreate_Tick_L_8006162C
    lis r3, jumptable_803F9F00@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_803F9F00@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    lwz r3, 0xc(r31)
    li r4, 0x0
    li r5, 0xc
    addi r3, r3, 0x1
    bl WrapInRange
    stw r3, 0xc(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lwz r3, 0x10(r31)
    li r4, 0x0
    li r5, 0x2
    addi r3, r3, 0x1
    bl WrapInRange
    stw r3, 0x10(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lwz r3, 0x14(r31)
    li r4, 0x0
    li r5, 0x2
    addi r3, r3, 0x1
    bl WrapInRange
    stw r3, 0x14(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lwz r3, 0x18(r31)
    li r4, 0x0
    li r5, 0x2
    addi r3, r3, 0x1
    bl WrapInRange
    stw r3, 0x18(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lbz r4, 0x1c(r31)
    subfic r3, r4, 0x1
    subi r0, r4, 0x1
    or r0, r3, r0
    srwi r0, r0, 31
    stb r0, 0x1c(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lbz r4, 0x1d(r31)
    subfic r3, r4, 0x1
    subi r0, r4, 0x1
    or r0, r3, r0
    srwi r0, r0, 31
    stb r0, 0x1d(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lbz r4, 0x1e(r31)
    subfic r3, r4, 0x1
    subi r0, r4, 0x1
    or r0, r3, r0
    srwi r0, r0, 31
    stb r0, 0x1e(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lwz r3, 0x20(r31)
    li r4, 0x0
    li r5, 0x10
    addi r3, r3, 0x1
    bl WrapInRange
    stw r3, 0x20(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lwz r3, 0x24(r31)
    li r4, 0x0
    li r5, 0x28
    addi r3, r3, 0x1
    bl WrapInRange
    stw r3, 0x24(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lbz r4, 0x28(r31)
    subfic r3, r4, 0x1
    subi r0, r4, 0x1
    or r0, r3, r0
    srwi r0, r0, 31
    stb r0, 0x28(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lwz r0, 0x24(r31)
    cmpwi r0, 0x0
    bgt clMiyoshiCardCreate_Tick_L_8006157C
    li r5, 0x0
    b clMiyoshiCardCreate_Tick_L_80061584
    clMiyoshiCardCreate_Tick_L_8006157C:
    mulli r3, r0, 0x64
    subi r5, r3, 0x1
    clMiyoshiCardCreate_Tick_L_80061584:
    lwz r0, 0x20(r31)
    lis r4, clMiyoshiCardCreate_Tick_data_803F9E70@ha
    lis r3, g_playerData@ha
    slwi r0, r0, 2
    addi r4, r4, clMiyoshiCardCreate_Tick_data_803F9E70@l
    lwzx r0, r4, r0
    addi r3, r3, g_playerData@l
    stw r0, 0x8(r1)
    stw r5, 0xc(r1)
    lbz r0, 0x28(r31)
    stw r0, 0x10(r1)
    lwz r4, 0xc(r31)
    lwz r5, 0x10(r31)
    lwz r6, 0x14(r31)
    lwz r7, 0x18(r31)
    lbz r8, 0x1c(r31)
    lbz r9, 0x1d(r31)
    lbz r10, 0x1e(r31)
    bl PlayerData_Construct
    li r3, 0x0
    bl card_save_trigger
    li r0, 0x1
    stw r0, 0x0(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    clMiyoshiCardCreate_Tick_L_800615E4:
    cmpwi r0, 0x1
    bne clMiyoshiCardCreate_Tick_L_8006160C
    bl CardSave_Tick
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne clMiyoshiCardCreate_Tick_L_8006162C
    li r0, 0x2
    stw r0, 0x0(r31)
    bl card_rw_kick_state_machine
    b clMiyoshiCardCreate_Tick_L_8006162C
    clMiyoshiCardCreate_Tick_L_8006160C:
    cmpwi r0, 0x2
    bne clMiyoshiCardCreate_Tick_L_8006162C
    bl card_rw_state_machine
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne clMiyoshiCardCreate_Tick_L_8006162C
    li r0, 0x3
    stw r0, 0x0(r31)
    clMiyoshiCardCreate_Tick_L_8006162C:
    lwz r3, 0x8(r31)
    addi r0, r3, 0x1
    stw r0, 0x8(r31)
    lwz r0, 0x0(r31)
    cmpwi r0, 0x3
    bne clMiyoshiCardCreate_Tick_L_8006164C
    li r3, -0x4
    b clMiyoshiCardCreate_Tick_L_80061650
    clMiyoshiCardCreate_Tick_L_8006164C:
    li r3, -0x2
    clMiyoshiCardCreate_Tick_L_80061650:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}




#pragma cplusplus on
MiyoshiMode::~MiyoshiMode() {
    MemoryManager_TimedFree((void *)clMiyoshiCardCreate_bss_806D10D8);
    clMiyoshiCardCreate_bss_806D10D8 = 0;
    /* Counterintuitive but authoritative: call when the pointer is NULL. */
    if (lbl_806D1880 == 0) {
        fn_801DB68C((void *)lbl_806D1880, 1);
        lbl_806D1880 = 0;
    }
}
extern "C" MiyoshiMode *clMiyoshiCardCreate_Ctor() { return new MiyoshiMode; }
#pragma cplusplus off


