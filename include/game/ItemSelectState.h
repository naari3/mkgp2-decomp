typedef unsigned int u32;
struct IconValue { char opaque[4]; ~IconValue() {} };
extern "C" void SpriteAnimHandle_Destroy(void *, int);
struct IconPack {
    void *handles[4]; IconValue *values[4]; char tail[0x34];
    IconPack();
    ~IconPack() {
        for(int i=0;i<4;i++) if(handles[i]) {SpriteAnimHandle_Destroy(handles[i],1);handles[i]=0;}
        for(int i=0;i<4;i++) if(values[i]) {delete values[i];values[i]=0;}
    }
};
struct TextManager { char data[0x230]; TextManager(); ~TextManager() {} };
struct ItemSelectState {
    IconPack *iconArray;
    void *groups[9];
    u32 sprites[5];
    u32 itemSprites[66];
    TextManager *auxBuffer;
    int field148,field14c,resultCode,phase;
    unsigned char doneFlag,shownFlag,pad15a[2];
    int row0,col0,selectedItemId0;
    int row1,col1,selectedItemId1;
    int row2,col2,selectedItemId2;
    ItemSelectState();
    ~ItemSelectState();
};
