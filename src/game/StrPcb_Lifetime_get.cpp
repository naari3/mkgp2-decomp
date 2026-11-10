#include "game/StrPcbLifetimePrivate.h"

extern "C" StrPcb *StrPcb_GetInstance(void)
{
    return StrPcb_bss_806D1010;
}

