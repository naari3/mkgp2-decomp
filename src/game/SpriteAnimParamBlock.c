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
 * All three functions are C with CW auto-emitted extab (#pragma exceptions
 * on). In Reload the flush and template-copy loops are inline helpers; the
 * copy loop is a flat 50-element loop that CW unrolls 5x (ctr=10), which
 * leaves the dead `li r4,0` / `addi r4,r4,4` index update seen in the
 * target (the same fragment appears in fn_8023F320 /
 * SpriteGroup_CreateOrInit). Inlining the flush loop also gives the
 * target's i=r31 / cursor=r30 register assignment.
 */

typedef struct SpriteAnimRes {
    unsigned char pad00[0x1C];
    short *params; /* +0x1C */
} SpriteAnimRes;

typedef struct Sprite {
    unsigned char pad00[0x28];
    SpriteAnimRes *res; /* +0x28 */
} Sprite;

#include "game/types/SpriteAnimParamBlock.h"

extern void Sprite_SetAnimParam(Sprite *sprite, short oldParam, short newParam);
extern void fn_801A0500(Sprite *sprite);
extern void fn_801A0584(Sprite *sprite, int arg, int a, int b);

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

static inline void SpriteAnimParamBlock_Flush(SpriteAnimParamBlock *block) {
    int i;

    if (block->sprite) {
        for (i = 0; i < 50; i++) {
            if (block->keys[i] == -1) {
                break;
            }
            if (block->params[i] != block->keys[i]) {
                Sprite_SetAnimParam(block->sprite, block->params[i], block->keys[i]);
                block->params[i] = block->keys[i];
            }
        }
        fn_801A0500(block->sprite);
    }
}

static inline void SpriteAnimParamBlock_LoadKeys(SpriteAnimParamBlock *block) {
    int i;
    short *src;

    src = block->sprite->res->params;
    for (i = 0; i < 50; i++) {
        block->keys[i] = src[i];
        block->params[i] = src[i];
        if (src[i] == -1) {
            break;
        }
    }
}

void SpriteAnimParamBlock_Reload(SpriteAnimParamBlock *block, int arg) {
    SpriteAnimParamBlock_Flush(block);
    if (block->sprite) {
        fn_801A0584(block->sprite, arg, 1, 0);
        SpriteAnimParamBlock_LoadKeys(block);
    }
}

#pragma exceptions reset
