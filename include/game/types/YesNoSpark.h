#ifndef GAME_TYPES_YESNOSPARK_H
#define GAME_TYPES_YESNOSPARK_H

/* Declare before including (each user already does): FlowFaderF, FlowTask, VHolder */

struct YesNoSpark : FlowTask {
    VHolder<FlowFaderF> offset;
    VHolder<FlowFaderF> scale;
    VHolder<FlowFaderF> alpha;
    int layer;
    float x;
    float y;
    unsigned char flag;
    YesNoSpark(int id, int layer_, float x_, float y_, unsigned char flag_)
        : FlowTask(id), offset(new FlowFaderF(lbl_806DAB10)), scale(new FlowFaderF(lbl_806DAB10)), alpha(new FlowFaderF(lbl_806DAB10)),
          layer(layer_), x(x_), y(y_), flag(flag_) {
        fn_8020A734(offset.p, 0x14, lbl_806DAB10, lbl_806DAB54);
        fn_8020A734(scale.p, 0xA, lbl_806DAB18, lbl_806DAB20);
        fn_8020A734(alpha.p, 0xA, lbl_806DAB10, lbl_806DAB20);
    }
    ~YesNoSpark();
    virtual void Update();
    virtual void Draw();
    virtual void _key2();
};

#endif /* GAME_TYPES_YESNOSPARK_H */
