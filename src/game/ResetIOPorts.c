/* ResetIOPorts @ 0x80084FF0, 192 bytes. */
#include "game/ResetIOPorts_private.h"

extern int g_localPcbRole;
extern int g_myPcbId;
extern void *lbl_806D11B0;
extern void *GetDisplayContext(int pcbIndex);
extern ResetIOPort lbl_805A6154[4];

#pragma exceptions on
int ResetIOPorts(void) {
    int role;
    ResetIOPort *port;
    int i;

    if (g_localPcbRole == 0) {
        return 0;
    }
    lbl_806D11B0 = GetDisplayContext(g_myPcbId - 1);
    role = g_localPcbRole;
    port = lbl_805A6154;
    for (i = 0; i < 4; i++, port++) {
        if (((port->header >> 4) & 7) == role) {
            port->status = 0x40;
        }
    }
    return 1;
}
#pragma exceptions reset
