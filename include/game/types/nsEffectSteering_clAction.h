#ifndef GAME_TYPES_NS_EFFECT_STEERING_CL_ACTION_H
#define GAME_TYPES_NS_EFFECT_STEERING_CL_ACTION_H
namespace nsEffectSteering {
struct clAction {
    clAction() {}
    virtual ~clAction();
    virtual void Reset() = 0;
    virtual void Step() = 0;
};
}
#endif
