typedef struct HudSelectionInit { void *vptr; unsigned char flag; float x, y; } HudSelectionInit;
extern char lbl_804EE7B8[];
extern const float lbl_806DBEDC;
extern void PreloadResource(int);
HudSelectionInit *fn_802457E0(HudSelectionInit *self) {
 self->vptr=lbl_804EE7B8; self->flag=0; self->x=lbl_806DBEDC; self->y=lbl_806DBEDC;
 PreloadResource(0x1CB6); return self;
}
