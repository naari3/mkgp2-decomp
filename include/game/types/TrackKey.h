#ifndef GAME_TYPES_TRACKKEY_H
#define GAME_TYPES_TRACKKEY_H

/* One key of a joint animation track: the tracks are static data, ended by
 * a key with frame -1 (docs/notes/port_abi.md, "Word tables read as bytes"). */
typedef struct TrackKey {
    short frame;
    short reserved;
    float value;
} TrackKey;

#endif
