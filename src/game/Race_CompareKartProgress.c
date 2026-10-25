extern int Path_GetTotalCount(void *self);
extern int abs(int x);

typedef struct PathParticipant {
    unsigned char pad_0[0x14];
    int node;
    unsigned char pad_18[0x42];
    unsigned short segment;
    unsigned char pad_5C[4];
    int lap;
    unsigned char pad_64[0x34];
} PathParticipant;

/* 0x8003CDD8: progress of kart a minus kart b, in path nodes. */
int Race_CompareKartProgress(PathParticipant *karts, int a, int b)
{
    int lapA;
    int lapB;
    int nodeA;
    int nodeB;

    if (a == b) {
        return -1;
    }
    lapA = karts[a].lap + 1;
    nodeA = karts[a].node;
    lapB = karts[b].lap + 1;
    nodeB = karts[b].node;
    if (lapA == 0) {
        lapA = 0;
        nodeA = 0;
    }
    if (lapB == 0) {
        lapB = 0;
        nodeB = 0;
    }
    if (karts[a].segment > Path_GetTotalCount(karts) - 10 && nodeA < 10) {
        nodeA += Path_GetTotalCount(karts);
    }
    if (karts[b].segment > Path_GetTotalCount(karts) - 10 && nodeB < 10) {
        nodeB += Path_GetTotalCount(karts);
    }
    return abs(nodeA + lapA * Path_GetTotalCount(karts)) - abs(nodeB + lapB * Path_GetTotalCount(karts));
}
