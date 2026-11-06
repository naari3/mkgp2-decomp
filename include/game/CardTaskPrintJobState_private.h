#ifndef GAME_CARDTASKPRINTJOBSTATE_PRIVATE_H
#define GAME_CARDTASKPRINTJOBSTATE_PRIVATE_H

/* C representation of the three-word CardStep member-function pointer. */
typedef struct CardTaskPrintJobCallback {
    int this_adjustment;
    int vtable_offset;
    void *function;
} CardTaskPrintJobCallback;

typedef struct CardTaskPrintJobState {
    CardTaskPrintJobCallback step;
    int result;
    unsigned int status;
} CardTaskPrintJobState;

#endif
