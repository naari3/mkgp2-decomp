/* Four display-buffer descriptors, their links, and render state.
 * The TU owns the three .bss arrays, so the loop addresses them from one pooled base.
 * Built as C++: C++ lays out the uninitialized arrays in definition order (C uses first-use order). */
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
extern "C" {
BufferEntry DisplayBuffersReset_bss_806795B8[4];
BufferLink lbl_806795E8[4];
DisplayBufferState lbl_80679608[4];
}
extern "C" const float lbl_806DA6A8;
extern "C" void *GetDisplayContext(int);
#pragma exceptions on
extern "C" void fn_801F6494(void) {
    DisplayBufferState *state;
    BufferLink *link;
    BufferEntry *entry;
    int i;
    state = lbl_80679608;
    link = lbl_806795E8;
    entry = DisplayBuffersReset_bss_806795B8;
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
