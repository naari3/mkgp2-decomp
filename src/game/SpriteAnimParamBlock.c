/*
 * SpriteAnimParamBlock key/param cache (GitHub claim issue #9)
 *
 * SpriteAnimParamBlock_SetKey             @ 0x8023EF38 (size 0x8C)
 * SpriteAnimParamBlock_SetAnimParamCached @ 0x8023EFC4 (size 0x98)
 * SpriteAnimParamBlock_Reload             @ 0x8023F05C (size 0x16C)
 *
 * Three adjacent single-fn reversed-extab groups merged into one TU
 * (extab 0x8001CD94..0x8001CDAC, extabindex 0x8002AF14..0x8002AF38,
 * .text 0x8023EF38..0x8023F1C8). Built with CW 1.3.2 +
 * `-Cpp_exceptions on` so all three extab/extabindex pairs are
 * auto-emitted in fn definition order.
 *
 * SpriteAnimParamBlock:
 *   +0x00 : Sprite* sprite (0 = unbound)
 *   +0x04 : s16 keys[50]   (-1 terminated)
 *   +0x68 : s16 params[50] (cached anim params, mirrors keys layout)
 *
 * SetKey / SetAnimParamCached are C-matched with CW auto-emitted extab
 * (#pragma exceptions on). Reload is asm_fn with manual extab/extabindex
 * emit (.extab_user -> extab via tools/postprocess_extab_user.py; mix rule
 * per docs/per_fn_matching_strategy.md sec 14.1: auto group SetKey/Cached is
 * address-before the manual entry, so final extab order matches target).
 *
 * Reload asm_fn reason: 96.47% from C (draft in HANDOFF), two source-closed
 * residuals: (1) flush-loop i/cursor callee-saved swap (target i=r31
 * cursor=r30), (2) a dead row counter `li r4,0` + `addi r4,r4,4` in the
 * template copy loop (also present in fn_8023F320 / SpriteGroup_CreateOrInit,
 * same shared source fragment). ~12 probe shapes (loop-control fold, static
 * inline helper returned counter, break-redundant tests, register volatile,
 * NULL-based dead SR cursor, do-while, param reuse) all either DCE the
 * counter or emit an extra cmpwi. See HANDOFF.md notes.
 */

typedef struct SpriteAnimRes {
    unsigned char pad00[0x1C];
    short *params; /* +0x1C */
} SpriteAnimRes;

typedef struct Sprite {
    unsigned char pad00[0x28];
    SpriteAnimRes *res; /* +0x28 */
} Sprite;

typedef struct SpriteAnimParamBlock {
    Sprite *sprite;   /* +0x00 */
    short keys[50];   /* +0x04 */
    short params[50]; /* +0x68 */
} SpriteAnimParamBlock;

extern void Sprite_SetAnimParam(Sprite *sprite, short oldParam, short newParam);
extern void fn_801A0500(Sprite *sprite);
extern void fn_801A0584(Sprite *sprite, int arg, int a, int b);

/* --- forward decl (extabindex ref) --- */
asm void SpriteAnimParamBlock_Reload(void);

/* --- extab/extabindex manual emit for the asm_fn (Reload only; SetKey and
 * SetAnimParamCached use CW auto-emit) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SpriteAnimParamBlock_Reload[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SpriteAnimParamBlock_Reload = {
    (void *)&SpriteAnimParamBlock_Reload, 0x0000016C, (void *)extab_SpriteAnimParamBlock_Reload
};

#pragma exceptions on

void SpriteAnimParamBlock_SetKey(SpriteAnimParamBlock *block, int key, int param) {
    int i;

    if (block->sprite) {
        for (i = 0; i < 50; i++) {
            if (block->keys[i] == -1) {
                break;
            }
            if (key == block->keys[i]) {
                Sprite_SetAnimParam(block->sprite, block->params[i], param);
                block->params[i] = param;
                break;
            }
        }
    }
}

void SpriteAnimParamBlock_SetAnimParamCached(SpriteAnimParamBlock *block, int oldParam, int newParam) {
    int i;

    if (block->sprite) {
        for (i = 0; i < 50; i++) {
            if (block->keys[i] == -1) {
                break;
            }
            if (oldParam == block->params[i]) {
                Sprite_SetAnimParam(block->sprite, oldParam, newParam);
                block->params[i] = newParam;
                break;
            }
        }
    }
}

/*
 * asm_fn: flush changed params (Sprite_SetAnimParam per changed slot +
 * fn_801A0500), then rebind anim resource (fn_801A0584) and copy the
 * template rows (10 rows x 5 shorts, -1 sentinel) into keys/params.
 * C draft reached 96.47% (see TU header comment / HANDOFF notes).
 */
