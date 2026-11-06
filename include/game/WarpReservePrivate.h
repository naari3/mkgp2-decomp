#ifndef GAME_WARP_RESERVE_PRIVATE_H
#define GAME_WARP_RESERVE_PRIVATE_H

extern "C" {
unsigned long strlen(const char *);
char *strcpy(char *, const char *);
void *FUN_8003b120(unsigned long);
void *Alloc(unsigned long);
void MemoryManager_TimedFree(void *);
extern const char lbl_803284A4[];
}
inline void *operator new(unsigned long, void *p) throw() { return p; }
inline void operator delete(void *, void *) throw() {}

/* Four corners have nontrivial lifetime; the two remaining vectors are plain. */
struct WarpPlainVector { float x, y, z; };
struct WarpCorner : WarpPlainVector {
    WarpCorner(const WarpCorner &v) : WarpPlainVector(v) {}
    ~WarpCorner();
};
struct WarpZoneValue {
    unsigned long flags;
    WarpCorner corners[4];
    WarpPlainVector vector1, vector2;
    float distance;
};

struct WarpErrorString {
    char *ptr;
    void *control;
    WarpErrorString(void *);
    ~WarpErrorString();
};
struct WarpErrorMessage {
    WarpErrorString storage;
    ~WarpErrorMessage();
    WarpErrorMessage(const char *s) : storage(FUN_8003b120(strlen(s) + 1)) {
        strcpy(storage.ptr, s);
    }
};
namespace std {
struct exception { exception() {} virtual ~exception(); };
struct logic_error : exception {
    WarpErrorMessage message;
    logic_error(const char *s) : message(s) {}
    virtual ~logic_error();
};
struct length_error : logic_error {
    length_error(const char *s) : logic_error(s) {}
    virtual ~length_error();
};
}

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
extern "C" {
void WarpZoneVector_Clear(WarpZoneVectorStorage *);
void WarpZoneArray_UninitFillN(WarpZoneValue *, unsigned long, const WarpZoneValue *);
WarpZoneValue *WarpZoneArray_CopyBackward(WarpZoneValue *, WarpZoneValue *, WarpZoneValue *);
}
extern "C" void WarpZoneVector_ClearCall(WarpZoneVectorStorage *);
inline WarpZoneVectorStorage::~WarpZoneVectorStorage() {
    WarpZoneVector_ClearCall(this);
    if (data) MemoryManager_TimedFree(data);
}

#endif
