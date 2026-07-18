/*
 * LapBannerScene @ 0x800882B8..0x80088700 (.text)
 *
 * Final-lap banner scene object:
 *   +0x0  void *obj        (scene object; owns the banner archive/JObj tree)
 *   +0x4  void *driver     (KartDriver the banner follows)
 *   +0x8  u8    active
 *   +0xC  float timer      (frames since trigger)
 *
 * Functions:
 *   0x800882B8 LapBannerScene_TriggerBannerAnim (0x4C)
 *   0x80088304 LapBannerScene_RenderIfActive    (0x54)
 *   0x80088358 LapBannerScene_UpdateAndDriveAnim(0x348)
 *   0x800886A0 LapBannerScene_Dtor              (0x60)
 *
 * The JObj setter idiom (assert line numbers 0x3B8/0x3C6/0x3D4/0x2B8/0x2B9/
 * 0x25D) matches the already-matched src/game/Object_SetJObjRotation.c.
 */

typedef struct HSD_JObj {
    unsigned char pad[0x14];
    unsigned int flags;
    unsigned int pad_18;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    unsigned char pad_28[4];
    float scale_x;
    float scale_y;
    float scale_z;
    float position_x;
    float position_y;
    float field_40;
} HSD_JObj;

typedef struct LapBannerScene {
    void *obj;            /* 0x0 */
    void *driver;         /* 0x4 */
    unsigned char active; /* 0x8 */
    float timer;          /* 0xC */
} LapBannerScene;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern const float lbl_806D3250; /* 0.0f */
extern const float lbl_806D3254; /* timer step */
extern const float lbl_806D3258; /* timer limit / scale arg */
extern char lbl_806D325C[7]; /* assert file string */
extern char lbl_806D3264[5]; /* assert expr string ("jobj") */
extern const float lbl_806D326C;   /* Y offset */
extern const float lbl_806D3270;   /* yaw offset */
extern char lbl_803127B8[0x58]; /* quaternion assert message */

extern void __assert(char *, int, char *);
extern void fn_802D20AC(HSD_JObj *);
extern void clNormal3D_SetScale(void *, int, float, float, float, float);
extern void Jyugemu_ReverseFlag_SetEnable(unsigned char);
extern void Object_RenderJObjTree(void *, int);
extern void *KartDriver_GetKartRootMtx(void *);
extern void *Archive_GetRootJObj(void *);
extern void *GetCourseScene3D(void);
extern void CObj_LoadProjMatrix(void *, Vec3 *);
extern void CObj_ApplyScissor(void *, Vec3 *);
extern void Vec3_Subtract(Vec3 *, Vec3 *, Vec3 *);
extern void Vec3_Normalize(Vec3 *, Vec3 *);
extern double Atan2(float, float);
extern void clNormal3D_Exec(void *);
extern void Object_DriveAnimMatrix(void *);
extern void Object_DtorWithGXSync(void *, int);
extern void MemoryManager_TimedFree(void *);

static void update_matrix(HSD_JObj *jobj) {
    unsigned int flags;
    unsigned char skip;

    flags = jobj->flags;
    skip = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) {
        skip = 1;
    }
    if (!skip) {
        fn_802D20AC(jobj);
    }
}

static void advance_timer(LapBannerScene *self) {
    self->timer += lbl_806D3254;
    if (self->timer >= lbl_806D3258) {
        self->active = 0;
        Jyugemu_ReverseFlag_SetEnable(1);
    }
}

static void set_mtx_dirty(HSD_JObj *jobj) {
    if (!(jobj->flags & 0x02000000) && jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D325C, 0x25D, lbl_806D3264);
        }
        update_matrix(jobj);
    }
}

static void set_position_x(void *obj, float v) {
    HSD_JObj *jobj = Archive_GetRootJObj(obj);

    if (jobj == 0) {
        __assert(lbl_806D325C, 0x3B8, lbl_806D3264);
    }
    jobj->position_x = v;
    set_mtx_dirty(jobj);
}

static void set_position_y(void *obj, float v) {
    HSD_JObj *jobj = Archive_GetRootJObj(obj);

    if (jobj == 0) {
        __assert(lbl_806D325C, 0x3C6, lbl_806D3264);
    }
    jobj->position_y = v;
    set_mtx_dirty(jobj);
}

static void set_position_z(void *obj, float v) {
    HSD_JObj *jobj = Archive_GetRootJObj(obj);

    if (jobj == 0) {
        __assert(lbl_806D325C, 0x3D4, lbl_806D3264);
    }
    jobj->field_40 = v;
    set_mtx_dirty(jobj);
}

static void set_rotation_y(void *obj, float v) {
    HSD_JObj *jobj = Archive_GetRootJObj(obj);

    if (jobj == 0) {
        __assert(lbl_806D325C, 0x2B8, lbl_806D3264);
    }
    if (jobj->flags & 0x00020000) {
        __assert(lbl_806D325C, 0x2B9, lbl_803127B8);
    }
    jobj->rotation_y = v;
    set_mtx_dirty(jobj);
}

#pragma exceptions on
void LapBannerScene_TriggerBannerAnim(LapBannerScene *self) {
    float zero = lbl_806D3250;
    float step = lbl_806D3254;
    float limit = lbl_806D3258;

    self->active = 1;
    self->timer = zero;
    clNormal3D_SetScale(self->obj, 0, zero, step, zero, limit);
    Jyugemu_ReverseFlag_SetEnable(0);
}

int LapBannerScene_RenderIfActive(LapBannerScene *self) {
    void *obj = self->obj;

    if (obj == 0) {
        return 0;
    }
    if (self->active == 0) {
        return 0;
    }
    Object_RenderJObjTree(obj, 7);
    return 1;
}

int LapBannerScene_UpdateAndDriveAnim(LapBannerScene *self) {
    float *mtx;
    void *cobj;
    Vec3 at;
    Vec3 eye;
    Vec3 dir;

    if (self->obj == 0) {
        return 0;
    }
    if (self->driver == 0) {
        return 0;
    }
    if (self->active == 0) {
        return 0;
    }

    advance_timer(self);

    mtx = KartDriver_GetKartRootMtx(self->driver);

    set_position_x(self->obj, mtx[3]);
    set_position_y(self->obj, lbl_806D326C + mtx[7]);
    set_position_z(self->obj, mtx[11]);

    cobj = GetCourseScene3D();
    if (cobj != 0) {
        CObj_LoadProjMatrix(cobj, &eye);
        CObj_ApplyScissor(cobj, &at);
        Vec3_Subtract(&at, &eye, &dir);
        dir.y = lbl_806D3250;
        Vec3_Normalize(&dir, &dir);
        set_rotation_y(self->obj, lbl_806D3270 + (float)Atan2(dir.x, dir.z));
    }

    clNormal3D_Exec(self->obj);
    Object_DriveAnimMatrix(self->obj);
    return 1;
}

void *LapBannerScene_Dtor(LapBannerScene *self, short flag) {
    if (self != 0) {
        Object_DtorWithGXSync(self->obj, 1);
        self->obj = 0;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset
