/* Observed single-constructor lifetime views; no shared class definitions. */
#pragma cplusplus on
void *operator new(unsigned long);
void operator delete(void *);

extern "C" const float lbl_806D29A8;

struct BoxWords {
    unsigned int data[3];
};
extern "C" BoxWords lbl_803F9C6C[5];

struct ItemBoxVec {
    float x, y, z;
    ItemBoxVec(float a, float b, float c) : x(a), y(b), z(c) {}
    ~ItemBoxVec();
};

struct BoxVelocity {
    float x, y, z;
    BoxVelocity(float a, float b, float c) : x(a), y(b), z(c) {}
};

struct BoxParticle {
    unsigned char opaque00[0x1c];
    float age;
    unsigned char opaque20[0x0c];
    BoxParticle();
    ~BoxParticle();
};

struct BoxDebris {
    unsigned char active;
    unsigned char pad01[3];
    BoxParticle particles[15];
    BoxDebris()
    {
        active = 0;
        for (int i = 0; i < 15; ++i) {
            particles[i].age = lbl_806D29A8;
        }
    }
};

struct ItemBoxXYZ {
    float height;
    BoxDebris *debris;
    ItemBoxVec position;
    float spin;
    BoxWords direction;
    int state;
    BoxVelocity velocity;
    ItemBoxXYZ(float, float, float);
};

ItemBoxXYZ::ItemBoxXYZ(float x, float y, float z)
    : height(lbl_806D29A8), debris(0), position(x, y, z),
      spin(lbl_806D29A8), direction(lbl_803F9C6C[0]), state(0),
      velocity(lbl_806D29A8, lbl_806D29A8, lbl_806D29A8)
{
    state = 0;
    height = position.y;
    if (debris == 0) {
        debris = new BoxDebris;
    }
}
#pragma cplusplus off

