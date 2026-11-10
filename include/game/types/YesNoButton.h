#ifndef GAME_TYPES_YESNOBUTTON_H
#define GAME_TYPES_YESNOBUTTON_H

/* Declare before including (each user already does): FlowFaderF, FlowFaderI, FlowTask, ResCtrl, VHolder */

struct YesNoButton : FlowTask {
    int layer;
    int kind;
    int field18;
    const char *text0;
    const char *text1;
    int state;
    VHolder<FlowFaderF> fade;
    float x;
    float y;
    float field34;
    float field38;
    float scale;
    float scaleX;
    float scaleY;
    int alpha;
    bool selected;
    VHolder<FlowFaderF> appear;
    VHolder<FlowFaderF> offX;
    VHolder<FlowFaderF> offY;
    VHolder<FlowFaderI> alphaF;
    VHolder<FlowFaderF> pulse;
    VHolder<FlowFaderF> zoomX;
    VHolder<FlowFaderF> zoomY;
    YesNoButton(int kind_, bool flag, int layer_, int id);
    ~YesNoButton() {}
    virtual void _key2();
    void Animate();

    unsigned int Color() {
        int c = 0x7FFFFF;
        if (selected) {
            c = -1;
        }
        return (c & ~0xFF) | alpha;
    }
    /* Fills colour, scale and the (ox, oy) button-space position of c. */
    void Place(ResCtrl &c, unsigned int col, float ox, float oy) {
        c.SetColor(col);
        c.SetScaleXY(scaleX, scaleY);
        c.Show(ox * scaleX + (x + field34), oy * scaleY + (y + field38), lbl_806DAB20);
    }
    /* Draws resource res at the absolute position (px, py). */
    void PutAbs(ResCtrl &c, int res, unsigned int col, float px, float py, int lay) {
        fn_80121E10(&c);
        c.resId = res;
        c.SetColor(col);
        c.SetScaleXY(scaleX, scaleY);
        c.Show(px, py, lbl_806DAB20);
        fn_8011FAFC(&c, lay);
    }

    void SetSelected(bool sel) {
        if (selected != sel) {
            if (sel) {
                fn_8020A734(fade.p, 5, lbl_806DAB10, lbl_806DAB14);
                fn_8020A734(pulse.p, 5, lbl_806DAB18, lbl_806DAB1C);
                fn_8020A734(zoomX.p, 0xF, lbl_806DAB20, lbl_806DAB24);
                fn_8020A734(zoomY.p, 0xF, lbl_806DAB20, lbl_806DAB28);
            } else {
                fn_8020A734(fade.p, 5, lbl_806DAB2C, lbl_806DAB30);
                fn_8020A734(pulse.p, 5, lbl_806DAB20, lbl_806DAB24);
                fn_8020A734(zoomX.p, 1, lbl_806DAB20, lbl_806DAB20);
                fn_8020A734(zoomY.p, 1, lbl_806DAB20, lbl_806DAB20);
            }
        }
        selected = sel;
    }
};

#endif /* GAME_TYPES_YESNOBUTTON_H */
