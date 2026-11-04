/* Four display-buffer descriptors, their links, and render state.
 * NonMatching: initialization address materialization differs. */
typedef struct DisplayBufferState {
    unsigned short width, height;
    int mode;
    void *context;
    int a,b,c,d;
    float scale;
    unsigned char flags[4];
} DisplayBufferState;
typedef struct BufferLink { DisplayBufferState *buffer; int value; } BufferLink;
typedef struct BufferEntry { int a,b; BufferLink *link; } BufferEntry;
typedef struct BufferPool { BufferEntry entries[4]; BufferLink links[4]; DisplayBufferState states[4]; } BufferPool;
extern BufferPool lbl_806795B8;
extern const float lbl_806DA6A8;
extern void *GetDisplayContext(int);
#pragma exceptions on
void fn_801F6494(void) {
    DisplayBufferState *state = lbl_806795B8.states;
    BufferLink *link = lbl_806795B8.links;
    BufferEntry *entry = lbl_806795B8.entries;
    int i;
    for(i=0;i<=3;i++) {
        state->width = 128;
        state->height = 128;
        state->mode = 4;
        state->context = GetDisplayContext(i);
        state->a = 0;
        state->b = 0;
        state->c = 0;
        state->d = 0;
        state->scale = lbl_806DA6A8;
        state->flags[0] = 0;
        state->flags[1] = 0;
        entry->a = 0;
        state->flags[2] = 0;
        link->buffer = state;
        entry->b = 1;
        state->flags[3] = 0;
        entry->link = link;
        link->value = 0;
        state++; entry++; link++;
    }
}
#pragma exceptions reset
