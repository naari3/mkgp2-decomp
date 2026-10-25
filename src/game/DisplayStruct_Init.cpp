/* DisplayStruct_Init @ 0x80045B50..0x80045E20: constructor of the 0x380
 * byte kart display block that KartDriver_New_Full.c forwards to. Field
 * names are offsets until the layout is known. */
void *operator new(unsigned long size);
void operator delete(void *ptr);

extern "C" {
extern const float lbl_806D2540; /* 0.0f */
extern const float lbl_806D2570; /* 1.0f */
extern const float lbl_806D25CC; /* 60.0f */
}

class ISESlot {
public:
    ISESlot();
    unsigned char data[0x24];
};

struct DisplayStruct {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    int words[49]; /* 0x24 */
    int fE8;
    int fEC;
    int fF0;
    int fF4;
    int fF8;
    int fFC;
    int f100;
    int f104;
    unsigned char pad_108[0x4];
    int f10C;
    unsigned char pad_110[0x4];
    int f114;
    int f118;
    int f11C;
    int f120;
    int f124;
    int f128;
    int f12C;
    unsigned char pad_130[0x20];
    int f150;
    int f154;
    int f158;
    int f15C;
    int f160;
    int f164;
    int f168;
    int f16C;
    float f170;
    unsigned char pad_174[0x44];
    int f1B8;
    unsigned char pad_1BC[0x4];
    float f1C0;
    float f1C4;
    float f1C8;
    float f1CC;
    float f1D0;
    float f1D4;
    float f1D8;
    float f1DC;
    float f1E0;
    float f1E4;
    int f1E8;
    int f1EC;
    int f1F0;
    unsigned char pad_1F4[0x10];
    char f204;
    char f205;
    unsigned char pad_206[0x12];
    int f218;
    unsigned char pad_21C[0x14];
    char f230;
    unsigned char pad_231[0x7];
    int f238;
    int f23C;
    int f240;
    char f244;
    unsigned char pad_245[0x3];
    int f248;
    unsigned char pad_24C[0x50];
    int f29C;
    unsigned char pad_2A0[0x4];
    int f2A4;
    char f2A8;
    signed char f2A9;
    unsigned char pad_2AA[0x2];
    int f2AC;
    char f2B0;
    char f2B1;
    char f2B2;
    char f2B3;
    int f2B4;
    char f2B8;
    unsigned char pad_2B9[0x7];
    int f2C0;
    signed char f2C4;
    char f2C5;
    unsigned char pad_2C6[0x2];
    int f2C8;
    int f2CC;
    char f2D0;
    unsigned char pad_2D1[0x3];
    float f2D4;
    int f2D8;
    ISESlot *slots[10]; /* 0x2DC */
    int f304;
    int f308;
    unsigned char pad_30C[0x20];
    int f32C;
    unsigned char pad_330[0x8];
    float f338;
    float f33C;
    float f340;
    int f344;
    char f348;
    unsigned char pad_349[0x1];
    short f34A;
    unsigned char pad_34C[0xC];
    int f358;
    int f35C;
    int f360;
    int f364;
    char f368;
    unsigned char pad_369[0x3];
    float f36C;
    int f370;
    unsigned char pad_374[0x8];
    float f37C;

    void Init();
};

void DisplayStruct::Init()
{
    int i;
    int j;

    f0 = 0;
    f4 = 0;
    f8 = 0;
    fC = 0;
    f10 = 0;
    f14 = 0;
    f29C = 0;
    fE8 = 0;
    fEC = 0;
    fF0 = 0;
    fF4 = 0;
    fF8 = 0;
    fFC = 0;
    f100 = 0;
    f104 = 0;
    f10C = 0;
    f114 = 0;
    f118 = 0;
    f11C = 0;
    f120 = 0;
    f124 = 0;
    f128 = 0;
    f12C = 0;
    f158 = 0;
    f15C = 0;
    f160 = 0;
    f154 = 0;
    f164 = 0;
    f170 = lbl_806D2540;
    f168 = 0;
    f16C = 0;
    f1B8 = 0;
    f20 = 0;
    f150 = 0;
    f1C0 = lbl_806D2540;
    f1C4 = lbl_806D2540;
    f1C8 = lbl_806D2540;
    f1CC = lbl_806D2540;
    f37C = lbl_806D2570;
    f1D0 = lbl_806D2540;
    f1D4 = lbl_806D2540;
    f1D8 = lbl_806D2540;
    f1DC = lbl_806D2540;
    f1E0 = lbl_806D2540;
    f1E4 = lbl_806D25CC;
    f1F0 = 0;
    f204 = 1;
    f2A4 = 0;
    f2A8 = 0;
    f2A9 = -1;
    f1EC = f1F0;
    f218 = -1;
    f230 = 1;
    f2B0 = 0;
    f2B3 = 0;
    f2B1 = 0;
    f2B2 = 0;
    f2B4 = 0;
    f2B8 = 0;
    f2C8 = -1;
    f2C0 = -1;
    f205 = 0;
    f2C4 = -1;
    f2C5 = 0;
    f2AC = -1;
    f240 = 0x3E7;
    f244 = 0;
    f23C = 0;
    f248 = 0;
    f238 = 0;
    f2CC = 0;
    f2D0 = 0;
    f2D4 = lbl_806D2570;
    f2D8 = 5;
    f338 = lbl_806D2540;
    f33C = lbl_806D2540;
    f340 = lbl_806D2540;
    f348 = 0;
    f304 = 0;
    f308 = 0;
    f18 = 0;
    f1C = 0;
    f32C = 0;
    f344 = 0;
    f34A = 0;
    f358 = -1;
    f35C = 0;
    f360 = 0;
    f364 = 0;
    f1E8 = -1;
    f368 = 0;
    f36C = lbl_806D2540;
    f370 = -1;
    for (j = 0; j < 10; j++) {
        slots[j] = new ISESlot();
    }
    for (i = 0; i < 49; i++) {
        words[i] = 0;
    }
}
