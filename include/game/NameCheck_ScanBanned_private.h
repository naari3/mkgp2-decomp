#ifndef NAMECHECK_SCAN_BANNED_PRIVATE_H
#define NAMECHECK_SCAN_BANNED_PRIVATE_H

typedef unsigned short NameCode;
typedef unsigned char NameBool;
typedef struct NameCharacterSets {
    const NameCode *first;
    int first_count;
    const NameCode *second;
    int second_count;
} NameCharacterSets;
typedef struct NameDelimiterPair {
    const char *open;
    const char *close;
} NameDelimiterPair;

#endif
