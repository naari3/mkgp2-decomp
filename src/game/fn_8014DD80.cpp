/*
 * 0x8014DD80..0x8014E004: scene cache lookup / create.
 *
 * Returns the cached scene object for (id, type), bumping its reference
 * count, or creates it (normal model, 3D scene, animated-camera 3D scene or
 * scene model, named by the id's archive path) and appends it to the cache.
 */
#pragma cplusplus on

void *operator new(unsigned long);
void operator delete(void *);

extern const char *lbl_80364368[];

struct SceneCacheNormal {
    unsigned char opaque[0x5c];
    SceneCacheNormal(const char *path, int flags);
};

struct SceneCacheAnimLeaf { void *value; };
struct SceneCacheAnimNode { void *opaque; SceneCacheAnimLeaf *next; };
struct SceneCacheDescriptor { void *opaque; SceneCacheAnimNode *next; };

static inline void *leaf_value(SceneCacheAnimLeaf *leaf)
{
    if (leaf == 0) return 0;
    return leaf->value;
}

static inline void *node_value(SceneCacheAnimNode *node)
{
    if (node == 0) return 0;
    return leaf_value(node->next);
}

static inline void *descriptor_value(SceneCacheDescriptor *descriptor)
{
    if (descriptor == 0) return 0;
    return node_value(descriptor->next);
}

extern "C" {
void HSD_CObjAddAnim(void *cobj, void *anim);
void HSD_CObjReqAnim(void *cobj, float frame);
void HSD_CObjAnim(void *cobj);
}

struct SceneCacheSceneRoot { virtual void identity(); };

struct SceneCacheScene : SceneCacheSceneRoot {
    void *camera;                       /* 0x0004 */
    unsigned char opaque8[0x24];
    SceneCacheDescriptor *descriptor;   /* 0x002C */
    unsigned char opaque30[0x3054];
    SceneCacheScene(const char *path);
    virtual void identity();
};

struct SceneCacheAnimScene : SceneCacheScene {
    unsigned char active, opaque3085[3]; /* 0x3084 */
    float speed;                         /* 0x3088 */
    float frame;                         /* 0x308C */
    SceneCacheAnimScene(const char *path) : SceneCacheScene(path) {
        speed = -1.0f;
        frame = 0.0f;
    }
    virtual void identity();
    void start() {
        if (camera) {
            active = 1;
            frame = 0.0f;
            speed = 1.0f;
            HSD_CObjAddAnim(camera, descriptor_value(descriptor));
            HSD_CObjReqAnim(camera, frame);
            HSD_CObjAnim(camera);
        }
    }
};

struct SceneCacheModel {
    unsigned char opaque[0x28];
    SceneCacheModel(const char *path, int flags);
};

struct SceneCacheEntry {
    unsigned int key;  /* id | type << 29 */
    int refCount;
    void *obj;
};

struct SceneCacheLink {
    SceneCacheLink *prev;
    SceneCacheLink *next;
};

struct SceneCacheNode : SceneCacheLink {
    SceneCacheEntry entry;
};

struct SceneCacheIter {
    SceneCacheIter(SceneCacheLink *n) : node(n) {}
    SceneCacheLink *node;
};

struct SceneCacheList {
    unsigned int count;
    SceneCacheLink anchor;
    SceneCacheIter end() { return SceneCacheIter(&anchor); }
    SceneCacheIter insert(const SceneCacheIter &pos, const SceneCacheEntry &entry);
};

extern "C" void *fn_8014DD80(SceneCacheList *list, unsigned int id, unsigned int type)
{
    SceneCacheEntry entry;
    SceneCacheLink *node;
    unsigned int key;

    if (id >= 29 || type >= 4) {
        return 0;
    }

    key = id | (type << 29);
    if (list->count != 0) {
        for (node = list->anchor.next; node != &list->anchor; node = node->next) {
            if (((SceneCacheNode *)node)->entry.key == key) {
                ((SceneCacheNode *)node)->entry.refCount++;
                return ((SceneCacheNode *)node)->entry.obj;
            }
        }
    }

    entry.key = key;
    entry.refCount = 1;
    switch (type) {
    case 0:
        entry.obj = new SceneCacheNormal(lbl_80364368[id], 0);
        if (entry.obj == 0) {
            return 0;
        }
        break;
    case 1:
        entry.obj = new SceneCacheScene(lbl_80364368[id]);
        if (entry.obj == 0) {
            return 0;
        }
        break;
    case 2: {
        SceneCacheAnimScene *scene = new SceneCacheAnimScene(lbl_80364368[id]);
        entry.obj = scene;
        if (scene == 0) {
            return 0;
        }
        scene->start();
        break;
    }
    case 3:
        entry.obj = new SceneCacheModel(lbl_80364368[id], 1);
        if (entry.obj == 0) {
            return 0;
        }
        break;
    default:
        return 0;
    }

    SceneCacheIter pos = list->end();
    list->insert(pos, entry);
    return entry.obj;
}
