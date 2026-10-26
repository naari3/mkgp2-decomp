/* clItemBox destructor: free the debris particle array, then the box
 * itself when called as a deleting destructor. */
typedef struct clItemBoxDebris {
    int count;                 /* 0x00 */
    unsigned char items[0x294]; /* 0x04: 15 particles of 0x2c */
} clItemBoxDebris;

typedef struct clItemBox {
    unsigned char pad00[0x4];
    clItemBoxDebris *debris; /* 0x04 */
} clItemBox;

extern void clItemBoxResponder_DebrisParticle_Dtor(void *self, short flag);
extern void __destroy_arr(void *arr, void *dtor, unsigned long size, unsigned long count);
extern void MemoryManager_TimedFree(void *p);

clItemBox *clItemBox_Dtor(clItemBox *self, short flag)
{
    clItemBoxDebris *debris;

    if (self != 0) {
        debris = self->debris;
        if (debris != 0) {
            __destroy_arr(debris->items, clItemBoxResponder_DebrisParticle_Dtor, 0x2c, 0xf);
            MemoryManager_TimedFree(debris);
        }
        self->debris = 0;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
