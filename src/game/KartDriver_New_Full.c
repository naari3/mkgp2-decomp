/* Observed forwarding constructor; no allocation and no cleanup action. */
#pragma cplusplus on
#pragma exceptions on

struct KartFullDisplay {
    unsigned char opaque[0x380];
    KartFullDisplay();
    /* Trivial destruction: the target has only a plain exception record. */
};

struct KartFullDriver : KartFullDisplay {
    KartFullDriver(int slot, int character, float* matrix,
                   int raceSlot, int displayMode, int modelMode);
};

extern "C" int KartDriver_InitFull(void* self, int slot, int character,
                                   float* matrix, int raceSlot,
                                   int displayMode, int modelMode);

KartFullDriver::KartFullDriver(int slot, int character, float* matrix,
                               int raceSlot, int displayMode, int modelMode)
    : KartFullDisplay()
{
    KartDriver_InitFull(this, slot, character, matrix,
                        raceSlot, displayMode, modelMode);
}

#pragma exceptions reset
#pragma cplusplus off


