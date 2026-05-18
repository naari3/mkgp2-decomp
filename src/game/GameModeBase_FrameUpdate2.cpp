struct Scene {
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

struct GameModeBase {
    void *vtable;
    Scene *scene;
};

#pragma exceptions on
extern "C" void GameModeBase_FrameUpdate2(GameModeBase *self) {
    if (self->scene != 0) {
        self->scene->f2();
    }
}
#pragma exceptions reset
