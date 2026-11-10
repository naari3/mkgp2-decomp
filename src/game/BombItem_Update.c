#include "game/BombItem_UpdatePrivate.h"

extern void BombItem_TickActive(BombItem *, BombWork *);
extern float BuildOrientationFromYaw(float);
extern void GetSpawnPosition(Vec *, float, float, float);
extern void ItemObject_DecrementCategoryBudget(BombItem *);
extern BombItem *ItemObject_SpawnWithAlias(int, int);
extern int Item_AdvanceTetherToJoint13(BombItem *, float *, float, float, float);
extern void Item_DecayVelocityScalar(BombItem *, float);
extern int Item_OrbitAnchorKart(BombItem *, Vec *, unsigned int, float, float);
#ifdef __MWERKS__
extern Vec JointByName_GetWorldPosition(void *, const char *);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void JointByName_GetWorldPosition(Vec *, void *, const char *);
static inline Vec JointByName_GetWorldPosition_ByValue(void *a0, const char *a1) { Vec port_ret; JointByName_GetWorldPosition(&port_ret, a0, a1); return port_ret; }
#define JointByName_GetWorldPosition JointByName_GetWorldPosition_ByValue
#endif
extern void SpriteSlot_Container_Free(BombItem *);
extern void SpriteSlot_InitNonLoop(void *, int);
extern void SpriteSlot_SetTransform(void *, Vec *, Vec *, float);
extern void SpriteSlot_TickAnim(void *);
extern void Vec3_Add_DestFirst(Vec *, Vec *, Vec *);
extern void Vec3_Copy(Vec *, Vec *);
extern void Vec3_Subtract_DestFirst(Vec *, Vec *, Vec *);
extern void VfxEffect_UpdateTwoChildSpinAndSound_Helper(void *, Vec *, float, float);
extern char lbl_8032FA60[];

static inline void BombItem_UpdateFade(BombItem *item, BombWork *work)
{
    switch (item->phase) {
    case 0:
        if (item->mode != 5) work->timer = 10;
        else work->timer = 0;
        item->phase++;
        /* fall through */
    case 1:
        break;
    }
    if (work->timer == 0) {
        item->alpha -= 0.05f;
        if (item->alpha < 0.0f) {
            item->visible = 0;
            item->state = 3;
            item->phase = 0;
            return;
        }
    }
    Item_DecayVelocityScalar(item, 2.0f);
    if (item->mode == 9) {
        item->velocity.y += -0.1f;
        item->rotation.x = BuildOrientationFromYaw(0.08726644515991211f + item->rotation.x);
    }
}

void BombItem_Update(BombItem *item)
{
    BombWork *work = &item->work;
    BombItem *spawn;
    Vec joint;
    Vec position;
    Vec rotation;
    Vec effectPosition;
    switch (item->state) {
    case 0:
        work->active = 1;
        SpriteSlot_InitNonLoop(item->sprite, 0x4D);
        item->sprite[0] = 4;
        item->spriteMode = 3;
        item->spriteFlag = 0;
        item->state = 1;
        item->phase = 0;
        /* fall through */
    case 1:
        BombItem_TickActive(item, work);
        break;
    case 2:
        switch (item->mode) {
        case 0:
            spawn = ItemObject_SpawnWithAlias(0x63, 0xFF);
            if (spawn) {
                spawn->work.alias = work->alias;
                spawn->work.context = work->context;
                Vec3_Copy(&spawn->pos, &item->pos);
                spawn->work.owner = work->owner;
                spawn->work.target = work->target;
            }
            item->visible = 0;
            item->state = 3;
            item->phase = 0;
            break;
        case 3:
            switch (item->phase) {
            case 0:
                GetSpawnPosition(&item->velocity, 0.0f, 0.0f, 0.0f);
                item->flag = 0;
                work->tether = 0.0f;
                work->tetherScale = item->scale;
                item->phase++;
                /* fall through */
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(item, &work->tether, work->tetherScale, 0.08726644515991211f, 0.08726644515991211f)) {
                item->visible = 0;
                item->state = 3;
                item->phase = 0;
            }
            break;
        case 4:
            spawn = ItemObject_SpawnWithAlias(0x63, 0xFF);
            if (spawn) {
                spawn->work.alias = work->alias;
                spawn->work.context = work->context;
                Vec3_Copy(&spawn->pos, &item->pos);
                spawn->work.owner = work->owner;
                spawn->work.target = work->target;
            }
            item->visible = 0;
            item->state = 3;
            item->phase = 0;
            break;
        case 6:
            switch (item->phase) {
            case 0:
                GetSpawnPosition(&item->velocity, 0.0f, 0.0f, 0.0f);
                item->flag = 0;
                Vec3_Subtract_DestFirst(&work->offset, &item->pos, &item->anchor->pos);
                work->timer = 30;
                item->phase++;
                /* fall through */
            case 1:
                break;
            }
            Item_DecayVelocityScalar(item, 2.0f);
            if (Item_OrbitAnchorKart(item, &work->offset, work->timer, 0.26179933547973633f, 0.26179933547973633f)) {
                item->visible = 0;
                item->state = 3;
                item->phase = 0;
            }
            break;
        case 9:
            BombItem_UpdateFade(item, work);
            break;
        case 5:
            BombItem_UpdateFade(item, work);
            break;
        }
        break;
    case 3:
        if (work->effect) ((BombItem *)work->effect)->phase = 1;
        work->effect = 0;
        ItemObject_DecrementCategoryBudget(item);
        SpriteSlot_Container_Free(item);
        return;
    }
    Vec3_Add_DestFirst(&item->pos, &item->pos, &item->velocity);
    rotation = item->rotation;
    position = item->pos;
    SpriteSlot_SetTransform(item->sprite, &position, &rotation, item->scale);
    SpriteSlot_TickAnim(item->sprite);
    joint = JointByName_GetWorldPosition(item->sprite, lbl_8032FA60);
    effectPosition = joint;
    VfxEffect_UpdateTwoChildSpinAndSound_Helper(work->effect, &effectPosition, item->scale, item->alpha);
    if (work->timer) work->timer--;
    if (work->timer2) work->timer2--;
    if (work->timer3) work->timer3--;
    if (work->timer4) work->timer4--;
}
