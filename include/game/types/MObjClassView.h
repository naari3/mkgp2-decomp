#ifndef GAME_TYPES_MOBJCLASSVIEW_H
#define GAME_TYPES_MOBJCLASSVIEW_H

/* Merged from 4 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct MObjClassView MObjClassView;
struct MObjClassView {
    /* 0x000 */ unsigned char base[0x40];
    /* 0x040 */ int (*load) (MObjView *, void *);  /* also: initMember */
    /* 0x044 */ void *(*setupTev) (MObjView *, void *, void **);
    /* 0x048 */ unsigned char tail[0x10];
};

#endif /* GAME_TYPES_MOBJCLASSVIEW_H */
