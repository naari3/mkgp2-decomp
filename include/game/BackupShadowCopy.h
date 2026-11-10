#ifndef GAME_BACKUP_SHADOW_COPY_H
#define GAME_BACKUP_SHADOW_COPY_H

#include "game/os_time.h"

/*
 * Backup record: working copy lbl_80598A60 and the published copy
 * g_backupShadowCopy (size 0x6A20). The header block is byte-packed (fields at
 * +0x2B/+0x53/+0x57/+0x5B are unaligned); the alignment holes at +0x01,
 * +0x14, +0x32 and +0x61 are never transferred by the publish routines.
 */

typedef struct BackupBytes4 {
    unsigned char b[4];
} BackupBytes4;

#pragma options align=packed
typedef struct BackupData {
    unsigned char b00;
    unsigned char pad01[3];
    unsigned int w04;
    unsigned int w08;
    unsigned int w0c;
    unsigned int w10;
    unsigned char pad14[4];
    OSTime time; /* 0x18: OSGetTime() at last publish */
    unsigned int w20;
    unsigned int w24;
    unsigned short h28;
    unsigned char b2a;
    unsigned int w2b;
    unsigned short h2f;
    unsigned char b31;
    unsigned char pad32[2];
    unsigned int steerCalib; /* 0x34 */
    unsigned int posCalib;   /* 0x38 */
    unsigned int brakeCalib; /* 0x3C */
    unsigned int accelCalib; /* 0x40 */
    unsigned int w44;
    unsigned int w48;
    unsigned int w4c;
    unsigned short h50;
    unsigned char b52;
    unsigned int w53;
    BackupBytes4 s57;
    BackupBytes4 s5b;
    unsigned short h5f;
    unsigned char pad61[3];
    struct { unsigned int w[0x210 / 4]; } blk064;
    struct { unsigned int w[0x26C / 4]; } stats;  /* 0x274 */
    struct { unsigned int w[0x2D00 / 4]; } blk4E0;
    struct { unsigned int w[0x3840 / 4]; } blk31E0;
} BackupData; /* size 0x6A20 */
#pragma options align=reset

extern unsigned char lbl_806D1120; /* backup available */
extern int lbl_806D1128;           /* backup busy */
extern BackupData lbl_80598A60;    /* working copy */
extern BackupData g_backupShadowCopy;    /* published copy */
extern void fn_80288210(int, BackupData *);

/* Field-by-field publish of the working copy (alignment holes skipped). */
static inline void Backup_CopyToPublished(void) {
    g_backupShadowCopy.b00 = lbl_80598A60.b00;
    g_backupShadowCopy.w04 = lbl_80598A60.w04;
    g_backupShadowCopy.w08 = lbl_80598A60.w08;
    g_backupShadowCopy.w0c = lbl_80598A60.w0c;
    g_backupShadowCopy.w10 = lbl_80598A60.w10;
    g_backupShadowCopy.time = lbl_80598A60.time;
    g_backupShadowCopy.w20 = lbl_80598A60.w20;
    g_backupShadowCopy.w24 = lbl_80598A60.w24;
    g_backupShadowCopy.h28 = lbl_80598A60.h28;
    g_backupShadowCopy.b2a = lbl_80598A60.b2a;
    g_backupShadowCopy.w2b = lbl_80598A60.w2b;
    g_backupShadowCopy.h2f = lbl_80598A60.h2f;
    g_backupShadowCopy.b31 = lbl_80598A60.b31;
    g_backupShadowCopy.steerCalib = lbl_80598A60.steerCalib;
    g_backupShadowCopy.posCalib = lbl_80598A60.posCalib;
    g_backupShadowCopy.brakeCalib = lbl_80598A60.brakeCalib;
    g_backupShadowCopy.accelCalib = lbl_80598A60.accelCalib;
    g_backupShadowCopy.w44 = lbl_80598A60.w44;
    g_backupShadowCopy.w48 = lbl_80598A60.w48;
    g_backupShadowCopy.w4c = lbl_80598A60.w4c;
    g_backupShadowCopy.h50 = lbl_80598A60.h50;
    g_backupShadowCopy.b52 = lbl_80598A60.b52;
    g_backupShadowCopy.w53 = lbl_80598A60.w53;
    g_backupShadowCopy.s57 = lbl_80598A60.s57;
    g_backupShadowCopy.s5b = lbl_80598A60.s5b;
    g_backupShadowCopy.h5f = lbl_80598A60.h5f;
    g_backupShadowCopy.blk064 = lbl_80598A60.blk064;
    g_backupShadowCopy.stats = lbl_80598A60.stats;
    g_backupShadowCopy.blk4E0 = lbl_80598A60.blk4E0;
    g_backupShadowCopy.blk31E0 = lbl_80598A60.blk31E0;
}

#endif
