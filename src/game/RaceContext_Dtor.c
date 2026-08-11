/* === extracted from auto_RaceContext_Dtor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void MemoryManager_TimedFree(void *);

/* --- extern decls: sda21-referenced data --- */
#pragma cplusplus on
struct PolymorphicOwner {
    virtual ~PolymorphicOwner();
};
struct RaceContextView {
    void *vtable;
};
extern PolymorphicOwner *lbl_806D10A0;
#pragma cplusplus off

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8040E4D0[];
extern unsigned int lbl_8040E4DC[];

/* --- function index (1 fns, .text 0x8009D638..0x8009D6CC) ---
 * [  0] 0x8009D638 size:0x94    global RaceContext_Dtor
 */

/* --- forward decls --- */
#pragma cplusplus on
extern "C" void *RaceContext_Dtor(RaceContextView *, short);
#pragma cplusplus off

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_RaceContext_Dtor[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RaceContext_Dtor = {
    (void *)&RaceContext_Dtor, 0x00000094, (void *)extab_RaceContext_Dtor
};

/* --- asm function bodies (.text order = fn address order) --- */
#pragma cplusplus on
#pragma exceptions off
extern "C" void *RaceContext_Dtor(RaceContextView *self, short freeFlag) { /* 0x8009D638 size:0x94 */
    if (self != 0) {
        self->vtable = (void *)lbl_8040E4D0;
        delete lbl_806D10A0;
        lbl_806D10A0 = 0;
        if (self != 0) {
            self->vtable = (void *)lbl_8040E4DC;
        }
        if (freeFlag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset
#pragma cplusplus off

