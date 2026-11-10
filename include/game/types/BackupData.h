#ifndef GAME_TYPES_BACKUPDATA_H
#define GAME_TYPES_BACKUPDATA_H

typedef struct BackupData {
    unsigned char pad000[0x274];
    unsigned char stats[0x26c];
} BackupData;

#endif /* GAME_TYPES_BACKUPDATA_H */
