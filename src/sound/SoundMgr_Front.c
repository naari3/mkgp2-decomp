#include "game/types/reg_args.h"
/*
 * 0x8016C0A4..0x8016C3FC: sound manager front-end wrappers. Each one is a
 * no-op while the weather/sound system is not created, and the SE starters
 * are suppressed while its +0x2C flag is set.
 */

typedef struct WeatherSystem {
    char pad[0x2C];
    unsigned char suppress;
} WeatherSystem;

extern WeatherSystem *g_weatherSystem;
extern int fn_801915F4(int, int);
extern int fn_801916FC(int, int);
extern int fn_80191804(int, int);
extern int fn_8019190C(int, int);
extern int fn_80191A14(int MORE_REG_ARGS1(float));
extern int fn_80191B5C(int, int, int);
extern int fn_80191CF4(int, int);
extern int fn_80191DF8(int MORE_REG_ARGS3(float, float, float));
extern int fn_80191F1C(int);
extern int fn_80192010(int);
extern int fn_80192348(int);
extern int fn_80192688(int MORE_REG_ARGS1(int));
extern int fn_80192F04(int MORE_REG_ARGS4(const void *, unsigned char *, unsigned char *, unsigned char *));

#pragma exceptions on

/* The callers of these four pass the full argument list of the function
 * behind them; the extra arguments stay in their registers on the way through. */
int fn_8016C0A4(int a0 MORE_REG_ARGS4(const void *position, unsigned char *volume, unsigned char *pan, unsigned char *surround)) {
    if (g_weatherSystem == 0) {
        return 0;
    }
    return fn_80192F04(a0 MORE_REG_ARGS4(position, volume, pan, surround));
}

int fn_8016C0D8(int a0, int a1) {
    if (g_weatherSystem == 0) {
        return 0;
    }
    if (g_weatherSystem->suppress) {
        return 1;
    }
    return fn_801915F4(a0, a1);
}

int fn_8016C120(int a0, int a1) {
    if (g_weatherSystem == 0) {
        return 0;
    }
    if (g_weatherSystem->suppress) {
        return 1;
    }
    return fn_801916FC(a0, a1);
}

int fn_8016C168(int a0, int a1) {
    if (g_weatherSystem == 0) {
        return 0;
    }
    if (g_weatherSystem->suppress) {
        return 1;
    }
    return fn_80191804(a0, a1);
}

int fn_8016C1B0(int a0, int a1) {
    if (g_weatherSystem == 0) {
        return 0;
    }
    if (g_weatherSystem->suppress) {
        return 1;
    }
    return fn_8019190C(a0, a1);
}

int fn_8016C1F8(int a0 MORE_REG_ARGS1(float f)) {
    if (g_weatherSystem == 0) {
        return 0;
    }
    if (g_weatherSystem->suppress) {
        return 1;
    }
    return fn_80191A14(a0 MORE_REG_ARGS1(f));
}

int fn_8016C240(int a0, int a1, int a2) {
    if (g_weatherSystem == 0) {
        return 0;
    }
    if (g_weatherSystem->suppress) {
        return 1;
    }
    return fn_80191B5C(a0, a1, a2);
}

int fn_8016C288(int a0, int a1) {
    if (g_weatherSystem == 0) {
        return 0;
    }
    if (g_weatherSystem->suppress) {
        return 1;
    }
    return fn_80191CF4(a0, a1);
}

int fn_8016C2D0(int a0 MORE_REG_ARGS3(float x, float y, float z)) {
    if (g_weatherSystem == 0) {
        return 0;
    }
    if (g_weatherSystem->suppress) {
        return 1;
    }
    return fn_80191DF8(a0 MORE_REG_ARGS3(x, y, z));
}

int fn_8016C318(int a0) {
    if (g_weatherSystem == 0) {
        return 0;
    }
    if (g_weatherSystem->suppress) {
        return 0;
    }
    return fn_80191F1C(a0);
}

int fn_8016C360(int a0) {
    if (g_weatherSystem == 0) {
        return 0;
    }
    return fn_80192010(a0);
}

int fn_8016C394(int a0) {
    if (g_weatherSystem == 0) {
        return 0;
    }
    return fn_80192348(a0);
}

int fn_8016C3C8(int a0 MORE_REG_ARGS1(int v)) {
    if (g_weatherSystem == 0) {
        return 0;
    }
    return fn_80192688(a0 MORE_REG_ARGS1(v));
}

#pragma exceptions reset
