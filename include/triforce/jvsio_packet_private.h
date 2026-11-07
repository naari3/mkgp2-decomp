#ifndef TRIFORCE_JVSIO_PACKET_PRIVATE_H
#define TRIFORCE_JVSIO_PACKET_PRIVATE_H

#include <dolphin/types.h>

/* An SI response packet contains a command, payload length, and payload. */
typedef struct JvsPacket {
    u8 command;
    u8 length;
    u8 payload[0x7E];
} JvsPacket;

#endif
