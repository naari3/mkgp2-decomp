struct ModelEntry {
    const void *a;
    const void *b;
};

extern "C" {
extern int g_cupId;
extern int g_courseVariantIdx;
extern int g_longRoundFlag;
extern int g_reverseRoundFlag;
extern int g_gameMode;
extern float lbl_806D15F0;
extern const char lbl_80371F28[];
void *Alloc(unsigned long size);
}

struct clModelGroup {
    clModelGroup *next;
    void *obj;
    void *models;
    clModelGroup(const ModelEntry *entry);
    void Append(clModelGroup *node);
};

struct clModelMgr {
    void *cam;
    clModelGroup *groups;
    clModelMgr(void *arg);
};

#define TBL(off) ((const ModelEntry *)(base + (off)))

clModelMgr::clModelMgr(void *arg) {
    const ModelEntry *e;
    float scale;
    const char *base = lbl_80371F28;
    cam = 0;
    groups = 0;
    if (arg == 0) {
        return;
    }
    e = 0;
    scale = -50.0f;
    switch (g_cupId) {
    case 1:
        switch (g_courseVariantIdx) {
        case 0:
            if (g_longRoundFlag == 0) {
                e = TBL(0x6B8);
            } else {
                e = TBL(0x790);
            }
            break;
        case 1:
            if (g_longRoundFlag == 0) {
                e = TBL(0x704);
            } else {
                e = TBL(0x7B8);
            }
            break;
        case 2:
            if (g_longRoundFlag == 0) {
                e = TBL(0x750);
            } else {
                e = TBL(0x7E0);
            }
            break;
        }
        break;
    case 2:
        if (g_longRoundFlag == 0) {
            e = TBL(0xC9C);
        } else {
            e = TBL(0xCBC);
        }
        break;
    case 3:
        switch (g_courseVariantIdx) {
        case 0:
            if (g_longRoundFlag == 0) {
                e = TBL(0xF28);
            } else {
                e = TBL(0xF6C);
            }
            break;
        case 1:
            if (g_longRoundFlag == 0) {
                e = TBL(0xFC0);
            } else {
                e = TBL(0x1004);
            }
            break;
        case 2:
            if (g_longRoundFlag == 0) {
                e = TBL(0x1058);
            } else {
                e = TBL(0x109C);
            }
            break;
        }
        break;
    case 4:
        if (g_gameMode != 0) {
            if (g_longRoundFlag == 0) {
                e = TBL(0x15E8);
            } else if (g_reverseRoundFlag == 0) {
                e = TBL(0x1620);
            } else {
                e = TBL(0x1648);
            }
        } else {
            switch (g_courseVariantIdx) {
            case 0:
                if (g_longRoundFlag == 0) {
                    e = TBL(0x16BC);
                } else if (g_reverseRoundFlag == 0) {
                    e = TBL(0x16FC);
                } else {
                    e = TBL(0x1744);
                }
                break;
            case 1:
                if (g_longRoundFlag == 0) {
                    e = TBL(0x178C);
                } else if (g_reverseRoundFlag == 0) {
                    e = TBL(0x17CC);
                } else {
                    e = TBL(0x1814);
                }
                break;
            case 2:
                if (g_longRoundFlag == 0) {
                    e = TBL(0x185C);
                } else if (g_reverseRoundFlag == 0) {
                    e = TBL(0x189C);
                } else {
                    e = TBL(0x18E4);
                }
                break;
            case 3:
                if (g_longRoundFlag == 0) {
                    e = TBL(0x192C);
                } else if (g_reverseRoundFlag == 0) {
                    e = TBL(0x196C);
                } else {
                    e = TBL(0x19B4);
                }
                break;
            }
        }
        break;
    case 5:
        if (g_longRoundFlag == 0) {
            if (g_reverseRoundFlag == 0) {
                e = TBL(0x22E4);
            } else {
                e = TBL(0x230C);
            }
        } else {
            if (g_reverseRoundFlag == 0) {
                e = TBL(0x2334);
            } else {
                e = TBL(0x2354);
            }
        }
        break;
    case 6:
        switch (g_courseVariantIdx) {
        case 0:
            if (g_longRoundFlag == 0) {
                if (g_reverseRoundFlag == 0) {
                    e = TBL(0x3F5C);
                } else {
                    e = TBL(0x3F84);
                }
            } else {
                if (g_reverseRoundFlag == 0) {
                    e = TBL(0x3FBC);
                } else {
                    e = TBL(0x3FF8);
                }
            }
            break;
        case 1:
            if (g_longRoundFlag == 0) {
                if (g_reverseRoundFlag == 0) {
                    e = TBL(0x4024);
                } else {
                    e = TBL(0x403C);
                }
            } else {
                if (g_reverseRoundFlag == 0) {
                    e = TBL(0x406C);
                } else {
                    e = TBL(0x40A0);
                }
            }
            break;
        case 2:
            if (g_longRoundFlag == 0) {
                if (g_reverseRoundFlag == 0) {
                    e = TBL(0x40D8);
                } else {
                    e = TBL(0x40F8);
                }
            } else {
                if (g_reverseRoundFlag == 0) {
                    e = TBL(0x4138);
                } else {
                    e = TBL(0x4160);
                }
            }
            break;
        case 3:
            if (g_longRoundFlag == 0) {
                if (g_reverseRoundFlag == 0) {
                    e = TBL(0x4198);
                } else {
                    e = TBL(0x41B8);
                }
            } else {
                if (g_reverseRoundFlag == 0) {
                    e = TBL(0x41D8);
                } else {
                    e = TBL(0x41E8);
                }
            }
            break;
        }
        scale = -20.0f;
        break;
    case 14:
        e = TBL(0x40D8);
        break;
    }
    if (e == 0) {
        return;
    }
    const ModelEntry *p = e;
    while (1) {
        if (p->a == 0 && p->b == 0) {
            break;
        }
        clModelGroup *g = new clModelGroup(p);
        if (groups != 0) {
            groups->Append(g);
        } else {
            groups = g;
        }
        p++;
    }
    lbl_806D15F0 = scale;
}
