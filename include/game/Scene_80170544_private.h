#ifndef SCENE_80170544_PRIVATE_H
#define SCENE_80170544_PRIVATE_H

struct SparkJoint {
    char pad00[8];
    SparkJoint *next;
    char pad0C[4];
    SparkJoint *child;
};
struct clNormal3D {
    char opaque[0x5C];
    clNormal3D(void *, int);
};
struct CourseMarkerBase {
    virtual void key();
    virtual ~CourseMarkerBase();
    CourseMarkerBase() {}
};
struct CourseSpark {
    unsigned char active;
    unsigned char pad[3];
    int timer;
    int index;
};
struct SparkModels : CourseMarkerBase {
    SparkJoint *root;
    int count;
    clNormal3D *modelA;
    clNormal3D *modelB;
    void *joints[4];
    CourseSpark sparks[5];
    int cooldown;
    int randomIndex;
    SparkModels(SparkJoint *);
    virtual void keyDerived();
};
#endif
