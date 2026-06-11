/* Merged-web probe: `m` is produced by a helper return (return-merge) so it
 * becomes a CSE/merged web. Per phase2f, merged webs color LAST. Observe whether
 * the merged web gets the LOWEST key (popped/colored last) in the pop order. */
extern int src(void);
extern void sink5(int, int, int, int, int);

static int helper(int x) { return x + src(); }

int p_merge(int seed) {
    int a = src();
    int b = src();
    int c = src();
    int d = src();
    int m = helper(seed);   /* return-merged web */
    sink5(a, b, c, d, m);
    return 0;
}
