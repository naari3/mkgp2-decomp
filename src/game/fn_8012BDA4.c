/* fn_8012BDA4: starts the kart preview's character pose animation. */
#include "game/types/KartPreviewParts.h"

#include "game/types/CharacterDataEntry.h"

extern CharacterDataEntry *GetCharacterDataEntry(int id);

void fn_8012BDA4(KartPreviewParts *self)
{
    self->animNext = 0x2B;
    self->f108 = 0.0f;
    self->f10C = 1.0f;
    self->f154 = GetCharacterDataEntry(self->characterId)->pose;
}
