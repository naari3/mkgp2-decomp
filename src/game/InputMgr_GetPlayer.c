struct InputObject;

struct InputObject *InputMgr_GetPlayer(struct InputObject **mgr, unsigned int playerIdx) {
    if (playerIdx >= 1) {
        return 0;
    }
    return mgr[playerIdx];
}
