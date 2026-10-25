/* dolsdk2004 src/odemustubs/odemustubs.c
 * Only the two functions the game keeps. The weak Hu_IsStub (returning 1)
 * lost to odenotstub's definition, and the DB I/O stubs were dead-stripped. */

void DBInitComm(int* inputFlagPtr, int* mtrCallback) {}

void DBInitInterrupts() {}
