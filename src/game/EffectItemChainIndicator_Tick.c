/* EffectItemChainIndicator_Tick (0x800BF5B0): a chain of six ribbon
 * segments that trails a kart joint. The head effect (index 0) follows
 * the joint, spawns five child segments and, whenever it has moved far
 * enough, shifts every segment's pose one link down the chain; each
 * segment rebuilds its billboard matrix and the two end points the
 * ribbon renderer joins. Command 1 detaches the children, command 2
 * fades the chain out.
 * NonMatching (99.7%): the s8 -> float conversions use this TU's own
 * 0x4330000080000000 literal instead of the pooled lbl_806D5378, and one
 * loop-setup move is scheduled earlier. */

typedef struct Vec {
    float x, y, z;
} Vec;

extern int g_gameMode;
extern int g_kartVariant;
extern int g_cupId;
extern const float lbl_8032A36C[];
extern const float lbl_806D51BC; /* 2.0 */
extern const float lbl_806D51C0; /* 0.0 */
extern const float lbl_806D51C4; /* 1.0 */
extern const float lbl_806D5208; /* 0.8 */
extern const float lbl_806D5230; /* -1.0 */
extern const float lbl_806D5270; /* 6.0 */
extern const float lbl_806D5284; /* 0.02 */
extern const float lbl_806D528C; /* 0.01 */
extern const float lbl_806D5374; /* 0.85 */

extern void fn_8022B150(void);
extern float *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx_TransposeToMtx44(float m[4][4], float *src);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);
extern char ItemObject_GetGroundTypeAt(Vec pos, float *y, void *n);
extern void Vec3_Copy(void *dst, const void *src);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern unsigned char *PcbSlot_GetByIndex(int idx);
extern float fn_800D3184(const Vec *a, const void *b);
extern void Vec3_Subtract_DestFirst(void *out, const void *a, const void *b);
extern float Vec3_ToPitch(const void *v);
extern float Vec3_ToYaw(const void *v);
extern float Vec3_Magnitude_Wrapper(const void *v);
extern float Item_ProbeLateralGroundPitch(Vec pos, float yaw, float a, float b);
extern void Matrix4_Identity(float m[4][4]);
extern void Matrix4_PreMultiplyTranslation(float dst[4][4], float src[4][4], float x, float y, float z);
extern void Matrix4_PreMultiplyRotZ(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotX(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotY(float dst[4][4], float src[4][4], float a);
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec t);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);
extern void PSMTXMultVec(void *m, const Vec *src, Vec *dst);
extern void DrawEffect_Free(unsigned char *self);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);

void EffectItemChainIndicator_Tick(unsigned char *self);

typedef struct ChainData {
    unsigned char pad0[0x10];
    unsigned char *child[5]; /* 0x10 */
    unsigned char pad24[0x2C];
    unsigned char *kart;     /* 0x50 */
    Vec prevPos;             /* 0x54 */
    unsigned char pad60[0x64];
    signed char type;        /* 0xC4 */
    signed char variant;     /* 0xC5 */
    signed char visCheck;    /* 0xC6 */
    unsigned char color;     /* 0xC7 */
} ChainData;

#define F(p, o) (*(float *)((p) + (o)))
#define CHILD(c, i) ((c)->child[i])
#define KART(c) ((c)->kart)

static inline int Chain_GetColorIndex(unsigned char *kart)
{
    int ch;
    int v;

    if (kart == 0) {
        return -1;
    }
    ch = *(int *)(kart + 0x1F4);
    if (ch < 0 || ch > 3) {
        return -1;
    }
    if (g_gameMode == 2) {
        if ((unsigned int)((PcbSlot_GetByIndex(ch)[6] >> 1) & 3) < 2) {
            return -1;
        }
    } else if (g_kartVariant < 2) {
        return -1;
    } else if (g_cupId >= 9) {
        return -1;
    }
    v = *(int *)(kart + 0x1F8);
    if (v < 0 || v >= 15) {
        return -1;
    }
    return v;
}

static inline void Chain_BuildMatrix(unsigned char *e, float m[4][4])
{
    if (e != 0) {
        Matrix4_Identity(m);
        Matrix4_PreMultiplyTranslation(m, m, lbl_806D51C0, lbl_806D51C0, lbl_806D5230);
        Matrix4_PreMultiplyRotZ(m, m, F(e, 0xA0));
        Matrix4_PreMultiplyRotX(m, m, F(e, 0x98));
        Matrix4_PreMultiplyRotY(m, m, F(e, 0x9C));
        Mtx44_Translate(m, m, *(Vec *)(e + 0x8C));
        DbgScene_CopyMatrix3x4Transpose(e + 0x48, m);
    }
}

