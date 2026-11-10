# clMiyoshiCardCreate-native

Source: Codex worker c24_a10_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 832 B.

Draw 80061054 is native C++ 100%. The old two-instruction residual lwz r3/global + mr r28,r3 was solved by a natural rendering helper boundary: outer Draw calls void Miyoshi_EnsureContext(), then Miyoshi_DrawMenu(lbl_806D1880). The context is a by-value inline parameter, not a caller local copied from a getter result. This emits target lwz r28/global and mr r3,r28 without pragmas or dummy code. Existing TU-owned strings/tables must be used by object name. Compiler emits exact 40-byte Draw EH; original manual Draw extab/index were removed. Constructor bridge __ct__14MiyoshiDisplayFv -> DisplayContext_Init is the only rename addition. Source member reuses canonical DebugDisplayContext, whose size is 216 bytes.

## c24_a10_20261109
Source: Codex worker c24_a10_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 832 B.

Tick best partial: 97.95028%, 720 B. Everything before +0x298 is opcode/register identical, aside from normalized generated jump-table symbol @54 vs jumptable_803F9F00. At +0x298 target lwz r3,counter; addi r0,r3,1; stw; lwz status; cmpwi; bne; li r3,-4; b join; li r3,-2. Source hoists li r3,-2 above counter increment, loads counter in r4, then conditionally assigns -4, eliminating the b join. This is genuine control-flow/size mismatch, not mere coloring. Direct returns and inline result helper produce the same output; no optimization-disabling pragmas used. To retry this draft, replace existing Tick asm and its manual extab/index, remove hand-written jumptable_803F9F00, and let compiler emit its table. Depends on existing MiyoshiState and clMiyoshiCardCreate_Tick_data_803F9E70:

```cpp
#pragma cplusplus on
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
#pragma cplusplus off
```
