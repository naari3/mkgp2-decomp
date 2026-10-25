typedef struct WeatherSystem {
    unsigned char pad[0x2c];
    unsigned char muted;
} WeatherSystem;

typedef struct WeatherCtl {
    int pad0;
    void *active;
    int mode;
    int sub;
    unsigned char flag10;
    unsigned char pad11[7];
    unsigned char flag18;
    unsigned char pad19[7];
    int level;
} WeatherCtl;

extern WeatherSystem *g_weatherSystem;
extern void SoundMgr_Play(int id);
extern void fn_80192348(int id);

void fn_8016BF20(WeatherCtl *c, unsigned int cmd, int arg) {
    if (c->active == 0) return;
    switch (cmd) {
    case 0:
        c->mode = 2;
        c->sub = 0;
        break;
    case 1:
        c->mode = 1;
        c->sub = 0;
        break;
    case 2:
        c->mode = 3;
        c->sub = 0;
        break;
    case 3:
        c->mode = 4;
        c->sub = 0;
        break;
    case 4:
        if (arg != 0) {
            c->mode = 6;
            c->sub = 0;
        } else {
            c->mode = 5;
            c->sub = 0;
        }
        break;
    case 5:
        if (arg != 0) {
            if (g_weatherSystem != 0 && g_weatherSystem->muted == 0) SoundMgr_Play(0x47);
        } else {
            if (g_weatherSystem != 0) fn_80192348(0x47);
        }
        break;
    case 6:
        if (arg != 0) c->flag10 = 1;
        else c->flag10 = 0;
        break;
    case 7:
        if (arg != 0) c->flag18 = 1;
        else c->flag18 = 0;
        break;
    case 8:
        if (arg != 0) {
            c->level++;
        } else {
            c->level--;
            if (c->level < 0) c->level = 0;
        }
        break;
    }
}
