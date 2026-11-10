#include "game/types/JyugemuFlag.h"

int Jyugemu_Flag_SetKartDriver(JyugemuFlag *self, void *kart_driver)
{
    if (self->kart_driver != 0) {
        return 0;
    }

    self->kart_driver = kart_driver;
    return 1;
}
