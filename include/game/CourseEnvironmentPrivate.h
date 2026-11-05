#ifndef GAME_COURSE_ENVIRONMENT_PRIVATE_H
#define GAME_COURSE_ENVIRONMENT_PRIVATE_H

#include "sysdolphin/baselib/jobj.h"

/* Private views of the fields consumed by 80046D84..8004893C. */
struct CourseObject {
    unsigned char mode;
    char reserved[3];
    float nearZ, farZ;
    void *model;
    HSD_JObj *joint;
    const char *filename, *jointName;
};
struct ZoneObject {
    signed char kind, variant;
    short slot;
    const char *filename, *jointName;
};
struct CourseZone {
    int kind;
    float x0, z0, x1, z1, x2, z2, x3, z3;
    ZoneObject *objects;
};
struct CourseZoneSlot {
    int references;
    const char *filename, *jointName;
    void *model;
    HSD_JObj *joint;
};
class CourseSubsystem {
public:
    virtual void Destroy(int);
    virtual void Update();
    virtual void Render(int);
};
struct CourseEnvironmentView {
    HSD_JObj *joint0, *joint4, *joint8;
    char reserved0C[0xC];
    HSD_JObj *joint18, *joint1C, *joint20, *joint24;
    HSD_JObj *joint28, *joint2C, *joint30, *joint34;
    HSD_JObj *joint38, *joint3C, *joint40, *joint44, *joint48;
    CourseObject *objects;
    void *models[8];
    void *secondaryModel;
    float view[3][4];
    float projection[3];
    void *collision;
    void *archiveRegistration;
    void *archive;
    CourseZone *zones;
    CourseZoneSlot slots[32];
    void *renderers[8];
    void *secondaryRenderer;
    void *animationManager;
    void *effects;
    CourseSubsystem *subsystem;
    void *objectManager;
    void *zoneManager;
    unsigned char field378;
};

/* Each external constructor is bridged to its existing unmangled symbol. */
struct CEModel { char data[0x5C]; CEModel(const char *, int); };
struct CEArchive { char data[0x18]; CEArchive(const char *); };
struct CEZoneManager { char data[0x180]; CEZoneManager(); };
struct CECollision { char pad[8]; void *collisionData; CECollision(const char *); };
struct CEAnimation { char data[0x10]; CEAnimation(void *); };
struct CEEffects { char data[8]; CEEffects(void *); };
struct CEObjectManager { char data[4]; CEObjectManager(void *); };
struct CERenderer { char data[0x48]; CERenderer(void *, int); };

#endif
