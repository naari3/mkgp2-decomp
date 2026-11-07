#include "texpdag.h"

#include <placeholder.h>
#include <string.h>

#include "debug.h"
#include "texp.h"
#include "tobj.h"

#undef HSD_ASSERT
#define HSD_ASSERT(line, cond) ((cond) ? (void) 0 : __assert("texpdag.c", line, #cond))
void CalcDistance(HSD_TExp** tevs, int* dist, HSD_TExp* tev, int num,
                  int depth)
{
    int idx; HSD_TExp** p; int i;

    p = tevs;
    idx = 0;
    for (i = 0; i < num; i++) {
        if (*p == tev) {
            if (dist[idx] < depth) {
                dist[idx] = depth;
                for (i = 0; i < 4; i++) {
                    if (tev->tev.c_in[i].type == 1) {
                        CalcDistance(tevs, dist, tev->tev.c_in[i].exp, num,
                                     depth + 1);
                    }
                    if (tev->tev.a_in[i].type == 1) {
                        CalcDistance(tevs, dist, tev->tev.a_in[i].exp, num,
                                     depth + 1);
                    }
                }
            }
            return;
        }
        p++;
        idx++;
    }
}

#define HSD_TEXP_MAX_NUM 32

int HSD_TExpMakeDag(HSD_TExp* root, HSD_TExpDag* list)
{
    HSD_TExp* sp94[HSD_TEXP_MAX_NUM];
    int sp14[32];
    int n;
    int j;
    int i;
    int k;
    int l;
    int idx;
    int num;
    HSD_TExpDag* dag;

    HSD_ASSERT(0xEE, HSD_TExpGetType(root) == HSD_TE_TEV);

    n = 0;
    sp94[n++] = root;
    for (j = 0; j < n; j++) {
        HSD_TExp* tmp;
        HSD_ASSERT(0xF6, j<HSD_TEXP_MAX_NUM);
        tmp = sp94[j];
        for (i = 0; i < 4; i++) {
            if (tmp->tev.c_in[i].type == HSD_TE_TEV) {
                for (k = 0; k < n; k++) {
                    if (sp94[k] == tmp->tev.c_in[i].exp) {
                        break;
                    }
                }
                if (k >= n) {
                    sp94[n++] = tmp->tev.c_in[i].exp;
                }
            }
        }

        for (i = 0; i < 4; i++) {
            if (tmp->tev.a_in[i].type == HSD_TE_TEV) {
                for (k = 0; k < n; k++) {
                    if (sp94[k] == tmp->tev.a_in[i].exp) {
                        break;
                    }
                }
                if (k >= n) {
                    sp94[n++] = tmp->tev.a_in[i].exp;
                }
            }
        }
    }

    num = n;
    for (n = 0; n < num; n++) {
        sp14[n] = -1;
    }

    CalcDistance(&sp94[0], &sp14[0], sp94[0], num, 0);
    for (idx = 0; idx < num; idx++) {
        for (j = idx + 1; j < num; j++) {
            if (sp14[j - 1] > sp14[j]) {
                {
                    HSD_TExp* tmp = sp94[j - 1];
                    sp94[j - 1] = sp94[j];
                    sp94[j] = tmp;
                }

                {
                    int tmp = sp14[j - 1];
                    sp14[j - 1] = sp14[j];
                    sp14[j] = tmp;
                }
            }
        }
    }

    for (j = num - 1; j >= 0; j--) {
        HSD_TExp* tmp;
        dag = &list[j];
        tmp = sp94[j];
        dag->idx = (u8) j;
        dag->nb_ref = 0;
        dag->nb_dep = 0;
        dag->tev = &tmp->tev;
        for (idx = 0; idx < 4; idx++) {
            if (tmp->tev.c_in[idx].type == HSD_TE_TEV) {
                for (l = j; l < num; l++) {
                    if (tmp->tev.c_in[idx].exp == sp94[l]) {
                        HSD_TExpDag* dep_entry = &list[l];
                        for (l = 0; l < dag->nb_dep; l++) {
                            if (dag->depend[l] == dep_entry) {
                                break;
                            }
                        }
                        if (l >= (int) dag->nb_dep) {
                            dag->depend[dag->nb_dep++] = dep_entry;
                            dep_entry->nb_ref++;
                        }
                        break;
                    }
                }
                HSD_ASSERT(0x145, l < num);
            }
        }

        for (idx = 0; idx < 4; idx++) {
            if (tmp->tev.a_in[idx].type == HSD_TE_TEV) {
                for (l = j; l < num; l++) {
                    if (tmp->tev.a_in[idx].exp == sp94[l]) {
                        u8 dep_count2 = dag->nb_dep;
                        HSD_TExpDag* dep_entry2 = &list[l];
                        for (l = 0; l < (int) dep_count2; l++) {
                            if (dag->depend[l] == dep_entry2) {
                                break;
                            }
                        }
                        if (l >= dag->nb_dep) {
                            dag->depend[dag->nb_dep++] = dep_entry2;
                            dep_entry2->nb_ref++;
                        }
                        break;
                    }
                }
                HSD_ASSERT(0x15B, l < num);
            }
        }
    }
    return num;
}

