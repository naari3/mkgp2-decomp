/* Five-code-unit card-name filter. Tables remain owned by the original data TU. */
#include "game/NameCheck_ScanBanned_private.h"

extern NameCode *wcscpy(NameCode *, const NameCode *);
extern int strcmp(const void *, const void *);
extern int strncmp(const void *, const void *, unsigned int);
extern void *strstr(const void *, const void *);
extern void *strcpy(void *, const void *);
extern void *strcat(void *, const void *);
extern void *memset(void *, int, unsigned int);
extern void DebugPrintf(const char *, ...);
extern const char lbl_80318270[];
extern const NameDelimiterPair lbl_8040E450[12];
extern const char *lbl_8040E4B0[5];
extern const NameCode lbl_806D4740[4];
extern const char lbl_806D4750[4], lbl_806D4754[4], lbl_806D4758[8];
extern const char lbl_806D4760[8], lbl_806D4768[8], lbl_806D4770[8];
extern const char lbl_806D4778[8], lbl_806D4780[8], lbl_806D4788[8];

static inline NameBool contains(unsigned int c, const NameCode *set, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        if (c == *set) return 1;
        set++;
    }
    return 0;
}

static inline NameBool contains_at(const NameCode *p, const NameCode *set, int count)
{
    NameBool found = 0;
    int i;
    for (i = 0; i < count; i++) {
        if (*p == *set) { found = 1; break; }
        set++;
    }
    return found;
}

static inline NameBool at_boundary(const NameCode *p, const NameCode *set, int count)
{
    NameBool found = 0;
    int i;
    if (p) {
        for (i = 0; i < count; i++) {
            if (*p == *set) { found = 1; break; }
            set++;
        }
    }
    return found;
}

#pragma inline_max_size(10000)
static inline int extract_one(const NameCode *buf, NameCode *out, int position,
                             const NameCode *set, int count)
{
    int cursor;
    int length = 0;
    for (cursor = position; cursor < 5; cursor++) {
        if (contains(buf[cursor], set, count) == 1) out[length++] = buf[cursor];
        else if (length > 0) break;
    }
    return cursor;
}
static inline int extract_two(const NameCode *buf, NameCode *out, int position,
                             const NameCode *a, int na, const NameCode *b, int nb)
{
    int cursor;
    int length = 0;
    for (cursor = position; cursor < 5; cursor++) {
        if (contains(buf[cursor], a, na) == 1) out[length++] = buf[cursor];
        else if (contains(buf[cursor], b, nb) == 1) out[length++] = buf[cursor];
        else if (length > 0) break;
    }
    return cursor;
}

/* A scan may consume several characters while it walks the table. */
#define COLLECT_RUN(SET, COUNT) \
    for (k = position; k < 5; k++) { \
        found = 0; \
        for (j = 0; j < (COUNT); j++) { \
            if (buf[position] == (SET)[j]) { \
                parts[part][length++] = buf[position++]; \
                found = 1; \
            } \
        } \
        if (!found) { parts[part][length] = 0; break; } \
    }

#define SPLIT_PARTS(WITH_SYMBOLS) \
    for (part = 0; part < 5; part++) memset(parts[part], 0, 10); \
    position = 0; \
    for (part = 0; part < 5; part++) { \
        length = 0; \
        COLLECT_RUN(upper, 26); \
        if (length > 0) continue; \
        COLLECT_RUN(lower, 26); \
        if (length > 0) continue; \
        COLLECT_RUN(katakana, 81); \
        if (length > 0) continue; \
        COLLECT_RUN(hiragana, 81); \
        if (length > 0) continue; \
        COLLECT_RUN(digits, 10); \
        if (length > 0) continue; \
        if (WITH_SYMBOLS) { COLLECT_RUN(symbols, 25); } \
    }

#define CHECK_WORD(WORD) \
    for (word = 0; word < 1067; word++) { \
        if (strcmp(banned[word], (WORD)) == 0) return 1; \
    }

