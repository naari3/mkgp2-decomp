#if 0
/* Retry c11_a33: captured SetPos arguments improve native text to 95.86775%.
 * Still disabled: foreign switch table, resource-base caching and EH PCs differ.
 * Activation requires C++ constructor bridges; see HANDOFF evidence. */
#pragma cplusplus on
#pragma exceptions on
#pragma use_lmw_stmw on
void *operator new(unsigned long);
void operator delete(void*);
typedef float CharaMatrix[3][4];
class CharaNormal {
    unsigned char storage[92];
public:
    CharaNormal(const char*, int);
};
class CharaModel {
public:
    unsigned char beforeMatrix[0x58];
    CharaMatrix* matrix;
    unsigned char tail[8];
    CharaModel(int, int, unsigned char, unsigned char);
};
class CharaSprite {
public:
    unsigned char beforePosition[12];
    float x, y;
    unsigned char remaining[28];
    void SetPos(float px, float py) { x = px; y = py; }
    CharaSprite(int, unsigned char, int);
};
struct CharaInput { unsigned char pad[0x14]; int delta; };
struct CharaJoint {
    unsigned char pad[0x14]; unsigned int flags;
    unsigned char pad18[0x2C]; CharaMatrix matrix;
};
struct CharaOwner { virtual void Destroy(short); };
struct CharaFrame {
    short a, b; unsigned int unknown; int ticks; float dx, x, y;
};
struct CharaView {
    unsigned int unknown;
    int selection, state;
    unsigned char pending, padD[3];
    int frame;
    CharaSprite* sprites[13];
    CharaSprite* leftArrow;
    CharaSprite* rightArrow;
    CharaSprite* stats[3];
    CharaSprite* header;
    int result;
    unsigned char complete, display, pad66[2];
    int unknown68;
    float brightness;
    CharaOwner* owner;
    void* lightList;
    CharaMatrix matrix;
    int variants[13];
    CharaNormal* normals[13];
    CharaNormal* alternateNormals[13];
    CharaModel* models[13];
    unsigned char pad178[0x5C];
    CharaJoint* joint;
};
extern "C" {
extern CharaInput* g_pInputState;
extern CharaFrame FrameParam_ARRAY_8049aad0[];
extern float g_tierCursorPosTable[][2];
extern const unsigned char clFlowChara_rodata_8039AA40[];
extern signed char lbl_806D184C, lbl_806D184D;
extern const float FLOAT_ARROW_RIGHT_OFFSET, FLOAT_ARROW_SCALE;
extern const float FLOAT_BRIGHTNESS_DARK, FLOAT_FULL_ALPHA, FLOAT_SPRITE_INIT_TIME;
extern const float lbl_806D9B7C, lbl_806D9B80, lbl_806D9BA8;
extern const float lbl_806D9BB0, lbl_806D9BB4, lbl_806D9BBC, lbl_806D9BC0;
extern const char lbl_806D9BC4[7], lbl_806D9BCC[5];
void RumbleUpdate();
void* FileLoader_Open(const char*);
int GetFrameIdxFromVisualIdx(CharaView*, int);
const char** GetKartModelNameEntry(int, int);
void CharaSelect_SetupCharacterDisplay(CharaView*, int);
void fn_801C37E8(CharaView*, int, int, int, float);
int fn_801B85DC(int, unsigned char, short);
int fn_801B8918(int);
void PSMTXScale(CharaMatrix*, float, float, float);
void PSMTXRotRad(CharaMatrix*, int, float);
void PSMTXTrans(CharaMatrix*, float, float, float);
void PSMTXIdentity(CharaMatrix*);
void PSMTXConcat(CharaMatrix*, CharaMatrix*, CharaMatrix*);
int Sprite_AdvanceAnim(CharaSprite*, float);
int fn_8019FF6C(CharaSprite*, unsigned char);
int SetScreenBrightness(float);
void fn_801699D8(unsigned int, unsigned char);
int fn_801B84B4(int);
void fn_801B7CAC();
int clFlowChara_HandleConfirm(CharaView*);
int clNormal3D_SetScale(CharaNormal*, CharaNormal*, float, float, float, float);
CharaSprite* Sprite_Destroy(CharaSprite*, short);
int fn_801A024C(CharaSprite*);
int fn_801B87D8();
int fn_801B8540(int);
int fn_801B8398(int);
void* LObjList_Destroy(void*, short);
int clNormal3D_Exec(CharaNormal*);
float Object_GetField8(CharaNormal*);
int Object_DriveAnimMatrix(CharaNormal*);
int Object_SetAnimBinding(CharaNormal*, CharaMatrix*, CharaJoint*);
void fn_8021A660(CharaModel*, float, float, float);
void fn_8021A71C(CharaModel*, float, float, float);
void fn_8021A9E8(CharaModel*);
void __assert(const char*, int, const char*);
void HSD_JObjSetupMatrixSub(CharaJoint*);
}
static inline CharaInput* CurrentCharaInput()
{
    return SINGLETON_INSTANCE(g_pInputState);
}
static inline int ApplyCharaInput(CharaView* self, CharaInput* input)
{
    int previous = self->selection;
    self->selection += input->delta;
    return previous;
}
static inline CharaMatrix* CharaJointMatrix(CharaJoint* joint)
{
    if (!joint) __assert(lbl_806D9BC4, 0x47C, lbl_806D9BCC);
    if (joint) {
        if (!joint) __assert(lbl_806D9BC4, 0x25D, lbl_806D9BCC);
        unsigned char update = 0;
        if (!(joint->flags & 0x00800000) && (joint->flags & 0x40)) update = 1;
        if (update) HSD_JObjSetupMatrixSub(joint);
    }
    return &joint->matrix;
}
extern "C" int clFlowChara_Update(CharaView* self)
{
    struct SoundIds { short ids[13]; };
    SoundIds soundCopy = *(const SoundIds*)(clFlowChara_rodata_8039AA40 + 0x74C);
    short (&soundIds)[13] = soundCopy.ids;
    CharaMatrix scale, rotation, translation;
    RumbleUpdate();
    if (self->pending) { ++self->state; self->pending = 0; }
    ++self->frame;
    switch (self->state) {
    case 0: {
        if (self->frame >= 2 && self->frame <= 14)
            FileLoader_Open(((const char* const*)(clFlowChara_rodata_8039AA40 + 0x70C))[self->frame - 2]);
        if (self->frame >= 15 && self->frame <= 27) {
            int visual = self->frame - 15;
            if (self->variants[GetFrameIdxFromVisualIdx(self, visual)] >= 1)
                FileLoader_Open(*GetKartModelNameEntry(GetFrameIdxFromVisualIdx(self, visual), 2));
            else FileLoader_Open(((const char* const*)(clFlowChara_rodata_8039AA40 + 0x5D4))[visual]);
        }
        if (self->frame == 28) {
            for (int i = 0; i < 13; ++i) {
                self->normals[i] = new CharaNormal(((const char* const*)(clFlowChara_rodata_8039AA40 + 0x70C))[i], 0);
                Object_SetAnimBinding(self->normals[i], &self->matrix, 0);
            }
        }
        if (self->frame == 29) {
            for (int i = 0; i < 13; ++i) {
                if (self->variants[GetFrameIdxFromVisualIdx(self, i)] >= 1) {
                    self->models[i] = new CharaModel(GetFrameIdxFromVisualIdx(self, i), 2, 0, 0);
                    fn_8021A660(self->models[i], lbl_806D9BB0, lbl_806D9BB0, lbl_806D9BB0);
                    fn_8021A71C(self->models[i], lbl_806D9B7C, FLOAT_BRIGHTNESS_DARK, lbl_806D9BB4);
                } else {
                    self->alternateNormals[i] = new CharaNormal(((const char* const*)(clFlowChara_rodata_8039AA40 + 0x5D4))[i], 0);
                }
            }
        }
        if (self->frame == 1) {
            fn_801C37E8(self, 6, 0x169, 16, FLOAT_ARROW_SCALE);
            fn_801C37E8(self, 7, 0x169, 16, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 3) {
            fn_801C37E8(self, 5, 0x169, 16, FLOAT_ARROW_SCALE);
            fn_801C37E8(self, 8, 0x169, 16, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 5) {
            fn_801C37E8(self, 4, 0x169, 16, FLOAT_ARROW_SCALE);
            fn_801C37E8(self, 9, 0x169, 16, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 7) {
            fn_801C37E8(self, 3, 0x169, 16, FLOAT_ARROW_SCALE);
            fn_801C37E8(self, 10, 0x169, 16, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 9) {
            fn_801C37E8(self, 2, 0x169, 16, FLOAT_ARROW_SCALE);
            fn_801C37E8(self, 11, 0x169, 16, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 11) {
            fn_801C37E8(self, 1, 0x169, 16, FLOAT_ARROW_SCALE);
            fn_801C37E8(self, 12, 0x169, 16, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 13) {
            fn_801C37E8(self, 0, 0x169, 16, FLOAT_ARROW_SCALE);
            fn_801B85DC(13, 0, soundIds[self->selection]);
        }
        if (self->frame == 22) {
            self->header = new CharaSprite(0x16A, 1, 0);
            self->header->x = lbl_806D9BA8;
            self->header->y = lbl_806D9BBC;
            lbl_806D184C = 1; lbl_806D184D = 0;
        }
        unsigned char done = 1;
        for (int i = 0; i < 13; ++i) {
            if (self->sprites[i]) {
                self->sprites[i]->SetPos(FrameParam_ARRAY_8049aad0[i].dx * (float)FrameParam_ARRAY_8049aad0[i].ticks + FrameParam_ARRAY_8049aad0[i].x, FrameParam_ARRAY_8049aad0[i].y);
                if (FrameParam_ARRAY_8049aad0[i].ticks) { --FrameParam_ARRAY_8049aad0[i].ticks; done = 0; }
            }
        }
        if (done && self->frame >= 30) {
            for (int i = 0; i < 13; ++i) fn_801C37E8(self, i, 0x20, -1, FLOAT_ARROW_SCALE);
            fn_801B8918(0x1AE1);
            PSMTXScale(&scale, lbl_806D9B80, lbl_806D9B80, lbl_806D9B80);
            PSMTXRotRad(&rotation, 'y', FLOAT_SPRITE_INIT_TIME);
            const float* pos = (const float*)(clFlowChara_rodata_8039AA40 + 0x740);
            PSMTXTrans(&translation, pos[0], pos[1], pos[2]);
            PSMTXIdentity(&self->matrix);
            PSMTXConcat(&scale, &self->matrix, &self->matrix);
            PSMTXConcat(&rotation, &self->matrix, &self->matrix);
            PSMTXConcat(&translation, &self->matrix, &self->matrix);
            CharaSelect_SetupCharacterDisplay(self, GetFrameIdxFromVisualIdx(self, self->selection));
            self->display = 1; self->pending = 1;
        }
        break;
    }
    case 1:
        for (int i = 0; i < 13; ++i)
            if (self->sprites[i] && (unsigned char)Sprite_AdvanceAnim(self->sprites[i], lbl_806D9BC0))
                fn_801C37E8(self, i, 0x169, 0, FLOAT_ARROW_SCALE);
        if (self->frame > 30) {
            for (int i = 0; i < 13; ++i) {
                if (i == self->selection) fn_801C37E8(self, i, 0x1E, 0, FLOAT_FULL_ALPHA);
                else fn_801C37E8(self, i, 0x168, 0, FLOAT_ARROW_SCALE);
                fn_8019FF6C(self->sprites[i], 1);
            }
            SetScreenBrightness(self->brightness); self->pending = 1;
            fn_801699D8(0, 1);
        }
        break;
    case 2:
        if (CurrentCharaInput()) {
            int previous = ApplyCharaInput(self, CurrentCharaInput());
            if (self->selection > 12) self->selection = 0;
            if (self->selection < 0) self->selection = 12;
            if (previous != self->selection) {
                fn_801C37E8(self, previous, 0x168, -1, FLOAT_ARROW_SCALE);
                fn_801C37E8(self, self->selection, 0x1E, -1, FLOAT_FULL_ALPHA);
                CharaSelect_SetupCharacterDisplay(self, GetFrameIdxFromVisualIdx(self, self->selection));
                fn_801B84B4(soundIds[self->selection]); fn_801B7CAC();
            if (self->leftArrow) {
                self->leftArrow->SetPos(g_tierCursorPosTable[self->selection][0], g_tierCursorPosTable[self->selection][1]);
            }
            if (self->rightArrow) {
                self->rightArrow->SetPos(FLOAT_ARROW_RIGHT_OFFSET + g_tierCursorPosTable[self->selection][0], g_tierCursorPosTable[self->selection][1]);
            }
            }
        }
        if (clFlowChara_HandleConfirm(self) != -1) {
            fn_801C37E8(self, self->selection, 0x1F, -1, FLOAT_FULL_ALPHA);
            const float* range = (const float*)(clFlowChara_rodata_8039AA40 + 0x4A4);
            clNormal3D_SetScale(self->normals[self->selection], 0, range[2], FLOAT_FULL_ALPHA, range[2], range[3]);
            lbl_806D184C = -1;
            Sprite_Destroy(self->leftArrow, 1); Sprite_Destroy(self->rightArrow, 1);
            self->leftArrow = 0; self->rightArrow = 0; self->pending = 1;
        }
        break;
    case 3:
        if (self->complete) self->pending = 1;
        break;
    case 4:
        if ((unsigned char)fn_801A024C(self->sprites[self->selection]) == 0) {
            fn_801C37E8(self, self->selection, 0x1D, -1, FLOAT_FULL_ALPHA);
            fn_801B87D8(); self->frame = 0; self->pending = 1;
        }
        for (int i = 0; i < 13; ++i) if (i != self->selection) FrameParam_ARRAY_8049aad0[i].ticks = 0;
        break;
    case 5:
        if (self->frame == 14) {
            if (self->result == 15) fn_801B8540(soundIds[self->selection]);
            else fn_801B8398(soundIds[self->selection]);
            if (self->owner) self->owner->Destroy(1);
            LObjList_Destroy(self->lightList, 1);
            self->owner = 0; self->lightList = 0; self->display = 0;
            Sprite_Destroy(self->header, 1); self->header = 0;
            Sprite_Destroy(self->stats[0], 1); Sprite_Destroy(self->stats[1], 1); Sprite_Destroy(self->stats[2], 1);
            self->stats[0] = 0; self->stats[1] = 0; self->stats[2] = 0;
            fn_801699D8(0, 0);
        }
        if (self->frame == 14) {
            if (self->selection != 6) fn_801C37E8(self, 6, 0x169, 1, FLOAT_ARROW_SCALE);
            if (self->selection != 7) fn_801C37E8(self, 7, 0x169, 1, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 18) {
            if (self->selection != 5) fn_801C37E8(self, 5, 0x169, 1, FLOAT_ARROW_SCALE);
            if (self->selection != 8) fn_801C37E8(self, 8, 0x169, 1, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 22) {
            if (self->selection != 4) fn_801C37E8(self, 4, 0x169, 1, FLOAT_ARROW_SCALE);
            if (self->selection != 9) fn_801C37E8(self, 9, 0x169, 1, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 24) {
            if (self->selection != 3) fn_801C37E8(self, 3, 0x169, 1, FLOAT_ARROW_SCALE);
            if (self->selection != 10) fn_801C37E8(self, 10, 0x169, 1, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 28) {
            if (self->selection != 2) fn_801C37E8(self, 2, 0x169, 1, FLOAT_ARROW_SCALE);
            if (self->selection != 11) fn_801C37E8(self, 11, 0x169, 1, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 32) {
            if (self->selection != 1) fn_801C37E8(self, 1, 0x169, 1, FLOAT_ARROW_SCALE);
            if (self->selection != 12) fn_801C37E8(self, 12, 0x169, 1, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 36 && self->selection != 0) fn_801C37E8(self, 0, 0x169, 1, FLOAT_ARROW_SCALE);
        for (int i = 0; i < 13; ++i) {
            if (self->sprites[i]) {
                self->sprites[i]->SetPos(FrameParam_ARRAY_8049aad0[i].x - FrameParam_ARRAY_8049aad0[i].dx * (float)FrameParam_ARRAY_8049aad0[i].ticks, FrameParam_ARRAY_8049aad0[i].y);
                if (FrameParam_ARRAY_8049aad0[i].ticks != 0 && FrameParam_ARRAY_8049aad0[i].ticks != -16) ++FrameParam_ARRAY_8049aad0[i].ticks;
            }
        }
        if (self->frame == 60) self->pending = 1;
        break;
    case 6: return self->result;
    }
    for (int i = 0; i < 13; ++i)
        if (self->sprites[i]) Sprite_AdvanceAnim(self->sprites[i], lbl_806D9BC0);
    if (self->header) Sprite_AdvanceAnim(self->header, lbl_806D9BC0);
    if (!self->display) return -1;
    if (self->display) {
        if (self->leftArrow) Sprite_AdvanceAnim(self->leftArrow, lbl_806D9BC0);
        if (self->rightArrow) Sprite_AdvanceAnim(self->rightArrow, lbl_806D9BC0);
        if (self->stats[0]) Sprite_AdvanceAnim(self->stats[0], lbl_806D9BC0);
        if (self->stats[1]) Sprite_AdvanceAnim(self->stats[1], lbl_806D9BC0);
        if (self->stats[2]) Sprite_AdvanceAnim(self->stats[2], lbl_806D9BC0);
    }
    if (self->normals[self->selection]) {
        clNormal3D_Exec(self->normals[self->selection]);
        if (self->state >= 3 && Object_GetField8(self->normals[self->selection]) >= ((const float*)(clFlowChara_rodata_8039AA40 + 0x4A4))[3]) {
            self->complete = 1;
            float end = ((const float*)(clFlowChara_rodata_8039AA40 + 0x4A4))[3] - FLOAT_FULL_ALPHA;
            clNormal3D_SetScale(self->normals[self->selection], 0, end, FLOAT_FULL_ALPHA, end, end);
        }
        Object_DriveAnimMatrix(self->normals[self->selection]);
    }
    if (self->alternateNormals[self->selection] && self->joint) {
        CharaMatrix* matrix = CharaJointMatrix(self->joint);
        Object_SetAnimBinding(self->alternateNormals[self->selection], matrix, 0);
        clNormal3D_Exec(self->alternateNormals[self->selection]);
        Object_DriveAnimMatrix(self->alternateNormals[self->selection]);
    } else if (self->models[self->selection] && self->joint) {
        CharaMatrix* matrix = CharaJointMatrix(self->joint);
        self->models[self->selection]->matrix = matrix;
        fn_8021A9E8(self->models[self->selection]);
    }
    return -1;
}
#endif
