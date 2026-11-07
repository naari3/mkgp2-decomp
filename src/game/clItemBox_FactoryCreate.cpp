/* clItemBox_FactoryCreate: allocate one item box for a spawn-table entry.
 * Flag bit 0 picks the ground-snapped (x, z) constructor. GC/2.7 (like
 * Vec3_ToYaw.c): the flag load schedules ahead of the r30 save. */
void *operator new(unsigned long size);
void operator delete(void *p);

struct ItemBoxSpawnEntry {
    float x;
    float y;
    float z;
    unsigned int flags;
};

class clItemBox {
public:
    clItemBox(float x, float z);
    clItemBox(float x, float y, float z);

private:
    unsigned char m_body[0x34];
};

extern "C" clItemBox *clItemBox_FactoryCreate(const ItemBoxSpawnEntry *entry) {
    if (entry->flags & 1) {
        return new clItemBox(entry->x, entry->z);
    }
    return new clItemBox(entry->x, entry->y, entry->z);
}
