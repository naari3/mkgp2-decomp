#ifndef GAME_ITEMALIASSPRITE_H
#define GAME_ITEMALIASSPRITE_H
#include "game/SpritePairOwner.h"
struct ItemAliasSprite {
    int style, layer;
    float x,y,scaleX,scaleY;
    unsigned int color;
    unsigned char active;
    char pad1D[3];
    int item, resource;
    signed char alias;
    char pad29[3];
    int handles[2];
    ItemAliasSprite(int style, int layer);
    ~ItemAliasSprite();
    void Draw();
};
struct ItemSpriteResource { int resource; int tail[3]; };
extern "C" {
void SpriteLayer_SetResource(int,int);
void fn_8011F744(int,float,float);
void fn_8011F610(int,int,int,int);
int ItemAlias_DestToSource(unsigned int,void *);
extern unsigned int g_itemIdToIndexTable[0x148];
extern ItemSpriteResource lbl_803DC530[];
extern int lbl_803E57E8[];
extern const float lbl_806DBD8C, lbl_806DBD90, lbl_806DBD94, lbl_806DBD98, lbl_806DBD9C, lbl_806DBDA0;
}
#endif
