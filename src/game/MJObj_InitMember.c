/* MJObj member init: run the parent class init, then default the RGBA
 * colour to opaque white. */
typedef struct MJObj {
    unsigned char pad00[0x88];
    unsigned char rgba[4]; /* 0x88 */
} MJObj;

typedef struct MJObjClassInfo {
    unsigned char pad00[0x2c];
    int (*member_init)(MJObj *self);
} MJObjClassInfo;

extern MJObjClassInfo lbl_804FC9A8;

int MJObj_InitMember_RGBA(MJObj *self)
{
    int ret = lbl_804FC9A8.member_init(self);

    if (ret != 0) {
        return ret;
    }
    self->rgba[0] = 0xff;
    self->rgba[1] = 0xff;
    self->rgba[2] = 0xff;
    self->rgba[3] = 0xff;
    return 0;
}
