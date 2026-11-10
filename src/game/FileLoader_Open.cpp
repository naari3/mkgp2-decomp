/* Shared file-loader cache open/release and collision special-face
 * registration, 0x80034EC0..0x80035220. The FileLoader layout matches
 * clRomLifecycle.c and FileLoader_LoadBin.c.
 *
 * Object_ReleaseAnimResource_Impl: the target `bne; b exit` after the
 * archive test is the last term of `if (a == 0 || b == 1) return;`. */
void *operator new(unsigned long size);
void operator delete(void *ptr);

struct FileLoader;

extern "C" {
extern FileLoader *g_romListHead; /* head */
extern FileLoader *g_romListTail; /* tail */
extern int g_romActiveCount; /* live count */
extern int g_romActiveCountPeak; /* peak count */
extern unsigned char g_resourceLoadingFlag;
extern char lbl_802E9800[];
int strcmp(const char *a, const char *b);
void *DVDLoad_OpenAllocReadRelocSync(const char *path);
void DebugPrintf(const char *fmt, ...);
void HSD_ArchiveFree(void *archive);
void HSD_Free(void *block);
void *HSD_ArchiveTakeData(void *archive);
}

struct FileLoader {
    int references;
    const char *path;
    FileLoader *previous;
    FileLoader *next;
    void *archive;
    unsigned char rawBlock;

    FileLoader(const char *name)
    {
        int attempt;

        g_romActiveCount++;
        if (g_romActiveCountPeak < g_romActiveCount) {
            g_romActiveCountPeak = g_romActiveCount;
        }
        rawBlock = 0;
        references = 1;
        path = name;
        previous = 0;
        next = 0;
        archive = 0;
        attempt = 1;
        while ((archive = DVDLoad_OpenAllocReadRelocSync(name)) == 0) {
            attempt++;
            DebugPrintf(lbl_802E9800, attempt);
        }
        if (g_romListHead == 0) {
            g_romListHead = this;
            g_romListTail = this;
        } else {
            previous = g_romListTail;
            g_romListTail->next = this;
            g_romListTail = this;
        }
    }

    ~FileLoader()
    {
        --g_romActiveCount;
        if (archive != 0) {
            if (rawBlock == 0) {
                HSD_ArchiveFree(archive);
            } else {
                HSD_Free(archive);
            }
        }
        if (previous == 0) {
            g_romListHead = next;
        } else {
            previous->next = next;
        }
        if (next == 0) {
            g_romListTail = previous;
        } else {
            next->previous = previous;
        }
    }
};

static inline FileLoader *FileLoader_Find(const char *name)
{
    FileLoader *p;

    for (p = g_romListHead; p != 0; p = p->next) {
        if (strcmp(p->path, name) == 0) {
            return p;
        }
    }
    return 0;
}

extern "C" FileLoader *FileLoader_Open(const char *name)
{
    FileLoader *p = FileLoader_Find(name);

    if (p != 0) {
        p->references++;
        return p;
    }
    p = new FileLoader(name);
    if (p->archive == 0) {
        delete p;
        return 0;
    }
    if (g_resourceLoadingFlag == 1) {
        p->references++;
    }
    return p;
}

extern "C" void Object_ReleaseAnimResource_Impl(FileLoader *p)
{
    if (p->archive == 0 || p->rawBlock == 1) {
        return;
    }
    p->rawBlock = 1;
    void *data = HSD_ArchiveTakeData(p->archive);
    HSD_ArchiveFree(p->archive);
    p->archive = data;
}

struct SpecialFace {
    float v[9];
    unsigned char pad24[0xC];
    int type; /* 0x30 */
};

struct CollFace {
    unsigned char pad00[0x10];
    float v[9]; /* 0x10 */
    unsigned char pad34[0x28];
    unsigned int flags; /* 0x5C */
    unsigned char pad60[0x10];
};

struct CollGroup {
    CollFace *faces;
    int count;
    unsigned char pad08[8];
};

struct CollData {
    unsigned char pad00[0x28];
    CollGroup *groups; /* 0x28 */
};

struct SpecialFaceMesh;

extern "C" {
extern SpecialFaceMesh *lbl_806D1138;
extern CollData *g_collisionData;
void SpecialFaceMesh_AddFace(SpecialFaceMesh *mesh, SpecialFace *face);
}

static inline SpecialFaceMesh *SpecialFaceMesh_Get(void)
{
    SpecialFaceMesh *m = lbl_806D1138;
    if (m == 0) {
        return 0;
    }
    return m;
}

extern "C" int Collision_RegisterSpecialFaces(void)
{
    SpecialFaceMesh *mesh;
    CollData *cd;
    int count;
    int i;

    if (SpecialFaceMesh_Get() == 0) {
        return -1;
    }
    mesh = SpecialFaceMesh_Get();
    cd = g_collisionData;
    count = 0;
    for (i = 0; cd->groups[i].faces != 0; i++) {
        CollFace *f = cd->groups[i].faces;
        int n = cd->groups[i].count;
        while (n-- > 0) {
            if (f->flags & 0x80000000) {
                SpecialFace face;
                face.v[0] = f->v[0];
                face.v[1] = f->v[1];
                face.v[2] = f->v[2];
                face.v[3] = f->v[3];
                face.v[4] = f->v[4];
                face.v[5] = f->v[5];
                face.v[6] = f->v[6];
                face.v[7] = f->v[7];
                face.v[8] = f->v[8];
                face.type = 3;
                SpecialFaceMesh_AddFace(mesh, &face);
                count++;
            }
            f++;
        }
    }
    return count;
}
