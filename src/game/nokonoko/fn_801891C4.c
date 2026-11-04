/* Shadow-tree traversal expanded to the depth observed in the target. */
#include "src/game/bbox/nokobbox_private.h"
extern void fn_80189394(BBox *);
void fn_801891C4(BBox *);
#pragma auto_inline off
void fn_801891C4(BBox *box) {
    {
        ShadowEntry *l;
        for (l = box->head; l; l = l->next) l->dobj->flags |= 1;
    }
    {
        BBox *c0;
        for (c0 = box->child; c0; c0 = c0->next) {
            {
                ShadowEntry *l;
                for (l = c0->head; l; l = l->next) l->dobj->flags |= 1;
            }
            {
                BBox *c1;
                for (c1 = c0->child; c1; c1 = c1->next) {
                    {
                        ShadowEntry *l;
                        for (l = c1->head; l; l = l->next) l->dobj->flags |= 1;
                    }
                    {
                        BBox *c2;
                        for (c2 = c1->child; c2; c2 = c2->next) {
                            {
                                ShadowEntry *l;
                                for (l = c2->head; l; l = l->next) l->dobj->flags |= 1;
                            }
                            {
                                BBox *c3;
                                for (c3 = c2->child; c3; c3 = c3->next) {
                                    {
                                        ShadowEntry *l;
                                        for (l = c3->head; l; l = l->next) l->dobj->flags |= 1;
                                    }
                                    {
                                        BBox *c4;
                                        for (c4 = c3->child; c4; c4 = c4->next) {
                                            {
                                                ShadowEntry *l;
                                                for (l = c4->head; l; l = l->next) l->dobj->flags |= 1;
                                            }
                                            {
                                                BBox *c5;
                                                for (c5 = c4->child; c5; c5 = c5->next) {
                                                    {
                                                        ShadowEntry *l;
                                                        for (l = c5->head; l; l = l->next) l->dobj->flags |= 1;
                                                    }
                                                    {
                                                        BBox *c6;
                                                        for (c6 = c5->child; c6; c6 = c6->next) {
                                                            fn_80189394(c6);
                                                            {
                                                                BBox *c;
                                                                for (c = c6->child; c; c = c->next) fn_801891C4(c);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
#pragma auto_inline reset
