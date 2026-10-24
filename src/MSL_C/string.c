#include <cstring>
#include <cstdio>


#define K1 0x80808080
#define K2 0xFEFEFEFF

size_t strlen(const char* str) {
    size_t len = -1;
    unsigned char* p = (unsigned char*)str - 1;

    do {
        len++;
    } while (*++p);

    return len;
}

char* strcpy(char* dst, const char* src) {
    register unsigned char *destb, *fromb;
    register unsigned long w, t, align;

    fromb = (unsigned char*)src;
    destb = (unsigned char*)dst;

    if ((align = ((int)fromb & 3)) != ((int)destb & 3)) {
        goto bytecopy;
    }

    if (align) {
        if ((*destb = *fromb) == 0) {
            return dst;
        }

        for (align = 3 - align; align; align--) {
            if ((*(++destb) = *(++fromb)) == 0) {
                return dst;
            }
        }
        ++destb;
        ++fromb;
    }

    w = *((int*)(fromb));

    t = w + K2;
    t &= K1;
    if (t) {
        goto bytecopy;
    }
    --((int*)(destb));

    do {
        *(++((int*)(destb))) = w;
        w = *(++((int*)(fromb)));

        t = w + K2;
        t &= K1;
        if (t) {
            goto adjust;
        }
    } while (1);

adjust:
    ++((int*)(destb));

bytecopy:
    if ((*destb = *fromb) == 0) {
        return dst;
    }

    do {
        if ((*(++destb) = *(++fromb)) == 0) {
            return dst;
        }
    } while (1);

    return dst;
}

char* strncpy(char* dst, const char* src, size_t n) {
    const unsigned char* p = (const unsigned char*)src - 1;
    unsigned char* q = (unsigned char*)dst - 1;

    n++;
    while (--n) {
        if (!(*++q = *++p)) {
            while (--n) {
                *++q = 0;
            }
            break;
        }
    }

    return dst;
}

char* strcat(char* dst, const char* src) {
    const unsigned char* p = (unsigned char*)src - 1;
    unsigned char* q = (unsigned char*)dst - 1;

    while (*++q) {
    }

    q--;

    while (*++q = *++p) {
    }

    return dst;
}

char* strncat(char* dst, const char* src, size_t n) {
    const unsigned char* p = (unsigned char*)src - 1;
    unsigned char* q = (unsigned char*)dst - 1;

    while (*++q) {}

    q--;
    n++;

    while (--n) {
        if (!(*++q = *++p)) {
            q--;
            break;
        }
    }

    *++q = 0;
    return dst;
}

int strcmp(const char* str1, const char* str2) {
    register unsigned char* left = (unsigned char*)str1;
    register unsigned char* right = (unsigned char*)str2;
    unsigned long align, l1, r1, x;

    l1 = *left;
    r1 = *right;
    if (l1 - r1) {
        return l1 - r1;
    }

    if ((align = ((int)left & 3)) != ((int)right & 3)) {
        goto bytecopy;
    }

    if (align) {
        if (l1 == 0) {
            return 0;
        }
        for (align = 3 - align; align; align--) {
            l1 = *(++left);
            r1 = *(++right);
            if (l1 - r1) {
                return l1 - r1;
            }
            if (l1 == 0) {
                return 0;
            }
        }
        left++;
        right++;
    }

    l1 = *(int*)left;
    r1 = *(int*)right;
    x = l1 + K2;
    if (x & K1) {
        goto adjust;
    }

    while (l1 == r1) {
        l1 = *(++((int*)(left)));
        r1 = *(++((int*)(right)));
        x = l1 + K2;
        if (x & K1) {
            goto adjust;
        }
    }

    if (l1 > r1) {
        return 1;
    }
    return -1;

adjust:
    l1 = *left;
    r1 = *right;
    if (l1 - r1) {
        return l1 - r1;
    }

bytecopy:
    if (l1 == 0) {
        return 0;
    }

    do {
        l1 = *(++left);
        r1 = *(++right);
        if (l1 - r1) {
            return l1 - r1;
        }
        if (l1 == 0) {
            return 0;
        }
    } while (1);
}

int strncmp(const char* str1, const char* str2, size_t n) {
    const unsigned char* p1 = (unsigned char*)str1 - 1;
    const unsigned char* p2 = (unsigned char*)str2 - 1;
    unsigned long c1, c2;

    n++;
    while (--n) {
        if ((c1 = *++p1) != (c2 = *++p2)) {
            return c1 - c2;
        } else if (c1 == 0) {
            break;
        }
    }

    return 0;
}

