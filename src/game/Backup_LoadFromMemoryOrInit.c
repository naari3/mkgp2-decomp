/* Backup_LoadFromMemoryOrInit @ 0x80074190 (size 0x1E0).
 * Fills the backup working copy with the factory settings: game options,
 * calibration defaults and the coin/credit counters read back from the
 * coin unit, then stamps it with the current time.  Returns 0 when the
 * backup is unavailable or busy. */
#include "game/os_time.h"

#include "game/types/CoinCounters.h"

typedef struct BackupSettings {
    unsigned char version;      /* 0x000 */
    unsigned char pad001[3];
    int id;                     /* 0x004 */
    int w08;                    /* 0x008 */
    unsigned int coinsSeen;     /* 0x00C */
    unsigned int creditsSeen;   /* 0x010 */
    unsigned char pad014[4];
    OSTime time;                /* 0x018 */
    signed char region;         /* 0x020 */
    unsigned char b21;              /* 0x021 */
    unsigned char b22;              /* 0x022 */
    unsigned char b23;              /* 0x023 */
    unsigned char b24;              /* 0x024 */
    unsigned char b25;              /* 0x025 */
    unsigned char b26;              /* 0x026 */
    unsigned char b27;              /* 0x027 */
    unsigned char b28;              /* 0x028 */
    unsigned char b29;              /* 0x029 */
    unsigned char b2A;              /* 0x02A */
    unsigned char b2B;              /* 0x02B */
    unsigned char b2C;              /* 0x02C */
    unsigned char b2D;              /* 0x02D */
    unsigned char b2E;              /* 0x02E */
    unsigned char b2F;              /* 0x02F */
    unsigned char b30;              /* 0x030 */
    unsigned char b31;              /* 0x031 */
    unsigned char pad032[2];
    int steerCalib;             /* 0x034 */
    int posCalib;               /* 0x038 */
    int brakeCalib;             /* 0x03C */
    int accelCalib;             /* 0x040 */
    unsigned char b44;          /* 0x044 */
    unsigned char b45;          /* 0x045 */
    unsigned char pad046[2];
    int w48;                    /* 0x048 */
    int w4c;                    /* 0x04C */
    unsigned char b50;              /* 0x050 */
    unsigned char b51;              /* 0x051 */
    unsigned char b52;              /* 0x052 */
    unsigned char b53;              /* 0x053 */
    unsigned char b54;              /* 0x054 */
    unsigned char b55;              /* 0x055 */
    unsigned char b56;              /* 0x056 */
    unsigned char b57;              /* 0x057 */
    unsigned char b58;              /* 0x058 */
    unsigned char b59;              /* 0x059 */
    unsigned char b5A;              /* 0x05A */
    unsigned char b5B;              /* 0x05B */
    unsigned char b5C;              /* 0x05C */
    unsigned char b5D;              /* 0x05D */
    unsigned char b5E;              /* 0x05E */
    unsigned char b5F;              /* 0x05F */
    unsigned char b60;              /* 0x060 */
    unsigned char pad061[3];
    unsigned char b64;          /* 0x064 */
    unsigned char pad065[0x207];
    int w26c;                   /* 0x26C */
    unsigned char b270;         /* 0x270 */
} BackupSettings;

extern unsigned char lbl_806D1120; /* backup available */
extern int lbl_806D1128;           /* backup busy */
extern BackupSettings lbl_80598A60;
extern void fn_80289A90(CoinCounters *out);

int Backup_LoadFromMemoryOrInit(void)
{
    CoinCounters coins;

    if (lbl_806D1120 == 0) {
        return 0;
    }
    if (lbl_806D1128 != 0) {
        return 0;
    }

    lbl_80598A60.region = 0;
    lbl_80598A60.b21 = 1;
    lbl_80598A60.b22 = 2;
    lbl_80598A60.b25 = 1;
    lbl_80598A60.b2A = 0;
    lbl_80598A60.b28 = 0;
    lbl_80598A60.b29 = 0;
    if (lbl_80598A60.region == 0) {
        lbl_80598A60.b24 = 1;
        lbl_80598A60.b23 = 1;
        lbl_80598A60.b27 = 1;
        lbl_80598A60.b26 = 1;
    } else if (lbl_80598A60.region == 1) {
        lbl_80598A60.b24 = 1;
        lbl_80598A60.b23 = 1;
        lbl_80598A60.b27 = 0;
        lbl_80598A60.b26 = 1;
    } else {
        lbl_80598A60.b24 = 0;
        lbl_80598A60.b23 = 0;
        lbl_80598A60.b27 = 0;
        lbl_80598A60.b28 = 1;
        lbl_80598A60.b26 = 0;
    }

    lbl_80598A60.b2B = 0x60;
    lbl_80598A60.b2C = 0x0C;
    lbl_80598A60.b2D = 0x08;
    lbl_80598A60.b2E = 0x78;
    lbl_80598A60.b2F = 0x55;
    lbl_80598A60.b30 = 0x3F;
    lbl_80598A60.b31 = 0x3F;
    lbl_80598A60.steerCalib = 0x7FFF;
    lbl_80598A60.posCalib = 0x1FF;
    lbl_80598A60.accelCalib = 0;
    lbl_80598A60.brakeCalib = 0;
    lbl_80598A60.b44 = 1;
    lbl_80598A60.b45 = 1;
    lbl_80598A60.w48 = 0x0C;
    lbl_80598A60.w4c = -0x10;
    lbl_80598A60.b50 = 0;
    lbl_80598A60.b51 = 0;
    lbl_80598A60.b52 = 0;
    lbl_80598A60.b53 = 0;
    lbl_80598A60.b54 = 0;
    lbl_80598A60.b55 = 0;
    lbl_80598A60.b56 = 0;
    lbl_80598A60.b57 = 0;
    lbl_80598A60.b58 = 0;
    lbl_80598A60.b59 = 0;
    lbl_80598A60.b5A = 0;
    lbl_80598A60.b5B = 0;
    lbl_80598A60.b5C = 0;
    lbl_80598A60.b5D = 0;
    lbl_80598A60.b5E = 0;
    lbl_80598A60.b5F = 0;
    lbl_80598A60.b60 = 0;
    lbl_80598A60.b64 = 0;
    lbl_80598A60.w26c = 0;
    lbl_80598A60.b270 = 0;

    fn_80289A90(&coins);
    lbl_80598A60.coinsSeen = coins.totalCoins;
    lbl_80598A60.creditsSeen = coins.serviceCredits;
    lbl_80598A60.version = 0x0F;
    lbl_80598A60.w08 = 0;
    lbl_80598A60.id = -1;
    lbl_80598A60.time = OSGetTime();
    return 1;
}
