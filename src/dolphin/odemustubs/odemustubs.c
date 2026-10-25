/* dolsdk2004 src/odemustubs/odemustubs.c
 * Only DBClose/DBOpen survive: the real ODEMU library right after this unit
 * provides DBWrite/DBRead/DBQueryData/DBInitInterrupts/DBInitComm (MetroTRK's
 * gdev calls them), the weak Hu_IsStub (returning 1) lost to odenotstub's
 * definition, and the remaining stubs were dead-stripped. */

void DBClose() {}

void DBOpen() {}
