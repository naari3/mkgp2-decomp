#ifndef GAME_TYPES_SCENEOVERLAY_H
#define GAME_TYPES_SCENEOVERLAY_H

struct SceneOverlay {
    unsigned char data[0x24];
    SceneOverlay(int frames);
};

#endif /* GAME_TYPES_SCENEOVERLAY_H */
