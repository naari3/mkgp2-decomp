#include "game/InputCmd.h"

/* The leaf accessors use only the first pointer in this 8-byte SDA symbol. */
extern void *InputCmd_data_806CEE50[2];

void InputCmd_SetCooldown(InputCmdView *self, int cooldown)
{
    self->cooldown = cooldown;
}

unsigned char InputCmd_GetDetectedFlag(InputCmdView *self)
{
    return self->detected;
}

void *InputCmd_GetGlobalConfig(void)
{
    return InputCmd_data_806CEE50[0];
}

void InputCmd_SetGlobalConfig(void *config)
{
    InputCmd_data_806CEE50[0] = config;
}

/* Preserve the unmangled external constructor bridge used by array lifetime. */
InputCmdSampleView *fn_8005B10C(InputCmdSampleView *self)
{
    self->live = 0;
    return self;
}
