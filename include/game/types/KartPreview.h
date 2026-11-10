#ifndef GAME_TYPES_KARTPREVIEW_H
#define GAME_TYPES_KARTPREVIEW_H

struct HSD_JObj;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct KartPreview KartPreview;
struct KartPreview {
    /* 0x000 */ void *vtbl;
    /* 0x004 */ void *kart;
    /* 0x008 */ void *obj8;
    /* 0x00C */ void *driver;
    /* 0x010 */ void *obj10;
    /* 0x014 */ void *anims14[4];
    /* 0x024 */ void *obj24;
    /* 0x028 */ struct HSD_JObj *jobj28;
    /* 0x02C */ struct HSD_JObj *jobj2C;
    /* 0x030 */ struct HSD_JObj *jobj30;
    /* 0x034 */ struct HSD_JObj *jobj34;
    /* 0x038 */ struct HSD_JObj *jobj38;
    /* 0x03C */ struct HSD_JObj *jobj3C;
    /* 0x040 */ struct HSD_JObj *jobj40;
    /* 0x044 */ struct HSD_JObj *jobj44;
    /* 0x048 */ int chara;
    /* 0x04C */ int anim_state;
    /* 0x050 */ float frame;
    /* 0x054 */ float end_frame;
    /* 0x058 */ unsigned char pad_058[0x30];
    /* 0x088 */ float view_x;
    /* 0x08C */ float view_y;
};

#endif /* GAME_TYPES_KARTPREVIEW_H */
