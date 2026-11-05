/* Secondary interface entry points adjust this to the complete controller. */
extern void *fn_801E81D8(void *, int);
extern unsigned int AI_GrantItem(void *, int, unsigned char);
extern int fn_801E6670(void *);
extern int fn_801E66B4(void *, void *);
extern int fn_801E68B4(void *, void *);
void *fn_801E8C90(char *p, int deleting) { return fn_801E81D8(p - 12, deleting); }
unsigned int fn_801E8C98(char *p, int item, unsigned char force) { return AI_GrantItem(p - 12, item, force); }
int fn_801E8CA0(char *p) { return fn_801E6670(p - 12); }
int fn_801E8CA8(char *p, void *other) { return fn_801E66B4(p - 12, other); }
int fn_801E8CB0(char *p, void *other) { return fn_801E68B4(p - 12, other); }
