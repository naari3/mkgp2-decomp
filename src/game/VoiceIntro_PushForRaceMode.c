/* VoiceIntro_PushForRaceMode: queues the course call, round call and the
 * player's character greeting for the normal race mode intro. */
extern int g_cupId, g_longRoundFlag, g_courseVariantIdx, g_roundIndex;
extern int g_gameMode, g_humanPlayerCount, g_kartStartSlot;
extern unsigned int g_voiceTickCounter;
extern short g_charRaceStartVoiceTable[14], lbl_80496D5C[52];
extern int GetKartSlotCharId(int slot);
extern unsigned char VoiceQueue_Push(short id, short priority, unsigned char flag, unsigned char flush);

static inline short SelectStartVoice(int character, int id) {
    short *normal = g_charRaceStartVoiceTable;
    short *special = lbl_80496D5C;
    short voice = 0x43;
    if (character > -1 && character < 13) {
        if (g_gameMode == 2) {
            if (id >= 0 && id <= 3) voice = special[character + id * 13];
            else voice = normal[character];
        } else voice = normal[character];
    }
    return voice;
}

void VoiceIntro_PushForRaceMode(void) {
    int cup = g_cupId;
    int longRound = g_longRoundFlag;
    int variant = g_courseVariantIdx;
    int voice;

    if (cup == 1) VoiceQueue_Push(0x10 + longRound * 3 + variant, -1, 0, 1);
    if (cup == 2) VoiceQueue_Push(0x16 + longRound * 3 + variant, -1, 0, 1);
    if (cup == 3) VoiceQueue_Push(0x1C + longRound * 3 + variant, -1, 0, 1);
    if (cup == 4) {
        switch (g_roundIndex) {
        case 0: VoiceQueue_Push(0x22, -1, 0, 1); break;
        case 1: VoiceQueue_Push(0x24, -1, 0, 1); break;
        case 2: VoiceQueue_Push(0x22, -1, 0, 1); break;
        case 3: VoiceQueue_Push(0x24, -1, 0, 1); break;
        case 4: VoiceQueue_Push(0x22, -1, 0, 1); break;
        case 5: VoiceQueue_Push(0x24, -1, 0, 1); break;
        case 6: VoiceQueue_Push(0x23, -1, 0, 1); break;
        case 7: VoiceQueue_Push(0x25, -1, 0, 1); break;
        }
    }
    if (cup == 5) {
        switch (g_roundIndex) {
        case 0: VoiceQueue_Push(0x26, -1, 0, 1); break;
        case 1: VoiceQueue_Push(0x28, -1, 0, 1); break;
        case 2: VoiceQueue_Push(0x27, -1, 0, 1); break;
        case 3: VoiceQueue_Push(0x29, -1, 0, 1); break;
        case 4: VoiceQueue_Push(0x27, -1, 0, 1); break;
        case 5: VoiceQueue_Push(0x29, -1, 0, 1); break;
        case 6: VoiceQueue_Push(0x27, -1, 0, 1); break;
        case 7: VoiceQueue_Push(0x29, -1, 0, 1); break;
        }
    }
    if (cup == 6) {
        switch (g_roundIndex) {
        case 0: VoiceQueue_Push(0x2A, -1, 0, 1); break;
        case 1: VoiceQueue_Push(0x2C, -1, 0, 1); break;
        case 2: VoiceQueue_Push(0x2B, -1, 0, 1); break;
        case 3: VoiceQueue_Push(0x2D, -1, 0, 1); break;
        case 4: VoiceQueue_Push(0x2A, -1, 0, 1); break;
        case 5: VoiceQueue_Push(0x2C, -1, 0, 1); break;
        case 6: VoiceQueue_Push(0x2B, -1, 0, 1); break;
        case 7: VoiceQueue_Push(0x2D, -1, 0, 1); break;
        }
    }
    if (cup == 7) {
        switch (g_roundIndex) {
        case 0: VoiceQueue_Push(0x2E, -1, 0, 1); break;
        case 1: VoiceQueue_Push(0x2F, -1, 0, 1); break;
        case 2: VoiceQueue_Push(0x30, -1, 0, 1); break;
        case 3: VoiceQueue_Push(0x31, -1, 0, 1); break;
        case 4: VoiceQueue_Push(0x2E, -1, 0, 1); break;
        case 5: VoiceQueue_Push(0x2F, -1, 0, 1); break;
        case 6: VoiceQueue_Push(0x30, -1, 0, 1); break;
        case 7: VoiceQueue_Push(0x31, -1, 0, 1); break;
        }
    }
    if (cup == 8) {
        switch (g_roundIndex) {
        case 0: VoiceQueue_Push(0x32, -1, 0, 1); break;
        case 1: VoiceQueue_Push(0x33, -1, 0, 1); break;
        case 2: VoiceQueue_Push(0x34, -1, 0, 1); break;
        case 3: VoiceQueue_Push(0x35, -1, 0, 1); break;
        case 4: VoiceQueue_Push(0x32, -1, 0, 1); break;
        case 5: VoiceQueue_Push(0x33, -1, 0, 1); break;
        case 6: VoiceQueue_Push(0x34, -1, 0, 1); break;
        case 7: VoiceQueue_Push(0x35, -1, 0, 1); break;
        }
    }
    voice = SelectStartVoice(GetKartSlotCharId(g_kartStartSlot), -1);
    if (g_humanPlayerCount <= 0) {
        unsigned int pick = g_voiceTickCounter % 3;
        if (pick == 0) {
            VoiceQueue_Push(0x18F, 0, 0, 0);
        } else if (pick == 1) {
            VoiceQueue_Push(0x171, 0, 0, 0);
        } else {
            VoiceQueue_Push(0x18C, 0, 0, 0);
            VoiceQueue_Push(voice, 0, 0, 0);
            VoiceQueue_Push(0x175, 0, 0, 0);
        }
    } else {
        switch (g_voiceTickCounter % 4) {
        case 0:
            VoiceQueue_Push(0x18C, 0, 0, 0);
            VoiceQueue_Push(voice, 0, 0, 0);
            VoiceQueue_Push(0x175, 0, 0, 0);
            break;
        case 1:
            VoiceQueue_Push(0x18D, 0, 0, 0);
            VoiceQueue_Push(voice, 0, 0, 0);
            VoiceQueue_Push(0x176, 0, 0, 0);
            break;
        case 2:
            VoiceQueue_Push(0x173, 0, 0, 0);
            break;
        default:
            VoiceQueue_Push(0x171, 0, 0, 0);
            break;
        }
    }
}
