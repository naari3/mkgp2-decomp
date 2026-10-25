extern "C" void fn_801DB8BC(void *self);
extern "C" void fn_801E2C40(void *self);

struct PathStorage {
    char pad[0xC];
    void *data;

    ~PathStorage() {
        if (data) {
            delete data;
        }
    }
};

struct PathBuffer {
    PathStorage storage;
};

struct PathCursor {
    int unk0;
    PathBuffer buffer;

    ~PathCursor() { fn_801E2C40(this); }
};

struct PathTracker {
    char pad[0x70];
    PathCursor cursor;

    ~PathTracker();
};

PathTracker::~PathTracker() {
    fn_801DB8BC(this);
}
