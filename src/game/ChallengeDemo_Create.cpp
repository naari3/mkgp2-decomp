/* fn_80124DF8: creates the challenge demo scene for the current challenge
 * cup (cups 9..16). */
#pragma cplusplus on

void *operator new(unsigned long size);

struct ChallengeDemo {
    virtual int Update();
};
struct ChallengeDemoObj : ChallengeDemo {
    unsigned char opaque[0x54];
    ChallengeDemoObj();
};
struct ChallengeDemoShell : ChallengeDemo {
    unsigned char opaque[0x54];
    ChallengeDemoShell();
};
struct ChallengeDemoWC : ChallengeDemo {
    unsigned char opaque[0x58];
    ChallengeDemoWC();
};
struct ChallengeDemoTornado : ChallengeDemo {
    unsigned char opaque[0x54];
    ChallengeDemoTornado();
};
struct ChallengeDemoBlock : ChallengeDemo {
    unsigned char opaque[0x90];
    ChallengeDemoBlock();
};
struct ChallengeDemoUra : ChallengeDemo {
    unsigned char opaque[0x54];
    ChallengeDemoUra();
};
struct ChallengeDemoCoin : ChallengeDemo {
    unsigned char opaque[0x384];
    ChallengeDemoCoin();
};
struct ChallengeDemoExtra : ChallengeDemo {
    unsigned char opaque[0x68];
    ChallengeDemoExtra();
};

extern "C" {
extern int g_cupId;
void PlayStats_OnMissionSceneInit_Stub(void);
}

extern "C" ChallengeDemo *fn_80124DF8(void)
{
    PlayStats_OnMissionSceneInit_Stub();
    switch (g_cupId) {
    case 9:
        return new ChallengeDemoObj;
    case 10:
        return new ChallengeDemoShell;
    case 11:
        return new ChallengeDemoWC;
    case 12:
        return new ChallengeDemoTornado;
    case 13:
        return new ChallengeDemoBlock;
    case 14:
        return new ChallengeDemoUra;
    case 15:
        return new ChallengeDemoCoin;
    case 16:
        return new ChallengeDemoExtra;
    }
    return 0;
}
