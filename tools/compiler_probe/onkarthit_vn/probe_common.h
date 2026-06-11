/* standalone probe context for KartItem_OnKartHit 0x8004A238
 * (types extracted verbatim from src/game/auto_ONKARTHIT_block.c) */

typedef struct SpeedTableEntry SpeedTableEntry;

typedef struct KartMovementSpeedView {
    char pad_0x0[0x8];
    int tableIdx;                    /* 0x8 */
    float speed;                     /* 0xc */
    char pad_0x10[0x12];
    unsigned char capFlag;           /* 0x22 */
    char pad_0x23[0x1];
    SpeedTableEntry *table;          /* 0x24 */
    char pad_0x28[0x4];
    float accelFactor2c;             /* 0x2c */
    char pad_0x30[0x28];
    float transform[16];             /* 0x58 */
    char pad_0x98[0x20];
} KartMovementSpeedView;

/* 0x1EC-byte hit event record built on the stack and dispatched virtually */
typedef struct OnHitEvent {
    char pad_0x0[0x8];
    int kind;               /* 0x8 */
    char pad_0xc[0x94];
    float posX;             /* 0xa0: impact midpoint */
    float posY;             /* 0xa4 */
    float posZ;             /* 0xa8 */
    char pad_0xac[0x140];   /* total 0x1ec */
} OnHitEvent;

typedef struct HitDispatcher HitDispatcher;
typedef struct HitDispatcherVt {
    char pad_0x0[0x8];
    void (*onHitEvent)(HitDispatcher *self, OnHitEvent *ev, int param); /* 0x8 */
} HitDispatcherVt;
struct HitDispatcher {
    HitDispatcherVt *vt;    /* 0x0 */
};

struct KartDriverHitView;

/* item bus view with the last-victim slot at +0x8 exposed */
typedef struct OnHitBusView {
    char pad_0x0[0x8];
    struct KartDriverHitView *lastVictim;   /* 0x8 */
    char pad_0xc[0x4];
    unsigned long long flags;               /* 0x10 */
} OnHitBusView;

typedef struct KartDriverHitView {
    char pad_0x0[0x1f4];
    int state1f4;               /* 0x1f4 */
    char pad_0x1f8[0xd4];
    int coins2cc;               /* 0x2cc */
    char pad_0x2d0[0x34];
    OnHitBusView *itemBus;      /* 0x304 */
    HitDispatcher *dispatcher;  /* 0x308 */
} KartDriverHitView;

typedef struct KartItemHit KartItemHit;
typedef struct KartItemHitVt {
    char pad_0x0[0x34];
    void (*applyEffect)(KartItemHit *self, OnHitEvent *ev, int param);  /* 0x34 */
} KartItemHitVt;

/* kart root matrix view (3x4 row-major, translation at column 3) */
typedef struct KartRootMtxView {
    char pad_0x0[0xc];
    float posX;             /* 0xc */
    char pad_0x10[0xc];
    float posY;             /* 0x1c */
    char pad_0x20[0xc];
    float posZ;             /* 0x2c */
} KartRootMtxView;

typedef struct KartItemOpsView KartItemOpsView;