#define PRINT_PARTS() \
    DebugPrintf(lbl_806D4768, parts[0]); \
    DebugPrintf(lbl_806D4770, parts[1]); \
    DebugPrintf(lbl_806D4778, parts[2]); \
    DebugPrintf(lbl_806D4780, parts[3]); \
    DebugPrintf(lbl_806D4788, parts[4])

#pragma use_lmw_stmw on
#pragma exceptions on
NameBool NameCheck_ScanBannedWords(NameCode *name)
{
    NameCode buf[6];
    NameCode first[6], second[6];
    NameCode parts[5][5];
    NameCode single[2];
    const char *base = lbl_80318270 + 0x10000;
    const char *const *banned = (const char *const *)(lbl_80318270 + 0x72e8);
#define upper ((const NameCode *)(base - 0x7c20))
#define lower ((const NameCode *)(base - 0x7c54))
#define katakana ((const NameCode *)(base - 0x7b48))
#define hiragana ((const NameCode *)(base - 0x7bec))
#define digits ((const NameCode *)(base - 0x7a70))
#define symbols ((const NameCode *)(base - 0x7aa4))
    const NameCharacterSets *sets;
    const NameCode *boundary_set;
    NameCode *open, *close, *p, *next;
    NameBool found, invalid;
    int word, i, j, k, part, position, length, count, boundary_count;
    unsigned int group;
    wcscpy(buf, name);
    buf[5] = 0;
    CHECK_WORD(buf);
    sets = (const NameCharacterSets *)(base - 0x7a5c);
    for (group = 0; group < 10; group++, sets++) {
        for (i = 0; i < 6; i++) { second[i] = 0; first[i] = 0; }
        if (!sets->second) {
            position = extract_one(buf, first, 0, sets->first, sets->first_count);
            extract_one(buf, second, position, sets->first, sets->first_count);
        } else {
            position = extract_two(buf, first, 0, sets->first, sets->first_count,
                                   sets->second, sets->second_count);
            extract_two(buf, first, position, sets->first, sets->first_count,
                        sets->second, sets->second_count);
        }
        DebugPrintf(base - 0x7984, group, first);
        DebugPrintf(base - 0x796c, group, second);
        for (word = 0; word < 1067; word++) {
            if (strcmp(banned[word], first) == 0) return 1;
            if (strcmp(banned[word], second) == 0) return 1;
        }
    }
    for (group = 0; group < 12; group++) {
        boundary_set = katakana;
        boundary_count = 81;
        if ((int)group >= 11) { boundary_set = lower; boundary_count = 26; }
        else if ((int)group >= 10) { boundary_set = upper; boundary_count = 26; }
        else if ((int)group >= 5) { boundary_set = hiragana; boundary_count = 81; }
        open = (NameCode *)strstr(buf, lbl_8040E450[group].open);
        if (open) {
            next = open;
            while (next) {
                next = (NameCode *)strstr(open + 1, lbl_8040E450[group].open);
                if (next) open = next;
            }
            DebugPrintf(base - 0x7954);
            if (open != buf && contains_at(open - 1, boundary_set, boundary_count) == 1) break;
            DebugPrintf(base - 0x7948);
            close = (NameCode *)strstr(open, lbl_8040E450[group].close);
            if (close) {
                /* The original guard tests byte-address + 1, then reads a code unit. */
                if ((char *)close + 1 && contains_at(close + 1, boundary_set, boundary_count) == 1) break;
                DebugPrintf(base - 0x793c, group, open, close);
                invalid = 0;
                for (p = open + 1; *p != *close; p++) {
                    single[0] = *p; single[1] = 0;
                    DebugPrintf(lbl_806D4750, single);
                    found = 0;
                    for (j = 0; j < 25; j++) {
                        if (*p == symbols[j]) { found = 1; break; }
                    }
                    if (!found) { invalid = 1; break; }
                }
                if (invalid == 1) break;
                for (p = open + 1; *p != *close; p++) {
                    for (i = 0; (unsigned int)i < 5; i++) {
                        if (strncmp(p, lbl_8040E4B0[i], 2) == 0) return 1;
                    }
                }
                break;
            }
        }
    }
    open = (NameCode *)strstr(buf, lbl_806D4754);
    if (open) {
        NameBool prefix_found;
        count = 0; prefix_found = 0;
        for (p = buf; *p != *open; p++) {
            for (j = 0; j < 3; j++) {
                if (*p == lbl_806D4740[j]) { count++; break; }
            }
            prefix_found = 0;
            for (j = 0; j < 25; j++) {
                if (*p == symbols[j]) { prefix_found = 1; break; }
            }
            if (!prefix_found) count = 0;
        }
        if (count >= 2) {
            for (j = 0; j < 26; j++) {
                if (*open == upper[j]) { prefix_found = 1; break; }
                if (prefix_found == 1) break;
            }
            boundary_set = upper; boundary_count = 26;
            if (prefix_found == 1) { boundary_set = lower; boundary_count = 26; }
            if (!at_boundary(open + 1, boundary_set, boundary_count)) return 1;
        }
    }
    open = (NameCode *)strstr(buf, lbl_806D4758);
    DebugPrintf(lbl_806D4760, open);
    if (open) {
        NameBool prefix_found;
        count = 0; prefix_found = 0;
        for (p = buf; *p != *open; p++) {
            for (j = 0; j < 3; j++) {
                if (*p == lbl_806D4740[j]) { count++; break; }
            }
            prefix_found = 0;
            for (j = 0; j < 25; j++) {
                if (*p == symbols[j]) { prefix_found = 1; break; }
            }
            if (!prefix_found) count = 0;
        }
        DebugPrintf(base - 0x7920, count);
        if (count >= 1) {
            for (j = 0; j < 26; j++) {
                if (*open == upper[j]) { prefix_found = 1; break; }
                if (prefix_found == 1) break;
            }
            boundary_set = upper; boundary_count = 26;
            if (prefix_found == 1) { boundary_set = lower; boundary_count = 26; }
            if (!at_boundary(open + 2, boundary_set, boundary_count)) return 1;
        }
    }
    SPLIT_PARTS(1);
    PRINT_PARTS();
    for (i = 0; i < 5; i++) {
        memset(first, 0, 12);
        strcpy(first, parts[i]);
        DebugPrintf(lbl_806D4750, first);
        CHECK_WORD(first);
        for (k = i + 1; k < 5; k++) {
            strcat(first, parts[k]);
            DebugPrintf(lbl_806D4750, first);
            CHECK_WORD(first);
        }
    }
    found = 0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 81; j++) {
            if (buf[i] == katakana[j]) { found = 1; break; }
        }
        if (found) break;
    }
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 81; j++) {
            if (buf[i] == hiragana[j]) { found = 1; break; }
        }
        if (found) break;
    }
    if (!found) {
        count = 0;
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 26; j++) if (buf[i] == upper[j]) { count++; break; }
        }
        if (count >= 2) found = 1;
    }
    if (!found) {
        count = 0;
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 26; j++) if (buf[i] == lower[j]) { count++; break; }
        }
        if (count >= 2) found = 1;
    }
    if (!found) {
        count = 0;
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 10; j++) if (buf[i] == digits[j]) { count++; break; }
        }
        if (count >= 2) found = 1;
    }
    if (found) {
        for (i = 0; i < 5;) {
            for (j = 0; j < 25; j++) {
                if (buf[i] == symbols[j]) {
                    for (j = i; j < 5; j++) buf[j] = buf[j + 1];
                    break;
                }
            }
            if ((unsigned int)j >= 25) i++;
        }
        CHECK_WORD(buf);
    }
    SPLIT_PARTS(0);
    PRINT_PARTS();
    for (i = 0; i < 5; i++) {
        memset(first, 0, 12);
        strcpy(first, parts[i]);
        DebugPrintf(lbl_806D4750, first);
        CHECK_WORD(first);
        for (k = i + 1; k < 5; k++) {
            strcat(first, parts[k]);
            DebugPrintf(lbl_806D4750, first);
            CHECK_WORD(first);
        }
    }
    return 0;
}
#pragma exceptions reset
#pragma use_lmw_stmw reset
