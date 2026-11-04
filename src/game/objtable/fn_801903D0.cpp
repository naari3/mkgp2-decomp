extern "C" {
extern int g_cupId, g_longRoundFlag;
struct Data903D0 { char bytes[0xb04]; };
extern const Data903D0 lbl_803785F8;
void *FUN_8003b120(unsigned long);
}
struct Entry { void *data; Entry(const void *, int); };
struct Table903D0 { Entry **items; int count; Table903D0(); };
Table903D0::Table903D0() {
    const Data903D0 *data = &lbl_803785F8;
    items = 0;
    count = 0;
    switch (g_cupId) {
    case 2:
        if (g_longRoundFlag == 1) {
            count = 1;
            items = (Entry **)FUN_8003b120(4);
            items[0] = new Entry(&data->bytes[0], 7);
        }
        break;
    case 4:
        if (g_longRoundFlag == 1) {
            count = 6;
            items = (Entry **)FUN_8003b120(24);
            items[0] = new Entry(data->bytes + 0x1a4, 10);
            items[1] = new Entry(data->bytes + 0x3fc, 10);
            items[2] = new Entry(data->bytes + 0x654, 4);
            items[3] = new Entry(data->bytes + 0x744, 4);
            items[4] = new Entry(data->bytes + 0x834, 4);
            items[5] = new Entry(data->bytes + 0x924, 4);
        }
        break;
    case 5:
        if (g_longRoundFlag == 1) {
            count = 2;
            items = (Entry **)FUN_8003b120(8);
            items[0] = new Entry(data->bytes + 0xa14, 1);
            items[1] = new Entry(data->bytes + 0xa50, 1);
        }
        break;
    case 6:
        count = 2;
        items = (Entry **)FUN_8003b120(8);
        items[0] = new Entry(data->bytes + 0xa8c, 1);
        items[1] = new Entry(data->bytes + 0xac8, 1);
        break;
    }
}
