#ifndef GAME_CLFLOWCOURSE_UPDATE_PRIVATE_H
#define GAME_CLFLOWCOURSE_UPDATE_PRIVATE_H

/* Course-selection fields in the received PCB slot. */
struct CourseRecvSlot {
    unsigned char flags;
    unsigned char reserved[4];
    unsigned char courseFlags;

    bool HasRole(int role) const { return ((flags >> 4) & 7) == role; }
    int Selection() const { return (courseFlags >> 1) & 0x7F; }
};

#endif
