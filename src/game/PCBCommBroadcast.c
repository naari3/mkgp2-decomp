/* Complete NonMatching reconstruction: 88.45247% in the bounded three-approach
 * batch. Typed wire overlays preserve all writes and the signed ring remainder.
 * Only observed layouts are modeled; no storage or complete runtime class is
 * owned. Original object remains the linked fallback. */
struct BroadcastInput {
    virtual ~BroadcastInput();
    virtual void Update();
    virtual float Steering();
    virtual float DefaultFloat();
    virtual float Accelerator();
    virtual float Brake();
    virtual int IsPressed(unsigned int);
    virtual int IsHeld(unsigned int);
    virtual unsigned int PressedMasked(unsigned int);
};
struct HeaderByte {
    unsigned char active:1, role:3, host:1, flag2:1, low:2;
    void SetActive(unsigned char value) { active = value; }
    void SetRole(int value) { role = value; }
    void SetHost(unsigned char value) { host = value; }
    void SetFlag2(unsigned char value) { flag2 = value; }
};
struct StateByte {
    unsigned char sceneLow:1, raceEnded:1, flag5:1, unused4:1;
    unsigned char active:1, scratch:1, scratchNext:1, flag0:1;
    void SetActive(unsigned char value) { active = value; }
    void SetFlag5(unsigned char value) { flag5 = value; }
    void SetRaceEnded(unsigned char value) { raceEnded = value; }
    void SetScratch(unsigned char value) { scratch = value; }
    void SetScratchNext(unsigned char value) { scratchNext = value; }
    void SetFlag0(unsigned char value) { flag0 = value; }
};
struct StatusByte {
    unsigned char flag7:1, card:1, confirmed:1, display:1;
    unsigned char unused3:1, flag2:1, host:1, displayLow:1;
    void SetFlag7(unsigned char value) { flag7 = value; }
    void SetCard(unsigned char value) { card = value; }
    void SetConfirmed(unsigned char value) { confirmed = value; }
    void SetDisplay(unsigned char value) { display = value; }
    void SetFlag2(unsigned char value) { flag2 = value; }
    void SetHost(unsigned char value) { host = value; }
    void SetDisplayLow(unsigned char value) { displayLow = value; }
};
union BroadcastHeader {
    struct { HeaderByte first; unsigned char second; StateByte state; StatusByte status; } bytes;
    struct { unsigned int upper:9, scene:8, lower:15; } word;
};
struct DisplayByte { unsigned char character:4, buffer:4; };
struct RoundByte { unsigned char round:7, reverse:1; };
struct ClassByte { unsigned char mode:2, cc:2, allCleared:1, kart:2, low:1; };
union ClassHeader {
    struct { ClassByte first; unsigned char second; } bytes;
    struct { unsigned short upper:7, wins:4, low:5; } half;
};
struct BroadcastSlot {
    BroadcastHeader header;
    DisplayByte display;
    RoundByte round;
    ClassHeader classes;
    unsigned char pad8[4];
    float value;
    unsigned short counters[3];
    unsigned short name[6];
    unsigned short score0, score1;
    unsigned char titles[3];
    unsigned char pad29[3];
    float steering, accelerator, brake;
    unsigned int buttons;
    unsigned char pad3C[0x12];
    unsigned char queued;
    unsigned char tail[5];
};
struct PlayerSnapshot {
    unsigned short name[6];
    unsigned char padC[2];
    unsigned short score0, score1;
    unsigned char pad12[0x189];
    unsigned char title0, title1, card;
    unsigned char pad19E[0x13];
    unsigned char title2;
    unsigned char tail[0x2A];
};
extern "C" {
extern BroadcastSlot lbl_805A60C4;
extern PlayerSnapshot g_playerData;
extern unsigned char lbl_80598A60[0x2A];
extern unsigned char g_confirmFlag, g_isCommHost, lbl_806D12A0, lbl_806D12AD;
extern unsigned char g_raceEnded, lbl_806D12C4, lbl_806D12AE, g_isPcbHost;
extern unsigned char lbl_806D1264[3];
extern int g_localPcbRole, lbl_806D129C, g_currentSceneState;
extern int lbl_806D11A4, lbl_806D11A8, lbl_806CF12C, lbl_806D12BC;
extern int g_reverseRoundFlag, g_characterId, g_ccClass, g_kartVariant;
extern int g_consecutiveWinsTier, g_ringReadIdx, lbl_806D11A0;
extern float lbl_806D12A8;
extern float lbl_806D3148;
extern BroadcastInput** GetInputManager(void);
extern BroadcastInput* InputMgr_GetPlayer(BroadcastInput**, unsigned int);
extern unsigned char GetVBlankFlag(void), VBlankValue_Get(void);
extern int GetDisplayBufferIndex(void);
extern int fn_801D5C88(PlayerSnapshot*, int);

static inline float QuantizeBroadcastInput(float value)
{
    return (float)(int)(lbl_806D3148 * value) / lbl_806D3148;
}

void PCBComm_BuildBroadcastSlot(void)
{
    BroadcastSlot* slot = &lbl_805A60C4;
    BroadcastInput* input = InputMgr_GetPlayer(GetInputManager(), 0);
    unsigned char card = 1;
    unsigned char confirmed = 1;
    if (g_playerData.card == 0) card = 0;
    if (!GetVBlankFlag() || VBlankValue_Get() == 1) confirmed = 0;
    if (g_confirmFlag == 0) confirmed = 0;
    slot->header.bytes.first.SetActive(1);
    slot->header.bytes.first.SetRole(g_localPcbRole);
    slot->header.bytes.first.SetHost(g_isCommHost);
    slot->header.bytes.first.SetFlag2(lbl_806D12A0);
    slot->header.bytes.state.SetActive(1);
    slot->header.bytes.state.SetFlag5(lbl_806D129C);
    slot->header.word.scene = g_currentSceneState;
    slot->header.bytes.status.SetFlag7(lbl_806D12AD);
    slot->header.bytes.status.SetCard(card);
    slot->header.bytes.status.SetConfirmed(confirmed);
    slot->header.bytes.status.SetDisplay(lbl_80598A60[0x23]);
    slot->header.bytes.state.SetRaceEnded(g_raceEnded);
    slot->header.bytes.state.SetScratch(lbl_806D11A4);
    slot->header.bytes.state.SetScratchNext(lbl_806D11A8);
    slot->header.bytes.state.SetFlag0(lbl_806D12AE);
    slot->header.bytes.status.SetFlag2(lbl_806D12C4);
    slot->header.bytes.status.SetHost(g_isPcbHost);
    slot->header.bytes.status.SetDisplayLow(lbl_80598A60[0x29]);
    slot->display.buffer = GetDisplayBufferIndex();
    slot->display.character = (unsigned char)g_characterId;
    slot->round.round = lbl_806CF12C;
    slot->round.reverse = (unsigned char)g_reverseRoundFlag;
    slot->classes.bytes.first.mode = lbl_806D12BC;
    slot->classes.bytes.first.cc = g_ccClass;
    slot->classes.bytes.first.allCleared = fn_801D5C88(&g_playerData, g_ccClass);
    slot->classes.bytes.first.kart = g_kartVariant;
    slot->classes.half.wins = g_consecutiveWinsTier;
    slot->value = lbl_806D12A8;
    slot->counters[0] = lbl_806D1264[0];
    slot->counters[1] = lbl_806D1264[1];
    slot->counters[2] = lbl_806D1264[2];
    slot->score0 = g_playerData.score0;
    slot->score1 = g_playerData.score1;
    slot->titles[0] = g_playerData.title0;
    slot->titles[1] = g_playerData.title1;
    slot->titles[2] = g_playerData.title2;
    for (int i = 0; i < 6; ++i) slot->name[i] = g_playerData.name[i];
    slot->steering = QuantizeBroadcastInput(input->Steering());
    slot->accelerator = QuantizeBroadcastInput(input->Accelerator());
    slot->brake = QuantizeBroadcastInput(input->Brake());
    slot->buttons = input->PressedMasked(0xE7FF);
    unsigned char count = 0;
    int read = g_ringReadIdx;
    int write = lbl_806D11A0;
    while ((read + count) % 64 != write) ++count;
    slot->queued = count;
}
}
