#ifndef GAME_TYPES_WARPZONEVECTORSTORAGE_H
#define GAME_TYPES_WARPZONEVECTORSTORAGE_H

/* Declare before including (each user already does): WarpZoneValue */

struct WarpZoneVectorStorage {
    unsigned long capacity, count;
    WarpZoneValue *data;
    WarpZoneVectorStorage() : capacity(0), count(0), data(0) {}
    ~WarpZoneVectorStorage();
    void swap(WarpZoneVectorStorage &other) {
        if (this != &other) {
            unsigned long c = capacity; capacity = other.capacity; other.capacity = c;
            WarpZoneValue *p = data; data = other.data; other.data = p;
            unsigned long n = count; count = other.count; other.count = n;
        }
    }
};

#endif /* GAME_TYPES_WARPZONEVECTORSTORAGE_H */
