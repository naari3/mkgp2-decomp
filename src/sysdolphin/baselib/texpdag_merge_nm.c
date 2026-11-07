#include "texpdag.h"

static inline int HasColorConstant(HSD_TExp* exp)
{
    int result = 0;
    if (exp->tev.c_in[0].type == HSD_TE_CNST ||
        exp->tev.c_in[1].type == HSD_TE_CNST ||
        exp->tev.c_in[2].type == HSD_TE_CNST ||
        exp->tev.c_in[3].type == HSD_TE_CNST) {
        result = 1;
    }
    return result;
}

static inline int HasAlphaConstant(HSD_TExp* exp)
{
    int result = 0;
    if (exp->tev.a_in[0].type == HSD_TE_CNST ||
        exp->tev.a_in[1].type == HSD_TE_CNST ||
        exp->tev.a_in[2].type == HSD_TE_CNST ||
        exp->tev.a_in[3].type == HSD_TE_CNST) {
        result = 1;
    }
    return result;
}

static inline int OrderConflict(HSD_TExp* parent, HSD_TExp* child)
{
    if (parent->tev.tex != NULL && child->tev.tex != NULL &&
        parent->tev.tex != child->tev.tex) {
        return 1;
    }
    if (parent->tev.chan != 0xFF && child->tev.chan != 0xFF &&
        parent->tev.chan != child->tev.chan) {
        return 1;
    }
    return 0;
}

static inline int MergeBias(int op, int child_bias, int parent_bias, u8* result)
{
    int bias;
    switch (child_bias) {
    case 1: bias = 1; break;
    case 2: bias = -1; break;
    default: bias = 0; break;
    }
    if (op == 1) {
        bias = -bias;
    }
    switch (parent_bias) {
    case 1: bias += 1; break;
    case 2: bias -= 1; break;
    }
    switch (bias) {
    case 0: *result = 0; return 1;
    case 1: *result = 1; return 1;
    case -1: *result = 2; return 1;
    default: return 0;
    }
}

static inline int ScaleValue(int scale)
{
    switch (scale) {
    case 0: return 2;
    case 1: return 4;
    case 2: return 8;
    case 3: return 1;
    default: return 2;
    }
}

static inline int MergeScale(int parent_scale, int child_scale, u8* result)
{
    int scale = ScaleValue(parent_scale) * ScaleValue(child_scale) / 2;
    switch (scale) {
    case 1: *result = 3; break;
    case 2: *result = 0; break;
    case 4: *result = 1; break;
    case 8: *result = 2; break;
    default: return 0;
    }
    return 1;
}

static inline void InheritOrder(HSD_TExp* parent, HSD_TExp* child)
{
    if (parent->tev.tex == NULL) parent->tev.tex = child->tev.tex;
    if (parent->tev.chan == 0xFF) parent->tev.chan = child->tev.chan;
    if (parent->tev.tex_swap == 0xFF) parent->tev.tex_swap = child->tev.tex_swap;
    if (parent->tev.ras_swap == 0xFF) parent->tev.ras_swap = child->tev.ras_swap;
}

