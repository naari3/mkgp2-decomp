#ifndef GAME_TYPES_STEERINGQUEUEVALUE_H
#define GAME_TYPES_STEERINGQUEUEVALUE_H

struct SteeringQueueValue {
    int first, second;
    SteeringQueueValue() {}
    SteeringQueueValue(const SteeringQueueValue &v) : first(v.first), second(v.second) {}
};

#endif /* GAME_TYPES_STEERINGQUEUEVALUE_H */
