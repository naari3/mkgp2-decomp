#include "texpdag.h"

#include <placeholder.h>
#include <string.h>

#include "debug.h"
#include "texp.h"
#include "tobj.h"

static inline s32 TETev_GetCRef(HSD_TETev* tev)
{
    return tev->c_ref;
}

int assign_reg(int num, UNUSED u32* arg1, HSD_TExpDag* list, const int* order)
{
    u8 color_refs[4] = { 0 };
    u8 alpha_refs[4] = { 0 };
    HSD_TETev* tev;
    HSD_TExpDag* dag_entry;
    int idx;
    int i;
    int min_color_reg = 4;
    int min_alpha_reg = 4;
    int alpha_ref_count;
    PAD_STACK(4);

    for (idx = num - 1; idx >= 0; idx--) {
        dag_entry = &list[order[idx]];
        tev = dag_entry->tev;

        for (i = 0; i < 4; i++) {
            if (HSD_TExpGetType(tev->c_in[i].exp) == HSD_TE_TEV) {
                if (tev->c_in[i].sel == 1) {
                    color_refs[tev->c_in[i].exp->tev.c_dst] -= 1;
                } else {
                    alpha_refs[tev->c_in[i].exp->tev.a_dst] -= 1;
                }
            }
            if (HSD_TExpGetType(tev->a_in[i].exp) == HSD_TE_TEV) {
                alpha_refs[tev->a_in[i].exp->tev.a_dst] -= 1;
            }
        }

        tev = dag_entry->tev;
        if (TETev_GetCRef(tev) > 0) {
            for (i = 3; i >= 0; i--) {
                if (color_refs[i] == 0) {
                    color_refs[i] = TETev_GetCRef(tev);
                    tev->c_dst = i;
                    if (min_color_reg > i) {
                        min_color_reg = i;
                    }
                    break;
                }
            }
        }
        alpha_ref_count = tev->a_ref;
        if (alpha_ref_count > 0) {
            for (i = 3; i >= 0; i--) {
                if (alpha_refs[i] == 0) {
                    alpha_refs[i] = tev->a_ref;
                    tev->a_dst = i;
                    if (min_alpha_reg > i) {
                        min_alpha_reg = i;
                    }
                    break;
                }
            }
        }
    }
    return (4 - min_color_reg) + (4 - min_alpha_reg);
}

void order_dag(int num, u32* dep, u32* full_dep, HSD_TExpDag* list, int depth,
               int idx, u32 done_set, u32 ready_set, int* order, int* min,
               int* min_order)
{
    int* sp8;
    int* spC;
    int* sp10;
    HSD_TExpDag* dag;
    u32 dep_bits;
    u32 blocked;
    u32 full_bits;
    int score;
    int i;

    done_set |= 1 << idx;
    ready_set &= ~(1 << idx);
    order[depth++] = (u8) idx;

    if (depth == num) {
        score = assign_reg(num, dep, list, order);
        if (score < *min) {
            *min = score;
            for (i = 0; i < num; i++) {
                min_order[i] = order[i];
            }
        }
    } else {
        {
            dep_bits = dep[idx];
            blocked = ready_set | dep_bits;
            full_bits = 0;
            for (i = 0; i < num; i++) {
                if (blocked & (1 << i)) {
                    full_bits |= full_dep[i];
                }
            }
        }
        dag = &list[idx];
        ready_set = blocked & ~full_bits;
        dep_bits = dep[idx];
        if (dag->nb_dep == 1 && (ready_set & dep_bits)) {
            sp8 = order;
            spC = min;
            sp10 = min_order;
            order_dag(num, dep, full_dep, list, depth, dag->depend[0]->idx,
                      done_set, ready_set, sp8, spC, sp10);
        } else {
            for (i = 0; i < num; i++) {
                if (ready_set & (1 << i)) {
                    sp8 = order;
                    spC = min;
                    sp10 = min_order;
                    order_dag(num, dep, full_dep, list, depth, i, done_set,
                              ready_set, sp8, spC, sp10);
                }
            }
        }
    }
}
