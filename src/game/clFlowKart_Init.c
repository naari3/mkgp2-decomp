/* clFlowKart_Init: FlowKart constructor (C++, compiled with -lang=c++).
 * The TU owns .rodata 0x8039E508..0x8039E9F8 so the pooled base register is
 * hoisted to the prologue like the target. Unused objects stay global so they
 * are emitted in place; "cone.dat" is a string literal emitted after them.
 * Mangled names are mapped to the original symbols in
 * tools/extab_user_renames.json.
 */
#pragma readonly_strings on

void* operator new(unsigned long);
void operator delete(void*);
struct FKScene;
struct FKDriver;
struct FKTex;
struct FKVec { float x, y, z; };
/* .rodata 0x8039E508..0x8039E9F8 */
extern "C" {
extern const unsigned int lbl_8039E508[0x10C];
/* tables used by other clFlowKart functions */
const unsigned int lbl_8039E508[0x10C] = {
    0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x0000001E, 0x000005BE, 0x000004CE,
    0x00000096, 0x000002EE, 0x00000546, 0x0000010E, 0x00000276, 0x000003DE,
    0x00000186, 0x00000456, 0x000001FE, 0x00000366,
};
/* coin mileage needed per character */
extern const int g_kartEnhancedUnlockThreshold[13];
const int g_kartEnhancedUnlockThreshold[13] = {
    0x00000636, 0x00000BD6, 0x00000AE6, 0x000006AE, 0x00000906, 0x00000B5E,
    0x00000726, 0x0000088E, 0x000009F6, 0x0000079E, 0x00000A6E, 0x00000816,
    0x0000097E,
};
/* texture index per character */
extern const int lbl_8039E96C[13];
const int lbl_8039E96C[13] = {
    0x00000002, 0x00000002, 0x00000003, 0x00000001, 0x00000003, 0x00000000,
    0x00000003, 0x00000001, 0x00000002, 0x00000000, 0x00000001, 0x00000002,
    0x00000000,
};
extern const int lbl_8039E9A0[3];
const int lbl_8039E9A0[3] = {
    0x00000000, 0x00000000, 0x00000000,
};
}
static const FKVec s_position = { 10.0f, -5.5f, 3.0f };
extern "C" {
extern const int lbl_8039E9B8[5];
const int lbl_8039E9B8[5] = { 0x16B4, 0x16B3, 0x16B2, 0x16B1, 0x16B0 };
extern const char clFlowKart[];
const char clFlowKart[] = "clFlowKart";
extern const char clFlowProcess[];
const char clFlowProcess[] = "clFlowProcess";
}
struct FKInput {
    unsigned char opaque0[4], enabled, opaque5[0x13];
    int first, second;
};
extern "C" {
extern unsigned int g_characterId;
extern FKInput* g_pInputState;
extern unsigned char g_playerData[];
extern const float lbl_806DA130, lbl_806DA134, lbl_806DA138, lbl_806DA13C;
extern const float lbl_806DA144, lbl_806DA14C, lbl_806DA154, lbl_806DA15C;
extern const float lbl_806DA174, lbl_806DA178, lbl_806DA17C, lbl_806DA180;
extern const float lbl_806DA184, lbl_806DA188, lbl_806DA18C;
void SetSyncTarget(int);
unsigned char PreloadResource(int);
int CObj_LoadIntoGX(FKScene*, const FKVec*);
int CObj_ApplyViewport(FKScene*, const FKVec*);
void PSMTXScale(float*, float, float, float);
void PSMTXTrans(float*, float, float, float);
void PSMTXIdentity(float*);
void PSMTXConcat(const float*, const float*, float*);
void PSMTXRotRad(float*, int, float);
unsigned char RenderObj_ItemStateMachine_Timed(FKDriver*, int, float, float);
unsigned char SetScreenBrightness(float);
unsigned char fn_801B8918(int);
const char* GetTextureByIdAndLang(unsigned int, int);
void TexMgr_SetTexture(FKTex*, const char*, ...);
void fn_801F93EC(FKTex*, float, float);
int isJapanese();
int GetCoinMilage(const void*);
unsigned char InitRumbleController(unsigned char);
}
struct FKBase {
    FKBase();
    virtual ~FKBase();
    virtual void identity();
};
struct FKResource {
    int id, chain, mode, opaqueC;
    unsigned char enabled, opaque11[3];
    float x, y, z, scaleX, scaleY, angle, width, height;
    int parameters[4];
    unsigned char opaque44[0x14];
    FKResource();
    ~FKResource();
};
struct FKScene { unsigned char opaque[0x3084]; FKScene(const char*); };
struct FKModel { unsigned char opaque[0x28]; FKModel(const char*, unsigned char); };
struct FKDriver { unsigned char opaque[0x384]; FKDriver(int, int, float*, int, int, int); };
struct FKTex { unsigned char opaque[0x22c]; float scale; FKTex(); };
static inline FKInput* input()
{
    if (g_pInputState == 0) return 0;
    return g_pInputState;
}
static inline int indexed_value(const int* table, unsigned int index)
{
    return table[index];
}
static inline void copy_position(FKVec* destination, const FKVec* source)
{
    *destination = *source;
}
struct FKOwner : FKBase {
    int state, selection, opaqueC;
    unsigned char active, opaque11[3];
    int counter;
    float scale;
    FKScene* scene;
    FKModel* model;
    FKDriver* driver;
    FKDriver* alternate;
    float matrix[12];
    FKVec position;
    int slots[3], values[3];
    FKTex* texture;
    FKResource resource;
    FKOwner();
    virtual void identity();
};
FKOwner::FKOwner()
{
    FKVec vector;
    float translation[12], rotation[12], scaling[12];
    float z, zero, initialScale;
    int character;
    SetSyncTarget(15);
    PreloadResource(0x167f);
    state = 1;
    selection = -1;
    opaqueC = 0;
    active = 0;
    driver = 0;
    alternate = 0;
    scene = new FKScene("cone.dat");
    model = new FKModel("cone.dat", 0);
    initialScale = lbl_806DA174;
    zero = lbl_806DA13C;
    z = lbl_806DA178;
    slots[0] = 0;
    slots[1] = 0;
    slots[2] = 0;
    scale = initialScale;
    counter = 0;
    values[0] = 0;
    values[1] = 0;
    values[2] = 0;
    vector.x = zero;
    vector.y = zero;
    vector.z = z;
    CObj_LoadIntoGX(scene, &vector);
    vector.x = lbl_806DA13C;
    vector.y = lbl_806DA13C;
    vector.z = lbl_806DA13C;
    CObj_ApplyViewport(scene, &vector);
    character = g_characterId;
    PSMTXScale(scaling, lbl_806DA130, lbl_806DA130, lbl_806DA130);
    copy_position(&position, &s_position);
    PSMTXTrans(translation, position.x, position.y, position.z);
    PSMTXIdentity(matrix);
    PSMTXConcat(scaling, matrix, matrix);
    PSMTXRotRad(rotation, 'x', lbl_806DA134);
    PSMTXConcat(rotation, matrix, matrix);
    PSMTXRotRad(rotation, 'y', lbl_806DA138);
    PSMTXConcat(rotation, matrix, matrix);
    PSMTXConcat(translation, matrix, matrix);
    driver = new FKDriver(6, character, matrix, 0, 0, 0);
    alternate = new FKDriver(6, character, matrix, 0, 0, 2);
    if (driver) RenderObj_ItemStateMachine_Timed(driver, 0, lbl_806DA13C, lbl_806DA13C);
    if (alternate) RenderObj_ItemStateMachine_Timed(alternate, 0, lbl_806DA13C, lbl_806DA13C);
    if (input()) {
        FKInput* controller = input();
        controller->enabled = 1;
        controller->first = 0;
        controller->second = 0;
    }
    SetScreenBrightness(lbl_806DA144);
    fn_801B8918(0x1ae2);
    texture = new FKTex;
    TexMgr_SetTexture(texture, GetTextureByIdAndLang(indexed_value(lbl_8039E96C, g_characterId) + 0x95, -1));
    fn_801F93EC(texture, lbl_806DA17C, lbl_806DA14C);
    texture->scale = !isJapanese() ? lbl_806DA180 : lbl_806DA184;
    resource.id = 0x1d5c;
    resource.width = lbl_806DA188;
    resource.height = lbl_806DA188;
    resource.enabled = 1;
    resource.x = lbl_806DA18C;
    resource.y = lbl_806DA154;
    resource.z = lbl_806DA15C;
    character = g_characterId;
    if (GetCoinMilage(g_playerData) < g_kartEnhancedUnlockThreshold[character]) {
        resource.parameters[0] = -256;
        resource.parameters[1] = -256;
        resource.parameters[2] = -256;
        resource.parameters[3] = -256;
    }
    InitRumbleController(1);
}
