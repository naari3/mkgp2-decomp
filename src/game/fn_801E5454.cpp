/* Metrowerks::cdeque<const void *>::push_back, instantiated from the genuine
 * MSL C++ header (std::deque<T> keeps its block map in a cdeque<const void *>).
 * The two callers below are never referenced and are stripped by the linker;
 * they only reproduce the instantiation order of the original TU, whose real
 * users live in the neighbouring units (game/fn_801DEF94.cpp and the
 * DriveBehavior code before it). */
#include <deque>

#include "game/types/SteerStep.h"

static void UseCtor(std::deque<SteerStep> *queue) {
    new (queue) std::deque<SteerStep>(3);
}

static void UsePushFront(std::deque<SteerStep> &queue, const SteerStep &step) {
    queue.push_front(step);
}