static inline void Chain_UpdateEnds(unsigned char *e, Vec *ends)
{
    Vec v;

    if (e != 0) {
        v.z = lbl_806D51C0;
        v.y = lbl_806D51C0;
        v.x = -(signed char)e[0x193];
        PSMTXMultVec(e + 0x48, &v, &ends[0]);
        v.x = (signed char)e[0x193];
        PSMTXMultVec(e + 0x48, &v, &ends[1]);
        F(e, 0x50) = ends[0].x;
        F(e, 0x60) = ends[0].y;
        F(e, 0x70) = ends[0].z;
        F(e, 0x54) = ends[1].x;
        F(e, 0x64) = ends[1].y;
        F(e, 0x74) = ends[1].z;
    }
}

static inline void Chain_Link(unsigned char *cur, unsigned char *prev)
{
    if (cur != 0 && prev != 0) {
        F(cur, 0x48) = F(prev, 0x54);
        F(cur, 0x58) = F(prev, 0x64);
        F(cur, 0x68) = F(prev, 0x74);
        F(cur, 0x4C) = F(prev, 0x50);
        F(cur, 0x5C) = F(prev, 0x60);
        F(cur, 0x6C) = F(prev, 0x70);
    }
}

void EffectItemChainIndicator_Tick(unsigned char *self)
{
    ChainData *c = (ChainData *)(self + 0xCC);
    float m[4][4];
    float mc[4][4];
    float ms[4][4];
    Vec ec[2];
    Vec es[2];
    Vec pos;
    Vec d;
    int i;

    if ((signed char)self[0x190] == 0) {
        switch (*(int *)(self + 0x10)) {
        case 0:
            Mtx_TransposeToMtx44(m, KartDriver_GetJointByIdx(KART(c), 6));
            break;
        case 1:
            Mtx_TransposeToMtx44(m, KartDriver_GetJointByIdx(KART(c), 7));
            break;
        case 2:
            Mtx_TransposeToMtx44(m, KartDriver_GetJointByIdx(KART(c), 4));
            break;
        case 3:
            Mtx_TransposeToMtx44(m, KartDriver_GetJointByIdx(KART(c), 5));
            break;
        }
        {
            float groundY;

            Mtx44_GetTranslation_ColMajor(&pos, m);
            if (ItemObject_GetGroundTypeAt(pos, &groundY, 0)) {
                pos.y = lbl_806D5374 + groundY;
            }
        }
    }

    switch ((signed char)self[0xB4]) {
    case 0: {
        int idx;

        switch (c->variant) {
        case 1:
            self[0x14] = 0;
            break;
        case 3:
            self[0x14] = 2;
            break;
        case 2:
            self[0x14] = 4;
            break;
        default:
            self[0x14] = 0;
            break;
        }
        if (c->type == 5) {
            self[0x14]++;
        }
        *(void **)(self + 0x78) = fn_8022B150;
        F(self, 0x2C) = lbl_806D5208;
        self[0x28] = 0;
        c->visCheck = 0;
        if (c->type == 0) {
            Vec3_Copy(&c->prevPos, &pos);
            for (i = 0; i < 5; i++) {
                CHILD(c, i) = DrawEffect_SpawnDirect(EffectItemChainIndicator_Tick);
                if (CHILD(c, i) != 0) {
                    CHILD(c, i)[0x190] = i + 1;
                    CHILD(c, i)[0x191] = c->variant;
                    *(unsigned char **)(CHILD(c, i) + 0x11C) = KART(c);
                }
            }
        }
        idx = Chain_GetColorIndex(KART(c));
        if (idx < 0) {
            c->color = 2;
        } else {
            c->color = (int)lbl_8032A36C[idx];
        }
        self[0xB4]++;
    }
    case 1:
        if (c->type == 0) {
            if (lbl_806D5270 < fn_800D3184(&pos, &c->prevPos)) {
                for (i = 4; i >= 1; i--) {
                    unsigned char *cur = CHILD(c, i);
                    if (cur != 0 && CHILD(c, i - 1) != 0) {
                        Vec3_Copy(cur + 0x8C, CHILD(c, i - 1) + 0x8C);
                        Vec3_Copy(CHILD(c, i) + 0x98, CHILD(c, i - 1) + 0x98);
                        F(CHILD(c, i), 0xB0) = F(CHILD(c, i - 1), 0xB0);
                        CHILD(c, i)[0x192] = CHILD(c, i - 1)[0x192];
                    }
                }
                if (CHILD(c, 0) != 0) {
                    Vec3_Subtract_DestFirst(&d, &pos, &c->prevPos);
                    Vec3_Copy(CHILD(c, 0) + 0x8C, &pos);
                    F(CHILD(c, 0), 0x98) = Vec3_ToPitch(&d);
                    F(CHILD(c, 0), 0x9C) = Vec3_ToYaw(&d);
                    F(CHILD(c, 0), 0xA0) = Item_ProbeLateralGroundPitch(*(Vec *)(CHILD(c, 0) + 0x8C),
                                                                         F(CHILD(c, 0), 0x9C), lbl_806D51BC,
                                                                         lbl_806D51C4);
                    F(CHILD(c, 0), 0xB0) = Vec3_Magnitude_Wrapper(&d);
                    CHILD(c, 0)[0x192] = 1;
                }
                for (i = 0; i < 5; i++) {
                    if (CHILD(c, i) != 0) {
                        Vec3_Copy(CHILD(c, i) + 0x80, &pos);
                    }
                    Chain_BuildMatrix(CHILD(c, i), mc);
                    Chain_UpdateEnds(CHILD(c, i), ec);
                }
                for (i = 4; i > 0; i--) {
                    Chain_Link(CHILD(c, i), CHILD(c, i - 1));
                    if (CHILD(c, i) != 0 && CHILD(c, i - 1) != 0) {
                        if ((signed char)CHILD(c, i)[0x192] == 0) {
                            CHILD(c, i - 1)[0x14] |= 1;
                        } else {
                            *(signed char *)(CHILD(c, i - 1) + 0x14) &= ~1;
                        }
                    }
                }
                Vec3_Copy(&c->prevPos, &pos);
            }
            Vec3_Copy(self + 0x8C, &pos);
            Vec3_Subtract_DestFirst(self + 0xA4, self + 0x8C, &c->prevPos);
            F(self, 0xB0) = Vec3_Magnitude_Wrapper(self + 0xA4);
            F(self, 0x98) = Vec3_ToPitch(self + 0xA4);
            F(self, 0x9C) = Vec3_ToYaw(self + 0xA4);
            F(self, 0xA0) = Item_ProbeLateralGroundPitch(*(Vec *)(self + 0x8C), F(self, 0x9C), lbl_806D51BC,
                                                         lbl_806D51C4);
            Chain_BuildMatrix(self, ms);
            Chain_UpdateEnds(self, es);
            Chain_Link(CHILD(c, 0), self);
            Vec3_Copy(self + 0x80, &pos);
        }
        if ((signed char)self[0xC9] == 1) {
            if (c->type == 0) {
                for (i = 0; i < 5; i++) {
                    if (CHILD(c, i) != 0) {
                        CHILD(c, i)[0xC9] = 1;
                    }
                    CHILD(c, i) = 0;
                }
            }
            self[0xB4]++;
            return;
        }
        if ((signed char)self[0xC9] == 2) {
            F(self, 0x2C) -= lbl_806D5284;
            for (i = 0; i < 5; i++) {
                if (CHILD(c, i) != 0) {
                    F(CHILD(c, i), 0x2C) = F(self, 0x2C);
                }
            }
            if (F(self, 0x2C) < lbl_806D51C0) {
                for (i = 0; i < 5; i++) {
                    if (CHILD(c, i) != 0) {
                        DrawEffect_Free(CHILD(c, i));
                    }
                    CHILD(c, i) = 0;
                }
                DrawEffect_Free(self);
                return;
            }
        }
        break;
    case 2:
        F(self, 0x2C) -= lbl_806D528C;
        if (F(self, 0x2C) < lbl_806D51C0) {
            DrawEffect_Free(self);
            return;
        }
        break;
    }

    if (c->visCheck) {
        if (*(int *)(KART(c) + 0x238) == 0) {
            self[0x28] = 0;
        } else if (FinalLapCoinJump_CheckActiveForObject(KART(c))) {
            self[0x28] = 0;
        } else {
            self[0x28] = 1;
        }
    }
}