asm void SpriteAnimParamBlock_Reload(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r29, r4
    stw r28, 0x10(r1)
    mr r28, r3
    lwz r0, 0x0(r3)
    cmplwi r0, 0x0
    beq SpriteAnimParamBlock_Reload_L_8023F0D4
    li r31, 0x0
    mr r30, r28
    SpriteAnimParamBlock_Reload_L_8023F094:
    lha r5, 0x4(r30)
    cmpwi r5, -0x1
    beq SpriteAnimParamBlock_Reload_L_8023F0CC
    lha r4, 0x68(r30)
    cmpw r4, r5
    beq SpriteAnimParamBlock_Reload_L_8023F0BC
    lwz r3, 0x0(r28)
    bl Sprite_SetAnimParam
    lha r0, 0x4(r30)
    sth r0, 0x68(r30)
    SpriteAnimParamBlock_Reload_L_8023F0BC:
    addi r31, r31, 0x1
    addi r30, r30, 0x2
    cmpwi r31, 0x32
    blt SpriteAnimParamBlock_Reload_L_8023F094
    SpriteAnimParamBlock_Reload_L_8023F0CC:
    lwz r3, 0x0(r28)
    bl fn_801A0500
    SpriteAnimParamBlock_Reload_L_8023F0D4:
    lwz r3, 0x0(r28)
    cmplwi r3, 0x0
    beq SpriteAnimParamBlock_Reload_L_8023F1A8
    mr r4, r29
    li r5, 0x1
    li r6, 0x0
    bl fn_801A0584
    lwz r3, 0x0(r28)
    li r0, 0xa
    mr r5, r28
    li r4, 0x0
    lwz r3, 0x28(r3)
    lwz r3, 0x1c(r3)
    mtctr r0
    SpriteAnimParamBlock_Reload_L_8023F10C:
    lha r0, 0x0(r3)
    sth r0, 0x4(r5)
    lha r0, 0x0(r3)
    sth r0, 0x68(r5)
    lha r0, 0x0(r3)
    cmpwi r0, -0x1
    beq SpriteAnimParamBlock_Reload_L_8023F1A8
    lha r0, 0x2(r3)
    sth r0, 0x6(r5)
    lha r0, 0x2(r3)
    sth r0, 0x6a(r5)
    lha r0, 0x2(r3)
    cmpwi r0, -0x1
    beq SpriteAnimParamBlock_Reload_L_8023F1A8
    lha r0, 0x4(r3)
    sth r0, 0x8(r5)
    lha r0, 0x4(r3)
    sth r0, 0x6c(r5)
    lha r0, 0x4(r3)
    cmpwi r0, -0x1
    beq SpriteAnimParamBlock_Reload_L_8023F1A8
    lha r0, 0x6(r3)
    sth r0, 0xa(r5)
    lha r0, 0x6(r3)
    sth r0, 0x6e(r5)
    lha r0, 0x6(r3)
    cmpwi r0, -0x1
    beq SpriteAnimParamBlock_Reload_L_8023F1A8
    lha r0, 0x8(r3)
    sth r0, 0xc(r5)
    lha r0, 0x8(r3)
    sth r0, 0x70(r5)
    lha r0, 0x8(r3)
    cmpwi r0, -0x1
    beq SpriteAnimParamBlock_Reload_L_8023F1A8
    addi r3, r3, 0xa
    addi r5, r5, 0xa
    addi r4, r4, 0x4
    bdnz SpriteAnimParamBlock_Reload_L_8023F10C
    SpriteAnimParamBlock_Reload_L_8023F1A8:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

#pragma exceptions reset
