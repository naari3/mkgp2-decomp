#ifndef GAME_TYPES_REG_ARGS_H
#define GAME_TYPES_REG_ARGS_H

/* Arguments that the original code leaves in the register.
 *
 * A call matches when the argument registers hold the right values, whether
 * or not the source names them: `buf = Alloc(n); DisplayContext_Init();`
 * compiles to the original code because r3 still holds buf, and a function
 * that only forwards its own arguments can be written without any. Naming
 * the argument makes MWCC move the value again and breaks the match, but any
 * other calling convention needs it.
 *
 *   DisplayContext_Init(REG_ARGS1(buf));
 *   fn_80288574(0, &lbl_80598A60 MORE_REG_ARGS1(&cfg));
 *   void DisplayContext_Init(REG_ARGS1(void *self));        (prototype)
 *
 * REG_ARGSn(...) is the whole argument list, MORE_REG_ARGSn(...) follows the
 * arguments that are written out (no comma in front of it). Both expand to
 * nothing under MWCC. What goes in them is read from the disassembly of the
 * call site: the value the register holds there.
 *
 * tools: mkgp2-pc port/tools/arity_census.py lists calls whose argument
 * count differs from the definition.
 */
#ifdef __MWERKS__
#define REG_ARGS1(a)
#define REG_ARGS2(a, b)
#define REG_ARGS3(a, b, c)
#define REG_ARGS4(a, b, c, d)
#define MORE_REG_ARGS1(a)
#define MORE_REG_ARGS2(a, b)
#define MORE_REG_ARGS3(a, b, c)
#define MORE_REG_ARGS4(a, b, c, d)
#else
#define REG_ARGS1(a) a
#define REG_ARGS2(a, b) a, b
#define REG_ARGS3(a, b, c) a, b, c
#define REG_ARGS4(a, b, c, d) a, b, c, d
#define MORE_REG_ARGS1(a) , a
#define MORE_REG_ARGS2(a, b) , a, b
#define MORE_REG_ARGS3(a, b, c) , a, b, c
#define MORE_REG_ARGS4(a, b, c, d) , a, b, c, d
#endif

#endif
