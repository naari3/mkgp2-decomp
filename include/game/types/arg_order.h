#ifndef GAME_TYPES_ARG_ORDER_H
#define GAME_TYPES_ARG_ORDER_H

/*
 * A parameter list written in another float/integer order than the
 * function's definition.
 *
 * PowerPC passes floats and integers in separate registers, so
 * `RaceCamera(float, int, float, int, void *)` calls the code defined as
 * `(int, int, void *, float, float)` correctly there. The order the caller
 * wrote decides the order in which MWCC loads the arguments, so it cannot
 * simply be corrected. ARGS_ORDER carries both: the list as written (used
 * under MWCC) and the list in the definition's order (used elsewhere).
 *
 *   RaceCamera ARGS_ORDER((float a, int w, float b, int h, void *t),
 *                         (int w, int h, void *t, float a, float b));
 *   new RaceCamera ARGS_ORDER((far, 0x200, near, 0x200, t),
 *                             (0x200, 0x200, t, far, near));
 *
 * Both lists must name the same values; only their order differs.
 * tools/port_abi/rename_order.py finds such constructors and member
 * functions through tools/extab_user_renames.json.
 * docs/notes/port_abi.md, "Constructors declared in another order".
 */
#ifdef __MWERKS__
#define ARGS_ORDER(written, defined) written
#else
#define ARGS_ORDER(written, defined) defined
#endif

#endif
