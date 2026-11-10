#ifndef GAME_TYPES_JOINTTRANSFORM_H
#define GAME_TYPES_JOINTTRANSFORM_H

typedef struct JointTransform {
    float rotation[4];
    float scale[3];
    float translation[3];
} JointTransform;

#endif /* GAME_TYPES_JOINTTRANSFORM_H */
