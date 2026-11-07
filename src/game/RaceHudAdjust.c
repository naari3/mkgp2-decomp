struct HudRoot;

extern struct HudRoot *fn_80248F48(struct HudRoot *self, short flag);

/* Secondary-base destructor thunk; native C++ emits a tail branch here. */
struct HudRoot *fn_8024904C(char *self, short flag) {
    return fn_80248F48((struct HudRoot *)(self - 8), flag);
}
