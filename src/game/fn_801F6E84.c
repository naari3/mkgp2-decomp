typedef struct Sprite {
    char pad00[0x3C];
    float scaleX;
    float scaleY;
    unsigned int color[4];
    int hasPos;
    int x;
    int y;
} Sprite;


void fn_801F6E84(Sprite *s, int x, int y) {
    s->hasPos = 1;
    s->x = x;
    s->y = y;
}

void fn_801F6E98(Sprite *s, unsigned int color) {
    s->color[0] = color;
    s->color[1] = color;
    s->color[2] = color;
    s->color[3] = color;
}

void fn_801F6EAC(Sprite *s, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    unsigned int color = (r << 24) | (g << 16) | (b << 8) | a;
    s->color[0] = color;
    s->color[1] = color;
    s->color[2] = color;
    s->color[3] = color;
}

void fn_801F6ED0(Sprite *s, float sx, float sy) {
    double ax = __fabs(sx);
    double ay = __fabs(sy);
    s->scaleX = ax;
    s->scaleY = ay;
}