char* strchr(const char* str, int c) {
    const unsigned char* p = (unsigned char*)str - 1;
    unsigned long chr = (c & 0xFF);

    unsigned long ch;
    while (ch = *++p) {
        if (ch == chr) {
            return (char*)p;
        }
    }

    return chr ? NULL : (char*)p;
}


typedef unsigned char char_map[32];

#define set_char_map(map, ch) map[(unsigned char)(ch) >> 3] |= (1 << ((ch) & 7))
#define tst_char_map(map, ch) (map[(unsigned char)(ch) >> 3] & (1 << ((ch) & 7)))

char* strtok(char* str, const char* set) {
    unsigned char *p, *n;
    int c;
    static unsigned char* empty = (unsigned char*)"";
    static unsigned char* s = (unsigned char*)"";
    char_map map = {0};

    if (str) {
        s = (unsigned char*)str;
    }

    p = (unsigned char*)set - 1;
    while (c = *++p) {
        set_char_map(map, c);
    }

    p = s - 1;
    while (c = *++p) {
        if (!tst_char_map(map, c)) {
            break;
        }
    }

    if (!c) {
        s = empty;
        return NULL;
    }

    n = p;
    while (c = *++p) {
        if (tst_char_map(map, c)) {
            break;
        }
    }

    if (!c) {
        s = empty;
    } else {
        s = p + 1;
        *p = 0;
    }

    return (char*)n;
}

char* strstr(const char* str, const char* pat) {
    unsigned char* s1 = (unsigned char*)str - 1;
    unsigned char* p1 = (unsigned char*)pat - 1;
    unsigned long firstc, c1, c2;

    if ((pat == NULL) || (!(firstc = *++p1))) {
        return (char*)str;
    }

    while (c1 = *++s1) {
        if (c1 == firstc) {
            const unsigned char* s2 = s1 - 1;
            const unsigned char* p2 = p1 - 1;

            while ((c1 = *++s2) == (c2 = *++p2) && c1) {}

            if (!c2) {
                return (char*)s1;
            }
        }
    }

    return NULL;
}

char* __strerror(int errnum, char* str) {
    switch (errnum) {
    case 0: strcpy(str, "Argument list too long"); break;
    case 1: strcpy(str, "Permission denied"); break;
    case 2: strcpy(str, "Resource temporarily unavailable"); break;
    case 3: strcpy(str, "Bad file descriptor"); break;
    case 4: strcpy(str, "Device busy"); break;
    case 5: strcpy(str, "No child processes"); break;
    case 6: strcpy(str, "Resource deadlock avoided"); break;
    case 7: strcpy(str, "Numerical argument out of domain"); break;
    case 8: strcpy(str, "File exists"); break;
    case 9: strcpy(str, "Bad address"); break;
    case 10: strcpy(str, "File too large"); break;
    case 11: strcpy(str, "File Position Error"); break;
    case 12: strcpy(str, "Wide character encoding error"); break;
    case 13: strcpy(str, "Interrupted system call"); break;
    case 14: strcpy(str, "Invalid argument"); break;
    case 15: strcpy(str, "Input/output error"); break;
    case 16: strcpy(str, "Is a directory"); break;
    case 17: strcpy(str, "Too many open files"); break;
    case 18: strcpy(str, "Too many links"); break;
    case 19: strcpy(str, "File name too long"); break;
    case 20: strcpy(str, "Too many open files in system"); break;
    case 21: strcpy(str, "Operation not supported by device"); break;
    case 22: strcpy(str, "No such file or directory"); break;
    case 23: strcpy(str, "No error detected"); break;
    case 24: strcpy(str, "Exec format error"); break;
    case 25: strcpy(str, "No locks available"); break;
    case 26: strcpy(str, "Cannot allocate memory"); break;
    case 27: strcpy(str, "No space left on device"); break;
    case 28: strcpy(str, "Function not implemented"); break;
    case 29: strcpy(str, "Not a directory"); break;
    case 30: strcpy(str, "Directory not empty"); break;
    case 31: strcpy(str, "Inappropriate ioctl for device"); break;
    case 32: strcpy(str, "Device not configured"); break;
    case 33: strcpy(str, "Operation not permitted"); break;
    case 34: strcpy(str, "Broken pipe"); break;
    case 35: strcpy(str, "Result too large"); break;
    case 36: strcpy(str, "Read-only file system"); break;
    case 37: strcpy(str, "Signal error"); break;
    case 38: strcpy(str, "Illegal seek"); break;
    case 39: strcpy(str, "No such process"); break;
    case 40: strcpy(str, "Unknown error"); break;
    case 41: strcpy(str, "Cross-device link"); break;
    default: sprintf(str, "Unknown Error (%d)", errnum); break;
    }
    return str;
}

char* strerror(int errnum) {
    static char errstr[100];
    return __strerror(errnum, errstr);
}
