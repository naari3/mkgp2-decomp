/* JObj_SetExpressionByIndex @ 0x8003DDAC: show the face joint for the
 * requested expression and hide the other three. */

void JObj_Show(void *character, void *joint, unsigned int flags);
void JObj_Hide(void *character, void *joint, unsigned int flags);

typedef struct ExprObj {
    unsigned char pad0[0x1C];
    void *character;
    unsigned char pad20[0x140 - 0x20];
    void *face[4];
} ExprObj;

int JObj_SetExpressionByIndex(ExprObj *self, int index)
{
    if (self->character == 0) {
        return 0;
    }
    switch (index) {
    case 0:
        if (self->face[0]) JObj_Show(self->character, self->face[0], 0x10);
        if (self->face[1]) JObj_Hide(self->character, self->face[1], 0x10);
        if (self->face[2]) JObj_Hide(self->character, self->face[2], 0x10);
        if (self->face[3]) JObj_Hide(self->character, self->face[3], 0x10);
        break;
    case 1:
        if (self->face[0]) JObj_Hide(self->character, self->face[0], 0x10);
        if (self->face[1]) JObj_Show(self->character, self->face[1], 0x10);
        if (self->face[2]) JObj_Hide(self->character, self->face[2], 0x10);
        if (self->face[3]) JObj_Hide(self->character, self->face[3], 0x10);
        break;
    case 2:
        if (self->face[0]) JObj_Hide(self->character, self->face[0], 0x10);
        if (self->face[1]) JObj_Hide(self->character, self->face[1], 0x10);
        if (self->face[2]) JObj_Show(self->character, self->face[2], 0x10);
        if (self->face[3]) JObj_Hide(self->character, self->face[3], 0x10);
        break;
    default:
        if (self->face[0]) JObj_Hide(self->character, self->face[0], 0x10);
        if (self->face[1]) JObj_Hide(self->character, self->face[1], 0x10);
        if (self->face[2]) JObj_Hide(self->character, self->face[2], 0x10);
        if (self->face[3]) JObj_Show(self->character, self->face[3], 0x10);
        break;
    }
    return 1;
}
