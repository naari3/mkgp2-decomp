#ifndef GAME_TYPES_HUDPANEL_H
#define GAME_TYPES_HUDPANEL_H

/* Include before this header (each user already does): "game/types/VObj14.h", "game/types/VObjC.h" */

typedef struct HudPanel {
    char pad0[0x14];
    void *vt14;
    char pad18[0x60];
    VObjC *f78;
    void *f7C;
    VObj14 *f80;
} HudPanel;

#endif /* GAME_TYPES_HUDPANEL_H */
