#ifndef GAME_TYPES_MOBJCLASSVIEW_H
#define GAME_TYPES_MOBJCLASSVIEW_H

#include "game/types/MObjView.h"

typedef struct MObjClassView {
    unsigned char base[0x40];
    int (*load) (MObjView *, void *);
    void *(*setupTev) (MObjView *, void *, void **);
    unsigned char tail[0xC];
} MObjClassView;

#endif /* GAME_TYPES_MOBJCLASSVIEW_H */