int SimplifyByMerge(HSD_TExp* parent)
{
    int result = 0;
    int merged;
    u8 bias;
    u8 scale;
    HSD_TExp* child;
    u8 child_sel;
    int i;
    do {
        merged = 0;
        if ((parent->tev.c_op == 0 || parent->tev.c_op == 1) &&
            parent->tev.c_in[2].sel == HSD_TE_0)
        {
            child = parent->tev.c_in[0].exp;
            child_sel = parent->tev.c_in[0].sel;
            if (!(parent->tev.c_in[0].type == HSD_TE_TEV && parent->tev.c_in[0].sel == HSD_TE_RGB &&
                  child->tev.c_range == 0 &&
                  child->tev.c_in[3].sel == HSD_TE_0 &&
                  !OrderConflict(parent, child) &&
                  (!HasColorConstant(parent) || !HasColorConstant(child))))
            {
                child = parent->tev.c_in[3].exp;
                child_sel = parent->tev.c_in[3].sel;
                if (!(parent->tev.c_op == 0 &&
                      parent->tev.c_in[3].type == HSD_TE_TEV && parent->tev.c_in[3].sel == HSD_TE_RGB &&
                      child->tev.c_range == 0 &&
                      child->tev.c_in[3].sel == HSD_TE_0 &&
                      !OrderConflict(parent, child) &&
                      (!HasColorConstant(parent) || !HasColorConstant(child))))
                    goto c_d;
                if (parent->tev.c_in[0].type == HSD_TE_TEV) {
                    HSD_TExp* first = parent->tev.c_in[0].exp;
                    if (parent->tev.c_in[0].sel == HSD_TE_RGB) {
                        if (first->tev.c_range != 0 && first->tev.c_clamp != 1)
                            goto c_d;
                    } else {
                        if (first->tev.a_range != 0 && first->tev.a_clamp != 1)
                            goto c_d;
                    }
                }
                {
                    HSD_TEArg tmp = parent->tev.c_in[0];
                    parent->tev.c_in[0] = parent->tev.c_in[3];
                    parent->tev.c_in[3] = tmp;
                }
            }
            if (child->tev.c_scale == 0) {
                if (!MergeBias(parent->tev.c_op, child->tev.c_bias,
                               parent->tev.c_bias, &bias)) goto c_d;
                scale = parent->tev.c_scale;
            } else {
                if (parent->tev.c_in[3].sel != HSD_TE_0 ||
                    parent->tev.c_bias != 0 ||
                    !MergeScale(parent->tev.c_scale, child->tev.c_scale, &scale))
                    goto c_d;
                bias = child->tev.c_bias;
            }
            if (parent->tev.c_op == 1) {
                parent->tev.c_op = child->tev.c_op == 0;
            } else {
                parent->tev.c_op = child->tev.c_op;
            }
            for (i = 0; i < 3; i++) {
                parent->tev.c_in[i] = child->tev.c_in[i];
                HSD_TExpRef(parent->tev.c_in[i].exp, parent->tev.c_in[i].sel);
            }
            parent->tev.c_bias = bias;
            parent->tev.c_scale = scale;
            HSD_TExpUnref(child, child_sel);
            InheritOrder(parent, child);
            merged = 1;
        }
c_d:
        {
            u8 type = parent->tev.c_in[3].type;
            child = parent->tev.c_in[3].exp;
            child_sel = parent->tev.c_in[3].sel;
            if (type == HSD_TE_TEV && child_sel == HSD_TE_RGB &&
                !OrderConflict(parent, child) &&
                (!HasColorConstant(parent) || !HasColorConstant(child)))
            {
                if (child->tev.c_range != 0 && child->tev.c_clamp == 1) {
                    if (parent->tev.c_in[0].sel != HSD_TE_0 ||
                        parent->tev.c_in[2].sel != HSD_TE_0 ||
                        parent->tev.c_bias != 0 || parent->tev.c_scale == 3 ||
                        !MergeScale(parent->tev.c_scale, child->tev.c_scale, &scale))
                        goto alpha;
                    parent->tev.c_bias = child->tev.c_bias;
                    parent->tev.c_scale = scale;
                    merged = 1;
                    if (parent->tev.c_clamp != 1)
                        parent->tev.c_clamp = child->tev.c_clamp;
                    InheritOrder(parent, child);
                    for (i = 0; i < 4; i++) {
                        HSD_TExp* old = parent->tev.c_in[i].exp;
                        u8 old_sel = parent->tev.c_in[i].sel;
                        parent->tev.c_in[i] = child->tev.c_in[i];
                        HSD_TExpRef(parent->tev.c_in[i].exp, parent->tev.c_in[i].sel);
                        HSD_TExpUnref(old, old_sel);
                    }
                } else {
                    if (!(parent->tev.a_op == 0xFF ||
                          parent->tev.a_op == 0xE || parent->tev.a_op == 0xF ||
                          parent->tev.a_op <= 1) &&
                        (child->tev.c_in[0].sel != HSD_TE_0 ||
                         child->tev.c_in[1].sel != HSD_TE_0 ||
                         child->tev.c_in[2].sel != HSD_TE_0)) goto alpha;
                    if (child->tev.c_scale == 0) {
                        if (!((parent->tev.c_in[0].sel == HSD_TE_0 &&
                               parent->tev.c_in[2].sel == HSD_TE_0) ||
                              (child->tev.c_in[0].sel == HSD_TE_0 &&
                               child->tev.c_in[2].sel == HSD_TE_0)) ||
                            !MergeBias(0, child->tev.c_bias, parent->tev.c_bias, &bias))
                            goto alpha;
                        scale = parent->tev.c_scale;
                    } else {
                        if (parent->tev.c_in[0].sel != HSD_TE_0 ||
                            parent->tev.c_in[1].sel != HSD_TE_0 ||
                            parent->tev.c_in[2].sel != HSD_TE_0 ||
                            parent->tev.c_bias != 0 ||
                            !MergeScale(parent->tev.c_scale, child->tev.c_scale, &scale))
                            goto alpha;
                        bias = child->tev.c_bias;
                    }
                    merged = 1;
                    parent->tev.c_in[3] = child->tev.c_in[3];
                    HSD_TExpRef(parent->tev.c_in[3].exp, parent->tev.c_in[3].sel);
                    parent->tev.c_bias = bias;
                    parent->tev.c_scale = scale;
                    InheritOrder(parent, child);
                    if (child->tev.c_in[0].sel != HSD_TE_0 ||
                        child->tev.c_in[1].sel != HSD_TE_0 ||
                        child->tev.c_in[2].sel != HSD_TE_0) {
                        for (i = 0; i < 3; i++) {
                            HSD_TExp* old = parent->tev.c_in[i].exp;
                            u8 old_sel = parent->tev.c_in[i].sel;
                            parent->tev.c_in[i] = child->tev.c_in[i];
                            HSD_TExpRef(parent->tev.c_in[i].exp, parent->tev.c_in[i].sel);
                            HSD_TExpUnref(old, old_sel);
                        }
                    }
                    HSD_TExpUnref(child, child_sel);
                }
            }
        }
alpha:
        if ((parent->tev.a_op == 0 || parent->tev.a_op == 1) &&
            parent->tev.a_in[2].sel == HSD_TE_0)
        {
            child = parent->tev.a_in[0].exp;
            child_sel = parent->tev.a_in[0].sel;
            if (!(parent->tev.a_in[0].type == HSD_TE_TEV &&
                  child->tev.a_range == 0 &&
                  child->tev.a_in[3].sel == HSD_TE_0 &&
                  !OrderConflict(parent, child) &&
                  (!HasAlphaConstant(parent) || !HasAlphaConstant(child))))
            {
                child = parent->tev.a_in[3].exp;
                child_sel = parent->tev.a_in[3].sel;
                if (!(parent->tev.a_op == 0 &&
                      parent->tev.a_in[3].type == HSD_TE_TEV &&
                      child->tev.a_range == 0 &&
                      child->tev.a_in[3].sel == HSD_TE_0 &&
                      !OrderConflict(parent, child) &&
                      /* The original alpha swap tests the child at both sites. */
                      (!HasAlphaConstant(child) || !HasAlphaConstant(child))))
                    goto a_d;
                if (parent->tev.a_in[0].type == HSD_TE_TEV &&
                    parent->tev.a_in[0].exp->tev.a_range != 0 &&
                    parent->tev.a_in[0].exp->tev.a_clamp != 1) goto a_d;
                {
                    HSD_TEArg tmp = parent->tev.a_in[0];
                    parent->tev.a_in[0] = parent->tev.a_in[3];
                    parent->tev.a_in[3] = tmp;
                }
            }
            if (child->tev.a_scale == 0) {
                if (!MergeBias(parent->tev.a_op, child->tev.a_bias,
                               parent->tev.a_bias, &bias)) goto a_d;
                scale = parent->tev.a_scale;
            } else {
                if (parent->tev.a_in[3].sel != HSD_TE_0 ||
                    parent->tev.a_bias != 0 ||
                    !MergeScale(parent->tev.a_scale, child->tev.a_scale, &scale))
                    goto a_d;
                bias = child->tev.a_bias;
            }
            if (parent->tev.a_op == 1) {
                parent->tev.a_op = child->tev.a_op == 0;
            } else {
                parent->tev.a_op = child->tev.a_op;
            }
            for (i = 0; i < 3; i++) {
                parent->tev.a_in[i] = child->tev.a_in[i];
                HSD_TExpRef(parent->tev.a_in[i].exp, parent->tev.a_in[i].sel);
            }
            parent->tev.a_bias = bias;
            parent->tev.a_scale = scale;
            HSD_TExpUnref(child, child_sel);
            InheritOrder(parent, child);
            merged = 1;
        }
a_d:
        child = parent->tev.a_in[3].exp;
        child_sel = parent->tev.a_in[3].sel;
        if (parent->tev.a_in[3].type == HSD_TE_TEV &&
            !OrderConflict(parent, child) &&
            (!HasAlphaConstant(parent) || !HasAlphaConstant(child)))
        {
            if (child->tev.a_range != 0 && child->tev.a_clamp == 1) {
                if (parent->tev.a_in[0].sel != HSD_TE_0 ||
                    parent->tev.a_in[2].sel != HSD_TE_0 ||
                    parent->tev.a_bias != 0 || parent->tev.a_scale == 3 ||
                    !MergeScale(parent->tev.a_scale, child->tev.a_scale, &scale))
                    goto done;
                parent->tev.a_bias = child->tev.a_bias;
                parent->tev.a_scale = scale;
                merged = 1;
                if (parent->tev.a_clamp != 1)
                    parent->tev.a_clamp = child->tev.a_clamp;
                InheritOrder(parent, child);
                for (i = 0; i < 4; i++) {
                    HSD_TExp* old = parent->tev.a_in[i].exp;
                    u8 old_sel = parent->tev.a_in[i].sel;
                    parent->tev.a_in[i] = child->tev.a_in[i];
                    HSD_TExpRef(parent->tev.a_in[i].exp, parent->tev.a_in[i].sel);
                    HSD_TExpUnref(old, old_sel);
                }
            } else {

                if (child->tev.a_scale == 0) {
                    if (!((parent->tev.a_in[0].sel == HSD_TE_0 &&
                           parent->tev.a_in[2].sel == HSD_TE_0) ||
                          (child->tev.a_in[0].sel == HSD_TE_0 &&
                           child->tev.a_in[2].sel == HSD_TE_0)) ||
                        !MergeBias(0, child->tev.a_bias, parent->tev.a_bias, &bias))
                        goto done;
                    scale = parent->tev.a_scale;
                } else {
                    if (parent->tev.a_in[0].sel != HSD_TE_0 ||
                        parent->tev.a_in[1].sel != HSD_TE_0 ||
                        parent->tev.a_in[2].sel != HSD_TE_0 ||
                        parent->tev.a_bias != 0 ||
                        !MergeScale(parent->tev.a_scale, child->tev.a_scale, &scale))
                        goto done;
                    bias = child->tev.a_bias;
                }
                merged = 1;
                parent->tev.a_in[3] = child->tev.a_in[3];
                HSD_TExpRef(parent->tev.a_in[3].exp, parent->tev.a_in[3].sel);
                parent->tev.a_bias = bias;
                parent->tev.a_scale = scale;
                InheritOrder(parent, child);
                if (child->tev.a_in[0].sel != HSD_TE_0 ||
                    child->tev.a_in[1].sel != HSD_TE_0 ||
                    child->tev.a_in[2].sel != HSD_TE_0) {
                    for (i = 0; i < 3; i++) {
                        HSD_TExp* old = parent->tev.a_in[i].exp;
                        u8 old_sel = parent->tev.a_in[i].sel;
                        parent->tev.a_in[i] = child->tev.a_in[i];
                        HSD_TExpRef(parent->tev.a_in[i].exp, parent->tev.a_in[i].sel);
                        HSD_TExpUnref(old, old_sel);
                    }
                }
                HSD_TExpUnref(child, child_sel);
            }
        }
done:
        if (merged != 0) result = 1;
    } while (merged != 0);
    return result;
}

