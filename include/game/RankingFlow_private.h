#ifndef RANKING_FLOW_PRIVATE_H
#define RANKING_FLOW_PRIVATE_H
#include "game/RankingSpriteOwner_private.h"
struct RankingFlowTrack {
    unsigned char active;
    char pad1[3];
    float from, to, speed, time, value;
    RankingFlowTrack();
};
struct RankingAnim {
    virtual ~RankingAnim();
    virtual void Update();
    virtual void Draw();
    RankingSprite *sprite;
    int delay;
    RankingFlowTrack tracks[5];
    unsigned char active, mode;
    char pad86[2];
    RankingAnim(RankingSprite *p, int frames) : sprite(p), delay(frames), active(0), mode(0) {
        tracks[0].active = 0; tracks[1].active = 0; tracks[2].active = 0;
        tracks[3].active = 0; tracks[4].active = 0;
    }
};
struct RankingFade : RankingAnim {
    virtual void _key2();
    unsigned char flags88, flags89, flags8A;
    char pad8B;
    int layer;
    RankingFade(int frames = 0, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, int layer_ = 7)
        : RankingAnim(0, frames), flags88(r), flags89(g), flags8A(b), layer(layer_) {}
};
struct RankingFlowNode {
    RankingFlowNode *prev, *next;
    RankingAnim *entry;
};
struct RankingFlowIter {
    RankingFlowNode *node;
    RankingFlowIter() {}
    RankingFlowIter(RankingFlowNode *n) : node(n) {}
    RankingFlowIter(const RankingFlowIter &it) : node(it.node) {}
};
struct RankingFlowList {
    int count;
    RankingFlowNode *last, *first;
    RankingFlowList();
    ~RankingFlowList();
    RankingFlowIter Add(RankingAnim *const &entry);
    RankingFlowNode *End() { return (RankingFlowNode *)&last; }
};
struct RankingFlowView {
    void *vtable;
    int state;
    RankingFlowList list;
    RankingSpriteOwnerView *players[4];
    RankingScene *scene;
    void *lights;
    int field2C, delay, timer;
    unsigned char phase;
    int Update();
};
extern "C" {
RankingFlowIter DoublyLinkedList_PushBefore(RankingFlowList *, const RankingFlowIter *, RankingAnim *const *);
extern const float lbl_806D9FA8, lbl_806D9FAC, lbl_806D9FB0, lbl_806D9FB4, lbl_806D9FC0;
}
inline RankingFlowIter RankingFlowList::Add(RankingAnim *const &entry) {
    RankingFlowIter last(End());
    return DoublyLinkedList_PushBefore(this, &last, &entry);
}
static inline void RankingStartFade(RankingAnim *p) {
    p->tracks[0].from = lbl_806D9FA8;
    p->tracks[0].to = lbl_806D9FAC;
    p->tracks[0].speed = lbl_806D9FB0;
    p->tracks[0].time = lbl_806D9FA8;
    p->tracks[0].value = lbl_806D9FA8;
    p->tracks[0].active = 1;
}
#endif
