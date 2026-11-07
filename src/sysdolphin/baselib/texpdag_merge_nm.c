#include "texpdag.h"

#include <placeholder.h>
#include <string.h>

#include "debug.h"
#include "texp.h"
#include "tobj.h"

int SimplifyByMerge(HSD_TExp* arg0)
{
    HSD_TExp* child;
    int bias;
    int result;
    int merged;
    int i;
    int conflict;
    u8 type;
    u8 child_sel;
    u8 new_op;
    HSD_TEArg tmp_arg;

    result = 0;
    do {
        merged = 0;

        if (arg0->tev.a_op == 0xFF || arg0->tev.a_op == 0xE ||
            arg0->tev.a_op == 0xF || arg0->tev.a_op <= 1)
        {
            if ((arg0->tev.c_op == 0 || arg0->tev.c_op == 1) &&
                arg0->tev.c_in[1].sel == HSD_TE_0 &&
                arg0->tev.c_in[2].sel == HSD_TE_0 &&
                HSD_TExpGetType(arg0->tev.c_in[0].exp) != HSD_TE_CNST &&
                HSD_TExpGetType(arg0->tev.c_in[3].exp) != HSD_TE_CNST)
            {
                if (arg0->tev.c_op == 0 &&
                    arg0->tev.c_in[3].type == HSD_TE_TEV &&
                    ((arg0->tev.c_in[3].sel == HSD_TE_RGB &&
                      arg0->tev.c_in[3].exp->tev.c_clamp != 0) ||
                     (arg0->tev.c_in[3].sel == HSD_TE_A &&
                      arg0->tev.c_in[3].exp->tev.a_clamp != 0)))
                {
                    type = arg0->tev.c_in[0].type;
                    switch (type) {
                    case HSD_TE_TEX:
                    case HSD_TE_RAS:
                        tmp_arg = arg0->tev.c_in[0];
                        arg0->tev.c_in[0] = arg0->tev.c_in[3];
                        arg0->tev.c_in[3] = tmp_arg;
                        break;
                    }
                }

                switch (arg0->tev.c_in[0].type) {
                case HSD_TE_TEV:
                    if (arg0->tev.c_in[0].sel == HSD_TE_RGB) {
                        child = arg0->tev.c_in[0].exp;
                        child_sel = arg0->tev.c_in[0].sel;
                        if ((child->tev.c_op == 0 || child->tev.c_op == 1) &&
                            child->tev.c_in[3].sel == HSD_TE_0 &&
                            child->tev.c_scale == 0)
                        {
                            if (arg0->tev.tex != NULL &&
                                child->tev.tex != NULL &&
                                arg0->tev.tex != child->tev.tex)
                            {
                                conflict = 1;
                            } else if (arg0->tev.chan != 0xFF &&
                                       child->tev.chan != 0xFF &&
                                       arg0->tev.chan != child->tev.chan)
                            {
                                conflict = 1;
                            } else {
                                conflict = 0;
                            }
                            if (conflict == 0) {
                                switch ((s32) child->tev.c_bias) {
                                case 1:
                                    bias = 1;
                                    break;
                                case 2:
                                    bias = -1;
                                    break;
                                default:
                                    bias = 0;
                                    break;
                                }
                                if (child->tev.c_op == 1) {
                                    bias = -bias;
                                }
                                switch ((s32) arg0->tev.c_bias) {
                                case 1:
                                    bias += 1;
                                    break;
                                case 2:
                                    bias -= 1;
                                    break;
                                }
                                switch (bias) {
                                case 0:
                                    arg0->tev.c_bias = 0;
                                    merged = 1;
                                    break;
                                case 1:
                                    arg0->tev.c_bias = 1;
                                    merged = 1;
                                    break;
                                case -1:
                                    arg0->tev.c_bias = 2;
                                    merged = 1;
                                    break;
                                default:
                                    merged = 0;
                                    break;
                                }
                                if (merged != 0) {
                                    if (child->tev.c_op == 1) {
                                        if (arg0->tev.c_op == 0) {
                                            new_op = 1;
                                        } else {
                                            new_op = 0;
                                        }
                                        arg0->tev.c_op = new_op;
                                    }
                                    for (i = 0; i < 3; i++) {
                                        arg0->tev.c_in[i] = child->tev.c_in[i];
                                        HSD_TExpRef(arg0->tev.c_in[i].exp,
                                                    arg0->tev.c_in[i].sel);
                                    }
                                    if (arg0->tev.tex == NULL) {
                                        arg0->tev.tex = child->tev.tex;
                                    }
                                    if (arg0->tev.chan == 0xFF) {
                                        arg0->tev.chan = child->tev.chan;
                                    }
                                    if (arg0->tev.tex_swap == 0xFF) {
                                        arg0->tev.tex_swap =
                                            child->tev.tex_swap;
                                    }
                                    if (arg0->tev.ras_swap == 0xFF) {
                                        arg0->tev.ras_swap =
                                            child->tev.ras_swap;
                                    }
                                    HSD_TExpUnref(child, child_sel);
                                }
                            }
                        }
                    }
                    break;
                case HSD_TE_ZERO:
                    if (arg0->tev.c_in[3].type == HSD_TE_TEV) {
                        child_sel = arg0->tev.c_in[3].sel;
                        if (child_sel == HSD_TE_RGB) {
                            child = arg0->tev.c_in[3].exp;
                            if (child->tev.c_scale == 0 &&
                                (arg0->tev.c_bias == 0 ||
                                 arg0->tev.c_bias != child->tev.c_bias))
                            {
                                if (arg0->tev.tex != NULL &&
                                    child->tev.tex != NULL &&
                                    arg0->tev.tex != child->tev.tex)
                                {
                                    conflict = 1;
                                } else if (arg0->tev.chan != 0xFF &&
                                           child->tev.chan != 0xFF &&
                                           arg0->tev.chan != child->tev.chan)
                                {
                                    conflict = 1;
                                } else {
                                    conflict = 0;
                                }
                                if (conflict == 0) {
                                    merged = 1;
                                    for (i = 0; i < 4; i++) {
                                        arg0->tev.c_in[i] = child->tev.c_in[i];
                                        HSD_TExpRef(arg0->tev.c_in[i].exp,
                                                    arg0->tev.c_in[i].sel);
                                    }
                                    arg0->tev.c_op = child->tev.c_op;
                                    switch ((s32) child->tev.c_bias) {
                                    case 1:
                                        bias = 1;
                                        break;
                                    case 2:
                                        bias = -1;
                                        break;
                                    default:
                                        bias = 0;
                                        break;
                                    }
                                    if (child->tev.c_op == 1) {
                                        bias = -bias;
                                    }
                                    switch ((s32) arg0->tev.c_bias) {
                                    case 1:
                                        bias += 1;
                                        break;
                                    case 2:
                                        bias -= 1;
                                        break;
                                    }
                                    switch (bias) {
                                    case 1:
                                        arg0->tev.c_bias = 1;
                                        break;
                                    case -1:
                                        arg0->tev.c_bias = 2;
                                        break;
                                    default:
                                    case 0:
                                        arg0->tev.c_bias = 0;
                                        break;
                                    }
                                    if (arg0->tev.c_clamp == 0xFF ||
                                        arg0->tev.c_clamp == 0)
                                    {
                                        arg0->tev.c_clamp = child->tev.c_clamp;
                                    }
                                    if (arg0->tev.tex == NULL) {
                                        arg0->tev.tex = child->tev.tex;
                                    }
                                    if (arg0->tev.chan == 0xFF) {
                                        arg0->tev.chan = child->tev.chan;
                                    }
                                    if (arg0->tev.tex_swap == 0xFF) {
                                        arg0->tev.tex_swap =
                                            child->tev.tex_swap;
                                    }
                                    if (arg0->tev.ras_swap == 0xFF) {
                                        arg0->tev.ras_swap =
                                            child->tev.ras_swap;
                                    }
                                    HSD_TExpUnref(child, child_sel);
                                }
                            }
                        }
                    }
                    break;
                }
            }

            if ((arg0->tev.a_op == 0 || arg0->tev.a_op == 1) &&
                arg0->tev.a_in[1].sel == HSD_TE_0 &&
                arg0->tev.a_in[2].sel == HSD_TE_0 &&
                HSD_TExpGetType(arg0->tev.a_in[0].exp) != HSD_TE_CNST &&
                HSD_TExpGetType(arg0->tev.a_in[3].exp) != HSD_TE_CNST)
            {
                if (arg0->tev.a_op == 0 &&
                    arg0->tev.a_in[3].type == HSD_TE_TEV &&
                    arg0->tev.a_in[3].exp->tev.a_clamp != 0)
                {
                    type = arg0->tev.a_in[0].type;
                    switch ((s32) type) {
                    case HSD_TE_TEX:
                    case HSD_TE_RAS:
                        tmp_arg = arg0->tev.a_in[0];
                        arg0->tev.a_in[0] = arg0->tev.a_in[3];
                        arg0->tev.a_in[3] = tmp_arg;
                        break;
                    }
                }

                switch (arg0->tev.a_in[0].type) {
                case HSD_TE_TEV:
                    child = arg0->tev.a_in[0].exp;
                    child_sel = arg0->tev.a_in[0].sel;
                    if ((child->tev.a_op == 0 || child->tev.a_op == 1) &&
                        child->tev.a_in[3].sel == HSD_TE_0 &&
                        child->tev.a_scale == 0)
                    {
                        if (arg0->tev.tex != NULL && child->tev.tex != NULL &&
                            arg0->tev.tex != child->tev.tex)
                        {
                            conflict = 1;
                        } else if (arg0->tev.chan != 0xFF &&
                                   child->tev.chan != 0xFF &&
                                   arg0->tev.chan != child->tev.chan)
                        {
                            conflict = 1;
                        } else {
                            conflict = 0;
                        }
                        if (conflict == 0) {
                            switch ((s32) child->tev.a_bias) {
                            case 1:
                                bias = 1;
                                break;
                            case 2:
                                bias = -1;
                                break;
                            default:
                                bias = 0;
                                break;
                            }
                            if (child->tev.a_op == 1) {
                                bias = -bias;
                            }
                            switch ((s32) arg0->tev.a_bias) {
                            case 1:
                                bias += 1;
                                break;
                            case 2:
                                bias -= 1;
                                break;
                            }
                            switch (bias) {
                            case 0:
                                arg0->tev.a_bias = 0;
                                merged = 1;
                                break;
                            case 1:
                                arg0->tev.a_bias = 1;
                                merged = 1;
                                break;
                            case -1:
                                arg0->tev.a_bias = 2;
                                merged = 1;
                                break;
                            default:
                                merged = 0;
                                break;
                            }
                            if (merged != 0) {
                                if (child->tev.a_op == 1) {
                                    if (arg0->tev.a_op == 0) {
                                        new_op = 1;
                                    } else {
                                        new_op = 0;
                                    }
                                    arg0->tev.a_op = new_op;
                                }
                                for (i = 0; i < 3; i++) {
                                    arg0->tev.a_in[i] = child->tev.a_in[i];
                                    HSD_TExpRef(arg0->tev.a_in[i].exp,
                                                arg0->tev.a_in[i].sel);
                                }
                                if (arg0->tev.tex == NULL) {
                                    arg0->tev.tex = child->tev.tex;
                                }
                                if (arg0->tev.chan == 0xFF) {
                                    arg0->tev.chan = child->tev.chan;
                                }
                                HSD_TExpUnref(child, child_sel);
                            }
                        }
                    }
                    break;
                case HSD_TE_ZERO:
                    if (arg0->tev.a_in[3].type == HSD_TE_TEV) {
                        child = arg0->tev.a_in[3].exp;
                        child_sel = arg0->tev.a_in[3].sel;
                        if (child->tev.a_scale == 0 &&
                            (arg0->tev.a_bias == 0 ||
                             arg0->tev.a_bias != child->tev.a_bias))
                        {
                            if (arg0->tev.tex != NULL &&
                                child->tev.tex != NULL &&
                                arg0->tev.tex != child->tev.tex)
                            {
                                conflict = 1;
                            } else if (arg0->tev.chan != 0xFF &&
                                       child->tev.chan != 0xFF &&
                                       arg0->tev.chan != child->tev.chan)
                            {
                                conflict = 1;
                            } else {
                                conflict = 0;
                            }
                            if (conflict == 0) {
                                merged = 1;
                                for (i = 0; i < 4; i++) {
                                    arg0->tev.a_in[i] = child->tev.a_in[i];
                                    HSD_TExpRef(arg0->tev.a_in[i].exp,
                                                arg0->tev.a_in[i].sel);
                                }
                                arg0->tev.a_op = child->tev.a_op;
                                switch ((s32) child->tev.a_bias) {
                                case 1:
                                    bias = 1;
                                    break;
                                case 2:
                                    bias = -1;
                                    break;
                                default:
                                    bias = 0;
                                    break;
                                }
                                if (child->tev.a_op == 1) {
                                    bias = -bias;
                                }
                                switch ((s32) arg0->tev.a_bias) {
                                case 1:
                                    bias += 1;
                                    break;
                                case 2:
                                    bias -= 1;
                                    break;
                                }
                                switch (bias) {
                                case 1:
                                    arg0->tev.a_bias = 1;
                                    break;
                                case -1:
                                    arg0->tev.a_bias = 2;
                                    break;
                                default:
                                case 0:
                                    arg0->tev.a_bias = 0;
                                    break;
                                }
                                if (arg0->tev.a_clamp == 0xFF ||
                                    arg0->tev.a_clamp == 0)
                                {
                                    arg0->tev.a_clamp = child->tev.a_clamp;
                                }
                                if (arg0->tev.tex == NULL) {
                                    arg0->tev.tex = child->tev.tex;
                                }
                                if (arg0->tev.chan == 0xFF) {
                                    arg0->tev.chan = child->tev.chan;
                                }
                                HSD_TExpUnref(child, child_sel);
                            }
                        }
                    }
                    break;
                }
            }
        }

        if (merged != 0) {
            result = 1;
        }
    } while (merged != 0);

    return result;
}

