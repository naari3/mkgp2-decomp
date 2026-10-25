extern "C" {
void *FUN_8003b120(int size);
void Object_SetJObjScaleXYZ(void *, float, float, float);
void Object_SetJObjRotationY(void *, float);
void clNormal3D_SetScale(void *, int, float, float, float, float);
int Object_SetField8_AndDirty(void *, float);
void clNormal3D_Exec(void *);
unsigned char IsSpawnTableTerminator(void *);
unsigned char Terrain_GetGroundHeight(float *pos, float *height, int, int);
extern char lbl_8037DA7C[];
}

class Normal3D {
public:
    Normal3D(void *desc, int flags);
    unsigned char data[0x5C];
};

struct SpawnEntry {
    float pos[3];
    int extra;
};

struct BananaPosition {
    int flags;
    float pos[3];
    int pad[2];
};

struct BananaPositionData {
    Normal3D *model;
    BananaPosition *positions;
    int count;
    unsigned char ready;

    BananaPositionData(int course);
};

extern SpawnEntry *lbl_806CFCD0[2];

BananaPositionData::BananaPositionData(int course) {
    SpawnEntry *spawn;
    int i;
    float height;

    model = 0;
    positions = 0;
    count = 0;
    ready = 0;
    model = new Normal3D(lbl_8037DA7C, 1);
    Object_SetJObjScaleXYZ(model, 2.5f, 2.5f, 2.5f);
    Object_SetJObjRotationY(model, 3.141592f);
    clNormal3D_SetScale(model, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    Object_SetField8_AndDirty(model, 153.0f);
    clNormal3D_Exec(model);
    spawn = lbl_806CFCD0[course];
    count = 0;
    while (1) {
        if (IsSpawnTableTerminator(&spawn[count])) {
            break;
        }
        count++;
    }
    if (count <= 0) {
        count = 0;
        return;
    }
    positions = (BananaPosition *)FUN_8003b120(count * sizeof(BananaPosition));
    for (i = 0; i < count; i++) {
        positions[i].flags = 0;
        positions[i].pos[0] = spawn[i].pos[0];
        positions[i].pos[1] = spawn[i].pos[1];
        positions[i].pos[2] = spawn[i].pos[2];
        if (Terrain_GetGroundHeight(positions[i].pos, &height, 0, 0)) {
            positions[i].pos[1] = height;
        }
    }
}
