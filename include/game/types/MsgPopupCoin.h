#ifndef GAME_TYPES_MSGPOPUPCOIN_H
#define GAME_TYPES_MSGPOPUPCOIN_H

/* Declare before including (each user already does): MsgPopup */

struct MsgPopupCoin : MsgPopup {
    MsgPopupCoin(int msg, int layer_, int id) : MsgPopup(msg, layer_, id) {}
    ~MsgPopupCoin();
    virtual void _key4();
};

#endif /* GAME_TYPES_MSGPOPUPCOIN_H */
