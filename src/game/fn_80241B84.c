typedef struct JointTaskView {
    const unsigned char *vtable;
} JointTaskView;

extern const unsigned char lbl_804EE6AC[], lbl_804EE6C0[];
extern void MemoryManager_TimedFree(void *);

void *fn_80241B84(JointTaskView *self, short destroy) {
    if (self) {
        self->vtable = lbl_804EE6AC;
        if (self) self->vtable = lbl_804EE6C0;
        if (destroy > 0) MemoryManager_TimedFree(self);
    }
    return self;
}
