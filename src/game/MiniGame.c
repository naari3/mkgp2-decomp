extern "C" {
extern int g_courseVariantIdx;
extern int g_cupId;
extern int g_longRoundFlag;
}

class SuikaBall {
    char data[0x6c];
public:
    SuikaBall();
};

class NokoNokoChallenge {
    char data[0x48];
public:
    NokoNokoChallenge();
};

class ReverseChallenge {
    char data[0x4c];
public:
    ReverseChallenge();
};

class BiribiriLand {
    char data[0x44];
public:
    BiribiriLand();
};

class CGameCoin {
    char data[0xc4];
public:
    CGameCoin();
};

class RivalRun {
    char data[0x3c];
public:
    RivalRun();
};

class MiniGame_CoinChallenge {
    char data[0x48];
public:
    MiniGame_CoinChallenge();
};

class JumpDistanceMode {
    char data[0x8c];
public:
    JumpDistanceMode();
};

void *MiniGame_CreateByCourseid(void) {
    g_longRoundFlag = 0;
    g_courseVariantIdx = 0;

    switch (g_cupId) {
    case 9:
        return new SuikaBall;
    case 10:
        return new NokoNokoChallenge;
    case 11:
        return new ReverseChallenge;
    case 12:
        return new BiribiriLand;
    case 13:
        return new CGameCoin;
    case 14:
        return new RivalRun;
    case 15:
        return new MiniGame_CoinChallenge;
    case 16:
        return new JumpDistanceMode;
    default:
        return 0;
    }
}
