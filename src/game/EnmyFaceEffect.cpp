// 0x8022CE04: update the face reaction only while a kart owner is attached.
class clEFacePolyEffect {
public:
    void Update();
};

class clEFacePoly {
public:
    char fields[0x28];
    void *owner;
    clEFacePolyEffect *effect;
    void Update();
};

void clEFacePoly::Update() {
    if (owner) {
        effect->Update();
    }
}
