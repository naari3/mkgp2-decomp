#ifndef GAME_PRELOAD_ITEM_RESOURCES_PRIVATE_H
#define GAME_PRELOAD_ITEM_RESOURCES_PRIVATE_H

extern int ItemAlias_DestToSource(unsigned int item, void *alias);
extern void FileLoader_Open(const char *path);
extern void PreloadEffectResources(int set);
extern void PreloadResource(int resource);
extern const char *g_itemDescriptorTable[];
extern const char *lbl_8041BC00[];

#endif
