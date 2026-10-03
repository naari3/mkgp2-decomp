/* Destructor-only bridges and observed constructor field views. */
#pragma cplusplus on
void* operator new(unsigned long);
void operator delete(void*);
struct DemoWCScene;
struct DemoWCNormal;
struct DemoWCDriver;
struct DemoWCTornado;
extern "C" {
extern const float lbl_806D4F94, lbl_806D4F98, lbl_806D4FA8;
extern const char* lbl_806CF2C8;
extern const char* lbl_806CF2CC;
extern int g_characterId;
extern unsigned char g_lakituStartAnimDone;
extern void* g_raceCamera;
void MTXIdentity(float*);
void SetResourceLoadingFlag(unsigned char);
void* DrawManager_GetOrCreate();
void DMAChannelManager_Init();
void SoundChannels_ClearAll();
void ItemObjectManager_Init();
void CourseObjectManager_Init();
void ProcessSystemTick(int);
int GetDisplayBufferIndex();
unsigned char clNormal3D_SetScale(DemoWCNormal*, void*, float, float, float, float);
void* ResolveJointByName(DemoWCNormal*, const char*);
void SetCourseScene3D(DemoWCScene*);
int SceneDrawList_RegisterArchive(void*, int);
void fn_802C6430(void*, void*);
void fn_802C6640(void*, float);
void fn_802C65F0(void*);
}
struct DemoWCRoot {
    DemoWCRoot();
    virtual ~DemoWCRoot();
    virtual void identity();
};
struct DemoWCBase : DemoWCRoot {
    DemoWCBase() {}
    virtual ~DemoWCBase();
    virtual void identity();
};
struct DemoWCAnimLeaf { void* value; };
struct DemoWCAnimNode { void* opaque; DemoWCAnimLeaf* next; };
struct DemoWCDescriptor { void* opaque; DemoWCAnimNode* next; };
static inline void* leaf_value(DemoWCAnimLeaf* leaf)
{
    if (leaf == 0) return 0;
    return leaf->value;
}
static inline void* node_value(DemoWCAnimNode* node)
{
    if (node == 0) return 0;
    return leaf_value(node->next);
}
static inline void* descriptor_value(DemoWCDescriptor* descriptor)
{
    if (descriptor == 0) return 0;
    return node_value(descriptor->next);
}
struct DemoWCSceneRoot { virtual void identity(); };
struct DemoWCSceneBase : DemoWCSceneRoot {
    void* camera;
    unsigned char opaque8[0x24];
    DemoWCDescriptor* descriptor;
    unsigned char opaque30[0x3054];
    unsigned char active, opaque3085[3];
    DemoWCSceneBase(const char*);
    virtual void identity();
};
struct DemoWCScene : DemoWCSceneBase {
    float speed, frame;
    DemoWCScene(const char* path) : DemoWCSceneBase(path) {
        speed = lbl_806D4FA8;
        frame = lbl_806D4F94;
    }
    virtual void identity();
    void start() {
        if (camera) {
            active = 1;
            frame = lbl_806D4F94;
            speed = lbl_806D4F98;
            fn_802C6430(camera, descriptor_value(descriptor));
            fn_802C6640(camera, frame);
            fn_802C65F0(camera);
        }
    }
};
struct DemoWCNormal {
    unsigned char opaque[0x24];
    void* archive;
    unsigned char opaque28[0x34];
    DemoWCNormal(const char*, int);
};
struct DemoWCDriverBase {
    unsigned char opaque[0x384];
    DemoWCDriverBase(int, int, float*, int, int, int);
};
struct DemoWCDriver : DemoWCDriverBase {
    DemoWCDriver(int character, float* matrix) :
        DemoWCDriverBase(GetDisplayBufferIndex(), character, matrix, 0, 0, 0) {}
};
struct DemoWCTornado {
    unsigned char opaque[0x154];
    DemoWCTornado(unsigned char, DemoWCDriver*, int, unsigned char, float, float, float);
};
struct DemoWCAux {
    unsigned char opaque[0x24];
    DemoWCAux();
};
struct DemoWCOwner : DemoWCBase {
    unsigned char enabled, opaque5[3];
    float phase;
    DemoWCScene* scene;
    int drawHandle;
    DemoWCNormal* normal;
    DemoWCDriver* driver;
    DemoWCTornado* tornado;
    float matrix[12];
    void* joint;
    int counter;
    DemoWCAux* auxiliary;
    DemoWCOwner();
    virtual void identity();
};
DemoWCOwner::DemoWCOwner()
{
    enabled = 1;
    phase = lbl_806D4F94;
    scene = 0;
    drawHandle = -1;
    normal = 0;
    driver = 0;
    tornado = 0;
    joint = 0;
    MTXIdentity(matrix);
    SetResourceLoadingFlag(0);
    DrawManager_GetOrCreate();
    DMAChannelManager_Init();
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    scene = new DemoWCScene(lbl_806CF2C8);
    scene->start();
    normal = new DemoWCNormal(lbl_806CF2C8, 0);
    clNormal3D_SetScale(normal, 0, lbl_806D4F94, lbl_806D4F98, lbl_806D4F94, lbl_806D4F94);
    ProcessSystemTick(0);
    driver = new DemoWCDriver(g_characterId, matrix);
    tornado = new DemoWCTornado(0, driver, g_characterId, 0, lbl_806D4F94, lbl_806D4F94, lbl_806D4F94);
    joint = ResolveJointByName(normal, lbl_806CF2CC);
    counter = 0;
    auxiliary = new DemoWCAux;
    g_raceCamera = 0;
    g_lakituStartAnimDone = 0;
    SetCourseScene3D(scene);
    drawHandle = SceneDrawList_RegisterArchive(normal->archive, 4);
    SetResourceLoadingFlag(1);
}
#pragma cplusplus off

