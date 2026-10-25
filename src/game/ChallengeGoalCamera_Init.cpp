/* ChallengeGoalCamera_Init (0x80124CF4): creates the challenge goal
 * camera scene and starts its camera animation. */
#pragma cplusplus on
#include "game/DemoKartScene.h"

extern "C" {
extern const float lbl_806D6EA8;
extern const float lbl_806D6EAC;
extern const float lbl_806D6EB0;
extern const char lbl_80355978[];
}

struct ChallengeGoalCamera {
    DemoScene *scene;
    float t;
};

extern "C" ChallengeGoalCamera *ChallengeGoalCamera_Init(ChallengeGoalCamera *self)
{
    self->scene = new DemoScene(lbl_80355978, lbl_806D6EAC, lbl_806D6EA8);
    DemoScene *s = self->scene;
    if (s != 0) {
        s->Start(lbl_806D6EA8, lbl_806D6EB0);
    }
    self->t = lbl_806D6EA8;
    return self;
}
