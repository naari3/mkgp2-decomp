/* Observed Gabyou item fields; no unobserved layout is asserted. */
struct Vec3 { float x, y, z; };
struct Vec3Words { unsigned int x, y, z; };
struct GabyouUpdateContext {
    unsigned char matrixEnabled;
    unsigned char pad01[3];
    unsigned int timer04, timer08, timer0C, timer10;
    float tetherTime, tetherScale;
    unsigned char pad1C[0x74];
    unsigned char flag90;
};
struct GabyouUpdateItem {
    unsigned char pad00[8];
    int type;
    unsigned char pad0C[8];
    unsigned char sprite[0x14];
    unsigned char active;
    unsigned char pad29[3];
    float lifetime;
    unsigned char pad30[0xC];
    unsigned char flag3C;
    unsigned char pad3D[0xB];
    float matrix[12];
    unsigned char pad78[0x14];
    unsigned char category, categoryPhase;
    unsigned char pad8E[0x12];
    Vec3 position;
    float rotationX, rotationY, rotationZ;
    Vec3 velocity;
    float scale;
    signed char state, phase;
    unsigned char padCA;
    unsigned char kind;
    unsigned char padCC[0x20];
    GabyouUpdateContext context;
};
extern "C" {
extern char lbl_8032F598[0x478];
extern float lbl_806D6088, lbl_806D608C, lbl_806D6090;
extern float lbl_806D6094, lbl_806D6098;
void SpriteSlot_InitNonLoop(void *, int);
void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *, int);
void SpriteSlot_SetJointVisibilityByName(void *, const char *, int, int);
void GabyouItem_TickActive(GabyouUpdateItem *, GabyouUpdateContext *);
void ShellPile_Spawn(GabyouUpdateItem *, GabyouUpdateContext *);
void SoundMgr_PlaySE_Positional(int, Vec3, int);
void GetSpawnPosition(Vec3 *, float, float, float);
int Item_AdvanceTetherToJoint13(GabyouUpdateItem *, float *, float, float, float);
void Item_DecayVelocityScalar(GabyouUpdateItem *, float);
float BuildOrientationFromYaw(float);
void ItemObject_DecrementCategoryBudget(GabyouUpdateItem *);
void SpriteSlot_Container_Free(GabyouUpdateItem *);
void Vec3_Add_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
void Matrix4_Identity(float *);
void Mtx44_Scale_Uniform(float *, const float *, float);
void Matrix4_PreMultiplyRotZ(float *, const float *, float);
void Matrix4_PreMultiplyRotX(float *, const float *, float);
void Matrix4_PreMultiplyRotY(float *, const float *, float);
void Mtx44_Translate(float *, const float *, const Vec3 *);
void DbgScene_CopyMatrix3x4Transpose(float *, const float *);

static inline void Retire(GabyouUpdateItem *item)
{
    item->active = 0;
    item->state = 3;
    item->phase = 0;
}
static inline bool DecayLifetime(GabyouUpdateItem *item, float decay)
{
    float minimum = 0.0f;
    item->lifetime -= decay;
    if (item->lifetime < minimum)
        return true;
    return false;
}
static inline void TickExpiry(GabyouUpdateItem *item, GabyouUpdateContext *context, int kind)
{
    switch (item->phase) {
    case 0:
        if (kind != 5)
            context->timer04 = 10;
        else
            context->timer04 = 0;
        ++item->phase;
        break;
    case 1:
        break;
    }
    if (context->timer04 == 0) {
        if (DecayLifetime(item, lbl_806D6090)) {
            Retire(item);
            return;
        }
    }
    Item_DecayVelocityScalar(item, lbl_806D6094);
    if ((int)item->kind == 9) {
        float gravity, velocity, turn;
        turn = lbl_806D608C;
        velocity = item->velocity.y;
        gravity = lbl_806D6098;
        item->velocity.y = velocity + gravity;
        item->rotationX = BuildOrientationFromYaw(turn + item->rotationX);
    }
}

void GabyouItem_Update(GabyouUpdateItem *item)
{
    GabyouUpdateContext *context = &item->context;
    const char *names = lbl_8032F598;
    float matrix[16];
    Vec3 matrixPosition;
    switch (item->state) {
    case 0:
        context->flag90 = 1;
        if (item->type == 0x43)
            SpriteSlot_InitNonLoop(item->sprite, 0x47);
        else
            SpriteSlot_InitNonLoop(item->sprite, 0x48);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(item->sprite, 1);
        context->matrixEnabled = 1;
        if (item->type == 0x43) {
            SpriteSlot_SetJointVisibilityByName(item->sprite, names + 0x428, 0x10, 0);
            SpriteSlot_SetJointVisibilityByName(item->sprite, names + 0x43C, 0x10, 1);
        } else {
            SpriteSlot_SetJointVisibilityByName(item->sprite, names + 0x450, 0x10, 0);
            SpriteSlot_SetJointVisibilityByName(item->sprite, names + 0x464, 0x10, 1);
        }
        item->category = 4;
        item->categoryPhase = 0;
        item->state = 1;
        item->phase = 0;
        /* fall through */
    case 1:
        GabyouItem_TickActive(item, context);
        break;
    case 2:
        switch ((signed char)item->kind) {
        case 0:
            ShellPile_Spawn(item, context);
            SoundMgr_PlaySE_Positional(0xC9, item->position, 0);
            Retire(item);
            break;
        case 3:
            switch (item->phase) {
            case 0:
                GetSpawnPosition(&item->velocity, lbl_806D6088, lbl_806D6088, lbl_806D6088);
                item->flag3C = 0;
                context->tetherTime = 0.0f;
                context->tetherScale = item->scale;
                ++item->phase;
                break;
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(item, &context->tetherTime, context->tetherScale,
                                          lbl_806D608C, lbl_806D608C) != 0)
                Retire(item);
            break;
        case 4:
            ShellPile_Spawn(item, context);
            SoundMgr_PlaySE_Positional(0xC9, item->position, 0);
            Retire(item);
            break;
        case 9:
            TickExpiry(item, context, (signed char)item->kind);
            break;
        case 5:
            TickExpiry(item, context, (signed char)item->kind);
            break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(item);
        SpriteSlot_Container_Free(item);
        return;
    }
    Vec3_Add_DestFirst(&item->position, &item->position, &item->velocity);
    if (context->matrixEnabled != 0) {
        Matrix4_Identity(matrix);
        Mtx44_Scale_Uniform(matrix, matrix, item->scale);
        Matrix4_PreMultiplyRotZ(matrix, matrix, item->rotationZ);
        Matrix4_PreMultiplyRotX(matrix, matrix, item->rotationX);
        Matrix4_PreMultiplyRotY(matrix, matrix, item->rotationY);
        /* Preserve the three IEEE-754 words when copying the ABI argument. */
        unsigned int first, second;
        first = ((const Vec3Words *)&item->position)->x;
        second = ((const Vec3Words *)&item->position)->y;
        ((Vec3Words *)&matrixPosition)->x = first;
        ((Vec3Words *)&matrixPosition)->y = second;
        ((Vec3Words *)&matrixPosition)->z = ((const Vec3Words *)&item->position)->z;
        Mtx44_Translate(matrix, matrix, &matrixPosition);
        DbgScene_CopyMatrix3x4Transpose(item->matrix, matrix);
    }
    if (context->timer04 != 0) --context->timer04;
    if (context->timer08 != 0) --context->timer08;
    if (context->timer0C != 0) --context->timer0C;
    if (context->timer10 != 0) --context->timer10;
}
}
