#ifndef GAME_TYPES_TWEEN_SET_ORDER_H
#define GAME_TYPES_TWEEN_SET_ORDER_H

/* fn_8020A734 is Tween::Set(float from, float to, short frames)
 * (anon_80209FA4_set.cpp): parameters (this, from, to, frames). The units that
 * use it under its address name declare and call it with the frame count
 * first, `fn_8020A734(tween, frames, from, to)`. MWCC numbers integer and
 * float arguments separately, so both orders use the same registers and the
 * written order fixes the order of the argument loads; it cannot be corrected
 * in place. A compiler with one argument list needs the definition's order:
 * there this macro reorders every prototype and call that follows it. Include
 * it ahead of the prototype. Notes: docs/notes/port_abi.md. */
#ifndef __MWERKS__
#define fn_8020A734(self, frames, from, to) fn_8020A734(self, from, to, frames)
#endif

#endif
