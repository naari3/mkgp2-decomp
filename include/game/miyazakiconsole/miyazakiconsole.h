#ifndef MIYAZAKICONSOLE_H
#define MIYAZAKICONSOLE_H

extern "C" {
unsigned long strlen(const char *);
void MemoryManager_TimedFree(void *p);
}

typedef void (*MenuCallback)(int msg, void *user, int cursor, int arg3, int arg4);

struct MenuItem {
    char name[0x24];
    MenuItem *next;
    MenuItem() {
        name[0] = 0;
        next = 0;
    }
    ~MenuItem() {}
};

struct Menu {
    int x0;
    int x4;
    int x8;
    char title[0x24];
    MenuItem *head;
    MenuItem *tail;
    unsigned int count;
    unsigned int cursor;
    MenuCallback callback;
    void *user;

    Menu(const char *name) {
        unsigned long i = 0;
        if (name != 0) {
            unsigned long len = strlen(name);
            for (i = 0; i < len && i < 0x20; i++) {
                title[i] = name[i];
            }
        }
        title[i] = 0;
        head = 0;
        tail = 0;
        count = 0;
        cursor = 0;
        x8 = 0;
        callback = 0;
        user = 0;
        x0 = 0;
        x4 = 0;
    }
    ~Menu();
    void Clear() {
        if (head != 0) {
            MenuItem *p = head;
            while (p != 0) {
                MenuItem *next = p->next;
                delete p;
                p = next;
            }
        }
        head = 0;
        tail = 0;
        count = 0;
        cursor = 0;
    }
};

#ifndef MENU_DTOR_OUTLINE
inline
#endif
Menu::~Menu() {
    if (callback != 0) {
        callback(2, user, cursor, 1, 0);
    }
    Clear();
}

#endif
