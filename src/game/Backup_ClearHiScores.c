/* Backup_ClearHiScores @ 0x8007502C (size 0x1C4).
 * Resets every best-time slot of the backup working copy to 599.999 s and
 * refills the top-10 name records with each course's default name/kart.
 * Returns 0 when the backup is unavailable or busy. */
#pragma use_lmw_stmw on

typedef unsigned short wchar;

#include "game/types/HiScoreName.h"

#include "game/types/BackupHiScores.h"

extern unsigned char lbl_806D1120; /* backup available */
extern int lbl_806D1128;           /* backup busy */
extern BackupHiScores lbl_80598A60;
extern const float lbl_806D2EB4;   /* 599.999f */
extern const wchar *Backup_ClearHiScores_data_803FDF70[9];
extern const int Backup_ClearHiScores_rodata_8031128C[9];
extern unsigned int wcslen(const wchar *s);

int Backup_ClearHiScores(void)
{
    int i;
    int course;
    int j;
    int k;
    int rank;
    int c;

    if (lbl_806D1120 == 0) {
        return 0;
    }
    if (lbl_806D1128 != 0) {
        return 0;
    }
    for (i = 0; i < 2; i++) {
        for (course = 0; course < 9; course++) {
            for (j = 0; j < 2; j++) {
                for (k = 0; k < 2; k++) {
                    HiScoreName *names = lbl_80598A60.names[i][course][j][k];
                    float *times = lbl_80598A60.times[i][course][j][k];
                    for (rank = 0; rank < 50; rank++) {
                        times[rank] = lbl_806D2EB4;
                        if (rank < 10) {
                            HiScoreName *rec = &names[rank];
                            rec->name[0] = 0;
                            rec->name[1] = 0;
                            rec->name[2] = 0;
                            rec->name[3] = 0;
                            rec->name[4] = 0;
                            rec->name[5] = 0;
                            for (c = 0; c < wcslen(Backup_ClearHiScores_data_803FDF70[course]) && c < 5; c++) {
                                rec->name[c] = Backup_ClearHiScores_data_803FDF70[course][c];
                            }
                            rec->kart = Backup_ClearHiScores_rodata_8031128C[course];
                            rec->extra[0] = 0;
                            rec->extra[1] = 0;
                            rec->extra[2] = 0;
                        }
                    }
                }
            }
        }
    }
    return 1;
}
