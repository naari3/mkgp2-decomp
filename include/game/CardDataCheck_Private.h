#ifndef GAME_CARDDATACHECK_PRIVATE_H
#define GAME_CARDDATACHECK_PRIVATE_H
#include "game/TestMenuPage.h"

/* The editable card settings occupy page +0x60 and backup +0x64. */
struct CardCheckSettings { unsigned int words[10]; };
struct CardCheckRecords { unsigned int words[119]; };
struct CardCheckData {
    unsigned char enabled;
    unsigned char reserved[3];
    CardCheckSettings settings;
    CardCheckRecords records;
    int count;
    unsigned char flag;
};
struct CardCheckStep {
    unsigned char (*fn)(void);
    unsigned char checkError;
};
static inline CardCheckData *CardCheck_PageData(TestPage *self)
{
    return (CardCheckData *)((char *)self + 0x60);
}
static inline CardCheckData *CardCheck_BackupData(TestPage *self)
{
    return (CardCheckData *)((char *)self->data + 0x64);
}
#endif
