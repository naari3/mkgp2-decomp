/* PathManager_Init @ 0x8003D1F4: the path manager constructor. The path
 * manager embeds the path cursor at offset 0 (PathCursor_InitFromPath /
 * PathCursor_Free); its destructor is PathParticipantArray_Dtor. */

class PathCursor {
public:
    PathCursor(void *path);
    ~PathCursor();
    void ResetToPath(void *path);

    unsigned char pad_0[0x14];
};

struct PathParticipant {
    unsigned char pad_0[0x14];
    int node;
    unsigned char pad_18[0x80];
};

class PathManager {
public:
    PathManager(void *path, int c, int d, void *car, int a, int b);
    void RegisterCarObject(void *car, int a, int b, int c, int d, int e);

    void DetachAll()
    {
        int i;

        for (i = 0; i < 8; i++) {
            karts()[i].node = -1;
            active[i] = 0;
        }
    }
    PathParticipant *karts() { return (PathParticipant *)this; }

    PathCursor cursor;
    unsigned char pad_14[0x4C0];
    unsigned char active[8];
};

#pragma exceptions on

PathManager::PathManager(void *path, int c, int d, void *car, int a, int b) : cursor(0)
{
    DetachAll();
    DetachAll();
    cursor.ResetToPath(path);
    if (car != 0) {
        RegisterCarObject(car, a, b, c, d, 0);
    }
}

#pragma exceptions reset
