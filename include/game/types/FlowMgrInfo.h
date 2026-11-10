#ifndef GAME_TYPES_FLOWMGRINFO_H
#define GAME_TYPES_FLOWMGRINFO_H

typedef struct FlowMgrInfo {
    char pad000[0x164];
    int chara;
    int f168;
    int mode;
    int f170;
    int f174;
    int f178;
    int f17C;
    int f180;
    int pad184;
    int f188[3];
    unsigned char f194;
} FlowMgrInfo;

#endif /* GAME_TYPES_FLOWMGRINFO_H */
