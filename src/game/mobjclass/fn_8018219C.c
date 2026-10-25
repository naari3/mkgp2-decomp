typedef struct MObjView MObjView;

typedef struct MObjClassView {
    unsigned char base[0x40];
    int (*load)(MObjView *, void *);
    void *(*setupTev)(MObjView *, void *, void **);
    unsigned char tail[0x10];
} MObjClassView;

extern MObjClassView hsdMObj;
extern MObjClassView lbl_80495B58;
extern const char lbl_80376FC4[];
extern const char lbl_80376FD8[];
extern void hsdInitClassInfo(MObjClassView *, MObjClassView *, const char *, const char *, unsigned int, unsigned int);
extern int fn_80182138(MObjView *, void *);
extern void *fn_8018201C(MObjView *, void *, void **);

void fn_8018219C(void) {
    hsdInitClassInfo(&lbl_80495B58, &hsdMObj, lbl_80376FC4, lbl_80376FD8, 0x54, 0x24);
    lbl_80495B58.load = fn_80182138;
    lbl_80495B58.setupTev = fn_8018201C;
}
