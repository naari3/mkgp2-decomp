/* Target ASM audited directly; Ghidra unavailable. TU-local object views. */
struct CIInput; struct CICamera; struct CICar; struct CIScene;
struct CIHud; struct CIWeather;
struct CIRender {
    unsigned char pad[0x238]; int visible;
    unsigned char middle[0x94]; unsigned char active;
};
extern "C" {
extern const float lbl_806DAE30, lbl_806DAE44, lbl_806DAE2C, lbl_806DAE48;
extern const char lbl_803C3E38[];
extern int lbl_804EDA60[7][2];
extern int g_characterId, g_roundIndex, g_ccClass, lbl_806D12BC, lbl_806CF128;
extern unsigned char g_lakituStartAnimDone, g_raceEnded;
extern float g_raceTimeRemaining;
extern CICamera* g_raceCamera;
extern CIWeather* g_weatherSystem;
void* DrawManager_GetOrCreate(); void SetResourceLoadingFlag(unsigned char);
void DMAChannelManager_Init(); void* TransitionEffect_GetOrCreate();
void SoundChannels_ClearAll(); void ItemObjectManager_Init();
void CourseObjectManager_Init(); void SetReverseRoundFlag(unsigned char);
void* GetCourseDataPtr(); void* RenderTarget_Create(void*);
void* SetActiveCamera(int, CICamera*); void ProcessSystemTick(int);
void* GetRaceContextPtr(); void RankingTable_Init(void*);
void* SoundDriver_GetOrCreate(void*);
int GetStartPosition(int,float*,float*,float*); float GetCourseStartYaw();
int GetDisplayBufferIndex();
void CarObject_Init(CICar*,int,int,int,int,unsigned char,int,int,unsigned char,float,float,float);
CIRender* CarObject_GetRenderObj(CICar*); void SetPlayerCarObject(CICar*);
const char** GetKartModelNameEntry(int,int); void Scene3D_Init(CIScene*,const char*);
void Scene3D_GetCameraPos(CIScene*,float*,float*);
int Scene3D_SetupProjection(CIScene*,float,float);
void HUD_RegisterOverlay(CIHud*,int,int); void SetCourseScene3D(CIScene*);
int MiniGame_GetTimerValue(); void PreloadEffectResources(int);
const float* MiniGame_GetCourseData(); int* NokoNokoChallenge_GetCoinDivisor();
void SpriteLayer_SetResource(void*,int); void CoinSystem_Init(int,int);
void CourseObjects_Activate();
}
struct CIRoot { CIRoot(); virtual ~CIRoot(); virtual void identity(); };
struct CIBase : CIRoot {
    float phase;
    CIBase() { phase=lbl_806DAE30; }
    virtual ~CIBase(); virtual void identity();
};
struct CIInput { unsigned char opaque[0x37C]; CIInput(); };
struct CICamera { unsigned char opaque[0x2C]; CICamera(int,int,float,float,void*); };
struct CICar {
    unsigned char pad[0xFD]; unsigned char fd,fe; unsigned char tail[0x19];
    CIRender* render();
    CICar(const float* x,const float* z) {
        int character=g_characterId;
        float yaw=GetCourseStartYaw();
        int display=GetDisplayBufferIndex();
        CarObject_Init(this,display,character,0,0,1,6,0,0,*x,*z,yaw);
    }
};
struct CILakitu { unsigned char opaque[0x58]; CILakitu(const char*,int,float,float,float); };
struct CIScene {
    unsigned char opaque[0x3084];
    CIScene() { Scene3D_Init(this,*GetKartModelNameEntry(g_characterId,-1)); }
};
struct CIGoal { unsigned char opaque[8]; CIGoal(); };
struct CIHud { unsigned char opaque[0x80]; CIHud(int); };
struct CIScore {
    unsigned char pad[0x10]; void* first; void* second;
    unsigned char tail[0x14]; CIScore(int);
};
struct CIWeather { unsigned char opaque[0x1B4]; CIWeather(unsigned char); };
struct CIOwner : CIBase {
    CICar* car; CILakitu* lakitu; CIInput* input; CIScene* scene; CIGoal* goal;
    CICamera* camera; void* renderTarget; int unused24; CIHud* hud; CIScore* score;
    unsigned char b30,b31,pad32[2]; int w34,w38,goalCount,w40,divisor;
    CIOwner(); virtual void identity();
};
CIOwner::CIOwner() {
    DrawManager_GetOrCreate(); SetResourceLoadingFlag(0); DMAChannelManager_Init();
    TransitionEffect_GetOrCreate(); SoundChannels_ClearAll(); ItemObjectManager_Init();
    CourseObjectManager_Init(); SetReverseRoundFlag(0);
    input=new CIInput;
    renderTarget=RenderTarget_Create(GetCourseDataPtr());
    camera=new CICamera(256,256,lbl_806DAE44,lbl_806DAE2C,renderTarget);
    SetActiveCamera(0,camera); g_raceCamera=camera; ProcessSystemTick(0);
    RankingTable_Init(GetRaceContextPtr()); lbl_806D12BC=0; SoundDriver_GetOrCreate(0);
    float x,z; GetStartPosition(0,&x,0,&z);
    car=new CICar(&x,&z); car->fd=0; car->fe=0;
    car->render()->visible=1;
    car->render()->active=1;
    SetPlayerCarObject(car);
    lakitu=new CILakitu(lbl_803C3E38,0,lbl_806DAE30,lbl_806DAE30,lbl_806DAE30);
    scene=new CIScene; goal=new CIGoal; ProcessSystemTick(0);
    float projectionX,projectionZ;
    Scene3D_GetCameraPos(scene,&projectionX,&projectionZ);
    projectionX+=lbl_806DAE48; Scene3D_SetupProjection(scene,projectionX,projectionZ);
    hud=new CIHud(0);
    HUD_RegisterOverlay(hud,6,0); HUD_RegisterOverlay(hud,17,0);
    HUD_RegisterOverlay(hud,18,0); HUD_RegisterOverlay(hud,14,0);
    g_lakituStartAnimDone=0; SetCourseScene3D(scene); g_raceEnded=0;
    lbl_806CF128=1; b30=0; b31=0; w34=0; w38=0;
    g_raceTimeRemaining=(float)MiniGame_GetTimerValue();
    PreloadEffectResources(9); PreloadEffectResources(10);
    goalCount=(int)*MiniGame_GetCourseData(); score=new CIScore(goalCount);
    CIScore* display=score;
    SpriteLayer_SetResource(display->second,0x14BA);
    SpriteLayer_SetResource(display->first,0x1ECD);
    w40=0; divisor=*NokoNokoChallenge_GetCoinDivisor();
    int highRound=(g_roundIndex>=4) ? 1 : 0;
    CoinSystem_Init(lbl_804EDA60[g_ccClass][highRound],1);
    CourseObjects_Activate();
    if(!g_weatherSystem) g_weatherSystem=new CIWeather(1);
    SetResourceLoadingFlag(1);
}
