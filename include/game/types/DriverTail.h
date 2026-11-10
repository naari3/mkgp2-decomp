#ifndef GAME_TYPES_DRIVERTAIL_H
#define GAME_TYPES_DRIVERTAIL_H

/* Declare before including (each user already does): Driver */

struct DriverTail {
    Driver *owner; int a04, a08, a0C, a10;
    unsigned char a14,a15,pad16[2]; int a18;
    DriverTail(Driver *p) { owner=p; a04=0; a0C=0; a10=0; a14=0; a15=0; a18=-1; }
};

#endif /* GAME_TYPES_DRIVERTAIL_H */
