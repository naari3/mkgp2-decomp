/*
 * 0x8016C444..0x8016C730: weather / ambience channel toggles forwarded to
 * fn_8016BF20, and the weather system destructor.
 */

typedef struct StreamPair {
    int a;
    int b;
} StreamPair;

typedef struct WeatherSystem {
    unsigned char kart;
    unsigned char variant;
    char pad02[2];
    StreamPair *streams;
} WeatherSystem;

extern WeatherSystem *g_weatherSystem;
extern void fn_8016BF20(WeatherSystem *, int, int);
extern void fn_80192348(int);
extern unsigned char fn_8019083C(int);
extern void fn_801909A4(int);
extern void fn_80192514(int, int);
extern void MemoryManager_TimedFree(void *);

#pragma exceptions on

void fn_8016C444(unsigned char on) {
    if (g_weatherSystem) {
        fn_8016BF20(g_weatherSystem, 8, on != 0);
    }
}

void fn_8016C488(unsigned char on) {
    if (g_weatherSystem) {
        fn_8016BF20(g_weatherSystem, 7, on != 0);
    }
}

void fn_8016C4CC(unsigned char on) {
    if (g_weatherSystem) {
        fn_8016BF20(g_weatherSystem, 6, on != 0);
    }
}

void fn_8016C510(unsigned char on) {
    if (g_weatherSystem) {
        fn_8016BF20(g_weatherSystem, 5, on != 0);
    }
}

void fn_8016C554(unsigned char on) {
    if (g_weatherSystem) {
        fn_8016BF20(g_weatherSystem, 4, on != 0);
    }
}

void fn_8016C598(void) {
    if (g_weatherSystem) {
        fn_8016BF20(g_weatherSystem, 3, 0);
    }
}

void fn_8016C5CC(void) {
    if (g_weatherSystem) {
        fn_8016BF20(g_weatherSystem, 2, 0);
    }
}

void fn_8016C600(void) {
    if (g_weatherSystem) {
        fn_8016BF20(g_weatherSystem, 0, 0);
    }
}

WeatherSystem *fn_8016C634(WeatherSystem *self, short flag) {
    if (self) {
        fn_80192348(0x40000050);
        fn_80192348(0x40000051);
        if (self->streams) {
            if (fn_8019083C(self->streams->a)) {
                fn_801909A4(self->streams->a);
            }
            if (fn_8019083C(self->streams->b)) {
                fn_801909A4(self->streams->b);
            }
        }
        self->streams = 0;
        fn_80192514(2, 5);
        fn_80192514(3, 5);
        fn_80192514(4, 5);
        fn_80192514(5, 5);
        fn_80192514(6, 5);
        fn_80192514(7, 5);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

#pragma exceptions reset
