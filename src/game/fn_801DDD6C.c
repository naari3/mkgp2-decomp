/* Per-course enemy tuning lookups (table indexed by cup, cc class and round). */
typedef struct CourseTuning {
    int unk0;
    float f4;
    float f8;
    float fC;
    float f10;
    float bonus;
    int count;
    float bonusAlt;
    int value;
    float bonus2;
    int count2;
    float bonus2Alt;
    int value2;
} CourseTuning;

extern const float FLOAT_defaultBonus;
extern int g_ccClass;
extern int g_cupId;
extern int g_gameMode;
extern unsigned char g_nonFirstFinishFlag;
extern int g_roundIndex;
extern CourseTuning lbl_803A0908[];

static inline int CourseTuning_Index(void) {
    int cup = g_cupId;
    int round = g_roundIndex;
    if (cup < 1 || cup >= 9) {
        return 0;
    }
    return (cup - 1) * 0x18 + g_ccClass * 8 + round;
}

static inline CourseTuning *CourseTuning_Get(void) {
    if (g_gameMode == 0) {
        return &lbl_803A0908[CourseTuning_Index()];
    }
    return 0;
}

int fn_801DDD6C(void) {
    CourseTuning *t = CourseTuning_Get();
    if (t == 0) {
        return 0;
    }
    if (g_nonFirstFinishFlag) {
        return t->value2;
    }
    return t->value;
}

float fn_801DDDF4(void) {
    CourseTuning *t = CourseTuning_Get();
    if (t == 0) {
        return FLOAT_defaultBonus;
    }
    if (g_nonFirstFinishFlag) {
        return t->bonus2Alt;
    }
    return t->bonusAlt;
}

int fn_801DDE7C(void) {
    CourseTuning *t = CourseTuning_Get();
    if (t == 0) {
        return 0;
    }
    if (g_nonFirstFinishFlag) {
        return t->count2;
    }
    return t->count;
}

float fn_801DDF04(void) {
    CourseTuning *t = CourseTuning_Get();
    if (t == 0) {
        return FLOAT_defaultBonus;
    }
    if (g_nonFirstFinishFlag) {
        return t->bonus2;
    }
    return t->bonus;
}

float fn_801DDF8C(void) {
    CourseTuning *t = CourseTuning_Get();
    if (t != 0) {
        return t->f10;
    }
    return FLOAT_defaultBonus;
}

float fn_801DE000(void) {
    CourseTuning *t = CourseTuning_Get();
    if (t != 0) {
        return t->fC;
    }
    return FLOAT_defaultBonus;
}

float fn_801DE074(void) {
    CourseTuning *t = CourseTuning_Get();
    if (t != 0) {
        return t->f8;
    }
    return FLOAT_defaultBonus;
}

float fn_801DE0E8(void) {
    CourseTuning *t = CourseTuning_Get();
    if (t != 0) {
        return t->f4;
    }
    return FLOAT_defaultBonus;
}
