#ifndef SCENE_80166BE8_PRIVATE_H
#define SCENE_80166BE8_PRIVATE_H
struct TitlePreview { virtual ~TitlePreview(); virtual void Update(); };
struct TitlePreviewScene {
    void *vtable;
    char pad04[0xc];
    void *text;
    int cursor;
    int repeat;
    int character;
    int title;
    int variant;
    TitlePreview *preview;
};
#endif
