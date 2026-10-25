/* RaceScene_GetPerspFovyForCup (0x8009B9D0): per-cup perspective fovy table
 * lookup. NonMatching: the target addresses the tables section-relative
 * (base + addis/subi per case, then lfsx), which needs the tables as statics
 * of this TU; with an extern base the offset folds into the lfs displacement. */

extern int g_cupId;
extern int g_longRoundFlag;
extern int g_courseVariantIdx;
extern unsigned char lbl_80401118[];
extern const float lbl_806D4790;
extern const float lbl_806D4794;

float RaceScene_GetPerspFovyForCup(void)
{
    unsigned char *b = lbl_80401118 + 0x10000;

    if (g_cupId < 0) {
        return lbl_806D4790;
    }
    if (g_longRoundFlag < 0) {
        return lbl_806D4790;
    }
    if (g_courseVariantIdx < 0) {
        return lbl_806D4790;
    }
    switch (g_cupId) {
    case 2:
        return *(float *)((b - 0x3364) + g_longRoundFlag * 0x10 + g_courseVariantIdx * 4);
    case 3:
        return *(float *)((b - 0x3344) + g_longRoundFlag * 0x10 + g_courseVariantIdx * 4);
    case 4:
        return *(float *)((b - 0x3324) + g_longRoundFlag * 0x10 + g_courseVariantIdx * 4);
    case 5:
        return *(float *)((b - 0x3304) + g_longRoundFlag * 0x10 + g_courseVariantIdx * 4);
    case 6:
        return *(float *)((b - 0x32e4) + g_longRoundFlag * 0x10 + g_courseVariantIdx * 4);
    }
    return lbl_806D4794;
}
