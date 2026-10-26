/* clItemBoxResponder command-slot helpers. */

typedef struct clItemBoxResponder {
    unsigned char pad00[0x4];
    void *boundPos; /* 0x04 */
    int cmdTimer;   /* 0x08 */
} clItemBoxResponder;

int clItemBoxResponder_IsCmdSlotFree(clItemBoxResponder *self)
{
    return self->cmdTimer <= 0;
}

void clItemBoxResponder_CmdSlotCountdown(clItemBoxResponder *self)
{
    if (self->cmdTimer > 0) {
        self->cmdTimer--;
    }
}

void *clItemBoxResponder_GetBoundPosVec3(clItemBoxResponder *self)
{
    return self->boundPos;
}
