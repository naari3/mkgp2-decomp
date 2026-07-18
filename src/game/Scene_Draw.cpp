struct Scene {
    virtual void Init();
    virtual void Draw();
};

#pragma exceptions on

extern "C" void Scene_Draw(Scene *scene)
{
    scene->Draw();
}
